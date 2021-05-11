//--------------------------
//����[enemy.h]
//--------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "main.h"
#include "scene2d.h"

//--------------------------
//�}�N����`
//--------------------------
#define ENEMY_LIFE 2

//--------------------------
//�N���X
//--------------------------
class CEnemy :public CScene2D
{
public:
	CEnemy(int nPriority = 7);						//�R���X�g���N�^
	~CEnemy();											//�f�X�g���N�^

	static HRESULT Load(void);						//�e�N�X�`���̓ǂݍ���
	static void Unload(void);							//�e�N�X�`���̔j��

	static CEnemy *Create(float nPosX, float nPosY);//��������

	HRESULT Init(float nPosX, float nPosY);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��

	void HitBullet(void);
	void HitObject(void);
private:
	LPDIRECT3DTEXTURE9 m_apScene[3];
	static LPDIRECT3DTEXTURE9 m_pTexture;
	float	m_move;
	int		m_nLife;
};
#endif // !_ENEMY_H_
