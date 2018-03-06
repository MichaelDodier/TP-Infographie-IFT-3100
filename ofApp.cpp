#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	nPts = 0;
	ofSetCircleResolution(60);

	//Création des eventsListener
	Circle.addListener(this, &ofApp::CircleButtonPressed);
	Rectangle.addListener(this, &ofApp::RectangleButtonPressed);
	Triangle.addListener(this, &ofApp::TriangleButtonPressed);
	Draw.addListener(this, &ofApp::DrawButtonPressed);
	Line.addListener(this, &ofApp::LineButtonPressed);
	LineThickness.addListener(this, &ofApp::LineThicknessChanged);

	//Initiallisation du GUI
	gui.setup();
	gui.add(Circle.setup("Cercle"));
	gui.add(Rectangle.setup("Rectangle"));
	gui.add(Triangle.setup("Triangle"));
	gui.add(Draw.setup("Dessin Libre"));
	gui.add(Line.setup("Ligne"));
	gui.add(LineThickness.setup("Ep. lignes contour", 1, 1, 10));

	//Initialisation du FrameBuffer
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(255, 255, 255);
	fbo.end();

	is_mouse_button_pressed = false;
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

void ofApp::DrawButtonPressed() {
	polygon = 4;
}

void ofApp::LineButtonPressed() {
	polygon = 5;
}

void ofApp::LineThicknessChanged(int &lineThickness) {
	ofSetLineWidth(lineThickness);
}

void ofApp::exit(){
}


//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::update(){
	ofSetLineWidth(LineThickness);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//Affiche le GUI
	gui.draw();

	//Afficher la zone de sélection
	if (is_mouse_button_pressed)
	{
		ofSetColor(255);
		ofSetLineWidth(3);
		ofNoFill();

		draw_zone(
			mouse_press_x,
			mouse_press_y,
			ofGetMouseX(),
			ofGetMouseY());
	}

	//Affiche le FrameBuffer
	fbo.draw(0, 0);

	//Dessine une ligne libre si elle existe 
	if (nPts > 1) {
		for (int i = 0; i < nPts - 1; i++) {
			ofLine(pts[i].x, pts[i].y, pts[i + 1].x, pts[i + 1].y);
		}
	}

	//Affiche le curseur
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
	//Garde en mémoire la position du clic d'origine
	mouse_press_x = x;
	mouse_press_y = y;
	is_mouse_button_pressed = true;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	is_mouse_button_pressed = false;
	float diameter_x = ofGetMouseX() - mouse_press_x;
	float diameter_y = ofGetMouseY() - mouse_press_y;
	ofSetLineWidth(LineThickness);

	//Dessine une forme selon l'option choisi
	fbo.begin();
	switch (polygon) {
	//Dessine une élipse
	case 1:
		ofFill();
		ofSetColor(255, 0, 0);
		ofDrawEllipse(mouse_press_x + diameter_x / 2.0f, mouse_press_y + diameter_y / 2.0f, diameter_x, diameter_y);

		//Ligne de contour
		ofNoFill();
		ofSetColor(0, 0, 0);
		ofDrawEllipse(mouse_press_x + diameter_x / 2.0f, mouse_press_y + diameter_y / 2.0f, diameter_x, diameter_y);
		break;
	//Dessine un triangle
	case 2:
		ofFill();
		ofSetColor(255, 0, 0);
		ofTriangle(mouse_press_x, mouse_press_y, ofGetMouseX(), mouse_press_y, mouse_press_x + (diameter_x/2), ofGetMouseY());

		//Ligne de contour
		ofNoFill();
		ofSetColor(0, 0, 0);
		ofTriangle(mouse_press_x, mouse_press_y, ofGetMouseX(), mouse_press_y, mouse_press_x + (diameter_x / 2), ofGetMouseY());
		break;
	//Dessine un rectangle
	case 3:
		ofFill();
		ofSetColor(255, 0, 0);
		ofDrawRectangle(mouse_press_x, mouse_press_y, diameter_x, diameter_y);

		//Ligne de contour
		ofNoFill();
		ofSetColor(0, 0, 0);
		ofDrawRectangle(mouse_press_x, mouse_press_y, diameter_x, diameter_y);
		break;
	//Dessine une ligne
	case 5:
		ofFill();
		ofSetColor(255, 0, 0);
		ofDrawLine(mouse_press_x, mouse_press_y, ofGetMouseX(), ofGetMouseY());
		break;
	}
	fbo.end();
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
	//Curseur de l'elipse
	case 1:
		ofHideCursor();
		ofCircle(x, y, 10);
		break;
	//Curseur du triangle 
	case 2:
		ofHideCursor();
		ofTriangle(x - 10, y + 10, x + 10, y + 10, x, y - 10);
		break;
	//Curseur du rectangle
	case 3:
		ofHideCursor();
		ofDrawRectangle(x - 10, y - 7, 20, 14);
		break;
	//Curseur du dessin libre
	case 4:
		ofHideCursor();
		ofDrawLine(x + 5, y, x + 15, y);
		ofDrawLine(x - 5, y, x - 15, y);
		ofDrawLine(x, y + 5, x, y + 15);
		ofDrawLine(x, y - 5, x, y - 15);
		break;
	//Curseur de la ligne
	case 5:
		ofHideCursor();
		ofDrawLine(x - 5, y -5, x + 5, y +5);
		break;
	}
}

void ofApp::draw_zone(float x1, float y1, float x2, float y2) const
{
	if (polygon != 4)
	{
		float x2_clamp = min(max(0.0f, x2), (float)ofGetWidth());
		float y2_clamp = min(max(0.0f, y2), (float)ofGetHeight());

		ofDrawRectangle(x1, y1, x2_clamp - x1, y2_clamp - y1);
	}
}
