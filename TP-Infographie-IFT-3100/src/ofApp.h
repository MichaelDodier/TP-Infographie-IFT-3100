#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void exit();

	ofxDatGui* gui;

	void onButtonEvent(ofxDatGuiButtonEvent e);
	void onSliderEvent(ofxDatGuiSliderEvent e);
	void onColorPickerEvent(ofxDatGuiColorPickerEvent e);

	int lineThickness;
	ofColor backgroundColor;
	ofColor lineColor;
	ofColor fillColor;
	int tIndex;
	vector<ofxDatGuiTheme*> themes;

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

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

