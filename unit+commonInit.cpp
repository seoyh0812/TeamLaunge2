#include "stdafx.h"
#include "unit.h"

void unit::commonInit()
{
	// int
	_frameCount = _frame = _delay = _frameDirection = _deathDuration = 0;
	_target = -1; // 타겟이 없는 상태면 -1
	// float
	_angle = 0.f;
	// bool
	_attackReady = _erase = false;
	setState(WALK);

	_rc = RectMakeCenter(_x, _y, _width, _height);
	_destX = _x; _destY = _y;
	_HP = _maxHP;
}


void unit::commonRelease()
{
	SAFE_DELETE(_image);
}