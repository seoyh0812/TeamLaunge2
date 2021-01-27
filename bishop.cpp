#include "stdafx.h"
#include "bishop.h"

bishop::bishop()
{
}

bishop::~bishop()
{
}

HRESULT bishop::init(BELONG belong, float x, float y)
{
	_belong = belong;
	_ID = 5;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 120; // ���� 2�ʿ� �ѹ� ��ų����
	_damage = 0;
	_maxHP = 40;
	_attackIndex = 3; // 1�� �ε����� �ɶ� ��ų����
	_width = 12;
	_height = 30; // �ϴ��� ���� �����س�������(�̹���ũ��)
	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������

	return S_OK;
}

void bishop::release()
{
}

void bishop::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 100, _height + 100);

}

void bishop::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 5, _rc.top, _frameDirection / 2, 0);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		_image->frameRender(getMemDC(), _rc.left - 24, _rc.top - 4, _frame / 2, 0);
		break;
	}
}

void bishop::setState(STATE state)
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
			_image = FINDIMG("�������̵�");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("��������");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("��������");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_damage = 0; // ������ �Ⱦ��״� �׾����� ī��Ʈ�� ��Ȱ���Ѵ�(..)
			_image = FINDIMG("����������");
			_maxFrame = _image->getMaxFrameX();
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("�������̵�");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("��������");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("��������");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("����������");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}
}