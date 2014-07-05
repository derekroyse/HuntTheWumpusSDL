#ifndef GLOBALS_H
#define GLOBALS_H

#define P(x) std::cout << #x << "value is " << x << std::endl;

//keys, start at 1; command 0 is IDLE

enum {
	IDLE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DEBUG_MODE,
	UP_CAMERA,
	DOWN_CAMERA,
	LEFT_CAMERA,
	RIGHT_CAMERA,
	FLIPPED_LEFT,
	FLIPPED_RIGHT,
	NOT_FLIPPED_RIGHT,
	NOT_FLIPPED_LEFT,
	QUIT = 20
};
//add stuff that might interact with other props here
namespace G {

}

#endif