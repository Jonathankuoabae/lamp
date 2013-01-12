#pragma once

#include "ofMain.h"

#include "ofxNite2.h"

class testApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		virtual void exit();

private:

		ofxOniDevice oniDevice;
		ofxDepthStream depthStream;
		ofxColorStream colorStream;
		ofxHandTracker handTracker;
		ofxUserTracker userTracker;
		ofxRecorder recorder;
		
		ofEasyCam cam;

};
