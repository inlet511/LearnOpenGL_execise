#pragma once

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix4(const std::string& name, glm::mat4& mat) const;
	void setMatrix3(const std::string& name, glm::mat3& mat) const;
	void setVec3(const std::string& name, glm::vec3& value) const;
	void Shader::setVec3(const std::string& name, float x, float y, float z) const;
};

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vFileStream;
	std::ifstream fFileStream;

	std::stringstream vStringStream;
	std::stringstream fStringStream;



	try{
		vFileStream.open(vertexPath);
		vStringStream << vFileStream.rdbuf();

		fFileStream.open(fragmentPath);
		fStringStream << fFileStream.rdbuf();

		vFileStream.close();
		fFileStream.close();

		vertexCode = vStringStream.str();
		fragmentCode = fStringStream.str();

	}catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}


	const char* vertexCode_cstr = vertexCode.c_str();
	const char* fragmentCode_cstr = fragmentCode.c_str();

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode_cstr, NULL);
	glCompileShader(vertexShader);

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode_cstr, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//link shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	// check for linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	int loc = glGetUniformLocation(ID, name.c_str());
	glUniform1i(loc,(int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	int loc = glGetUniformLocation(ID, name.c_str());
	glUniform1i(loc, value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	int loc = glGetUniformLocation(ID, name.c_str());
	glUniform1f(loc, value);
}

void Shader::setMatrix4(const std::string& name, glm::mat4& mat) const
{
	int loc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMatrix3(const std::string& name, glm::mat3& mat) const
{
	int loc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec3(const std::string& name, glm::vec3& value) const
{
	int loc = glGetUniformLocation(ID, name.c_str());
	glUniform3fv(loc, 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	int loc = glGetUniformLocation(ID, name.c_str());
	glUniform3f(loc, x, y, z);
}
