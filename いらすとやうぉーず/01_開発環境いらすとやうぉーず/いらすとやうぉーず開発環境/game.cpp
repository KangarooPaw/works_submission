
#include "game.h"
#include "bg.h"
#include "bomb.h"
#include "player.h"
#include "fence.h"
#include "reticule.h"
#include "enemy.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_enemyPopTime = 0;
	m_PopSpeed = 100;
	nPosX = 0;
	nPosY = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
//����������
//=============================================================================
void CGame::Init(void)
{
	//�J�[�\����\��
	ShowCursor(false);
	//�w�i����
	CBg::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	//�{���\������
	CBomb::Create(BOMB_WIDTH / 2, BOMB_HEIGHT / 2);
	//�v���C���[����
	CPlayer::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	//�t�F���X����
	CFence::Create(SCREEN_CENTER_X - 125, SCREEN_CENTER_Y, 0);
	CFence::Create(SCREEN_CENTER_X + 125, SCREEN_CENTER_Y, 0);
	CFence::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y - 125, 1);
	CFence::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y + 125, 1);
	//���e�B�N������
	CReticule::Create(0, 0);
}

//=============================================================================
//�I������
//=============================================================================
void CGame::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	//�G�l�~�[�����^�C��
	m_enemyPopTime++;
	//�G�l�~�[�����^�C�~���O�ȊO�u���C�N
	if (m_enemyPopTime%m_PopSpeed != 0)return;

	//����������
	srand((unsigned)time(NULL));
	//�G�l�~�[�̐���
	for (int nCount = 0; nCount < ENEMY_CONCURRENT; nCount++)
	{
		//��������
		int nDirection = rand() % DIRECTION_MAX;
		//X���AY���ɗ���
		nPosX = rand() % SCREEN_WIDTH;
		nPosY = rand() % SCREEN_HEIGHT;
		//�G�l�~�[����
		switch (nDirection)
		{
		case DIRECTION_UP://��
			CEnemy::Create((float)nPosX, 10.f);
			break;
		case DIRECTION_DOWN://��
			CEnemy::Create((float)nPosX, (float)SCREEN_HEIGHT - 15.f);
			break;
		case DIRECTION_LEFT://��
			CEnemy::Create(10.f, (float)nPosY);
			break;
		case DIRECTION_RIGHT://�E
			CEnemy::Create((float)SCREEN_WIDTH - 15.f, (float)nPosY);
			break;
		}
	}
}
