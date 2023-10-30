#include "HelloWorldScene.h"
#include "Utilities/AnimationUtils.h"
#include "DemoSingleton.h"
#include "KeyBoardInput.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	ui::ScrollView* scrollView = ui::ScrollView::create();
	scrollView->setContentSize(Size(200, 200));
	scrollView->setBackGroundImage("bg.jpg", ui::Widget::TextureResType::LOCAL);
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setScrollBarEnabled(false);
	scrollView->setBounceEnabled(true);


	//this->addChild(scrollView, 3);
	_character = Character::create(new EntityInfo(1, "ice-cube"));

	_moveSpeed = 100.0f;
	this->addChild(_character, 1);
	this->scheduleUpdate();

	/*TMXTiledMap* map = TMXTiledMap::create("Maps/map1.tmx");

	this->addChild(map);

	TMXObjectGroup* objGroup = map->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("CharacterSpawnPoint");

	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();
	_character->setPosition(position);

	this->getDefaultCamera()->setPosition(position);*/


	_gameMap = GameMap::create("/Maps/Demo/map-demo.tmx");

	TMXObjectGroup* objGroup = _gameMap->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("CharacterSpawnPoint");

	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();

	_character->setPosition(position);

	this->addChild(_gameMap);
	return true;
}

void HelloWorld::update(float dt)
{
	Vec2 direction = KeyboardInput::getInstance()->getDirection();

	Vec2 nextPosition = _character->getPosition() + direction * _moveSpeed * dt;
	if (_gameMap->getMetaAtPos(nextPosition) == GameMap::MetaRed) {
		nextPosition = _character->getPosition() - direction * _moveSpeed * dt;
	}

	_character->setPosition(nextPosition);

	Camera* defaultCam = this->getDefaultCamera();
	defaultCam->setPosition(_character->getPosition());
}

void HelloWorld::onEnter()
{
	Scene::onEnter();
	if (KeyboardInput::getInstance()->getParent() != nullptr)
		KeyboardInput::getInstance()->removeFromParent();

	this->addChild(KeyboardInput::getInstance());
}
