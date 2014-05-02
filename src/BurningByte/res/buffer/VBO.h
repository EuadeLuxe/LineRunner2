/*
 * VBO - VertexBufferObject
 * Author: Marvin Blum
 * Last Update: 2014/03/29 16:30
 * */

#ifndef VBO_H_
#define VBO_H_

#include <vector>
#include <iostream>
#include "Buffer.h"

namespace bb{

template <typename T>
class VBO:public Buffer{
    private:
		unsigned int bufferSize;
		std::vector<T> data;

    public:
        VBO(const std::string &name, const unsigned int target):Buffer(name, target){
        	bufferSize = 0;
        	glGenBuffers(1, &id);
        }

        virtual ~VBO(){
            drop();
        }
        
        void drop(){
			Buffer::drop();

			bufferSize = 0;
			data.clear();
		}

        bool fill(T* data, const unsigned int elements, const unsigned int size, const unsigned int use, const bool copyData = false){
			if(data){
				if(copyData){
					this->data.clear();
					this->data = std::vector<T>(data, data+elements);
					bufferSize = this->data.size();
				}
				else{
					bufferSize = elements;
				}

				bind();
				glBufferData(target, elements*size, &data[0], use);
				unbind();

				loaded = true;

				return true;
			}

			return false;
		}

        bool fill(std::vector<T> &data, const unsigned int size, const unsigned int use, const bool copyData = false){
            if(data.size()){
                if(copyData){
                	this->data.clear();
                    this->data = std::vector<T>(data);
                }

                return fill(&data[0], data.size(), size, use, false);
            }

            return false;
        }

        bool update(T* data, const unsigned int elements, unsigned int offset, unsigned int size, bool copyData = false){
			if(loaded && data){
				if(copyData){
					this->data.clear();
					this->data = std::vector<T>(data, data+elements);
					bufferSize = this->data.size();
				}
				else{
					bufferSize = elements;
				}

				bind();
				glBufferSubData(target, offset, elements*size, &data[0]);
				unbind();

				loaded = true;

				return true;
			}

			return false;
		}

        bool update(std::vector<T> &data, unsigned int offset, unsigned int size, bool copyData = false){
            if(loaded && data.size()){
                if(copyData){
                	this->data.clear();
                	this->data = std::vector<T>(data);
                }

                return update(&data[0], data.size(), offset, size, false);
            }

            return false;
        }

        void vertexAttribPointer(const unsigned int attribLocation, const int size, const unsigned int type, const bool normalized, const unsigned int stride, const void* pointer){
            if(loaded){
                glVertexAttribPointer(attribLocation, size, type, normalized, stride, pointer);
            }
        }

        void vertexAttribIPointer(const unsigned int attribLocation, const int size, const unsigned int type, const unsigned int stride, const void* pointer){
            if(loaded){
                glVertexAttribIPointer(attribLocation, size, type, stride, pointer);
            }
        }

        //void vertexAttribLPointer(unsigned int attribLocation, int size, unsigned int type, bool normalized, unsigned int stride, void* pointer)

        unsigned int size(){
        	return bufferSize;
        }

        const std::vector<T>& getData(){
            return data;
        }
};

};

#endif
