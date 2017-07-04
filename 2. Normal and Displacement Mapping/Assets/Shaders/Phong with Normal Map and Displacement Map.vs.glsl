#version 410
layout(location = 0) in vec3 VertexPos;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec3 VertexNormal;
layout(location = 3) in vec3 VertexTangents;
layout(location = 4) in vec3 VertexBitangents;

out vec3 BaryPos;
out vec3 SurfaceNormal;
out vec3 ToLightVector;
out vec2 UV;

uniform mat4 ProjectionM;
uniform mat4 ViewM;
uniform mat4 ModelM;

uniform vec3 LightPos;					// 光的位置
uniform sampler2D DisplacementMap;		// 要位移的貼圖

const float ConstHeight = .05;

void main()
{
	// Normal Map 需要用到的東西
	vec3 T = normalize(VertexTangents);
	vec3 B = normalize(VertexBitangents);
	vec3 N = normalize(VertexNormal);
	mat3 TBN = transpose(mat3(
		T,
		B,
		N
	));

	// 世界座標的點
	vec4 WorldPos = ModelM * vec4(VertexPos, 1);

	ToLightVector = TBN * normalize(LightPos - WorldPos.xyz);
	SurfaceNormal = TBN * normalize((ModelM * vec4(VertexNormal, 0)).xyz);

    UV = VertexUV;

	// 位移點的位置
	float HeightValue = texture2D(DisplacementMap, VertexUV).r;
	mat4 TranslateMatrix = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(0, ConstHeight * HeightValue, 0, 1));

	gl_Position = ProjectionM * ViewM * ModelM * TranslateMatrix * vec4(VertexPos, 1.0);
}