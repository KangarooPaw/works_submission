//--------------------------
//数字描画処理[number.h]
//--------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "main.h"

//--------------------------
//クラス
//--------------------------
class CNumber
{
public:
	CNumber();		//コンストラクタ
	~CNumber();		//デストラクタ

	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);			//テクスチャの破棄

	static CNumber *Create(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight);//生成処理

	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void SetNumber(int nNumber);//数字のセット
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//頂点バッファ
	int m_nNumber;//数字情報
};
#endif