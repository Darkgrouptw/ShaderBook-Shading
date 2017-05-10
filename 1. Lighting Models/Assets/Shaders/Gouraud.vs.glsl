#version 410
layout(location = 0) in vec3 VertexPos;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec3 VertexNormal;

out vec3 BarryPos;
out vec4 OutColor;									// 輸出顏色

uniform mat4 ProjectionM;
uniform mat4 ViewM;
uniform mat4 ModelM;

// 材質資訊
struct MaterialInfo {
	vec3	Ka;
	vec3	Kd;
	vec3	Ks;
	float	Shininess;
};
uniform MaterialInfo	matInfo;					// 材質資訊

uniform vec3 LightPos;								// 光的位置
uniform sampler2D		Texture;
uniform uint			IsUseTexture;				// 是否使用貼圖

const vec3 BarryCoordPos[] = vec3[3]( vec3(1,0,0), vec3(0,1,0), vec3(0,0,1));

const vec4 AmbientLightColor = vec4(0.1, 0.1, 0.1, 1);
const vec4 DiffuseLightColor = vec4(0.8, 0.8, 0.8, 1);
const vec4 SpecularLightColor = vec4(1, 1, 1, 1);

void main()
{
	// 世界座標的點
	vec4 WorldPos = ModelM * vec4(VertexPos, 1);

	vec3 ToLightVector = normalize(LightPos - WorldPos.xyz);
	vec3 SurfaceNormal = normalize((ModelM * vec4(VertexNormal, 0)).xyz);

	vec4 TextureColor = (IsUseTexture == 1) ? texture2D(Texture, VertexUV) : vec4(0, 0, 0, 1);
	OutColor = vec4(0, 0, 0, 1);

	float diff = max(0, dot(SurfaceNormal, ToLightVector));

	BarryPos = BarryCoordPos[gl_VertexID % 3];

	//////////////////////////////////////////////////////////////////////////
	// 算顏色 (Illumination = Ka * Ia + Kd * Id + Ks * Is)
	//////////////////////////////////////////////////////////////////////////
	// Ambient
	OutColor += AmbientLightColor * vec4(matInfo.Ka, 1) +
		AmbientLightColor * TextureColor;

	// Diffuse
	OutColor += diff * DiffuseLightColor * vec4(matInfo.Kd, 1) +
		diff * DiffuseLightColor * TextureColor;

	// Specular
	vec3 vReflection = normalize(reflect(-ToLightVector, SurfaceNormal));						// 算反射角
	float spec = max(0.0, dot(SurfaceNormal, vReflection));										// 算反射係數
	if (diff != 0)
	{
		spec = pow(spec, matInfo.Shininess);
		OutColor += SpecularLightColor * vec4(matInfo.Ks, 1) * spec +
			SpecularLightColor * TextureColor * spec;
	}

	gl_Position = ProjectionM * ViewM * ModelM * vec4(VertexPos, 1.0);
}