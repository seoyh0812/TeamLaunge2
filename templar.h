#pragma once
#include "unit.h"
class templar :
	public unit
{
private:

public:
	templar();
	~templar();

	virtual HRESULT init(BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	virtual void setState(STATE state);
};

