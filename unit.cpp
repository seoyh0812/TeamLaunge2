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
