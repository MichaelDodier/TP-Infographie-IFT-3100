#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);		

	ofxPanel gui;
	ofxButton Circle;
	ofxButton Rectangle;
	ofxButton Triangle;
	ofxButton Draw;
	ofxButton Line;

	void CircleButtonPressed();
	void TriangleButtonPressed();
	void RectangleButtonPressed();
	void LineButtonPressed();
	void DrawButtonPressed();

	int polygon = 0;
	int nPts;
	int mouse_press_x;
	int mouse_press_y;
	bool is_mouse_button_pressed;

	ofFbo fbo;
	ofPoint pts[3000];

	void draw_cursor(float x, float y) const;
	void ofApp::draw_zone(float x1, float y1, float x2, float y2) const;
};

