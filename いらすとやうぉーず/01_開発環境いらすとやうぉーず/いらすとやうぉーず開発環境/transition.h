//--------------------------
//遷移を促す文字の描画処理[transition.h]
//--------------------------
#ifndef _TRANSITION_H_
#define _TRANSITION_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "renderer.h"

//--------------------------
//前方宣言
//--------------------------
class CScene2D;

//--------------------------
//クラス
//--------------------------
class CTransition
{
public:
	CTransition();									//コンストラクタ
	~CTransition();									//デストラクタ

	static HRESULT Load(void);					//テクスチャの読み込み
	static void Unload(void);						// テクスチャの破棄

	static CTransition *Create(float nPosX, float nPosY);	//生成処理

	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);			//初期化処理
	void Uninit(void);								//終了処理	
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャのポインタ
	CScene2D *m_pScene2D;		//シーンのポインタ
	bool m_bMinus;					//アルファ値の減算判定
	int m_nAlpha;					//アルファ値
};
#endif // !_TITLE_H_