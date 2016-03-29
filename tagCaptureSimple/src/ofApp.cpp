#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60.0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetWindowTitle("tagCaptureSimple");
    
    
    index = 0;
    brushWidth = 20;
    
    tagger.setup();
    
    
    
    tagStarted = false;
    l1.setPosition(200, 300, 50);
    l2.setPosition(-100, -100, 50);
    cam.disableMouseInput();
    cam.setOrientation(ofPoint(0, -100, 0));
    pBrush = new pngBrush();
    pBrush->setup(ofGetWidth(), ofGetHeight());
    
    colorTexture.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, false);
    colorTexture2.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, false);
    
    
    
    pBrush->dripsSettings(true, 6, .200, 0, 1);
    
    vBrush = new vectorBrush();
    vBrush ->setup(ofGetWidth(), ofGetHeight());
    vBrush ->setBrushWidth(brushWidth);
    vBrush ->setBrushNumber(2);
    vBrush ->setBrushColor(255, 0, 255);
    
    playback = false;
    
    
    colorNameMap["white"] = ofColor::white;
    colorNameMap["red"] = ofColor::red;
    colorNameMap["green"] = ofColor::green;
    colorNameMap["blue"] = ofColor::blue;
    colorNameMap["cyan"] = ofColor::cyan;
    colorNameMap["magenta"] = ofColor::magenta;
    colorNameMap["yellow"] = ofColor::yellow;
    colorNameMap["aliceBlue"] = ofColor::aliceBlue;
    colorNameMap["aqua"] = ofColor::aqua;
    colorNameMap["aquamarine"] = ofColor::aquamarine;
    colorNameMap["azure"] = ofColor::azure;
    colorNameMap["blueViolet"] = ofColor::blueViolet;
    colorNameMap["brown"] = ofColor::brown;
    colorNameMap["cadetBlue"] = ofColor::cadetBlue;
    colorNameMap["chartreuse"] = ofColor::chartreuse;
    colorNameMap["chocolate"] = ofColor::chocolate;
    colorNameMap["cornflowerBlue"] = ofColor::cornflowerBlue;
    colorNameMap["crimson"] = ofColor::crimson;
    colorNameMap["darkBlue"] = ofColor::darkBlue;
    colorNameMap["darkCyan"] = ofColor::darkCyan;
    colorNameMap["darkGoldenRod"] = ofColor::darkGoldenRod;
    colorNameMap["darkGreen"] = ofColor::darkGreen;
    colorNameMap["darkMagenta"] = ofColor::darkMagenta;
    colorNameMap["darkSlateBlue"] = ofColor::darkSlateBlue;
    colorNameMap["darkSlateGray"] = ofColor::darkSlateGray;
    colorNameMap["darkSlateGrey"] = ofColor::darkSlateGrey;
    colorNameMap["darkTurquoise"] = ofColor::darkTurquoise;
    colorNameMap["darkViolet"] = ofColor::darkViolet;
    colorNameMap["deepPink"] = ofColor::deepPink;
    colorNameMap["deepSkyBlue"] = ofColor::deepSkyBlue;
    colorNameMap["dimGray"] = ofColor::dimGray;
    colorNameMap["dimGrey"] = ofColor::dimGrey;
    colorNameMap["dodgerBlue"] = ofColor::dodgerBlue;
    colorNameMap["fireBrick"] = ofColor::fireBrick;
    colorNameMap["floralWhite"] = ofColor::floralWhite;
    colorNameMap["forestGreen"] = ofColor::forestGreen;
    colorNameMap["fuchsia"] = ofColor::fuchsia;
    colorNameMap["gainsboro"] = ofColor::gainsboro;
    colorNameMap["ghostWhite"] = ofColor::ghostWhite;
    colorNameMap["gold"] = ofColor::gold;
    colorNameMap["goldenRod"] = ofColor::goldenRod;
    colorNameMap["grey"] = ofColor::grey;
    colorNameMap["greenYellow"] = ofColor::greenYellow;
    colorNameMap["honeyDew"] = ofColor::honeyDew;
    colorNameMap["hotPink"] = ofColor::hotPink;
    colorNameMap["indianRed "] = ofColor::indianRed ;
    colorNameMap["indigo "] = ofColor::indigo ;
    colorNameMap["ivory"] = ofColor::ivory;
    colorNameMap["teal"] = ofColor::teal;
    colorNameMap["thistle"] = ofColor::thistle;
    colorNameMap["tomato"] = ofColor::tomato;
    colorNameMap["turquoise"] = ofColor::turquoise;
    colorNameMap["violet"] = ofColor::violet;
    
    
    for (int i = 0; i < colorNameMap.size(); i++){
        
        map<string, ofColor>::iterator mapEntry = colorNameMap.begin();
        std::advance( mapEntry, i );
        
        colorNameMapping mapping;
        mapping.name = mapEntry->first;
        mapping.color = mapEntry->second;
        colorNames.push_back(mapping);
        
    }
    fileindex = 0;
    strokeIndex = 0;
    count = 0;
    fileCount = 0;
    playback = false;
    clearAfter = false;
    switchBrush = true;
    preTime = -1;
    pointIndex = 0;
    colorCount = 0;
    colorIndex = 0;
    
    pBrush->setBrushWidth(brushWidth);
    pBrush->setBrushNumber(9);
    pBrush->setBrushColor(colorNames[colorIndex].color.r, colorNames[colorIndex].color.g, colorNames[colorIndex].color.b, 255);
    tagger.setBrush(9, colorNames[colorIndex].color, brushWidth);
    
    preStrokeIndex = -1;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    pBrush->update();
    colorTexture.loadData(pBrush->getImageAsPixels(), ofGetWidth(), ofGetHeight(), GL_RGBA);
    float time = ofGetElapsedTimef();
    if(playback){
        
        if(fileindex < reader.tags.size()){
            
            if(strokeIndex < reader.tags[fileindex].strokes.size()){
                
                if(time-tagStart < reader.tags[fileindex].strokeEndTime[strokeIndex]){
                    
                    pointIndex = reader.tags[fileindex].strokes[strokeIndex].getIndexAtPercent((time - strokeStartTime)/reader.tags[fileindex].strokeDuration[strokeIndex]);
                    ofPoint pt = reader.tags[fileindex].strokes[strokeIndex].getPointAtIndexInterpolated(pointIndex);
                    cout<<pt<<endl;
                    
                    if(preStrokeIndex != strokeIndex){
                        preStrokeIndex = strokeIndex;
                        if(switchBrush){
                            pBrush->addPoint(pt.x, pt.y, true);
                        }else{
                            vBrush->addPoint(pt.x, pt.y, true);
                        }
                    }else{
                        if(switchBrush){
                            pBrush->addPoint(pt.x, pt.y, false);
                        }else{
                            vBrush->addPoint(pt.x, pt.y, false);
                        }
                    }
            
                    
                }else{
                    preStrokeIndex = strokeIndex;
                    strokeIndex++;
                    strokeStartTime = time;
                }
                if(colorCount < reader.tags[fileindex].colors.size()){
                    if(time-tagStart > reader.tags[fileindex].brushes[colorCount].time){
                        ofColor c = reader.tags[fileindex].colors[colorCount];
                        pBrush->setBrushColor(c.r, c.g, c.b, 255);
                        brushWidth = reader.tags[fileindex].brushes[colorIndex].size;
                        pBrush->setBrushNumber(reader.tags[fileindex].brushes[colorCount].num);
                        pBrush->setBrushWidth(brushWidth);
                        colorCount++;
                    }
                }else{
                    colorCount == reader.tags[fileindex].colors.size()-1;
                }
            }else{
                pointIndex = 0;
                strokeIndex = 0;
                preStrokeIndex = -1;
                colorCount = 0;
                tagStart = time;
                preFileIndex= fileindex;
                fileindex++;
                pBrush->clear();
            }
        }else{
            pointIndex = 0;
            strokeIndex = 0;
            preStrokeIndex = -1;
            colorCount = 0;
            fileindex = 0;
            tagStart = time;
            pBrush->clear();
        }
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    if(switchBrush){
        colorTexture.draw(0, 0);
    }else{
        vBrush->draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    drawControls();
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        if(!playback){
            tagger.saveFile();
            tagger.reset();
            tagger.setBrush(pBrush->getBrushNumber(), colorNames[colorIndex].color, brushWidth);
            tag.clear();
            index = 0;
        }
        tagStarted = false;
        pBrush->clear();
        vBrush->clear();
    }else if(key == OF_KEY_LEFT){
        brushWidth--;
        if(brushWidth < 10){
            brushWidth = 10;
        }
        pBrush->setBrushWidth(brushWidth);
        tagger.setBrush(pBrush->getBrushNumber(), colorNames[colorIndex].color, brushWidth);
    }else if (key == OF_KEY_RIGHT){
        brushWidth++;
        if(brushWidth > 65){
            brushWidth = 65;
        }
        pBrush->setBrushWidth(brushWidth);
        tagger.setBrush(pBrush->getBrushNumber(), colorNames[colorIndex].color, brushWidth);
    }else if (key == 'd' || key == 'D'){
        drips = !drips;
        pBrush->dripsSettings(drips, 10, .225, 0, 15);
    }else if (key == '+' || key == '='){
        clearAfter = !clearAfter;
    }else if(key == '0'){
        if(!switchBrush){
            switchBrush = true;
        }
        pBrush->setBrushNumber(0);
        tagger.setBrush(0, colorNames[colorIndex].color, brushWidth);
    }else if(key == '1'){
        if(!switchBrush){
            switchBrush = true;
        }
        pBrush->setBrushNumber(1);
        tagger.setBrush(1, colorNames[colorIndex].color, brushWidth);
    }else if(key == '2'){
        if(!switchBrush){
            switchBrush = true;
        }
        pBrush->setBrushNumber(2);
        tagger.setBrush(2, colorNames[colorIndex].color, brushWidth);
    }else if(key == '3'){
        if(!switchBrush){
            switchBrush = true;
        }
        pBrush->setBrushNumber(3);
        tagger.setBrush(3, colorNames[colorIndex].color, brushWidth);
    }else if(key == '4'){
        if(!switchBrush){
            switchBrush = true;
        }
        pBrush->setBrushNumber(4);
        tagger.setBrush(4, colorNames[colorIndex].color, brushWidth);
    }else if(key == '5'){
        if(!switchBrush){
            switchBrush = true;
        }
        pBrush->setBrushNumber(5);
        tagger.setBrush(5, colorNames[colorIndex].color, brushWidth);
    }else if(key == '6'){
        if(!switchBrush){
            switchBrush = true;
        }
        pBrush->setBrushNumber(6);
        tagger.setBrush(6, colorNames[colorIndex].color, brushWidth);
    }else if(key == '7'){
        if(!switchBrush){
            switchBrush = true;
        }
        pBrush->setBrushNumber(7);
        tagger.setBrush(7, colorNames[colorIndex].color, brushWidth);
    }else if(key == '8'){
        if(!switchBrush){
            switchBrush = true;
        }
        pBrush->setBrushNumber(8);
        tagger.setBrush(8, colorNames[colorIndex].color, brushWidth);
    }else if(key == '9'){
        if(!switchBrush){
            switchBrush = true;
        }
        pBrush->setBrushNumber(9);
        tagger.setBrush(9, colorNames[colorIndex].color, brushWidth);
    }else if(key == 'v'){
        if(switchBrush){
            switchBrush = false;
        }
        vBrushType++;
        if(vBrushType > 3){
            vBrushType = 0;
        }
        vBrush->setBrushNumber(vBrushType);
    }else if(key == 'c'){
        colorIndex++;
        if(colorIndex > colorNames.size()-1){
            colorIndex = 0;
        }
        pBrush->setBrushColor(colorNames[colorIndex].color.r, colorNames[colorIndex].color.g, colorNames[colorIndex].color.b, 255);
        vBrush->setBrushColor(colorNames[colorIndex].color.r, colorNames[colorIndex].color.g, colorNames[colorIndex].color.b);
        tagger.setBrush(pBrush->getBrushNumber(), colorNames[colorIndex].color, brushWidth);
    }else if(key == 'g' || key == 'G'){
        loadFiles();
        tagStart = ofGetElapsedTimef();
    }else if(key == 'h'){
        playback = false;
        files.clear();
        pBrush->clear();
        vBrush->clear();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

void ofApp::exit(){
    tagger.saveFile();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (x > brushWidth && x < brushWidth+100 && y > 0 && y < 50){
        
    }else if(!playback){
        float stroke_x = ofMap(x, 0, ofGetWidth(), 0, 1.0);
        float stroke_y = ofMap(y, 0, ofGetHeight(), 0, 1.0);
        
        tagger.addPoint(stroke_x, stroke_y);
        
        ofPolyline & line = tag[index];
        line.addVertex(x, y);
        
        if(switchBrush){
            pBrush->addPoint(stroke_x, stroke_y, false);
        }else{
            vBrush->addPoint(stroke_x, stroke_y, false);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (x > brushWidth && x < brushWidth+100 && y > 0 && y < 50){
        if(playback){
            
            playback = false;
            files.clear();
            pBrush->clear();
            vBrush->clear();
            tagger.setBrush(pBrush->getBrushNumber(), colorNames[colorIndex].color, brushWidth);
        }else{
            loadFiles();
            pointIndex = 0;
            strokeIndex = 0;
            colorCount = 0;
            fileindex = 0;
            
        }
        
    }else if(!playback){
        tagger.newStroke();
        ofPolyline p;
        tag.push_back(p);
        if(!tagStarted){
            tagStarted = true;
        }else{
            index++;
        }
        float stroke_x = ofMap(x, 0, ofGetWidth(), 0, 1);
        float stroke_y = ofMap(y, 0, ofGetHeight(), 0, 1);
        if(switchBrush){
            pBrush->addPoint(stroke_x, stroke_y, true);
        }else{
            vBrush->addPoint(stroke_x, stroke_y, true);
        }
        
    }
}

void ofApp::loadFiles(){
    
    gml.clear();
    newFiles.clear();
    reader.clear();
    dir.listDir(ofToDataPath(""));
    dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    //allocate the vector to have as many ofImages as files
    
    for(int i = 0; i < (int)dir.size(); i++){
        if(dir.getPath(i)!="../../../data/brushes"){
            string path = dir.getPath(i);
            reader.loadFile(path);
        }
    }
    
    pBrush->clear();
    vBrush->clear();
    
    fileindex = 0;
    strokeIndex = 0;
    pointIndex = 0;
    colorIndex = 0;
    
    tagStart = ofGetElapsedTimef();
    playback = true;
}


void ofApp::drawControls(){
    float rectHeight = brushWidth<50?50:brushWidth;
    ofSetColor(150, 150, 150);
    ofDrawRectangle(0, 0, ofGetWidth(),rectHeight);
    ofSetColor(255, 255, 255);
    
    pBrush->drawBrushColor(0, 0, brushWidth, brushWidth);
    pBrush->drawTool(brushWidth, 0, brushWidth, brushWidth);
    
    
    float x = brushWidth*2;
    
    
    if(playback)
        ofSetColor(255, 0, 0);
    else
        ofSetColor(0, 255, 0);
    
    ofDrawRectangle(x, 0, 100, rectHeight);
    x+=100;
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(playback==true?"Stop":"Play", ofPoint(x-75, 25));
    ofDrawBitmapString("file index: "+ofToString(index), ofPoint(x+70, 25));
    ofDrawBitmapString("stroke index: "+ofToString(strokeIndex), ofPoint(x+270, 25));
    ofDrawBitmapString("point index: "+ofToString(pointIndex), ofPoint(x+470, 25));
    ofDrawBitmapString("size: "+ofToString(reader.tags.size()), ofPoint(x+670, 25));
    ofDrawBitmapString("color: "+ofToString(colorIndex), ofPoint(x+870, 25));
    
    ///debug string
    if(playback){
        ofSetColor(150, 150, 150);
        ofDrawBitmapString("Playback Mode", ofPoint(25, ofGetHeight()-25));
        ofSetColor(255, 255, 255, 255);
    }else{
        ofSetColor(150, 150, 150);
        ofDrawBitmapString("Record Mode", ofPoint(25, ofGetHeight()-25));
        ofSetColor(255, 255, 255, 255);
    }
    
    ofSetColor(150, 150, 150);
    string keys = "SPACE BAR - SAVE \nBRUSH SIZE - LEFT/RIGHT ARROW KEYS \nG - PLAY \nH - RECORD \n0/9 - BRUSHES\nV - Vector Brush\nC - CHANGE COLOR\n ";
    ofDrawBitmapString("KEY COMMANDS: \n"+keys, ofPoint(25, ofGetHeight()-150));
    ofSetColor(255, 255, 255, 255);
}


