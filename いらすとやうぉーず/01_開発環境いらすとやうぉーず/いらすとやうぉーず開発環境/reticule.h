//--------------------------
//���e�B�N������[reticule.h]
//--------------------------
#ifndef _RETICULE_H_
#define _RETICULE_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "main.h"
#include "scene2d.h"

//--------------------------
//�N���X
//--------------------------
class CReticule :public CScene2D
{
public:
	CReticule(int nPriority = 10);//�R���X�g���N�^
	~CReticule();//�f�X�g���N�^

	static HRESULT Load(void);//�e�N�X�`���̓ǂݍ���
	static void Unload(void);//�e�N�X�`���̔j��

	static CReticule *Create(float nPosX, float nPosY);//��������

	HRESULT Init(float nPosX, float nPosY);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`���̃|�C���^
};
#endif // !_ENEMY_H_