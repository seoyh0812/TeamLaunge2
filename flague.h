#pragma once
#include "skillNEffect.h"

class flague :	public skillNEffect
{
private:

public:
	flague();
	~flague();

	virtual HRESULT init(S_BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

