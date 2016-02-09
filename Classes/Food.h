#pragma once
#include "cocos2d.h"
#include "snake.h"
#include <string>
using namespace std;

class  Food {

public:
	Food();
	~Food();
	void SpawnFood(cocos2d::Layer *layer, Snake *snake);
	cocos2d::Sprite* Food::getSprite();
	std::wstring s2ws(const std::string& s);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *spr;
	cocos2d::Vec2 foodPos;
};