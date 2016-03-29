//
//  tagWriter.h
//  metTag
//
//  Created by Daniel Moore on 12/12/12.
//  Copyright 2012 File:Print. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"


class tagWriter {
public:
    tagWriter();
    ~tagWriter();
    void setup();
    void addPoint(float x, float y);
    void newStroke();
    void saveFile();
    bool uploadFile();
    int tagIndex;
    void setBrush(int num, ofColor c, int size);
    void screenClear();
    string getFileName();
    void reset();
protected:
    
    bool useLength;
    void update();
    void setupGML();
    void endDrawing();
    ofxXmlSettings gml;
    string fileName;
    int numSteps;
    float tagTimeStart;
    float tagTimeEnd;
    bool tagStart;
    int lastTagNumber;
    int brushCount;
    ofColor mColor;

};