#include "../include/includes.hpp"

using namespace geode::prelude;

class $modify(DailyLevelNodeHook, DailyLevelNode) {
    struct Fields {
        bool m_skip = false;
    };
#ifndef GEODE_IS_MACOS
    void onSkipLevel(CCObject * sender) {
        if (m_fields->m_skip) {
            DailyLevelNode::onSkipLevel(sender);
            return;
        }
        createQuickPopup(
            "Nuh uh",
            "You are <cr>NOT</c> skipping a daily level!",
            "Fine.",
            "PRETTY PLEASE!!!",
            [this, sender](auto, bool btn2) {
                if (btn2) {
                    m_fields->m_skip = true;
                    this->onSkipLevel(sender);
                }
            }
        );
    }
#endif
    bool init(GJGameLevel * level, DailyLevelPage * page, bool isNew) {
        if (!DailyLevelNode::init(level, page, isNew)) return false;
        if (!Mod::get()->getSettingValue<bool>("useDaily") || !atEvent) return true;
        if (this->getChildByID("crown-sprite") == nullptr)
            return true;
        auto dn = this->getChildByID("background");
        auto dnSize = dn->getContentSize();
        auto dnPos = dn->getPosition();
        auto dnZ = dn->getZOrder();
        dn->removeFromParent();
        auto newDn = CCScale9Sprite::create("GJ_square05.png");
        newDn->setContentSize(dnSize);
        newDn->setPosition(dnPos);
        newDn->setZOrder(dnZ);
        newDn->setID("background");
        this->addChild(newDn);

        auto pos = this->getChildByID("crown-sprite")->getPosition();
        auto z = this->getChildByID("crown-sprite")->getZOrder();
        this->removeChildByID("crown-sprite");
        CCNode* newNode = (CCNode*) CCSprite::createWithSpriteFrameName("gj_eventCrown_001.png");
        newNode->setPosition(pos);
        newNode->setZOrder(z);
        newNode->setID("crown-sprite");
        this->addChild(newNode);

        return true;
    }
};