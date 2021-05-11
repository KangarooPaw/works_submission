//--------------------------
//処理[fade.h]
//--------------------------
#ifndef _FADE_H_
#define _FADE_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "renderer.h"
#include "manager.h"

//--------------------------
//前方宣言
//--------------------------
class CScene2D;

//--------------------------
//クラス
//--------------------------
class CFade
{
public:
	//フェードの構造体
	typedef enum
	{
		FADE_NONE=0,
		FADE_IN,
		FADE_OUT
	}FADE;

	CFade();											//コンストラクタ
	~CFade();											//デストラクタ

	static HRESULT Load(void);					//テクスチャの読み込み
	static void Unload(void);						//テクスチャの破棄

	static CFade *Create(float nPosX, float nPosY);		//生成処理

	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//初期化処理
	void Uninit(void);									//終了処理	
	void Update(void);									//更新処理
	void Draw(void);									//描画処理

	static void SetFade(CManager::MODE mode);			//フェード処理

	void FadeIn(void);									//フェードイン処理
	void FadeOut(void);									//フェードアウト処理
private:	
	static LPDIRECT3DTEXTURE9 m_pTexture;					//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	CScene2D *m_pScene2D;										//シーンのポインタ
	int	 m_nFade;													//フェードのアルファ値
	static CManager::MODE m_mode;								//モード情報
	static FADE m_fade;											//フェード情報
};
#endif // !_FADE_H_