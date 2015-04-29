//This code was written by Andreas Muller as part of his Noise Workshop. 
//The .h file has been separated into a .h and .cpp and the code has been commented by Joni, but otherwise remains the same. 
//This has been done for educational purposes.

#pragma once

#include "ofMain.h"
#include "ofxGui.h" //includes the ofxGui addon so we can have easily made guis

class ofApp : public ofBaseApp
{
	public:
		void setup(); //this gives us a setup funtion
		void update(); //this gives us an update funtion
		void threshold( bool _upload ); //this gives us a threshold funtion (which returns a bool)
		void draw(); //this gives us a draw funtion
		void resolutionChanged( int& _res ); //this gives us a resolution changed funtion, which will use the slider to change the resolution
		void keyPressed (int _key); //this gives us a keyPressed funtion
	
		ofParameter<int> resolution; //parameters for resolution
		ofParameter<float> noiseFrequency; //parameters for frequency
		ofParameter<bool> animate; //parameters (bool) for whether or not to animate
	
		ofParameter<bool> doThreshold; //parameters (bool) for whether or not to show threshold
		ofParameter<int> thresholdLow; //parameters for the low (black) threshold
		ofParameter<int> thresholdHigh; //parameters for the high (white) threshold
		ofParameter<bool> invert; //parameters (bool) for whether or not to invert the threshold
	
		int noiseStartX; //the starting x position of the noise
		int noiseStartY; //the starting y position of the noise
	
		ofImage noiseImage; //the image that is used for the noise
	
		ofxPanel gui; //gui panel
		bool drawGui; //boolean to decide if gui panel is shown
};
