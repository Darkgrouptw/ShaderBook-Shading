#version 410
in vec3 SurfaceNormal;								// Lighting Model 相關
in vec3 ToLightVector;								// Lighting Model 相關
in vec2 UV;

out vec4 FragColor;									// 輸出顏色

// 材質資訊
struct MaterialInfo {								
	vec3	Ka;
	vec3	Kd;
	vec3	Ks;
	float	Shininess;
};

uniform MaterialInfo	matInfo;					// 材質資訊

// 顏色設定
const vec4 AmbientLightColor	= vec4(0.8, 0.8, 0.8, 1);
const vec4 DiffuseLightColor	= vec4(0.9, 0.9, 0.9, 1);
const vec4 SpecularLightColor	= vec4(1, 1, 1, 1);

void main()
{
	vec4 OutColor = vec4(0, 0, 0, 1);

	float diff = max(0, dot(SurfaceNormal, ToLightVector));

	//////////////////////////////////////////////////////////////////////////
	// 算顏色 (Illumination = Ka * Ia + Kd * Id + Ks * Is)
	//////////////////////////////////////////////////////////////////////////
	// Ambient
	OutColor +=	AmbientLightColor * vec4(matInfo.Ka, 1);

	// Diffuse
	OutColor += diff * DiffuseLightColor * vec4(matInfo.Kd, 1);

	// Specular
	vec3 vReflection = normalize(reflect(-ToLightVector, SurfaceNormal));						// 算反射角
	float spec = max(0.0, dot(SurfaceNormal, vReflection));										// 算反射係數
	if(diff != 0)
	{
		spec = pow(spec, matInfo.Shininess);
		OutColor += SpecularLightColor * vec4(matInfo.Ks, 1) * spec;
	}
	
	// 根據做出來的結果，去算 Toon Shading 的顏色
	if(diff > 0.66)
		FragColor = OutColor;
	else if(diff > 0.33)
		FragColor = OutColor * 0.66f;
	else
		FragColor = OutColor * 0.33f;
}