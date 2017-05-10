#version 410
layout(location = 0) in vec3 VertexPos;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec3 VertexNormal;

out vec3 BarryPos;
out vec2 UV;

uniform mat4 ProjectionM;
uniform mat4 ViewM;
uniform mat4 ModelM;

const vec3 BarryCoordPos[] = vec3[3](vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1));

void main()
{
    UV = VertexUV;

	BarryPos = BarryCoordPos[gl_VertexID % 3];
	gl_Position = ProjectionM * ViewM * ModelM * vec4(VertexPos, 1.0);
}