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
	_damage = 5;
	_maxHP = 35;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 20;
	_height = 20; // �ϴ��� ���� �����س�������(�̹���ũ��)

	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������
	
	return S_OK;
}

void zergling::release()
{
	SAFE_DELETE(_image);
}

void zergling::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 4, _height + 4);
	// ��Ÿ� ���缭 ���⼭ ����


	// ���ϴ� ���۸�Ư���̴ϱ� ������ص� ������
	if (_HP / _maxHP <= 0.5f && _maxDelay == 60)
	{ // �ǰ� 50%���ϸ� ����2��
		_maxDelay /= 2.f;
	}
}

void zergling::render()
{
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
			_image = FINDIMG("���۸����ݺ��");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
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
			_image = FINDIMG("���۸���������");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("���۸�����");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}
	
}
