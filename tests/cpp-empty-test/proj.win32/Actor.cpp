#include "cocos2d.h"

#include "3d/CCSprite3D.h"
#include "Path.h"

#include "Actor.h"

// For "Actor Child Tag Type"
#define e3DSprite 0

CActor::CActor():
m_pAvatar(nullptr),
m_pPath(nullptr)
{
}

CActor::~CActor()
{
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

void CActor::setPath(CPath* path)
{
	m_pPath = path;
}

void CActor::update(float delta)
{
	if (m_pPath)
	{
		cocos2d::Vec3 vPos;

		m_pPath->runSplineLogicEx(vPos);
		m_pAvatar->setPosition3D(vPos);
	}

	return;
}
