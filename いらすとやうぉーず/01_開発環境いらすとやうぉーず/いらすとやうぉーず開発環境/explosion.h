//--------------------------
//����[explosion.h]
//--------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "scene2d.h"

//--------------------------
//�N���X
//--------------------------
class CExplosion :public CScene2D
{
public:
	CExplosion();				//�R���X�g���N�^
	~CExplosion();				//�f�X�g���N�^

	static HRESULT Load(void);	//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��

	static CExplosion *Create(float nPosX, float nPosY);//��������

	HRESULT Init(float nPosX, float nPosY);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	int m_nCounterAnim;		//�J�E���^�[
	int m_nPatternAnim;		//�p�^�[��
};
#endif // !_BULLET_H_