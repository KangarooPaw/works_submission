//=============================================================================
//弾処理[bullet.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "sound.h"

//=============================================================================
//スタティック変数初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CBullet::CBullet(int nPriority)
{
	m_fMove = 5.f;
	m_angleX =0.f;
	m_angleY = 0.f;
	m_bHit = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CBullet::~CBullet()
{
	
}

//=============================================================================
//生成処理
//=============================================================================
CBullet *CBullet::Create(float nPosX, float nPosY)
{
	CBullet *pBullet;
	pBullet = new CBullet;
	pBullet->Init(nPosX, nPosY);
	//posの取得
	D3DXVECTOR3 pos = pBullet->GetPosition();
	//マウスカーソル位置取得
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
	//角度計算
	double angle = atan2(double(point.y -pos.y ), double( point.x -pos.x));
	pBullet->m_angleX= (float)cos(angle);
	pBullet->m_angleY= (float)sin(angle);

	return pBullet;
}

//=============================================================================
//テクスチャの読み込み
//=============================================================================
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BULLET,					// ファイルの名前
		&m_pTexture);
	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CBullet::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CBullet::Init(float nPosX, float nPosY)
{

	CScene2D::Init(nPosX, nPosY ,BULLET_WIDTH,BULLET_HEIGHT);	
	CScene2D::BindTexture(m_pTexture);
	
	//オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BULLET);
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}
   
//=============================================================================
//更新処理
//=============================================================================
void CBullet::Update(void)
{
	//位置の取得
	D3DXVECTOR3 pos = GetPosition();
	//進行方向の計算
	pos.x += m_angleX*m_fMove;
	pos.y += m_angleY*m_fMove;
	//位置のセット
	SetPosition(pos);
	CScene2D::Update();

	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			//Scene2Dを取得
			CScene2D *pScene2D = (CScene2D*)GetScene(nCountpriority, nCntScene);
			//pScene2DがNULLならばコンティニュー
			if (pScene2D == NULL)continue;
			//OBJTYPEがエネミー以外ならばコンティニュー
			if (pScene2D->GetObjType() != CEnemy::OBJTYPE_ENEMY)continue;
			//エネミーの位置取得
			D3DXVECTOR3 posEnemy = pScene2D->GetPosition();
			//エネミーに当たった処理
			if (pos.x >= posEnemy.x - (ENEMY_WIDTH / 2) && pos.x <= posEnemy.x + (ENEMY_WIDTH / 2) &&
				pos.y >= posEnemy.y - (ENEMY_HEIGHT / 2) && pos.y <= posEnemy.y + (ENEMY_HEIGHT / 2))
			{
				//エネミーのヒット処理
				((CEnemy*)(pScene2D))->HitBullet();
				//爆破エフェクト生成
				CExplosion::Create(pos.x, pos.y);
				//ヒットフラグ
				m_bHit = true;
			}
			//弾が画面外に出たときもヒットフラグを立てる
			else if (pos.x<-5 || pos.x>SCREEN_WIDTH + 5 || pos.y<-5 || pos.y>SCREEN_HEIGHT + 5)m_bHit = true;
		}
	}
	//弾が敵に当たる、画面外に出るとreturn
	if (m_bHit != true)return;
	//ヒットフラグリセット
	m_bHit = false;
	//終了処理
	CScene2D::Uninit();
}

//=============================================================================
//描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}