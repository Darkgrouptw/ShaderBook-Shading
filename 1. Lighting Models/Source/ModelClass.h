#pragma once
#include "../Include/Common.h"

using namespace glm;
using namespace std;

struct ModelLocInfo
{
	GLuint Projection_MatrixLoc;													// Projection Matrix
	GLuint View_MatrixLoc;															// View Matrix
	GLuint Model_MatrixLoc;															// Model Matrix

	GLuint MaterialInfo_KaLoc;														// 材質 Ka 資訊的位置
	GLuint MaterialInfo_KdLoc;														// 材質 Kd 資訊的位置
	GLuint MaterialInfo_KsLoc;														// 材質 Ks 資訊的位置
	GLuint MaterialInfo_ShininessLoc;												// 材質亮度資訊的位置

	GLuint LightPosLoc;																// 光亮度的位置

	GLuint IsUseTextureLoc;															// Use Texture Loc
	GLuint IsDrawWireframeLoc;														// 是否要話 Wireframe
};
struct MaterialInfo
{
	vec3 Ka;																		// Ambient
	vec3 Kd;																		// Diffuse
	vec3 Ks;																		// Specular
	float Shininess;																// 亮度係數
};
struct ModelInfo
{
	GLuint VAO;																		// Vertex Array Object		=> 把所有的資訊，綁成一個陣列
	GLuint VertextBO;																// Vertex Buffer Object		=> 點的資訊
	GLuint UVBO;																	// Texture UV 的 BufferObject=> 存貼圖的座標資訊
	GLuint NormalBO;																// Normal 的 Buffer Object	=> 向量的資訊

	MaterialInfo matInfo;															// 材質資訊

	int indexCount;																	// 總共有幾個 Index
	GLuint IsUseTexture = 1;														// 是否有使用貼圖
	GLuint textureID;																// 貼圖的 ID
};

class ModelClass
{
public:
	ModelClass(string, string, string, string, bool);
	~ModelClass();

	void Draw(mat4, mat4, mat4, vec3, bool);

	mat4 ModelM;																	// Model 移動的矩陣
private:
	void InitProgram(string, string);												// 初始化程式
	void LoadModel(string, string, bool);											// 讀 Model & Texture


	//////////////////////////////////////////////////////////////////////////
	// Shader 相關
	//////////////////////////////////////////////////////////////////////////
	GLuint				Program;													// Shader Program


	ModelInfo			model;														// Model 的資訊
	ModelLocInfo		modelLoc;													// 矩陣的 ID 資訊
};