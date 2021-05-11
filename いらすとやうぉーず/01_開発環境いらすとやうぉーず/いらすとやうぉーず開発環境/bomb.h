//--------------------------
//���e����[bomb.h]
//--------------------------
#ifndef _BOMB_H_
#define _BOMB_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "scene2d.h"

//--------------------------
//�O���錾
//--------------------------
class CManager;

//--------------------------
//�N���X
//--------------------------
class CBomb:public CScene2D
{
public:
	CBomb(int nPriority = 9);				//�R���X�g���N�^
	~CBomb();								//�f�X�g���N�^

	static HRESULT Load(void);						//�e�N�X�`���̓ǂݍ���
	static void Unload(void);							//�e�N�X�`���̔j��

	static CBomb*Create(float nPosX, float nPosY);		//��������

	HRESULT Init(float nPosX, float nPosY);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	bool m_bUse;											//���e�g�p����
};
#endif // !_PLAYER_H_