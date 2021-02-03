#pragma once
#include "unit.h"
#include "diablo.h"
class skeleton :
	public unit
{

private:

	diablo* _diablo;

public:
	skeleton();
	~skeleton();

	virtual HRESULT init(BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	virtual void reRender();

	virtual void setState(STATE state);
};
