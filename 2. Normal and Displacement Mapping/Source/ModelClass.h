#pragma once
#include "../Include/Common.h"

using namespace glm;
using namespace std;

struct ModelLocInfo
{
	GLuint Projection_MatrixLoc;													// Projection Matrix
	GLuint View_MatrixLoc;															// View Matrix
	GLuint Model_MatrixLoc;															// Model Matrix

	GLuint MaterialInfo_KaLoc;														// ���� Ka ��T����m
	GLuint MaterialInfo_KdLoc;														// ���� Kd ��T����m
	GLuint MaterialInfo_KsLoc;														// ���� Ks ��T����m
	GLuint MaterialInfo_ShininessLoc;												// ����G�׸�T����m

	GLuint LightPosLoc;																// ���G�ת���m
};
struct MaterialInfo
{
	vec3 Ka;																		// Ambient
	vec3 Kd;																		// Diffuse
	vec3 Ks;																		// Specular
	float Shininess;																// �G�׫Y��
};
struct ModelInfo
{
	GLuint VAO;																		// Vertex Array Object		=> ��Ҧ�����T�A�j���@�Ӱ}�C
	GLuint VertextBO;																// Vertex Buffer Object		=> �I����T
	GLuint UVBO;																	// Texture UV �� BufferObject=> �s�K�Ϫ��y�и�T
	GLuint NormalBO;																// Normal �� Buffer Object	=> �V�q����T

	GLuint TangentBO;																// Tangent Buffer Object	=> �Φb�e Normal Map �|�Ψ쪺
	GLuint BitangentBO;																// Bitangent Buffer Object	=> �Φb�e Normal Map �|�Ψ쪺

	MaterialInfo matInfo;															// �����T
	vector<GLuint> TextureID;														// �K�Ϫ� ID

	int indexCount;																	// �`�@���X�� Index
};

class ModelClass
{
public:
	ModelClass(string, string, string, int);
	~ModelClass();

	void BindMultiTexture(vector<string>, vector<string>);							// �j�h�ӹϤ�
	void Draw(mat4, mat4, mat4, vec3);

	mat4 ModelM;																	// Model ���ʪ��x�}
private:
	void InitProgram(string, string);												// ��l�Ƶ{��
	void LoadModel(string);															// Ū Model & Texture
	void LoadModelWithNormalMap(string);											// Ū Model & Texture
	void ComputeTangentBasis(tinyobj::shape_t, vector<float> &, vector<float> &);	// �� Tangent


	//////////////////////////////////////////////////////////////////////////
	// Shader ����
	//////////////////////////////////////////////////////////////////////////
	GLuint				Program;													// Shader Program


	ModelInfo			model;														// Model ����T
	ModelLocInfo		modelLoc;													// �x�}�� ID ��T


	const GLuint ActiveTexture[11] = { GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3,
		GL_TEXTURE4 ,GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9, GL_TEXTURE10 };
};