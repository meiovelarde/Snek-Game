#include "MenuScene.h"
#include "stdlib.h"
#include "HelloWorldScene.h"
USING_NS_CC;
using namespace std;

Scene* MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("ddune.mp3", true);
	selecting = true;
	bg1 = CCSprite::create("bg.png");
	bg1->setAnchorPoint(ccp(0, 0));
	bg1->setPosition(ccp(0, 0));

	bg2 = CCSprite::create("bg.png");
	bg2->setAnchorPoint(ccp(0, 0));
	bg2->setPosition(ccp(bg1->boundingBox().size.width - 1, 0));

	bg3 = CCSprite::create("bg2.png");
	bg3->setAnchorPoint(ccp(0, 0));
	bg3->setPosition(ccp(0,0));

	bg4 = CCSprite::create("bg2.png");
	bg4->setAnchorPoint(ccp(0, 0));
	bg4->setPosition(ccp(bg3->boundingBox().size.width - 1, 0));

	auto snekLabel = Label::createWithSystemFont("Snek", "WerdnasReturn", 128);
	snekLabel->setPosition(Vec2(visibleSize.width/2 + snekLabel->getContentSize().width*.030,
							visibleSize.height/2 + snekLabel->getContentSize().height));
	snekLabel->setColor(ccc3(60,38,15));

	auto snekLabel2 = Label::createWithSystemFont("Snek", "WerdnasReturn", 128);
	snekLabel2->setPosition(Vec2((visibleSize.width / 2 + snekLabel->getContentSize().width*.065),
								 visibleSize.height / 2 + (snekLabel->getContentSize().height*1.025)));
	snekLabel2->setColor(ccc3(255, 242, 30));

	startLabel = Label::createWithSystemFont("Start", "Minecraft", 32);
	startLabel->setColor(ccc3(132, 174, 174));
	startLabel->setPosition(Vec2((visibleSize.width / 2 + 16), visibleSize.height / 3.5));
	

	exitLabel = Label::createWithSystemFont("Exit", "Minecraft", 32);
	exitLabel->setColor(ccc3(60, 38, 15));
	exitLabel->setPosition(Vec2((visibleSize.width / 2 + 16), visibleSize.height / 3.5 - (startLabel->getContentSize().height * 1.5)));

	snek = CCSprite::create("sel.png");
	snek->setPosition(Vec2((visibleSize.width / 2 + 16)- startLabel->getContentSize().width/2 - snek->getContentSize().width
						   , visibleSize.height / 3.5 + snek->getContentSize().height/6));

	// add the sprite as a child to this layer
	this->addChild(snekLabel, 35);
	this->addChild(snekLabel2, 37);
	this->addChild(startLabel, 36);
	this->addChild(exitLabel, 36);
	this->addChild(bg1, 20);
	this->addChild(bg2, 20);
	this->addChild(bg3, 30);
	this->addChild(bg4, 30);
	this->addChild(snek, 35);
	bgduler = schedule_selector(MenuScene::scrollBg);
	this->schedule(bgduler, 0.05f);

	selected = 0;
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		 if(selecting) menuCommand(keyCode); 
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);


	return true;
}

void MenuScene::menuCommand(EventKeyboard::KeyCode code) {
	switch (code) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		if (selected) {
			sel();
		}
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		if (!selected) {
			sel();
		}
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		selecting = false;
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect("menu3.wav", false);
		unschedule(bgduler);
		snek->setTexture("sel2.png");
		if (selected) {
			this->schedule(schedule_selector(MenuScene::exitGame), 1.5);
		}
		else {
			this->schedule(schedule_selector(MenuScene::startGame), 1.5);
		}
		break;
	}
}

void MenuScene::sel() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("menu2.wav", false);

	if (selected) {
		selected = 0;
		startLabel->setColor(ccc3(132, 174, 174));
		exitLabel->setColor(ccc3(0, 0, 0));
		snek->setPosition(Vec2((visibleSize.width / 2 + 16) - startLabel->getContentSize().width / 2 - snek->getContentSize().width
			, visibleSize.height / 3.5 + snek->getContentSize().height / 6));

	}
	else {
		exitLabel->setColor(ccc3(132, 174, 174));
		startLabel->setColor(ccc3(0, 0, 0));
		selected = 1;
		snek->setPosition(Vec2((visibleSize.width / 2 + 16) - startLabel->getContentSize().width / 2 - snek->getContentSize().width
			, visibleSize.height / 3.5 + snek->getContentSize().height / 6 - (startLabel->getContentSize().height * 1.5)));

	}
}

void MenuScene::startGame(float dt) {
	auto director = Director::getInstance();
	auto scene2 = HelloWorld::createScene();
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
	director->replaceScene(scene2);

}

void MenuScene::exitGame(float dt) {
	auto director = Director::getInstance();
	director->end();
}


void MenuScene::scrollBg(float delta){
	bg1->setPosition(ccp(bg1->getPosition().x - .5, bg1->getPosition().y));
	bg2->setPosition(ccp(bg2->getPosition().x - .5, bg2->getPosition().y));

	if (bg1->getPosition().x < -bg1->boundingBox().size.width-20) {
		bg1->setPosition(ccp(bg2->getPosition().x + bg2->boundingBox().size.width, bg1->getPosition().y));
	}
	if (bg2->getPosition().x < -bg2->boundingBox().size.width-20) {
		bg2->setPosition(ccp(bg1->getPosition().x + bg1->boundingBox().size.width, bg2->getPosition().y));
	}

	bg3->setPosition(ccp(bg3->getPosition().x - 1.5, bg3->getPosition().y));
	bg4->setPosition(ccp(bg4->getPosition().x - 1.5, bg4->getPosition().y));

	if (bg3->getPosition().x < -bg3->boundingBox().size.width - 20) {
		bg3->setPosition(ccp(bg4->getPosition().x + bg4->boundingBox().size.width, bg4->getPosition().y));
	}
	if (bg4->getPosition().x < -bg4->boundingBox().size.width - 20) {
		bg4->setPosition(ccp(bg3->getPosition().x + bg3->boundingBox().size.width, bg4->getPosition().y));
	}
}