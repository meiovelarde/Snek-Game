#pragma once
#include "cocos2d.h"
#include "Segment.h"
#include <string>
using namespace std;

class  Snake {

public:
	Snake(cocos2d::Layer *layer);
	void move();
	void changeDir(cocos2d::EventKeyboard::KeyCode);
	void changeDir(Segment *seg);
	boolean checkHit(cocos2d::Sprite *chk);
	boolean checkHeadHit(cocos2d::Sprite *chk);
	boolean checkHeadSame(cocos2d::Sprite *chk);
	cocos2d::Sprite* getHead();
	int getLength();
	std::vector<Segment*> getBody();
	void grow(cocos2d::Layer *layer);
	void ready(boolean rdy);
	boolean chkReady();
	std::wstring s2ws(const std::string& s);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Layer *boss;
	Segment *head;
	std::vector<Segment*> body;
	cocos2d::Size snakeSize;
	cocos2d::Vec2 cdCoords;
	int length;
	std::string cdDir;
	std::string prevDir;
	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;
	boolean isReady;
};