//--------------------------
//����[fade.h]
//--------------------------
#ifndef _FADE_H_
#define _FADE_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "renderer.h"
#include "manager.h"

//--------------------------
//�O���錾
//--------------------------
class CScene2D;

//--------------------------
//�N���X
//--------------------------
class CFade
{
public:
	//�t�F�[�h�̍\����
	typedef enum
	{
		FADE_NONE=0,
		FADE_IN,
		FADE_OUT
	}FADE;

	CFade();											//�R���X�g���N�^
	~CFade();											//�f�X�g���N�^

	static HRESULT Load(void);					//�e�N�X�`���̓ǂݍ���
	static void Unload(void);						//�e�N�X�`���̔j��

	static CFade *Create(float nPosX, float nPosY);		//��������

	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//����������
	void Uninit(void);									//�I������	
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��

	static void SetFade(CManager::MODE mode);			//�t�F�[�h����

	void FadeIn(void);									//�t�F�[�h�C������
	void FadeOut(void);									//�t�F�[�h�A�E�g����
private:	
	static LPDIRECT3DTEXTURE9 m_pTexture;					//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D *m_pScene2D;										//�V�[���̃|�C���^
	int	 m_nFade;													//�t�F�[�h�̃A���t�@�l
	static CManager::MODE m_mode;								//���[�h���
	static FADE m_fade;											//�t�F�[�h���
};
#endif // !_FADE_H_