//=============================================================================
//リザルト処理[result.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "result.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CResult::CResult(int nPriority)
{
	m_pScene2D = NULL;
}

//=============================================================================
//デストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
//テクスチャの読み込み
//=============================================================================
HRESULT CResult::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_RESULT,								// ファイルの名前
		&m_pTexture);
	return S_OK;
}

//=============================================================================
//テクスチャの破棄
//=============================================================================
void CResult::Unload(void)
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
CResult * CResult::Create(float nPosX, float nPosY)
{
	CResult *pResult;
	pResult = new CResult;
	pResult->Init(nPosX, nPosY, BG_WIDTH, BG_HEIGHT);
	return pResult;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CResult::Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	m_pScene2D = new CScene2D;
	m_pScene2D->Init(nPosX, nPosY, nPolygonWidth, nPolygonHeight);
	m_pScene2D->BindTexture(m_pTexture);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CResult::Uninit(void)
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
void CResult::Update(void)
{
}

//=============================================================================
//描画処理
//=============================================================================
void CResult::Draw(void)
{
	m_pScene2D->Draw();
}
