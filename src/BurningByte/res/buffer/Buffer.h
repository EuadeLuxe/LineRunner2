/*
 * Buffer
 * Author: Marvin Blum
 * Last Update: 31/12/2013 15:26
 * */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <string>
#include <GL/gl3w.h>
#include "../../Component.h"

namespace bb{

class Buffer:public Component{
    protected:
        unsigned int id, target;
        bool loaded;

    public:
        std::string name;

        Buffer(const std::string &name, const unsigned int target);
        virtual ~Buffer();

        void drop();
        void bind();
        void unbind();

        bool good();

        unsigned int getID();
        unsigned int getType();
};

};

#endif
