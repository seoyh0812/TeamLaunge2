#include "stdafx.h"
#include "unit.h"

unit::unit()
{
}

unit::~unit()
{
}

HRESULT unit::init(BELONG belong, float x, float y)
{
	return S_OK;
}

void unit::release()
{
}

void unit::update()
{
}

void unit::render()
{
}

void unit::progressBarRender()
{
	if (_state == DEAD || _ID == 20) return; // ����� ���α׷���
	// ü�¹� �����ϴ°�
	if (_HP > _maxHP) _HP = _maxHP;
	FINDIMG("ü�¹ٵ�")->resizedRender(getMemDC(), _rc.left - 5, _rc.top - 10, _width + 10, 6);
	if (_HP / _maxHP > 0.5f)
	{
		FINDIMG("�ʷ���")->resizedRender(getMemDC(), _rc.left - 5, _rc.top - 10, (_width + 10) *_HP / _maxHP, 6);
	}
	else if (_HP / _maxHP > 0.3f)
	{
		FINDIMG("�����")->resizedRender(getMemDC(), _rc.left - 5, _rc.top - 10, (_width + 10) *_HP / _maxHP, 6);
	}
	else
	{
		FINDIMG("������")->resizedRender(getMemDC(), _rc.left - 5, _rc.top - 10, (_width + 10) *_HP / _maxHP, 6);
	}
	FINDIMG("�����̹�")->resizedRender(getMemDC(), _rc.left - 3, _rc.top - 4, (_width + 6)* (1.f - _delay / _maxDelay), 3);
}

void unit::reRender()
{
}

void unit::moveCancel()
{
	if (_state == WALK)
	{
		_x -= _speed * cosf(_angle);
		_y += _speed * sinf(_angle);
	}
}


void unit::RMC()
{
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void unit::setDest(float destX, float destY)
{ // ������ �������ָ鼭 �ޱ۵� �ٲ��ְ�
	// �ޱۿ� ���� �����ӵ� �ٲ��ִ� �Լ�
	_destX = destX;
	_destY = destY;
	_angle = getAngle(_x, _y, _destX, _destY);
	if (_angle < 0) _angle += PI2;
	_frameDirection = 10 - (int)((_angle + PI8) / PI4);
	_frameDirection %= 8;
}

void unit::setAngle(float angle)
{
	_angle = angle;
	if (_angle < 0) _angle += PI2;
	_frameDirection = 10 - (int)((_angle + PI8) / PI4);
	_frameDirection %= 8;
}
