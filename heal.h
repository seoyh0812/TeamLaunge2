#pragma once
#include "skillNEffect.h"

class heal : public skillNEffect
{
private:

public:
	heal() {};
	~heal() {};

	virtual HRESULT init(S_BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

