#pragma once

#include "ofMain.h"
#include "tagWriter.h"
#include "ofxStrip.h"
#include "pngBrush.h"
#include "vectorBrush.h"
#include "ofxXmlSettings.h"
#include "ofxGML.h"

#define PORT 12345
typedef struct {
    string name;
    ofColor color;
} colorNameMapping;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);

    void loadFiles();
    void getNextStroke();
    void getNextFile();
    void drawControls();
    
    tagWriter tagger;
    int index;
    bool tagStarted;
    vector<ofPolyline> tag;
    ofEasyCam cam;
	ofLight l1;
	ofLight l2;
	ofMaterial m1;
    
    
    
    
    vector<ofxXmlSettings> gml;
    deque<ofPolyline> files;
    vector<int> newFiles;
    int fileCount;
    
    pngBrush * pBrush;
    vectorBrush * vBrush;
    ofTexture colorTexture;
    ofTexture colorTexture2;
    
    tagReader reader;
    
    bool playback;
    int preFileIndex;
    int fileindex;
    int preStroke;
    int preStrokeIndex;
    int strokeIndex;
    int pointIndex;
    int colorIndex;
    int colorCount;
    int count;
    int numPT;
    float tagStart;
    float strokeStartTime;
    float preTime;
    
    //*brush data
    int brushWidth;
    int vBrushType;
    bool drips;
    bool switchBrush;
    bool clearAfter;
    map < string, ofColor > colorNameMap;
    
    vector < colorNameMapping > colorNames;
};
