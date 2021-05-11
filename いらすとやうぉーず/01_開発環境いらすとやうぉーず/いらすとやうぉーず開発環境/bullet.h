//--------------------------
//弾処理[bullet.h]
//--------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "scene2d.h"

//--------------------------
//クラス
//--------------------------
class CBullet:public CScene2D
{
public:
	CBullet(int nPriority = 6);					//コンストラクタ
	~CBullet();										//デストラクタ
	
	static HRESULT Load(void);					//テクスチャの読み込み
	static void Unload(void);						//テクスチャの破棄

	static CBullet *Create(float nPosX, float nPosY);//生成処理

	HRESULT Init(float nPosX, float nPosY);	//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャのポインタ
	float m_fMove;										//移動量
	float m_angleX, m_angleY;						//角度
	bool m_bHit;											//ヒットフラグ
};
#endif // !_BULLET_H_