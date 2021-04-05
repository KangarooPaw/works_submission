//=============================================================================
//�e����[bullet.cpp]
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "sound.h"

//=============================================================================
//�X�^�e�B�b�N�ϐ�������
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nPriority)
{
	m_move = 5.f;
	m_angleX =0.f;
	m_angleY = 0.f;
	m_hit = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
	
}

//=============================================================================
//��������
//=============================================================================
CBullet *CBullet::Create(float nPosX, float nPosY)
{
	CBullet *pBullet;
	pBullet = new CBullet;
	pBullet->Init(nPosX, nPosY);
	//pos�̎擾
	D3DXVECTOR3 pos = pBullet->GetPosition();
	//�}�E�X�J�[�\���ʒu�擾
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
	//�p�x�v�Z
	double angle = atan2(double(point.y -pos.y ), double( point.x -pos.x));
	pBullet->m_angleX= (float)cos(angle);
	pBullet->m_angleY= (float)sin(angle);

	return pBullet;
}

//=============================================================================
//�e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BULLET,					// �t�@�C���̖��O
		&m_pTexture);
	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CBullet::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//����������
//=============================================================================
HRESULT CBullet::Init(float nPosX, float nPosY)
{

	CScene2D::Init(nPosX, nPosY ,BULLET_WIDTH,BULLET_HEIGHT);	
	CScene2D::BindTexture(m_pTexture);
	
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BULLET);
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}
   
//=============================================================================
//�X�V����
//=============================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	pos.x += m_angleX*m_move;
	pos.y += m_angleY*m_move;

	SetPosition(pos);
	CScene2D::Update();
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene2D *pScene2D = (CScene2D*)GetScene(nCountpriority,nCntScene);
			if (pScene2D != NULL)
			{
				//�G�l�~�[�̈ʒu�擾
				D3DXVECTOR3 posEnemy = pScene2D->GetPosition();
				if (pScene2D->GetObjType() == CEnemy::OBJTYPE_ENEMY)
				{
					//�G�l�~�[�ɓ�����������
					if (pos.x >= posEnemy.x - (ENEMY_WIDTH / 2) && pos.x <= posEnemy.x + (ENEMY_WIDTH / 2) &&
						pos.y >= posEnemy.y - (ENEMY_HEIGHT / 2) && pos.y <= posEnemy.y + (ENEMY_HEIGHT / 2))
					{
						((CEnemy*)(pScene2D))->HitBullet();
						CExplosion::Create(pos.x, pos.y);
						m_hit = true;
					}
				}
			}
		}
	}
	//�e����ʊO�ɏo���Ƃ�
	if (pos.x<-5 || pos.x>SCREEN_WIDTH + 5 ||
		pos.y<-5 || pos.y>SCREEN_HEIGHT + 5)
	{
		m_hit = true;
	}
	//�e���G�ɓ�����A��ʊO�ɏo���
	if (m_hit == true)
	{	
		m_hit = false;
		CScene2D::Uninit();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}