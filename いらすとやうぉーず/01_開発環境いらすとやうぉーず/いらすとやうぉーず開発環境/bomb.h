//--------------------------
//爆弾処理[bomb.h]
//--------------------------
#ifndef _BOMB_H_
#define _BOMB_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "scene2d.h"

//--------------------------
//前方宣言
//--------------------------
class CManager;

//--------------------------
//クラス
//--------------------------
class CBomb:public CScene2D
{
public:
	CBomb(int nPriority = 9);				//コンストラクタ
	~CBomb();								//デストラクタ

	static HRESULT Load(void);						//テクスチャの読み込み
	static void Unload(void);							//テクスチャの破棄

	static CBomb*Create(float nPosX, float nPosY);		//生成処理

	HRESULT Init(float nPosX, float nPosY);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャのポインタ
	bool m_bUse;											//爆弾使用判定
};
#endif // !_PLAYER_H_