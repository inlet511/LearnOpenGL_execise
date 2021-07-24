#pragma once
#include <glad/glad.h>
#include <string>
#include <glm.hpp>

class Shader
{
public:
	unsigned int programID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geoPath=nullptr);
	void use();

	// uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string &name, const glm::vec3 &vec) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, float x,float y, float z, float w) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
};
