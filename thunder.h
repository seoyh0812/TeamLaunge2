#pragma once
#include "skillNEffect.h"

class thunder : public skillNEffect
{
private:

public:
	thunder();
	~thunder();

	virtual HRESULT init(S_BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

