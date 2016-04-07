//
//  tagWriter.cpp
//  metTag
//
//  Created by Daniel Moore on 12/12/12.
//  Copyright 2012 File:Print. All rights reserved.
//

#include "tagWriter.h"

tagWriter::tagWriter(){
    setupGML();
    tagStart  = false;
    useLength = false;
    tagIndex = 0;
}

tagWriter::~tagWriter(){
    
}

void tagWriter::setup(){
    setupGML();
    tagStart  = false;
    useLength = false;
    tagIndex = 0;
}

void tagWriter::reset(){
    
}

//
// This sets up the gml file with a dummy header for now
// includes some optional gml spec
// needs to use more of the optional spec
//

void tagWriter::setupGML(){
    
    fileName = "session-"+ofToString(ofGetDay())+"-"+ofToString(ofGetHours())+"-"+ofToString(ofGetMinutes())+"-"+ofToString(ofGetSeconds())+".gml";
    gml.loadFile(fileName);
    gml.addTag("gml");
    gml.pushTag("gml");
    gml.addValue("spec", "1.0");
    gml.addTag("tag");
    gml.pushTag("tag");
    gml.addTag("header");
    gml.pushTag("header");//<headers>
    gml.addTag("client");//<client>
    gml.pushTag("client");
    gml.addValue("name", "metTag");
    gml.addValue("version", 1.0);
    gml.addValue("username", "FILL THIS IN");
    gml.addValue("keywords","ofxGML");
    gml.popTag();//</client>
    gml.popTag();//</header>
    
    gml.addTag("envrionment");
    gml.pushTag("envrionment");//push<envrionment>
    
    gml.addTag("offset");
    gml.pushTag("offset");//<offset>
    gml.addValue("x", 0);
    gml.addValue("y", 0);
    gml.addValue("z", 0);
    gml.popTag();//</offset>
    
    gml.addTag("up");
    gml.pushTag("up");//<up>
    gml.addValue("x", 0);
    gml.addValue("y", -1);
    gml.addValue("z", 0);
    gml.popTag();//</up>
    
    gml.addTag("screenBounds");
    gml.pushTag("screenBounds");//<screenBounds>
    gml.addValue("x", ofGetWidth());
    gml.addValue("y", ofGetHeight());
    gml.addValue("z", 0);
    gml.popTag();//</screenBounds>
    gml.popTag();//</envrionment>
    gml.saveFile(fileName);
    numSteps = 500;
    tagStart = false;
    brushCount = 0;
    tagTimeStart = ofGetElapsedTimef();
}

void tagWriter::startCapture(){
    tagTimeStart = ofGetElapsedTimef();

}

void tagWriter::addPoint(ofVec3f pt){
    float t = ofGetElapsedTimef() - tagTimeStart;
    if( gml.pushTag("stroke", lastTagNumber) ){
        int tagNum = gml.addTag("pt");
        gml.pushTag("pt", tagNum);
        gml.setValue("x", pt.x, tagNum);
        gml.setValue("y", pt.y, tagNum);
        gml.setValue("z", pt.z, tagNum);
        gml.setValue("t", ofGetElapsedTimef()-tagTimeStart, tagNum);
        gml.popTag();
        gml.popTag();
    }
}

void tagWriter::addPoint(float x, float y, float z){
    float t = abs(tagTimeStart-ofGetElapsedTimef());
    if( gml.pushTag("stroke", lastTagNumber) ){
        int tagNum = gml.addTag("pt");
        gml.pushTag("pt", tagNum);
        gml.setValue("x", x, tagNum);
        gml.setValue("y", y, tagNum);
        gml.setValue("z", z, tagNum);
        gml.setValue("t", ofGetElapsedTimef()-tagTimeStart, tagNum);
        gml.popTag();
        gml.popTag();
    }
}

void tagWriter::addPoint(float x, float y){
    float t = abs(tagTimeStart-ofGetElapsedTimef());
    if( gml.pushTag("stroke", lastTagNumber) ){
		int tagNum = gml.addTag("pt");
        gml.pushTag("pt", tagNum);
		gml.setValue("x", x, tagNum);
		gml.setValue("y", y, tagNum);
        gml.setValue("t", ofGetElapsedTimef()-tagTimeStart, tagNum);
		gml.popTag();
        gml.popTag();
	}
}
void tagWriter::newStroke(){
    if(!tagStart){
        gml.addTag("drawing");
        gml.pushTag("drawing");
        tagStart = true;
        tagIndex = 0;
    }else{
        tagIndex++;
    }
    lastTagNumber	=  gml.addTag("stroke");
}

void tagWriter::setBrush(int num, ofColor c, int size){
    mColor = c;
    
    if(gml.getPushLevel() < 3){
        gml.addTag("drawing");
        gml.pushTag("drawing");
        tagStart = true;
        tagIndex = 0;
    }
    
    int tagNum = gml.addTag("brush");
    gml.pushTag("brush", tagNum);
    gml.addTag("color");
    gml.pushTag("color");
    gml.setValue("red", mColor.r, tagNum);
    gml.setValue("blue", mColor.b, tagNum);
    gml.setValue("green", mColor.g, tagNum);
    gml.popTag();//</color>
    gml.setValue("number", num, tagNum);
    gml.setValue("size", size, tagNum);
    gml.setValue("time", ofGetElapsedTimef()-tagTimeStart, tagNum);
    gml.popTag();//</brush>
}


void tagWriter::screenClear(){
    gml.addValue("clear", ofGetElapsedTimef()-tagTimeStart);
}


void tagWriter::endDrawing(){
    while(gml.getPushLevel() > 0){
        gml.popTag();
    }
    tagStart  = false;
    useLength = false;
    tagIndex = 0;
}

void tagWriter::saveFile(){
    endDrawing();
    gml.saveFile(fileName);
    gml.clear();
}

string tagWriter::getFileName(){
    return fileName;
}



