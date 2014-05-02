#include "plyFile.h"

namespace bb{

plyFile::plyFile(){
	vertexCount = 0;
	faceCount = 0;
	quadCount = 0;

	format[0] = false;
	format[1] = false;
	format[2] = false;

	center = vec3();
	radius = 0;
	boundingBox[0] = vec3();
	boundingBox[1] = vec3();
}

bool plyFile::load(const std::string &path){
	std::ifstream file;
	char line[100];
	unsigned int index = 0;
	bool readVertex = false, readFaces = false, readVertexPropertys = false;

	file.open(path.c_str());

	if(!file.good()){
		return false;
	}
	
	while(!file.eof()){
		file.getline(line, 99);

		// vertex count
		if(!std::strncmp("element vertex", line, 14)){
			std::sscanf(line, "element vertex %i", &vertexCount);
			readVertexPropertys = true;
		}
		// face count
		else if(!std::strncmp("element face", line, 12)){
			std::sscanf(line, "element face %i", &faceCount);
			readVertexPropertys = false;
		}
		// vertex format
		else if(readVertexPropertys){
			if(!std::strncmp("property float nx", line, 17)){
				format[0] = true; // nx ny nz
			}
			else if(!std::strncmp("property float s", line, 17)){
				format[1] = true; // s t
			}
			else if(!std::strncmp("property float red", line, 17)){
				format[2] = true; // red green blue
			}
		}
		// end of header
		else if(!std::strncmp("end_header", line, 10)){
			faces.resize(faceCount);
			vertices.resize(vertexCount);

			if(format[0]){
				normals.resize(vertexCount);
			}

			if(format[1]){
				texCoords.resize(vertexCount);
			}

			if(format[2]){
				colors.resize(vertexCount);
			}
				
			readVertex = true;
		}
		// read vertices
		else if(readVertex){
			if(index < vertexCount){					
				vec3 ver, nor;
				vec2 tex;
				vec4 col;

				std::sscanf(line, "%f %f %f %f %f %f %f %f %f %f %f", &ver.x, &ver.y, &ver.z,
																 	  &nor.x, &nor.y, &nor.z,
																 	  &tex.x, &tex.y,
																 	  &col.x, &col.y, &col.z);
				
				vertices[index] = ver;

				if(format[0]){
					normals[index] = nor;
				}

				if(format[1]){
					texCoords[index] = tex;
				}

				if(format[2]){
					colors[index] = col;
				}

				// bounding box
				if(ver.x < boundingBox[0].x){
					boundingBox[0].x = ver.x;
				}

				if(ver.y < boundingBox[0].y){
					boundingBox[0].y = ver.y;
				}

				if(ver.z < boundingBox[0].z){
					boundingBox[0].z = ver.z;
				}

				if(ver.x > boundingBox[1].x){
					boundingBox[1].x = ver.x;
				}

				if(ver.y > boundingBox[1].y){
					boundingBox[1].y = ver.y;
				}
								
				if(ver.z > boundingBox[1].z){
					boundingBox[1].z = ver.z;
				}
				
				index++;
			}	
			
			if(index == vertexCount){
				readVertex = false;
				readFaces = true;
				index = 0;
			}
		}
		// read faces
		else if(readFaces){
			if(index < faceCount){
				face fac;
				int type;
				
				std::sscanf(line, "%i %i %i %i %i", &type, &fac.a, &fac.b, &fac.c, &fac.d);
				faces[index] = fac;

				if(type == 4){
					faces[index].quad = true;
					quadCount++;
				}
				
				index++;
			}
		}
	}

	// center, radius
	center = boundingBox[0]+((boundingBox[1]-boundingBox[0])/2.0f);
	radius = ((boundingBox[1]-boundingBox[0])/2.0f).length()/2.0f;

	file.close();
	
	reorganize();
	
	return true;
}

void plyFile::reorganize(){
	std::vector<face> newFaces;
	unsigned int fa = 0;
	
	faceCount = faceCount+quadCount;

	newFaces.resize(faceCount);
	
	// quads -> triangles
	for(unsigned int f = 0; f < faces.size(); f++){
		if(faces[f].quad){
			face f1, f2;
				
			f1 = face(faces[f].a, faces[f].b, faces[f].c);
			f2 = face(faces[f].a, faces[f].c, faces[f].d);

			newFaces[fa] = f1;
			newFaces[fa+1] = f2;
			fa++;			
		}
		else{
			newFaces[fa] = faces[f];
		}

		fa++;
	}

	faces.resize(newFaces.size());
	faces = newFaces;
	newFaces.clear();
				
	// generate indices
	fa = 0;
	indices.resize(faceCount*3);

	for(unsigned int i = 0; i < indices.size(); i += 3){
		indices[i] = faces[fa].a;
		indices[i+1] = faces[fa].b;
		indices[i+2] = faces[fa].c;

		fa++;
	}
}

};
