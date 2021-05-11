//=============================================================================
//エネミー処理[enemy.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "score.h"
#include "sound.h"

//=============================================================================
//スタティック変数初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;

//-------------------------------------------
//コンストラクタ
//-------------------------------------------
CEnemy::CEnemy(int nPriority)
{
	m_move = 0.5;	//移動量
	m_nLife = ENEMY_LIFE;	//体力
}

//-------------------------------------------
//デストラクタ
//-------------------------------------------
CEnemy::~CEnemy()
{

}

//-------------------------------------------
//テクスチャ読み込み
//-------------------------------------------
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_ENEMY,							// ファイルの名前
		&m_pTexture);
	return S_OK;
}

//-------------------------------------------
// テクスチャの破棄
//-------------------------------------------
void CEnemy::Unload(void)
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
CEnemy * CEnemy::Create(float nPosX, float nPosY)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy;
	pEnemy->Init(nPosX, nPosY);
	return pEnemy;
}

//-------------------------------------------
//初期化処理
//-------------------------------------------
HRESULT CEnemy::Init(float nPosX, float nPosY)
{
	CScene2D::Init(nPosX, nPosY,ENEMY_WIDTH,ENEMY_HEIGHT);
	BindTexture(m_pTexture);
	if (nPosX < SCREEN_CENTER_X)
	{
		CScene2D::SetEnemyTex(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (nPosX > SCREEN_CENTER_X)
	{
		CScene2D::SetEnemyTex(0.0f, 1.0f, 0.0f, 1.0f);
	}
	//オブジェクトタイプを設定
	SetObjType(OBJTYPE_ENEMY);
	return S_OK;
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void CEnemy::Update(void)
{
	//位置を取得
	D3DXVECTOR3 pos=GetPosition();
	//画面中央に向かって進む
	double angle = atan2(double(SCREEN_CENTER_Y -pos.y ), double(SCREEN_CENTER_X -pos.x ));
	//進行方向計算
	pos.x +=(float)cos(angle)*m_move;
	pos.y += (float)sin(angle)*m_move;
	//位置をセット
	SetPosition(pos);
	CScene2D::Update();
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//-------------------------------------------
//弾に当たった時の処理
//-------------------------------------------
void CEnemy::HitBullet(void)
{
	CSound *pSound = CManager::GetSound();
	//弾が当たったら体力を減らす
	m_nLife--;
	//1度目のヒット判定
	CScene2D::SetColor(0);
	//体力がなくなったら
	if (m_nLife > 0)return;

	for (int nCountPriority = 0; nCountPriority < PRIORITY; nCountPriority++)
	{
		for (int nCountScene = 0; nCountScene < MAX_POLYGON; nCountScene++)
		{
			//Scene2Dの取得
			CScene2D *pScene2D = (CScene2D*)GetScene(nCountPriority, nCountScene);
			//pScene2DがNULLならコンティニュー
			if (pScene2D == NULL)continue;
			//OBJTYPEがSCORE以外ならコンティニュー
			if (pScene2D->GetObjType() != CScore::OBJTYPE_SCORE)continue;
			//スコア+1
			((CScore*)pScene2D)->AddScore(1);
		}
	}
	//SE再生
	pSound->Play(CSound::SE_EXPLOSION);
	//終了処理
	CScene2D::Uninit();
}

//-------------------------------------------
//弾以外に当たった時の処理
//-------------------------------------------
void CEnemy::HitObject(void)
{
	//Soundを取得
	CSound *pSound = CManager::GetSound();
	//SEを再生
	pSound->Play(CSound::SE_EXPLOSION);
	//終了処理
	Uninit();
}
