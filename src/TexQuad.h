//
//  TexQuad.h
//  ofApp
//
//  Created by Ben Van Citters on 12/2/13.
//
//

#ifndef __ofApp__TexQuad__
#define __ofApp__TexQuad__

#include <iostream>
#include "ofMain.h"

class TexQuad
{
public:
    TexQuad(ofVec2f pos, ofVec2f sz, ofVec2f vel);
    ofVboMesh mQuad;
    ofVec2f mStartPosition;
    ofVec2f mPosition;
    ofVec2f mVelocity;
    ofVec2f mSz;
    void resetPosition();
    void update();
    void draw();
};

#endif /* defined(__ofApp__TexQuad__) */
