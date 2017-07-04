#version 410
in vec3 BaryPos;									// �e��ɥΪ�
in vec3 SurfaceNormal;								// Lighting Model ����
in vec3 ToLightVector;								// Lighting Model ����
in vec2 UV;

out vec4 FragColor;									// ��X�C��

// �����T
struct MaterialInfo {								
	vec3	Ka;
	vec3	Kd;
	vec3	Ks;
	float	Shininess;
};

uniform MaterialInfo	matInfo;					// �����T
uniform sampler2D		Texture;

// �C��]�w
const vec4 BorderColor			= vec4(0, 0, 0, 1);
const vec4 AmbientLightColor	= vec4(0.4, 0.4, 0.4, 1);
const vec4 DiffuseLightColor	= vec4(0.8, 0.8, 0.8, 1);
const vec4 SpecularLightColor	= vec4(1, 1, 1, 1);


void main()
{
	vec4 TextureColor = texture2D(Texture, UV);
	vec4 OutColor = vec4(0, 0, 0, 1);

	float diff = max(0, dot(SurfaceNormal, ToLightVector));

	//////////////////////////////////////////////////////////////////////////
	// ���C�� (Illumination = Ka * Ia + Kd * Id + Ks * Is)
	//////////////////////////////////////////////////////////////////////////
	// Ambient
	OutColor +=	AmbientLightColor * TextureColor;

	// Diffuse
	OutColor +=	diff * DiffuseLightColor * TextureColor;

	// Specular
	vec3 vReflection = normalize(reflect(-ToLightVector, SurfaceNormal));						// ��Ϯg��
	float spec = max(0.0, dot(SurfaceNormal, vReflection));										// ��Ϯg�Y��
	if(diff != 0)
	{
		spec = pow(spec, matInfo.Shininess);
		OutColor +=	SpecularLightColor * TextureColor * spec;
	}

	FragColor = OutColor;
}