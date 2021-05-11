//=============================================================================
//�v���C���[����[player.cpp]
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "enemy.h"
#include "scene2d.h"
#include "renderer.h"
#include "mouse.h"
#include "bullet.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	m_move = 5.0f;
	m_bulletTime = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
//��������
//=============================================================================
CPlayer *CPlayer::Create(float nPosX, float nPosY)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init(nPosX, nPosY);
	return pPlayer;
}

//=============================================================================
//�e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PLAYER,					// �t�@�C���̖��O
		&m_pTexture);

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CPlayer::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//����������
//=============================================================================
HRESULT CPlayer::Init(float nPosX, float nPosY)
{
	CScene2D::Init(nPosX, nPosY,PLAYER_WIDTH,PLAYER_HEIGHT);
	CScene2D::BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_PLAYER);
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CPlayer::Update(void)
{
	//�}�E�X�̎擾
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	//�T�E���h�̎擾
	CSound *pSound = CManager::GetSound();
	//�ʒu���̎擾
	D3DXVECTOR3 pos = GetPosition();
	//�}�E�X�J�[�\���ʒu�擾
	POINT point;
	GetCursorPos(&point);
	//�E�B���h�E���̃|�C���^�[����
	ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
	//���a
	double r = sqrtf((PLAYER_WIDTH / 2 ^ 2) + (PLAYER_HEIGHT / 2 ^ 2));
	//�p�x�v�Z
	double angle = atan2(double(point.y - pos.y), double(point.x - pos.x));

	if (pInputMouse->GetMouseTriggerLeft())
	{
		//SE�Đ�
		pSound->Play(CSound::SE_SHOT);
		//�e����
		CBullet::Create(pos.x, pos.y);
	}

	if (pInputMouse->GetMousePressLeft())
	{
		//�ˌ��^�C��
		m_bulletTime++;
		//�ˌ�
		if (m_bulletTime % 10 == 0)
		{
			//SE�Đ�
			pSound->Play(CSound::SE_SHOT);
			//�e����
			CBullet::Create(pos.x, pos.y);
		}
	}
	//���N���b�N��b�ă��Z�b�g
	if (pInputMouse->GetMouseReleaseLeft())
	{
		m_bulletTime = 0;
	}
	//�ʒu�Z�b�g
	SetPosition(pos);
	//�v���C���[�̊p�x
	CScene2D::SetRotVertex(PLAYER_WIDTH, PLAYER_HEIGHT, (float)angle);
	//�v���C���[���]����
	if (point.x < SCREEN_CENTER_X)
	{
		CScene2D::SetRotVertex(PLAYER_WIDTH, -PLAYER_HEIGHT, (float)angle);
	}

	//�����蔻�菈��
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			//Scene2D�̎擾
			CScene2D *pScene2D = (CScene2D*)GetScene(nCntPriority, nCntScene);
			//pScene2D��NULL�Ȃ�R���e�B�j���[
			if (pScene2D == NULL)continue;
			//OBJTYPE���G�l�~�[�Ȃ�R���e�B�j���[
			if (pScene2D->GetObjType() != CEnemy::OBJTYPE_ENEMY)continue;

			//�G�l�~�[�̈ʒu���擾
			D3DXVECTOR3 posEnemy = pScene2D->GetPosition();
			if (pos.x >= posEnemy.x - (ENEMY_WIDTH / 2) && pos.x <= posEnemy.x + (ENEMY_WIDTH / 2) &&
				pos.y >= posEnemy.y - (ENEMY_HEIGHT / 2) && pos.y <= posEnemy.y + (ENEMY_HEIGHT / 2))
			{
				//�G�l�~�[�̃q�b�g����
				((CEnemy*)pScene2D)->HitObject();
				//�v���C���[�̏I������
				Uninit();
				//��ʑJ�ڏ���
				CFade::SetFade(CManager::MODE_RESULT);
			}
		}
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}