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
	_maxDelay = 90; // ���� 1.5�ʿ� �Ѵ� ġ�Բ�
	_damage = 5;
	_maxHP = 35;
	_attackIndex = 2; // 2�� �ε����� �ɶ� ��������
	_width = 40;
	_height = 39; // �ϴ��� ���� �����س�������(�̹���ũ��)

	commonInit(); // �տ����� �����ؼ� ����� ������ �����Ƿ� �ڿ��� ��������
	
	return S_OK;
}

void zergling::release()
{
	commonRelease();
}

void zergling::update()
{
	commonUpdate();
}

void zergling::render()
{
	switch (_state)
	{ // ��ġ ������ �����ؼ� ����
	case IDLE: // ù���� ���������� ����
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, 0);
		break;
	case WALK:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // ù���� ���������� ����
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, _frame);
		break;
	case DEAD: // �������ε��� �ٸ��� ���ϱ� ����
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame, 0);
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
		case IDLE:
			_image = FINDIMG("���۸��̵����");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case WALK:
			_image = FINDIMG("���۸��̵����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("���۸��̵����");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case ATTACK:
			_image = FINDIMG("���۸����ݺ��");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_damage = 0; // ������ �Ⱦ��״� �׾����� ī��Ʈ�� ��Ȱ���Ѵ�(..)
			_image = FINDIMG("���۸�����");
			_maxFrame = _image->getMaxFrameX();
			break; // ��� x�� ���η� ����ϱ⋚��
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case IDLE:
			_image = FINDIMG("���۸��̵�����");
			_maxFrame = _image->getMaxFrameY();
			break;
			// ���۸��ǰ�� ���� �̵����� y������ 0���θ� ������
		case WALK:
			_image = FINDIMG("���۸��̵�����");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("���۸��̵�����");
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
