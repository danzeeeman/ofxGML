//
//  tagReader.h
//  tag_Capture_simple
//
//  Created by Dan Moore on 3/13/13.
//
//
#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"

class tagReader{
    
public:
    
    tagReader();
    ~tagReader();
    
    struct brush{
        int num;
        int size;
        float time;
    };
    
    struct playbackTag{
        vector<ofColor> colors;
        vector<brush> brushes;
        vector<ofPolyline> strokes;
        vector<float> strokeDuration;
        vector<float> strokeStartTime;
        vector<float> strokeEndTime;;
        float startTime;
        float endTime;
        float duration;
        float offsetX;
        float offsetY;
        float screenX;
        float screenY;
        string name;
    };
    

    void setup(float x, float y, float width, float height);
    void loadFile(string path);
    void clear();
    void useTime(bool bUseTime_);
    
    void getBoundingBox(vector<ofPolyline>& lines, ofVec3f& cornerMin, ofVec3f& cornerMax);
    void centerAndNormalize(vector<ofPolyline>& lines, ofVec3f cornerMin, ofVec3f cornerMax);
    void centerAndNormalize(vector<ofPolyline>& lines);
    
    void getBoundingBox(ofPolyline& line, ofVec3f& cornerMin, ofVec3f& cornerMax);
    void centerAndNormalize(ofPolyline& line, ofVec3f cornerMin, ofVec3f cornerMax);
    void centerAndNormalize(ofPolyline& line);
    void scale(ofPolyline& line, float scaleX, float scaleY);
    void scale(vector<ofPolyline>& line, float scaleX, float scaleY);
    playbackTag tag;
    vector<playbackTag> tags;
protected:
    int strokeCount;
    float zeroX;
    float zeroY;
    float maxX;
    float maxY;
    
    bool bUseTime;
    
};