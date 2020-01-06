#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include "stb_image.h"

using namespace std;

namespace shader
{
		string GetShaderFromFile(const char* filename)
		{
			std::string content = "";
			std::string line = "";
			std::ifstream inFile;
			inFile.open(filename);
			
			if (!inFile) 
			{
				perror("Opening File Failed");
			}

			while (getline(inFile, line))
			{
				content += line + "\n";
			}
			inFile.close();

			return content;
		}


		void CompileFragmentShader(int vertexShader)
		{
			int  success;
			char infoLog[512];
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				string error = "ERROR::FRAGMENT SHADER::COMPILATION_FAILED\n";
				error += infoLog;
				error += "\n";
				perror(error.c_str());
			}
		}

		void CompileVertexShader(int vertexShader)
		{
			int  success;
			char infoLog[512];
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				string error = "ERROR::VERTEX SHADER::COMPILATION_FAILED\n";
				error += infoLog;
				error += "\n";
				perror(error.c_str());
			}
		}
		
		void CompileProgram(int prog)
		{
			int  success;
			char infoLog[512];
			glGetProgramiv(prog, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetProgramInfoLog(prog, 512, NULL, infoLog);
				string error = "ERROR::SHADER::Linking Program::COMPILATION_FAILED\n";
				error += infoLog;
				error += "\n";
				perror(error.c_str());
			}
		}

		unsigned int GetShaderProgram(const char* vertexShaderFile, const char* fragShaderFile)
		{
			// Create and Setup Vertex Shader
			string vShaderStr = shader::GetShaderFromFile(vertexShaderFile);
			const char* vertexShaderSrc = vShaderStr.c_str();
			unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
			glCompileShader(vertexShader);
			shader::CompileVertexShader(vertexShader);

			// Create and Setup Fragment Shader
			string fShaderStr = shader::GetShaderFromFile(fragShaderFile);
			const char* fragShaderSrc = fShaderStr.c_str();
			unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
			glCompileShader(fragShader);
			shader::CompileFragmentShader(fragShader);

			//Create ShaderProgram and attach vertex anad fragment shaders to it
			unsigned int shaderProgram;
			shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragShader);
			glLinkProgram(shaderProgram);
			shader::CompileProgram(shaderProgram);

			//Delete Shaders
			glDeleteShader(vertexShader);
			glDeleteShader(fragShader);

			return shaderProgram;
		}
};

namespace texture
{
	enum  ImageType
	{
		JPG,
		PNG_transparent,
		PNG_opaque
	};
	unsigned int loadTextureBasic(const char* filename, ImageType type, GLenum textureNo = GL_TEXTURE0, bool flip = true)
	{
		unsigned int texture;
		glGenTextures(1, &texture);
		glActiveTexture(textureNo);
		glBindTexture(GL_TEXTURE_2D,texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		int width, height, noColorChannels;
		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = stbi_load(filename, &width, &height, &noColorChannels, 0);

		if (data)
		{
			GLenum intFormat , format;
			switch (type)
			{
				case texture::JPG:
					intFormat = GL_RGB;
					format = GL_RGB;
					break;
				case texture::PNG_transparent:
					intFormat = GL_RGBA;
					format = GL_RGBA;
					break;
				case texture::PNG_opaque:
					intFormat = GL_RGB;
					format = GL_RGBA;
					break;
				default:
					break;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, intFormat , width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		return texture;
	}
}