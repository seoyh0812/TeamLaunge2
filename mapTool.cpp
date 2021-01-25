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
	imageInit();
	createSampleTiles();

	createIsoMap(650, 0, TILEX, TILEY);
	_tempTile.fX = 0;
	_tempTile.fY = 0;
	_moveUnMove = false;
	return S_OK;
}

void mapTool::imageInit()
{
	//이미지 영역
	IMAGEMANAGER->addFrameImage("mapTiles", "image/maptool/iso256X160.bmp", 0, 0, 256, 160, 4, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save1", "image/maptool/save1.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save2", "image/maptool/save2.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save3", "image/maptool/save3.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load1", "image/maptool/load1.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load2", "image/maptool/load2.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load3", "image/maptool/load3.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("move", "image/maptool/move.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("unmove", "image/maptool/unmove.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("undo", "image/maptool/undo.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fill", "image/maptool/fill.bmp", 64, 32, false, RGB(255, 0, 255));

	//이미지를 덮어씌울 렉트 선언 영역
	_saveBt = RectMake(WINSIZEX-210, 720, 64, 32);
	_saveBt2 = RectMake(WINSIZEX-140, 720, 64, 32);
	_saveBt3 = RectMake(WINSIZEX-70, 720, 64, 32);

	_loadBt = RectMake(WINSIZEX-210, 760, 64, 32);
	_loadBt2 = RectMake(WINSIZEX-140, 760, 64, 32);
	_loadBt3 = RectMake(WINSIZEX-70, 760, 64, 32);

	_move = RectMake(WINSIZEX-210, 680, 64, 32);
	_unMove = RectMake(WINSIZEX-140, 680, 64, 32);

	_fill = RectMake(WINSIZEX-210, 640, 64, 32);

	_undo = RectMake(WINSIZEX-70, 680, 64, 32);
}

void mapTool::imageRender()
{
	//오른쪽 샘플타일
	IMAGEMANAGER->findImage("mapTiles")->render(getMemDC(), WINSIZEX-256, 0);

	//세이브와 로드
	IMAGEMANAGER->findImage("save1")->render(getMemDC(), _saveBt.left, _saveBt.top);
	IMAGEMANAGER->findImage("save2")->render(getMemDC(), _saveBt2.left, _saveBt2.top);
	IMAGEMANAGER->findImage("save3")->render(getMemDC(), _saveBt3.left, _saveBt3.top);
	IMAGEMANAGER->findImage("load1")->render(getMemDC(), _loadBt.left, _loadBt.top);
	IMAGEMANAGER->findImage("load2")->render(getMemDC(), _loadBt2.left, _loadBt2.top);
	IMAGEMANAGER->findImage("load3")->render(getMemDC(), _loadBt3.left, _loadBt3.top);
	IMAGEMANAGER->findImage("undo")->render(getMemDC(), _undo.left, _undo.top);
	IMAGEMANAGER->findImage("fill")->render(getMemDC(), _fill.left, _fill.top);

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
	if (PtInRect(&_move, _ptMouse))
	{
		_moveUnMove = false;
	}

	if (PtInRect(&_unMove, _ptMouse))
	{
		_moveUnMove = true;
	}
}

void mapTool::release()
{
}

//그려질 시작 x, 그려질 시작 y, TILEX 넣기, TILEY 넣기
void mapTool::createIsoMap(float x, float y, int tileX, int tileY)
{
	_tilePoint.x = x;
	_tilePoint.y = y;

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

			_isoTile[i * tileX + j].drawX = _tilePoint.x + ((j * TILESIZEX) / 2) - (i*(TILESIZEX / 2));
			_isoTile[i * tileX + j].drawY = _tilePoint.y + ((j * TILESIZEY) / 2) + (i*(TILESIZEY / 2));
			_isoTile[i * tileX + j].centerX = _isoTile[i * tileX + j].drawX + (TILEX / 2) + (TILEY / 2);
			_isoTile[i * tileX + j].centerY = _isoTile[i * tileX + j].drawY + (TILEX / 2) + (TILEY / 2);
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

			_sample[i * SAMPLEX + j].rc = RectMake((WINSIZEX - 256) + (j*TILESIZEX), 0 + (i*TILESIZEY), TILESIZEX, TILESIZEY);
			_sample[i * SAMPLEX + j].inRect = false;
		}
	}
}

void mapTool::ptInSample()
{
	//샘플타일안에 마우스가 들어갔으면 표시해라
	for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
	{
		if (PtInRect(&_sample[i].rc, _ptMouse))
		{
			_sample[i].inRect = true;
		}
		else _sample[i].inRect = false;
	}

	//이건 아이소 타일 안에 마우스가 들어갔으면 표시 
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//마우스포인트가 아이소타일안에 들어왔는지 확인해줌
		if (_ptMouse.x <= _isoTile[i].centerX + (TILESIZEX / 3) && _ptMouse.x >= _isoTile[i].centerX - (TILESIZEX / 3)
			&& _ptMouse.y <= _isoTile[i].centerY + (TILESIZEY / 3) && _ptMouse.y >= _isoTile[i].centerY - (TILESIZEY / 3))
		{
			_isoTile[i].inRect = true;
		}
		else _isoTile[i].inRect = false;
	}
}

void mapTool::createTile()
{
	//새로운 타일을 만들어보즈아!!
	for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
	{
		if (PtInRect(&_sample[i].rc, _ptMouse))
		{
			_tempTile.fX = _sample[i].fX;
			_tempTile.fY = _sample[i].fY;
			break;
		}
	}

	_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fX = _tempTile.fX;
	_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fY = _tempTile.fY;
	InvalidateRect(_hWnd, NULL, false);

	//for (int i = 0; i < TILEX * TILEY; ++i)
	//{
	//	//마우스포인트가 아이소타일안에 들어왔는지 확인해줌
	//	//무브 상태로 그려지면 타일안의 MUM의 값이 무브
	//	if (_ptMouse.x <= _isoTile[i].centerX + (TILESIZEX / 3) && _ptMouse.x >= _isoTile[i].centerX - (TILESIZEX / 3)
	//		&& _ptMouse.y <= _isoTile[i].centerY + (TILESIZEY / 3) && _ptMouse.y >= _isoTile[i].centerY - (TILESIZEY / 3) && !_moveUnMove)
	//	{
	//		_isoTile[i].fX = _tempTile.fX;
	//		_isoTile[i].fY = _tempTile.fY;
	//		_isoTile[i].MUM = MOVE;
	//		//화면 갱신해주는 함수
	//		InvalidateRect(_hWnd, NULL, false);
	//		break;
	//	}
	//	//언무브 상태로 그려지면 타일안의 MUM의 값이 언무브
	//	else if (_ptMouse.x <= _isoTile[i].centerX + (TILESIZEX / 3) && _ptMouse.x >= _isoTile[i].centerX - (TILESIZEX / 3)
	//		&& _ptMouse.y <= _isoTile[i].centerY + (TILESIZEY / 3) && _ptMouse.y >= _isoTile[i].centerY - (TILESIZEY / 3) && _moveUnMove)
	//	{
	//		_isoTile[i].fX = _tempTile.fX;
	//		_isoTile[i].fY = _tempTile.fY;
	//		_isoTile[i].MUM = UNMOVE;
	//		//화면 갱신해주는 함수
	//		InvalidateRect(_hWnd, NULL, false);
	//		break;
	//	}
	//}
}

void mapTool::save()
{
	if (PtInRect(&_saveBt, _ptMouse))
	{
		HANDLE file;
		DWORD write;

		file = CreateFile("saveMap1.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_saveBt2, _ptMouse))
	{
		HANDLE file;
		DWORD write;

		file = CreateFile("saveMap2.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_saveBt3, _ptMouse))
	{
		HANDLE file;
		DWORD write;

		file = CreateFile("saveMap3.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
	}
}

void mapTool::load()
{
	if (PtInRect(&_loadBt, _ptMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("saveMap1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_loadBt2, _ptMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("saveMap2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_loadBt3, _ptMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("saveMap3.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &read, NULL);

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

	WriteFile(file, _isoTile, sizeof(tagIsoTile) * TILEX*TILEY, &write, NULL);

	CloseHandle(file);
}

void mapTool::tempLoad()
{// temp를 불러옴
		if (!_tempSaved) return;
		HANDLE file;
		DWORD read;

		file = CreateFile("temp.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(tagIsoTile) * TILEX*TILEY, &read, NULL);

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

void mapTool::update()
{
	_pickingPt = picking(_ptMouse.x, _ptMouse.y);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_undo, _ptMouse)) tempLoad();
		tempSave();
		createTile();
		save();
		load();
		moveUnMove();
		if (PtInRect(&_fill, _ptMouse)) fill(_tempTile.fX, _tempTile.fY);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		createTile();
	}
	ptInSample();
}

void mapTool::render()
{
	//아이소타일
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_isoTile[i].inRect) IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 150);
		else IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
	}

	//샘플타일
	for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
	{
		HBRUSH _brush;
		_brush = CreateSolidBrush(RGB(100, 100, 100));

		if (_sample[i].inRect) FillRect(getMemDC(), &_sample[i].rc, _brush);

		if (KEYMANAGER->isToggleKey(VK_F2)) Rectangle(getMemDC(), _sample[i].rc);
	}
	imageRender();
	//이건 마우스 위에 현재 고른 타일 출력인데 접어둠
	//IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _ptMouse.x - TILESIZEX / 2, _ptMouse.y - TILESIZEY / 2, _tempTile.fX, _tempTile.fY, 200);

	//아래는 편의상 만든 숫자보이게하는거
	char str[256];
	sprintf_s(str, "TempTile X : %d , Y : %d", _tempTile.fX, _tempTile.fY);
	TextOut(getMemDC(), 0, 70, str, strlen(str));

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		sprintf_s(str, "%d, %d", _isoTile[i].nX, _isoTile[i].nY);
		if (KEYMANAGER->isToggleKey(VK_F1)) TextOut(getMemDC(), _isoTile[i].drawX + (TILEX + 5), _isoTile[i].drawY + (TILEY / 2), str, strlen(str));
	}

	sprintf_s(str, "ptMouse X : %d , Y : %d", _pickingPt.x, _pickingPt.y);
	TextOut(getMemDC(), 150, 70, str, strlen(str));
}

inline POINT mapTool::picking(long x, long y)
{ // 이게 피킹
	int xx; int yy;
	//if (2 * y < (x - 320))	return { -1,0 }; // y=1/2x보다 위에있는지 (맵밖 벗어남)
	//if (2 * y < -(x - 320))	return { -1,0 }; // y=-1/2x보다 위에있는지 (맵밖 벗어남)
	//-1이면 예외처리됨(키매니저 L버튼 참고)

	// 왜 y=1/2x가 아니라 2y=x로 썼냐면 나눗셈연산이 느리기때문에 이렇게 쓴거임.
	// 320은 TILEWIDTH * TILENUMX / 2 (=맵전체 가로크기의 절반값)와 같은데 부하를 줄이기 위해 계산하고 넣은것임

	 // 64는 타일 높이(TILEHEIGHT)에 양변 2곱한값이며 이만큼씩 이격된(밑으로간) 직선이라 보면 됨
	xx = (2 * y + (x - 682)) / 64; // y절편을 이용한 방식으로 바꾸었음
	if (xx > 19) return { -1,0 }; // 맵밖 벗어난거면 예외처리

	yy = (2 * y - (x - 682)) / 64; // 기울기만 음수고 나머진 상동
	if (yy > 19) return { -1,0 };

	return { xx , yy };
}
