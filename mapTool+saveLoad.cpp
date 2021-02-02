#include "stdafx.h"
#include "mapTool.h"

void mapTool::tempSave()
{// ���콺 �� �������� Ÿ���� �׷������� �ߵ���. temp�� ����
	_tempSaved = true;
	HANDLE file;
	DWORD write;

	file = CreateFile("temp.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &write, NULL);

	CloseHandle(file);
}

void mapTool::tempLoad()
{// temp�� �ҷ���
	if (!_tempSaved) return;
	HANDLE file;
	DWORD read;

	file = CreateFile("temp.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);

	CloseHandle(file);
}

void mapTool::save()
{
	if (PtInRect(&_saveBt, _cameraPtMouse))
	{
		aStarPath(0, 899); // �ӽ÷�. ������θ� aStarPath(_playerTile, _enemyTile)��.
		_seePath = true;
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