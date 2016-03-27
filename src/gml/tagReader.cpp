//
//  tagReader.cpp
//  tag_Capture_simple
//
//  Created by Dan Moore on 3/13/13.
//
//

#include "tagReader.h"

tagReader::tagReader(){
    
}

tagReader::~tagReader(){
    
}
void tagReader::setup(float x, float y, float width, float height){
    zeroX = x;
    zeroY = y;
    maxX = width;
    maxY = height;
}

void tagReader::loadFile(string path){
    clear();
    tag.name = path;
    tag.offsetY = 0;
    tag.offsetX = 0;
    ofxXmlSettings foo;
    foo.loadFile(path);
    if(foo.tagExists("gml") || foo.tagExists("GML")){
        if(foo.pushTag("gml")){
            
        }else{
            foo.pushTag("GML");
        }
        
        if(foo.tagExists("tag")){
            foo.pushTag("tag");
            
            tag.screenX = 1;
            tag.screenY = 1;
            
            if(foo.tagExists("environment")){
                tag.offsetX = foo.getValue("environment:offset:x", 1.0);
                tag.offsetY = foo.getValue("environment:offset:y", 1.0);
                tag.screenX = foo.getValue("environment:screenBounds:x", ofGetWidth());
                tag.screenY = foo.getValue("environment:screenBounds:y", ofGetHeight());
            }
            
            if(foo.tagExists("drawing")){
                foo.pushTag("drawing");
                
                count = foo.getNumTags("stroke");
                for(int i = 0; i < foo.getNumTags("stroke"); i++){
                    foo.pushTag("stroke", i);
                    cout<<"STROKE: "<<i<<endl;
                    ofPolyline line;
                    int numPtTags = foo.getNumTags("pt");
                    for(int j = 0; j < numPtTags; j++){
                        double x = foo.getValue("pt:x", 0.0, j)*maxX;
                        double y = foo.getValue("pt:y", 0.0, j)*maxY*tag.screenY/tag.screenX;
                        line.addVertex(ofPoint(x, y, 0));
                    }
                    tag.strokes.push_back(line);
                    foo.popTag();
                }
            }else{
                cout<<"cannot load file 1"<<endl;
            }
        }else{
            cout<<"cannot load file 2"<<endl;
        }
    }else{
        cout<<"cannot load file 3"<<endl;
    }
    
    
}

void tagReader::clear(){
    tag.strokes.clear();
    tag.brushes.clear();
    tag.colors.clear();
}

void tagReader::getBoundingBox(vector<ofPolyline>& lines, ofVec3f& cornerMin, ofVec3f& cornerMax) {
    for(int j = 0; j < lines.size(); j++){
        const vector<ofVec3f>& vertices = lines[j].getVertices();
        if(vertices.size() > 0) {
            cornerMin = vertices[0];
            cornerMax = vertices[0];
        }
        for(int i = 0; i < vertices.size(); i++) {
            cornerMin.x = MIN(cornerMin.x, vertices[i].x);
            cornerMin.y = MIN(cornerMin.y, vertices[i].y);
            cornerMin.z = MIN(cornerMin.z, vertices[i].z);
            cornerMax.x = MAX(cornerMax.x, vertices[i].x);
            cornerMax.y = MAX(cornerMax.y, vertices[i].y);
            cornerMax.z = MAX(cornerMax.z, vertices[i].z);
        }
    }
}

void tagReader::centerAndNormalize(vector<ofPolyline>& lines, ofVec3f cornerMin, ofVec3f cornerMax) {
    ofVec3f translate = -(cornerMax + cornerMin) / 2;
    ofVec3f range = (cornerMax - cornerMin);
    float maxRange = 0;
    maxRange = MAX(maxRange, range.x);
    maxRange = MAX(maxRange, range.y);
    maxRange = MAX(maxRange, range.z);
    float scale = 1 / maxRange;
    for(int j = 0; j < lines.size(); j++){
        vector<ofVec3f>& vertices = lines[j].getVertices();
        for(int i = 0; i < vertices.size(); i++) {
            vertices[i] += translate;
            vertices[i] *= scale;
        }
    }
}

void tagReader::centerAndNormalize(vector<ofPolyline>& lines) {
    ofVec3f cornerMin, cornerMax;
    getBoundingBox(lines, cornerMin, cornerMax);
    centerAndNormalize(lines, cornerMin, cornerMax);
}

void tagReader::getBoundingBox(ofPolyline& line, ofVec3f& cornerMin, ofVec3f& cornerMax) {
    
    const vector<ofVec3f>& vertices = line.getVertices();
    if(vertices.size() > 0) {
        cornerMin = vertices[0];
        cornerMax = vertices[0];
    }
    for(int i = 0; i < vertices.size(); i++) {
        cornerMin.x = MIN(cornerMin.x, vertices[i].x);
        cornerMin.y = MIN(cornerMin.y, vertices[i].y);
        cornerMin.z = MIN(cornerMin.z, vertices[i].z);
        cornerMax.x = MAX(cornerMax.x, vertices[i].x);
        cornerMax.y = MAX(cornerMax.y, vertices[i].y);
        cornerMax.z = MAX(cornerMax.z, vertices[i].z);
    }
    
}

void tagReader::centerAndNormalize(ofPolyline& line, ofVec3f cornerMin, ofVec3f cornerMax) {
    ofVec3f translate = -(cornerMax + cornerMin) / 2;
    ofVec3f range = (cornerMax - cornerMin);
    float maxRange = 0;
    maxRange = MAX(maxRange, range.x);
    maxRange = MAX(maxRange, range.y);
    maxRange = MAX(maxRange, range.z);
    float scale = 1 / maxRange;
    
    vector<ofVec3f>& vertices = line.getVertices();
    for(int i = 0; i < vertices.size(); i++) {
        vertices[i] += translate;
        vertices[i] *= scale;
    }
    
}
void tagReader::scale(vector<ofPolyline>& lines, float scaleX, float scaleY){
    for(int j = 0; j < lines.size(); j++){
        scale(lines[j], scaleX, scaleY);
    }
}
void tagReader::scale(ofPolyline& line, float scaleX, float scaleY){
    vector<ofVec3f>& vertices = line.getVertices();
    for(int i = 0; i < vertices.size(); i++) {
        vertices[i] *= ofVec3f(scaleX, scaleY);
    }
}

void tagReader::centerAndNormalize(ofPolyline& line) {
    ofVec3f cornerMin, cornerMax;
    getBoundingBox(line, cornerMin, cornerMax);
    centerAndNormalize(line, cornerMin, cornerMax);
}
