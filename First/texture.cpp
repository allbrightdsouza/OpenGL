#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "openGLHelper.h"
#include "openGLBasics.h"
#include "stb_image.h"
//#include <glm/glm.hpp>

using namespace std;


//Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow*);

//Consts
const float vertices[] =
{
//	 x		y	  z      s		t
	 0.0f,  0.5f, 0.0f,  1.0f, 2.0f,// bottom 
	 0.5f, -0.5f, 0.0f,  2.0f, 0.0f,// bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,// bottom left
};

const unsigned int indices[] = {  // note that we start from 0!
	0, 1, 2,   // first triangle
};

int main()
{
	GLbasics::InitWindowHints();
	GLFWwindow* window = GLbasics::CreateAndSetContextWindow("Triangle");
	GLbasics::InitGLAD();


	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glClearColor(1.0f, 0.3f, 0.3f, 1.0f);

	unsigned int happyFaceTexture = texture::loadTextureBasic("happyface.png", texture::ImageType::PNG_transparent, GL_TEXTURE0);
	unsigned int wallTexture = texture::loadTextureBasic("wall.jpg", texture::ImageType::JPG,GL_TEXTURE1);
	unsigned int shaderProgram = shader::GetShaderProgram("vshadertexture.txt", "fshadertexture.txt");
	//unsigned int shaderProgram = shader::GetShaderProgram("triangleVShader.txt", "triangleFShader.txt");

	//Buffer Pointing

	// Vertex Attribute Object
	// This stores calls to the 1-glVertexAttribute(),2-glEnableVertexAttrib, and VBOs based on 1.
	unsigned int VAO;
	unsigned int VBO, EBO;

	// Generate Objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the VAO then bind the VBO, and EBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //VBO is bound as the Array Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //VBO is bound as the Array Buffer

	// Static doesnt keep the data in memory
	// since it is drawn infrequently
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// How the vertices need to be fed to the shader
	// Amount of information described by one vertex
	
	// Vertex Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture Position
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Unbind the VAO, (good practice)
	glBindVertexArray(0);



	// Draw wireframe mode.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);

		float speed = 2.0f;
		float timeValue = glfwGetTime();
		float alpha = (sin(timeValue * speed) / 2.0f) + 0.5f;
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wallTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, happyFaceTexture);
		glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
		glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
		glUniform1f(glGetUniformLocation(shaderProgram, "alpha"), alpha);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents(); //process inputs given and calls the appropriate callback
	}


	// Clean up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	//Termination
	glfwTerminate();

	return 0;
}

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

