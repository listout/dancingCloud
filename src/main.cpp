#include "ofApp.h"
#include "ofAppGlutWindow.h"
#include "ofMain.h"

//========================================================================
int
main(int argc, char *argv[])
{

	//vector for storing the string
	std::vector<string> args;
	if(argc == 2)
	{
		for(int i = 0; i < argc; ++i)
		{
			args.push_back(argv[i]);
		}
	}
	else
	{
		std::cout << "Wrong Argument format" << std::endl;
		return 1;
	}

	// create a window
	ofAppGlutWindow window;

	ofSetupOpenGL(800, 600, OF_WINDOW); // <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofApp *app     = new ofApp();
	app->arguments = args;
	ofRunApp(app);
}
