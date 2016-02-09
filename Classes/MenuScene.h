#pragma once

#include "cocos2d.h"
#include "Snake.h"
#include "Food.h"
#include "SimpleAudioEngine.h"  
class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void scrollBg(float);
	void menuCommand(cocos2d::EventKeyboard::KeyCode);
	void sel();
	void startGame(float);
	void exitGame(float);
	CREATE_FUNC(MenuScene);

private:
	cocos2d::Sprite* bg1;
	cocos2d::Sprite* bg2;
	cocos2d::Sprite* bg3;
	cocos2d::Sprite* bg4;
	cocos2d::Sprite* snek;
	cocos2d::Label* startLabel;
	cocos2d::Label* exitLabel;
	cocos2d::SEL_SCHEDULE bgduler;
	int selected;
	boolean selecting;
};