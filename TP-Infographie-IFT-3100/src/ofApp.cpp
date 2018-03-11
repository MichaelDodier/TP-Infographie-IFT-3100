#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	nPts = 0;
	ofSetCircleResolution(60);

	//Initiallisation du GUI
	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);

	//Ajouts des éléments du GUI
	folder1 = gui->addFolder("Module 1", ofColor::blueSteel);
	folder1->addButton("Importer une image");
	gui->addBreak();
	folder2 = gui->addFolder("Module 2", ofColor::greenYellow);
	folder2->addButton("Elipse");
	folder2->addButton("Cercle");
	folder2->addButton("Carre");
	folder2->addButton("Rectangle");
	folder2->addButton("Triangle");
	folder2->addButton("Dessin Libre");
	folder2->addButton("Ligne");
	folder2->addSlider("Ep. lignes contour", 1, 10, 5);
	folder2->addColorPicker("Couleur background", ofColor::whiteSmoke);
	folder2->addColorPicker("Couleur contour", ofColor::grey);
	folder2->addColorPicker("Couleur formes", ofColor::black);
	gui->addBreak();
	folder3 = gui->addFolder("Module 3", ofColor::orangeRed);
	gui->addBreak();
	folder4 = gui->addFolder("Module 4", ofColor::thistle);
	gui->addBreak();
	folder5 = gui->addFolder("Module 5", ofColor::whiteSmoke);

	//Assignation des variables
	backgroundColor = ofColor::lightGray;
	lineColor = ofColor::grey;
	fillColor = ofColor::black;

	//Initialisation des events Listeners
	gui->onButtonEvent(this, &ofApp::onButtonEvent);
	gui->onSliderEvent(this, &ofApp::onSliderEvent);
	gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);

	//Initialisation du FrameBuffer
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(255, 255, 255);
	fbo.end();
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e){
	if (e.target->is("Importer une image")) {
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select an image file");

		if (openFileResult.bSuccess) {
			ofLogVerbose("User selected a file");
			processOpenFileSelection(openFileResult);
		}
		else {
			ofLogVerbose("User hit cancel");
		}
	}
	else if (e.target->is("Elipse")) {
		polygon = 1;
	}
	else if (e.target->is("Triangle")){
		polygon = 2;
	}
	else if (e.target->is("Rectangle")){
		polygon = 3;
	}
	else if (e.target->is("Dessin Libre")){
		polygon = 4;
	}
	else if (e.target->is("Ligne")){
		polygon = 5;
	}
	else if (e.target->is("Carre")){
		polygon = 6;
	}
	else if (e.target->is("Cercle")) {
		polygon = 7;
	}
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
	if (e.target->is("Ep. lignes contour")) {
		lineThickness = e.target->getValue();
	}
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e) {
	if (e.target->is("Couleur background")) {
		backgroundColor = e.color;
	}
	else if (e.target->is("Couleur contour")) {
		lineColor = e.color;
	}
	else if (e.target->is("Couleur formes")) {
		fillColor = e.color;
	}
}

//--------------------------------------------------------------
void ofApp::exit(){
}


//--------------------------------------------------------------
void ofApp::update(){
	ofSetLineWidth(lineThickness);
}

//--------------------------------------------------------------
void ofApp::draw(){

	img.draw(0, 0);

	//importe une image
	for (unsigned int i = 0; i<loadedImages.size(); i++) {
		loadedImages[i].draw(0, 0);
	}

	//Change la couleur de Background
	ofSetBackgroundColor(backgroundColor);

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
		for (int i = 0; i < nPts - 1; i++){
			ofLine(pts[i].x, pts[i].y, pts[i + 1].x, pts[i + 1].y);
		}
	}

	//Affiche le curseur
	draw_cursor(ofGetMouseX(), ofGetMouseY());
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (nPts < 3000 && polygon == 4){
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
void ofApp::mouseReleased(int x, int y, int button) {
	is_mouse_button_pressed = false;
	float diameter_x = ofGetMouseX() - mouse_press_x;
	float diameter_y = ofGetMouseY() - mouse_press_y;
	int minValue = min(diameter_x, diameter_y);
	ofSetLineWidth(lineThickness);

	//Dessine une forme selon l'option choisi
	fbo.begin();
	switch (polygon) {
		//Dessine une élipse
		case 1:
			ofFill();
			ofSetColor(fillColor);
			ofDrawEllipse(mouse_press_x + diameter_x / 2.0f, mouse_press_y + diameter_y / 2.0f, diameter_x, diameter_y);

			//Ligne de contour
			ofNoFill();
			ofSetColor(lineColor);
			ofDrawEllipse(mouse_press_x + diameter_x / 2.0f, mouse_press_y + diameter_y / 2.0f, diameter_x, diameter_y);
			break;
			//Dessine un triangle
		case 2:
			ofFill();
			ofSetColor(fillColor);
			ofTriangle(mouse_press_x, mouse_press_y, ofGetMouseX(), mouse_press_y, mouse_press_x + (diameter_x / 2), ofGetMouseY());

			//Ligne de contour
			ofNoFill();
			ofSetColor(lineColor);
			ofTriangle(mouse_press_x, mouse_press_y, ofGetMouseX(), mouse_press_y, mouse_press_x + (diameter_x / 2), ofGetMouseY());
			break;
			//Dessine un rectangle
		case 3:
			ofFill();
			ofSetColor(fillColor);
			ofDrawRectangle(mouse_press_x, mouse_press_y, diameter_x, diameter_y);

			//Ligne de contour
			ofNoFill();
			ofSetColor(lineColor);
			ofDrawRectangle(mouse_press_x, mouse_press_y, diameter_x, diameter_y);
			break;
			//Dessine une ligne
		case 5:
			ofFill();
			ofSetColor(fillColor);
			ofDrawLine(mouse_press_x, mouse_press_y, ofGetMouseX(), ofGetMouseY());
			break;
			//Dessine un carre
		case 6:
			ofFill();
			ofSetColor(fillColor);
			ofDrawRectangle(mouse_press_x, mouse_press_y, minValue, minValue);

			//Ligne de contour
			ofNoFill();
			ofSetColor(lineColor);
			ofDrawRectangle(mouse_press_x, mouse_press_y, minValue, minValue);
			break;
			//Dessine un cercle
		case 7:
			ofFill();
			ofSetColor(fillColor);
			ofDrawEllipse(mouse_press_x + diameter_x / 2.0f, mouse_press_y + diameter_y / 2.0f, minValue, minValue);

			//Ligne de contour
			ofNoFill();
			ofSetColor(lineColor);
			ofDrawEllipse(mouse_press_x + diameter_x / 2.0f, mouse_press_y + diameter_y / 2.0f, minValue, minValue);
			break;
	}
	fbo.end();
}

bool sortColorFunction(ofColor i, ofColor j) {
	return (i.getBrightness()<j.getBrightness());
}

// Fonction qui ouvre une image
void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {

	ofFile file(openFileResult.getPath());

	if (file.exists()) {
		//Limiting this example to one image so we delete previous ones
		processedImages.clear();
		loadedImages.clear();
		string fileExtension = ofToUpper(file.getExtension());
		//We only want images
		if (fileExtension == "JPG" || fileExtension == "PNG") {
			//Save the file extension to use when we save out
			originalFileExtension = fileExtension;
			//Load the selected image
			ofImage image;
			image.load(openFileResult.getPath());
			if (image.getWidth()>ofGetWidth() || image.getHeight() > ofGetHeight())
			{
				image.resize(image.getWidth() / 2, image.getHeight() / 2);
			}
			loadedImages.push_back(image);
			//Make some short variables 
			int w = image.getWidth();
			int h = image.getHeight();
			//Make a new image to save manipulation by copying the source
			ofImage processedImage = image;
			//Walk through the pixels
			for (int y = 0; y < h; y++) {
				//Create a vector to store and sort the colors
				vector<ofColor> colorsToSort;
				for (int x = 0; x < w; x++) {
					//Capture the colors for the row
					ofColor color = image.getColor(x, y);
					colorsToSort.push_back(color);
				}
				//Sort the colors for the row
				sort(colorsToSort.begin(), colorsToSort.end(), sortColorFunction);
				for (int x = 0; x < w; x++)
				{
					//Put the sorted colors back in the new image
					processedImage.setColor(x, y, colorsToSort[x]);
				}
			}
			//Store the processed image
			processedImages.push_back(processedImage);
		}
	}
}

// Fonction qui dessine un curseur
void ofApp::draw_cursor(float x, float y) const
{
	ofNoFill();
	switch (polygon) {
		//Curseur de l'elipse
	case 1:
		ofHideCursor();
		ofDrawEllipse(x, y, 20, 14);
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
		ofDrawLine(x - 5, y - 5, x + 5, y + 5);
		break;
		//Curseur du carre
	case 6:
		ofHideCursor();
		ofDrawRectangle(x - 10, y - 10, 20, 20);
		break;
		//Curseur du cercle
	case 7:
		ofHideCursor();
		ofCircle(x, y, 10);
		break;
	}
}

void ofApp::draw_zone(float x1, float y1, float x2, float y2) const{
	if (polygon != 4)
	{
		float x2_clamp = min(max(0.0f, x2), (float)ofGetWidth());
		float y2_clamp = min(max(0.0f, y2), (float)ofGetHeight());

		ofDrawRectangle(x1, y1, x2_clamp - x1, y2_clamp - y1);
	}
}