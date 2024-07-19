#include <Geode/Geode.hpp>
#include <Geode/cocos/actions/CCActionEase.h>
#include <Geode/cocos/actions/CCActionInterval.h>
#include <Geode/cocos/cocoa/CCGeometry.h>
#include <Geode/modify/MenuLayer.hpp>
#include <sstream>

using namespace geode::prelude;

// THIS IS MY VERY FIRST MOD, MADE JUST TO TEST

const char* getTextureName() {
    int randnum = rand() % 12;
    std::ostringstream iconlol;

    switch (randnum) {
        case 11:
            iconlol << "diffIcon_auto_btn_001.png";
            break;
        case 10:
            iconlol << "diffIcon_" << randnum << "_btn_001.png";
            break;
        default:
            iconlol << "diffIcon_0" << randnum << "_btn_001.png";
            break;
    }
    return iconlol.str().c_str();
}

class $modify(funnyshit, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto edsprite = cocos2d::CCSprite::createWithSpriteFrameName("diffIcon_10_btn_001.png");

        auto myButton = CCMenuItemSpriteExtra::create(edsprite, this, menu_selector(funnyshit::whenNewButtonClickedlol));

        auto menu = this->getChildByID("bottom-menu");
        menu->addChild(myButton);
        menu->setZOrder(3);

        myButton->setID("my-button"_spr);
        menu->updateLayout();

        return true;
    }

    void whenNewButtonClickedlol(CCObject * sender) {
        // FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show();
        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        auto node = static_cast<CCNode*>(sender);
        CCPoint point;
        if (node->getPositionX() < -30 && node->getPositionY() >= 50)
            point = CCPoint(node->getPositionX(), node->getPositionY() - 25);
        else if (node->getPositionY() >= 260 && node->getPositionX() >= -30)
            point = CCPoint(node->getPositionX() - 25, node->getPositionY());
        else if (node->getPositionX() <= 260 && node->getPositionY() < 50)
            point = CCPoint(node->getPositionX() + 25, node->getPositionY());
        else
            point = CCPoint(node->getPositionX(), node->getPositionY() + 25);

        auto move = CCMoveTo::create(0.5, point);
        auto easedMove = CCEaseInOut::create(move, 2);
        button->setSprite(CCSprite::createWithSpriteFrameName(getTextureName()));
        node->runAction(easedMove);
    }
};