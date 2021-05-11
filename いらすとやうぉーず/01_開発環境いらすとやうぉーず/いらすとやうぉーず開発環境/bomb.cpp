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
	//�E�N���b�N�Ŏ��s�A��������Ă���G��S����
	if (pInputMouse->GetMouseTriggerRight())
	{
		for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				//Scene2D���擾
				CScene2D *pScene2D = (CScene2D*)GetScene(nCountpriority, nCntScene);
				//pScene2D��NULL�Ȃ�R���e�B�j���[
				if (pScene2D == NULL)continue;
				//OBJTYPE��ENEMY�ȊO�Ȃ�R���e�B�j���[
				if (pScene2D->GetObjType() != CEnemy::OBJTYPE_ENEMY)continue;	
				for (int nCnt = 0; nCnt < ENEMY_LIFE; nCnt++)
				{
					((CEnemy*)pScene2D)->HitBullet();
				}
				//��x�g������true
				m_bUse = true;
			}
		}
	}
	//��x�g������I��
	if (m_bUse == true)Uninit();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CBomb::Draw(void)
{
	CScene2D::Draw();
}
