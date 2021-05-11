//=============================================================================
//�G�l�~�[����[enemy.cpp]
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "score.h"
#include "sound.h"

//=============================================================================
//�X�^�e�B�b�N�ϐ�������
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;

//-------------------------------------------
//�R���X�g���N�^
//-------------------------------------------
CEnemy::CEnemy(int nPriority)
{
	m_move = 0.5;	//�ړ���
	m_nLife = ENEMY_LIFE;	//�̗�
}

//-------------------------------------------
//�f�X�g���N�^
//-------------------------------------------
CEnemy::~CEnemy()
{

}

//-------------------------------------------
//�e�N�X�`���ǂݍ���
//-------------------------------------------
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ENEMY,							// �t�@�C���̖��O
		&m_pTexture);
	return S_OK;
}

//-------------------------------------------
// �e�N�X�`���̔j��
//-------------------------------------------
void CEnemy::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-------------------------------------------
//�N���G�C�g
//-------------------------------------------
CEnemy * CEnemy::Create(float nPosX, float nPosY)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy;
	pEnemy->Init(nPosX, nPosY);
	return pEnemy;
}

//-------------------------------------------
//����������
//-------------------------------------------
HRESULT CEnemy::Init(float nPosX, float nPosY)
{
	CScene2D::Init(nPosX, nPosY,ENEMY_WIDTH,ENEMY_HEIGHT);
	BindTexture(m_pTexture);
	if (nPosX < SCREEN_CENTER_X)
	{
		CScene2D::SetEnemyTex(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (nPosX > SCREEN_CENTER_X)
	{
		CScene2D::SetEnemyTex(0.0f, 1.0f, 0.0f, 1.0f);
	}
	//�I�u�W�F�N�g�^�C�v��ݒ�
	SetObjType(OBJTYPE_ENEMY);
	return S_OK;
}

//-------------------------------------------
//�I������
//-------------------------------------------
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void CEnemy::Update(void)
{
	//�ʒu���擾
	D3DXVECTOR3 pos=GetPosition();
	//��ʒ����Ɍ������Đi��
	double angle = atan2(double(SCREEN_CENTER_Y -pos.y ), double(SCREEN_CENTER_X -pos.x ));
	//�i�s�����v�Z
	pos.x +=(float)cos(angle)*m_move;
	pos.y += (float)sin(angle)*m_move;
	//�ʒu���Z�b�g
	SetPosition(pos);
	CScene2D::Update();
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//-------------------------------------------
//�e�ɓ����������̏���
//-------------------------------------------
void CEnemy::HitBullet(void)
{
	CSound *pSound = CManager::GetSound();
	//�e������������̗͂����炷
	m_nLife--;
	//1�x�ڂ̃q�b�g����
	CScene2D::SetColor(0);
	//�̗͂��Ȃ��Ȃ�����
	if (m_nLife > 0)return;

	for (int nCountPriority = 0; nCountPriority < PRIORITY; nCountPriority++)
	{
		for (int nCountScene = 0; nCountScene < MAX_POLYGON; nCountScene++)
		{
			//Scene2D�̎擾
			CScene2D *pScene2D = (CScene2D*)GetScene(nCountPriority, nCountScene);
			//pScene2D��NULL�Ȃ�R���e�B�j���[
			if (pScene2D == NULL)continue;
			//OBJTYPE��SCORE�ȊO�Ȃ�R���e�B�j���[
			if (pScene2D->GetObjType() != CScore::OBJTYPE_SCORE)continue;
			//�X�R�A+1
			((CScore*)pScene2D)->AddScore(1);
		}
	}
	//SE�Đ�
	pSound->Play(CSound::SE_EXPLOSION);
	//�I������
	CScene2D::Uninit();
}

//-------------------------------------------
//�e�ȊO�ɓ����������̏���
//-------------------------------------------
void CEnemy::HitObject(void)
{
	//Sound���擾
	CSound *pSound = CManager::GetSound();
	//SE���Đ�
	pSound->Play(CSound::SE_EXPLOSION);
	//�I������
	Uninit();
}
