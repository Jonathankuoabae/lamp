#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	try
	{
		oniDevice.setup();
	}
	catch (exception e)
	{
		oniDevice.setup("c:\\1.oni");
	}


	depthStream.setup(oniDevice.getDevice());
	colorStream.setup(oniDevice.getDevice());
	//oniDevice.setRegistration(true);

	recorder.setup();
	recorder.addStream(depthStream.getStream());
	recorder.addStream(colorStream.getStream());

	handTracker.setup(depthStream.getDevice());
	userTracker.setup(depthStream.getDevice());

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	ofTexture colorTexture;
	ofPixels colorPixels = colorStream.getPixels(); 
	colorTexture.allocate(colorPixels);
	colorTexture.loadData(colorPixels);
	colorTexture.draw(0,0);

	ofTexture depthTexture;
	ofPtr<ofShortPixels> depthRawPixels = depthStream.getPixels();

	ofPixels depthPixels;
	depthPixels.allocate(depthRawPixels->getWidth(), depthRawPixels->getHeight(), OF_PIXELS_RGB);

	const unsigned short* prd = depthRawPixels->getPixels();
	unsigned char* pd = depthPixels.getPixels();
	for (int i = 0; i < depthRawPixels->size(); i++)
	{
		short s = prd[i];
		for (int j = 0; j < 3; j++)
		{
			pd[3 * i + j] = 255 - (s >> 4);
		}
	}


	depthTexture.allocate(depthPixels);
	depthTexture.loadData(depthPixels);
	depthTexture.draw(320,0);

	if (recorder.IsRecording())
	{
		ofPushStyle();
		ofSetColor(ofColor::red);
		ofFill();
		ofSetLineWidth(3);
		ofCircle(20, 20, 10);
		ofPopStyle();
	}

	cam.begin();

	cam.end();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){


	switch (key)
	{

	case OF_KEY_F8:
		if (!recorder.IsRecording())
		{
			string filename = ofGetTimestampString();
			recorder.start(filename);
		}

		return;

	case OF_KEY_F7:
		if (recorder.IsRecording())
		{
			recorder.stop();
		}
		return;

	case 'f': ofToggleFullscreen(); break;
	default:
		break;
	}
}

void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

void testApp::exit()
{
	userTracker.exit();
	handTracker.exit();
	colorStream.exit();
	depthStream.exit();
	oniDevice.exit();
}
