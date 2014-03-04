#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup()
{
 	ofSetVerticalSync(true);
    
 	ofSetFrameRate(120);
    ofDisableArbTex();
    ofEnableNormalizedTexCoords();
    // this line grabs the last video device in the list... either the onboard webcam or whatever was plugged in
    cam.setDeviceID(cam.listDevices().size()-1);
 	cam.initGrabber(320, 240);
 	mCurTexture.allocate(ofGetWindowWidth(),ofGetWindowHeight(),OF_IMAGE_COLOR);
 	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    ofVec2f partDivs(16,9);
    partDivs *= 3;
    
        float xstps = partDivs.x;
        float ystps = partDivs.y;
    
    ofVec2f quadSz(ofGetWindowWidth()/xstps,ofGetWindowHeight()/ystps);
    ofVec2f windowSz(ofGetWindowWidth(),ofGetWindowHeight());
    cout << "window size: " <<  windowSz << "\nquadSz: " << quadSz << endl;
 	for(int y = 0; y < ystps; y++)
    {
        float yPct = y*1.f/ystps;
        
 		for(int x = 0; x < xstps; x++)
        {
            float xPct = x*1.f/xstps;
            quads.push_back(TexQuad(ofVec2f(xPct*windowSz.x,yPct*windowSz.y),
                                    ofVec2f(quadSz.x,quadSz.y),
                                    ofVec2f::zero()));
 		}
 	}
 	ofSetBackgroundAuto(false);
    
    getImageList();
}


void testApp::getImageList()
{
    string path = "";
    ofDirectory dir(path);
    dir.allowExt("jpg");
    dir.listDir();
    for(int i = 0; i < dir.numFiles(); i++)
    {
        mArts[i].loadImage(dir.getPath(i));
        ofLogNotice(dir.getPath(i));
    }
    randomizeCurrentImage();
}

void testApp::randomizeCurrentImage()
{
    int randIndex = (int)ofRandom(IMAGE_COUNT);
    mCurBackTexture = &mArts[randIndex];
}

void testApp::exit()
{
}

void testApp::update()
{
    cam.update();
 	if(cam.isFrameNew())
    {
        if(ofRandom(1) < .9)
        {
            mCurTexture.grabScreen(0,0,ofGetWindowWidth(),ofGetWindowHeight());
//            mCurTexture.resize(320, 240);
        }
        else
        {
            randomizeCurrentImage();
            mCurTexture.setFromPixels(cam.getPixels(), cam.width, cam.height, OF_IMAGE_COLOR);
            for(int i = 0; i < quads.size();i++)
            {
                quads[i].resetPosition();
            }
        }
        
        int windowSz = 8;
        flow.setWindowSize(windowSz);
 		flow.calcOpticalFlow(cam);
        ofVec2f ofWindowSz(ofGetViewportWidth(),ofGetWindowHeight());
        ofVec2f camSz(cam.width,cam.height);
        
        for(int i = 0; i < quads.size();i++)
        {
            ofVec2f relativeQuadSz(quads[i].mSz*camSz/ofWindowSz);
            ofVec2f relativePos(quads[i].mPosition*camSz/ofWindowSz);
            ofRectangle area(relativePos+relativeQuadSz/4,
                             relativeQuadSz.x,
                             relativeQuadSz.y);
            if(area.x > 0 && area.y > 0 && area.getRight() < 320 && area.getBottom() < 240)
            {
                ofVec2f vel =flow.getAverageFlowInRegion(area);
//                ofVec2f vel = flow.getFlowPosition(area.x, area.y);
                quads[i].mVelocity = (quads[i].mVelocity+vel) *.4;
                
            }
            quads[i].update();
        }
 	}
}

void testApp::draw()
{
//	ofBackground(0,0,0,0);
//	ofScale(2, 2);
//	ofBackground(0,0,0,0);ofGetWindowWidth(),ofGetWindowHeight()
//    float hScale = 0;
    mCurBackTexture->draw(0,0, ofGetWindowWidth(),ofGetWindowHeight());
    float hScale = ofGetWindowWidth()/640.f; // ofGetWindowHeight()/640.f;
        hScale = ofGetMouseX()*2.f/ofGetWindowWidth();
        float vScale = ofGetMouseY()*2.f/ofGetWindowHeight();
//    cout << "hscale: " << hScale << " v scale: " << vScale << endl;
    
//        mCurTexture.draw(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
//    	ofScale(1.60,1.5);
    
    
//    cam.getTextureReference().bind();
    mCurTexture.bind();
    
    for(int i = 0; i < quads.size();i++)
    {
        quads[i].draw();
    }
    mCurTexture.unbind();
//    ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
}
