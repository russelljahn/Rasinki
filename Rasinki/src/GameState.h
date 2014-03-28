#ifndef __GAMESTATE_CLASS_H__
#define __GAMESTATE_CLASS_H__


/* 
	Abstract class to encapsulate the state of some object in the game, such as for AI, a character controller, ect.
	Should be given enough information to be able to tell which GameState follows it.
*/
class GameState {

	public:
		virtual void Update() = 0;
		virtual GameState* NextState() = 0;

};

#endif