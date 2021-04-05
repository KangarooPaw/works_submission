//=============================================================================
//シーン処理[scene.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene.h"
#include "scene2d.h"
#include "enemy.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
CScene *CScene::m_apScene[PRIORITY][MAX_POLYGON] = {};
int CScene::m_nNumAll = 0;
int CScene::m_nCount = 0;

//=============================================================================
//コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		if (m_apScene[nPriority][nCount] == NULL)
		{
			m_apScene[nPriority][nCount] = this;
			m_objType = OBJTYPE_NONE;
			m_nPriority = nPriority;
			m_nID = nCount;
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
//デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//オブジェクト設定
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}


//=============================================================================
//シーン取得
//=============================================================================
CScene * CScene::GetScene(int nPriority,int nCnt)
{
	return m_apScene[nPriority][nCnt];
}

//=============================================================================
//リリース処理まとめ
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		// ポリゴンの終了処理
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nCountpriority][nCount] != NULL)
			{
				if (m_apScene[nCountpriority][nCount]->GetObjType() != OBJTYPE_FADE)
				{
					m_apScene[nCountpriority][nCount]->Uninit();
				}
			}
		}
	}
}

//=============================================================================
//更新処理まとめ
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		// ポリゴンの更新処理
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nCountpriority][nCount] != NULL)
			{
				m_apScene[nCountpriority][nCount]->Update();
			}
		}
	}
}

//=============================================================================
//描画処理まとめ
//=============================================================================
void CScene::DrawAll(void)
{	
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		// ポリゴンの描画処理
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nCountpriority][nCount] != NULL)
			{
				if (m_apScene[nCountpriority][nCount]->GetObjType() != OBJTYPE_FADE)
				{
					m_apScene[nCountpriority][nCount]->Draw();
				}
			}
		}
	}
}

//=============================================================================
//リリース処理
//=============================================================================
void CScene::Release(void)
{
	//メモリの解放
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}