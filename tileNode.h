#pragma once
//�� Ÿ���� ������ 32�� 32 X 32
#define TILESIZE 32

//Ÿ�� ���� ���� 20�� ���� 20��
#define TILEX 20
#define TILEY 20

//640 X 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�ϼ�(����Ÿ��) ����
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//Ÿ�Ͽ� �Ӽ��� �Űܺ���
//enum���� �ϸ� ���ϴ�.. �������� ��Ʈ�ʵ���� �����ִ°���

//�䷱ ���°� ��Ʈ�ʵ��ε� ������ �޸� �Ʋ��Ʋ�
//�������� �Ʋ� ���ٰ� ���� ������.. ��� �� ��ġ�°� ��..
#define ATTR_UNMOVE 0x00000001
#define ATTR_FROZEN 0x00000002
#define ATTR_SWAMP  0x00000004
#define ATTR_POISON 0x00000008


enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_NONE
};

//��ġ(������, ���� ��ġ ���)
enum POS
{
	POS_FLAG1, POS_FLAG2,
	POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;		//����
	OBJECT obj;				//������Ʈ
	RECT rc;				//��Ʈ
	int terrainFrameX;		//Ÿ�� ��ȣ(�ִϸ��̼� ������ ��ȣ �����ϸ��)
	int terrainFrameY;
	int objFrameX;			//������Ʈ ��ȣ (���� ����)
	int objFrameY;
};

//���� Ÿ�� ����ü(�ȷ�Ʈ Ÿ��)
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

