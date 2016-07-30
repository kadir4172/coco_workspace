#include "GameScene.h"
#include <iostream>
#include "HelloWorldScene.h"
#include <string>

using namespace cocos2d;

USING_NS_CC;

enum class PhysicsCategory {
  None = 0,
  Monster = (1 << 0),    // 1
  Projectile = (1 << 1), // 2
  All = PhysicsCategory::Monster | PhysicsCategory::Projectile // 3
};

Scene* GamePlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    auto layer = GamePlay::create();

    // add layer as a child to scene
    scene->addChild(layer,1,88);

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


          auto label = Label::createWithTTF("Kadirden Baskasi Gelirse Oldur", "fonts/Marker Felt.ttf", 30);

              // position the label on the center of the screen
              label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                      origin.y + visibleSize.height*3/4 - label->getContentSize().height/2));

              // add the label as a child to this layer
              this->addChild(label, 1,47);


              auto label2 = Label::createWithTTF("Hazir ol ! \n     " + std::to_string(this->init_counter), "fonts/Marker Felt.ttf", 50);

                     // position the label on the center of the screen
                     label2->setPosition(Vec2(origin.x + visibleSize.width/2,
                                             origin.y + visibleSize.height/2 - label2->getContentSize().height/2));

                     // add the label as a child to this layer
                     this->addChild(label2, 1, 46);

      //fill the screen with gray color background
      auto background = DrawNode::create();
      background->drawSolidRect(origin, visibleSize, Color4F(0.6,0.6,0.6,1.0));
      this->addChild(background);

      //add ciko as a player
      _player = Sprite::create("Homer_Simpson2.jpg");
      _player->setScale(0.1);
      _player->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.5));
      this->addChild(_player);

      srand((unsigned int)time(nullptr));
      this->schedule(schedule_selector(GamePlay::count_to_zero), 1);

      //get touch actions and register event listener
      auto eventListener = EventListenerTouchOneByOne::create();
      eventListener->onTouchBegan = CC_CALLBACK_2(GamePlay::onTouchBegan, this);
      this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);


      //detect collisions between monsters and bombs
      auto contactListener = EventListenerPhysicsContact::create();
      contactListener->onContactBegin = CC_CALLBACK_1(GamePlay::onContactBegan, this);
      this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
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
   this->unschedule(schedule_selector(GamePlay::count_to_zero));
   this->unschedule(schedule_selector(GamePlay::addMonster));

   Director::getInstance( )->popScene( );
}

void GamePlay::count_to_zero(float dt){
  auto tmp_label = dynamic_cast<Label*>(this->getChildByTag(46));

  if(this->init_counter > 0){
      this->init_counter -= 1;
         if(tmp_label != nullptr){
     	  tmp_label->setString("Hazir ol ! \n     " + std::to_string(this->init_counter));
         }
  }
  else{
      this->unschedule(schedule_selector(GamePlay::count_to_zero));
      if(tmp_label != nullptr){
        this->removeChild(tmp_label, true);
      }
      tmp_label = dynamic_cast<Label*>(this->getChildByTag(47));
      if(tmp_label != nullptr){
              this->removeChild(tmp_label, true);
      }
      this->schedule(schedule_selector(GamePlay::addMonster), 3);
  }

}

void GamePlay::addMonster(float dt){

    auto monster = Sprite::create("Johnny-Depp-Cartoon-Photo.png");
    monster->setScale(0.1);
    auto monsterSize = monster->getBoundingBox().size;
    auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width * 2.5 , monsterSize.height * 2.5),
                                              PhysicsMaterial(0.1f, 1.0f, 0.0f));
    // 2
    physicsBody->setDynamic(true);
    // 3
    physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
    physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
    physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);

    monster->setPhysicsBody(physicsBody);


    // 1
    auto monsterContentSize = monster->getBoundingBox().size;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int minY = monsterContentSize.height/2;
    int maxY = visibleSize.height - monsterContentSize.height/2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;

    monster->setPosition(Vec2(visibleSize.width + monsterContentSize.width/2 + origin.x, randomY));
    this->addChild(monster);

    // 2
    int minDuration = 4.0;
    int maxDuration = 8.0;
    int rangeDuration = maxDuration - minDuration;
    int randomDuration = (rand() % rangeDuration) + minDuration;

    // 3
    auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, randomY));
    auto actionRemove = RemoveSelf::create();
    monster->runAction(Sequence::create(actionMove,actionRemove, nullptr));



}

bool GamePlay::onTouchBegan(Touch* touch, Event* unused_event) {
  // 1  - Just an example for how to get the  _player object
  //auto node = unused_event->getCurrentTarget();

  // 2
  Vec2 touchLocation = touch->getLocation();
  Vec2 offset = touchLocation - _player->getPosition();

  // 3
  if (offset.x < 0) {
    return true;
  }

  // 4
  auto projectile = Sprite::create("Bomb.png");
  projectile->setScale(0.2);
  projectile->setPosition(this->_player->getPosition());

  auto projectileSize = projectile->getBoundingBox().size;
  auto physicsBody = PhysicsBody::createCircle(projectileSize.width *2);
  physicsBody->setDynamic(true);
  physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
  physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
  physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
  projectile->setPhysicsBody(physicsBody);

  this->addChild(projectile);

  // 5
  offset.normalize();
  auto shootAmount = offset * 1000;

  // 6
  auto realDest = shootAmount + projectile->getPosition();

  // 7
  auto actionMove = MoveTo::create(2.0f, realDest);
  auto actionRemove = RemoveSelf::create();
  projectile->runAction(Sequence::create(actionMove,actionRemove, nullptr));

  return true;
}

void GamePlay::set_init_counter(int value){
  GamePlay::init_counter = value;
}


bool GamePlay::onContactBegan(PhysicsContact &contact) {
  auto nodeA = contact.getShapeA()->getBody()->getNode();
  auto nodeB = contact.getShapeB()->getBody()->getNode();
  auto bang = Sprite::create("bang.png");
  bang->setScale(0.03);
  bang->setPosition(nodeA->getPosition());
  this->addChild(bang);

  auto actionMove = MoveTo::create(1, nodeA->getPosition());
  auto actionRemove = RemoveSelf::create();
  bang->runAction(Sequence::create(actionMove,actionRemove, nullptr));


  nodeA->removeFromParent();
  nodeB->removeFromParent();
  return true;
}
int GamePlay::init_counter = 5;
