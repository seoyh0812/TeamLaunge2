#include "stdafx.h"
#include "bone.h"

bone::bone()
{
}

bone::~bone()
{
}

HRESULT bone::init(BELONG belong, float x, float y)
{
	_belong = ENEMY;
	_ID = 7;
	_x = x; _y = y;
	_speed = 4.0f;
	_maxDelay = 120; // ���� 1�ʿ� �Ѵ� ġ�Բ�
	_damage = 20;
	_maxHP = 30;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 21;
	_height = 22; // �ϴ��� ���� �����س�������(�̹���ũ��) 
	_count = 0;
	_used = false;

	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������

	return S_OK;
}

void bone::release()
{
}

void bone::update()
{
}

void bone::render()
{
	switch (_state)
	{
	case WALK:
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top - 5, _frame, _frameDirection);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, 0, _frameDirection);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, _frame, _frameDirection);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8, _frame, 0);
		break;
	}
}

void bone::reRender()
{
}

void bone::setState(STATE state)
{
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("�ذ񺴻� ����");
			_maxFrame = _image->getMaxFrameX();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("�ذ񺴻� �ȱ�");
			_maxFrame = _image->getMaxFrameX();
			break;
		case ATTACK:
			_image = FINDIMG("�ذ񺴻� ����");
			_maxFrame = _image->getMaxFrameX();
			break;
		case DEAD:
			_damage = 0; // ������ �Ⱦ��״� �׾����� ī��Ʈ�� ��Ȱ���Ѵ�(..)
			_image = FINDIMG("�ذ񺴻� ����");
			_maxFrame = _image->getMaxFrameX();
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}
}
