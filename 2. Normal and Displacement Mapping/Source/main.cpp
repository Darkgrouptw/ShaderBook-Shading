#include "../Include/Common.h"
#include "../Include/viewmanager.h"
#include "ModelClass.h"

using namespace glm;
using namespace std;


#pragma region 畫面相關
const int Width = 1200;
const int Height = 900;
#pragma endregion
#pragma region Model 相關
vector<ModelClass>	models;

float			aspect;
ViewManager		m_camera;
vec3			lightPos;

#pragma endregion
#pragma region AnTweakBar 相關
TwBar *UIBar;						// 顯示的 Bar

//////////////////////////////////////////////////////////////////////////
// 參數
//////////////////////////////////////////////////////////////////////////

bool UI_AutoRotation = false;		// 是否要自動旋轉

//////////////////////////////////////////////////////////////////////////
// UI Callback Function
//////////////////////////////////////////////////////////////////////////
//#pragma region Flat Shading
//void TW_CALL SetUseFlatShadingCB(const void *value, void *clientData)
//{
//	UI_UseFlatShading = *(const bool *)value;										// 會自動幫你轉成負的，並在 Call 一次 Get
//	if (UI_UseFlatShading)
//	{
//		UI_UseGouraudShading = false;
//		UI_UsePhongShading = false;
//		SetModelVisiable("Flat");
//	}
//}
//void TW_CALL GetUseFlatShadingCB(void *value, void *clientData)
//{
//	*(bool *)value = UI_UseFlatShading;												// 拿這個值，設定到 UI 上面
//}
//#pragma endregion
//#pragma region Gouraud Shading
//void TW_CALL SetUseGouraudShadingCB(const void *value, void *clientData)
//{
//	UI_UseGouraudShading = *(const bool *)value;									// 會自動幫你轉成負的，並在 Call 一次 Get
//	if (UI_UseGouraudShading)
//	{
//		UI_UseFlatShading = false;
//		UI_UsePhongShading = false;
//		SetModelVisiable("Gouraud");
//	}
//}
//void TW_CALL GetUseGouraudShadingCB(void *value, void *clientData)
//{
//	*(bool *)value = UI_UseGouraudShading;											// 拿這個值，設定到 UI 上面
//}
//#pragma endregion
//#pragma region Phong Shading
//void TW_CALL SetUsePhongShadingCB(const void *value, void *clientData)
//{
//	UI_UsePhongShading = *(const bool *)value;										// 會自動幫你轉成負的，並在 Call 一次 Get
//	if (UI_UsePhongShading)
//	{
//		UI_UseFlatShading = false;
//		UI_UseGouraudShading = false;
//	}
//}
//void TW_CALL GetUsePhongShadingCB(void *value, void *clientData)
//{
//	*(bool *)value = UI_UsePhongShading;											// 拿這個值，設定到 UI 上面
//}
//#pragma endregion
//
//#pragma region Ambient Lighting
//void TW_CALL SetUseAmbientLightingCB(const void *value, void *clientData)
//{
//	UI_UseAmbientLighing = *(const bool *)value;									// 會自動幫你轉成負的，並在 Call 一次 Get
//}
//void TW_CALL GetUseAmbientLightingCB(void *value, void *clientData)
//{
//	*(bool *)value = UI_UseAmbientLighing;											// 拿這個值，設定到 UI 上面
//}
//#pragma endregion
//#pragma region Diffuse Lighting
//void TW_CALL SetUseDiffuseLightingCB(const void *value, void *clientData)
//{
//	UI_UseDiffuseLighing = *(const bool *)value;									// 會自動幫你轉成負的，並在 Call 一次 Get
//}
//void TW_CALL GetUseDiffuseLightingCB(void *value, void *clientData)
//{
//	*(bool *)value = UI_UseDiffuseLighing;											// 拿這個值，設定到 UI 上面
//}
//#pragma endregion
//#pragma region Specular Lighting
//void TW_CALL SetUseSpecularLightingCB(const void *value, void *clientData)
//{
//	UI_UseSpecularLighing = *(const bool *)value;									// 會自動幫你轉成負的，並在 Call 一次 Get
//}
//void TW_CALL GetUseSpecularLightingCB(void *value, void *clientData)
//{
//	*(bool *)value = UI_UseSpecularLighing;											// 拿這個值，設定到 UI 上面
//}
//#pragma endregion

#pragma region Auto Rotation
void TW_CALL SetAutoRotationCB(const void *value, void *clientData)
{
	UI_AutoRotation = *(const bool *)value;										// 會自動幫你轉成負的，並在 Call 一次 Get
}
void TW_CALL GetAutoRotationCB(void *value, void *clientData)
{
	*(bool *)value = UI_AutoRotation;
}
#pragma endregion
#pragma endregion


#pragma region 初始化
void TwBar_Init()
{
	// init
	TwInit(TW_OPENGL_CORE, NULL);

	// 設定原本 Windows 的大小
	TwWindowSize(Width, Height);

	// 設定選單
	UIBar = TwNewBar("=== UI Menu ===");

	// 設定視窗大小
	int barSize[2] = { 224, 320 };
	TwSetParam(UIBar, NULL, "size", TW_PARAM_INT32, 2, barSize);

	TwAddVarCB(UIBar, "Auto Rotation",		TW_TYPE_BOOL32,	SetAutoRotationCB,		GetAutoRotationCB,		NULL, "");
	TwAddVarRW(UIBar, "LightDir",			TW_TYPE_DIR3F, &lightPos," open ");
	//TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLUT and OpenGL.' "); // Message added to the help bar.
	//TwDefine(" TweakBar size='200 400' color='96 216 224' "); // change default tweak bar size and color
}
void Init_Event()
{
	glClearColor(0.2f, 0.84f, 0.8f, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);

	// Camera 設定
	//m_camera.SetZoom(1.56294f);
	//m_camera.SetRotation(0, 0.32f);

	// 設定光線
	lightPos = vec3(-1.64f, 6.12f, 12.64f);
	#pragma region 場景放置
	#pragma region Shading 的東西
	vector<string> ShaderName;
	vector<string> TextureName;
	ShaderName.push_back("Texture");
	TextureName.push_back("Texture.png");


	ModelClass *tempModel = new ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Plane_100x100.obj", 0);
	tempModel->BindMultiTexture(ShaderName, TextureName);
	tempModel->ModelM = rotate(tempModel->ModelM, 45.0f, vec3(1, 0, 0));
	tempModel->ModelM *= translate(vec3(-3, 0, 0));
	models.push_back(*tempModel);

	ShaderName.push_back("NormalMap");
	TextureName.push_back("Normal Map.png");

	tempModel = new ModelClass("Phong with Normal Map.vs.glsl", "Phong with Normal Map.fs.glsl", "Plane_100x100.obj", 1);
	tempModel->BindMultiTexture(ShaderName, TextureName);
	tempModel->ModelM = rotate(tempModel->ModelM, 45.0f, vec3(1, 0, 0));
	tempModel->ModelM *= translate(vec3(0, 0, 0));
	models.push_back(*tempModel);

	ShaderName.push_back("DisplacementMap");
	TextureName.push_back("Displacement Map.png");

	tempModel = new ModelClass("Phong with Normal Map and Displacement Map.vs.glsl", "Phong with Normal Map and Displacement Map.fs.glsl", "Plane_100x100.obj", 1);
	tempModel->BindMultiTexture(ShaderName, TextureName);
	tempModel->ModelM = rotate(tempModel->ModelM, 45.0f, vec3(1, 0, 0));
	tempModel->ModelM *= translate(vec3(3, 0, 0));
	models.push_back(*tempModel);
	#pragma endregion
	#pragma endregion
}
#pragma endregion

// GLUT callback. Called to draw the scene.
void Display_Event()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 把 Model 畫出來
	for (size_t i = 0; i < models.size(); i++)
		models[i].Draw(m_camera.GetProjectionMatrix(aspect), m_camera.GetViewMatrix(), m_camera.GetModelMatrix(), lightPos);

	// 畫 UI
	TwDraw();

	glutSwapBuffers();
}

//Call to resize the window
void Reshape_Event(int width, int height)
{
	aspect = width * 1.0f / height;
	m_camera.SetWindowSize(width, height);
	glViewport(0, 0, width, height);
}

//Timer event
void Timer_Event(int val)
{
	if(UI_AutoRotation)
		for (size_t i = 0; i < models.size(); i++)
			models[i].ModelM *= rotate(0.01f, vec3(0, 1, 0));

	glutPostRedisplay();
	glutTimerFunc(16, Timer_Event, val);
}

#pragma region KeyBoard & Mouse Event
void Keyboard_Event(unsigned char key, int x, int y)
{
	m_camera.keyEvents(key);
	printf("Key %c is pressed at (%d, %d)\n", key, x, y);

	// 測試矩陣
	if (key == 'm')
	{
		mat4 tempM = m_camera.GetProjectionMatrix(aspect);
		cout << "Zoom: " << m_camera.GetZoom() << endl;
		cout << "Aspect: " << aspect << endl;


		cout << "Projection Matrix" << endl;
		cout << tempM[0][0] << " " << tempM[0][1] << " " << tempM[0][2] << " " << tempM[0][3] << endl;
		cout << tempM[1][0] << " " << tempM[1][1] << " " << tempM[1][2] << " " << tempM[1][3] << endl;
		cout << tempM[2][0] << " " << tempM[2][1] << " " << tempM[2][2] << " " << tempM[2][3] << endl;
		cout << tempM[3][0] << " " << tempM[3][1] << " " << tempM[3][2] << " " << tempM[3][3] << endl;

		tempM = m_camera.GetViewMatrix();
		cout << "View Matrix" << endl;
		cout << tempM[0][0] << " " << tempM[0][1] << " " << tempM[0][2] << " " << tempM[0][3] << endl;
		cout << tempM[1][0] << " " << tempM[1][1] << " " << tempM[1][2] << " " << tempM[1][3] << endl;
		cout << tempM[2][0] << " " << tempM[2][1] << " " << tempM[2][2] << " " << tempM[2][3] << endl;
		cout << tempM[3][0] << " " << tempM[3][1] << " " << tempM[3][2] << " " << tempM[3][3] << endl;

		tempM = m_camera.GetModelMatrix();
		cout << "Model Matrix" << endl;
		cout << tempM[0][0] << " " << tempM[0][1] << " " << tempM[0][2] << " " << tempM[0][3] << endl;
		cout << tempM[1][0] << " " << tempM[1][1] << " " << tempM[1][2] << " " << tempM[1][3] << endl;
		cout << tempM[2][0] << " " << tempM[2][1] << " " << tempM[2][2] << " " << tempM[2][3] << endl;
		cout << tempM[3][0] << " " << tempM[3][1] << " " << tempM[3][2] << " " << tempM[3][3] << endl;
	}
}
void SpecialKeys_Event(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		printf("F1 is pressed at (%d, %d)\n", x, y);
		break;
	case GLUT_KEY_PAGE_UP:
		printf("Page up is pressed at (%d, %d)\n", x, y);
		break;
	case GLUT_KEY_LEFT:
		printf("Left arrow is pressed at (%d, %d)\n", x, y);
		break;
	default:
		printf("Other special key is pressed at (%d, %d)\n", x, y);
		break;
	}
}

void Mouse_Event(int button, int state, int x, int y)
{
	if (!TwEventMouseButtonGLUT(button, state, x, y))
	{
		m_camera.mouseEvents(button, state, x, y);

		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_DOWN)
			{
				printf("Mouse %d is pressed at (%d, %d)\n", button, x, y);
			}
			else if (state == GLUT_UP)
			{
				printf("Mouse %d is released at (%d, %d)\n", button, x, y);
			}
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			printf("Mouse %d is pressed\n", button);
		}
		printf("%d %d %d %d\n", button, state, x, y);
	}
}
void Mouse_Moving_Event(int x, int y) {
	if (!TwEventMouseMotionGLUT(x, y))
		m_camera.mouseMoveEvent(x, y);
}
#pragma endregion
void Terminate()
{
	TwTerminate();
}

// Print OpenGL context related information.
void DumpInfo(void)
{
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

int main(int argc, char *argv[])
{
	#pragma region 初始化 GLUT, GLEW, AnTweakBar 的視窗
	glutInit(&argc, argv);
	#ifdef _MSC_VER
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	#else
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	#endif

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Shading - Normal and Displacement Mapping");
	#ifdef _MSC_VER
	glewInit();
	#endif

	// UI 的初始化
	TwBar_Init();

	//Print debug information 
	DumpInfo();

	//Call custom initialize function
	Init_Event();
	#pragma endregion
	#pragma region GLUT 的 Callback functions
	glutDisplayFunc(Display_Event);
	glutReshapeFunc(Reshape_Event);
	glutMouseFunc(Mouse_Event);
	glutKeyboardFunc(Keyboard_Event);
	glutSpecialFunc(SpecialKeys_Event);
	glutTimerFunc(16, Timer_Event, 0);
	glutPassiveMotionFunc(Mouse_Moving_Event);
	glutMotionFunc(Mouse_Moving_Event);

	// send the ''glutGetModifers'' function pointer to AntTweakBar
	TwGLUTModifiersFunc(glutGetModifiers);
	#pragma endregion

	// Enter main event loop.
	glutMainLoop();

	// 結束要 Call 的
	atexit(Terminate);
	return 0;
}