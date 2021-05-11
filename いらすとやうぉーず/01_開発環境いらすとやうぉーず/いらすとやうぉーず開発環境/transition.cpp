//=============================================================================
//遷移を促す文字の描画処理[transition.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "transition.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CTransition::m_pTexture = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CTransition::CTransition()
{
	m_pScene2D = NULL;
	m_nAlpha = 255;
	m_bMinus = true;
}

//=============================================================================
//デストラクタ
//=============================================================================
CTransition::~CTransition()
{
}

//=============================================================================
//テクスチャの読み込み
//=============================================================================
HRESULT CTransition::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_TRANSITON,								// ファイルの名前
		&m_pTexture);
	return S_OK;
}

//=============================================================================
//テクスチャの破棄
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
//生成処理
//=============================================================================
CTransition * CTransition::Create(float nPosX, float nPosY)
{
	CTransition *pTransition;
	pTransition = new CTransition;
	pTransition->Init(nPosX, nPosY, TRANSITION_WIDTH, TRANSITION_HEIGHT);
	return pTransition;
}

//=============================================================================
//初期化処理
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
//終了処理
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
//更新処理
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
	//アルファ値を上書き
	m_pScene2D->SetAlpha(m_nAlpha);
}

//=============================================================================
//描画処理
//=============================================================================
void CTransition::Draw(void)
{
	m_pScene2D->Draw();
}
