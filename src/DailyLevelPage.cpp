#include "../include/includes.hpp"

using namespace geode::prelude;

void retexture(CCNode* pageNode, const char* ID, const char* spriteName) {
    auto pos = pageNode->getChildByID(ID)->getPosition();
    pageNode->removeChildByID(ID);
    CCNode* newNode = (CCNode*) CCSprite::createWithSpriteFrameName(spriteName);
    newNode->setPosition(pos);
    newNode->setID(ID);
    pageNode->addChild(newNode);
}

class $modify(MyDailyLevelPage, DailyLevelPage) {
    struct Fields {
        int randLabel;
    };
    void dailyStatusFinished(GJTimedLevelType type) {
        if (type == GJTimedLevelType::Event && !Mod::get()->getSettingValue<bool>("useDaily"))
            type = GJTimedLevelType::Daily;

        DailyLevelPage::dailyStatusFinished(type);
    }
    
    gd::string getDailyTimeString(int e) {
        auto ret = DailyLevelPage::getDailyTimeString(e);

        if (!atEvent || !Mod::get()->getSettingValue<bool>("useDaily")) return ret;

        switch (m_fields->randLabel) { // original labels :)
            case 0: ret = "New event level in ... ?"; break;
            case 1: ret = "Events are pretty random"; break;
            case 2: ret = "Next event in random hours from now"; break;
            case 3: ret = "When is the next event?"; break;
            case 4: ret = "NEW EVENT! .... soon"; break;
            case 5: ret = "Why did I program this..."; break;
            case 6: ret = "I believe in you"; break;
            case 7: ret = "You can do it"; break;
            case 8: ret = "Next one is a banger"; break;
            case 9: ret = "This is fun"; break;
            case 10: ret = "I can't find anything"; break;
            case 11: ret = "Why is this a thing"; break;
            case 12: ret = "Do or do not. There is no try"; break;
            case 13: ret = "The cake is a lie"; break;
            case 14: ret = "Challenge accepted"; break;
            case 15: ret = "I wonder what's next"; break;
            case 16: ret = "Welcome to the event"; break;
            case 17: ret = "Jump cube, jump"; break;
            case 18: ret = "No event for you"; break;
            case 19: ret = "This looks interesting"; break;
            default: break;
        }
        return ret;
    }
    bool init(GJTimedLevelType type) {
        if (type != GJTimedLevelType::Event) atEvent = false;
        if (!Mod::get()->getSettingValue<bool>("useDaily")) {
            DailyLevelPage::init(type); // Init Event Page and stop if daily is not wanted
            return true;
        }
        srand(time(NULL));
        m_fields->randLabel = rand() % 20;
        // Store type for future checks
        bool onEvent = type == GJTimedLevelType::Event;
        if (onEvent) { // Change to Daily Level page
            type = GJTimedLevelType::Daily;
        }
        else atEvent = false;
        if (!DailyLevelPage::init(type)) // Show Daily Layer
            return false;

        if (!onEvent) // Don't retexture
            return true;

        // Start retexturing
        CCNode* pageNode = static_cast<CCNode*>(this->getChildren()->objectAtIndex(0));
        // Title
        retexture(pageNode, "title-sprite", "eventLevelLabel_001.png");
        // Background
        CCNode* bg = pageNode->getChildByID("background");
        auto bgSize = bg->getContentSize();
        auto bgPos = bg->getPosition();
        auto bgZ = bg->getZOrder();
        bg->removeFromParent();
        ccColor3B color;
        color.r = 200;
        color.g = 50;
        color.b = 255;
        CCScale9Sprite* newBg = CCScale9Sprite::create("GJ_square04.png");
        newBg->setContentSize(bgSize);
        newBg->setPosition(bgPos);
        newBg->setZOrder(bgZ);
        newBg->setColor(color);
        newBg->setID("background");
        pageNode->addChild(newBg);
        auto timeLabel = pageNode->getChildByID("time-label");
        if (timeLabel != nullptr) {
            timeLabel->setScale(0.4);
            timeLabel->setAnchorPoint(CCPoint(0.5, 0.5));
            timeLabel->setPositionX(bgPos.x);
        }
        return true;
    }
};