#include "stdafx.h"
#include "tower1.h"


tower1::tower1()
{
}


tower1::~tower1()
{
}

HRESULT tower1::init(BELONG belong, float x, float y)
{ // �� ��ġ�� �ʰ� �̰� �����ؼ� ���� �ٲ���°� ��õ
	_belong = belong;
	_ID = 1;
	_x = x; _y = y;
	_speed = 0.0f;
	_maxDelay = 30; // ���� 1�ʿ� �Ѵ� ġ�Բ�
	_damage = 3;
	_maxHP = 9999;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 20;
	_height = 20; // �ϴ��� ���� �����س�������(�̹���ũ��)

	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������
	//if (_belong == PLAYER)PLAYSND("���۸�����");
	return S_OK;
}

void tower1::release()
{
	SAFE_DELETE(_image);
}

void tower1::update()
{
	commonUpdate();
	_focusRc = RectMakeCenter(_x, _y, _width + 300, _height + 300);
	_rangeRc = RectMakeCenter(_x, _y, _width + 300, _height + 300);

}

void tower1::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->frameRender(getMemDC(), _rc.left - 10, _rc.top - 18, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->frameRender(getMemDC(), _rc.left - 10, _rc.top - 18, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 10, _rc.top - 18, _frameDirection, _frame);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		_image->frameRender(getMemDC(), _rc.left - 22, _rc.top - 24, _frame, 0);
		break;
	}

	Rectangle(getMemDC(), _rc);
}

void tower1::reRender()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 10, _rc.top - 18, _frameDirection, _frame, 150);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->alphaFrameRender(getMemDC(), _rc.left - 10, _rc.top - 18, _frameDirection, 0, 150);
		break;
	case ATTACK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 10, _rc.top - 18, _frameDirection, _frame, 150);
		break;
	}
}

void tower1::setState(STATE state)
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
			_image = FINDIMG("tower1_idle_blue");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("tower1_atk_blue");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("tower1_atk_blue");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("tower1_dead");
			_maxFrame = _image->getMaxFrameX();
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("tower1_idle_red");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("tower1_atk_red");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("tower1_atk_red");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("tower1_dead");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}
}
