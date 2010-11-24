#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main() {
    ofAppGlutWindow window;
    window.setGlutDisplayString("rgb alpha double samples depth");
    ofSetupOpenGL(&window, 400, 400, OF_WINDOW);
	ofRunApp(new testApp());
}
