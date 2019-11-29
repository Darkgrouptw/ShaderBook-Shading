#include "../Include/Common.h"
#include "../Include/viewmanager.h"
#include "ModelClass.h"

using namespace glm;
using namespace std;


#pragma region �e������
const int Width = 1200;
const int Height = 900;
#pragma endregion
#pragma region Model ����
vector<ModelClass>	models;

float			aspect;
ViewManager		m_camera;
vec3			lightPos;

#pragma endregion
#pragma region AnTweakBar ����
TwBar *UIBar;						// ��ܪ� Bar

//////////////////////////////////////////////////////////////////////////
// �Ѽ�
//////////////////////////////////////////////////////////////////////////
bool UI_AutoRotation = false;		// �O�_�n�۰ʱ���

#pragma region Auto Rotation
void TW_CALL SetAutoRotationCB(const void *value, void *clientData)
{
	UI_AutoRotation = *(const bool *)value;										// �|�۰����A�ন�t���A�æb Call �@�� Get
}
void TW_CALL GetAutoRotationCB(void *value, void *clientData)
{
	*(bool *)value = UI_AutoRotation;
}
#pragma endregion
#pragma endregion


#pragma region ��l��
void TwBar_Init()
{
	// init
	TwInit(TW_OPENGL_CORE, NULL);

	// �]�w�쥻 Windows ���j�p
	TwWindowSize(Width, Height);

	// �]�w���
	UIBar = TwNewBar("=== UI Menu ===");

	// �]�w�����j�p
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

	// Camera �]�w
	m_camera.SetZoom(1.56294f);
	m_camera.SetRotation(0, 0.1f);

	// �]�w���u
	lightPos = vec3(0.38f, 0.23f, 14.13f);
	#pragma region ������m
	#pragma region Phong ���F��
	ModelClass tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_Body.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_Left_bEye.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_Left_fEye.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_Left_Foot.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_Left_Hand.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_lFace.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_Mouth.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_rFace.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_Right_bEye.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_Right_fEye.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_Right_Foot.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Phong.vs.glsl", "Phong.fs.glsl", "Kirby_Right_Hand.obj", "");
	tempModel.ModelM *= translate(vec3(-1.5, 0, 0));
	models.push_back(tempModel);
	#pragma endregion
	#pragma region Toon Shading ���F��
	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_Body.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_Left_bEye.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_Left_fEye.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_Left_Foot.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_Left_Hand.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_lFace.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_Mouth.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_rFace.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_Right_bEye.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_Right_fEye.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_Right_Foot.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);

	tempModel = ModelClass("Toon.vs.glsl", "Toon.fs.glsl", "Kirby_Right_Hand.obj", "");
	tempModel.ModelM *= translate(vec3(1.5, 0, 0));
	models.push_back(tempModel);
	#pragma endregion
	#pragma endregion
}
#pragma endregion

// GLUT callback. Called to draw the scene.
void Display_Event()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �� Model �e�X��
	for (size_t i = 0; i < models.size(); i++)
		models[i].Draw(m_camera.GetProjectionMatrix(aspect), m_camera.GetViewMatrix(), m_camera.GetModelMatrix(), lightPos);

	// �e UI
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

	// ���կx�}
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
	#pragma region ��l�� GLUT, GLEW, AnTweakBar ������
	glutInit(&argc, argv);
	#ifdef _MSC_VER
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	#else
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	#endif

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Shading - Lighting Models");
	#ifdef _MSC_VER
	glewInit();
	#endif

	// UI ����l��
	TwBar_Init();

	//Print debug information 
	DumpInfo();

	//Call custom initialize function
	Init_Event();
	#pragma endregion
	#pragma region GLUT �� Callback functions
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

	// �����n Call ��
	atexit(Terminate);
	return 0;
}