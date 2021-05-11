//--------------------------
//処理[fence.h]
//--------------------------
#ifndef _FENCE_H_
#define _FENCE_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "scene2d.h"

//--------------------------
//前方宣言
//--------------------------
class CManager;

//--------------------------
//クラス
//--------------------------
class CFence :public CScene2D
{
public:
	CFence(int nPriority = 2);	//コンストラクタ
	~CFence();						//デストラクタ

	static CFence*Create(float nPosX, float nPosY,int type);//生成処理

	static HRESULT Load(void);					//テクスチャの読み込み
	static void Unload(void);						//テクスチャの破棄

	HRESULT Init(float nPosX, float nPosY);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[2];	//テクスチャのポインタ
	static int	 m_fanceCnt;							//フェンスカウント
	bool m_Deathflag;									//死亡フラグ
	int m_type;											//タイプ情報
	int m_Life;											//体力情報
};
#endif // !_FENCE_H_