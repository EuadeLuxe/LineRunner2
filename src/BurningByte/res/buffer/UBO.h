/*
 * UBO - UniformBufferObject
 * Author: Marvin Blum
 * Last Update: 2014/03/29 16:24
 * */

#ifndef UBO_H_
#define UBO_H_

#include <vector>
#include <iostream>
#include "Buffer.h"

namespace bb{

template <class T>
class UBO:public Buffer{
	private:
		unsigned int index, port;
		std::vector<T> data;

	public:
		UBO(const std::string &name, const unsigned int target = GL_UNIFORM_BUFFER):Buffer(name, target){
			index = 0;
			port = 0;

			glGenBuffers(1, &id);
		}

		virtual ~UBO(){
			drop();
		}

		void drop(){
			Buffer::drop();

			index = 0;
			port = 0;
			data.clear();
		}

		bool fill(const unsigned int shader, const unsigned int port, T* data, unsigned int size, bool copyData = false, const unsigned int type = GL_DYNAMIC_DRAW){
			if(copyData){
				data = std::vector<T>(data, data+size);
			}

			bind();

			glBufferData(target, size, data, type);

			index = glGetUniformBlockIndex(shader, name.c_str());
			this->port = port;

			if(index == GL_INVALID_INDEX || port >= GL_MAX_UNIFORM_BUFFER_BINDINGS){
				drop();

				return false;
			}

			glUniformBlockBinding(shader, index, port);
			glBindBufferBase(target, port, id);

			unbind();

			loaded = true;

			return true;
		}

		bool fill(const unsigned int shader, const unsigned int port, std::vector<T> &data, unsigned int size, bool copyData = false, const unsigned int type = GL_DYNAMIC_DRAW){
			if(copyData){
				data = std::vector<T>(data);
			}

			return fill(shader, port, &data[0], size, false, type);
		}

		unsigned int size(){
			return data.size();
		}

		const std::vector<T>& getData(){
			return data;
		}
};

};

#endif
