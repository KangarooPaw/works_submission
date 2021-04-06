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

class CPlayer :public CScene2D
{
public:
	CPlayer(int nPriority = 9);
	~CPlayer();
	
	static CPlayer*Create(float nPosX, float nPosY);
	
	static HRESULT Load(void);
	static void Unload(void);
	
	HRESULT Init(float nPosX, float nPosY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	float	m_move;
	int		m_bulletTime;
};
#endif // !_PLAYER_H_
