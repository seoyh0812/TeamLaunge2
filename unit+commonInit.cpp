#include "stdafx.h"
#include "unit.h"

void unit::commonInit()
{
	// int
	_frameCount = _frame = _delay = _frameDirection = _deathDuration = 0;
	_target = _tileNum = -1; // ���� ���¸� -1
	// float
	_angle = 0.f;
	// bool
	_attackReady = _erase = false;
	_state = ATTACKWAIT; // �̰� ���ϸ� ó���� WALK�� ���ϴ� �̹����� ���־ ����	
	setState(WALK);		// �½�����Ʈ���� ��ũ�� �ٲ�� ���������..

	_rc = RectMakeCenter(_x, _y, _width, _height);
	_destX = _x; _destY = _y;
	_HP = _maxHP;
}