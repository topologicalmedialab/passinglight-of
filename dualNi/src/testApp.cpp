#include "testApp.h"

#include "ofxNI2.h"

ofxNI2::Device *device1;
ofxNI2::Device *device2;
ofxNI2::IrStream ir;
ofxNI2::ColorStream color;
ofxNI2::DepthStream depth1, depth2;

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	
	device1 = new ofxNI2::Device;
	device1->setup(1);
	device2 = new ofxNI2::Device;
	device2->setup(0);

	if (depth1.setup(*device1))
	{
		depth1.setSize(320, 240);
		depth1.setFps(30);
		depth1.start();
	}

	if (depth2.setup(*device2))
	{
		depth2.setSize(320, 240);
		depth2.setFps(30);
		depth2.start();
	}

	if (ir.setup(*device1)) // only for xtion device (OpenNI2-FreenectDriver issue)
	{
		ir.setSize(320, 240);
		ir.setFps(30);
		ir.start();
	}
	
//	if (color.setup(*device)) // only for kinect device
//	{
//		color.setSize(320, 240);
//		color.setFps(60);
//		color.start();
//	}

	sender1.init("Asus1");
	sender2.init("Asus2");
	fbo1.allocate(320, 480, GL_RGBA);
	fbo2.allocate(320, 480, GL_RGBA);
	fboMix.allocate(320, 480, GL_RGBA);

	shaderMix.load("shaders/mix");

	gui.setup(); // most of the time you don't need a name
	gui.add(translate1.setup("translate1", ofVec2f(160, 120), ofVec2f(0, 0), ofVec2f(320, 480)));
	gui.add(scale1.setup("scale1", ofVec2f(1, 1), ofVec2f(0, 0), ofVec2f(2, 2)));
	gui.add(rotate1.setup("rotate1", 0, -180, 180));
	gui.add(translate2.setup("translate2", ofVec2f(160, 120 + 240), ofVec2f(0, 0), ofVec2f(320, 480)));
	gui.add(scale2.setup("scale2", ofVec2f(1, 1), ofVec2f(0, 0), ofVec2f(2, 2)));
	gui.add(rotate2.setup("rotate2", 0, -180, 180));
}

void testApp::exit()
{
	device1->exit();
	delete device1;
	device2->exit();
	delete device2;
}

//--------------------------------------------------------------
void testApp::update()
{
}

//--------------------------------------------------------------
void testApp::draw()
{
	//ir.draw();
	//color.draw();

	// need this!!!
	// depthX may not be available - in this case we need buffered texture!
	// and make sure uncomment setupShader in ofxNI2.cpp!!
	fbo1.begin();
	ofBackground(0);
	ofPushMatrix();
	ofTranslate(translate1->x, translate1->y);
	ofRotate(rotate1);
	ofScale(scale1->x, scale1->y);
	depth1.draw(-160, -120);
	ofPopMatrix();
	fbo1.end();

	fbo2.begin();
	ofBackground(0);
	ofPushMatrix();
	ofTranslate(translate2->x, translate2->y);
	ofRotate(rotate2);
	ofScale(scale2->x, scale2->y);
	depth2.draw(-160, -120);
	ofPopMatrix();
	fbo2.end();

	fboMix.begin();
	ofBackground(0);
	ofSetColor(255);
	ofFill();
	shaderMix.begin();
	shaderMix.setUniformTexture("depth1", fbo1, 0);
	shaderMix.setUniformTexture("depth2", fbo2, 1);
	ofDrawPlane(fboMix.getWidth() * 0.5f, fboMix.getHeight() * 0.5f,
		fboMix.getWidth() * 1, fboMix.getHeight() * 1);
	shaderMix.end();
	fboMix.end();

	fboMix.draw(0, 0);

	gui.draw();

	sender1.send(fboMix.getTexture());
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}