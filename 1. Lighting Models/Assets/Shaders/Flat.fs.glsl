#version 410
in vec3 SurfaceNormal;
in vec3 ToLightVector;
in vec2 UV;

out vec4 FragColor;

uniform sampler2D		Texture;
uniform uint			IsUseTexture;				// 是否使用貼圖


void main()
{
	float diff = max(0, dot(SurfaceNormal, ToLightVector));
	if (IsUseTexture == 1)
		FragColor = texture2D(Texture, UV);
	else
		FragColor = diff * vec4(1,1,1,1);
}