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

	GLuint TangentBO;																// Tangent Buffer Object	=> 用在畫 Normal Map 會用到的
	GLuint BitangentBO;																// Bitangent Buffer Object	=> 用在畫 Normal Map 會用到的

	MaterialInfo matInfo;															// 材質資訊
	vector<GLuint> TextureID;														// 貼圖的 ID

	int indexCount;																	// 總共有幾個 Index
};

class ModelClass
{
public:
	ModelClass(string, string, string, int);
	~ModelClass();

	void BindMultiTexture(vector<string>, vector<string>);							// 綁多個圖片
	void Draw(mat4, mat4, mat4, vec3);

	mat4 ModelM;																	// Model 移動的矩陣
private:
	void InitProgram(string, string);												// 初始化程式
	void LoadModel(string);															// 讀 Model & Texture
	void LoadModelWithNormalMap(string);											// 讀 Model & Texture
	void ComputeTangentBasis(tinyobj::shape_t, vector<float> &, vector<float> &);	// 算 Tangent


	//////////////////////////////////////////////////////////////////////////
	// Shader 相關
	//////////////////////////////////////////////////////////////////////////
	GLuint				Program;													// Shader Program


	ModelInfo			model;														// Model 的資訊
	ModelLocInfo		modelLoc;													// 矩陣的 ID 資訊


	const GLuint ActiveTexture[11] = { GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3,
		GL_TEXTURE4 ,GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9, GL_TEXTURE10 };
};