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
uniform uint			IsUseTexture;				// �O�_�ϥζK��
uniform uint			IsDrawWireframe;			// �O�_�n����u

uniform uint			IsUseAmbientLighting;		// �O�_�ϥ� Ambient Lighting
uniform uint			IsUseDiffuseLighting;		// �O�_�ϥ� Diffuse Lighting
uniform uint			IsUseSpecularLighting;		// �O�_�ϥ� Specular Lighting

// �C��]�w
const vec4 BorderColor			= vec4(0, 0, 0, 1);
const vec4 AmbientLightColor	= vec4(0.4, 0.4, 0.4, 1);
const vec4 DiffuseLightColor	= vec4(0.8, 0.8, 0.8, 1);
const vec4 SpecularLightColor	= vec4(1, 1, 1, 1);

float edgeFactor()
{
	vec3 d = fwidth(BaryPos);
	vec3 a3 = smoothstep(vec3(0.0), d * 0.8f, BaryPos);
	return min(min(a3.x, a3.y), a3.z);
}

void main()
{
	vec4 TextureColor = (IsUseTexture == 1) ? texture2D(Texture, UV) : vec4(0,0,0,1);
	vec4 OutColor = vec4(0, 0, 0, 1);

	float diff = max(0, dot(SurfaceNormal, ToLightVector));

	//////////////////////////////////////////////////////////////////////////
	// ���C�� (Illumination = Ka * Ia + Kd * Id + Ks * Is)
	//////////////////////////////////////////////////////////////////////////
	// Ambient
	if(IsUseAmbientLighting == 1)
		OutColor +=	AmbientLightColor * vec4(matInfo.Ka, 1) +
					AmbientLightColor * TextureColor;

	// Diffuse
	if (IsUseDiffuseLighting == 1)
		OutColor += diff * DiffuseLightColor * vec4(matInfo.Kd, 1) +
					diff * DiffuseLightColor * TextureColor;

	// Specular
	if (IsUseSpecularLighting == 1)
	{
		vec3 vReflection = normalize(reflect(-ToLightVector, SurfaceNormal));						// ��Ϯg��
		float spec = max(0.0, dot(SurfaceNormal, vReflection));										// ��Ϯg�Y��
		if(diff != 0)
		{
			spec = pow(spec, matInfo.Shininess);
			OutColor += SpecularLightColor * vec4(matInfo.Ks, 1) * spec +
						SpecularLightColor * TextureColor * spec;
		}
	}

	// �O�_�n�� Wireframe
	if (IsDrawWireframe == 1)
		OutColor = mix(BorderColor, OutColor, edgeFactor());

	FragColor = OutColor;
}