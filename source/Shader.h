#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertShader, const char* fragShader);
	void use();
	void setInt(const std::string& name, int val) const;
	void setBool(const std::string& name, bool val) const;
	void setFloat(const std::string& name, float val) const;

};

Shader::Shader(const char* vertShader, const char* fragShader)
{
	// 1.read shader text
	std::string vertexString;
	std::string fragString;
	std::ifstream vertFile;
	std::ifstream fragFile;
	vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertFile.open(vertShader);
		fragFile.open(fragShader);
		std::stringstream vertStream, fragStream;
		vertStream << vertFile.rdbuf();
		fragStream << fragFile.rdbuf();
		vertFile.close();
		fragFile.close();

		vertexString = vertStream.str();
		fragString = fragStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexString.c_str();
	const char* fShaderCode = fragString.c_str();

	// 2.compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE_FAILED\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_FRAGMENT_SHADER, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

};

void Shader::use() {
	glUseProgram(ID);
};

void Shader::setInt(const std::string& name, int val) const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
}

void Shader::setBool(const std::string& name, bool val) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)val);
}

void Shader::setFloat(const std::string& name, float val) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
}

#endif // !SHADER_H

