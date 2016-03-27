#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    fbo.allocate(128, 128, GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 0);
    fbo.end();
    dir.listDir("PATH/TO/GML");
    dir.allowExt(".gml");
    tagIndex = 0;
    strokeIndex = 0;
    gmlReader.setup(0, 0, 128, 128);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(strokeIndex < currentTag.size()){
        fbo.begin();
        ofClear(0, 0, 0, 0);
        ofSetColor(255, 255, 255);
        ofPushMatrix();
        ofTranslate(fbo.getWidth()/2, fbo.getHeight()/2);
        currentTag[strokeIndex].draw();
        ofPopMatrix();
        fbo.end();
        strokeIndex++;
        fboReader.readToPixels(fbo, pixels);
        ofImage img;
        img.setFromPixels(pixels);
        img.update();
        img.save("/PATH/TO/SAVE/"+ofToString(tagIndex)+"-"+ofToString(strokeIndex)+".png");
    }else{
        loadGML();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofSetColor(255, 255, 255);
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::loadGML(){
    if(tagIndex < dir.size()){
        gmlReader.loadFile(dir.getPath(tagIndex));
        vector<ofPolyline> lines = gmlReader.tag.strokes;
        for(int i = 0; i < lines.size(); i++){
            gmlReader.centerAndNormalize(lines[i]);
            gmlReader.scale(lines[i], fbo.getWidth()-10, fbo.getHeight()-10);
        }
        strokes.push_back(lines);
        tagIndex++;
        if(strokes.size() > 0){
            currentTag = strokes.front();
            strokes.pop_front();
            strokeIndex = 0;
        }
    }else{
          ofExit();
    }
}
