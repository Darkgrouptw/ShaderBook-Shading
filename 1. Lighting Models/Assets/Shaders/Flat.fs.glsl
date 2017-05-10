#version 410
in vec3 BarryPos;									// 畫邊界用的
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

// 顏色設定
vec4 BorderColor		= vec4(0, 0, 0, 1);
vec4 AmbientLightColor	= vec4(0.1, 0.1, 0.1, 1);
vec4 DiffuseLightColor	= vec4(0.8, 0.8, 0.8, 1);
vec4 SpecularLightColor	= vec4(1, 1, 1, 1);

float edgeFactor()
{
	vec3 d = fwidth(BarryPos);
	vec3 a3 = smoothstep(vec3(0.0), d * 0.8f, BarryPos);
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
	OutColor +=	AmbientLightColor * vec4(matInfo.Ka, 1) +
				AmbientLightColor * TextureColor;

	// Diffuse
	OutColor += diff * DiffuseLightColor * vec4(matInfo.Kd, 1) +
				diff * DiffuseLightColor * TextureColor;

	// Specular
	vec3 vReflection = normalize(reflect(-ToLightVector, SurfaceNormal));						// 算反射角
	float spec = max(0.0, dot(SurfaceNormal, vReflection));										// 算反射係數
	if(diff != 0)
	{
		spec = pow(spec, matInfo.Shininess);
		OutColor += SpecularLightColor * vec4(matInfo.Ks, 1) * spec +
					SpecularLightColor * TextureColor * spec;
	}

	// 是否要話 Wireframe
	if (IsDrawWireframe == 1)
		OutColor = mix(BorderColor, OutColor, edgeFactor());

	FragColor = OutColor;
}