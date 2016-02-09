#pragma once

#include "cocos2d.h"
#include "Snake.h"
#include "Food.h"
#include "SimpleAudioEngine.h"  
class IntroScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void scrollBg(float);
	void skip();
	void transitionWithDelay(float delta);
	void transitionWithOutDelay();
	CREATE_FUNC(IntroScene);

private:
	cocos2d::Sprite* bg1;
	cocos2d::Sprite* bg2;
	cocos2d::Label* startLabel;
	cocos2d::SEL_SCHEDULE bgduler;
	int playing;
};