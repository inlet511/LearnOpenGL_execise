#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <gtc/type_ptr.hpp>
using namespace std;


Shader::Shader(const GLchar* vertexPath,const GLchar* geoPath, const GLchar* fragmentPath)
{
	string vertexCode;
	string geoCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream gShaderFile;
	ifstream fShaderFile;


	/*            Read shader file         */
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try 
	{
		vShaderFile.open(vertexPath);
        gShaderFile.open(geoPath);
		fShaderFile.open(fragmentPath);

		stringstream vShaderStream, gShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
        gShaderStream << gShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
        gShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
        geoCode = gShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* gShaderCode = geoCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	/*            Create and Compile Shader            */
	unsigned int vertex,geo, fragment;
	int success;
	char infoLog[512];

	// VertexShader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
    
// GeoShader
	geo = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geo, 1, &gShaderCode, NULL);
	glCompileShader(geo);
	glGetShaderiv(geo, GL_COMPILE_STATUS, &success);

	if (!success)
	{
	    glGetShaderInfoLog(geo, 512, NULL, infoLog);
		cout << "ERROR::SHADER::GEO::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// Fragment Shader

	fragment = glCreateShader(GL_FRAGMENT_SHADER);


	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}


	/*            Create Shader Program            */

	programID = glCreateProgram();
	glAttachShader(programID, vertex);
	glAttachShader(programID, geo);
	glAttachShader(programID, fragment);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(geo);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(programID);
}

void Shader::setBool(const std::string &name, bool value) const
{
	unsigned int loc = glGetUniformLocation(programID,name.c_str());
	glUniform1i(loc, (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
	unsigned int loc = glGetUniformLocation(programID, name.c_str());
	glUniform1i(loc, (int)value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	unsigned int loc = glGetUniformLocation(programID, name.c_str());
	glUniform1f(loc, value);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec) const
{
	glUniform3fv(glGetUniformLocation(programID, name.c_str()),1, glm::value_ptr(vec));
	//最后一个参数也可以使用&vec[0]
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
	unsigned int loc = glGetUniformLocation(programID, name.c_str());
	glUniform4f(loc, x, y, z, w);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
