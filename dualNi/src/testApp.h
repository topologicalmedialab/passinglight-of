#pragma once

#include "ofMain.h"
#include "ofxSpout.h"
#include "ofxGui.h"
#include "ofxAutoReloadedShader.h"

class testApp : public ofBaseApp
{
public:
	void setup();
	void exit();
	
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxSpout::Sender sender1;
	ofxSpout::Sender sender2;

	ofFbo fboMix;
	ofFbo fbo1;
	ofFbo fbo2;

	ofxAutoReloadedShader shaderMix;
	
	ofxPanel gui;
	ofxVec2Slider translate1, scale1, translate2, scale2;
	ofxFloatSlider rotate1, rotate2;
	ofxFloatSlider bias1,bias2;
};