#pragma once
#include "unit.h"
class templar :
	public unit
{
private:
	RECT _afterImage;
	POINT _afterImagePt;
	int _afterImageFrame;
	int _afterImageFrameDirection;
	int _afterImageCount;

public:
	templar();
	~templar();

	virtual HRESULT init(BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	virtual void reRender();

	virtual void setState(STATE state);
};

