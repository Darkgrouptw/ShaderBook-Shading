#version 410
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

// �C��]�w
const vec4 AmbientLightColor	= vec4(0.8, 0.8, 0.8, 1);
const vec4 DiffuseLightColor	= vec4(0.9, 0.9, 0.9, 1);
const vec4 SpecularLightColor	= vec4(1, 1, 1, 1);

void main()
{
	vec4 OutColor = vec4(0, 0, 0, 1);

	float diff = max(0, dot(SurfaceNormal, ToLightVector));

	//////////////////////////////////////////////////////////////////////////
	// ���C�� (Illumination = Ka * Ia + Kd * Id + Ks * Is)
	//////////////////////////////////////////////////////////////////////////
	// Ambient
	OutColor +=	AmbientLightColor * vec4(matInfo.Ka, 1);

	// Diffuse
	OutColor += diff * DiffuseLightColor * vec4(matInfo.Kd, 1);

	// Specular
	vec3 vReflection = normalize(reflect(-ToLightVector, SurfaceNormal));						// ��Ϯg��
	float spec = max(0.0, dot(SurfaceNormal, vReflection));										// ��Ϯg�Y��
	if(diff != 0)
	{
		spec = pow(spec, matInfo.Shininess);
		OutColor += SpecularLightColor * vec4(matInfo.Ks, 1) * spec;
	}

	FragColor = OutColor;
}