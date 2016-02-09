#include "Food.h"
#include <string>
#include<iostream>
#include "windows.h"
#include "time.h"
using namespace std;
USING_NS_CC;

Food::Food() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

Food::~Food() {
	spr->removeFromParentAndCleanup(true);
}

void Food::SpawnFood(cocos2d::Layer *layer, Snake *snake) {
	spr = Sprite::create("rat.png");
	cocos2d::Vec2 originCoords = Point(visibleSize.width/2  + origin.x,
									   visibleSize.height/2 + origin.y);
	int random = CCRANDOM_0_1();
	int randomX = 1;
	int randomY = 1;
	if (random) {
		randomX = 1;
	}
	else randomX = -1;
	random = CCRANDOM_0_1();
	if (random) {
		randomY = 1;
	}
	else randomY = -1;

	randomX *= RandomHelper::random_int(1, 5);
	randomY *= RandomHelper::random_int(1, 5);
	foodPos = Point(originCoords.x - (randomX * 32),
					originCoords.y - (randomY * 32));
	spr->setPosition(foodPos);


	std::ostringstream buffer;
	if (snake->checkHit(spr) == true || snake->checkHeadHit(spr) == true ) {
		while (snake->checkHit(spr) || snake->checkHeadHit(spr) == true || spr->getPosition().x < 0 ||
			   spr->getPosition().x > visibleSize.width || spr->getPosition().y < 0 ||
			   spr->getPosition().y > visibleSize.height){
				randomX = rand() % 5;
				randomY = rand() % 5;
				buffer << " X: " << randomX
					<< ", Y: " << randomY;
	std::wstring waw = s2ws(buffer.str());
	LPCWSTR result = waw.c_str();
	OutputDebugString(result);
			
			foodPos = Point(originCoords.x - (randomX * 32),
							originCoords.y - (randomY * 32));
			spr->setPosition(foodPos);
		}
	}

	layer->addChild(spr, 20);
}

std::wstring Food::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

cocos2d::Sprite* Food::getSprite() {
	return spr;
}