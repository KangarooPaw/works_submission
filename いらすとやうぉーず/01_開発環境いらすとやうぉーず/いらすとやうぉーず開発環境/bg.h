//--------------------------
//背景処理[bg.h]
//--------------------------
#ifndef _BG_H_
#define _BG_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "scene.h"

//--------------------------
//前方宣言
//--------------------------
class CScene2D;

//--------------------------
//クラス
//--------------------------
class CBg :public CScene
{
public:
	CBg(int nPriority=4);							//コンストラクタ
	~CBg();											//デストラクタ

	static HRESULT Load(void);					//テクスチャの読み込み
	static void Unload(void);						// テクスチャの破棄
	static CBg *Create(float nPosX, float nPosY);	//生成処理

	HRESULT Init(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight);//初期化処理
	void Uninit(void);								//終了処理	
	void Update(void);								//更新処理
	void Draw(void);								//描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ変数
	CScene2D *m_pScene2D;							//シーン2Dポインタ
};
#endif // !_BG_H_