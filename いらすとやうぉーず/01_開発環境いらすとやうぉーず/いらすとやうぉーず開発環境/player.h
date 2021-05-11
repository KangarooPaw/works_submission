//--------------------------
//プレイヤー処理[player.h]
//--------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

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
class CPlayer :public CScene2D
{
public:
	CPlayer(int nPriority = 9);//コンストラクタ
	~CPlayer();//デストラクタ

	static HRESULT Load(void);//テクスチャの読み込み
	static void Unload(void);//テクスチャの破棄
		
	static CPlayer*Create(float nPosX, float nPosY);//生成処理
	
	HRESULT Init(float nPosX, float nPosY);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャのポインタ
	float	m_move;//移動速度
	int		m_bulletTime;//射撃速度
};
#endif // !_PLAYER_H_
