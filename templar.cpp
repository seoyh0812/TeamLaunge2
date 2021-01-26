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
	_maxDelay = 300; // 대충 5초에 한대 치게끔
	_damage = 0;
	_maxHP = 70;
	_attackIndex = 2; // 2번 인덱스가 될때 공격판정
	_width = 21;
	_height = 26; // 일단은 대충 설정해놓은거임(이미지크기)

	commonInit(); // 앞에변수 참조해서 만드는 변수도 있으므로 뒤에다 만들어야함
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
	{ // 위치 적당히 보정해서 쓸것
	case WALK:
		if (_frame == 0) _frame = 1; // 0번프레임이 이상함 ㅡㅡ
		_image->frameRender(getMemDC(), _rc.left - 4, _rc.top - 6, _frameDirection, _frame);
		break;
	case ATTACKWAIT: // 첫번쨰 프레임으로 고정
		if (_frame == 0) _frame = 1; // 0번프레임이 이상함 ㅡㅡ
		_image->frameRender(getMemDC(), _rc.left - 4, _rc.top - 5, _frameDirection, _frame);
		break;
	case ATTACK:
		_image->frameRender(getMemDC(), _rc.left - 23, _rc.top - 24, _frameDirection, _frame);
		break;
	case DEAD: // 프레임인덱스 다르게 도니까 주의
		_image->frameRender(getMemDC(), _rc.left - 4, _rc.top - 23, _frame, 0);
		break;
	}
}

void templar::setState(STATE state)
{
	if (_state == state) return; // 같은걸로 셋한거면 처리 안해줌
	_frame = 0;
	_frameCount = 0;
	_state = state;
	if (_belong == PLAYER)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("템플러이동블루");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("템플러대기블루");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACK:
			_image = FINDIMG("템플러공격블루");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("템플러죽음");
			_maxFrame = _image->getMaxFrameX();
			_deathDuration = 10; // 얘는 시체가 금방사라지기때문에 지속시간이 당겨짐
			break; // 얘는 x임 가로로 재생하기떄문
		}
	}
	if (_belong == ENEMY)
	{
		switch (_state)
		{
		case WALK:
			_image = FINDIMG("템플러이동퍼플");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACKWAIT:
			_image = FINDIMG("템플러대기퍼플");
			_maxFrame = _image->getMaxFrameY();
			break;
		case ATTACK:
			_image = FINDIMG("템플러공격퍼플");
			_maxFrame = _image->getMaxFrameY();
			break;
		case DEAD:
			_image = FINDIMG("템플러죽음");
			_maxFrame = _image->getMaxFrameX();
			_deathDuration = 10;
			break;
		}
	}
} // 템플러잔상구현