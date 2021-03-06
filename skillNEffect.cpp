#include "stdafx.h"
#include "skillNEffect.h"

skillNEffect::skillNEffect()
{
}

skillNEffect::~skillNEffect()
{
}

HRESULT skillNEffect::init(S_BELONG belong, float x, float y)
{
	return S_OK;
}

void skillNEffect::release()
{
}

void skillNEffect::update()
{
}

void skillNEffect::render()
{
}

void skillNEffect::commonInit()
{
	_frame = _frameCount = _erase = _isOnce = 0;
}

void skillNEffect::commonUpdate()
{
	if (_frameCount < 6) ++_frameCount; // 0.1�ʸ���
	else
	{
		_frameCount = 0;
		++_frame;
		if (_frame > _maxFrame)
		{
			if (_isOnce)
			{
				_erase = true;
			}
			else
			{
				_frame = 0;
			}			
		}
	}
	
	if (_duration > 0) --_duration;
	else if (!_isOnce && _duration <= 0)
	{
		_erase = true;
	}
}
