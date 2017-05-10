#version 410
in vec3 BarryPos;									// �e��ɥΪ�
in vec2 UV;

out vec4 FragColor;

uniform sampler2D Texture;

uniform uint IsUseTexture;

// ����C��
vec4 BorderColor = vec4(0, 0, 0, 1);
float edgeFactor()
{
	vec3 d = fwidth(BarryPos);
	vec3 a3 = smoothstep(vec3(0.0), d * 0.8f, BarryPos);
	return min(min(a3.x, a3.y), a3.z);
}

void main()
{
	vec4 OutColor = vec4(1, 1, 1, 1);
	if (IsUseTexture == 1)
		FragColor = texture2D(Texture, UV);
	else
		FragColor = mix(BorderColor, OutColor, edgeFactor());;
}