#include "ModelClass.h"

ModelClass::ModelClass(string VertexShaderFileName, string FragmentShaderFileName, string objFileName, string textureFileName, bool IsFlat)
{
	InitProgram(VertexShaderFileName, FragmentShaderFileName);
	LoadModel(objFileName, textureFileName, IsFlat);
}
ModelClass::~ModelClass()
{
}

#pragma region 這些絕對不是我寫的 = =
void ShaderLog(GLuint shader)
{
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		GLchar* errorLog = new GLchar[maxLength];
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		printf("%s\n", errorLog);
		delete[] errorLog;
	}
}
void PrintGLError()
{
	GLenum code = glGetError();
	switch (code)
	{
	case GL_NO_ERROR:
		std::cout << "GL_NO_ERROR" << std::endl;
		break;
	case GL_INVALID_ENUM:
		std::cout << "GL_INVALID_ENUM" << std::endl;
		break;
	case GL_INVALID_VALUE:
		std::cout << "GL_INVALID_VALUE" << std::endl;
		break;
	case GL_INVALID_OPERATION:
		std::cout << "GL_INVALID_OPERATION" << std::endl;
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
		break;
	case GL_OUT_OF_MEMORY:
		std::cout << "GL_OUT_OF_MEMORY" << std::endl;
		break;
	case GL_STACK_UNDERFLOW:
		std::cout << "GL_STACK_UNDERFLOW" << std::endl;
		break;
	case GL_STACK_OVERFLOW:
		std::cout << "GL_STACK_OVERFLOW" << std::endl;
		break;
	default:
		std::cout << "GL_ERROR" << std::endl;
	}
}
typedef struct _TextureData
{
	_TextureData() : width(0), height(0), data(0) {}
	int width;
	int height;
	unsigned char* data;
} TextureData;
TextureData Load_png(const char* path)
{
	TextureData texture;
	int n;
	stbi_uc *data = stbi_load(path, &texture.width, &texture.height, &n, 4);
	if (data != NULL)
	{
		texture.data = new unsigned char[texture.width * texture.height * 4 * sizeof(unsigned char)];
		memcpy(texture.data, data, texture.width * texture.height * 4 * sizeof(unsigned char));
		// vertical-mirror image data
		for (size_t i = 0; i < (size_t)texture.width; i++)
		{
			for (size_t j = 0; j < (size_t)texture.height / 2; j++)
			{
				for (size_t k = 0; k < 4; k++) {
					std::swap(texture.data[(j * texture.width + i) * 4 + k], texture.data[((texture.height - j - 1) * texture.width + i) * 4 + k]);
				}
			}
		}
		stbi_image_free(data);
	}
	return texture;
}

//Read shader file
char** LoadShaderSource(const char* file)
{
	FILE *fp;
#ifdef _MSC_VER
	fopen_s(&fp, file, "rb");
#else
	fp = fopen(file, "rb");
#endif
	fseek(fp, 0, SEEK_END);
	long sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *src = new char[sz + 1];
	fread(src, sizeof(char), sz, fp);
	src[sz] = '\0';
	char **srcp = new char*[1];
	srcp[0] = src;
	return srcp;
}

//Release 2-dimension array
void FreeShaderSource(char** srcp)
{
	delete srcp[0];
	delete srcp;
}
#pragma endregion

void ModelClass::InitProgram(string VertexShaderFileName, string FragmentShaderFileName)
{
	// 讀 Shader 近來
	Program = glCreateProgram();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	char** vsSource = LoadShaderSource(("Shaders/" + VertexShaderFileName).c_str());
	char** fsSource = LoadShaderSource(("Shaders/" + FragmentShaderFileName).c_str());
	glShaderSource(vs, 1, vsSource, NULL);
	glShaderSource(fs, 1, fsSource, NULL);
	FreeShaderSource(vsSource);
	FreeShaderSource(fsSource);
	glCompileShader(vs);
	glCompileShader(fs);
	ShaderLog(vs);
	ShaderLog(fs);

	// Attach Shader to program
	glAttachShader(Program, vs);
	glAttachShader(Program, fs);
	glLinkProgram(Program);

	// 拿 Model 的 Loc
	modelLoc.Projection_MatrixLoc		= glGetUniformLocation(Program, "ProjectionM");
	modelLoc.View_MatrixLoc				= glGetUniformLocation(Program, "ViewM");
	modelLoc.Model_MatrixLoc			= glGetUniformLocation(Program, "ModelM");

	modelLoc.IsUseAmbientLightingLoc	= glGetUniformLocation(Program, "IsUseAmbientLighting");
	modelLoc.IsUseDiffuseLightingLoc	= glGetUniformLocation(Program, "IsUseDiffuseLighting");
	modelLoc.IsUseSpecularLightingLoc	= glGetUniformLocation(Program, "IsUseSpecularLighting");

	modelLoc.MaterialInfo_KaLoc			= glGetUniformLocation(Program, "matInfo.Ka");
	modelLoc.MaterialInfo_KdLoc			= glGetUniformLocation(Program, "matInfo.Kd");
	modelLoc.MaterialInfo_KsLoc			= glGetUniformLocation(Program, "matInfo.Ks");
	modelLoc.MaterialInfo_ShininessLoc = glGetUniformLocation(Program, "matInfo.Shininess");

	modelLoc.LightPosLoc				= glGetUniformLocation(Program, "LightPos");
	modelLoc.IsUseTextureLoc			= glGetUniformLocation(Program, "IsUseTexture");
	modelLoc.IsDrawWireframeLoc			= glGetUniformLocation(Program, "IsDrawWireframe");
}
void ModelClass::LoadModel(string objFileName, string textureFileName ,bool IsFlat)
{
	#pragma region 宣告
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	#pragma endregion
	#pragma region  讀檔部分
	bool ret = tinyobj::LoadObj(shapes, materials, err, ("Models/" + objFileName).c_str());
	if (err.size() > 0)
	{
		printf("Load Models Fail! Please check the solution path");
		return;
	}
	printf("Load Models Success ! Shapes size %d Material size %d\n", shapes.size(), materials.size());

	if(IsFlat)
		// Flat 的重點 => 因為以前的 GPU 計算比較慢，所以導致只用一個 Normal 來表示
		for (size_t i = 0; i < shapes[0].mesh.normals.size(); i += 3 * 3)
		{
			vec3 p1(shapes[0].mesh.positions[i],		shapes[0].mesh.positions[i + 1], shapes[0].mesh.positions[i + 2]);
			vec3 p2(shapes[0].mesh.positions[i + 3],	shapes[0].mesh.positions[i + 4], shapes[0].mesh.positions[i + 5]);
			vec3 p3(shapes[0].mesh.positions[i + 6],	shapes[0].mesh.positions[i + 7], shapes[0].mesh.positions[i + 8]);

			vec3 crossNormal = cross((p2 - p1), (p3 - p1));
			crossNormal = normalize(crossNormal);

			shapes[0].mesh.normals[i]		= crossNormal.x;
			shapes[0].mesh.normals[i + 1]	= crossNormal.y;
			shapes[0].mesh.normals[i + 2]	= crossNormal.z;
			shapes[0].mesh.normals[i + 3]	= crossNormal.x;
			shapes[0].mesh.normals[i + 4]	= crossNormal.y;
			shapes[0].mesh.normals[i + 5]	= crossNormal.z;
			shapes[0].mesh.normals[i + 6]	= crossNormal.x;
			shapes[0].mesh.normals[i + 7]	= crossNormal.y;
			shapes[0].mesh.normals[i + 8]	= crossNormal.z;
		}
	
	// Default 是 Gold
	model.matInfo.Ka = vec3(0.24725f, 0.1995f, 0.0745f);
	model.matInfo.Kd = vec3(0.75164f, 0.60648f, 0.22648);
	model.matInfo.Ks = vec3(0.628281f, 0.555802f, 0.366065f);
	model.matInfo.Shininess = .9 * 128;
	#pragma endregion
	#pragma region 綁點的資訊上 GPU
	//////////////////////////////////////////////////////////////////////////
	// 看一下其他章的，這種寫法 Shapes 只能有一個，超過一個畫無法畫出來 = =
	//////////////////////////////////////////////////////////////////////////

	// 將接下來的東西用 Array 包起來
	glGenVertexArrays(1, &model.VAO);
	glBindVertexArray(model.VAO);

	// 上傳 Vertex
	glGenBuffers(1, &model.VertextBO);
	glBindBuffer(GL_ARRAY_BUFFER, model.VertextBO);
	glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.positions.size() * sizeof(float), shapes[0].mesh.positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// 上傳 UV 座標
	glGenBuffers(1, &model.UVBO);
	glBindBuffer(GL_ARRAY_BUFFER, model.UVBO);
	glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.texcoords.size() * sizeof(float), shapes[0].mesh.texcoords.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// 上傳 Normal
	glGenBuffers(1, &model.NormalBO);
	glBindBuffer(GL_ARRAY_BUFFER, model.NormalBO);
	glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.normals.size() * sizeof(float), shapes[0].mesh.normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	model.indexCount = shapes[0].mesh.positions.size() / 3;
	#pragma endregion
	#pragma region 綁貼圖
	TextureData tdata = Load_png(("Images/" + textureFileName).c_str());

	// 如果沒有用貼圖的畫，就直接回傳
	if (tdata.data == NULL)
	{
		model.IsUseTexture = 0;
		return;
	}

	glGenTextures(1, &model.textureID);
	glBindTexture(GL_TEXTURE_2D, model.textureID);

	//Do texture setting
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, tdata.width, tdata.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tdata.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	#pragma endregion
}

void ModelClass::Draw(mat4 projM, mat4 viewM, mat4 modelM, vec3 lightPos, bool IsDrawWireframe, bool IsUseAmbientLighting, bool IsUseDiffuseLighting, bool IsUseSpecularLighting)
{
	glUseProgram(Program);
	glBindVertexArray(model.VAO);

	glUniformMatrix4fv(modelLoc.Projection_MatrixLoc, 1, GL_FALSE, value_ptr(projM));
	glUniformMatrix4fv(modelLoc.View_MatrixLoc, 1, GL_FALSE, value_ptr(viewM));
	glUniformMatrix4fv(modelLoc.Model_MatrixLoc, 1, GL_FALSE, value_ptr(modelM * ModelM));

	glUniform1ui(modelLoc.IsUseAmbientLightingLoc, ((IsUseAmbientLighting) ? 1 : 0));
	glUniform1ui(modelLoc.IsUseDiffuseLightingLoc, ((IsUseDiffuseLighting) ? 1 : 0));
	glUniform1ui(modelLoc.IsUseSpecularLightingLoc, ((IsUseSpecularLighting) ? 1 : 0));

	glUniform3fv(modelLoc.MaterialInfo_KaLoc, 1, value_ptr(model.matInfo.Ka));
	glUniform3fv(modelLoc.MaterialInfo_KdLoc, 1, value_ptr(model.matInfo.Kd));
	glUniform3fv(modelLoc.MaterialInfo_KsLoc, 1, value_ptr(model.matInfo.Ks));
	glUniform1f(modelLoc.MaterialInfo_ShininessLoc, model.matInfo.Shininess);

	glUniform3fv(modelLoc.LightPosLoc, 1, value_ptr(lightPos));

	glUniform1ui(modelLoc.IsUseTextureLoc, model.IsUseTexture);
	glUniform1ui(modelLoc.IsDrawWireframeLoc, ((IsDrawWireframe) ? 1 : 0));

	glDrawArrays(GL_TRIANGLES, 0, model.indexCount);
}
