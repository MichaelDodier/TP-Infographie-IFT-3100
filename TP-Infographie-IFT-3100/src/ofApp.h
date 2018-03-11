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
	ofxDatGuiFolder* folder1;
	ofxDatGuiFolder* folder2;
	ofxDatGuiFolder* folder3;
	ofxDatGuiFolder* folder4;
	ofxDatGuiFolder* folder5;

	void onButtonEvent(ofxDatGuiButtonEvent e);
	void onSliderEvent(ofxDatGuiSliderEvent e);
	void onColorPickerEvent(ofxDatGuiColorPickerEvent e);

	int lineThickness;
	ofColor backgroundColor;
	ofColor lineColor;
	ofColor fillColor;
	ofColor tempColor;
	int tIndex;
	vector<ofImage>loadedImages;
	vector<ofImage>processedImages;
	string originalFileExtension;

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	int polygon = 0;
	string colorspace = "RGB";
	int nPts;
	int mouse_press_x;
	int mouse_press_y;
	bool is_mouse_button_pressed;

	ofFbo fbo;
	ofPoint pts[3000];

	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void draw_cursor(float x, float y) const;
	void draw_zone(float x1, float y1, float x2, float y2) const;
};

