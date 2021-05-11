//--------------------------
//�e����[bullet.h]
//--------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "scene2d.h"

//--------------------------
//�N���X
//--------------------------
class CBullet:public CScene2D
{
public:
	CBullet(int nPriority = 6);					//�R���X�g���N�^
	~CBullet();										//�f�X�g���N�^
	
	static HRESULT Load(void);					//�e�N�X�`���̓ǂݍ���
	static void Unload(void);						//�e�N�X�`���̔j��

	static CBullet *Create(float nPosX, float nPosY);//��������

	HRESULT Init(float nPosX, float nPosY);	//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	float m_fMove;										//�ړ���
	float m_angleX, m_angleY;						//�p�x
	bool m_bHit;											//�q�b�g�t���O
};
#endif // !_BULLET_H_