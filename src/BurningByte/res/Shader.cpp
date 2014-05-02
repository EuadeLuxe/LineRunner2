#include "Shader.h"

namespace bb{

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader){
	this->vertexShader.filename = vertexShader;
	this->fragmentShader.filename = fragmentShader;
	programID = 0;
	attribIndex = 0;

	if(!initialize()){
		drop();

		std::cerr<<"Could not initialize Shader:"<<std::endl;
		std::cerr<<vertexShader<<std::endl;
		std::cerr<<fragmentShader<<std::endl;
	}
}

Shader::~Shader(){
	drop();
}

void Shader::drop(){
	glDetachShader(programID, vertexShader.id);
	glDetachShader(programID, fragmentShader.id);
	glDeleteShader(vertexShader.id);
	glDeleteShader(fragmentShader.id);
	glDeleteProgram(programID);
}

std::string Shader::readFile(const std::string &filename){
	std::ifstream file(filename.c_str());

	if(!file.good()){
		return std::string();
	}

	std::string stringBuffer(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));

	return stringBuffer;
}

bool Shader::compileShader(const GLSLShader &shader){
	glCompileShader(shader.id);

	int result;
	glGetShaderiv(shader.id, GL_COMPILE_STATUS, &result);

	if(!result){
		return false;
	}

	return true;
}

void Shader::outputShaderLog(unsigned int shaderID){
	std::vector<char> infoLog;
	GLint infoLen;

	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);
	infoLog.resize(infoLen);
	glGetShaderInfoLog(shaderID, infoLog.size(), &infoLen, &infoLog[0]);

	std::cerr<<std::string(infoLog.begin(), infoLog.end())<<std::endl;
}

void Shader::outputProgramLog(unsigned int programID){
	std::vector<char> infoLog;
	GLint infoLen;
	GLint result;

	glGetProgramiv(programID, GL_LINK_STATUS, &result);

	if(result){
		return;
	}

	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLen);
	infoLog.resize(infoLen);
	glGetProgramInfoLog(programID, infoLog.size(), &infoLen, &infoLog[0]);

	std::cerr<<std::string(infoLog.begin(), infoLog.end())<<std::endl;
}

bool Shader::initialize(){
	programID = glCreateProgram();
	vertexShader.id = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader.id = glCreateShader(GL_FRAGMENT_SHADER);

	// read source
	vertexShader.source = readFile(vertexShader.filename);
	fragmentShader.source = readFile(fragmentShader.filename);

	if(vertexShader.source.empty() || fragmentShader.source.empty()){
		return false;
	}

	const char* tmp = static_cast<const char*>(vertexShader.source.c_str());
	glShaderSource(vertexShader.id, 1, (const char**)&tmp, 0);
	tmp = static_cast<const char*>(fragmentShader.source.c_str());
	glShaderSource(fragmentShader.id, 1, (const char**)&tmp, 0);

	if(!compileShader(vertexShader) || !compileShader(fragmentShader)){
		outputShaderLog(vertexShader.id);
		outputShaderLog(fragmentShader.id);

		return false;
	}

	glAttachShader(programID, vertexShader.id);
	glAttachShader(programID, fragmentShader.id);
	linkProgram();

	return true;
}

void Shader::linkProgram(){
	glLinkProgram(programID);

	int result;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);

	if(!result){
		outputProgramLog(programID);
	}
}

void Shader::bind(){
	glUseProgram(programID);
}

void Shader::unbind(){
	glUseProgram(0);
}

void Shader::bindAttrib(unsigned int index, const std::string &name){
	glBindAttribLocation(programID, index, name.c_str());
	vaArrays.push_back(getAttribLocation(name));
}

void Shader::bindAttrib(const std::string &name){
	bindAttrib(attribIndex, name);
	attribIndex++;
}

void Shader::enableVertexAttribArrays(){
	for(unsigned int i : vaArrays){
		glEnableVertexAttribArray(i);
	}
}

void Shader::disableVertexAttribArrays(){
	for(unsigned int i : vaArrays){
		glDisableVertexAttribArray(i);
	}
}

unsigned int Shader::getUniformLocation(const std::string &name){
	std::map<std::string, unsigned int>::iterator i = uniformMap.find(name);

	if(i == uniformMap.end()){
		unsigned int location = glGetUniformLocation(programID, name.c_str());
		uniformMap.insert(std::make_pair(name, location));

		return location;
	}

	return (*i).second;
}

unsigned int Shader::getAttribLocation(const std::string &name){
	std::map<std::string, unsigned int>::iterator i = attribMap.find(name);

	if(i == attribMap.end()){
		unsigned int location = glGetAttribLocation(programID, name.c_str());
		attribMap.insert(make_pair(name, location));

		return location;
	}

	return (*i).second;
}

unsigned int Shader::getID(){
	return programID;
}

const Shader::GLSLShader& Shader::getVertexShader(){
	return vertexShader;
}

const Shader::GLSLShader& Shader::getFragmentShader(){
	return fragmentShader;
}

void Shader::sendUniform(const std::string &name, const int v1){
	glUniform1i(getUniformLocation(name), v1);
}

void Shader::sendUniform(const std::string &name, const int v1, const int v2){
	glUniform2i(getUniformLocation(name), v1, v2);
}

void Shader::sendUniform(const std::string &name, const int v1, const int v2, const int v3){
	glUniform3i(getUniformLocation(name), v1, v2, v3);
}

void Shader::sendUniform(const std::string &name, const int v1, const int v2, const int v3, const int v4){
	glUniform4i(getUniformLocation(name), v1, v2, v3, v4);
}

void Shader::sendUniform(const std::string &name, const float v1){
	glUniform1f(getUniformLocation(name), v1);
}

void Shader::sendUniform(const std::string &name, const float v1, const float v2){
	glUniform2f(getUniformLocation(name), v1, v2);
}

void Shader::sendUniform(const std::string &name, const float v1, const float v2, const float v3){
	glUniform3f(getUniformLocation(name), v1, v2, v3);
}

void Shader::sendUniform(const std::string &name, const float v1, const float v2, const float v3, const float v4){
	glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
}

void Shader::sendUniform1(const std::string &name, const int count, const int* value){
	glUniform1iv(getUniformLocation(name), count, value);
}

void Shader::sendUniform2(const std::string &name, const int count, const int* value){
	glUniform2iv(getUniformLocation(name), count, value);
}

void Shader::sendUniform3(const std::string &name, const int count, const int* value){
	glUniform3iv(getUniformLocation(name), count, value);
}

void Shader::sendUniform4(const std::string &name, const int count, const int* value){
	glUniform4iv(getUniformLocation(name), count, value);
}

void Shader::sendUniform1(const std::string &name, const int count, const float* value){
	glUniform1fv(getUniformLocation(name), count, value);
}

void Shader::sendUniform2(const std::string &name, const int count, const float* value){
	glUniform2fv(getUniformLocation(name), count, value);
}

void Shader::sendUniform3(const std::string &name, const int count, const float* value){
	glUniform3fv(getUniformLocation(name), count, value);
}

void Shader::sendUniform4(const std::string &name, const int count, const float* value){
	glUniform4fv(getUniformLocation(name), count, value);
}

void Shader::sendUniform2x2(const std::string &name, const float *matrix, const int count, bool transpose){
	glUniformMatrix2fv(getUniformLocation(name), count, transpose, matrix);
}

void Shader::sendUniform3x3(const std::string &name, const float* matrix, const int count, bool transpose){
	glUniformMatrix3fv(getUniformLocation(name), count, transpose, matrix);
}

void Shader::sendUniform4x4(const std::string &name, const float *matrix, const int count, bool transpose){
	glUniformMatrix4fv(getUniformLocation(name), count, transpose, matrix);
}

void Shader::sendUniform2x3(const std::string &name, const float *matrix, const int count, bool transpose){
	glUniformMatrix2x3fv(getUniformLocation(name), count, transpose, matrix);
}

void Shader::sendUniform3x2(const std::string &name, const float *matrix, const int count, bool transpose){
	glUniformMatrix3x2fv(getUniformLocation(name), count, transpose, matrix);
}

void Shader::sendUniform2x4(const std::string &name, const float *matrix, const int count, bool transpose){
	glUniformMatrix2x4fv(getUniformLocation(name), count, transpose, matrix);
}

void Shader::sendUniform4x2(const std::string &name, const float *matrix, const int count, bool transpose){
	glUniformMatrix4x2fv(getUniformLocation(name), count, transpose, matrix);
}

void Shader::sendUniform3x4(const std::string &name, const float *matrix, const int count, bool transpose){
	glUniformMatrix3x4fv(getUniformLocation(name), count, transpose, matrix);
}

void Shader::sendUniform4x3(const std::string &name, const float *matrix, const int count, bool transpose){
	glUniformMatrix4x3fv(getUniformLocation(name), count, transpose, matrix);
}

};
