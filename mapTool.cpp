#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	createSampleTiles();

	createIsoMap(TILEX, TILEY);
	_tempTile.fX = 0;
	_tempTile.fY = 0;
	_pickingPt = { 0,0 };
	_moveUnMove = false;
	_brushOn = false;
	_rs = MAX;
	return S_OK;
}

void mapTool::imageInit() // 캠좌표 참고로했고 그에따라 update로 옮겼음
{
	//이미지를 덮어씌울 렉트 선언 영역
	_saveBt = RectMake(WINSIZEX-210 + CAMX, 620 + CAMY, 64, 32);
	_saveBt2 = RectMake(WINSIZEX-140 + CAMX, 620 + CAMY, 64, 32);
	_saveBt3 = RectMake(WINSIZEX-70 + CAMX, 620 + CAMY, 64, 32);

	_loadBt = RectMake(WINSIZEX-210 + CAMX, 660 + CAMY, 64, 32);
	_loadBt2 = RectMake(WINSIZEX-140 + CAMX, 660 + CAMY, 64, 32);
	_loadBt3 = RectMake(WINSIZEX-70 + CAMX, 660 + CAMY, 64, 32);

	_move = RectMake(WINSIZEX-210 + CAMX, 580 + CAMY, 64, 32);
	_unMove = RectMake(WINSIZEX-140 + CAMX, 580 + CAMY, 64, 32);
	_undo = RectMake(WINSIZEX - 70 + CAMX, 580 + CAMY, 64, 32);

	_fill = RectMake(WINSIZEX-210 + CAMX, 540 + CAMY, 64, 32);
	_open = RectMake(WINSIZEX - 140 + CAMX, 540 + CAMY, 64, 32);
	_close = RectMake(WINSIZEX - 140 + CAMX, 540 + CAMY, 64, 32);

	_small = RectMake(WINSIZEX - 70 + CAMX, 540 + CAMY, 64, 32);
	_medium = RectMake(WINSIZEX - 70 + CAMX, 540 + CAMY, 64, 32);
	_max = RectMake(WINSIZEX - 70 + CAMX, 540 + CAMY, 64, 32);
}

void mapTool::imageRender()
{
	if (_brushOn)
	{
		//샘플타일 메뉴
		IMAGEMANAGER->findImage("tileMenu")->render(getMemDC(), CAMX + WINSIZEX - 522, CAMY);
		//샘플타일
		for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
		{
			HBRUSH _brush;
			_brush = CreateSolidBrush(RGB(0, 0, 0));

			if (_sample[i].inRect) FillRect(getMemDC(), &_sample[i].rc, _brush);

			if (KEYMANAGER->isToggleKey(VK_F2)) Rectangle(getMemDC(), _sample[i].rc);
		}
		//샘플타일
		IMAGEMANAGER->findImage("mapTiles")->render(getMemDC(), CAMX + WINSIZEX - 512, CAMY);
	}
	//세이브와 로드
	IMAGEMANAGER->findImage("save1")->render(getMemDC(), _saveBt.left, _saveBt.top);
	IMAGEMANAGER->findImage("save2")->render(getMemDC(), _saveBt2.left, _saveBt2.top);
	IMAGEMANAGER->findImage("save3")->render(getMemDC(), _saveBt3.left, _saveBt3.top);
	IMAGEMANAGER->findImage("load1")->render(getMemDC(), _loadBt.left, _loadBt.top);
	IMAGEMANAGER->findImage("load2")->render(getMemDC(), _loadBt2.left, _loadBt2.top);
	IMAGEMANAGER->findImage("load3")->render(getMemDC(), _loadBt3.left, _loadBt3.top);
	IMAGEMANAGER->findImage("undo")->render(getMemDC(), _undo.left, _undo.top);
	IMAGEMANAGER->findImage("fill")->render(getMemDC(), _fill.left, _fill.top);

	if(_rs == SMALL) IMAGEMANAGER->findImage("small")->render(getMemDC(), _small.left, _small.top);
	else if (_rs == MEDIUM) IMAGEMANAGER->findImage("medium")->render(getMemDC(), _medium.left, _medium.top);
	else IMAGEMANAGER->findImage("max")->render(getMemDC(), _max.left, _max.top);

	if(!_brushOn) IMAGEMANAGER->findImage("open")->render(getMemDC(), _open.left, _open.top);
	else IMAGEMANAGER->findImage("close")->render(getMemDC(), _close.left, _close.top);
	//무브와 언무드
	if (!_moveUnMove)
	{
		IMAGEMANAGER->findImage("move")->render(getMemDC(), _move.left, _move.top);
		IMAGEMANAGER->findImage("unmove")->alphaRender(getMemDC(), _unMove.left, _unMove.top, 80);
	}
	else
	{
		IMAGEMANAGER->findImage("move")->alphaRender(getMemDC(), _move.left, _move.top, 80);
		IMAGEMANAGER->findImage("unmove")->render(getMemDC(), _unMove.left, _unMove.top);
	}
}

void mapTool::moveUnMove()
{
	if (PtInRect(&_move, _cameraPtMouse))
	{
		_moveUnMove = false;
	}

	if (PtInRect(&_unMove, _cameraPtMouse))
	{
		_moveUnMove = true;
	}
}

void mapTool::openClose()
{
	if (PtInRect(&_open, _cameraPtMouse) && !_brushOn)
	{
		_brushOn = true;
	}
	else if (PtInRect(&_close, _cameraPtMouse) && _brushOn)
	{
		_brushOn = false;
	}
}

void mapTool::renderSize()
{
	if (PtInRect(&_small, _cameraPtMouse) && _rs == SMALL)
	{
		_rs = MEDIUM;
	}
	else if (PtInRect(&_medium, _cameraPtMouse) && _rs == MEDIUM)
	{
		_rs = MAX;
	}
	else if (PtInRect(&_max, _cameraPtMouse) && _rs == MAX)
	{
		_rs = SMALL;
	}
}

void mapTool::release()
{
}

//그려질 시작 x, 그려질 시작 y, TILEX 넣기, TILEY 넣기
void mapTool::createIsoMap(int tileX, int tileY)
{

	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			_isoTile[i * tileX + j].fX = 0;
			_isoTile[i * tileX + j].fY = 0;
			_isoTile[i * tileX + j].nX = j;
			_isoTile[i * tileX + j].nY = i;

			_isoTile[i * tileX + j].inRect = false;
			_isoTile[i * tileX + j].MUM = MOVE;

			_isoTile[i * tileX + j].centerX = TILESIZEX * (TILEX + (j - i))/2;
			_isoTile[i * tileX + j].centerY = TILESIZEY * (i + j + 1) / 2;

			_isoTile[i * tileX + j].drawX = _isoTile[i * tileX + j].centerX - TILESIZEX / 2;
			_isoTile[i * tileX + j].drawY = _isoTile[i * tileX + j].centerY - TILESIZEY / 2;
		}
	}
}

void mapTool::createSampleTiles()
{
	for (int i = 0; i < SAMPLEY; ++i)
	{
		for (int j = 0; j < SAMPLEX; ++j)
		{
			//이게 샘플의 위치를 저장해두는거 그래야 몇번째 타일인지 알고 가져다 쓸수있음
			_sample[i * SAMPLEX + j].fX = j;
			_sample[i * SAMPLEX + j].fY = i;

			_sample[i * SAMPLEX + j].rc = RectMake((WINSIZEX - 512) + (j*TILESIZEX), 0 + (i*TILESIZEY), TILESIZEX, TILESIZEY);
			_sample[i * SAMPLEX + j].inRect = false;
		}
	}
}

void mapTool::sampleTileMove()
{
	for (int i = 0; i < SAMPLEY; ++i)
	{
		for (int j = 0; j < SAMPLEX; ++j)
		{
			_sample[i * SAMPLEX + j].rc = RectMake((WINSIZEX + CAMX - 512) + (j*TILESIZEX), CAMY + (i*TILESIZEY), TILESIZEX, TILESIZEY);
		}
	}
}

void mapTool::ptInSample()
{
	if (_brushOn)
	{
		//샘플타일안에 마우스가 들어갔으면 표시해라
		for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
		{
			if (PtInRect(&_sample[i].rc, _cameraPtMouse))
			{
				_sample[i].inRect = true;
			}
			else _sample[i].inRect = false;
		}
	}

	//이건 아이소 타일 안에 마우스가 들어갔으면 표시 
	//마우스포인트가 아이소타일안에 들어왔는지 확인해줌
	//이거 그냥 피킹쓰면 되니까 수정했어
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (i == _pickingPt.y * TILEX + _pickingPt.x)
		{
			_isoTile[i].inRect = true;			
		}
		else _isoTile[i].inRect = false;
	}
}

void mapTool::createTile()
{
	if (_brushOn)
	{
		//새로운 타일을 만들어보즈아!!
		for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
		{
			if (PtInRect(&_sample[i].rc, _cameraPtMouse))
			{
				_tempTile.fX = _sample[i].fX;
				_tempTile.fY = _sample[i].fY;
				return;
			}
		}
	}

	if (!_moveUnMove)
	{
		_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fX = _tempTile.fX;
		_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fY = _tempTile.fY;
		_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = MOVE;
		InvalidateRect(_hWnd, NULL, false);
	}
	else if (_moveUnMove)
	{
		_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fX = _tempTile.fX;
		_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fY = _tempTile.fY;
		_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
		InvalidateRect(_hWnd, NULL, false);
	}
}

void mapTool::save()
{
	if (PtInRect(&_saveBt, _cameraPtMouse))
	{
		HANDLE file;
		DWORD write;

		file = CreateFile("stage1.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_saveBt2, _cameraPtMouse))
	{
		HANDLE file;
		DWORD write;

		file = CreateFile("stage2.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_saveBt3, _cameraPtMouse))
	{
		HANDLE file;
		DWORD write;

		file = CreateFile("stage3.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
	}
}

void mapTool::load()
{
	if (PtInRect(&_loadBt, _cameraPtMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_loadBt2, _cameraPtMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_loadBt3, _cameraPtMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("stage3.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
	}
}

void mapTool::tempSave()
{// 마우스 딱 누를때만 타일이 그려지기전 발동함. temp에 저장
	_tempSaved = true;
	HANDLE file;
	DWORD write;

	file = CreateFile("temp.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &write, NULL);

	CloseHandle(file);
}

void mapTool::tempLoad()
{// temp를 불러옴
		if (!_tempSaved) return;
		HANDLE file;
		DWORD read;

		file = CreateFile("temp.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);

		CloseHandle(file);
}

void mapTool::fill(int x, int y)
{
	for (int i = 0; i < TILEX* TILEY; ++i)
	{
		_isoTile[i].fX = x;
		_isoTile[i].fY = y;
	}
}

void mapTool::cameraControl()
{
	_cameraPtMouse.x = _ptMouse.x + CAMX;
	_cameraPtMouse.y = _ptMouse.y + CAMY;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setCameraX(CAMX - 5);
		if (CAMX < 0) CAMERAMANAGER->setCameraX(0);
		sampleTileMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setCameraX(CAMX + 5);
		if (CAMX > MAPSIZEX-WINSIZEX) CAMERAMANAGER->setCameraX(MAPSIZEX - WINSIZEX);
		sampleTileMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->setCameraY(CAMY - 5);
		if (CAMY < 0) CAMERAMANAGER->setCameraY(0);
		sampleTileMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraY(CAMY + 5);
		if (CAMY > MAPSIZEY - WINSIZEY) CAMERAMANAGER->setCameraY(MAPSIZEY - WINSIZEY);
		sampleTileMove();
	}
}

void mapTool::update()
{
	_pickingPt = picking(_cameraPtMouse.x, _cameraPtMouse.y);
	cameraControl();

	imageInit();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_undo, _cameraPtMouse)) tempLoad();
		tempSave();
		createTile();
		save();
		load();
		moveUnMove();
		if (PtInRect(&_fill, _cameraPtMouse)) fill(_tempTile.fX, _tempTile.fY);
		openClose();
		renderSize();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		createTile();
	}
	ptInSample();
	if (KEYMANAGER->isOnceKeyDown(VK_F4)) SCENEMANAGER->changeScene("메인씬");
}

void mapTool::render()
{
	//아이소타일
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ // 화면 밖의 맵은 그리지 않도록 함. 렉 방지용. 메인씬에도 이거 쓰고 시연떄도 이거 줄여서 보여줘도 될듯
		if (_rs == SMALL)
		{
			if (_isoTile[i].nX > 9) continue;
			if (_isoTile[i].nY > 9) continue;
		}
		else if (_rs == MEDIUM)
		{
			if (_isoTile[i].nX > 19) continue;
			if (_isoTile[i].nY > 19) continue;
		}
		else
		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;
		if (_isoTile[i].inRect) IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 150);
		else IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
	}
	imageRender();

	//아래는 편의상 만든 숫자보이게하는거
	char str[256];
	sprintf_s(str, "TempTile X : %d , Y : %d", _tempTile.fX, _tempTile.fY);
	TextOut(getMemDC(), CAMX, CAMY+70, str, strlen(str));

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		sprintf_s(str, "%d, %d", _isoTile[i].nX, _isoTile[i].nY);
		if (KEYMANAGER->isToggleKey(VK_F1)) TextOut(getMemDC(), CAMX+ _isoTile[i].drawX + TILEX, CAMY+_isoTile[i].drawY + (TILEY / 2), str, strlen(str));
	}

	sprintf_s(str, "ptMouse X : %d , Y : %d", CAMX + _cameraPtMouse.x, CAMY + _cameraPtMouse.y);
	TextOut(getMemDC(), CAMX+ 150, CAMY+ 70, str, strlen(str));
}

inline POINT mapTool::picking(long x, long y)
{ // 이게 피킹
	int xx; int yy;
	if (2 * y < (x - 960))	return { -1,0 }; // y=1/2x보다 위에있는지 (맵밖 벗어남)
	if (2 * y < -(x - 960))	return { -1,0 }; // y=-1/2x보다 위에있는지 (맵밖 벗어남)
	//-1이면 예외처리됨(키매니저 L버튼 참고)

	// 왜 y=1/2x가 아니라 2y=x로 썼냐면 나눗셈연산이 느리기때문에 이렇게 쓴거임.
	// 320은 TILEWIDTH * TILEX / 2 (=맵전체 가로크기의 절반값)와 같은데 부하를 줄이기 위해 계산하고 넣은것임

	 // 64는 타일 높이(TILEHEIGHT)에 양변 2곱한값이며 이만큼씩 이격된(밑으로간) 직선이라 보면 됨
	xx = (2 * y + (x - 960)) / 64; // y절편을 이용한 방식으로 바꾸었음
	if (xx > 29) return { -1,0 }; // 맵밖 벗어난거면 예외처리

	yy = (2 * y - (x - 960)) / 64; // 기울기만 음수고 나머진 상동
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}
