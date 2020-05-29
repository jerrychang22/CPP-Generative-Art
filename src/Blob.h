#ifndef BLOB_H
#define BLOB_H

#include "cinder/gl/gl.h"
#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std; 
using namespace ci;

class Blob {
    public :
        
        Blob();
        Blob(float x, float y, float direction, float size, float vel_x, float vel_y, ColorT<float> color);
        
        vec2 get_pos();
        float get_dir();
        float get_size();
        vec2 get_vel();
        ColorT<float> get_color();
        vector<Blob*> get_nn();

        void rotate_blob(float angle);
        void rotate_blob();
        void set_vel(vec2 vel);
        void set_color(ColorT<float> color);
        void set_nn(vector<Blob*> nn);
        vector<vec2> get_vertices();

        void update();
        void update(vector<vec2> vels);
        void draw();
    
    private : 
        vec2 _pos;
        float _dir;
        float _size;
        vec2 _vel;
        ColorT<float> _color;

        vector<Blob*> _knn; 
};

#endif
