#ifndef __ACTOR__
#define __ACTOR__

namespace cocos2d
{
	class Sprite3D;
}

class CPath;

class CActor : public cocos2d::Ref
{
public:
	CActor();
	~CActor();

	CREATE_FUNC(CActor);
public:
	virtual bool		init();
public:

	bool				update(float delta);
public:
	cocos2d::Sprite3D*	m_pAvatar;
	CPath*				m_pPath;
};

#endif
