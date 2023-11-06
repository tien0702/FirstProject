#include "CharacterIdleState.h"
#include "KeyBoardInput.h"
#include "StateMachine/StateMachine.h"

void CharacterIdleState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	_owner->getModel()->runAction(animate);
}

std::string CharacterIdleState::updateState()
{
	auto keyboard = KeyboardInput::getInstance();

	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_SPACE))
	{
		return "attack";
	}

	if (keyboard->getDirection() != Vec2::ZERO)
	{
		return "run";
	}

	return "idle";
}

void CharacterIdleState::exitState()
{
	State::exitState();
}
