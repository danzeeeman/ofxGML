#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    fbo.allocate(256, 256, GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 0);
    fbo.end();
    dir.listDir("/Volumes/LACIE SHARE/gml_xml");
    dir.allowExt(".gml");
    tagIndex = 0;
    strokeIndex = 0;
    gmlReader.setup(0, 0, 256, 256);
    loadGML();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    fbo.begin();
    ofClear(0, 0, 0, 0);
    ofSetColor(255, 255, 255);
    ofPushMatrix();
    ofSetColor(255, 255, 255);
    ofTranslate(fbo.getWidth()/2, fbo.getHeight()/2);
    for(int i = 0; i < currentTag.size(); i++){
        currentTag[i].draw();
    }
    ofPopMatrix();
    fbo.end();
    tagIndex++;
    fboReader.readToPixels(fbo, pixels);
    ofImage img;
    img.setFromPixels(pixels);
    img.update();
    img.save("/Volumes/LACIE SHARE/gml_tags_images/"+ofToString(tagIndex)+".png");
    
    loadGML();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofSetColor(255, 255, 255);
    fbo.draw(0, 0);
}

void ofApp::loadGML(){
    if(tagIndex < dir.size()){
        gmlReader.loadFile(dir.getPath(tagIndex));
        vector<ofPolyline> lines = gmlReader.tag.strokes;
        gmlReader.centerAndNormalize(lines);
        gmlReader.scale(lines, 250, 250);
        currentTag = lines;
    }
}
