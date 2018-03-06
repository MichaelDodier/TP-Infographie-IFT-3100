#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	nPts = 0;

	//Initiallisation du GUI
	Circle.addListener(this, &ofApp::CircleButtonPressed);
	Rectangle.addListener(this, &ofApp::RectangleButtonPressed);
	Triangle.addListener(this, &ofApp::TriangleButtonPressed);
	Line.addListener(this, &ofApp::LineButtonPressed);

	gui.setup();
	gui.add(Circle.setup("Circle"));
	gui.add(Rectangle.setup("Rectangle"));
	gui.add(Triangle.setup("Triangle"));
	gui.add(Line.setup("Line"));

	//Initialisation du FrameBuffer
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(255, 255, 255);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::CircleButtonPressed() {
	polygon = 1;
}

void ofApp::TriangleButtonPressed() {
	polygon = 2;
}

void ofApp::RectangleButtonPressed() {
	polygon = 3;
}

void ofApp::LineButtonPressed() {
	polygon = 4;
}
void ofApp::exit(){
}


//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 0, 0);
	gui.draw();
	fbo.draw(0, 0);

	if (nPts > 1) {
		for (int i = 0; i < nPts - 1; i++) {
			ofLine(pts[i].x, pts[i].y, pts[i + 1].x, pts[i + 1].y);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (nPts < 3000 && polygon == 4) {
		pts[nPts].x = x;
		pts[nPts].y = y;
		nPts++;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	fbo.begin();
	switch (polygon) {
	case 1:
		ofCircle(x, y, 100);
		break;
	case 2:
		ofTriangle(x - 40, y + 40, x + 40, y + 40, x, y - 40);
		break;
	case 3:
		ofDrawRectangle(x, y, 200, 100);
		break;
	}
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
