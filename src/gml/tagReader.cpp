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
    playbackTag tag;
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
                        double x = foo.getValue("pt:x", 0.0, j);
                        double y = foo.getValue("pt:y", 0.0, j);
                        line.addVertex(ofPoint(x, y, 0));
                    }
                    tag.strokes.push_back(line);
                    foo.popTag();
                }
                tags.push_back(tag);
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
    tags.clear();
}

