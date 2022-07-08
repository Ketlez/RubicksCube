#pragma once
#include "GLFW.h"
class Window
{
public:
	GLFWwindow* window = nullptr;
	Window()
	{
		window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
		
	}
	~Window()
	{
		glfwDestroyWindow(window);
	}
	bool isInit()
	{
		return window != nullptr;

	}
	GLFWwindow* get()
	{
		return window;
	}
	void setCurrent()
	{
		glfwMakeContextCurrent(window);
	}
	bool gladisInit()
	{
		return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
};