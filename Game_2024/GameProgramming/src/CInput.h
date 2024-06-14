#pragma once
#include <Windows.h>
#include "GLFW/glfw3.h"
#ifndef CINPUT_H
#define CINPUT_H

class CInput
{
public:
	static void Window(GLFWwindow* pwindow);
	void GetMousePos(float* px, float* py);

	CInput();
	bool Key(char key);
private:
	static GLFWwindow* mpWindow;	//ウィンドウのポインタ
};
#endif