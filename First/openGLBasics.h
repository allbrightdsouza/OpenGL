#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace GLbasics
{
	///<summary>
	///Initalizes basic version set up
	///</summary>
	void InitWindowHints()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	GLFWwindow* CreateAndSetContextWindow(const char* title)
	{
		GLFWwindow* window = glfwCreateWindow(800, 600, title, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return NULL;
		}
		glfwMakeContextCurrent(window);

		return window;
	}
	///<summary>
	///Allows expansions of gl calls to GLAD OpenGL API calls
	///</summary>
	void InitGLAD()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << endl;
		}

	}

}