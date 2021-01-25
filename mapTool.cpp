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


	// Ÿ�Ͽ� idX, idY�� ������� �ְ� �ʱ�ȭ
	for (int i = 0; i < TILENUMX * TILENUMY; ++i)
	{ // Ÿ�ϼ��ڸ�ŭ �ε��� ��ȣ�� �ο����ش�
		_tiles[i]._idX = i % TILENUMX;
		_tiles[i]._idY = i / TILENUMY;
		// ����� �ε�����ȣ�� ���� ������ ��������
		_tiles[i]._center = PointMake(TILENUMX*TILEWIDTH / 2 + (_tiles[i]._idX - i / TILENUMY)*TILEWIDTH / 2,
			(_tiles[i]._idX + _tiles[i]._idY) * 16 + (TILEHEIGHT / 2));
		// ������������ Ÿ�ϳʺ� Ÿ�ϳ��̷� ��Ʈ����ũ(�̰� Ÿ���� ���� ��Ʈ�� Ÿ�Ϻ��� 2�� ũ��)
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
		if (_waccess_s(L"./stage1.map", 0) == 0) load(); // stage1.map�� �����ϸ� �ε���
		else fill(0, 0);
		// �������� ������ �ε��ϰ� �ƴϸ� �Ϲ�Ÿ�Ϸ� ä��
		// waccess ������ ������ 0�� ��ȯ�ϴ� �Լ�
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{ // ���� ����
		_currentStage = 1;
		if (_waccess_s(L"./stage2.map", 0) == 0) load();
		else fill(0, 0);
	}
	if (KEYMANAGER->isOnceKeyDown('3')) SCENEMANAGER->changeScene("Ÿ��Ʋ��");
	if (KEYMANAGER->isOnceKeyDown('S')) save(); // ����
	if (KEYMANAGER->isOnceKeyDown('D'))	load(); // �ε�
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		tempSave(); // �ʼ����ϱ��� ��¦ ������ ������ �Ѵ�
		fill(_selectTileX, _selectTileY); // ���õȰɷ� ä��
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))	tempLoad();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{ // �ʼ����ϱ��� ��¦ ������ ������ �Ѵ�
		if (_ptMouse.x < 640 && _ptMouse.y < 320) tempSave();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{ // ��ư �������
		if (_ptMouse.x > 640 && _ptMouse.y < 32)
		{ // �ȷ�Ʈ�� ��������� -> ��Ÿ�� ���������� ������
			_selectTileX = (_ptMouse.x - 640) / 64;
			_selectTileY = _ptMouse.y / 32;
		}
		else if (_ptMouse.x < 640 && _ptMouse.y < 320)
		{ // �������� ���� ����� -> ��ŷ�Ͽ� �ŵ� �׷��ش�
			POINT point = picking(_ptMouse.x, _ptMouse.y); // ��ŷ�Ͽ� ����Ʈ ����
			if (point.x == -1) goto ONE; // ONE�ִµ����� �ð� ������. ��ŷ�Ѱ� {-1,0}�϶� ����ó���ϴ� �κ���
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
	{ // �� Ÿ�ϸ��� �����Ӵ�� ����
		IMAGEMANAGER->findImage("tile")->frameRender(getMemDC(),
			_tiles[i]._rc.left, _tiles[i]._rc.top, _tiles[i]._frameX, _tiles[i]._frameY);

		// ������ �� �׸���
		LineMake(getMemDC(), _tiles[i]._center.x - 32, _tiles[i]._center.y, _tiles[i]._center.x, _tiles[i]._center.y - 16);
		LineMake(getMemDC(), _tiles[i]._center.x - 32, _tiles[i]._center.y, _tiles[i]._center.x, _tiles[i]._center.y + 16);
		LineMake(getMemDC(), _tiles[i]._center.x + 32, _tiles[i]._center.y, _tiles[i]._center.x, _tiles[i]._center.y - 16);
		LineMake(getMemDC(), _tiles[i]._center.x + 32, _tiles[i]._center.y, _tiles[i]._center.x, _tiles[i]._center.y + 16);
		
		char str[128];
		sprintf_s(str, "%d,%d", _tiles[i]._idX, _tiles[i]._idY);
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{ // �Ǵ����� ���޸� ������ �����ַ���
			TextOut(getMemDC(), _tiles[i]._rc.left + 20, _tiles[i]._rc.top + 8, str, strlen(str));
		}
	}

	// ����
	TextOut(getMemDC(), WINSIZEX - 448, 90, "S����, D�ε�, F����Ÿ�Ϸ� ä���, Z�������", strlen("S����, D�ε�, F����Ÿ�Ϸ� ä���, Z�������"));
	TextOut(getMemDC(), WINSIZEX - 448, 110, "1:1����������, 2:2����������, 3: Ÿ��Ʋ��", strlen("1:1����������, 2:2����������, 3: Ÿ��Ʋ��"));
	if (_currentStage == 0) TextOut(getMemDC(), WINSIZEX - 448, 60, "����:1����������", strlen("����:1����������"));
	else if (_currentStage == 1) TextOut(getMemDC(), WINSIZEX - 448, 60, "����:2����������", strlen("����:2����������"));
}

void mapTool::save()
{ // �����Լ�
	if (_currentStage == 0)
	{ // 0�϶� stage1�� ����
		HANDLE file;
		DWORD write;

		file = CreateFile("stage1.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &write, NULL);

		CloseHandle(file);
	}
	if (_currentStage == 1)
	{ // 1�϶� stage2�� ����
		HANDLE file;
		DWORD write;

		file = CreateFile("stage2.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &write, NULL);

		CloseHandle(file);
	}

}

void mapTool::load()
{	// �ҷ������Լ�
	if (_currentStage == 0)
	{  // 0�϶� stage1�� �ε�
		HANDLE file;
		DWORD read;

		file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &read, NULL);

		CloseHandle(file);
	}
	if (_currentStage == 1)
	{ // 1�϶� stage2�� �ε�
		HANDLE file;
		DWORD read;

		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &read, NULL);

		CloseHandle(file);
	}
}

void mapTool::tempSave()
{ // ���콺 �� �������� Ÿ���� �׷������� �ߵ���. temp�� ����
	_tempSaved = true;
	HANDLE file;
	DWORD write;

	file = CreateFile("temp.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &write, NULL);

	CloseHandle(file);
}

void mapTool::tempLoad()
{ // temp�� �ҷ���
	if (!_tempSaved) return;
	HANDLE file;
	DWORD read;

	file = CreateFile("temp.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &read, NULL);

	CloseHandle(file);
}

void mapTool::fill(int x, int y)
{ // Ư�� �����Ӱ����� ��ü ĥ���ִ� �Լ�
	for (int i = 0; i < TILENUMX*TILENUMY; ++i)
	{
		_tiles[i]._frameX = x;
		_tiles[i]._frameY = y;
	}
}

inline POINT mapTool::picking(long x, long y)
{ // �̰� ��ŷ
	int xx; int yy;
	if (2 * y < (x - 320))	return { -1,0 }; // y=1/2x���� �����ִ��� (�ʹ� ���)
	if (2 * y < -(x - 320))	return { -1,0 }; // y=-1/2x���� �����ִ��� (�ʹ� ���)
	//-1�̸� ����ó����(Ű�Ŵ��� L��ư ����)

	// �� y=1/2x�� �ƴ϶� 2y=x�� ��ĸ� ������������ �����⶧���� �̷��� ������.
	// 320�� TILEWIDTH * TILENUMX / 2 (=����ü ����ũ���� ���ݰ�)�� ������ ���ϸ� ���̱� ���� ����ϰ� ��������

	 // 64�� Ÿ�� ����(TILEHEIGHT)�� �纯 2���Ѱ��̸� �̸�ŭ�� �̰ݵ�(�����ΰ�) �����̶� ���� ��
	xx = (2 * y + (x - 320)) / 64; // y������ �̿��� ������� �ٲپ���
	if (xx > 9) return { -1,0 }; // �ʹ� ����Ÿ� ����ó��

	yy = (2 * y - (x - 320)) / 64; // ���⸸ ������ ������ ��
	if (yy > 9) return { -1,0 };

	return { xx , yy };
}
