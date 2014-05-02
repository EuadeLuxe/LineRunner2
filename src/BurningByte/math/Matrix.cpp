#include "Matrix.h"

namespace bb{

mat4::mat4(){
	for(unsigned int i = 0; i < 16; i++){
		values[i] = 0;
	}
}

mat4::mat4(const mat4 &m){
	for(unsigned int i = 0; i < 16; i++){
		values[i] = m.values[i];
	}
}

mat4::mat4(const float m[16]){
	for(unsigned int i = 0; i < 16; i++){
		values[i] = m[i];
	}
}

mat4::mat4(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i, const float j, const float k, const float l, const float m, const float n, const float o, const float p){
	values[0] = a;
	values[1] = b;
	values[2] = c;
	values[3] = d;
	values[4] = e;
	values[5] = f;
	values[6] = g;
	values[7] = h;
	values[8] = i;
	values[9] = j;
	values[10] = k;
	values[11] = l;
	values[12] = m;
	values[13] = n;
	values[14] = o;
	values[15] = p;
}

float mat4::operator[](const unsigned int v){
	if(v < 16){
		return values[v];
	}
	else{
		return 0;
	}
}

void mat4:: operator=(const mat4 &m){
	for(unsigned int i = 0; i < 16; i++){
		values[i] = m.values[i];
	}
}

void mat4::operator=(float m[16]){
	for(unsigned int i = 0; i < 16; i++){
		values[i] = m[i];
	}
}

mat4 mat4::operator*(float v){
	mat4 m;

	for(unsigned int i = 0; i < 16; i++){
		m.values[i] = values[i]*v;
	}

	return m;
}

mat4 mat4::operator*(const mat4 &m){
	mat4 mat;
		
	mat.values[0] = m.values[0]*values[0]+m.values[1]*values[4]+m.values[2]*values[8]+m.values[3]*values[12];		
	mat.values[1] = m.values[0]*values[1]+m.values[1]*values[5]+m.values[2]*values[9]+m.values[3]*values[13];
	mat.values[2] = m.values[0]*values[2]+m.values[1]*values[6]+m.values[2]*values[10]+m.values[3]*values[14];
	mat.values[3] = m.values[0]*values[3]+m.values[1]*values[7]+m.values[2]*values[11]+m.values[3]*values[15];

	mat.values[4] = m.values[4]*values[0]+m.values[5]*values[4]+m.values[6]*values[8]+m.values[7]*values[12];
	mat.values[5] = m.values[4]*values[1]+m.values[5]*values[5]+m.values[6]*values[9]+m.values[7]*values[13];
	mat.values[6] = m.values[4]*values[2]+m.values[5]*values[6]+m.values[6]*values[10]+m.values[7]*values[14];
	mat.values[7] = m.values[4]*values[3]+m.values[5]*values[7]+m.values[6]*values[11]+m.values[7]*values[15];
		
	mat.values[8] = m.values[8]*values[0]+m.values[9]*values[4]+m.values[10]*values[8]+m.values[11]*values[12];
	mat.values[9] = m.values[8]*values[1]+m.values[9]*values[5]+m.values[10]*values[9]+m.values[11]*values[13];
	mat.values[10] = m.values[8]*values[2]+m.values[9]*values[6]+m.values[10]*values[10]+m.values[11]*values[14];
	mat.values[11] = m.values[8]*values[3]+m.values[9]*values[7]+m.values[10]*values[11]+m.values[11]*values[15];

	mat.values[12] = m.values[12]*values[0]+m.values[13]*values[4]+m.values[14]*values[8]+m.values[15]*values[12];
	mat.values[13] = m.values[12]*values[1]+m.values[13]*values[5]+m.values[14]*values[9]+m.values[15]*values[13];
	mat.values[14] = m.values[12]*values[2]+m.values[13]*values[6]+m.values[14]*values[10]+m.values[15]*values[14];
	mat.values[15] = m.values[12]*values[3]+m.values[13]*values[7]+m.values[14]*values[11]+m.values[15]*values[15];

	return mat;
}
	
mat4 mat4::operator/(float v){
	mat4 m;

	for(unsigned int i = 0; i < 16; i++){
		m.values[i] = values[i]/v;
	}

	return m;
}

mat4 mat4::operator/(const mat4 &m){
	mat4 mat;

	for(unsigned int i = 0; i < 16; i++){
		mat.values[i] = values[i]/m.values[i];
	}

	return mat;
}

mat4 mat4::operator+(float v){
	mat4 m;

	for(unsigned int i = 0; i < 16; i++){
		m.values[i] = values[i]+v;
	}

	return m;
}

mat4 mat4::operator+(const mat4 &m){
	mat4 mat;

	for(unsigned int i = 0; i < 16; i++){
		mat.values[i] = values[i]+m.values[i];
	}

	return mat;
}

mat4 mat4::operator-(float v){
	mat4 m;

	for(unsigned int i = 0; i < 16; i++){
		m.values[i] = values[i]-v;
	}

	return m;
}

mat4 mat4::operator-(const mat4 &m){
	mat4 mat;

	for(unsigned int i = 0; i < 16; i++){
		mat.values[i] = values[i]-m.values[i];
	}

	return mat;
}

mat4 mat4::operator*=(float v){
	for(unsigned int i = 0; i < 16; i++){
		values[i] *= v;
	}

	return *this;
}

mat4 mat4::operator*=(const mat4 &m){
	mat4 mat = mat4(getArray());

	values[0] = m.values[0]*mat.values[0]+m.values[1]*mat.values[4]+m.values[2]*mat.values[8]+m.values[3]*mat.values[12];		
	values[1] = m.values[0]*mat.values[1]+m.values[1]*mat.values[5]+m.values[2]*mat.values[9]+m.values[3]*mat.values[13];
	values[2] = m.values[0]*mat.values[2]+m.values[1]*mat.values[6]+m.values[2]*mat.values[10]+m.values[3]*mat.values[14];
	values[3] = m.values[0]*mat.values[3]+m.values[1]*mat.values[7]+m.values[2]*mat.values[11]+m.values[3]*mat.values[15];

	values[4] = m.values[4]*mat.values[0]+m.values[5]*mat.values[4]+m.values[6]*mat.values[8]+m.values[7]*mat.values[12];
	values[5] = m.values[4]*mat.values[1]+m.values[5]*mat.values[5]+m.values[6]*mat.values[9]+m.values[7]*mat.values[13];
	values[6] = m.values[4]*mat.values[2]+m.values[5]*mat.values[6]+m.values[6]*mat.values[10]+m.values[7]*mat.values[14];
	values[7] = m.values[4]*mat.values[3]+m.values[5]*mat.values[7]+m.values[6]*mat.values[11]+m.values[7]*mat.values[15];
		
	values[8] = m.values[8]*mat.values[0]+m.values[9]*mat.values[4]+m.values[10]*mat.values[8]+m.values[11]*mat.values[12];
	values[9] = m.values[8]*mat.values[1]+m.values[9]*mat.values[5]+m.values[10]*mat.values[9]+m.values[11]*mat.values[13];
	values[10] = m.values[8]*mat.values[2]+m.values[9]*mat.values[6]+m.values[10]*mat.values[10]+m.values[11]*mat.values[14];
	values[11] = m.values[8]*mat.values[3]+m.values[9]*mat.values[7]+m.values[10]*mat.values[11]+m.values[11]*mat.values[15];

	values[12] = m.values[12]*mat.values[0]+m.values[13]*mat.values[4]+m.values[14]*mat.values[8]+m.values[15]*mat.values[12];
	values[13] = m.values[12]*mat.values[1]+m.values[13]*mat.values[5]+m.values[14]*mat.values[9]+m.values[15]*mat.values[13];
	values[14] = m.values[12]*mat.values[2]+m.values[13]*mat.values[6]+m.values[14]*mat.values[10]+m.values[15]*mat.values[14];
	values[15] = m.values[12]*mat.values[3]+m.values[13]*mat.values[7]+m.values[14]*mat.values[11]+m.values[15]*mat.values[15];
	
	return *this;
}

mat4 mat4::operator/=(float v){
	for(unsigned int i = 0; i < 16; i++){
		values[i] /= v;
	}

	return *this;
}

mat4 mat4::operator/=(const mat4 &m){
	for(unsigned int i = 0; i < 16; i++){
		values[i] /= m.values[i];
	}

	return *this;
}

mat4 mat4::operator+=(float v){
	for(unsigned int i = 0; i < 16; i++){
		values[i] = values[i]+v;
	}

	return *this;
}

mat4 mat4::operator+=(const mat4 &m){
	for(unsigned int i = 0; i < 16; i++){
		values[i] = values[i]+m.values[i];
	}

	return *this;
}

mat4 mat4::operator-=(float v){
	for(unsigned int i = 0; i < 16; i++){
		values[i] = values[i]-v;
	}

	return *this;
}

mat4 mat4::operator-=(const mat4 &m){
	for(unsigned int i = 0; i < 16; i++){
		values[i] = values[i]-m.values[i];
	}

	return *this;
}

bool mat4::operator==(const mat4 &m){
	return m.values[0] == m.values[0] &&
		   m.values[1] == m.values[1] &&
		   m.values[2] == m.values[2] &&
		   m.values[3] == m.values[3] &&

		   m.values[4] == m.values[4] &&
		   m.values[5] == m.values[5] &&
		   m.values[6] == m.values[6] &&
		   m.values[7] == m.values[7] &&

		   m.values[8] == m.values[8] &&
		   m.values[9] == m.values[9] &&
		   m.values[10] == m.values[10] &&
		   m.values[11] == m.values[11] &&

		   m.values[12] == m.values[12] &&
		   m.values[13] == m.values[13] &&
		   m.values[14] == m.values[14] &&
		   m.values[15] == m.values[15];
}

bool mat4::operator!=(const mat4 &m){
	return m.values[0] != m.values[0] ||
		   m.values[1] != m.values[1] ||
		   m.values[2] != m.values[2] ||
		   m.values[3] != m.values[3] ||

		   m.values[4] != m.values[4] ||
		   m.values[5] != m.values[5] ||
		   m.values[6] != m.values[6] ||
		   m.values[7] != m.values[7] ||

		   m.values[8] != m.values[8] ||
		   m.values[9] != m.values[9] ||
		   m.values[10] != m.values[10] ||
		   m.values[11] != m.values[11] ||

		   m.values[12] != m.values[12] ||
		   m.values[13] != m.values[13] ||
		   m.values[14] != m.values[14] ||
		   m.values[15] != m.values[15];
}

vec4 mat4::operator*(const vec4 &v){
	vec4 r = vec4();

	r.x = values[0]*v.x+values[4]*v.y+values[8]*v.z+values[12]*v.w;
	r.y = values[1]*v.x+values[5]*v.y+values[9]*v.z+values[13]*v.w;
	r.z = values[2]*v.x+values[6]*v.y+values[10]*v.z+values[14]*v.w;
	r.w = values[3]*v.x+values[7]*v.y+values[11]*v.z+values[15]*v.w;

	return r;
}

vec3 mat4::operator*(const vec3 &v){
	vec3 r = vec3();

	r.x = values[0]*v.x+values[4]*v.x+values[8]*v.x+values[12];
	r.y = values[1]*v.y+values[5]*v.y+values[9]*v.y+values[13];
	r.z = values[2]*v.z+values[6]*v.z+values[10]*v.z+values[14];

	return r;
}

float* mat4::getArray(){
	return values;
}

void mat4::clear(){
	for(int i = 0; i < 16; i++){
		values[i] = 0;
	}
}

float mat4::determinate(){
	float determinate;
		
	determinate = values[0]*values[4]*values[8]+values[1]*values[5]*values[6]+values[2]*values[3]*values[7];
	determinate -= values[2]*values[4]*values[6]+values[0]*values[5]*values[7]+values[1]*values[3]*values[8];
		
	return determinate;
}

mat4 mat4::normalize(){
	mat4 m;

	m.values[0] = values[0];
	m.values[1] = values[1];
	m.values[2] = values[2];
	m.values[3] = values[4];
	m.values[4] = values[5];
	m.values[5] = values[6];
	m.values[6] = values[8];
	m.values[7] = values[9];
	m.values[8] = values[10];

	float det = 1/m.determinate();

	values[0] = (m.values[4]*m.values[8]-m.values[5]*m.values[7])*det;
	values[1] = (m.values[5]*m.values[6]-m.values[3]*m.values[8])*det;
	values[2] = (m.values[3]*m.values[7]-m.values[4]*m.values[6])*det;

	values[3] = (m.values[2]*m.values[7]-m.values[1]*m.values[8])*det;
	values[4] = (m.values[0]*m.values[8]-m.values[2]*m.values[6])*det;
	values[5] = (m.values[1]*m.values[6]-m.values[8]*m.values[7])*det;

	values[6] = (m.values[1]*m.values[5]-m.values[2]*m.values[4])*det;
	values[7] = (m.values[2]*m.values[3]-m.values[0]*m.values[5])*det;
	values[8] = (m.values[0]*m.values[4]-m.values[1]*m.values[3])*det;

	return *this;
}

mat4 mat4::inverse(){
	mat4 m = mat4(values);

	values[0] = m.values[0];
	values[1] = m.values[4];
	values[2] = m.values[8];
	values[4] = m.values[1];
	values[6] = m.values[9];
	values[8] = m.values[2];
	values[9] = m.values[6];

	values[12] = values[0]*-m.values[12]+values[4]*-m.values[13]+values[8]*-m.values[14];
	values[13] = values[1]*-m.values[12]+values[5]*-m.values[13]+values[9]*-m.values[14];
	values[14] = values[2]*-m.values[12]+values[6]*-m.values[13]+values[10]*-m.values[14];

	values[3] = 0;
	values[7] = 0;
	values[11] = 0;
	values[15] = 1;

	return *this;
}

mat4 mat4::transpose(){
	mat4 m = mat4(values);

	values[1] = m.values[4];
	values[2] = m.values[8];
	values[3] = m.values[12];

	values[4] = m.values[1];
	values[6] = m.values[9];
	values[7] = m.values[13];

	values[8] = m.values[2];
	values[9] = m.values[6];
	values[11] = m.values[14];

	values[12] = m.values[3];
	values[13] = m.values[2];
	values[14] = m.values[11];
		
	return *this;
}

void mat4::setIdentity(){
	for(int i = 0; i < 16; i++){
		values[i] = 0;
	}

	values[0] = 1;
	values[5] = 1;
	values[10] = 1;
	values[15] = 1;
}

void mat4::translate(const float x, const float y, const float z){
	mat4 m;

	m.setIdentity();

	m.values[12] = x;
	m.values[13] = y;
	m.values[14] = z;

	*this *= m;
}

void mat4::translate(const vec3 &v){
	translate(v.x, v.y, v.z);
}

void mat4::translate(const vec2 &v){
	translate(v.x, v.y, 0.0f);
}

void mat4::scale(const float x, const float y, const float z){
	mat4 m;

	m.setIdentity();
		
	m.values[0] = x;
	m.values[5] = y;
	m.values[10] = z;

	*this *= m;
}

void mat4::scale(const vec3 &v){
	scale(v.x, v.y, v.z);
}

void mat4::scale(const vec2 &v){
	scale(v.x, v.y, 0.0f);
}

void mat4::rotate(float angle, const float x, const float y, const float z){
	mat4 m;
	float co, si;
	vec3 axis;
		
	axis = vec3(x, y, z);
	axis.normalize();

	angle = angle*(M_PI/180.0f);
	si = sinf(angle);
	co = cosf(angle);
 
	m.values[0] = axis.x*axis.x*(1-co)+co;
	m.values[1] = axis.y*axis.x*(1-co)+axis.z*si;
	m.values[2] = axis.x*axis.z*(1-co)-axis.y*si;
	m.values[3]= 0;
 
	m.values[4] = axis.x*axis.y*(1-co)-axis.z*si;
	m.values[5] = axis.y*axis.y*(1-co)+co;
	m.values[6] = axis.y*axis.z*(1-co)+axis.x*si;
	m.values[7]= 0;
 
	m.values[8] = axis.x*axis.z*(1-co)+axis.y*si;
	m.values[9] = axis.y*axis.z*(1-co)-axis.x*si;
	m.values[10]= axis.z*axis.z*(1-co)+co;
	m.values[11]= 0;
 
	m.values[12] = 0;
	m.values[13] = 0;
	m.values[14]= 0;
	m.values[15]= 1;
		
	*this *= m;
}

void mat4::rotate(float angle, const vec3 &v){
	rotate(angle, v.x, v.y, v.z);
}

void mat4::lookAt(const float x, const float y, const float z, const float xlook, const float ylook, const float zlook, const float xup, const float yup, const float zup){
	mat4 m;
	vec3 dir, right, up, eye;
 
	eye.x = x;
	eye.y = y;
	eye.z = z;

	up.x = xup;
	up.y = yup;
	up.z = zup;
	
	dir.x = (xlook-x);
	dir.y = (ylook-y);
	dir.z = (zlook-z);
	dir.normalize();

	right.cross(dir, up);
	right.normalize();

	up.cross(right, dir);
	up.normalize();
 
	m.values[0] = right.x;
	m.values[4] = right.y;
	m.values[8] = right.z;
	m.values[12] = -right.dot(eye);
 
	m.values[1] = up.x;
	m.values[5] = up.y;
	m.values[9] = up.z;
	m.values[13] = -up.dot(eye);
 
	m.values[2] = -dir.x;
	m.values[6] = -dir.y;
	m.values[10] = -dir.z;
	m.values[14] = dir.dot(eye);
 
	m.values[3] = 0;
	m.values[7] = 0;
	m.values[11] = 0;
	m.values[15] = 1;

	*this *= m;
}

void mat4::lookAt(const vec3 &pos, const vec3 &look, const vec3 &up){
	lookAt(pos.x, pos.y, pos.z, look.x, look.y, look.z, up.x, up.y, up.z);
}

void mat4::perspective(const float fov, const float ratio, const float nearp, const float farp){
	mat4 m;		
	float f = 1/tan(fov*(M_PI/360));
 
	m.setIdentity();
 
	m.values[0] = f/ratio;
	m.values[5] = f;
	m.values[10] = (farp+nearp)/(nearp-farp);
	m.values[11] = -1;
	m.values[14] = (2*farp*nearp)/(nearp-farp);
	m.values[15] = 0;
 
	*this *= m;
}

void mat4::ortho(const int left, const int right, const int bottom, const int top, const float nearp, const float farp){
	if(left != right && bottom != top && nearp != farp){
		mat4 m = mat4();

		m.values[0] = 2/(float(right-left));
		m.values[5] = 2/(float(top-bottom));
		m.values[10] = -2/(farp-nearp);
		m.values[12] = -(float(right+left))/(float(right-left));
		m.values[13] = -(float(top+bottom))/(float(top-bottom));
		m.values[14] = -(farp+nearp)/(farp-nearp);
		m.values[15] = 1;

		*this *= m;
	}
}

mat3::mat3(){
	for(unsigned int i = 0; i < 9; i++){
		values[i] = 0;
	}
}

mat3::mat3(const mat3 &m){
	for(unsigned int i = 0; i < 9; i++){
		values[i] = m.values[i];
	}
}

mat3::mat3(const float m[9]){
	for(unsigned int i = 0; i < 9; i++){
		values[i] = m[i];
	}
}

mat3::mat3(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i){
	values[0] = a;
	values[1] = b;
	values[2] = c;
	values[3] = d;
	values[4] = e;
	values[5] = f;
	values[6] = g;
	values[7] = h;
	values[8] = i;
}

float mat3::operator[](const unsigned int v){
	if(v < 9){
		return values[v];
	}
	else{
		return 0;
	}
}

void mat3::operator=(const mat3 &m){
	for(unsigned int i = 0; i < 9; i++){
		values[i] = m.values[i];
	}
}

void mat3::operator=(float m[9]){
	for(unsigned int i = 0; i < 9; i++){
		values[i] = m[i];
	}
}

mat3 mat3::operator*(float v){
	mat3 m;

	for(unsigned int i = 0; i < 9; i++){
		m.values[i] = values[i]*v;
	}

	return m;
}

mat3 mat3::operator*(const mat3 &m){
	mat3 mat;

	mat.values[0] = m.values[0]*values[0]+m.values[1]*values[3]+m.values[2]*values[6];
	mat.values[1] = m.values[0]*values[1]+m.values[1]*values[4]+m.values[2]*values[7];
	mat.values[2] = m.values[0]*values[2]+m.values[1]*values[5]+m.values[2]*values[8];

	mat.values[3] = m.values[3]*values[0]+m.values[4]*values[3]+m.values[5]*values[6];
	mat.values[4] = m.values[3]*values[1]+m.values[4]*values[4]+m.values[5]*values[7];
	mat.values[5] = m.values[3]*values[2]+m.values[4]*values[5]+m.values[5]*values[8];

	mat.values[6] = m.values[6]*values[0]+m.values[7]*values[3]+m.values[8]*values[6];
	mat.values[7] = m.values[6]*values[1]+m.values[7]*values[4]+m.values[8]*values[7];
	mat.values[8] = m.values[6]*values[2]+m.values[7]*values[5]+m.values[8]*values[8];

	return mat;
}

mat3 mat3::operator/(float v){
	mat3 m;

	for(unsigned int i = 0; i < 9; i++){
		m.values[i] = values[i]/v;
	}

	return m;
}

mat3 mat3::operator/(const mat3 &m){
	mat3 mat;

	for(unsigned int i = 0; i < 9; i++){
		mat.values[i] = values[i]/m.values[i];
	}

	return mat;
}

mat3 mat3::operator+(float v){
	mat3 mat;

	for(unsigned int i = 0; i < 9; i++){
		mat.values[i] = values[i]+v;
	}

	return mat;
}

mat3 mat3::operator+(const mat3 &m){
	mat3 mat;

	for(unsigned int i = 0; i < 9; i++){
		mat.values[i] = values[i]+m.values[i];
	}

	return mat;
}

mat3 mat3::operator-(float v){
	mat3 mat;

	for(unsigned int i = 0; i < 9; i++){
		mat.values[i] = values[i]-v;
	}

	return mat;
}

mat3 mat3::operator-(const mat3 &m){
	mat3 mat;

	for(unsigned int i = 0; i < 9; i++){
		mat.values[i] = values[i]-m.values[i];
	}

	return mat;
}

mat3 mat3::operator*=(float v){
	for(unsigned int i = 0; i < 9; i++){
		values[i] *= v;
	}

	return *this;
}

mat3 mat3::operator*=(const mat3 &m){
	mat3 mat = mat3(getArray());

	values[0] = m.values[0]*mat.values[0]+m.values[1]*mat.values[3]+m.values[2]*mat.values[6];
	values[1] = m.values[0]*mat.values[1]+m.values[1]*mat.values[4]+m.values[2]*mat.values[7];
	values[2] = m.values[0]*mat.values[2]+m.values[1]*mat.values[5]+m.values[2]*mat.values[8];

	values[3] = m.values[3]*mat.values[0]+m.values[4]*mat.values[3]+m.values[5]*mat.values[6];
	values[4] = m.values[3]*mat.values[1]+m.values[4]*mat.values[4]+m.values[5]*mat.values[7];
	values[5] = m.values[3]*mat.values[2]+m.values[4]*mat.values[5]+m.values[5]*mat.values[8];

	values[6] = m.values[6]*mat.values[0]+m.values[7]*mat.values[3]+m.values[8]*mat.values[6];
	values[7] = m.values[6]*mat.values[1]+m.values[7]*mat.values[4]+m.values[8]*mat.values[7];
	values[8] = m.values[6]*mat.values[2]+m.values[7]*mat.values[5]+m.values[8]*mat.values[8];

	return *this;
}

mat3 mat3::operator/=(float v){
	for(unsigned int i = 0; i < 9; i++){
		values[i] /= v;
	}

	return *this;
}

mat3 mat3::operator/=(const mat3 &m){
	for(unsigned int i = 0; i < 9; i++){
		values[i] /= m.values[i];
	}

	return *this;
}

mat3 mat3::operator+=(float v){
	for(unsigned int i = 0; i < 9; i++){
		values[i] += v;
	}

	return *this;
}

mat3 mat3::operator+=(const mat3 &m){
	for(unsigned int i = 0; i < 9; i++){
		values[i] += m.values[i];
	}

	return *this;
}

mat3 mat3::operator-=(float v){
	for(unsigned int i = 0; i < 9; i++){
		values[i] -= v;
	}

	return *this;
}

mat3 mat3::operator-=(const mat3 &m){
	for(unsigned int i = 0; i < 9; i++){
		values[i] -= m.values[i];
	}

	return *this;
}

bool mat3::operator==(const mat3 &m){
	return m.values[0] == m.values[0] &&
		   m.values[1] == m.values[1] &&
		   m.values[2] == m.values[2] &&

		   m.values[3] == m.values[3] &&
		   m.values[4] == m.values[4] &&
		   m.values[5] == m.values[5] &&

		   m.values[6] == m.values[6] &&
		   m.values[7] == m.values[7] &&
		   m.values[8] == m.values[8];
}

bool mat3::operator!=(const mat3 &m){
	return m.values[0] != m.values[0] ||
		   m.values[1] != m.values[1] ||
		   m.values[2] != m.values[2] ||

		   m.values[3] != m.values[3] ||
		   m.values[4] != m.values[4] ||
		   m.values[5] != m.values[5] ||

		   m.values[6] != m.values[6] ||
		   m.values[7] != m.values[7] ||
		   m.values[8] != m.values[8];
}

vec3 mat3::operator*(const vec3 &v){
	vec3 r = vec3();

	r.x = values[0]*v.x+values[3]*v.y+values[6]*v.z;
	r.y = values[1]*v.x+values[4]*v.y+values[7]*v.z;
	r.z = values[2]*v.x+values[5]*v.y+values[8]*v.z;

	return r;
}

vec2 mat3::operator*(const vec2 &v){
	vec2 r = vec2();

	r.x = values[0]*v.x+values[3]*v.y+values[6];
	r.y = values[1]*v.x+values[4]*v.y+values[7];

	return r;
}

float* mat3::getArray(){
	return values;
}

void mat3::clear(){
	for(unsigned int i = 0; i < 9; i++){
		values[i] = 0;
	}
}

float mat3::determinate(){
	float determinate;

	determinate = values[0]*values[4]*values[8]+values[3]*values[7]*values[2]+values[6]*values[1]*values[5];
	determinate -= values[2]*values[4]*values[6]-values[5]*values[7]*values[0]-values[8]*values[1]*values[3];

	return determinate;
}

mat3 mat3::inverse(){
	mat3 m = mat3(getArray());

	float det = 1/determinate();

	values[0] = (m.values[4]*m.values[8]-m.values[7]*m.values[5])*det;
	values[1] = (m.values[7]*m.values[2]-m.values[1]*m.values[8])*det;
	values[2] = (m.values[1]*m.values[5]-m.values[4]*m.values[2])*det;

	values[3] = (m.values[6]*m.values[5]-m.values[3]*m.values[8])*det;
	values[4] = (m.values[0]*m.values[8]-m.values[6]*m.values[2])*det;
	values[5] = (m.values[3]*m.values[2]-m.values[0]*m.values[5])*det;

	values[6] = (m.values[3]*m.values[7]-m.values[6]*m.values[4])*det;
	values[7] = (m.values[6]*m.values[1]-m.values[0]*m.values[7])*det;
	values[8] = (m.values[0]*m.values[4]-m.values[3]*m.values[1])*det;

	return *this;
}

mat3 mat3::transpose(){
	mat4 m = mat4(values);

	values[1] = m.values[3];
	values[2] = m.values[6];
	values[3] = m.values[1];

	values[5] = m.values[7];
	values[6] = m.values[2];
	values[7] = m.values[5];

	return *this;
}

void mat3::setIdentity(){
	clear();

	values[0] = 1;
	values[4] = 1;
	values[8] = 1;
}

void mat3::translate(const float x, const float y){
	mat3 m;

	m.setIdentity();

	m.values[6] = x;
	m.values[7] = y;

	*this *= m;
}

void mat3::translate(const vec2 &v){
	translate(v.x, v.y);
}

void mat3::scale(const float x, const float y){
	mat3 m;

	m.setIdentity();

	m.values[0] = x;
	m.values[4] = y;

	*this *= m;
}

void mat3::scale(const vec2 &v){
	scale(v.x, v.y);
}

void mat3::rotate(float angle){
	mat3 m;
	float co, si;

	angle = angle*(M_PI/180.0f);
	si = sinf(angle);
	co = cosf(angle);

	m.values[0] = co;
	m.values[1] = si;
	m.values[2]= 0;

	m.values[3] = -si;
	m.values[4] = co;
	m.values[5]= 0;

	m.values[6] = 0;
	m.values[7] = 0;
	m.values[8]= 1;

	*this *= m;
}

void mat3::ortho(const int left, const int right, const int bottom, const int top){
	if(left != right && bottom != top){
		mat3 m = mat3();

		m.values[0] = 2/(float(right-left));
		m.values[4] = 2/(float(top-bottom));
		m.values[6] = -(float(right+left))/(float(right-left));
		m.values[7] = -(float(top+bottom))/(float(top-bottom));
		m.values[8] = 1;

		*this *= m;
	}
}

};
