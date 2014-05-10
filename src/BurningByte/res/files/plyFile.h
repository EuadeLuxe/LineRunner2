/*
 * plyFile
 * Author: Marvin Blum
 * Last Update: 2014/03/18
 * */

#ifndef PLYFILE_H_
#define PLYFILE_H_

/*
 * EuadeLuxe
 * 10/05/2014 16:29
 * Surrounded macro definition in order to avoid
 * redefinition. In Release build it is pre-defined
 * because the command line wide string given gy
 * windows has to be converted to a narrow string
 * using an "unsafe" function (wcstombs). Its "safe"
 * counterpart did not work for some reason.... :?
 */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //_CRT_SECURE_NO_WARNINGS

#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>
#include <string>
#include <cstring>
#include "../../Component.h"
#include "../../math/Vector.h"

namespace bb{

class plyFile:public Component{
	public:
		struct face{
			int a, b, c, d;
			bool quad;

			face():
				a(0),
				b(0),
				c(0),
				d(0),
				quad(false){}

			face(const int a, const int b, const int c):
				a(a),
				b(b),
				c(c),
				d(0),
				quad(false){}

			face(const int a, const int b, const int c, const int d):
				a(a),
				b(b),
				c(c),
				d(d),
				quad(true){}
		};

	protected:
		bool format[3]; // 0 normals, 1 texture coordinates, 2 color

	private:
		void reorganize();

	public:
		unsigned int vertexCount;
		unsigned int faceCount;
		unsigned int quadCount;

		std::vector<vec3> vertices;
		std::vector<vec2> texCoords;
		std::vector<vec3> normals;
		std::vector<vec4> colors;
		std::vector<unsigned int> indices;
		std::vector<face> faces;

		vec3 center, boundingBox[2]; // boundingBox: 0 min, 1 max
		float radius;

		plyFile();

		bool load(const std::string &path);
};

};

#endif
