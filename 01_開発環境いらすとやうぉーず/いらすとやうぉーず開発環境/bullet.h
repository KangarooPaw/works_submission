//--------------------------
//弾処理[bullet.h]
//--------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "scene2d.h"

class CBullet:public CScene2D
{
public:
	CBullet(int nPriority = 6);
	~CBullet();
	static CBullet *Create(float nPosX, float nPosY);
	
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(float nPosX, float nPosY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	float m_move;
	float m_angleX, m_angleY;
	bool m_hit;
};

#endif // !_BULLET_H_
