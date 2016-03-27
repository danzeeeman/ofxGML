#pragma once

#include "ofMain.h"
#include "ofxGML.h"
#include "ofxFastFboReader.h"
class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void loadGML();
    
    deque<vector<ofPolyline> > strokes;
    vector<ofPolyline> currentTag;
    ofFbo fbo;
    ofxFastFboReader fboReader;
    ofDirectory dir;
    int tagIndex;
    int strokeIndex;
    tagReader gmlReader;
    ofPixels pixels;
};
