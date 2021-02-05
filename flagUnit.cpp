#include "stdafx.h"
#include "flagUnit.h"

HRESULT flagUnit::init(BELONG belong, float x, float y)
{
	_belong = belong;
	_ID = 20; // ���� �Ȱ�ġ��
	_x = x; _y = y;
	_speed = 0.f;
	_maxDelay = 1000;
	_damage = 0;
	_maxHP = 100;
	_attackIndex = 5; // 2�� �ε����� �ɶ� ��������
	_width = 32;
	_height = 16; // �ϴ��� ���� �����س�������(�̹���ũ��)
	_rc = RectMakeCenter(_x, _y, _width, _height);

	_frameCount = _frame = _delay = _frameDirection = _tileNum = 0;
	_target = -1; // ���� ���¸� -1
	// float
	if (_belong == PLAYER) setAngle(0.f);
	else setAngle(PI);
	// bool
	_attackReady = _erase = _active = _return = _stuck = false;
	_state = ATTACKWAIT;

	setDest(_x, _y);
	_HP = _maxHP;
	_focusRc = RectMakeCenter(0, 0, 0, 0);
	_rangeRc = RectMakeCenter(0, 0, 0, 0);

	return S_OK;
}

void flagUnit::release()
{
}

void flagUnit::update()
{
	if (_HP <= 0)
	{
		_target = -1;
		_erase = true;
	}
}

void flagUnit::render() {}

void flagUnit::reRender(){
	FINDIMG("ü�¹ٵ�")->resizedRender(getMemDC(), _rc.left - 15, _rc.top - 130, _width + 30, 6);
	if (_HP / _maxHP > 0.5f)
	{
		FINDIMG("�ʷ���")->resizedRender(getMemDC(), _rc.left - 15, _rc.top - 130, (_width + 30) *_HP / _maxHP, 6);
	}
	else if (_HP / _maxHP > 0.3f)
	{
		FINDIMG("�����")->resizedRender(getMemDC(), _rc.left - 15, _rc.top - 130, (_width + 30) *_HP / _maxHP, 6);
	}
	else
	{
		FINDIMG("������")->resizedRender(getMemDC(), _rc.left - 15, _rc.top - 130, (_width + 30) *_HP / _maxHP, 6);
	}
}

void flagUnit::setState(STATE state){}
