#pragma once
#include "unit.h"
class civilian :
	public unit
{

private:

public:
	civilian();
	~civilian();

	virtual HRESULT init(BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	virtual void reRender();

	virtual void setState(STATE state);
};

