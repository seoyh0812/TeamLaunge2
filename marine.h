#pragma once
#include "unit.h"
class marine :
	public unit
{

public:
	virtual HRESULT init(BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	virtual void setState(STATE state);
};

