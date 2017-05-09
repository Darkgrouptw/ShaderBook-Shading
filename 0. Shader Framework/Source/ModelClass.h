#pragma once
#include "../Include/Common.h"

using namespace glm;
using namespace std;

struct ModelLocInfo
{
	GLuint Projection_MatrixLoc;													// Projection Matrix
	GLuint View_MatrixLoc;															// View Matrix
	GLuint Model_MatrixLoc;															// Model Matrix
	GLuint IsUseTextureLoc;															// Use Texture Loc
};
struct ModelInfo
{
	GLuint VAO;																		// Vertex Array Object		=> 把所有的資訊，綁成一個陣列
	GLuint VertextBO;																// Vertex Buffer Object		=> 點的資訊
	GLuint NormalBO;																// Normal 的 Buffer Object	=> 向量的資訊
	GLuint UVBO;																	// Texture UV 的 BufferObject=> 存貼圖的座標資訊

	int indexCount;																	// 總共有幾個 Index
	GLuint IsUseTexture = 1;														// 是否有使用貼圖
	GLuint textureID;																// 貼圖的 ID
};

class ModelClass
{
public:
	ModelClass(string, string, string, string);
	~ModelClass();

	void Draw(mat4, mat4, mat4);

private:
	void InitProgram(string, string);												// 初始化程式
	void LoadModel(string, string);													// 讀 Model & Texture


	//////////////////////////////////////////////////////////////////////////
	// Shader 相關
	//////////////////////////////////////////////////////////////////////////
	GLuint				Program;													// Shader Program


	ModelInfo			model;														// Model 的資訊
	ModelLocInfo		modelLoc;													// 矩陣的 ID 資訊
};