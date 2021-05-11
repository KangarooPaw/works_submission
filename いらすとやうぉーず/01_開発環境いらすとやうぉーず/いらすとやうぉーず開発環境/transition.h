//--------------------------
//�J�ڂ𑣂������̕`�揈��[transition.h]
//--------------------------
#ifndef _TRANSITION_H_
#define _TRANSITION_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "renderer.h"

//--------------------------
//�O���錾
//--------------------------
class CScene2D;

//--------------------------
//�N���X
//--------------------------
class CTransition
{
public:
	CTransition();									//�R���X�g���N�^
	~CTransition();									//�f�X�g���N�^

	static HRESULT Load(void);					//�e�N�X�`���̓ǂݍ���
	static void Unload(void);						// �e�N�X�`���̔j��

	static CTransition *Create(float nPosX, float nPosY);	//��������

	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);			//����������
	void Uninit(void);								//�I������	
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	CScene2D *m_pScene2D;		//�V�[���̃|�C���^
	bool m_bMinus;					//�A���t�@�l�̌��Z����
	int m_nAlpha;					//�A���t�@�l
};
#endif // !_TITLE_H_