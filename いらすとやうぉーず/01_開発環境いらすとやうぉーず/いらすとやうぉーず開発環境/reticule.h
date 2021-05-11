//--------------------------
//レティクル処理[reticule.h]
//--------------------------
#ifndef _RETICULE_H_
#define _RETICULE_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "main.h"
#include "scene2d.h"

//--------------------------
//クラス
//--------------------------
class CReticule :public CScene2D
{
public:
	CReticule(int nPriority = 10);//コンストラクタ
	~CReticule();//デストラクタ

	static HRESULT Load(void);//テクスチャの読み込み
	static void Unload(void);//テクスチャの破棄

	static CReticule *Create(float nPosX, float nPosY);//生成処理

	HRESULT Init(float nPosX, float nPosY);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャのポインタ
};
#endif // !_ENEMY_H_