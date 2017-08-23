#version 410
in vec3 BaryPos;
in vec4 OutColor;

out vec4 FragColor;

uniform uint			IsDrawWireframe;			// 是否要話邊線

const vec4 BorderColor = vec4(0, 0, 0, 1);
float edgeFactor()
{
	vec3 d = fwidth(BaryPos);
	vec3 a3 = smoothstep(vec3(0.0), d * 0.8f, BaryPos);
	return min(min(a3.x, a3.y), a3.z);
}
void main()
{
	vec4 OutColorTemp = OutColor;

	// 是否要話 Wireframe
	if (IsDrawWireframe == 1)
		OutColorTemp = mix(BorderColor, OutColorTemp, edgeFactor());
	FragColor = OutColorTemp;
}