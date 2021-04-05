#ifndef _OPERATION_H_
#define _OPERATION_H_
#include "renderer.h"
class CScene2D;
class COperation
{
public:
	COperation();											//コンストラクタ
	~COperation();											//デストラクタ
	static HRESULT Load(void);						//テクスチャの読み込み
	static void Unload(void);						// テクスチャの破棄
	static COperation *Create(float nPosX, float nPosY);	//生成処理
	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);			//初期化処理
	void Uninit(void);								//終了処理	
	void Update(void);
	void Draw(void);								//描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ変数
	CScene2D *m_pScene2D;
	float m_TexPos;
};
#endif // !_OPERATION_H_
