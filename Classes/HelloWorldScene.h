#pragma once

#include "cocos2d.h"
#include "Snake.h"
#include "Food.h"
#include "SimpleAudioEngine.h"  
class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void move(float) ;
	CREATE_FUNC(HelloWorld);
	void restart(float);

private:
	Snake *snake;
	float gamespeed;
	cocos2d::SEL_SCHEDULE snekduler;
	cocos2d::SEL_SCHEDULE restarting;
	Food *food;
	cocos2d::Sprite* wall;
	cocos2d::Sprite* wall2;
	cocos2d::Sprite* wall3;
	cocos2d::Sprite* wall4;

};