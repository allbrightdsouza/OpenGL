#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

using namespace std;

// Function definitions

// Null return type functions
void InitWindowHints();
void InitGLAD();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow*);

//Other functions
GLFWwindow* CreateAndSetContextWindow(const char*);

int main() 
{
	//Initialziation
	InitWindowHints(); //Clears all the flags
	GLFWwindow* window_1 = CreateAndSetContextWindow("LearnOpenGL");
	InitGLAD(); // Call GLAD before calling an OpenGL functions
	

	//Window handling
	
	//framebuffer_size_callback(window_1, 800, 600);
	glfwSetFramebufferSizeCallback(window_1, framebuffer_size_callback);
	glClearColor(1.0f, 0.3f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(window_1))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window_1);
		glfwSwapBuffers(window_1);
		glfwPollEvents(); //process inputs given and calls the appropriate callback
	}

	glfwTerminate();
	return 0;
}

void InitWindowHints()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* CreateAndSetContextWindow(const char* title)
{
	GLFWwindow* window = glfwCreateWindow(800, 600,  title , NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	return window;
}

void InitGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << endl;
	}

}

///<summary>
///Callback function on frame resize
///</summary>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Change size " << width << " " << height << endl;
	glViewport(0, 0, width, height);
}

///<summary>
///Close window on Esc 
///</summary>
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		cout << "Close window\n";
		glfwSetWindowShouldClose(window, true);
	}
}