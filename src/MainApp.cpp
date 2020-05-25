#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "cinder/Rand.h"
#include <glm/glm.hpp>
#include <time.h>

#include "Blob.h"

using namespace ci;
using namespace ci::app;
using namespace glm;
using namespace std;


//Main, add sub-apps
class MainApp : public App {
    public :
        void setup() override;
        void update() override;
        void draw() override;
    private :
        void render_to_FBO();
        
        gl::FboRef      mFbo;
        vector<Blob>    triangles;
};

//No additional settins yet
//Define window size in future
void prepareSettings(MainApp::Settings* settings){
   // settings->setMultiTouchEnabled(false);
}

//Future
//Cin << user input for 
//1) choosing art
//2) user parameters
void MainApp::setup(){
    //Initialize framebuffer
    gl::Fbo::Format format;
    mFbo = gl::Fbo::create(getWindowWidth(), getWindowHeight(), format.depthTexture() );

    //Seed RNG
    cinder::Rand::randomize();
    //srand(time(NULL));
    
    //Generate agent objects, in this case, Blobs
    Blob test_blob(randInt(getWindowWidth()), randInt(getWindowHeight()), 1.2, 10, 10, 5, Color(1, 0, 0));
    triangles.push_back(test_blob);
}

//Draw to FBO
//Call other draw() functions here
void MainApp::render_to_FBO(){
    gl::ScopedFramebuffer sfb(mFbo);
    //gl::clear to clear SFB
    gl::ScopedViewport svp( ivec2(0), mFbo->getSize());

    gl::color( Color::black());
    
    //Call agent draw()
    for (auto &t : triangles){
        t.draw();
    }
}

void MainApp::update(){

    //Update agent info
    float vx = (getElapsedSeconds() / 2) * cos(10 * getElapsedSeconds());
    float vy = (getElapsedSeconds() / 2) * sin(10 * getElapsedSeconds());
    for (auto &t : triangles){
        t.set_vel(vec2(vx, vy));
        t.rotate_blob(0.2);
        t.set_color(Color(randFloat(), randFloat(), randFloat()));
        t.update();
    }

    //Update FBO
    render_to_FBO();
}

//Draw FBO to screen
void MainApp::draw(){
    gl::clear(Color::gray(1));
    mFbo->bindTexture();
    gl::draw(mFbo->getColorTexture());
    
}

//Invoke run App macro
CINDER_APP( MainApp, RendererGl, prepareSettings )
