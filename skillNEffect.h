#pragma once
#include "gameNode.h"

enum S_BELONG
{
	S_PLAYER,
	S_ENEMY
};

class skillNEffect :	public gameNode
{ // ���ָ��� �������� �����Ƿ� �ϴ� ����� ���� ������
protected:
	int _ID;
	S_BELONG _belong;
	float _x; float _y;
	RECT _rc;
	int _frame;
	int _maxFrame;
	int _frameCount;
	int _duration; // ���ӽð�
	bool _erase;

	image* _image;

public:
	skillNEffect();
	~skillNEffect();

	virtual HRESULT init(S_BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	inline void commonRelease() { SAFE_DELETE(_image); }
	void commonInit();
	void commonUpdate();

	int getID() { return _ID; }
	S_BELONG getBelong() { return _belong; }
	float& getX() { return _x; }
	float& getY() { return _y; }
	RECT getRect() { return _rc; }
	int getDuration() { return _duration; }
	bool getErase() { return _erase; }
};

