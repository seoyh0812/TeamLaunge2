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
	_damage = 0;
	_maxHP = 1000;
	_attackIndex = 5; // 2�� �ε����� �ɶ� ��������
	_width = 80;
	_height = 80; // �ϴ��� ���� �����س�������(�̹���ũ��) 
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
	_rangeRc = RectMakeCenter(_x, _y, _width + 600, _height + 600);
	_focusRc = RectMakeCenter(_x, _y, _width + 600, _height + 600);
	// �̰� ������Ʈ�ε� ��Ÿ���Ʈ���� ������ �ȵǰ���?
}

void diablo::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 54, _rc.top - 41, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 54, _rc.top - 41, _frameDirection, 5);
		break;
	case ATTACK:
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 73, _rc.top - 77, _frameDirection, _frame);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->frameRender(getMemDC(), _rc.left - 54, _rc.top - 84,  _frame , 0);
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
			_image = FINDIMG("��ƺ�� �ȱ�");
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
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->alphaFrameRender(getMemDC(), _rc.left - 54, _rc.top - 41, _frameDirection, _frame,150);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->alphaFrameRender(getMemDC(), _rc.left - 54, _rc.top - 41, _frameDirection, 5,150);
		break;
	case ATTACK:
		//Rectangle(getMemDC(), _summonRc);
		//Rectangle(getMemDC(), _rangeRc);
		_image->alphaFrameRender(getMemDC(), _rc.left - 73, _rc.top - 77, _frameDirection, _frame,150);
		break;
	}
}