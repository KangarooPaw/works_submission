#ifndef _FENCE_H_
#define _FENCE_H_
#include "scene2d.h"

class CManager;
class CFence :public CScene2D
{
public:
	CFence(int nPriority = 2);
	~CFence();

	static CFence*Create(float nPosX, float nPosY,int type);

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(float nPosX, float nPosY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[2];
	static int				m_fanceCnt;
	bool m_Deathflag;
	int m_type;
	int m_Life;
};
#endif // !_FENCE_H_
