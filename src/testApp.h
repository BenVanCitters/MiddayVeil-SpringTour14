#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "TexQuad.h"

#define IMAGE_COUNT 30

class testApp : public ofBaseApp
{
public:
    
	void setup();
	void update();
    void exit();
	void draw();
    void getImageList();
    void randomizeCurrentImage();
    std::vector<TexQuad> quads;
    
	ofVideoGrabber cam;
	ofxCv::FlowFarneback flow;
	ofMesh mesh;
    ofImage mCurTexture;
    ofImage* mCurBackTexture;
    ofImage mArts[IMAGE_COUNT];
};