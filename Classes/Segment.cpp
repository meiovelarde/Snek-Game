#include "Segment.h"

USING_NS_CC;

Segment::Segment(cocos2d::Layer *layer, std::string type, Point startPos, std::string precedDir) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	Segment::type = type;
	if(type == "head"){
		spr = Sprite::create("1.png");
	} else if (type == "body"){
		switch (rand()%3) {
		case 0:
			spr = Sprite::create("2.png");
			break;
		case 1:
			spr = Sprite::create("3.png");	
			break;
		case 2:
			spr = Sprite::create("4.png");
			break;
		}
	};
	spr->setPosition(startPos);
	prevDir = precedDir;
	cdDir = precedDir;
	layer->addChild(spr, 100);

}

cocos2d::Sprite* Segment::getSprite(){
	return spr;
}

std::string Segment::getcdDir() {
	return cdDir;
}

std::string Segment::getprevDir() {
	return prevDir;
}

void Segment::setcdDir(std::string newDir) {
	cdDir = newDir;
}

void Segment::setprevDir(std::string newDir) {
	prevDir = newDir;
}

void Segment::addCdCoord(cocos2d::Vec2 cdCoord) {
	cCollec.push_back(cdCoord);
}

void Segment::removeCdCoord() {
	cCollec.erase(cCollec.begin());
}

cocos2d::Vec2 Segment::topCdCoord() {
	if (!cCollec.empty()) {
		return cCollec.at(0);
	}
	else { return NULL;
	}
}

boolean Segment::checkCdCoord() {
	return cCollec.empty();
}

void Segment::addCdDir(std::string cdDir) {
	dCollec.push_back(cdDir);
}

void Segment::removeCdDir() {
	dCollec.erase(dCollec.begin());
}

boolean Segment::checkCdDirs() {
	return dCollec.empty();
};

std::string Segment::topCdDir() {
	if (!dCollec.empty()) return dCollec.at(0);
	else return NULL;
}

std::vector<cocos2d::Vec2> Segment::getCCollec() {
	return cCollec;
}
std::vector<std::string> Segment::getDCollec() {
	return dCollec;
}
void Segment::setCCollec(std::vector<cocos2d::Vec2> newCol) {
	cCollec = newCol;
}

void Segment::setDCollec(std::vector<std::string> newCol) {
	dCollec = newCol;
}

boolean Segment::checkCollide(cocos2d::Sprite *check) {
	if (spr->getPosition() == check->getPosition())
	return true;
	else return false;
}	

void Segment::rotate(std::string cdDir, std::string prevDir) {
		if (cdDir == "rgt") {
			if (prevDir == "up") {
				auto rot90 = cocos2d::RotateBy::create(0, 90);
				spr->runAction(rot90);
			}
			else if (prevDir == "dwn") {
				auto rotn90 = cocos2d::RotateBy::create(0, -90);
				spr->runAction(rotn90);
			}
		}

		if (cdDir == "up") {
			if (prevDir == "rgt") {
				auto rot90 = cocos2d::RotateBy::create(0, -90);
				spr->runAction(rot90);
			}
			else if (prevDir == "lft") {
				auto rotn90 = cocos2d::RotateBy::create(0, 90);
				spr->runAction(rotn90);
			}
		}
		if (cdDir == "lft") {
			if (prevDir == "dwn") {
				auto rot90 = cocos2d::RotateBy::create(0, 90);
				spr->runAction(rot90);
			}
			else if (prevDir == "up") {
				auto rotn90 = cocos2d::RotateBy::create(0, -90);
				spr->runAction(rotn90);
			}
		}
		if (cdDir == "dwn") {
			if (prevDir == "lft") {
				auto rot90 = cocos2d::RotateBy::create(0, -90);
				spr->runAction(rot90);
			}
			else if (prevDir == "rgt") {
				auto rotn90 = cocos2d::RotateBy::create(0, 90);
				spr->runAction(rotn90);
			}
		}
	}

void Segment::move() {
	auto position = spr->getPosition();
		if (Segment::cdDir == "rgt") {
			position.x += spr->getContentSize().width;
		}

		if (Segment::cdDir == "up") {
			position.y += spr->getContentSize().width;
		}

		if (Segment::cdDir == "lft") {
			position.x -= spr->getContentSize().width;
		}

		if (Segment::cdDir == "dwn") {
			position.y -= spr->getContentSize().width;
		}

	spr->setPosition(position);
}

Segment::~Segment() {
	spr->removeFromParentAndCleanup(true);
};

boolean Segment::checkIfOut() {
	auto position = spr->getPosition();
	if (type == "body") {
		if (position.x > visibleSize.width + (spr->getContentSize().width / 2)) {
			return true;
		}

		if (position.x < 0 - (spr->getContentSize().width / 2)) {
			return true;
		}

		if (position.y > visibleSize.height + (spr->getContentSize().height / 2)) {
			return true;
		}

		if (position.y < 0 - (spr->getContentSize().height / 2)) {
			return true;
		}
		return false;
	}
}