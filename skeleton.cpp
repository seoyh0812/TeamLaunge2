#include "stdafx.h"
#include "skeleton.h"
#include "unit.h"
#include "stdafx.h"
#include "ghost.h"


skeleton::skeleton()
{
}


skeleton::~skeleton()
{
}

HRESULT skeleton::init(BELONG belong, float x, float y)
{ // �� ��ġ�� �ʰ� �̰� �����ؼ� ���� �ٲ���°� ��õ
	_belong = ENEMY;
	_ID = 7;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 120; // ���� 1�ʿ� �Ѵ� ġ�Բ�
	_damage = 6;
	_maxHP = 10;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 21;
	_height = 22; // �ϴ��� ���� �����س�������(�̹���ũ��)
	_count = 0;
	_used = false;

	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������

	return S_OK;
}

void skeleton::release()
{
	SAFE_DELETE(_image);
}

void skeleton::update()
{
	commonUpdate();
	_focusRc = RectMakeCenter(_x, _y, _width + 30, _height + 30);
	_rangeRc = RectMakeCenter(_x, _y, _width + 20, _height + 20);
}

void skeleton::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, 0);
		break;
	case ATTACK:
		Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8, _frame, 0);
		break;
	}

	// if (KEYMANAGER->isToggleKey(VK_F1)) Rectangle(getMemDC(), _rc);
}

void skeleton::reRender()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame, 150);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, 0, 150);
		break;
	case ATTACK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame, 150);
		break;
	}
}

void skeleton::setState(STATE state)
{ // �̰ſ� ���ؼ� ������ּ���
	if (_state == state) return; // �����ɷ� ���ѰŸ� ó�� ������
	_frame = 0;
	_frameCount = 0;
	_state = state;
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("�ذ񺴻� ����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("�ذ񺴻� ����");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("�ذ񺴻� ����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("�ذ񺴻� ����");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}

}