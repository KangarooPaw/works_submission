//--------------------------
//�n�C�X�R�A����[hiscore.h]
//--------------------------
#ifndef _GAME_H_
#define _GAME_H_

//--------------------------
//�N���X
//--------------------------
class CGame
{
public:
	CGame();		//�R���X�g���N�^
	~CGame();	//�f�X�g���N�^

	void Init(void);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����

private:
	//�����̍\����
	typedef enum
	{
		DIRECTION_UP = 0,//��
		DIRECTION_DOWN,//��
		DIRECTION_LEFT,//��
		DIRECTION_RIGHT,//�E
		DIRECTION_MAX//�ő�l
	}DIRECTION;

	int m_enemyPopTime;//�G�l�~�[�����^�C�~���O
	int m_PopSpeed;//�G�l�~�[�������x
	int nPosX, nPosY;//�G�l�~�[�������̍��W
};
#endif //_GAME_H_