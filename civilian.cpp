#include "stdafx.h"
#include "civilian.h"

civilian::civilian()
{
}

civilian::~civilian()
{
}

HRESULT civilian::init(BELONG belong, float x, float y)
{
	_belong = belong;
	_ID = 3;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 60; // ���� 1�ʿ� �ѹ� ��ų����
	_damage = 0;
	_maxHP = 40;
	_attackIndex = 1; // 1�� �ε����� �ɶ� ��ų����
	_width = 12;
	_height = 20; // �ϴ��� ���� �����س�������(�̹���ũ��)
	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������

	return S_OK;
}

void civilian::release()
{
}

void civilian::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 6, _height + 6);

}

void civilian::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top-5, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top-5, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top-5, _frameDirection, 0);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		_image->frameRender(getMemDC(), _rc.left - 24, _rc.top - 9, _frame, 0);
		break;
	}
}

void civilian::reRender()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 5, _rc.top-5, _frameDirection, _frame, 150);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->alphaFrameRender(getMemDC(), _rc.left - 5, _rc.top-5, _frameDirection, 0, 150);
		break;
	case ATTACK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 5, _rc.top-5, _frameDirection, 0, 150);
		break;
	}
}

void civilian::setState(STATE state)
{
	if (_state == state) return; // �����ɷ� ���ѰŸ� ó�� ������
	_frame = 0;
	_frameCount = 0;
	_state = state;
	if (_belong == PLAYER)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("�ù��Ķ�");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("�ù��Ķ�");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("�ù��Ķ�");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_damage = 0; // ������ �Ⱦ��״� �׾����� ī��Ʈ�� ��Ȱ���Ѵ�(..)
			_image = FINDIMG("�ù�����");
			_maxFrame = _image->getMaxFrameX();
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("�ù�����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("�ù�����");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("�ù�����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("�ù�����");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}
}
