#include "stdafx.h"
#include "zergling.h"

zergling::zergling()
{
}

zergling::~zergling()
{	
}

HRESULT zergling::init(BELONG belong, float x, float y)
{ // �� ��ġ�� �ʰ� �̰� �����ؼ� ���� �ٲ���°� ��õ
	_belong = belong;
	_ID = 1;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 60; // ���� 1�ʿ� �Ѵ� ġ�Բ�
	_damage = 7;
	_maxHP = 35;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 20;
	_height = 20; // �ϴ��� ���� �����س�������(�̹���ũ��)
	_healCount = 60;
	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������
	if (_belong == PLAYER)PLAYSND("���۸�����");
	return S_OK;
}

void zergling::release()
{
	SAFE_DELETE(_image);
}

void zergling::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 6, _height + 6);


	// ���ϴ� ���۸�Ư���̴ϱ� ������ص� ������
	if (_HP / _maxHP <= 0.5f)
	{ // �ǰ� 50%���ϸ� ����2�� + ��(�ִ� 18��ŭ)
		--_healCount;
	}
	if (_healCount < 60 && _healCount > 0)
	{ // �ǰ� 50%���ϸ� ����2�� + 1ȸ������(�ִ� 12��ŭ)
		_maxDelay = 30;
		_HP += 0.2f;
		--_healCount;
		if (_maxHP < _HP) _HP = _maxHP;
	}
}

void zergling::render()
{
	if (_healCount < 60 && _healCount > 0 && _state != DEAD) FINDIMG("���۸���")->frameRender(getMemDC(), _rc.left - 28, _rc.top - 15, _healCount / 6, 0);
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->frameRender(getMemDC(), _rc.left-9, _rc.top-9, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 9, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 9, _rc.top - 9, _frameDirection, _frame);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		_image->frameRender(getMemDC(), _rc.left - 22, _rc.top - 24, _frame, 0);
		break;
	}
}

void zergling::reRender()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 9, _frameDirection, _frame, 150);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 9, _frameDirection, 0, 150);
		break;
	case ATTACK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 9, _rc.top - 9, _frameDirection, _frame, 150);
		break;
	}
}

void zergling::setState(STATE state)
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
			_image = FINDIMG("���۸��̵����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("���۸����ݺ��");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			PLAYSND("���۸�����");
			_image = FINDIMG("���۸����ݺ��");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("���۸����");
			_image = FINDIMG("���۸�����");
			_maxFrame = _image->getMaxFrameX();
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("���۸��̵�����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("���۸���������");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			PLAYSND("���۸�����");
			_image = FINDIMG("���۸���������");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("���۸����");
			_image = FINDIMG("���۸�����");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}
	
}
