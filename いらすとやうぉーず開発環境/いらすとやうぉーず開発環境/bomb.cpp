//=============================================================================
//爆弾処理[bomb.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bomb.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "mouse.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CBomb::m_pTexture = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CBomb::CBomb(int nPriority)
{
	m_bUse = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CBomb::~CBomb()
{
}

//=============================================================================
//生成処理
//=============================================================================
CBomb * CBomb::Create(float nPosX, float nPosY)
{
	CBomb *pBomb;
	pBomb = new CBomb;
	pBomb->Init(nPosX, nPosY);
	return pBomb;
}

//=============================================================================
//テクスチャの読み込み
//=============================================================================
HRESULT CBomb::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_BOMB,					// ファイルの名前
		&m_pTexture);
	return S_OK;
}

//=============================================================================
//テクスチャの破棄
//=============================================================================
void CBomb::Unload(void)
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
HRESULT CBomb::Init(float nPosX, float nPosY)
{
	CScene2D::Init(nPosX, nPosY, BOMB_WIDTH, BOMB_HEIGHT);
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CBomb::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CBomb::Update(void)
{
	//マウスの取得
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	D3DXVECTOR3 pos = GetPosition();
	if (pInputMouse->GetMouseTriggerRight())
	{
		if (m_bUse == false)
		{
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
							for (int nCnt = 0; nCnt < ENEMY_LIFE; nCnt++)
							{
								((CEnemy*)pScene2D)->HitBullet();
							}
							m_bUse = true;
						}
					}
				}
			}
		}
	}
	if (m_bUse == true)Uninit();
}

//=============================================================================
//描画処理
//=============================================================================
void CBomb::Draw(void)
{
	CScene2D::Draw();
}
