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
	_speed = 0.9f;
	_maxDelay = 120; // ���� 1�ʿ� �Ѵ� ġ�Բ�
	_damage = 20;
	_maxHP = 1000;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 22;
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
	_summonRc = RectMakeCenter(_x + 40, _y + 90, 180, 180);
	_rangeRc = RectMakeCenter(_x + 40, _y + 90, _width + 400, _height + 400);
}

void diablo::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top - 5, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, _frameDirection, _frame);
		break;
	case ATTACK:
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 7, _rc.top - 10, _frameDirection, _frame);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8,  _frame , 0);
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
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("��ƺ�� ��ȯ");
			_maxFrame = _image->getMaxFrameY();
			PLAYSND("��ƺ�ΰ���");
			break;
		case DEAD:
			PLAYSND("��ƺ�λ��");
			_damage = 0; // ������ �Ⱦ��״� �׾����� ī��Ʈ�� ��Ȱ���Ѵ�(..)
			_image = FINDIMG("��ƺ�� ����");
			_maxFrame = _image->getMaxFrameX();
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}
}

void diablo::reRender()
{
}