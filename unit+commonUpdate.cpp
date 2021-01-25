#include "stdafx.h"
#include "unit.h"


void unit::commonUpdate()
{
	if (_HP <= 0 && _state != DEAD)
	{
		setState(DEAD);
	}

	if (_frameCount < 6) ++_frameCount; // 0.1ÃÊ¸¶´Ù
	else
	{
		_frameCount = 0;
		++_frame;
		if (_state != DEAD && _state != ATTACK && _frame > _maxFrame)
		{
			_frame = 0;
		}
	}

	switch (_state)
	{
	case IDLE:
		break;
	case WALK:

		break;
	case ATTACKWAIT:
		break;
	case ATTACK:
		if (_frame >= _maxFrame)
		{
			setState(ATTACKWAIT);
		}
		break;
	case DEAD:
		if (_frame >= _maxFrame)
		{
			_frame = _maxFrame;
			if (_deathDuration < 180) ++_deathDuration;
			else _erase = true;
		}
		break;
	}
}