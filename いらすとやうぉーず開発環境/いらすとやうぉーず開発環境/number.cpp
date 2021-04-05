//=============================================================================
//数字描画処理[number.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "scene.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//-------------------------------------------
//コンストラクタ
//-------------------------------------------
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_nNumber = 0;
}

//-------------------------------------------
//デストラクタ
//-------------------------------------------
CNumber::~CNumber()
{

}

//-------------------------------------------
//テクスチャ読み込み
//-------------------------------------------
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_NUMBER,							// ファイルの名前
		&m_pTexture);
	return S_OK;
}

//-------------------------------------------
//テクスチャの破棄
//-------------------------------------------
void CNumber::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-------------------------------------------
//クリエイト
//-------------------------------------------
CNumber * CNumber::Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	CNumber *pNumber;
	pNumber = new CNumber;
	pNumber->Init(nPosX,nPosY, nPolygonWidth, nPolygonHeight);
	((CScene*)pNumber)->SetObjType(CScene::OBJTYPE_NUMBER);
	return pNumber;
}

//-------------------------------------------
//初期化処理
//-------------------------------------------
HRESULT CNumber::Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_NUMBER,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = nPosX- nPolygonWidth;
	pVtx[0].pos.y = nPosY- nPolygonHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = nPosX+ nPolygonWidth;
	pVtx[1].pos.y = nPosY- nPolygonHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = nPosX - nPolygonWidth;
	pVtx[2].pos.y = nPosY + nPolygonHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = nPosX + nPolygonWidth;
	pVtx[3].pos.y = nPosY + nPolygonHeight;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	return S_OK;
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void CNumber::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.1f * m_nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * m_nNumber, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * m_nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * m_nNumber, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//-------------------------------------------
//セットナンバー
//-------------------------------------------
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;
}
