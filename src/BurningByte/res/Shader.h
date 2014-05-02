/*
 * Shader
 * Author: Marvin Blum
 * Last Update: 02/01/2014 20:47
 * */

#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <GL/gl3w.h>

namespace bb{

class Shader{
	public:
		struct GLSLShader{
			unsigned int id;
			std::string filename;
			std::string source;
		};

	private:
		std::vector<unsigned int> vaArrays;

		GLSLShader vertexShader;
		GLSLShader fragmentShader;
		unsigned int programID;

		unsigned int attribIndex;
		std::map<std::string, unsigned int> uniformMap;
		std::map<std::string, unsigned int> attribMap;

		std::string readFile(const std::string &filename);
		bool compileShader(const GLSLShader &shader);
		void outputShaderLog(unsigned int shaderID);
		void outputProgramLog(unsigned int programID);

	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		virtual ~Shader();
		
		void drop();

		bool initialize();
		void linkProgram();
		void bind();
		void unbind();

		void bindAttrib(unsigned int index, const std::string &name);
		void bindAttrib(const std::string &name);
		void enableVertexAttribArrays();
		void disableVertexAttribArrays();

		unsigned int getUniformLocation(const std::string &name);
		unsigned int getAttribLocation(const std::string &name);

		unsigned int getID();
		const GLSLShader& getVertexShader();
		const GLSLShader& getFragmentShader();

		void sendUniform(const std::string &name, const int v1);
		void sendUniform(const std::string &name, const int v1, const int v2);
		void sendUniform(const std::string &name, const int v1, const int v2, const int v3);
		void sendUniform(const std::string &name, const int v1, const int v2, const int v3, const int v4);
		void sendUniform(const std::string &name, const float v1);
		void sendUniform(const std::string &name, const float v1, const float v2);
		void sendUniform(const std::string &name, const float v1, const float v2, const float v3);
		void sendUniform(const std::string &name, const float v1, const float v2, const float v3, const float v4);
		void sendUniform1(const std::string &name, const int count, const int* value);
		void sendUniform2(const std::string &name, const int count, const int* value);
		void sendUniform3(const std::string &name, const int count, const int* value);
		void sendUniform4(const std::string &name, const int count, const int* value);
		void sendUniform1(const std::string &name, const int count, const float* value);
		void sendUniform2(const std::string &name, const int count, const float* value);
		void sendUniform3(const std::string &name, const int count, const float* value);
		void sendUniform4(const std::string &name, const int count, const float* value);
		void sendUniform2x2(const std::string &name, const float *matrix, const int count = 1, bool transpose = false);
		void sendUniform3x3(const std::string &name, const float *matrix, const int count = 1, bool transpose = false);
		void sendUniform4x4(const std::string &name, const float *matrix, const int count = 1, bool transpose = false);
		void sendUniform2x3(const std::string &name, const float *matrix, const int count = 1, bool transpose = false);
		void sendUniform3x2(const std::string &name, const float *matrix, const int count = 1, bool transpose = false);
		void sendUniform2x4(const std::string &name, const float *matrix, const int count = 1, bool transpose = false);
		void sendUniform4x2(const std::string &name, const float *matrix, const int count = 1, bool transpose = false);
		void sendUniform3x4(const std::string &name, const float *matrix, const int count = 1, bool transpose = false);
		void sendUniform4x3(const std::string &name, const float *matrix, const int count = 1, bool transpose = false);
};

};

#endif
