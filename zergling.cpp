#include "stdafx.h"
#include "zergling.h"

zergling::zergling()
{
}

zergling::~zergling()
{
}

HRESULT zergling::init(BELONG belong, float x, float y)
{ // 뭐 놓치지 않게 이거 복붙해서 각각 바꿔놓는걸 추천
	_belong = belong;
	_ID = 1;
	_x = x; _y = y;
	_speed = 2.0f;
	_maxDelay = 90; // 대충 1.5초에 한대 치게끔
	_damage = 5;
	_maxHP = 35;
	_attackIndex = 2; // 2번 인덱스가 될때 공격판정
	_width = 40;
	_height = 39; // 일단은 대충 설정해놓은거임(이미지크기)

	commonInit(); // 앞에변수 참조해서 만드는 변수도 있으므로 뒤에다 만들어야함
	
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
	{ // 위치 적당히 보정해서 쓸것
	case IDLE: // 첫번쨰 프레임으로 고정
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, 0);
		break;
	case WALK:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, 0);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameDirection, _frame);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frame, 0);
		break;
	}
}

void zergling::setState(STATE state)
{ // 이거에 준해서 만들어주세요
	if (_state == state) return; // 같은걸로 셋한거면 처리 안해줌
	_frame = 0;
	_frameCount = 0;
	_state = state;
	if (_belong == PLAYER)
	{
		switch (_state)
		{
		case IDLE:
			_image = FINDIMG("저글링이동블루");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case WALK:
			_image = FINDIMG("저글링이동블루");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("저글링이동블루");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			_image = FINDIMG("저글링공격블루");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_damage = 0; // 어차피 안쓸테니 죽었을때 카운트로 재활용한다(..)
			_image = FINDIMG("저글링죽음");
			_maxFrame = _image->getMaxFrameX();
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case IDLE:
			_image = FINDIMG("저글링이동퍼플");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case WALK:
			_image = FINDIMG("저글링이동퍼플");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("저글링이동퍼플");
			_maxFrame = _image->getMaxFrameY();
			break;
			// 저글링의경우 대기는 이동에서 y프레임 0으로만 쓸거임
		case ATTACK:
			_image = FINDIMG("저글링공격퍼플");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("저글링죽음");
			_maxFrame = _image->getMaxFrameX();
			break;
		}
	}
	
}
