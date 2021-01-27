#include "stdafx.h"
#include "marine.h"

HRESULT marine::init(BELONG belong, float x, float y)
{
	_belong = belong;
	_ID = 2;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 60; // ���� 1�ʿ� �Ѵ� ġ�Բ�
	_damage = 5;
	_maxHP = 40;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = FINDIMG("�����⺻�Ķ�")->getFrameWidth();
	_height = FINDIMG("�����⺻�Ķ�")->getFrameHeight(); // �ϴ��� ���� �����س�������(�̹���ũ��)

	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������
	return S_OK;
}

void marine::release()
{
	SAFE_DELETE(_image);
}

void marine::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 200, _height + 200);
}

void marine::render()
{
	int left = _x - _image->getFrameWidth() / 2;
	int top = _y - _image->getFrameHeight() / 2;
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->frameRender(getMemDC(), left, top, _frame, _frameDirection);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->frameRender(getMemDC(), left, top, 0, _frameDirection);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), left, top, _frame, _frameDirection);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		_image->frameRender(getMemDC(), left, top, _frame, 0);
		break;
	}
}

void marine::setState(STATE state)
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
			_image = FINDIMG("�����̵��Ķ�");
			_maxFrame = _image->getMaxFrameX();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("���������Ķ�");
			_maxFrame = _image->getMaxFrameX();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("���������Ķ�");
			_maxFrame = _image->getMaxFrameX();
			break;
		case DEAD:
			_damage = 0; // ������ �Ⱦ��״� �׾����� ī��Ʈ�� ��Ȱ���Ѵ�(..)
			_image = FINDIMG("���������Ķ�");
			_maxFrame = _image->getMaxFrameX();
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("�����̵�����");
			_maxFrame = _image->getMaxFrameX();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("�������ݻ���");
			_maxFrame = _image->getMaxFrameX();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("�������ݻ���");
			_maxFrame = _image->getMaxFrameX();
			break;
		case DEAD:
			_damage = 0; // ������ �Ⱦ��״� �׾����� ī��Ʈ�� ��Ȱ���Ѵ�(..)
			_image = FINDIMG("������������");
			_maxFrame = _image->getMaxFrameX();
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}

}
