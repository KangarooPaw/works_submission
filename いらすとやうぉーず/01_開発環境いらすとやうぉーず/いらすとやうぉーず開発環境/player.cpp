//=============================================================================
//プレイヤー処理[player.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "player.h"
#include "enemy.h"
#include "scene2d.h"
#include "renderer.h"
#include "mouse.h"
#include "bullet.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	m_move = 5.0f;
	m_bulletTime = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
//生成処理
//=============================================================================
CPlayer *CPlayer::Create(float nPosX, float nPosY)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init(nPosX, nPosY);
	return pPlayer;
}

//=============================================================================
//テクスチャの読み込み
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_PLAYER,					// ファイルの名前
		&m_pTexture);

	return S_OK;
}

//=============================================================================
//テクスチャの破棄
//=============================================================================
void CPlayer::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CPlayer::Init(float nPosX, float nPosY)
{
	CScene2D::Init(nPosX, nPosY,PLAYER_WIDTH,PLAYER_HEIGHT);
	CScene2D::BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_PLAYER);
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CPlayer::Update(void)
{
	//マウスの取得
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	//サウンドの取得
	CSound *pSound = CManager::GetSound();
	//位置情報の取得
	D3DXVECTOR3 pos = GetPosition();
	//マウスカーソル位置取得
	POINT point;
	GetCursorPos(&point);
	//ウィンドウ内のポインター判定
	ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
	//半径
	double r = sqrtf((PLAYER_WIDTH / 2 ^ 2) + (PLAYER_HEIGHT / 2 ^ 2));
	//角度計算
	double angle = atan2(double(point.y - pos.y), double(point.x - pos.x));

	if (pInputMouse->GetMouseTriggerLeft())
	{
		//SE再生
		pSound->Play(CSound::SE_SHOT);
		//弾生成
		CBullet::Create(pos.x, pos.y);
	}

	if (pInputMouse->GetMousePressLeft())
	{
		//射撃タイム
		m_bulletTime++;
		//射撃
		if (m_bulletTime % 10 == 0)
		{
			//SE再生
			pSound->Play(CSound::SE_SHOT);
			//弾生成
			CBullet::Create(pos.x, pos.y);
		}
	}
	//左クリックを話てリセット
	if (pInputMouse->GetMouseReleaseLeft())
	{
		m_bulletTime = 0;
	}
	//位置セット
	SetPosition(pos);
	//プレイヤーの角度
	CScene2D::SetRotVertex(PLAYER_WIDTH, PLAYER_HEIGHT, (float)angle);
	//プレイヤー反転処理
	if (point.x < SCREEN_CENTER_X)
	{
		CScene2D::SetRotVertex(PLAYER_WIDTH, -PLAYER_HEIGHT, (float)angle);
	}

	//当たり判定処理
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			//Scene2Dの取得
			CScene2D *pScene2D = (CScene2D*)GetScene(nCntPriority, nCntScene);
			//pScene2DがNULLならコンティニュー
			if (pScene2D == NULL)continue;
			//OBJTYPEがエネミーならコンティニュー
			if (pScene2D->GetObjType() != CEnemy::OBJTYPE_ENEMY)continue;

			//エネミーの位置を取得
			D3DXVECTOR3 posEnemy = pScene2D->GetPosition();
			if (pos.x >= posEnemy.x - (ENEMY_WIDTH / 2) && pos.x <= posEnemy.x + (ENEMY_WIDTH / 2) &&
				pos.y >= posEnemy.y - (ENEMY_HEIGHT / 2) && pos.y <= posEnemy.y + (ENEMY_HEIGHT / 2))
			{
				//エネミーのヒット処理
				((CEnemy*)pScene2D)->HitObject();
				//プレイヤーの終了処理
				Uninit();
				//画面遷移処理
				CFade::SetFade(CManager::MODE_RESULT);
			}
		}
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}