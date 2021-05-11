//--------------------------
//����[fence.h]
//--------------------------
#ifndef _FENCE_H_
#define _FENCE_H_

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
class CFence :public CScene2D
{
public:
	CFence(int nPriority = 2);	//�R���X�g���N�^
	~CFence();						//�f�X�g���N�^

	static CFence*Create(float nPosX, float nPosY,int type);//��������

	static HRESULT Load(void);					//�e�N�X�`���̓ǂݍ���
	static void Unload(void);						//�e�N�X�`���̔j��

	HRESULT Init(float nPosX, float nPosY);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[2];	//�e�N�X�`���̃|�C���^
	static int	 m_fanceCnt;							//�t�F���X�J�E���g
	bool m_Deathflag;									//���S�t���O
	int m_type;											//�^�C�v���
	int m_Life;											//�̗͏��
};
#endif // !_FENCE_H_