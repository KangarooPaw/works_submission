
#include "game.h"
#include "bg.h"
#include "bomb.h"
#include "player.h"
#include "fence.h"
#include "reticule.h"
#include "enemy.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_enemyPopTime = 0;
	m_PopSpeed = 100;
	nPosX = 0;
	nPosY = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
//初期化処理
//=============================================================================
void CGame::Init(void)
{
	//カーソル非表示
	ShowCursor(false);
	//背景生成
	CBg::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	//ボム表示生成
	CBomb::Create(BOMB_WIDTH / 2, BOMB_HEIGHT / 2);
	//プレイヤー生成
	CPlayer::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	//フェンス生成
	CFence::Create(SCREEN_CENTER_X - 125, SCREEN_CENTER_Y, 0);
	CFence::Create(SCREEN_CENTER_X + 125, SCREEN_CENTER_Y, 0);
	CFence::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y - 125, 1);
	CFence::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y + 125, 1);
	//レティクル生成
	CReticule::Create(0, 0);
}

//=============================================================================
//終了処理
//=============================================================================
void CGame::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	//エネミー生成タイム
	m_enemyPopTime++;
	//エネミー生成タイミング以外ブレイク
	if (m_enemyPopTime%m_PopSpeed != 0)return;

	//乱数初期化
	srand((unsigned)time(NULL));
	//エネミーの生成
	for (int nCount = 0; nCount < ENEMY_CONCURRENT; nCount++)
	{
		//方向乱数
		int nDirection = rand() % DIRECTION_MAX;
		//X軸、Y軸に乱数
		nPosX = rand() % SCREEN_WIDTH;
		nPosY = rand() % SCREEN_HEIGHT;
		//エネミー生成
		switch (nDirection)
		{
		case DIRECTION_UP://上
			CEnemy::Create((float)nPosX, 10.f);
			break;
		case DIRECTION_DOWN://下
			CEnemy::Create((float)nPosX, (float)SCREEN_HEIGHT - 15.f);
			break;
		case DIRECTION_LEFT://左
			CEnemy::Create(10.f, (float)nPosY);
			break;
		case DIRECTION_RIGHT://右
			CEnemy::Create((float)SCREEN_WIDTH - 15.f, (float)nPosY);
			break;
		}
	}
}
