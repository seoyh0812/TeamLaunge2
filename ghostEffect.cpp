#include "stdafx.h"
#include "ghostEffect.h"

HRESULT ghostEffect::init(S_BELONG belong, float x, float y)
{
	_ID = 6;
	_belong = belong;
	_x = x; _y = y;
	_rc = RectMakeCenter(_x, _y, 35, 33);
	_image = FINDIMG("��Ʈ��");
	_maxFrame = _image->getMaxFrameX();
	commonInit();
	_isOnce = true;
	_duration = 0; // isOnce�� �̰Ŷ� ������� ������ ���쵵�� �Ͽ���

	return S_OK;
}

void ghostEffect::release()
{
	SAFE_DELETE(_image);
}

void ghostEffect::update()
{
	commonUpdate();
}

void ghostEffect::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame, 0);
}
