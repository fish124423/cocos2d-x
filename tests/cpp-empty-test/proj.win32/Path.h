#ifndef __PATH__
#define __PATH__

// 移动数据的基类: 片段
class CPath
{
public:
	CPath();
	virtual ~CPath() {}

	static bool					init();

	virtual void				debugDraw() {}

	bool						update(float dt);

	void						runSplineLogicEx(cocos2d::Vec3& vRef);
public:

	float						m_fTime;    // 总时间
	float						m_fTimeAcc;

	cocos2d::Vec3				m_vInitPos; // 起始点
	cocos2d::Vec3				m_vEnd;

	int							m_nPointCount;
	std::vector<cocos2d::Vec3>	m_PointCon;
};

#endif