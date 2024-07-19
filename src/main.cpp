#include "../include/includes.hpp"

using namespace geode::prelude;

bool atEvent = false;

class $modify(MyCreatorLayer, CreatorLayer) {
    void onEventLevel(CCObject * sender) {
        atEvent = true;
        DailyLevelPage::create(GJTimedLevelType::Event)->show();
        return;
    }
    bool init() {
        if (!CreatorLayer::init()) return false;
        CCNode* eventButtonNode = this->getChildByID("creator-buttons-menu")->getChildByID("event-button");
        auto newSprite = CCSprite::createWithSpriteFrameName("GJ_eventBtn_001.png");
        newSprite->setScale(static_cast<CCNode*>(eventButtonNode->getChildren()->objectAtIndex(0))->getScale());
        static_cast<CCMenuItemSpriteExtra*>(eventButtonNode)->setSprite(newSprite);
        return true;
    }
};

