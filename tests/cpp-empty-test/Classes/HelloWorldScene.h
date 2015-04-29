#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class CActor;

class HelloWorld : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* sender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void         update(float dt);

	void				ResetActor(CActor*);
	cocos2d::Vec3		getRandPos(int nDist);
public:
	std::vector<CActor*>	m_Actors;
	cocos2d::Camera*		m_pCamera;
};

#endif // __HELLOWORLD_SCENE_H__
