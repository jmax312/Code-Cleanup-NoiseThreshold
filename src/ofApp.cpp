//This code was written by Andreas Muller as part of his Noise Workshop. 
//The .h file has been separated into a .h and .cpp and the code has been commented by Joni, but otherwise remains the same. 
//This has been done for educational purposes.

#include "ofApp.h"

		void ofApp::setup()
		{
			
			resolution.addListener(this, &ofApp::resolutionChanged ); //this is used for the slider for resolution, to see if it's been changed
			
			gui.setup( "Main", "Main.xml" ); //this will set up the gui panel
			
			gui.add( resolution.set( "Resolution", 512, 2, 1024 ) ); //slider for resolution (name shown, starting value, lowest value, highest value)
			gui.add( noiseFrequency.set( "Noise Frequency", 80.0f, 0.00001f, 4096.0f ) ); //slider for frequency 
			gui.add( animate.set( "Animate", false ) ); //button for animate (turned off at start)
			
			gui.add( doThreshold.set( "Threshold", false ) ); //button for showing the thresholds (makes things stark black and white)
			gui.add( thresholdLow.set( "Treshold Low", 0, 0, 255 ) ); //slider for low (black) threshold
			gui.add( thresholdHigh.set( "Treshold High", 127, 0, 255 ) ); //slider for high (white) threshold
			gui.add( invert.set( "Invert Threshold", false ) ); //button for inverting the low and high thresholds
			
			noiseStartX = 0; //starting x positon of noise
			noiseStartY = 0; //starting y postion of noise
			
			drawGui = true; //boolean for whether or not to show the gui (true at start)
			
			noiseImage.allocate( resolution, resolution, OF_IMAGE_GRAYSCALE ); //allocates an image to be used (?) and makes it greyscale
		}
		
		//--------------------------------------------------------------
		void ofApp::update()
		{
			if( ofGetKeyPressed(OF_KEY_LEFT)  )  { noiseStartX += 5; } //these move the noise start position variables 5 pixels based on arrow key presses
			if( ofGetKeyPressed(OF_KEY_RIGHT ) ) { noiseStartX -= 5; }
			if( ofGetKeyPressed(OF_KEY_UP)  )    { noiseStartY += 5; }
			if( ofGetKeyPressed(OF_KEY_DOWN ) )  { noiseStartY -= 5; }
			
			float time = 0.0f; //the time variable used for animating (set at 0 while "animate" is false)
			if( animate ) time = ofGetElapsedTimef(); //sets the time variable to the elapsed time in seconds if "animate" is true
			
			ofPixelsRef pixels = noiseImage.getPixelsRef(); //gets the pixels reference (?) from the image
			
			int tmpIndex = 0; //an integer (temp Index?)
			for( int y = 0; y < noiseImage.getHeight(); y++ ) //while y is less than the height of the image...
			{
				for( int x = 0; x < noiseImage.getWidth(); x++ ) //and while x is less than the width of the image...
				{
					// We're grabbing a single reading from the noise function here, but we can also add together more
					// readings at different frequencies to make more complex patterns
					
					float tmpNoise = ofNoise( (noiseStartX + x) / noiseFrequency, (noiseStartY + y) / noiseFrequency, time ); //makes a float that uses the noise of x and y postions divided by the frequency
					
					pixels[tmpIndex] = tmpNoise * 255.0f; //makes the pixels of the image change according to the noise
					tmpIndex++; //adds one to the tmpIndex each time the for loops go through
				}
			}
			
			if( doThreshold) //if doThreshold is true...
			{
				threshold( false ); //threshold is false
			}
			
			noiseImage.update(); // uploads the new pixels to the gfx card
		}
		
		//--------------------------------------------------------------
		void ofApp::threshold( bool _upload ) //this is for when threshold is on
		{
			ofPixelsRef pixels = noiseImage.getPixelsRef(); //references the pixels of the image(?)
			
			int tmpIndex = 0; //sets an integer to be used below
			for( int y = 0; y < noiseImage.getHeight(); y++ ) //while y is less than the height of the image...
			{
				for( int x = 0; x < noiseImage.getWidth(); x++ ) //and while x is less than the width of the image...
				{
					if( pixels[tmpIndex] >= thresholdLow && pixels[tmpIndex] <= thresholdHigh ) //if the array of pixels (which is set to tmpIndex) is greater than the low threshhold and less than the high one...
					{
						pixels[tmpIndex] = 255; //then the pixels are white
					}
					else
					{
						pixels[tmpIndex] = 0; //otherwise they're black
					}
					
					if( invert ) //if the invert button is true
					{
						pixels[tmpIndex] = 255 - pixels[tmpIndex]; //then invert the black and white
					}
					
					tmpIndex++; //add one to the tmpIndex each time the for loops go through
				}
			}
			
			
			if( _upload ) //if uploading...
			{
				noiseImage.update(); // uploads the new pixels to the gfx card
			}
		}
		
		
		//--------------------------------------------------------------
		void ofApp::draw()
		{
			ofBackgroundGradient( ofColor(0), ofColor(40), OF_GRADIENT_CIRCULAR ); //makes the background a nice gradient of gray
			
			ofRectangle imageRect(0,0,noiseImage.getWidth(), noiseImage.getHeight() ); //makes a rectangle the size of the image
			imageRect.scaleTo( ofRectangle(0,0,ofGetWidth(),ofGetHeight()) ); //and scales it to the image
			noiseImage.draw( imageRect ); //draws the image used in the rectangle that was drawn
			
			if( drawGui ) //if the gui bool is true...
			{
				gui.draw(); //show the gui panel
			}
			
		}
		
		//--------------------------------------------------------------
		void ofApp::resolutionChanged( int& _res ) //keeps track of the resolution slider change and performs an action based on it
		{
			noiseImage.allocate( _res, _res, OF_IMAGE_GRAYSCALE ); //allocates an image to be used and makes it greyscale
		}


		//--------------------------------------------------------------
		void ofApp::keyPressed( int _key )
		{
			if( _key == 'f' ) //if the f button is pushed...
			{
				ofToggleFullscreen(); //make the app fullscreen
			}
		}