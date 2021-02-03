#include "stdafx.h"
#include "ghost.h"


ghost::ghost()
{
}


ghost::~ghost()
{
}

HRESULT ghost::init(BELONG belong, float x, float y)
{ // �� ��ġ�� �ʰ� �̰� �����ؼ� ���� �ٲ���°� ��õ
	_belong = belong;
	_ID = 8;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 120; // ���� 1�ʿ� �Ѵ� ġ�Բ�
	_damage = 18;
	_maxHP = 45;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 21;
	_height = 22; // �ϴ��� ���� �����س�������(�̹���ũ��)
	_count = 0;
	_used = false;

	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������
	if (_belong == PLAYER)PLAYSND("��Ʈ����");
	return S_OK;
}

void ghost::release()
{
	SAFE_DELETE(_image);
}

void ghost::update()
{
	commonUpdate();
	_focusRc = RectMakeCenter(_x, _y, _width + 500, _height + 500);
	_rangeRc = RectMakeCenter(_x, _y, _width + 500, _height + 500);
	// ��Ÿ� ���缭 ���⼭ ����

	//���� ü���� 33%���ϰ� �Ǹ� ü���� ������ ȸ���Ѵ�
	if (_HP < _maxHP / 3 && !_used)
	{
		_HP += _maxHP / 2;
		_used = true;
	}
}

void ghost::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 11, _frameDirection, _frame);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		_image->frameRender(getMemDC(), _rc.left - 18, _rc.top - 8, _frame, 0);
		break;
	}

	if (KEYMANAGER->isToggleKey(VK_F1)) Rectangle(getMemDC(), _rc);
}

void ghost::reRender()
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

void ghost::setState(STATE state)
{ // �̰ſ� ���ؼ� ������ּ���
	if (_state == state) return; // �����ɷ� ���ѰŸ� ó�� ������
	_frame = 0;
	_frameCount = 0;
	_state = state;
	if (_belong == PLAYER)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("ghost_move_blue");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("ghost_atk_blue");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			PLAYSND("��Ʈ����");
			_image = FINDIMG("ghost_atk_blue");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("��Ʈ���");
			_image = FINDIMG("ghost_dead_blue");
			_maxFrame = _image->getMaxFrameX();
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("ghost_move_red");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("ghost_atk_red");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			PLAYSND("��Ʈ����");
			_image = FINDIMG("ghost_atk_red");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("��Ʈ���");
			_image = FINDIMG("ghost_dead_red");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}

}
