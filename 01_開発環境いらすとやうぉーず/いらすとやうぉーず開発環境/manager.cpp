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
#include "keyboard.h"
#include "mouse.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "sound.h"
#include "score.h"
#include "number.h"
#include "transition.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "fence.h"
#include "operation.h"
#include "bomb.h"
#include "reticule.h"

//=============================================================================
//スタティック変数初期化
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
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
int CManager::m_saveScore = 0;
//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager()
{
	m_enemyPopTime = 0;
	m_PopSpeed = 100;
	nPosX = 0;
	nPosY = 0;

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
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//TEXTUREのロード
	LoadAll();
	m_pFade = CFade::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	CFade::SetFade(m_mode);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CScene::	ReleaseAll();
	UnloadAll();
	//キーボードの終了
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
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
	m_pInputKeyboard->Update();
	m_pInputMouse->Update();
	m_pRenderer->Update();

	if (m_pTransition != NULL)
	{
		m_pTransition->Update();
	}

	switch (m_mode)
	{
	case MODE_TITLE:

		if (m_pInputMouse->GetMouseTriggerLeft())
		{
			m_enemyPopTime = 0;
			m_PopSpeed = 100;
			CFade::SetFade(MODE_OPERATION);
		}
		break;

	case MODE_OPERATION:
		if (m_pInputMouse->GetMouseTriggerLeft())
		{
			CFade::SetFade(MODE_GAME);
		}
		break;

	case MODE_GAME:
		m_enemyPopTime++;	
		if (m_PopSpeed <= 0)
		{
			CFade::SetFade(MODE_RESULT);
		}
		if (m_enemyPopTime%m_PopSpeed == 0)
		{
			////生成速度アップ
			//if (m_enemyPopTime % 100 == 0)m_PopSpeed -= 10;
			srand((unsigned)time(NULL));
			//エネミーの生成
			for (int nCount = 0; nCount < ENEMY_CONCURRENT; nCount++)
			{
				int nDirection = rand() % DIRECTION_MAX;

				switch (nDirection)
				{
				case DIRECTION_UP:
					nPosX = rand() % SCREEN_WIDTH;
					CEnemy::Create((float)nPosX, 10.f);
					break;
				case DIRECTION_DOWN:
					nPosX = rand() % SCREEN_WIDTH;
					CEnemy::Create((float)nPosX, (float)SCREEN_HEIGHT - 15.f);
					break;
				case DIRECTION_LEFT:
					nPosY = rand() % SCREEN_HEIGHT;
					CEnemy::Create(10.f, (float)nPosY);
					break;
				case DIRECTION_RIGHT:
					nPosY = rand() % SCREEN_WIDTH;
					CEnemy::Create((float)SCREEN_WIDTH - 15.f, (float)nPosY);
					break;
				default:
					break;
				}
			}

		}
		break;

	case MODE_RESULT:
		if (m_pInputMouse->GetMouseTriggerLeft())
		{
			CFade::SetFade(MODE_TITLE);
		}
		break;
	default:
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
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		if (m_pScore != NULL)
		{
			m_pScore->Uninit();
		}
		m_pTitle = CTitle::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		m_pTransition = CTransition::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		m_pSound->Play(CSound::BGM_TITLE);
		break;

	case MODE_OPERATION:	
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		m_pOperation = COperation::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		break;

	case MODE_GAME:
		if (m_pOperation != NULL)
		{
			m_pOperation->Uninit();
			delete m_pOperation;
			m_pOperation = NULL;
		}
		if (m_pTransition != NULL)
		{
			m_pTransition->Uninit();
			delete m_pTransition;
			m_pTransition = NULL;
		}
		if (m_pSound != NULL)
		{
			m_pSound->Stop(CSound::BGM_TITLE);
		}
		m_pSound->Play(CSound::BGM_MAIN);
		//カーソルを非表示
		ShowCursor(false);
		//2Dポリゴンの生成
		CBg::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		CBomb::Create(BOMB_WIDTH/2, BOMB_HEIGHT/2);
		m_pPlayer = CPlayer::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		CFence::Create(SCREEN_CENTER_X - 125, SCREEN_CENTER_Y, 0);
		CFence::Create(SCREEN_CENTER_X + 125, SCREEN_CENTER_Y, 0);
		CFence::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y - 125, 1);
		CFence::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y + 125, 1);
		CReticule::Create(0, 0);
		m_pScore=CScore::Create(SCREEN_WIDTH - SCORE_WIDTH, SCORE_HEIGHT,SCORE_WIDTH,SCORE_HEIGHT);
		break;

	case MODE_RESULT:
		if (m_pSound != NULL)
		{
			m_pSound->Stop();
		}
		m_pSound->Play(CSound::SE_RESULT);
		//カーソルを表示
		ShowCursor(true);
		//スコアセーブ
		m_saveScore = m_pScore->SaveScore();
		CScene::ReleaseAll();
		m_pResult = CResult::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		//スコアのクリエイト
		m_pScore=CScore::Create(SCREEN_CENTER_X+SCORE_WIDTH*7, SCREEN_CENTER_Y, SCORE_WIDTH*3, SCORE_HEIGHT*3);
		//セーブしたスコアをセット
		m_pScore->SetScore(m_saveScore);
		break;

	default:
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
//キーボードの受け取り
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
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