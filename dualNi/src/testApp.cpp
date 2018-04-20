#include "testApp.h"

#include "ofxNI2.h"

ofxNI2::Device *device;
ofxNI2::Device *device2;
ofxNI2::IrStream ir;
ofxNI2::ColorStream color;
ofxNI2::DepthStream depth, depth2;

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	
	device = new ofxNI2::Device;
	device->setup(1);
	device2 = new ofxNI2::Device;
	device2->setup(0);

	if (depth.setup(*device))
	{
		depth.setSize(320, 240);
		depth.setFps(30);
		depth.start();
	}

	if (depth2.setup(*device2))
	{
		depth2.setSize(320, 240);
		depth2.setFps(30);
		depth2.start();
	}

	if (ir.setup(*device)) // only for xtion device (OpenNI2-FreenectDriver issue)
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

	sender.init("Asus1");
	sender2.init("Asus2");
	fbo.allocate(320, 240, GL_RGBA);
	fbo2.allocate(320, 240, GL_RGBA);
}

void testApp::exit()
{
	device->exit();
	delete device;
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
	//depth.draw(320, 0);
	//depth2.draw(320, 240);

	fbo.begin();
	depth.draw(0, 0);
	fbo.end();
	fbo2.begin();
	depth2.draw(0, 0);
	fbo2.end();
	sender.send(fbo.getTexture());
	sender2.send(fbo2.getTexture());
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