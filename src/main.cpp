#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* p0, GameObject* p1) {
        PlayLayer::destroyPlayer(p0, p1);

        if (this->getCurrentPercent() == 16) {
            // kabum trigger
            FMODAudioEngine::sharedEngine()->playEffect("kabum.mp3");

            // the cat pfp overlay
            auto cat = CCSprite::create("cat.png");
            auto size = CCDirector::get()->getWinSize();
            cat->setPosition({size.width / 2, size.height / 2});
            this->addChild(cat, 100); 
        }
    }
};