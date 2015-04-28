#ifndef __PATH__
#define __PATH__

// �ƶ����ݵĻ���: Ƭ��
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

	float						m_fTime;    // ��ʱ��
	float						m_fTimeAcc;

	cocos2d::Vec3				m_vInitPos; // ��ʼ��
	cocos2d::Vec3				m_vEnd;

	int							m_nPointCount;
	std::vector<cocos2d::Vec3>	m_PointCon;
};

#endif