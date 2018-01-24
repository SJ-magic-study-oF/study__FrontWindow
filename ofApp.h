/************************************************************
■I need to keep my app in front of all other windows on the screen, but not steal focus from other windows.
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
					}
				}
			#endif
			}
			
		then inside your testApp::setup call
			ofEnableFloating(true);
			
		and that's about it.
		
		to disable call:
			ofEnableFloating(false);


■Xcode WindowLevelの順序
	http://www.rinpa.com/blog/archives/2005/03/xcode_windowlev.html
	
	contents
		矢印の上にある物ほど上に表示される 
		矢印がない物はアクティブになった物の方が上に表示された
		
		kCGMaximumWindowLevel 
		↑ 
		kCGCursorWindowLevel 
		↑ 
		kCGScreenSaverWindowLevel 
		↑ 
		kCGDraggingWindowLevel 
		↑ 
		kCGHelpWindowLevel 
		kCGOverlayWindowLevel 
		↑ 
		kCGPopUpMenuWindowLevel 
		kCGBackstopMenuLevel 
		↑ 
		kCGStatusWindowLevel 
		↑ 
		kCGMainMenuWindowLevel 
		↑ 
		kCGDockWindowLevel 
		↑ 
		kCGUtilityWindowLevel 
		↑ 
		kCGModalPanelWindowLevel 
		↑ 
		kCGFloatingWindowLevel 
		kCGTornOffMenuWindowLevel 
		↑ 
		kCGNormalWindowLevel 
		kCGBaseWindowLevel 
		kCGAssistiveTechHighWindowLevel 
		↑ 
		kCGDesktopIconWindowLevel 
		↑ 
		kCGDesktopWindowLevel 
		↑ 
		kCGMinimumWindowLevel


■foreground window on unity
	Conclusion
		macでは不可らしい。
		伊勢丹での経験から、通知系を全てoffにし、最後にFullScreenで起動すれば大丈夫なので、大概の場合はこれで行こう。
		万全を期すなら、unityはwindowsで実装するか、
			unity -syphon-> oF
		として、ここで示す例に従いoF appのwindowを最前面にすることで対応.
		
	
	windowsならできるらしい
		https://stackoverflow.com/questions/29092145/any-way-to-bring-unity3d-to-the-foreground
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
