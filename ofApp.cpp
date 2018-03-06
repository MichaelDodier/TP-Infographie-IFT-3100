#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	nPts = 0;
	ofSetCircleResolution(60);

	//Création des eventsListener
	Circle.addListener(this, &ofApp::CircleButtonPressed);
	Rectangle.addListener(this, &ofApp::RectangleButtonPressed);
	Triangle.addListener(this, &ofApp::TriangleButtonPressed);
	Line.addListener(this, &ofApp::LineButtonPressed);

	//Initiallisation du GUI
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
	gui.draw();
	fbo.draw(0, 0);

	if (nPts > 1) {
		for (int i = 0; i < nPts - 1; i++) {
			ofLine(pts[i].x, pts[i].y, pts[i + 1].x, pts[i + 1].y);
		}
	}

	draw_cursor(ofGetMouseX(), ofGetMouseY());
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
		ofFill();
		ofSetColor(0, 0, 0);
		ofCircle(x, y, 52);
		ofSetColor(255, 0, 0);
		ofCircle(x, y, 50);
		break;
	case 2:
		ofFill();
		ofSetColor(0, 0, 0);
		ofTriangle(x - 42, y + 42, x + 42, y + 42, x, y - 42);
		ofSetColor(255, 0, 0);
		ofTriangle(x - 40, y + 40, x + 40, y + 40, x, y - 40);
		break;
	case 3:
		ofFill();
		ofSetColor(0, 0, 0);
		ofDrawRectangle(x-101, y-51, 202, 102);
		ofSetColor(255, 0, 0);
		ofDrawRectangle(x-100, y-50, 200, 100);
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

// Fonction qui dessine un curseur
void ofApp::draw_cursor(float x, float y) const
{	
	ofNoFill();
	switch (polygon) {
	case 1:
		ofHideCursor();
		ofCircle(x, y, 10);
		break;
	case 2:
		ofHideCursor();
		ofTriangle(x - 10, y + 10, x + 10, y + 10, x, y - 10);
		break;
	case 3:
		ofHideCursor();
		ofDrawRectangle(x - 10, y - 7, 20, 14);
		break;
	case 4:
		ofHideCursor();
		ofDrawLine(x + 5, y, x + 15, y);
		ofDrawLine(x - 5, y, x - 15, y);
		ofDrawLine(x, y + 5, x, y + 15);
		ofDrawLine(x, y - 5, x, y - 15);
		break;
	}
}
