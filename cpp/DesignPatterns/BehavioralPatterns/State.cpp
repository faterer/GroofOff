// State
// The State Pattern allows an object to alter its behavior when its internal state changes. 
// The object will appear as having changed its class.
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>

enum Input {
	DUCK_DOWN,
	STAND_UP,
	JUMP,
	DIVE
};

class Fighter;
class StandingState;
class JumpingState;
class DivingState;

class FighterState {
public:
	static std::shared_ptr<StandingState> standing;
	static std::shared_ptr<DivingState>
};