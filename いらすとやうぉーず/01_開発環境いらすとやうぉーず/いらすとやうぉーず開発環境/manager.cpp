//=============================================================================
// マネージャー処理 [manager.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "mouse.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "sound.h"
#include "score.h"
#include "hiscore.h"
#include "number.h"
#include "transition.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "fence.h"
#include "operation.h"
#include "bomb.h"
#include "reticule.h"
#include "game.h"

//=============================================================================
//スタティック変数初期化
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CSound *CManager::m_pSound = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;
CTransition *CManager::m_pTransition = NULL;
CTitle *CManager::m_pTitle=NULL;
CResult *CManager::m_pResult=NULL;
CFade *CManager::m_pFade = NULL;
COperation *CManager::m_pOperation=NULL;
CScore*CManager::m_pScore = NULL;
CHiscore*CManager::m_pHiscore = NULL;
CGame*CManager::m_pGame = NULL;
int CManager::m_saveScore = 0;

//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
{
	//レンダリングクラス生成	// 初期化処理	
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, TRUE);
	//マウスクラス生成
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);
	//サウンドクラス生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//TEXTUREのロード
	LoadAll();
	//フェードクラス生成
	m_pFade = CFade::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	//遷移
	CFade::SetFade(m_mode);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CScene::	ReleaseAll();
	//TEXTUREの終了処理
	UnloadAll();
	//マウス終了処理
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}
	//レンダラーの終了
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	//マウス
	m_pInputMouse->Update();
	//レンダラー
	m_pRenderer->Update();
	//遷移用文字更新
	if (m_pTransition != NULL)
	{
		m_pTransition->Update();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pInputMouse->GetMouseTriggerLeft())
		{
			//遷移
			CFade::SetFade(MODE_OPERATION);
		}
		break;

	case MODE_OPERATION:
		if (m_pInputMouse->GetMouseTriggerLeft())
		{
			//遷移
			CFade::SetFade(MODE_GAME);
		}
		break;

	case MODE_GAME:
		if(m_pGame!=NULL)m_pGame->Update();
		break;

	case MODE_RESULT:
		if (m_pInputMouse->GetMouseTriggerLeft())
		{
			//遷移
			CFade::SetFade(MODE_TITLE);
		}
		break;
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//=============================================================================
//テクスチャの読み込みまとめ
//=============================================================================
void CManager::LoadAll(void)
{
	CTransition::Load();
	CTitle::Load();
	COperation::Load();
	CResult::Load();
	CFade::Load();
	CBg::Load();
	CPlayer::Load();
	CFence::Load();
	CEnemy::Load();
	CBullet::Load();
	CExplosion::Load();
	CNumber::Load();
	CBomb::Load();
	CReticule::Load();
}

//=============================================================================
//テクスチャの破棄まとめ
//=============================================================================
void CManager::UnloadAll(void)
{
	CReticule::Unload();
	CBomb::Unload();
	CNumber::Unload();
	CExplosion::Unload();
	CBullet::Unload();
	CEnemy::Unload();
	CFence::Unload();
	CPlayer::Unload();
	CBg::Unload();
	CFade::Unload();
	CResult::Unload();
	COperation::Unload();
	CTitle::Unload();
	CTransition::Unload();
}

//=============================================================================
//プレイヤーの受け取り処理
//=============================================================================
CPlayer *CManager::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
//モード変更処理
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_mode = mode;
	switch (m_mode)
	{
	case MODE_TITLE:
		//リザルト終了処理
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		//スコア終了処理
		if (m_pScore != NULL)
		{
			m_pScore->Uninit();
		}
		//ハイスコア終了処理
		if (m_pHiscore != NULL)
		{
			m_pHiscore->Uninit();
		}
		//タイトル生成
		m_pTitle = CTitle::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		//遷移用文字生成
		m_pTransition = CTransition::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		//サウンド再生
		m_pSound->Play(CSound::BGM_TITLE);
		break;

	case MODE_OPERATION:
		//タイトル終了処理
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		//説明生成
		m_pOperation = COperation::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		break;

	case MODE_GAME:
		//説明終了処理
		if (m_pOperation != NULL)
		{
			m_pOperation->Uninit();
			delete m_pOperation;
			m_pOperation = NULL;
		}
		//遷移用文字終了
		if (m_pTransition != NULL)
		{
			m_pTransition->Uninit();
			delete m_pTransition;
			m_pTransition = NULL;
		}
		//サウンド停止
		if (m_pSound != NULL)
		{
			m_pSound->Stop(CSound::BGM_TITLE);
		}
		//ゲームクラス生成
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;
			m_pGame->Init();
		}
		//サウンド再生
		m_pSound->Play(CSound::BGM_MAIN);
		//スコア生成
		m_pScore=CScore::Create(SCREEN_WIDTH - SCORE_WIDTH, SCORE_HEIGHT,SCORE_WIDTH,SCORE_HEIGHT);
		break;

	case MODE_RESULT:
		//ゲームの終了
		if (m_pGame != NULL)
		{
			delete m_pGame;
			m_pGame = NULL;
		}
		//サウンド停止
		if (m_pSound != NULL)
		{
			m_pSound->Stop();
		}
		//サウンド再生
		m_pSound->Play(CSound::SE_RESULT);
		//スコアセーブ
		m_saveScore = m_pScore->SaveScore();
		//リリース
		CScene::ReleaseAll();	
		//カーソル表示
		ShowCursor(true);
		//リザルト生成
		m_pResult = CResult::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		//スコア生成
		m_pScore=CScore::Create(SCREEN_CENTER_X+SCORE_WIDTH*7, SCREEN_CENTER_Y, SCORE_WIDTH*3, SCORE_HEIGHT*3);
		//セーブしたスコアをセット
		m_pScore->SetScore(m_saveScore);
		//ハイスコア生成
		m_pHiscore = CHiscore::Create(SCREEN_CENTER_X + SCORE_WIDTH * 7,125, SCORE_WIDTH * 3, SCORE_HEIGHT * 3);
		//ハイスコアとスコアを比べる
		m_pHiscore->compareHiScore(m_saveScore);
		break;
	}
}


//=============================================================================
//モードの受け取り
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
//レンダラーの受け取り
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;	
}

//=============================================================================
//マウスの受け取り
//=============================================================================
CInputMouse * CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//=============================================================================
//サウンドの受け取り
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
//フェードの受け取り
//=============================================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}