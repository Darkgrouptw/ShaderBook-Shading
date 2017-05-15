#version 410
in vec3 BaryPos;									// 畫邊界用的
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

uniform sampler2D		Texture;
uniform uint			IsUseTexture;				// 是否使用貼圖
uniform uint			IsDrawWireframe;			// 是否要話邊線

uniform uint			IsUseAmbientLighting;		// 是否使用 Ambient Lighting
uniform uint			IsUseDiffuseLighting;		// 是否使用 Diffuse Lighting
uniform uint			IsUseSpecularLighting;		// 是否使用 Specular Lighting

// 顏色設定
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
	// 算顏色 (Illumination = Ka * Ia + Kd * Id + Ks * Is)
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
		vec3 vReflection = normalize(reflect(-ToLightVector, SurfaceNormal));						// 算反射角
		float spec = max(0.0, dot(SurfaceNormal, vReflection));										// 算反射係數
		if(diff != 0)
		{
			spec = pow(spec, matInfo.Shininess);
			OutColor += SpecularLightColor * vec4(matInfo.Ks, 1) * spec +
						SpecularLightColor * TextureColor * spec;
		}
	}

	// 是否要話 Wireframe
	if (IsDrawWireframe == 1)
		OutColor = mix(BorderColor, OutColor, edgeFactor());

	FragColor = OutColor;
}