#ifndef _BOMB_H_
#define _BOMB_H_
#include "scene2d.h"

class CManager;
class CBomb:public CScene2D
{
public:
	CBomb(int nPriority = 9);
	~CBomb();

	static CBomb*Create(float nPosX, float nPosY);

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(float nPosX, float nPosY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	bool m_bUse;
};
#endif // !_PLAYER_H_
