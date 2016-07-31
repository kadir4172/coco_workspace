#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"


class GamePlay : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();


    virtual bool init(void);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref*);
    void menuGoHomeCallback(cocos2d::Ref*);
    void count_to_zero(float);
    void addMonster(float);
    static void set_init_counter(int, int, int);
    bool onContactBegan(cocos2d::PhysicsContact &contact);
    bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);

private:
    cocos2d::Sprite* _player;
    static int init_counter;
    static int monster_counter;
    static int live_counter;
    static int kiss_counter;

};



#endif
