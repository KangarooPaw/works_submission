//=============================================================================
//フェンス処理[fence.cpp]
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "fence.h"
#include "enemy.h"
#include "scene2d.h"
#include "renderer.h"
#include "keyboard.h"
#include "bullet.h"
#include "sound.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CFence::m_pTexture[2] = {};
int				 CFence::m_fanceCnt = 0;

//=============================================================================
//コンストラクタ
//=============================================================================
CFence::CFence(int nPriority)
{
	m_Deathflag = false;
	m_type = 0;
	m_Life = 5;
}

//=============================================================================
//デストラクタ
//=============================================================================
CFence::~CFence()
{

}

//=============================================================================
//生成処理
//=============================================================================
CFence *CFence::Create(float nPosX, float nPosY,int type)
{
	CFence *pFence;
	pFence = new CFence;
	pFence->m_type = type;
	pFence->Init(nPosX, nPosY);
	pFence->BindTexture(m_pTexture[pFence->m_type]);
	return pFence;
}

//=============================================================================
//テクスチャの読み込み
//=============================================================================
HRESULT CFence::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_FENCE1,					// ファイルの名前
		&m_pTexture[0]);
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_FENCE2,					// ファイルの名前
		&m_pTexture[1]);
	return S_OK;
}

//=============================================================================
//テクスチャの破棄
//=============================================================================
void CFence::Unload(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CFence::Init(float nPosX, float nPosY)
{
	//左右のフェンスを配置
	if (m_type == 0)
	{
		CScene2D::Init(nPosX, nPosY, FENCE_WIDTH, FENCE_HEIGHT);
	}
	//上下のフェンスを配置
	else if (m_type == 1)
	{
		CScene2D::Init(nPosX, nPosY, FENCE_HEIGHT, FENCE_WIDTH);
	}
	CScene2D::BindTexture(m_pTexture[m_type]);
	m_fanceCnt++;
	SetObjType(CScene::OBJTYPE_FENCE);
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CFence::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CFence::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
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
					//左右のフェンス
					if (m_type == 0)
					{
						//当たり判定
						if (pos.x - 10>= posEnemy.x - (ENEMY_WIDTH / 2) && pos.x + 10<= posEnemy.x + (ENEMY_WIDTH / 2) &&
							pos.y + (FENCE_HEIGHT / 2) >= posEnemy.y - (ENEMY_HEIGHT / 2) && pos.y - (FENCE_HEIGHT / 2) <= posEnemy.y + (ENEMY_HEIGHT / 2))
						{
							((CEnemy*)pScene2D)->HitObject();
							m_Life--;
							//フェンスの体力が無くなると死亡フラグ
							if (m_Life <= 0)
							{
								m_fanceCnt--;
								m_Deathflag = true;
							}
						}
					}
					//上下のフェンス
					else if (m_type == 1)
					{
						//当たり判定
						if (pos.x + (FENCE_HEIGHT / 2) >= posEnemy.x - (ENEMY_WIDTH / 2) && pos.x - (FENCE_HEIGHT / 2) <= posEnemy.x + (ENEMY_WIDTH / 2) &&
							pos.y + (ENEMY_WIDTH / 2) >= posEnemy.y - (ENEMY_HEIGHT / 2) && pos.y - (ENEMY_WIDTH / 2) <= posEnemy.y + (ENEMY_HEIGHT / 2))
						{
							((CEnemy*)pScene2D)->HitObject();
							m_Life--;
							//フェンスの体力が無くなると死亡フラグ
							if (m_Life <= 0)
							{
								m_fanceCnt--;
								m_Deathflag = true;
							}
						}
					}

				}
			}
		}
	}
	if (m_fanceCnt <= 0)
	{
		//フェンスがなくなるとBGM変更
		pSound->Stop(CSound::BGM_MAIN);
		pSound->Play(CSound::BGM_FENCEBREAK);
	}
	if (m_Deathflag == true)
	{
		//破壊SE再生
		pSound->Play(CSound::SE_BREAK);
		Uninit();
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CFence::Draw(void)
{
	CScene2D::Draw();
}