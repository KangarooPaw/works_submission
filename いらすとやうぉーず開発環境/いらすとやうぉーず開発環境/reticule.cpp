#include "reticule.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CReticule::m_pTexture = NULL;

CReticule::CReticule(int nPriority)
{

}

CReticule::~CReticule()
{

}

HRESULT CReticule::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RETICULE,							// �t�@�C���̖��O
		&m_pTexture);
	return S_OK;
}

void CReticule::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

CReticule * CReticule::Create(float nPosX, float nPosY)
{
	CReticule *pReticule;
	pReticule = new CReticule;
	pReticule->Init(nPosX, nPosY);
	return pReticule;
}

HRESULT CReticule::Init(float nPosX, float nPosY)
{
	CScene2D::Init(nPosX, nPosY, RETICULE_WIDTH, RETICULE_HEIGHT);
	CScene2D::BindTexture(m_pTexture);
	return S_OK;
}

void CReticule::Uninit(void)
{
	CScene2D::Uninit();
}

void CReticule::Update(void)
{
	//�}�E�X�J�[�\���ʒu�擾
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
	SetPosition(D3DXVECTOR3(point.x, point.y, 0));
	CScene2D::Update();
}

void CReticule::Draw(void)
{
	CScene2D::Draw();
}
