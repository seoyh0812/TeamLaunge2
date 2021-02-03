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
	_currentStage = 1;
	createIsoMap(TILEX, TILEY);
	_tempTile.fX = _tempTile.fY = 0;
	_savePopUp = _popUpCount = _modifyingCount = _modifyingNum = 0;
	_pickingPt = { 0,0 };
	_moveUnMove = _seePath = false;
	_brushOn = false;
	_rs = MAX;
	_menuNum = ONE;
	_objName = NONE;
	_objDelOn = false;
	_menuInPt = false;
	
	_playerTile = _enemyTile = -1;

	HANDLE file;
	DWORD read;

	file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);

	for (int i = 0; i < 900; ++i)
	{
		if (_isoTile[i].name == PLAYERFLAG) _playerTile = i;
		else if (_isoTile[i].name == ENEMYFLAG) _enemyTile = i;
	}

	return S_OK;
}

void mapTool::release()
{
}

//�׷��� ���� x, �׷��� ���� y, TILEX �ֱ�, TILEY �ֱ�
void mapTool::createIsoMap(int tileX, int tileY)
{

	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			_isoTile[i * tileX + j].fX = 0;
			_isoTile[i * tileX + j].fY = 0;
			_isoTile[i * tileX + j].gold = 0;
			_isoTile[i * tileX + j].nX = j;
			_isoTile[i * tileX + j].nY = i;

			_isoTile[i * tileX + j].inRect = false;
			_isoTile[i * tileX + j].MUM = MOVE;
			_isoTile[i * tileX + j].name = NONE;

			_isoTile[i * tileX + j].centerX = TILESIZEX * (TILEX + (j - i))/2;
			_isoTile[i * tileX + j].centerY = TILESIZEY * (i + j + 1) / 2;

			_isoTile[i * tileX + j].drawX = _isoTile[i * tileX + j].centerX - TILESIZEX / 2;
			_isoTile[i * tileX + j].drawY = _isoTile[i * tileX + j].centerY - TILESIZEY / 2;
		}
	}
	_isoTile[0].gold = 1000;
}


void mapTool::update()
{
	_pickingPt = picking(_cameraPtMouse.x, _cameraPtMouse.y);
	cameraControl();
	imageInit();
	menuInPt();

	if (_popUpCount > 0) --_popUpCount;
	if (_popUpCount == 0 && _savePopUp != 0)
	{
		_seePath = false;
		_savePopUp = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x > 240 || _ptMouse.y < 580) // �̴ϸ� �� ��������
		{
			if (PtInRect(&_undo, _cameraPtMouse)) tempLoad();
			tempSave();
			if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createTile();
			sampleInTemp();
			save();
			load();
			moveUnMove();
			if (PtInRect(&_fill, _cameraPtMouse) && _tempTile.fX >= 0 && _tempTile.fY >= 0) fill(_tempTile.fX, _tempTile.fY);
			openClose();
			renderSize();
			if (_brushOn) leftRightBt();
			ptInObj();
			if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createObj();
			if (PtInRect(&_objDel, _cameraPtMouse)) objDel();
			if (PtInRect(&_delAll, _cameraPtMouse)) objDelAll();
			if (PtInRect(&_homeBt, _cameraPtMouse)) homeBt();

			if (_ptMouse.x > 132 && _ptMouse.x < 147 && _ptMouse.y>555 && _ptMouse.y < 574)
			{ // õ���ڸ��� Ŭ��
				_modifyingNum = 1;
				_modifyingCount = 300;
			}
			else if (_ptMouse.x > 147 && _ptMouse.x < 162 && _ptMouse.y>555 && _ptMouse.y < 574)
			{ // �����ڸ��� Ŭ��
				_modifyingNum = 2;
				_modifyingCount = 300;
			}
			else if (_ptMouse.x > 162 && _ptMouse.x < 177 && _ptMouse.y>555 && _ptMouse.y < 574)
			{ // �����ڸ��� Ŭ��
				_modifyingNum = 3;
				_modifyingCount = 300;
			}
			else if (_ptMouse.x > 177 && _ptMouse.x < 192 && _ptMouse.y>555 && _ptMouse.y < 574)
			{ // �����ڸ��� Ŭ��
				_modifyingNum = 4;
				_modifyingCount = 300;
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x > 240 || _ptMouse.y < 580) // �̴ϸ� �� ��������
		{
			if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createTile();
			ptInObj();
			if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createObj();
		}
	}

	ptInIso();

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == PLAYERFLAG) _playerTile = -1;
		if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == ENEMYFLAG) _enemyTile = -1;
		_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = NONE;
		_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = MOVE;	//������Ʈ��ġ�� �ڵ����� �𹫺갡 ����� ���ﶧ�� ����� �ٲ��ִ°� �߰���
		InvalidateRect(_hWnd, NULL, false);
	}


	numberInput();
}

void mapTool::render()
{
	imageRender();
	
	//�Ʒ��� ���ǻ� ���� ���ں��̰��ϴ°�
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


	sprintf_s(str, "�۾����� �������� : %d ��������, ���� ��� : %d ", _currentStage, _isoTile[0].gold);
	TextOut(getMemDC(), CAMX + 100, CAMY + 100, str, strlen(str));
}



inline POINT mapTool::picking(long x, long y)
{ // �̰� ��ŷ
	int xx; int yy;
	if (2 * y < (x - 960))	return { -1,0 }; // y=1/2x���� �����ִ��� (�ʹ� ���)
	if (2 * y < -(x - 960))	return { -1,0 }; // y=-1/2x���� �����ִ��� (�ʹ� ���)
	//-1�̸� ����ó����(Ű�Ŵ��� L��ư ����)

	// �� y=1/2x�� �ƴ϶� 2y=x�� ��ĸ� ������������ �����⶧���� �̷��� ������.
	// 320�� TILEWIDTH * TILEX / 2 (=����ü ����ũ���� ���ݰ�)�� ������ ���ϸ� ���̱� ���� ����ϰ� ��������

	 // 64�� Ÿ�� ����(TILEHEIGHT)�� �纯 2���Ѱ��̸� �̸�ŭ�� �̰ݵ�(�����ΰ�) �����̶� ���� ��
	xx = (2 * y + (x - 960)) / 64; // y������ �̿��� ������� �ٲپ���
	// xx = ((y + 1/2*(x - 960)) / 32
	// (x��ǥ) = ((y + 1/2 *(x - ��x����)) / Ÿ�ϳ���
	//           �ѤѤѤѤѤѤѤѤѤѤѤѤ�
	//           ��>�� �κ��� y����(h)
	if (xx > 29) return { -1,0 }; // �ʹ� ����Ÿ� ����ó��

	yy = (2 * y - (x - 960)) / 64; // ���⸸ ������ ������ ��
	// yy = ((y - 1/2*(x - 960)) / 32
	// (y��ǥ) = ((y - 1/2 *(x - ��x����)) / Ÿ�ϳ���
	//           �ѤѤѤѤѤѤѤѤѤѤѤѤ�
	//           ��>�� �κ��� y����(h)
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}

