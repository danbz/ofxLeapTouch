#include "testApp.h"

bool bDrawGui = false;
bool bDrawDetails = true;

//--------------------------------------------------------------
void leapTouchExample::setup(){
//	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0);
	ofEnableAlphaBlending();

	// ----- leap
	leapTouch.setup(20,100);
	leapTouch.touchMode = TOUCH_VIA_ONE_FINGER;

	ofAddListener(ofEvents().touchDown,this,&leapTouchExample::touchDown);
	ofAddListener(ofEvents().touchUp,this,&leapTouchExample::touchUp);
	ofAddListener(ofEvents().touchMoved,this,&leapTouchExample::touchMoved);

	myTuioServer.start("127.0.0.1",3333);
	myTuioServer.setVerbose(true);
}

//--------------------------------------------------------------
void leapTouchExample::update(){
	leapTouch.update(true);
	myTuioServer.run();
}

//--------------------------------------------------------------
void leapTouchExample::draw(){

	ofSetColor(200);
	string isConnectedStr = leapTouch.getLeapMotionRef().isConnected() ? " " : " not ";
	string msg = "ofxLeapTouch - Example App\nLeap is"+isConnectedStr+"connected";
	msg += "\npress f: finger touch";
	msg += "\npress h: hand touch";
	msg += "\npress g: toggle gui";
	msg += "\npress d: toggle details";

	ofDrawBitmapString(msg, 20, 20);

	leapTouch.drawFingers(bDrawDetails);
	leapTouch.drawHands(bDrawDetails);

	if(bDrawGui){
		ofSetColor(255,255,255);
		leapTouch.gui.draw();
	}
}

void leapTouchExample::touchDown(ofTouchEventArgs & touch){
	cout << " cursor added: " + ofToString(touch.id)+
	" X: "+ofToString(touch.x)+
	" Y: "+ofToString(touch.y)
	<< endl;

	TuioCursor * cursor = myTuioServer.addCursor(touch.x*ofGetWidth(),touch.y*ofGetHeight());
	cursors.insert(CursorPair(touch.id,cursor));
}


void leapTouchExample::touchUp(ofTouchEventArgs & touch){
	cout << " cursor removed: " + ofToString(touch.id)+
	 " X: "+ofToString(touch.x)+
	 " Y: "+ofToString(touch.y)
	 << endl;

	myTuioServer.removeCursor(cursors.at(touch.id));
}

void leapTouchExample::touchMoved(ofTouchEventArgs & touch){
	cout << " cursor updated: " + ofToString(touch.id)+
	 " X: "+ofToString(touch.x)+
	 " Y: "+ofToString(touch.y)
	 << endl;

	myTuioServer.updateCursor(cursors.at(touch.id),touch.x*ofGetWidth(),touch.y*ofGetHeight());
}

//--------------------------------------------------------------
void leapTouchExample::keyPressed(int key){
	switch(key){
	case 'g':
		bDrawGui = !bDrawGui;
		break;
	case 'd':
		bDrawDetails = !bDrawDetails;
		break;
	case 'f':
		leapTouch.touchMode = TOUCH_VIA_ONE_FINGER;
		break;
	case 'h':
		leapTouch.touchMode = TOUCH_VIA_HANDS;
		break;
	}
}

//--------------------------------------------------------------
void leapTouchExample::keyReleased(int key){
}

void leapTouchExample::exit(){
	ofRemoveListener(ofEvents().touchDown,this,&leapTouchExample::touchDown);
	ofRemoveListener(ofEvents().touchUp,this,&leapTouchExample::touchUp);
	ofRemoveListener(ofEvents().touchMoved,this,&leapTouchExample::touchMoved);
}

//--------------------------------------------------------------
void leapTouchExample::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void leapTouchExample::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void leapTouchExample::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void leapTouchExample::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void leapTouchExample::windowResized(int w, int h){

}

//--------------------------------------------------------------
void leapTouchExample::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void leapTouchExample::dragEvent(ofDragInfo dragInfo){

}
