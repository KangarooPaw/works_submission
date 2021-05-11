//=============================================================================
//�J�ڂ𑣂������̕`�揈��[transition.cpp]
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "transition.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTransition::m_pTexture = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTransition::CTransition()
{
	m_pScene2D = NULL;
	m_nAlpha = 255;
	m_bMinus = true;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTransition::~CTransition()
{
}

//=============================================================================
//�e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CTransition::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TRANSITON,								// �t�@�C���̖��O
		&m_pTexture);
	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CTransition::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//��������
//=============================================================================
CTransition * CTransition::Create(float nPosX, float nPosY)
{
	CTransition *pTransition;
	pTransition = new CTransition;
	pTransition->Init(nPosX, nPosY, TRANSITION_WIDTH, TRANSITION_HEIGHT);
	return pTransition;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CTransition::Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	m_pScene2D = new CScene2D;
	m_pScene2D->Init(nPosX, nPosY, nPolygonWidth, nPolygonHeight);
	m_pScene2D->BindTexture(m_pTexture);
	m_pScene2D->SetColor(0);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CTransition::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CTransition::Update(void)
{
	if (m_bMinus==true)
	{
		m_nAlpha -= 2;
		if (m_nAlpha <= 0)
		{
			m_nAlpha = 0;
			m_bMinus = false;
		}
	}
	else
	{
		m_nAlpha += 2;
		if (m_nAlpha >= 255)
		{
			m_nAlpha = 255;
			m_bMinus = true;
		}
	}
	//�A���t�@�l���㏑��
	m_pScene2D->SetAlpha(m_nAlpha);
}

//=============================================================================
//�`�揈��
//=============================================================================
void CTransition::Draw(void)
{
	m_pScene2D->Draw();
}
