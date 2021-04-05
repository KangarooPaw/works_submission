#ifndef _TRANSITION_H_
#define _TRANSITION_H_
#include "renderer.h"
class CScene2D;
class CTransition
{
public:
	CTransition();									//コンストラクタ
	~CTransition();									//デストラクタ
	static HRESULT Load(void);						//テクスチャの読み込み
	static void Unload(void);						// テクスチャの破棄
	static CTransition *Create(float nPosX, float nPosY);	//生成処理
	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);			//初期化処理
	void Uninit(void);								//終了処理	
	void Update(void);								//更新処理
	void Draw(void);								//描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ変数
	CScene2D *m_pScene2D;	//シーン用ポインタ
	bool m_bMinus;			//アルファ値の減算判定
	int m_nAlpha;			//アルファ値
};
#endif // !_TITLE_H_
