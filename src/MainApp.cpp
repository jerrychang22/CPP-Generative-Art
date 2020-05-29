#include <iostream>
#include <unistd.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/Context.h"
#include "cinder/Rand.h"
#include <glm/glm.hpp>

#include "BlobBoid.h"

using namespace ci;
using namespace ci::app;
using namespace glm;
using namespace std;

const int window_len = 900;

//Main, add sub-apps
class MainApp : public App {
    public :
        void setup() override;
        void update() override;
        void draw() override;
    private :
        void render_to_FBO();
        
        gl::FboRef      mFbo;
        BlobBoid        bb;
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
    setWindowSize(window_len, window_len);
    //Initialize framebuffer
    //gl::Fbo::Format format;
    mFbo = gl::Fbo::create(window_len, window_len);

    //Seed RNG
    cinder::Rand::randomize();
    //srand(time(NULL));
    
    //Generate agent objects, in this case, Blobs
    this->bb = BlobBoid(100, window_len, window_len, 20, 60);
    cout << "Setup complete" << "\n";
}

//Draw to FBO
//Call other draw() functions here
void MainApp::render_to_FBO(){
    gl::ScopedFramebuffer sfb(mFbo);
    
    //gl::clear to clear SFB
    gl::clear(Color::white());
    gl::ScopedViewport svp( ivec2(0), mFbo->getSize());
    //gl::viewport( mFbo->getBounds() ); 
    //Call agent draw()
    bb.draw();
}

void MainApp::update(){

    //Update agent info
    bb.update();

    //Update FBO
    render_to_FBO();

    usleep(50000);
}

//Draw FBO to screen
void MainApp::draw(){
    gl::clear(Color::white());
    gl::color(Color::white());
    mFbo->bindTexture();
    gl::draw(mFbo->getColorTexture());
    
}

//Invoke run App macro
CINDER_APP( MainApp, RendererGl, prepareSettings )
