#pragma once
#include "../Include/Common.h"

using namespace glm;
using namespace std;

struct ModelLocInfo
{
	GLuint Projection_MatrixLoc;													// Projection Matrix
	GLuint View_MatrixLoc;															// View Matrix
	GLuint Model_MatrixLoc;															// Model Matrix

	GLuint LightPosLoc;																// ���G�ת���m

	GLuint IsUseTextureLoc;															// Use Texture Loc
	GLuint IsDrawWireframeLoc;														// �O�_�n�� Wireframe
};
struct ModelInfo
{
	GLuint VAO;																		// Vertex Array Object		=> ��Ҧ�����T�A�j���@�Ӱ}�C
	GLuint VertextBO;																// Vertex Buffer Object		=> �I����T
	GLuint UVBO;																	// Texture UV �� BufferObject=> �s�K�Ϫ��y�и�T
	GLuint NormalBO;																// Normal �� Buffer Object	=> �V�q����T

	int indexCount;																	// �`�@���X�� Index
	GLuint IsUseTexture = 1;														// �O�_���ϥζK��
	GLuint textureID;																// �K�Ϫ� ID
};

class ModelClass
{
public:
	ModelClass(string, string, string, string, bool);
	~ModelClass();

	void Draw(mat4, mat4, mat4, vec3, bool);

	mat4 ModelM;																	// Model ���ʪ��x�}
private:
	void InitProgram(string, string);												// ��l�Ƶ{��
	void LoadModel(string, string);													// Ū Model & Texture
	void LoadModel_Flat(string, string);											// Ū Model & Texture


	//////////////////////////////////////////////////////////////////////////
	// Shader ����
	//////////////////////////////////////////////////////////////////////////
	GLuint				Program;													// Shader Program


	ModelInfo			model;														// Model ����T
	ModelLocInfo		modelLoc;													// �x�}�� ID ��T
};