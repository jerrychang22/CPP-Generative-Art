#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <glm/glm.hpp>

using namespace ci;
using namespace ci::app;
using namespace glm;

typedef struct circle {
    vec2 pos;
    float r;
} circle;

class MainApp : public App {
    public :
        void setup() override;
        void draw() override;
        void addCircle(float x, float y, float r);
    private :
        std::vector<vec2> linePoints;
        std::vector<circle> circles;
};

void prepareSettings(MainApp::Settings* settings){
   // settings->setMultiTouchEnabled(false);
}

void MainApp::setup(){
    int x_spacing = 75;
    int num_x = getWindowWidth() % x_spacing;
    int x_padding = (getWindowWidth() - num_x * x_spacing) / 2;

    int y_spacing = 50;
    int num_y = getWindowHeight() % y_spacing;
    int y_padding = (getWindowHeight() - num_y * y_spacing) / 2;

    for (int i = 0; i < num_x; i++){
        for (int j = 0; j < num_y; j++){
            addCircle(i * x_spacing + x_padding, j * y_spacing + y_padding, std::rand() % 10 + 1);
        }
    }
}

void MainApp::addCircle(float x, float y, float r){
    circle newCircle;
    newCircle.pos = vec2(x, y);
    newCircle.r = r;
    circles.push_back(newCircle);
}

void MainApp::draw(){
    gl::clear(Color::gray(0));
    for (auto c : circles){
        cinder::gl::drawSolidCircle(c.pos, c.r);
    }

    /*
    double t = getElapsedSeconds();
    double scale = 100;
    double xshift = 300;
    double yshift = 400;
    //gl::color(cos(t), sin(t), 0.2*cos(t) + 0.2*sin(t));
    //gl::drawLine(vec2(scale * cos(t) + xshift, scale * sin(t) + yshift),
    //            vec2(scale * cos(t+1) + xshift, scale * sin(t+1) + yshift));
    */


}

CINDER_APP( MainApp, RendererGl, prepareSettings )
