//=============================================================================
//スコア処理[score.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "score.h"
#include "number.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CScore::CScore(int nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nScore = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
//生成処理
//=============================================================================
CScore * CScore::Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	CScore *pScore;
	pScore = new CScore;
	pScore->Init(nPosX, nPosY, nPolygonWidth, nPolygonHeight);
	pScore->SetObjType(OBJTYPE_SCORE);
	return pScore;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CScore::Init(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create(nPosX-((nPolygonWidth *2)*nCount),nPosY, nPolygonWidth, nPolygonHeight);
	}
	m_nScore = 0;
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Uninit();
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CScore::Update(void)
{
	SetScore(m_nScore);
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Update();
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//=============================================================================
//スコアの設定
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
	m_apNumber[nCount]->SetNumber(m_nScore % (int)pow(10, nCount + 1) / (int)pow(10, nCount));
	}
}

//=============================================================================
//スコアを加算
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->SetNumber(m_nScore % (int)pow(10, nCount + 1) / (int)pow(10, nCount));
	}
}

//=============================================================================
//スコアの取得
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//=============================================================================
//スコアを保存
//=============================================================================
int CScore::SaveScore(void)
{
	return m_nScore;
}
