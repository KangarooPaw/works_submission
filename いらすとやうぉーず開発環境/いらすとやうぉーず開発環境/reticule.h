#ifndef _RETICULE_H_
#define _RETICULE_H_

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
	HRESULT Init(float nPosX, float nPosY);	//‰Šú‰»ˆ—
	void Uninit(void);	//I—¹ˆ—
	void Update(void);	//XVˆ—
	void Draw(void);	//•`‰æˆ—

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif // !_ENEMY_H_
