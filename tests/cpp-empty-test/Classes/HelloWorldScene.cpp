#include "HelloWorldScene.h"
#include "AppMacros.h"

#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"

USING_NS_CC;

Scene* HelloWorld::scene()
{
    auto scene = Scene::create();
    
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	{
		auto szWin = Director::getInstance()->getWinSize();

		auto pPlane = Sprite3D::create("Sprite3DTest/boss1.obj");

		pPlane->setScale(4.f);
		pPlane->setTexture("Sprite3DTest/boss.png");
		pPlane->setPosition3D(Vec3(0, 0, 0));
		pPlane->runAction(RepeatForever::create(RotateBy::create(3, 360)));

		//add to scene
		addChild(pPlane);

		// Make sprite1 touchable
		auto listener1 = EventListenerTouchOneByOne::create();
		listener1->setSwallowTouches(true);

		listener1->onTouchBegan = [](Touch* touch, Event* event)
		{
			auto target = static_cast<Sprite3D*>(event->getCurrentTarget());

			Rect rect = target->getBoundingBox();
			if (rect.containsPoint(touch->getLocation()))
			{
				log("sprite3d began... x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
				target->setOpacity(100);
				return true;
			}
			return false;
		};

		listener1->onTouchMoved = [](Touch* touch, Event* event)
		{
			auto target = static_cast<Sprite3D*>(event->getCurrentTarget());
			target->setPosition(target->getPosition() + touch->getDelta());
		};

		listener1->onTouchEnded = [=](Touch* touch, Event* event)
		{
			auto target = static_cast<Sprite3D*>(event->getCurrentTarget());
			log("sprite3d onTouchesEnded.. ");
			target->setOpacity(255);
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, pPlane);

		{
			FileUtils::getInstance()->addSearchPath("Particle3D/materials");
			FileUtils::getInstance()->addSearchPath("Particle3D/scripts");
			FileUtils::getInstance()->addSearchPath("Sprite3DTest");

			auto rootps = PUParticleSystem3D::create("flareShield.pu");

			rootps->startParticleSystem();
			pPlane->addChild(rootps, 0, 0);
		}
	}

		{
			Size visibleSize = Director::getInstance()->getVisibleSize();
			auto _camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 10, 5000);
			_camera->setPosition3D(Vec3(0.f, 0.f, 500.f));
			_camera->setCameraFlag(CameraFlag::USER1);

			addChild(_camera);
			setCameraMask(static_cast<unsigned>(CameraFlag::USER1));
		}
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
