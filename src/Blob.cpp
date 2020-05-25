#include "Blob.h"
#include "cinder/gl/gl.h"
#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std;
using namespace ci;

//Constructors
Blob::Blob(){

}

Blob::Blob(float x, float y, float dir, float size, float vel_x, float vel_y, ColorT<float> color){
    _pos = vec2(x, y);
    _dir = dir;
    _size = size;
    _vel = vec2(vel_x, vel_y);
    _color = color;
}

//Accessors
vec2 Blob::get_pos(){
    return _pos;
}

float Blob::get_dir(){
    return _dir;
}

float Blob::get_size(){
    return _size;
}

vec2 Blob::get_vel(){
    return _vel;
}

ColorT<float> Blob::get_color(){
    return _color;
}

//Methods
void Blob::rotate_blob(float angle){
    _dir += angle;
}

void Blob::set_vel(vec2 vel){
    _vel = vel;
}

void Blob::set_color(ColorT<float> color){
    _color = color;
}

vector<vec2> Blob::get_vertices(){
    vector<vec2> vertices;
    vertices.push_back( vec2(_pos.x + cos(_dir) * _size, _pos.y + sin(_dir) * _size) );
    return vertices;
}


//Update and draw
void Blob::update(){
    _pos = vec2(_pos.x + _vel.x, _pos.y + _vel.y);
}

void Blob::update(vector<vec2> vels){
    _pos = vec2(_pos.x + _vel.x, _pos.y + _vel.y);
}

void Blob::draw(){
    cinder::gl::color(this->_color);
    cinder::gl::drawLine( _pos, this->get_vertices().back() );
}
