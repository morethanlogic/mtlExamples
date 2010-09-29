#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main() {
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1000, 510, OF_WINDOW);
	ofRunApp(new testApp());
}
