#pragma once

class tile // �׳� ����ü���� ����
{
public:
	int _idX;		//Ÿ���� �ε��� X
	int _idY;		//Ÿ���� �ε��� Y
	int _number;

	POINT _center;	//Ÿ���� ���� ��
	RECT _rc;

	bool _isOpen;	//�����ִ� Ÿ���̴�?
	
	int _frameX;
	int _frameY;


	tile();
	~tile();
};

