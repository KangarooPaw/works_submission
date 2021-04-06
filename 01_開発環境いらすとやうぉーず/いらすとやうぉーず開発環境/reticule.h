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

class CReticule :public CScene2D
{
public:
	CReticule(int nPriority = 10);
	~CReticule();
	static HRESULT Load(void);
	static void Unload(void);
	static CReticule *Create(float nPosX, float nPosY);
	HRESULT Init(float nPosX, float nPosY);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif // !_ENEMY_H_
