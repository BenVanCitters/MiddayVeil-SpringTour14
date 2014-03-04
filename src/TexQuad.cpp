//
//  TexQuad.cpp
//  ofApp
//
//  Created by Ben Van Citters on 12/2/13.
//
//

#include "TexQuad.h"

TexQuad::TexQuad(ofVec2f pos, ofVec2f sz, ofVec2f vel):mSz(sz),mPosition(pos),mStartPosition(pos),mVelocity(vel)
{
    ofVec2f vidSize(320, 240);
//    ofVec2f one(1.f,1.f);
    ofVec2f windowSz(ofGetViewportWidth(),ofGetWindowHeight());
    mQuad.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    mQuad.addVertex(ofVec2f(0,0));
    mQuad.addTexCoord(pos/windowSz);
    
    mQuad.addVertex(ofVec2f(sz.x,0));
    mQuad.addTexCoord(ofVec2f(pos.x+sz.x,pos.y)/windowSz);
    
    mQuad.addVertex(ofVec2f(0,sz.y));
    mQuad.addTexCoord(ofVec2f(pos.x,pos.y+sz.y)/windowSz);
    
    mQuad.addVertex(sz);
    mQuad.addTexCoord((pos+sz)/windowSz);
}

void TexQuad::resetPosition()
{
    mPosition = mStartPosition;
}

void TexQuad::update()
{
    mPosition += mVelocity;
}

void TexQuad::draw()
{
    //texture should already be bound
    ofPushMatrix();
    ofSetColor(ofColor(
    ofTranslate(mPosition);
    mQuad.draw();
    ofPopMatrix();
}