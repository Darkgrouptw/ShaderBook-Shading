#version 410
layout(location = 0) in vec3 VertexPos;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec3 VertexNormal;

out vec2 UV;

uniform mat4 ProjectionM;
uniform mat4 ViewM;
uniform mat4 ModelM;

void main()
{
    UV = VertexUV;

	gl_Position = ProjectionM * ViewM * ModelM * vec4(VertexPos, 1.0);
}