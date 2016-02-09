#include "IntroScene.h"
#include "stdlib.h"
#include "HelloWorldScene.h"
#include "MenuScene.h"
USING_NS_CC;
using namespace std;

Scene* IntroScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = IntroScene::create();
	scene->addChild(layer);
	return scene;
}

bool IntroScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	playing = 1;
	audio->playEffect("hisssss.mp3", false);
	bg1 = CCSprite::create("thisis.png");
	bg1->setAnchorPoint(ccp(0, 0));
	bg1->setPosition(ccp(0, -bg1->getContentSize().height-200));
	bg1->setScale(2);
	// add the sprite as a child to this layer
	this->addChild(bg1, 20);
	bgduler = schedule_selector(IntroScene::scrollBg);
	this->schedule(bgduler, 0.02f);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		unschedule(bgduler);
		transitionWithOutDelay();
		playing = 0;
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);


	return true;
}

void IntroScene::scrollBg(float delta){
	bg1->setPosition(ccp(bg1->getPosition().x, bg1->getPosition().y + 1));
	//bg2->setPosition(ccp(bg2->getPosition().x, bg2->getPosition().y + 1));

	if (bg1->getPosition().y > -100) {
		unschedule(bgduler);
		if (playing == 1)
		this->schedule(schedule_selector(IntroScene::transitionWithDelay), 3.0);
	}
	/*if (bg2->getPosition().y < -bg2->boundingBox().size.height-20) {
		bg2->setPosition(ccp(bg2->getPosition().x, bg1->getPosition().y + bg1->boundingBox().size.height));
	}*/

}

void IntroScene::transitionWithDelay(float delta) {
	auto scene = MenuScene::createScene();
	auto director = Director::getInstance();
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->stopAllEffects(); 
	stopAllActions();
	unscheduleAllSelectors();
	removeFromParentAndCleanup(true);
	director->replaceScene(TransitionFade::create(1.5, scene, Color3B(255, 255, 255)));
}
void IntroScene::transitionWithOutDelay() {
	auto scene = MenuScene::createScene();
	auto director = Director::getInstance();
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->stopAllEffects(); 
	director->replaceScene(TransitionFade::create(1.5, scene, Color3B(255, 255, 255)));
}