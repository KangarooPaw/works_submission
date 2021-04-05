#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene2d.h"

#define ENEMY_LIFE 2

class CEnemy :public CScene2D
{
public:
	CEnemy(int nPriority = 7);
	~CEnemy();
	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy *Create(float nPosX, float nPosY);
	HRESULT Init(float nPosX, float nPosY);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	void HitBullet(void);
	void HitObject(void);
private:
	LPDIRECT3DTEXTURE9 m_apScene[3];
	static LPDIRECT3DTEXTURE9 m_pTexture;
	float	m_move;
	int		m_nLife;
};
#endif // !_ENEMY_H_
