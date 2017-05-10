#version 410
layout(location = 0) in vec3 VertexPos;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec3 VertexNormal;

out vec3 BarryPos;
out vec3 SurfaceNormal;
out vec3 ToLightVector;
out vec2 UV;

uniform mat4 ProjectionM;
uniform mat4 ViewM;
uniform mat4 ModelM;

uniform vec3 LightPos;					// 光的位置

const vec3 BarryCoordPos[] = vec3[3]( vec3(1,0,0), vec3(0,1,0), vec3(0,0,1));

void main()
{
	// 世界座標的點
	vec4 WorldPos = ModelM * vec4(VertexPos, 1);

	ToLightVector = normalize(LightPos - WorldPos.xyz);
	SurfaceNormal = normalize((ModelM * vec4(VertexNormal, 0)).xyz);

    UV = VertexUV;

	BarryPos = BarryCoordPos[gl_VertexID % 3];
	gl_Position = ProjectionM * ViewM * ModelM * vec4(VertexPos, 1.0);
}