//--------------------------
//処理[explosion.h]
//--------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "scene2d.h"

//--------------------------
//クラス
//--------------------------
class CExplosion :public CScene2D
{
public:
	CExplosion();				//コンストラクタ
	~CExplosion();				//デストラクタ

	static HRESULT Load(void);	//テクスチャの読み込み
	static void Unload(void);		//テクスチャの破棄

	static CExplosion *Create(float nPosX, float nPosY);//生成処理

	HRESULT Init(float nPosX, float nPosY);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャのポインタ
	int m_nCounterAnim;		//カウンター
	int m_nPatternAnim;		//パターン
};
#endif // !_BULLET_H_