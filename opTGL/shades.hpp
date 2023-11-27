#ifndef SHADER_H
#define SHADER_H

//including glad to get the func/func pointers for openGL
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	//Program ID
	GLuint ID;

	//Initializing/Construtor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath)
	{

		//String for holding the shaders
		std::string vertexCode;
		std::string fragmentCode;

		//String variable for 'reading' from the shader files
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		//error opening the files
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			//read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			//close the opened files
			vShaderFile.close();
			fShaderFile.close();

			//convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (const std::exception&)
		{
			std::cout << "Cannot read the file(s) bra :), ERROR::SHADER::FILE_NOT_READ_SUCCESFULLY\n";
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//Compiling the shader files
		GLuint vertex, fragment;

		//Creating a vertex and fragment shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		fragment = glCreateShader(GL_FRAGMENT_SHADER);

		//Setting the shader source code
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glShaderSource(fragment, 1, &fShaderCode, NULL);

		//Compiling the shaders
		glCompileShader(vertex);
		glCompileShader(fragment);

		//Debug/Error checking the shaders
		detugg('v', vertex);
		detugg('f', fragment);

		//Creating a program to link the shaders
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		detugg('p', ID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void use()
	{
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

	}

	void setFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);

	}

private:
	//For debugging
	void detugg(char proSha, GLuint reference)
	{
		int success;
		char infoLog[512];

		if (proSha == 'v' || proSha == 'f')
		{
			glad_glGetShaderiv(reference, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(reference, 512, NULL, infoLog);
				std::cout << "Could not compile the " << proSha << "(v for vertex, f for fragment) shader bro :|. Your errror\n" << infoLog;
			}
		}

		else if (proSha == 'p')
		{
			glGetProgramiv(reference, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(reference, 512, NULL, infoLog);
				std::cout << "Could not link the program bro :| Here the error :|\n" << infoLog;
			}
		}
	}
};

#endif 