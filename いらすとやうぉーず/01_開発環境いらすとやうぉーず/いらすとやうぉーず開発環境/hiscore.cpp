//=============================================================================
//ハイスコア処理[hiscore.cpp]
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//インクルードファイル
//=============================================================================
#include "hiscore.h"
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CHiscore::m_pTexture = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CHiscore::CHiscore(int nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nHiScore = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CHiscore::~CHiscore()
{

}

HRESULT CHiscore::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_HISCORE,								// ファイルの名前
		&m_pTexture);
	return S_OK;
}

void CHiscore::Unload(void)
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
CHiscore * CHiscore::Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	CHiscore *pHiScore;
	pHiScore = new CHiscore;
	pHiScore->Init(nPosX, nPosY, nPolygonWidth, nPolygonHeight);
	pHiScore->SetObjType(OBJTYPE_SCORE);
	return pHiScore;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CHiscore::Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	//ハイスコア文字表示
	m_pScene2D = new CScene2D;
	m_pScene2D->Init(HISCORE_WIDTH, nPosY, HISCORE_WIDTH, HISCORE_HEIGHT);
	m_pScene2D->BindTexture(m_pTexture);
	//ハイスコア数値表示
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create(nPosX - ((nPolygonWidth * 2)*nCount), nPosY, nPolygonWidth, nPolygonHeight);
	}
	//ハイスコアの読み込み
	FileLoad();
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CHiscore::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//m_apNumberがNULLならコンティニュー
		if (m_apNumber[nCount] == NULL)continue;
		m_apNumber[nCount]->Uninit();
		delete m_apNumber[nCount];
		m_apNumber[nCount] = NULL;
	}
	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CHiscore::Update(void)
{
	SetHiScore();
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Update();
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CHiscore::Draw(void)
{
	m_pScene2D->Draw();
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//=============================================================================
//スコアの設定
//=============================================================================
void CHiscore::SetHiScore()
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->SetNumber(m_nHiScore % (int)pow(10, nCount + 1) / (int)pow(10, nCount));
	}
}

//=============================================================================
//バイナリファイル読み込み
//=============================================================================
void CHiscore::FileLoad()
{
	//ファイルを開く
	m_fp = fopen("data/hiscore.bin", "rb");
	//m_fpがNULLならreturn
	if (m_fp == NULL)return;
	//m_nHiScoreにファイル情報を取得
	fscanf(m_fp, "%d", &m_nHiScore);
	//ファイルを閉じる
	fclose(m_fp);
}

//=============================================================================
//バイナリファイル書き込み
//=============================================================================
void CHiscore::FileSave()
{
	//ファイルを開く
	m_fp = fopen("data/hiscore.bin", "wb");
	//m_fpがNULLならreturn
	if (m_fp == NULL)return;
	//m_nHiScoreの値をファイルに上書き
	fprintf(m_fp, "%d", m_nHiScore);
	//ファイルを閉じる
	fclose(m_fp);
}

//=============================================================================
//ハイスコアとの比較
//=============================================================================
void CHiscore::compareHiScore(int nScore)
{
	//スコアがハイスコアを越えなければreturn
	if (m_nHiScore >= nScore)return;
	//ハイスコアを更新
	m_nHiScore = nScore;
	//バイナリファイル上書き
	FileSave();
}