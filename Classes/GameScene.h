#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"


class GamePlay : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();


    virtual bool init(void);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuGoHomeCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);

private:
    cocos2d::Sprite* _player;

};



#endif
