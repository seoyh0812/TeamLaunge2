#include "stdafx.h"
#include "unit.h"

void unit::commonInit()
{
	// int
	_frameCount = _frame = _delay = _frameDirection = _tileNum = _stuck = 0;
	_deathDuration = 180; // �������� ��ü���ӽð�. �⺻���� 3���ε� ���ֿ����� ���ϼ�����(���÷�����)
	_target = -1; // ���� ���¸� -1
	// float
	if (_belong == PLAYER) setAngle(0.f);
	else setAngle(PI);
	// bool
	_attackReady = _erase = _active = _return = false;
	_state = ATTACKWAIT; // �̰� ���ϸ� ó���� WALK�� ���ϴ� �̹����� ���־ ����	
	setState(WALK);		// �½�����Ʈ���� ��ũ�� �ٲ�� ���������..

	_rc = RectMakeCenter(_x, _y, _width, _height);
	setDest(_x, _y);
	_HP = _maxHP;
}