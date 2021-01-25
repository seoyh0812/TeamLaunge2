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
	_selectTileX = _selectTileY = _currentStage = _tempSaved = 0;


	// 타일에 idX, idY를 순서대로 넣고 초기화
	for (int i = 0; i < TILENUMX * TILENUMY; ++i)
	{ // 타일숫자만큼 인덱스 번호를 부여해준다
		_tiles[i]._idX = i % TILENUMX;
		_tiles[i]._idY = i / TILENUMY;
		// 도출된 인덱스번호에 따라 중점을 지정해줌
		_tiles[i]._center = PointMake(TILENUMX*TILEWIDTH / 2 + (_tiles[i]._idX - i / TILENUMY)*TILEWIDTH / 2,
			(_tiles[i]._idX + _tiles[i]._idY) * 16 + (TILEHEIGHT / 2));
		// 중점에서부터 타일너비 타일높이로 렉트메이크(이건 타일을 덮는 렉트라 타일보다 2배 크다)
		_tiles[i]._rc = RectMakeCenter(_tiles[i]._center.x, _tiles[i]._center.y, TILEWIDTH, TILEHEIGHT);
	}

	load();

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_currentStage = 0;
		if (_waccess_s(L"./stage1.map", 0) == 0) load(); // stage1.map이 존재하면 로드함
		else fill(0, 0);
		// 맵파일이 있으면 로드하고 아니면 일반타일로 채움
		// waccess 파일이 있으면 0을 반환하는 함수
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{ // 위와 같음
		_currentStage = 1;
		if (_waccess_s(L"./stage2.map", 0) == 0) load();
		else fill(0, 0);
	}
	if (KEYMANAGER->isOnceKeyDown('3')) SCENEMANAGER->changeScene("타이틀씬");
	if (KEYMANAGER->isOnceKeyDown('S')) save(); // 저장
	if (KEYMANAGER->isOnceKeyDown('D'))	load(); // 로드
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		tempSave(); // 맵수정하기전 반짝 템프에 저장을 한다
		fill(_selectTileX, _selectTileY); // 선택된걸로 채움
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))	tempLoad();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{ // 맵수정하기전 반짝 템프에 저장을 한다
		if (_ptMouse.x < 640 && _ptMouse.y < 320) tempSave();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{ // 버튼 누른경우
		if (_ptMouse.x > 640 && _ptMouse.y < 32)
		{ // 팔레트를 누른경우임 -> 뭔타일 선택중인지 지정됨
			_selectTileX = (_ptMouse.x - 640) / 64;
			_selectTileY = _ptMouse.y / 32;
		}
		else if (_ptMouse.x < 640 && _ptMouse.y < 320)
		{ // 맵지역을 누른 경우임 -> 피킹하여 거따 그려준다
			POINT point = picking(_ptMouse.x, _ptMouse.y); // 피킹하여 포인트 저장
			if (point.x == -1) goto ONE; // ONE있는데까지 씹고 싶을떄. 피킹한게 {-1,0}일때 예외처리하는 부분임
			_tiles[point.y*TILENUMX + point.x]._frameX=_selectTileX;
			_tiles[point.y*TILENUMX + point.x]._frameY=_selectTileY;
			ONE:;
		}
	}
}

void mapTool::render()
{
	IMAGEMANAGER->render("tile", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("tile")->getWidth(), 0);

	for (int i = 0; i < TILENUMX * TILENUMY; ++i)
	{ // 각 타일마다 프레임대로 렌더
		IMAGEMANAGER->findImage("tile")->frameRender(getMemDC(),
			_tiles[i]._rc.left, _tiles[i]._rc.top, _tiles[i]._frameX, _tiles[i]._frameY);

		// 마름모 선 그리기
		LineMake(getMemDC(), _tiles[i]._center.x - 32, _tiles[i]._center.y, _tiles[i]._center.x, _tiles[i]._center.y - 16);
		LineMake(getMemDC(), _tiles[i]._center.x - 32, _tiles[i]._center.y, _tiles[i]._center.x, _tiles[i]._center.y + 16);
		LineMake(getMemDC(), _tiles[i]._center.x + 32, _tiles[i]._center.y, _tiles[i]._center.x, _tiles[i]._center.y - 16);
		LineMake(getMemDC(), _tiles[i]._center.x + 32, _tiles[i]._center.y, _tiles[i]._center.x, _tiles[i]._center.y + 16);
		
		char str[128];
		sprintf_s(str, "%d,%d", _tiles[i]._idX, _tiles[i]._idY);
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{ // 탭누르면 몇콤마 몇인지 보여주려고
			TextOut(getMemDC(), _tiles[i]._rc.left + 20, _tiles[i]._rc.top + 8, str, strlen(str));
		}
	}

	// 설명
	TextOut(getMemDC(), WINSIZEX - 448, 90, "S저장, D로드, F선택타일로 채우기, Z실행취소", strlen("S저장, D로드, F선택타일로 채우기, Z실행취소"));
	TextOut(getMemDC(), WINSIZEX - 448, 110, "1:1번스테이지, 2:2번스테이지, 3: 타이틀로", strlen("1:1번스테이지, 2:2번스테이지, 3: 타이틀로"));
	if (_currentStage == 0) TextOut(getMemDC(), WINSIZEX - 448, 60, "현재:1번스테이지", strlen("현재:1번스테이지"));
	else if (_currentStage == 1) TextOut(getMemDC(), WINSIZEX - 448, 60, "현재:2번스테이지", strlen("현재:2번스테이지"));
}

void mapTool::save()
{ // 저장함수
	if (_currentStage == 0)
	{ // 0일땐 stage1에 저장
		HANDLE file;
		DWORD write;

		file = CreateFile("stage1.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &write, NULL);

		CloseHandle(file);
	}
	if (_currentStage == 1)
	{ // 1일땐 stage2에 저장
		HANDLE file;
		DWORD write;

		file = CreateFile("stage2.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &write, NULL);

		CloseHandle(file);
	}

}

void mapTool::load()
{	// 불러오는함수
	if (_currentStage == 0)
	{  // 0일땐 stage1을 로드
		HANDLE file;
		DWORD read;

		file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &read, NULL);

		CloseHandle(file);
	}
	if (_currentStage == 1)
	{ // 1일땐 stage2를 로드
		HANDLE file;
		DWORD read;

		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &read, NULL);

		CloseHandle(file);
	}
}

void mapTool::tempSave()
{ // 마우스 딱 누를때만 타일이 그려지기전 발동함. temp에 저장
	_tempSaved = true;
	HANDLE file;
	DWORD write;

	file = CreateFile("temp.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &write, NULL);

	CloseHandle(file);
}

void mapTool::tempLoad()
{ // temp를 불러옴
	if (!_tempSaved) return;
	HANDLE file;
	DWORD read;

	file = CreateFile("temp.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &read, NULL);

	CloseHandle(file);
}

void mapTool::fill(int x, int y)
{ // 특정 프레임값으로 전체 칠해주는 함수
	for (int i = 0; i < TILENUMX*TILENUMY; ++i)
	{
		_tiles[i]._frameX = x;
		_tiles[i]._frameY = y;
	}
}

inline POINT mapTool::picking(long x, long y)
{ // 이게 피킹
	int xx; int yy;
	if (2 * y < (x - 320))	return { -1,0 }; // y=1/2x보다 위에있는지 (맵밖 벗어남)
	if (2 * y < -(x - 320))	return { -1,0 }; // y=-1/2x보다 위에있는지 (맵밖 벗어남)
	//-1이면 예외처리됨(키매니저 L버튼 참고)

	// 왜 y=1/2x가 아니라 2y=x로 썼냐면 나눗셈연산이 느리기때문에 이렇게 쓴거임.
	// 320은 TILEWIDTH * TILENUMX / 2 (=맵전체 가로크기의 절반값)와 같은데 부하를 줄이기 위해 계산하고 넣은것임

	 // 64는 타일 높이(TILEHEIGHT)에 양변 2곱한값이며 이만큼씩 이격된(밑으로간) 직선이라 보면 됨
	xx = (2 * y + (x - 320)) / 64; // y절편을 이용한 방식으로 바꾸었음
	if (xx > 9) return { -1,0 }; // 맵밖 벗어난거면 예외처리

	yy = (2 * y - (x - 320)) / 64; // 기울기만 음수고 나머진 상동
	if (yy > 9) return { -1,0 };

	return { xx , yy };
}
