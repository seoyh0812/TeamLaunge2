#include "stdafx.h"
#include "templar.h"

templar::templar()
{
}

templar::~templar()
{
}

HRESULT templar::init(BELONG belong, float x, float y)
{
	_belong = belong;
	_ID = 4;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 300; // ���� 5�ʿ� �Ѵ� ġ�Բ�
	_damage = 0;
	_maxHP = 70;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 21;
	_height = 26; // �ϴ��� ���� �����س�������(�̹���ũ��)

	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������
	return S_OK;
}

void templar::release()
{
	SAFE_DELETE(_image);
}

void templar::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 100, _height + 100);
}

void templar::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		if (_frame == 0) _frame = 1; // 0���������� �̻��� �Ѥ�
		_image->frameRender(getMemDC(), _rc.left - 4, _rc.top - 6, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		if (_frame == 0) _frame = 1; // 0���������� �̻��� �Ѥ�
		_image->frameRender(getMemDC(), _rc.left - 4, _rc.top - 5, _frameDirection, _frame);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 23, _rc.top - 24, _frameDirection, _frame);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		_image->frameRender(getMemDC(), _rc.left - 4, _rc.top - 23, _frame, 0);
		break;
	}
}

void templar::setState(STATE state)
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
			_image = FINDIMG("���÷��̵����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("���÷������");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACK:
			_image = FINDIMG("���÷����ݺ��");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("���÷�����");
			_maxFrame = _image->getMaxFrameX();
			_deathDuration = 10; // ��� ��ü�� �ݹ������⶧���� ���ӽð��� �����
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("���÷��̵�����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("���÷��������");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACK:
			_image = FINDIMG("���÷���������");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("���÷�����");
			_maxFrame = _image->getMaxFrameX();
			_deathDuration = 10;
			break;
		}
	}
} // ���÷��ܻ���