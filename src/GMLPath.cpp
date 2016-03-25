//
//  GMLPath.cpp
//  Lemur
//
//  Created by Dan Moore on 7/7/13.
//
//

#include "GMLPath.h"


void GMLPath::loadFile(string path, float x, float y, float maxx, float maxy){
    reader.setup(x, y, maxx, maxy);
    reader.loadFile(path);
    if(reader.tags.size() > 0){
        for(int i = 0; i < reader.tags.back().strokes.size(); i++){
            polys.push_back(reader.tags.back().strokes[i]);
        }
        aspectRatio = reader.tags.back().screenY/reader.tags.back().screenX;
    }
    
    scaledLines = getPath(1);
}

void GMLPath::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth()-200, ofGetHeight()-200);
    ofScale(200, 200);
    for(int i = 0; i < scaledLines.size(); i++){
        scaledLines[i].draw();
    }
    ofPopMatrix();
}

vector<ofPolyline> GMLPath::getPath(float scale){
    vector<ofPolyline> lines;
    ofQuaternion q;
    q.set(180, 0, 0, 0);
    q.makeRotate(180, 0, 0, 1);
    ofMatrix4x4 mat;
    q.get(mat);
    for(int i = 0; i < polys.size(); i++){
        ofPolyline line;
        for(int j = 0; j < polys[i].getVertices().size(); j++){
            line.addVertex(polys[i].getVertices()[j]*ofVec2f(scale, scale*aspectRatio)*mat);
        }
        lines.push_back(line);
    }
    return lines;
}
