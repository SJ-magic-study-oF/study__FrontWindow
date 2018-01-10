/************************************************************
I need to keep my app in front of all other windows on the screen, but not steal focus from other windows.
	https://forum.openframeworks.cc/t/floating-app-without-focus-osx/15030
	
	contents
		go inside your
			ofSystemUtils.h (/of_v0.9.0_osx_release/libs/openFrameworks/utils)
			
		and declare our function:
			void ofEnableFloating(bool isEnabled);
			
		then go to
			ofSystemUtils.cpp
			
		and write our implementation:
			
			void ofEnableFloating(bool isEnabled){
			#ifdef TARGET_OSX
				NSDictionary *info = [[NSBundle mainBundle] infoDictionary];
				NSString *bundleName = [NSString stringWithFormat:@"%@", [info objectForKey:@"CFBundleExecutable"]];
				string standardAppName = [bundleName UTF8String];
				for(NSWindow * myOFwindow in [NSApp windows]){
					if([myOFwindow.miniwindowTitle isEqual: [NSString stringWithCString:standardAppName.c_str()]]){
						continue;
					}else{
						if(isEnabled){
							[myOFwindow setLevel:kCGFloatingWindowLevel];
						}else{
							[myOFwindow setLevel:NSNormalWindowLevel];
						}
			s		}
				}
			#endif
			}
			
		then inside your testApp::setup call
			ofEnableFloating(true);
			
		and that's about it.
		
		to disable call:
			ofEnableFloating(false);


Xcode WindowLevelの順序
	http://www.rinpa.com/blog/archives/2005/03/xcode_windowlev.html
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		WIDTH = 300,
		HEIGHT = 300,
	};
	
	/****************************************
	****************************************/
	bool b_FullScreen;
	
public:
	/****************************************
	****************************************/
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
