#include "CInput.h"
#include <stdio.h>

GLFWwindow* CInput::mpWindow = nullptr;	//ウィンドウのポインタ

void CInput::Window(GLFWwindow* pwindow)
{
	mpWindow = pwindow;
}

void CInput::GetMousePos(float* px, float* py)
{
	double xpos, ypos;
	glfwGetCursorPos(mpWindow, &xpos, &ypos);
	*px = (float)xpos;
	*py = (float)ypos;
	return;
}

CInput::CInput()
{
	printf("入力インスタンスが生まれました\n");
}

bool CInput::Key(char key)
{
	return GetAsyncKeyState(key) < 0;
}
