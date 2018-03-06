#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void exit();

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);		

	ofxPanel gui;
	ofxButton Elipse;
	ofxButton Circle;
	ofxButton Carre;
	ofxButton Rectangle;
	ofxButton Triangle;
	ofxButton Draw;
	ofxButton Line;
	ofxIntSlider LineThickness;
	ofxColorSlider backgroundColor;
	ofxColorSlider LineColor;
	ofxColorSlider FillColor;

	void ElipseButtonPressed();
	void CircleButtonPressed();
	void TriangleButtonPressed();
	void CarreButtonPressed();
	void RectangleButtonPressed();
	void LineButtonPressed();
	void DrawButtonPressed();
	void LineThicknessChanged(int & LineThickness);

	int polygon = 0;
	int nPts;
	int mouse_press_x;
	int mouse_press_y;
	bool is_mouse_button_pressed;

	ofFbo fbo;
	ofPoint pts[3000];

	void draw_cursor(float x, float y) const;
	void draw_zone(float x1, float y1, float x2, float y2) const;
};

