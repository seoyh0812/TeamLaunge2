#pragma once
#include "unit.h"
class zergling :
	public unit
{
private:
	int _healCount;

public:
	zergling();
	~zergling();

	virtual HRESULT init(BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	virtual void reRender();

	virtual void setState(STATE state);
};

