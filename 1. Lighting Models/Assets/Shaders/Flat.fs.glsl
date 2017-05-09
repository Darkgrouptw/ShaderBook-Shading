#version 410
in vec3 BarryPos;									// 畫邊界用的
in vec3 SurfaceNormal;								// Lighting Model 相關
in vec3 ToLightVector;								// Lighting Model 相關
in vec2 UV;

out vec4 FragColor;									// 輸出顏色

uniform sampler2D		Texture;
uniform uint			IsUseTexture;				// 是否使用貼圖
uniform uint			IsDrawWireframe;			// 是否要話邊線

// 邊界顏色
vec4 BorderColor = vec4(0, 0, 0, 1);
float edgeFactor()
{
	vec3 d = fwidth(BarryPos);
	vec3 a3 = smoothstep(vec3(0.0), d * 0.8f, BarryPos);
	return min(min(a3.x, a3.y), a3.z);
}

void main()
{
	float diff = max(0, dot(SurfaceNormal, ToLightVector));
	vec4 OutColor;

	if (IsUseTexture == 1)
		OutColor = texture2D(Texture, UV);
	else
		OutColor = diff * vec4(1,1,1,1);

	if (IsDrawWireframe == 1)
		OutColor = mix(BorderColor, OutColor, edgeFactor());
	FragColor = OutColor;
}