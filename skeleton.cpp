#include "stdafx.h"
#include "skeleton.h"

skeleton::skeleton()
{
}

skeleton::~skeleton()
{
}

HRESULT skeleton::init(BELONG belong, float x, float y)
{
	_belong = ENEMY;
	_ID = 7;
	_x = x; _y = y;
	_speed = 2.0f;
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

void skeleton::release()
{
}

void skeleton::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x + 40, _y + 90, _width + 20, _height + 20);
}

void skeleton::render()
{

	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		//Rectangle(getMemDC(), _summonRc);
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top - 5, _frameDirection, _frame);
		break;
	case ATTACK:
		//Rectangle(getMemDC(), _summonRc);
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, _frameDirection, _frame);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		//Rectangle(getMemDC(), _summonRc); 
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8, _frame, 0);
		break;
	}

}

void skeleton::reRender()
{
}

void skeleton::setState(STATE state)
{
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
