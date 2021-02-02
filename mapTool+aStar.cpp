#include "stdafx.h"
#include "mapTool.h"

vector<int> mapTool::aStarPath(int fromTileNum, int toTileNum)
{
	_path.clear();
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();
	for (int i = 0; i < 900; ++i)
	{
		tagMAStarTile* aStarTile = new tagMAStarTile;
		aStarTile->tileNum = i;
		aStarTile->parentNodeTileNum = -1;
		aStarTile->totalCost = 0;
		aStarTile->costFromStart = 0;
		aStarTile->costToGoal = 0;
		aStarTile->isOpen = true;
		_vTotalList.push_back(aStarTile);
	}
	_stop = 0;
	_startTile = fromTileNum;
	_endTile = toTileNum;
	_currentTile = _startTile;
	pathFinder(_currentTile);

	return _path;
}

// #############################################################

vector<tagMAStarTile*> mapTool::addOpenList(int currentTile)
{
	int startX = currentTile % 30 - 1;
	int startY = currentTile / 30 - 1;

	for (int i = 0; i < 3; ++i)
	{
		//// ############ ���� �������� #####################
		if (startY + i < 0)			continue;
		if (startY + i >= 30)		continue;
		for (int j = 0; j < 3; ++j)
		{
			if (startX + j < 0)		continue;
			if (startX + j >= 30)	continue;

			int checkIndex = (startY + i) * 30 + (startX + j);
			tagMAStarTile* aStarTile = _vTotalList[checkIndex];

			//����ó��!
			if (!aStarTile->isOpen) continue;
			if (_isoTile[checkIndex].MUM == UNMOVE) continue;
			if (checkIndex == _startTile) continue;

			// ##################���� ����#############################
			int nodeTop;
			if (startY < 0)				nodeTop = 1;
			else nodeTop = _isoTile[(startY * 30) + startX + 1].MUM;
			// ������������ �������� ������ ���� �������� i==0�� i==2�Ʒ� j==0�� j==2����
			if (i == 0 && nodeTop == 1)	continue;
			int nodeBottom;
			if (startY + 2 >= 30)	nodeBottom = 1;
			else nodeBottom = _isoTile[(startY * 30) + startX + 61].MUM;
			// �Ʒ����������� ���ʾƷ��� ������ �Ʒ��� ��������
			if (i == 2 && nodeBottom == 1)	continue;
			int nodeLeft;
			if (startX < 0)				nodeLeft = 1;
			else nodeLeft = _isoTile[(startY * 30) + startX + 30].MUM;
			// ���ʸ��������� �������� ���ʾƷ��� ��������
			if (j == 0 && nodeLeft == 1)	continue;
			int nodeRight;
			if (startX + 2 >= 30)	nodeRight = 1;
			else nodeRight = _isoTile[(startY * 30) + startX + 32].MUM;
			// �����ʸ��������� ���������� ������ �Ʒ��� ��������
			if (j == 2 && nodeRight == 1)	continue;


			//���� Ÿ���� ��� �������ش�
			aStarTile->parentNodeTileNum = _currentTile;

			bool addObj = true;
			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == aStarTile)
				{ // �ִ°Ÿ� �߰�����
					addObj = false;
					break;
				}
			}
			if (!addObj) continue;

			_vOpenList.push_back(aStarTile);
		}
	}

	return _vOpenList;
}

void mapTool::pathFinder(int currentTile)
{
	//��κ���� �ſ� ���� �ϱ� ���ؼ� ������ ��κ���� ��
	int tempTotalCost = 5000;
	tagMAStarTile* tempTile = nullptr;

	bool changed = false;

	//���� �ִ� ���� ���� ���� ���ο��� ���� ���� ��θ� �̾ƾ��Ѵ�
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{ // ���⼭ �ֺ����� ������ ���ÿ� �������� �ѿ��¸���Ʈ�� �������°�
		_vOpenList[i]->costToGoal = (abs(_endTile % 30 - _vOpenList[i]->tileNum % 30) +
			abs(_endTile / 30 - _vOpenList[i]->tileNum / 30)) * 11;

		int cost;

		if (_vOpenList[i]->tileNum + 1 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 1 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum + 30 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 30 == _vOpenList[i]->parentNodeTileNum) cost = 9;
		else if (_vOpenList[i]->tileNum + 31 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 31 == _vOpenList[i]->parentNodeTileNum) cost = 8;
		else if (_vOpenList[i]->tileNum + 29 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 29 == _vOpenList[i]->parentNodeTileNum) cost = 16;

		_vOpenList[i]->costFromStart = cost;

		//F = G + H �ϱ�~ 
		_vOpenList[i]->totalCost = _vOpenList[i]->costToGoal + _vOpenList[i]->costFromStart;

		//��κ��(F)�� ���� ���� �ַ� ��� �������ش�
		if (tempTotalCost > _vOpenList[i]->totalCost)
		{
			tempTotalCost = _vOpenList[i]->totalCost;
			tempTile = _vOpenList[i];
		} // ��������Ʈ�� ��κ�� ���������ְ� Ž���Ǿ� ����Ÿ�Ϸ� ����

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{ // ��������Ʈ�� ����Ÿ���� �ִٸ� -> ���� ��������߿����� ��밪�� ������ ����?
				addObj = false;
				changed = true;
				break;
			} // �Ұ������ �������� ������ false�� ����� �������� �ȵ���������
		}
		_vOpenList[i]->isOpen = false; // ����
		if (!addObj) continue;

		_vOpenList.push_back(tempTile); // �߰��ؾߵȴٰ� ������ �߰��ϴ°�
	}

	// ############## ��� ��ã���� ������ �Լ� #####################
	if (!changed)
	{// �ƹ��͵� ������ϰ� ������ ������(?) ���Ҵٸ� ������
		_stop = true;
		return;
	}

	//�����ߴٸ�
	if (tempTile->tileNum == _endTile)
	{
		while (_currentTile != _startTile)
		{
			_path.push_back(_currentTile);
			_currentTile = _vTotalList[_currentTile]->parentNodeTileNum;
		}
		_stop = true;
		return;
	}

	_vCloseList.push_back(tempTile);
	// ����Ÿ���� ��������Ʈ�� �ְ� ���¸���Ʈ���� ����. �׸��� ����Ÿ�Ϸ� ����
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile->tileNum;

	if (!_stop) pathFinder(_currentTile);
}