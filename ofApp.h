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

	bool bHide;

	ofxPanel gui;
	ofxButton Circle;
	ofxButton Rectangle;
	ofxButton Triangle;
	ofxButton Line;

	void CircleButtonPressed();
	void TriangleButtonPressed();
	void RectangleButtonPressed();
	void LineButtonPressed();

	int polygon = 0;

	ofFbo fbo;
	ofPoint pts[3000];
	int nPts;
};

