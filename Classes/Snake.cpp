#include "Snake.h"
#include <string>
#include<iostream>
#include "windows.h"
using namespace std;
USING_NS_CC;

Snake::Snake(cocos2d::Layer *layer) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	boss = layer;
	cdDir = "rgt";
	prevDir = "rgt";
	cdCoords = Point(visibleSize.width / 2 + origin.x,
			   visibleSize.height / 2 + origin.y);
	length = 2;
	head = new Segment(layer, 
					  "head", 
					   cdCoords, 
					   cdDir);
	for (int i = 1; i <= length; i++) {
		body.push_back(new Segment(layer,
			"body",
			Point(cdCoords.x - i*(head->getSprite()->getBoundingBox().size.width),
				cdCoords.y
				),
			cdDir)
			);
	}

	OutputDebugString(L"right");
}

void Snake::grow(cocos2d::Layer *layer) {
	std::string dir = body.at(length-1)->getcdDir();
	cocos2d::Vec2 fatherPos = body.at(length-1)->getSprite()->getPosition();
	Segment *fatherSeg = body.at(length-1);
	Segment *newSeg;
	OutputDebugString(L" 1WAW1 ");
	length++;
	if (dir == "rgt") {
		OutputDebugString(L" 2LOL2 ");
		newSeg = new Segment(layer, "body",
		Point(fatherPos.x - (head->getSprite()->getBoundingBox().size.width),
		fatherPos.y),
		dir);
		body.push_back(newSeg);
		newSeg->setCCollec(fatherSeg->getCCollec());
		newSeg->setDCollec(fatherSeg->getDCollec());
		}
	else if (dir == "lft") {
		OutputDebugString(L" 2LOL2 ");
		newSeg = new Segment(layer,"body",
		Point(fatherPos.x + (head->getSprite()->getBoundingBox().size.width),
		fatherPos.y),
		dir);
		body.push_back(newSeg);
		newSeg->setCCollec(fatherSeg->getCCollec());
		newSeg->setDCollec(fatherSeg->getDCollec());
		}
	else if (dir == "up") {
		OutputDebugString(L" 2LOL2 ");
			newSeg = new Segment(layer, "body",
			Point(fatherPos.x,
			fatherPos.y - (head->getSprite()->getBoundingBox().size.height)),
			dir);
			body.push_back(newSeg);
			newSeg->setCCollec(fatherSeg->getCCollec());
			newSeg->setDCollec(fatherSeg->getDCollec());
		}
	else if (dir == "dwn") {
		OutputDebugString(L" 2LOL2 ");
		newSeg = new Segment(layer, "body",
		Point(fatherPos.x,
		fatherPos.y + (head->getSprite()->getBoundingBox().size.height)),
		dir);
		body.push_back(newSeg);
		newSeg->setCCollec(fatherSeg->getCCollec());
		newSeg->setDCollec(fatherSeg->getDCollec());
		}
	newSeg->checkCdCoord();
	newSeg->checkCdDirs();
	if (newSeg->getCCollec().empty() && !fatherSeg->getCCollec().empty()) {
		newSeg->setCCollec(fatherSeg->getCCollec());
		newSeg->setDCollec(fatherSeg->getDCollec());
		}
	std::ostringstream buffer;
	if (!newSeg->getDCollec().empty()) {
		buffer << " NewSeg Direction Top: " << newSeg->getDCollec().at(0) 
			<< ", FatherSeg Direction Top: "<< fatherSeg->getDCollec().at(0);
		newSeg->setCCollec(fatherSeg->getCCollec());
		newSeg->setDCollec(fatherSeg->getDCollec());
	}
	else buffer << " No commands for NewSeg ";
	std::wstring waw = s2ws(buffer.str());
	LPCWSTR result = waw.c_str();
		OutputDebugString(result);
}

std::wstring Snake::s2ws(const std::string& s)
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
int Snake::getLength(){
	return length;
}


void Snake::move() {
	head->move();/*
	for (int i = 0; i < body.size(); i++) {
		body.at(i)->move();
		int j = body.size() - i;
		if (j == 0) body.at(0)->setcdDir(head->getcdDir());
		else {
			  body.at(j)->setcdDir(body.at(j - 1)->getcdDir()); OutputDebugString(L" LOL ");
		}
	}*/


	
	for (std::vector<Segment*>::iterator it = body.begin(); it != body.end(); ++it) {
		(*it)->move();
		if (it == body.begin()) {
			(*it)->setprevDir((*it)->getcdDir());
			(*it)->setcdDir(head->getcdDir());
			(*it)->rotate((*it)->getcdDir(), (*it)->getprevDir());
		}
		else {
			auto temp = std::prev(it, 1);
			
			if (!(*it)->checkCdCoord()) {
				if ((*it)->getSprite()->getPosition() == (*it)->topCdCoord()) {
					(*it)->setprevDir((*it)->getcdDir());
					(*it)->setcdDir((*it)->topCdDir());
					(*it)->removeCdCoord();
					(*it)->removeCdDir();
					(*it)->rotate((*it)->getcdDir(), (*it)->getprevDir());
				}
			}
		} 
	}
	for (std::vector<Segment*>::iterator it = body.begin(); it != body.end();) {
		if ((*it)->checkIfOut()) {
			delete * it;
			it = body.erase(it);
			length--;
		}
		else {
			++it;
		}
	}
}

void Snake::changeDir(Segment *seg) {
	seg->setcdDir(cdDir);
}
void Snake::changeDir(EventKeyboard::KeyCode code) {
	if (head->getSprite()->getPosition() != cdCoords) {
		switch (code) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			if (cdDir == "up" || cdDir == "dwn") {
				prevDir = cdDir;
				cdDir = "lft";
				head->rotate(cdDir, prevDir);
				changeDir(head);
				cdCoords = head->getSprite()->getPosition();
				for (std::vector<Segment*>::iterator it = body.begin(); it != body.end(); ++it) {
					(*it)->addCdCoord(cdCoords);
					(*it)->addCdDir(cdDir);
				}
				OutputDebugString(L" LEFT ");
			}
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			if (cdDir == "up" || cdDir == "dwn") {
				prevDir = cdDir;
				cdDir = "rgt";
				head->rotate(cdDir, prevDir);
				changeDir(head);
				cdCoords = head->getSprite()->getPosition();
				for (std::vector<Segment*>::iterator it = body.begin(); it != body.end(); ++it) {
					(*it)->addCdCoord(cdCoords);
					(*it)->addCdDir(cdDir);
				}
				OutputDebugString(L" RIGHT ");
			}
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			if (cdDir == "lft" || cdDir == "rgt") {
				prevDir = cdDir;
				cdDir = "up";
				head->rotate(cdDir, prevDir);
				changeDir(head);
				cdCoords = head->getSprite()->getPosition();
				for (std::vector<Segment*>::iterator it = body.begin(); it != body.end(); ++it) {
					(*it)->addCdCoord(cdCoords);
					(*it)->addCdDir(cdDir);
				}
				OutputDebugString(L" UP ");
			}
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			if (cdDir == "lft" || cdDir == "rgt") {
				prevDir = cdDir;
				cdDir = "dwn";
				head->rotate(cdDir, prevDir);
				changeDir(head);
				cdCoords = head->getSprite()->getPosition();
				for (std::vector<Segment*>::iterator it = body.begin(); it != body.end(); ++it) {
					(*it)->addCdCoord(cdCoords);
					(*it)->addCdDir(cdDir);
				}
				OutputDebugString(L" DOWN ");
			}
			break;
		}

	}
}

boolean Snake::checkHeadHit(cocos2d::Sprite* chk) {
	cocos2d::Rect rect1 = chk->getBoundingBox();
	if (rect1.intersectsRect(head->getSprite()->getBoundingBox())) {
		return true;
	} return false;
}

boolean Snake::checkHeadSame(cocos2d::Sprite* chk) {
	if (chk->getPosition() == head->getSprite()->getPosition()) {
		return true;
	}
	return false;
}

boolean Snake::checkHit(cocos2d::Sprite* chk) {
	for (std::vector<Segment*>::iterator it = body.begin(); it != body.end(); ++it) {
		cocos2d::Rect rect1 = chk->getBoundingBox();
		if(chk->getPosition() == (*it)->getSprite()->getPosition()){
			return true;
		}
	} return false;
	
}
cocos2d::Sprite* Snake::getHead() {
	return head->getSprite();
};

std::vector<Segment*> Snake::getBody() {
	return body;
};

void Snake::ready(boolean rdy) {
	isReady = rdy;
}
boolean Snake::chkReady() {
	return isReady;
}

