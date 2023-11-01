#include "State.h"
#include "StateMachine.h"

void State::enterState(Entity* owner)
{
	this->_owner = owner;
}

std::string State::updateState()
{
	return std::string();
}

void State::exitState()
{
	_owner->getModel()->stopAllActions();
	//_owner->getModel()->stopActionByTag(StateMachine::AnimationTag);
}

