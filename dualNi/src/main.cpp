#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main() {
	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);    // <--- ofxShadertoy NEEDS the GL Programmable Renderer
	settings.width = 640, settings.height = 480;
	//settings.monitor = 2;
	ofCreateWindow(settings);       // <-------- setup the GL context

									// this kicks off the running of my app
	ofRunApp(new testApp());
}