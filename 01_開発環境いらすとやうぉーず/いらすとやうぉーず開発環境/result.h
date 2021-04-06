//--------------------------
//リザルト処理[result.h]
//--------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "renderer.h"

//--------------------------
//前方宣言
//--------------------------
class CScene2D;

class CResult 
{
	public:
		CResult(int nPriority = 4);											//コンストラクタ
		~CResult();											//デストラクタ
		static HRESULT Load(void);						//テクスチャの読み込み
		static void Unload(void);						// テクスチャの破棄
		static CResult *Create(float nPosX, float nPosY);	//生成処理
		HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);			//初期化処理
		void Uninit(void);								//終了処理	
		void Update(void);								//更新処理
		void Draw(void);								//描画処理

	private:
		static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ変数
		CScene2D *m_pScene2D;
};
#endif // !_RESULT_H_
