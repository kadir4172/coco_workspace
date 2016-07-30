#include "GameScene.h"
#include <iostream>
#include "HelloWorldScene.h"

using namespace cocos2d;

USING_NS_CC;

Scene* GamePlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GamePlay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GamePlay::init(void){
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();



  auto closeItem = MenuItemImage::create(
                                             "CloseNormal.png",
                                             "CloseSelected.png",
                                             CC_CALLBACK_1(GamePlay::menuCloseCallback, this));

      closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getBoundingBox().size.width/2 ,
                                  origin.y + closeItem->getBoundingBox().size.height/2));

      // create menu, it's an autorelease object
      auto menu = Menu::create(closeItem, NULL);
      menu->setPosition(Vec2::ZERO);
      this->addChild(menu, 1);


      auto backtoMainItem = MenuItemImage::create(
                                                 "home_button.png",
                                                 "home_button.png",
                                                 CC_CALLBACK_1(GamePlay::menuGoHomeCallback, this));
      backtoMainItem->setScale(0.05);

      backtoMainItem->setPosition(Vec2(origin.x + backtoMainItem->getBoundingBox().size.width/2 ,
                                      origin.y + backtoMainItem->getBoundingBox().size.height/2));

          // create menu, it's an autorelease object
          auto menu2 = Menu::create(backtoMainItem, NULL);
          menu2->setPosition(Vec2::ZERO);
          this->addChild(menu2, 1);


      //fill the screen with gray color background
      auto background = DrawNode::create();
      background->drawSolidRect(origin, visibleSize, Color4F(0.6,0.6,0.6,1.0));
      this->addChild(background);

      //add ciko as a player
      _player = Sprite::create("Homer_Simpson2.jpg");
      _player->setScale(0.1);
      _player->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.5));
      this->addChild(_player);

      return true;
}


void GamePlay::menuCloseCallback(Ref* pSender)
{

    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GamePlay::menuGoHomeCallback(cocos2d::Ref* pSender){
   Director::getInstance( )->popScene( );
}
