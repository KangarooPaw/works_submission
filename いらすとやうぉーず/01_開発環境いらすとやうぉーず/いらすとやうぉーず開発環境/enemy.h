//--------------------------
//処理[enemy.h]
//--------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "main.h"
#include "scene2d.h"

//--------------------------
//マクロ定義
//--------------------------
#define ENEMY_LIFE 2

//--------------------------
//クラス
//--------------------------
class CEnemy :public CScene2D
{
public:
	CEnemy(int nPriority = 7);						//コンストラクタ
	~CEnemy();											//デストラクタ

	static HRESULT Load(void);						//テクスチャの読み込み
	static void Unload(void);							//テクスチャの破棄

	static CEnemy *Create(float nPosX, float nPosY);//生成処理

	HRESULT Init(float nPosX, float nPosY);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理

	void HitBullet(void);
	void HitObject(void);
private:
	LPDIRECT3DTEXTURE9 m_apScene[3];
	static LPDIRECT3DTEXTURE9 m_pTexture;
	float	m_move;
	int		m_nLife;
};
#endif // !_ENEMY_H_
