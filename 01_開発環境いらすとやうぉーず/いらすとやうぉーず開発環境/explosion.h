//--------------------------
//����[explosion.h]
//--------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "scene2d.h"

class CExplosion :public CScene2D
{
public:
	CExplosion();
	~CExplosion();
	static CExplosion *Create(float nPosX, float nPosY);

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(float nPosX, float nPosY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nCounterAnim;		//�J�E���^�[
	int m_nPatternAnim;		//�p�^�[��
};

#endif // !_BULLET_H_
