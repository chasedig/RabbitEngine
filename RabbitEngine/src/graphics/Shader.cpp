#include "Shader.h"
#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
namespace RBT
{
	const std::string SHADER_DIRECTORY_PATH = "shaders/";
	const int INFO_LOG_BUFFER_SIZE = 2048;

	void createShader(std::string filename, int shaderId);
	std::string readShader(std::string filename);

	Shader::Shader(std::string vs_filename, std::string fs_filename)
	{
		program = glCreateProgram();

		vs = glCreateShader(GL_VERTEX_SHADER);
		createShader(vs_filename, vs);
		fs = glCreateShader(GL_FRAGMENT_SHADER);
		createShader(fs_filename, fs);
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		int linkSuccess;
		glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
		if (!linkSuccess)
		{
			char infoLog[INFO_LOG_BUFFER_SIZE];
			glGetProgramInfoLog(program, INFO_LOG_BUFFER_SIZE, NULL, infoLog);
			std::cout << "Shader linking error with program ID " << program << ": " << infoLog << std::endl;
		}

	}

	void Shader::bind()
	{
		glUseProgram(program);
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}


	int Shader::getUniformLocation(std::string name)
	{
		return glGetUniformLocation(this->program, &name[0]);
	}

    void Shader::setMat4Uniform(std::string name, glm::mat4 uniform)
    {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(uniform));
    }

	void createShader(std::string filename, int shaderId)
	{
		std::string source = readShader(filename);
		const char* source_cstr = &source[0];
		//const int* length = std::string::length(source);
		glShaderSource(shaderId, 1, &source_cstr, NULL);
		glCompileShader(shaderId);
		int compileSuccess;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileSuccess);
		if (!compileSuccess)
		{
			char infoLog[INFO_LOG_BUFFER_SIZE];
			glGetShaderInfoLog(shaderId, INFO_LOG_BUFFER_SIZE, NULL, infoLog);
			std::cout << "Shader compilation failed for '" << filename << "'" << " with error " << infoLog << std::endl;
		}
	}

	std::string readShader(std::string filename)
	{
		filename = SHADER_DIRECTORY_PATH + filename;
		std::string content = "";
		try
		{
			std::ifstream shaderFile(filename);
			std::string line;
			while (std::getline(shaderFile, line))
			{
				content = content + line + "\n";
			}
			shaderFile.close();
			return content;
		}
		catch (std::exception e)
		{
			std::cout << "Exception when reading shader: " << e.what() << std::endl;
		}
		return "";
	}

}