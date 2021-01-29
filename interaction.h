#pragma once
#include "gameNode.h"
#include "stageManager.h"
#include "unitManager.h"
#include "skillNEffectManager.h"


class interaction :	public gameNode
{
private:
	stageManager*			_sm;
	unitManager*			_um;
	skillNEffectManager*	_se;

public:
	interaction();
	~interaction();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void chanhoInit();		void chanhoUpdate();	void chanhoRender();
	void deokhoInit();		void deokhoUpdate();	void deokhoRender();
	void hyunjeongInit();	void hyunjeongUpdate();	void hyunjeongRender();
	void yoonghoInit();		void yoonghoUpdate();	void yoonghoRender();
	void younghanInit();	void younghanUpdate();	void younghanRender();
	
	void smLink(stageManager* sm) { _sm = sm; }
	void umLink(unitManager* um) { _um = um; }
	void seLink(skillNEffectManager* se) { _se = se; }

	inline POINT picking(long x, long y);
};

