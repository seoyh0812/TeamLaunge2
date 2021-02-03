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
	_afterImageFrame = _afterImageCount = _damage = 0;
	_maxHP = 40;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 21;
	_height = 21; // �ϴ��� ���� �����س�������(�̹���ũ��)

	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������

	_afterImage = _rc;
	if (_belong == PLAYER)PLAYSND("���÷�����");
	return S_OK;
}

void templar::release()
{
	SAFE_DELETE(_image);
}

void templar::update()
{
	commonUpdate();
	_rangeRc = RectMakeCenter(_x, _y, _width + 250, _height + 250);

	// ���ϴ� �ܻ�׸����
	if (_state == WALK && (_x < _afterImage.left+5 ||
		_x > _afterImage.right-5 ||
		_y < _afterImage.top+5 ||
		_y > _afterImage.bottom-5))
	{
		_afterImagePt.x = _afterImage.left;
		_afterImagePt.y = _afterImage.top;
		_afterImage = _rc;
		_afterImageFrame = _afterImageCount = 0;
		_afterImageFrameDirection = _frameDirection;
	}
	if (_afterImageCount < 6 && _afterImageFrame < 4) ++_afterImageCount;
	else if (_afterImageCount > 5 && _afterImageFrame < 4)
	{
		_afterImageCount = 0;
		++_afterImageFrame;
	}
}

void templar::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->frameRender(getMemDC(), _rc.left - 4, _rc.top - 6, _frameDirection, 0);
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

	if (_afterImageFrame < 4)
	{
		FINDIMG("���÷��ܻ�")->frameRender(getMemDC(), _afterImagePt.x - 4, _afterImagePt.y - 6, _afterImageFrameDirection, _afterImageFrame);
	}
	
}

void templar::reRender()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case WALK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 4, _rc.top - 6, _frameDirection, 0, 150);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		if (_frame == 0) _frame = 1; // 0���������� �̻��� �Ѥ�
		_image->alphaFrameRender(getMemDC(), _rc.left - 4, _rc.top - 5, _frameDirection, _frame, 150);
		break;
	case ATTACK:
		_image->alphaFrameRender(getMemDC(), _rc.left - 23, _rc.top - 24, _frameDirection, _frame, 150);
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
			PLAYSND("���÷�����");
			_image = FINDIMG("���÷����ݺ��");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("���÷����");
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
			PLAYSND("���÷�����");
			_image = FINDIMG("���÷���������");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			PLAYSND("���÷����");
			_image = FINDIMG("���÷�����");
			_maxFrame = _image->getMaxFrameX();
			_deathDuration = 10;
			break;
		}
	}
}