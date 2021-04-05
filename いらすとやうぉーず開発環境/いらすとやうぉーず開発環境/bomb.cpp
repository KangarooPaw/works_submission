//=============================================================================
//���e����[bomb.cpp]
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bomb.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "mouse.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CBomb::m_pTexture = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBomb::CBomb(int nPriority)
{
	m_bUse = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBomb::~CBomb()
{
}

//=============================================================================
//��������
//=============================================================================
CBomb * CBomb::Create(float nPosX, float nPosY)
{
	CBomb *pBomb;
	pBomb = new CBomb;
	pBomb->Init(nPosX, nPosY);
	return pBomb;
}

//=============================================================================
//�e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBomb::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BOMB,					// �t�@�C���̖��O
		&m_pTexture);
	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CBomb::Unload(void)
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
HRESULT CBomb::Init(float nPosX, float nPosY)
{
	CScene2D::Init(nPosX, nPosY, BOMB_WIDTH, BOMB_HEIGHT);
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CBomb::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CBomb::Update(void)
{
	//�}�E�X�̎擾
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	D3DXVECTOR3 pos = GetPosition();
	if (pInputMouse->GetMouseTriggerRight())
	{
		if (m_bUse == false)
		{
			for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
			{
				for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
				{
					CScene2D *pScene2D = (CScene2D*)GetScene(nCountpriority, nCntScene);
					if (pScene2D != NULL)
					{
						D3DXVECTOR3 posEnemy = pScene2D->GetPosition();
						if (pScene2D->GetObjType() == CEnemy::OBJTYPE_ENEMY)
						{
							for (int nCnt = 0; nCnt < ENEMY_LIFE; nCnt++)
							{
								((CEnemy*)pScene2D)->HitBullet();
							}
							m_bUse = true;
						}
					}
				}
			}
		}
	}
	if (m_bUse == true)Uninit();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CBomb::Draw(void)
{
	CScene2D::Draw();
}
