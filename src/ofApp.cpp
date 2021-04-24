#include "ofApp.h"

const int N = 256; //Number of bands in the spectrum
float spectrum[N]; //Smoothed spectrum values
float Rad   = 500; //Cloud radius parameter
float Vel   = 0.1; //Cloud points velocity
int bandRad = 2;   //Band Index in spectrum, affecting Rad value
int bandVel = 100; //Band index in spectrum, affecting Vel value

const int n = 300; //Number of cloud points

//Offset for Perlin noise calculation for points
float tx[n], ty[n];
ofPoint p[n]; //Cloud points position

float time0 = 0; //Time value, use for dt computation

//--------------------------------------------------------------
void
ofApp::setup()
{
	//Set up sound sample
	sound.load(arguments[1]);
	sound.setLoop(true);
	sound.play();

	//Set spectrum values to 0
	for(int i = 0; i < N; ++i)
	{
		spectrum[i] = 0.0f;
	}

	//Initialize points offset by random number
	for(int j = 0; j < n; ++j)
	{
		tx[j] = ofRandom(0, 1000);
		ty[j] = ofRandom(0, 1000);
	}
}

//--------------------------------------------------------------
void
ofApp::update()
{
	//Update sound engine
	ofSoundUpdate();

	//Get current spectrum with N bands
	float *val = ofSoundGetSpectrum(N);

	//Update the smoothed spectrum
	//by slowly decreasing the values and getting maximum value
	//to have slowly falling peaks in the spectrum
	for(int i = 0; i < N; ++i)
	{
		spectrum[i] *= 0.97;
		spectrum[i] = max(spectrum[i], val[i]);
	}

	//Update particles using spectrum values

	//Computing dt as time between the last and the current
	//calling of update()
	float time = ofGetElapsedTimef();
	float dt   = time - time0;
	dt         = ofClamp(dt, 0.0, 0.1);
	time0      = time;

	//Updating Rad and vel from the spectrum
	Rad = ofMap(spectrum[bandRad], 1, 3, 400, 800, true);
	Vel = ofMap(spectrum[bandVel], 0, 0.1, 0.05, 0.5);

	//Update particle position
	for(int j = 0; j < n; ++j)
	{
		tx[j] += Vel * dt; //move offset
		tx[j] += Vel * dt; //move offset

		//Calculate Perlin's noise in [-1,1] and
		//muliply on Rad
		p[j].x = ofSignedNoise(tx[j]) * Rad;
		p[j].y = ofSignedNoise(ty[j]) * Rad;
	}
}

//--------------------------------------------------------------
void
ofApp::draw()
{
	ofBackground(28, 28, 28); //Backgroud color

	//Draw background rect color for spectrum
	ofSetColor(28, 28, 28);
	ofFill();
	ofDrawRectangle(10, 600, N * 6, -100);

	//Draw spectrum
	ofSetColor(46, 49, 61);
	for(int i = 0; i < N; ++i)
	{
		//Draw bandRad and bandVel by black color
		//and any other by gray color
		if(i == bandRad || i == bandVel)
		{
			ofSetColor(161, 141, 175);
		}
		else
		{
			ofSetColor(198, 174, 215);
		}
		ofDrawRectangle(10 + i * 5, 600, 3, -spectrum[i] * 100);
	}

	//Draw cloud

	//Move centre of coordinate system to the screen center
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	//Draw cloud's points
	ofSetColor(181, 180, 201);
	ofFill();
	for(int i = 0; i < n; ++i)
	{
		ofDrawCircle(p[i], 2);
	}

	//Draw lines between near points
	float dist = 40; //Threshold parameter of distance
	for(int j = 0; j < n; ++j)
	{
		for(int k = 0; k < n; ++k)
		{
			if(ofDist(p[j].x, p[j].y, p[k].x, p[k].y) < dist)
			{
				ofDrawLine(p[j], p[k]);
			}
		}
	}

	//Restore coordinate system
	ofPopMatrix();
}

//--------------------------------------------------------------
void
ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void
ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void
ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void
ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void
ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void
ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void
ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void
ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void
ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void
ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void
ofApp::dragEvent(ofDragInfo dragInfo)
{
}
