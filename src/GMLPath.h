//
//  GMLPath.h
//  Lemur
//
//  Created by Dan Moore on 7/7/13.
//
//

#pragma once
#include "tagReader.h"

class GMLPath {
    string filepath;
    
public:
    GMLPath(){};
    ~GMLPath(){};
    GMLPath(string _filepath){
        loadFile(_filepath, 0, 0, 640, 480);
    }
    void loadFile(string _filepath, float x, float y, float maxx, float maxy);
    void draw();
    vector<ofPolyline> getPath(float scale);
    tagReader reader;
    vector<ofPolyline> polys;
    vector<ofPolyline> scaledLines;
    float aspectRatio;
};
