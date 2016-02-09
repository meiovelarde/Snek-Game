#pragma once
#include "cocos2d.h"

class  Segment
{
public:
	Segment(cocos2d::Layer *layer, std::string type, cocos2d::Point precedPos, std::string precedDir);
	~Segment();
	boolean checkIfOut();
	cocos2d::Sprite *getSprite();
	void move();
	void Segment::rotate(std::string cdDir, std::string prevDir);
	std::string getcdDir();
	std::string getprevDir();
	void Segment::setcdDir(std::string newDir);
	void Segment::setprevDir(std::string newDir);
	void Segment::addCdCoord(cocos2d::Vec2 cdCoord);
	void Segment::removeCdCoord();
	boolean Segment::checkCdCoord();
	cocos2d::Vec2 Segment::topCdCoord();
	void Segment::addCdDir(std::string cdDir);
	void Segment::removeCdDir();
	boolean Segment::checkCdDirs();
	std::string Segment::topCdDir();
	boolean Segment::checkCollide(cocos2d::Sprite *check);
	std::vector<cocos2d::Vec2> getCCollec();
	std::vector<std::string> getDCollec();
	void setCCollec(std::vector<cocos2d::Vec2> newCol);
	void setDCollec(std::vector<std::string> newCol);
	/*void setPosition(cocos2d:: Vec2 position);*/
private:
	cocos2d::Sprite *spr;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	std::string type;
	std::vector<cocos2d::Vec2> cCollec;
	std::vector<std::string> dCollec;
	cocos2d::Point precedPosit;
	std::string cdDir;
	std::string prevDir;
};
