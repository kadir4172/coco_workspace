#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;
Sprite* sprite = nullptr;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    /////////////////////////////
    // 2.5 add a start game button menu item


    auto startgameItem = MenuItemImage::create(
                                           "HelloWorld.png",
                                           "HelloWorld.png",
                                           CC_CALLBACK_1(HelloWorld::startgame_Callback, this));

    startgameItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + startgameItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu_start = Menu::create(startgameItem, NULL);
    menu_start->setPosition(Vec2::ZERO);
    this->addChild(menu_start, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Merhaba Ciko", "fonts/Marker Felt.ttf", 35);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height/2));

    // add the label as a child to this layer
    this->addChild(label, 1);





    // add "HelloWorld" splash screen"

    sprite = Sprite::create("HelloWorld.png");
    sprite->setScale(0.5);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*2/4 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{

    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    

}

void HelloWorld::startgame_Callback(Ref* pSender){
  GamePlay::set_init_counter(7,10,3);
  auto scene = GamePlay::createScene();
  if(sprite != nullptr){
	 // sprite->setScale(5);
  }

  //schedule(schedule_selector(GamePlay::count_to_zero), 1);
  Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(255,0,255)));

}
