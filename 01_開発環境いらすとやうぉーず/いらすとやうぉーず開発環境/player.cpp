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
	ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
	//半径
	double r = sqrtf((PLAYER_WIDTH / 2 ^ 2) + (PLAYER_HEIGHT / 2 ^ 2));
	//角度計算
	double angle = atan2(double(point.y - pos.y), double(point.x - pos.x));
	
	//弾の発射
	if (pInputMouse->GetMouseTriggerLeft())
	{
		pSound->Play(CSound::SE_SHOT);
		CBullet::Create(pos.x, pos.y);
	}
	if (pInputMouse->GetMousePressLeft())
	{
		m_bulletTime++;
		if (m_bulletTime % 10 == 0)
		{
			pSound->Play(CSound::SE_SHOT);
			CBullet::Create(pos.x, pos.y);
		}
	}
	if (pInputMouse->GetMouseReleaseLeft())
	{
		m_bulletTime = 0;
	}

	SetPosition(pos);
	CScene2D::SetRotVertex(PLAYER_WIDTH,PLAYER_HEIGHT,(float)angle);
	if (point.x < SCREEN_CENTER_X)
	{
		CScene2D::SetRotVertex(PLAYER_WIDTH, -PLAYER_HEIGHT, (float)angle);
	}

	//当たり判定処理
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			CScene2D *pScene2D = (CScene2D*)GetScene(nCountpriority, nCntScene);
			if (pScene2D != NULL)
			{
				D3DXVECTOR3 posEnemy = pScene2D->GetPosition();
				if (pScene2D->GetObjType() == CEnemy::OBJTYPE_ENEMY)
				{
					if (pos.x >= posEnemy.x - (ENEMY_WIDTH / 2) && pos.x <= posEnemy.x + (ENEMY_WIDTH / 2) &&
						pos.y >= posEnemy.y - (ENEMY_HEIGHT / 2) && pos.y <= posEnemy.y + (ENEMY_HEIGHT / 2))
					{
						((CEnemy*)pScene2D)->HitObject();
						Uninit();
						CFade::SetFade(CManager::MODE_RESULT);
					}
				}
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