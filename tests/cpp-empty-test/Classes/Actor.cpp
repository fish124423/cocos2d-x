#include "cocos2d.h"

#include "3d/CCSprite3D.h"
#include "Path.h"

#include "Actor.h"

// For "Actor Child Tag Type"
#define e3DSprite 0

CActor::CActor():
m_pAvatar(nullptr)
{
	m_pPath = new CPath;
	m_pPath->init();
}

CActor::~CActor()
{
	delete m_pPath;
}

bool CActor::init()
{
	m_pAvatar = cocos2d::Sprite3D::create("Sprite3DTest/boss1.obj");
	if (nullptr != m_pAvatar)
	{
		m_pAvatar->setScale(4.f);
		m_pAvatar->setTexture("Sprite3DTest/boss.png");
		return true;
	}

	return false;
}

bool CActor::update(float delta)
{
	bool bDead = false;

	if (m_pPath)
	{
		static cocos2d::Vec3 l_vMRU;
		cocos2d::Vec3 vPos;

		bDead = m_pPath->update(delta);
		m_pPath->runSplineLogicEx(vPos);
		m_pAvatar->setPosition3D(vPos);

		l_vMRU = vPos;
	}

	return bDead;
}