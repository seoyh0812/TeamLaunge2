#include "stdafx.h"
#include "diablo.h"

diablo::diablo()
{
}

diablo::~diablo()
{
}
/*
��ƺ�� 
 - ���� �ð����� �ذ���� ��ȯ�Ѵ�
 - �ذ���� ���������� ��ƺ�� �ڽ� ������ �ٿ��Ÿ� ������ �Ѵ�
*/
HRESULT diablo::init(BELONG belong, float x, float y)
{
	_belong = ENEMY;
	_ID = 6;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 120; // ���� 1�ʿ� �Ѵ� ġ�Բ�
	_damage = 20;
	_maxHP = 300;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 21;
	_height = 22; // �ϴ��� ���� �����س�������(�̹���ũ��) 
	_count = 0;
	_used = false;

	//_isAttack = false;
	//_isAttackCount = 0;

	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������
	
	return S_OK;
}

void diablo::release()
{
}

void diablo::update()
{
	commonUpdate();
	_summonRc = RectMakeCenter(_x, _y, 300, 300);
	_rangeRc = RectMakeCenter(_x, _y, _width + 500, _height + 500);
}

void diablo::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		Rectangle(getMemDC(), _summonRc);
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top - 5, _frame, _frameDirection);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		Rectangle(getMemDC(), _summonRc);
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, 0, _frameDirection);
		break;
	case ATTACK:
		Rectangle(getMemDC(), _summonRc);
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, _frame, _frameDirection);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		Rectangle(getMemDC(), _summonRc); 
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8, _frame, 0);
		break;
	}
}

void diablo::setState(STATE state)
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
			_image = FINDIMG("��ƺ�� ����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("��ƺ�� �ȱ�");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACK:
			_image = FINDIMG("��ƺ�� ��ȯ");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("��ƺ�� ����");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}
}

void diablo::reRender()
{
}