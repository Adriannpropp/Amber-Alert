#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/fmod/fmod.hpp>

using namespace geode::prelude;

class $modify(AmberPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* p0, GameObject* p1) {
        PlayLayer::destroyPlayer(p0, p1);

        if (static_cast<int>(this->getCurrentPercent()) == 16) {
            auto resDir = Mod::get()->getResourcesDir();
            auto audioPath = (resDir / "kabum.mp3").string();
            
            FMOD::System* system = FMODAudioEngine::sharedEngine()->m_system;
            FMOD::Sound* sound = nullptr;
            FMOD::Channel* channel = nullptr;
            
            system->createSound(
                audioPath.c_str(),
                FMOD_DEFAULT,
                nullptr,
                &sound
            );
            
            if (sound) {
                system->playSound(sound, nullptr, false, &channel);
                
                if (channel) {
                    channel->setVolume(0.5f);
                    
                    unsigned long long dspClock;
                    int rate;
                    system->getSoftwareFormat(&rate, nullptr, nullptr);
                    channel->getDSPClock(nullptr, &dspClock);
                    
                    channel->addFadePoint(dspClock + (rate * 1.5), 0.5f);
                    channel->addFadePoint(dspClock + (rate * 2.5), 0.0f);
                    channel->setDelay(0, dspClock + (rate * 2.5), true);
                }
            }

            if (Mod::get()->getSettingValue<bool>("show-cat")) {
                auto cat = CCSprite::create((resDir / "cat.png").string().c_str());
                if (cat) {
                    auto size = CCDirector::get()->getWinSize();
                    cat->setPosition({size.width / 2, size.height / 2});
                    cat->setOpacity(0); 
                    cat->setZOrder(9999); 
                    this->addChild(cat);

                    cat->runAction(CCSequence::create(
                        CCFadeIn::create(0.1f),
                        CCDelayTime::create(1.7f),
                        CCFadeOut::create(0.1f),
                        CCCallFunc::create(cat, callfunc_selector(CCNode::removeFromParent)),
                        nullptr
                    ));
                }
            }
        }
    }
};