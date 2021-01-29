#pragma once
#include "gameNode.h"

enum BELONG
{
	PLAYER,
	ENEMY
};

enum STATE
{
	WALK,		// ��� ������ ���� ������
	ATTACKWAIT,	// ���� �߰��Ͽ� �������� ����ϴ� ����
	ATTACK,		// �����ҋ�. Ư�������ӿ��� ����������
	DEAD		// �̰� ������ ���Ϳ��� ����
};

class unit : public gameNode
{
protected:
	int _ID;
	// ############ IDǥ ##################
	// ���� ���鶧 ������ȣ ������ ������ ������� �Ȱ�ĥ��. ���ָ��鶧 �߰�
	// 1 : ���۸�(��50%���ϸ� �����2��)
	// 2 : ����
	// 3 : �ù�(��׷�)
	// 4 : ���÷�(����)
	// 5 : ���
	// 6 : ��ƺ��
	// 7 : �ذ񺴻�
	// 8 : ��Ʈ
	// ####################################

	int _frameCount;	// �����ӿ� ī��Ʈ
	int _frame;			// ����������
	// 8���� �������̹����� frameY�� ���̰�(bmp���Ͽ��� ���ι������� �ִϸ��̼�)
	// �ƴϸ�(DEAD) frameX�� ���δ�(bmp���Ͽ��� ���ι������� �ִϸ��̼�)
	int _maxFrame;
	// ��������. ���޽� �ѱ�ų� ���¹ٲٰų� �ϱ� ������.
	
	BELONG _belong;	// �����Ҽ�����(�÷��̾� �ƴ� ���)
	STATE _state;	// ���� ����	

	float _x;	float _y;
	int _width; int _height;
	RECT _rc; // _rc = RectMakeCenter(_x, _y, _width, _height);
	// ��Ʈũ��� �ٲ��� ���� �ϳ��� ���޼����� ���ô�..
	RECT _rangeRc; // ��Ÿ���Ʈ. ������ width���� �� �� ũ��
	// �̰� ����� �̵����� �½�����Ʈ �Ϸ��� �ִ°�
	RECT _focusRc; // ������Ʈ. Ÿ����� �۷� ���Բ��Ϸ���
	// �ٰŸ� �����̶� ����� Ŀ�ߵ�.


	image* _image;

	float _destX; float _destY; // ������
	float _angle;	// �������� ������ ����(8�����̹����� ������x��꿡�� �̿�)
	int _frameDirection; // �ޱۿ� ���� �����ӵ���(0~7)

	float _speed;	// �̵��ӵ�
	
	int _delay;		// �����̰� 0�϶� �����ϵ��� ����.
	int _maxDelay;	// ����ӵ�(�� �ֱ�� �ѹ澿 ġ����). 60�̸� 1�ʿ� �ѹ澿 ������

	float _damage;	// ������(�̰� ���ͼ�Ʈ���� ���ڷ� ����)

	float _HP;	//����ü��
	float _maxHP;		//�ִ�ü��

	int _target;
	// ���Ϳ� ���° ��븦 Ÿ������ ��Ҵ���?
	// ���� �� Ÿ���� �������°� �Ǹ� ���ͼ�Ʈ Ŭ��������
	// ���������� �� �������� Ÿ������ִ� �����
	// Ÿ�ٹ�ȣ�� -1�� �ٲ�����մϴ�.(���ؾȵǸ� ����)
	// �ȱ׷��� ���� ������� �����ؼ� ���� �������� ������..

	int _attackIndex; // ���û��¿��� ������ӿ��� ������������
	bool _attackReady;
	// ���ݻ��¿��� �����ӹٲ����� Ư�� �������̸�
	// (�� �����̾�� �ѹ��� �ߵ�)
	// �̰� ������ ���ͼ�Ʈ���� ���ݿ����ϸ鼭 �̰� ����
	bool _erase;
	// �����ִϸ��̼� ������ �̰� ������ ���ָŴ������� ����

	int _tileNum;
	// ���� �ֱ� ���Ÿ�ϱ��� ��Ҵ���
	// �װſ����� ������ �ٲ���. �÷��̾�� �������� ���
	// ���̸� ������� �⵵�� ��

	int _deathDuration;
	// �׾����� ��ü(?)�� ġ�����µ����� �ɸ��� ī��Ʈ

	bool _active;

	int _count;
	bool _used;

public:
	unit();
	~unit();

	virtual HRESULT init(BELONG belong, float x, float y);
	// ��������?  �׸��� ������ġ
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	// ���������� ���̴°͵��� ���ָ��� �ֱ� ���ŷο��
	// �� �Լ��� ���ָ� ��
	void commonInit();		// ���������Ѱ� ���⼭ �̴�
	void commonUpdate();	// �������� �ൿ���
	// �߿���) �Լ��� ���⼭ ���õ�����
	// ����� ���Ŭ���������� �̴� �� ������Ʈ�� ���� �ִ°���.
	// �Լ� ���� ���⼭ ���Ǹ� ���� �س�����
	// �̴ֿ��� ���� ������ �ֱ⸸�ϸ� (�� ������..)
	// �� ������ ���� �˾Ƽ� �� �ൿ�ϵ��� �غ�������(�װ� �� ���� ��)
	// �׷��ٺ��� ��������� ���ϰ� ������ ���عٶ�(���� ���͵� ������)

	// ���뷻���� �ϰ� �;����� �̹������� ��ġ����������ؼ�

	void progressBarRender();
	virtual void reRender();
	void moveCancel(); // �̵������״� �ٽ� �����ִ� �Լ�(�ѹ�)

	virtual void setState(STATE state) = 0;
	// �̰� ���ֵ鸶�� �̹����� �ٸ��Ƿ� ���� ����� ���ô�.

	void RMC();
	// ��Ʈ����ũ���� ���ϰ� �Ϸ���

	// ���͵鵵 ���������ϰ� ����
	int getID() { return _ID; }
	BELONG& getBelong() { return _belong; }
	// �̰� ������ ���� ������ ������ ���������Ÿ�..
	STATE getState() { return _state; }
	// setState�Լ��� �����Ƿ� �̰ɷ� �����ϸ� �ȵ�(������X)
	float& getX() { return _x; }
	float& getY() { return _y; }
	void setDest(float destX, float destY); // ��ǥ������ �̰ɷ��Ұ���
	float getAngle1() { return _angle; }	// �� �ޱۿ� 1�� �ٳĸ� getAngle�Լ��� �̹��ֱ⶧����..
	void setAngle(float angle);				// ���������� �̰ɷ� �Ұ���
	int& getDelay() { return _delay; }
	float getDamage() { return _damage; }
	float& getHP() { return _HP; }
	int& getTarget() { return _target; }
	bool& getAttackReady() { return _attackReady; }
	bool getErase() { return _erase; }
	int getWidth() { return _width; }
	int getHeight() { return _height; }
	RECT getRect() { return _rc; }
	RECT getRangeRect() { return _rangeRc; }
	RECT getFocusRect() { return _focusRc; }
	int& getTileNum() { return _tileNum; }
	bool& getActive() { return _active; }
	float getSpeed() { return _speed; }
};

