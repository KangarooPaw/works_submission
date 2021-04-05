#include "reticule.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//静的メンバ変数の初期化
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

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_RETICULE,							// ファイルの名前
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
	//マウスカーソル位置取得
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
