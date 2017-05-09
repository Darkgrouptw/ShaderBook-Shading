#version 410
in vec2 UV;

out vec4 FragColor;

uniform sampler2D Texture;

uniform uint IsUseTexture;

void main()
{
	if (IsUseTexture == 1)
		FragColor = texture2D(Texture, UV);
	else
		FragColor = vec4(1, 1, 1, 1);
}