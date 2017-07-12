#version 410
layout(location = 0) in vec3 VertexPos;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec3 VertexNormal;

out vec3 SurfaceNormal;
out vec3 ToLightVector;
out vec2 UV;

uniform mat4 ProjectionM;
uniform mat4 ViewM;
uniform mat4 ModelM;

uniform vec3 LightPos;					// ������m

void main()
{
	// �@�ɮy�Ъ��I
	vec4 WorldPos = ModelM * vec4(VertexPos, 1);

	ToLightVector = normalize(LightPos - WorldPos.xyz);
	SurfaceNormal = normalize((ModelM * vec4(VertexNormal, 0)).xyz);

    UV = VertexUV;

	gl_Position = ProjectionM * ViewM * ModelM * vec4(VertexPos, 1.0);
}