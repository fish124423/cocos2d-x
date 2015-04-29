#include "HelloWorldScene.h"
#include "AppMacros.h"

#include "Actor.h"
#include "Path.h"

#include "Random.h"

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

#define TO_ROUND(x) ((x)/180.0f * 3.14159265358)

const float l_fHalfFov = 30;
const float l_fHalfFovRadian = TO_ROUND(l_fHalfFov);

float l_fH2WRatio = 1.f;

const int	l_nMaxDepth = 5000;
const int	l_nNear = 10;
const int   l_nFar = l_nMaxDepth + l_nNear;

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
		pPlane->setPosition3D(Vec3(0, 0, -100));
		pPlane->runAction(RepeatForever::create(RotateBy::create(3, 360)));

		//add to scene
		//addChild(pPlane);

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

			l_fH2WRatio = visibleSize.width / visibleSize.height;

			m_pCamera = Camera::createPerspective(60, l_fH2WRatio, l_nNear, l_nFar);
			m_pCamera->setPosition3D(Vec3(0.f, 0.f, 0.f));
			m_pCamera->setCameraFlag(CameraFlag::USER1);

			m_Actors.resize(100);
			for (int i = 0; i < 100; ++i)
			{
				auto pActor = CActor::create();
				addChild(pActor->m_pAvatar, i, i);
				m_Actors[i] = pActor;

				pActor->retain();

				ResetActor(pActor);
			}

			addChild(m_pCamera);
			setCameraMask(static_cast<unsigned>(CameraFlag::USER1));
		}

		scheduleUpdate();
    
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

void HelloWorld::update(float dt)
{
	for (auto pActor: m_Actors)
	{
		if (!pActor->update(dt))
		{
			ResetActor(pActor);
		}
	}
}

void HelloWorld::ResetActor(CActor* pActor)
{
	auto pPath = pActor->m_pPath;

	pPath->m_fTime = 10.f + Random::sharedRandom()->randInt(0, 20);

	int nSteps = 6;
	int nStepLen = l_nMaxDepth / nSteps;

	pPath->m_fTimeAcc = 0.f;
	pPath->m_PointCon.resize(nSteps + 1);

	for (int i = 0; i <nSteps; ++i)
	{
		int nCurDist = l_nFar - nStepLen * i;
		pPath->m_PointCon[i] = getRandPos(nCurDist);
	}

	pPath->m_PointCon[nSteps] = getRandPos(l_nNear);
}

cocos2d::Vec3 HelloWorld::getRandPos(int nDist)
{
	if (nDist < l_nNear)
		nDist = l_nNear;

	if (nDist > l_nFar)
		nDist = l_nFar;

	int nHalfH = std::tanf(l_fHalfFovRadian) * nDist;

	int nHalfW = nHalfH * l_fH2WRatio;

	int nW = Random::sharedRandom()->randInt(-nHalfW, nHalfW);
	int nH = Random::sharedRandom()->randInt(-nHalfH, nHalfH);

	return Vec3(nW, nH, -nDist);
}
