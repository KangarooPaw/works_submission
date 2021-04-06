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

class CFade
{
public:
	typedef enum
	{
		FADE_NONE=0,
		FADE_IN,
		FADE_OUT
	}FADE;

	CFade();											//�R���X�g���N�^
	~CFade();											//�f�X�g���N�^
	static HRESULT Load(void);
	static void Unload(void);
	static CFade *Create(float nPosX, float nPosY);		//��������
	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//����������
	void Uninit(void);									//�I������	
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	static void SetFade(CManager::MODE mode);			//�t�F�[�h����
	void FadeIn(void);									//�t�F�[�h�C������
	void FadeOut(void);									//�t�F�[�h�A�E�g����
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D				*m_pScene2D;
	int						m_nFade;
	static CManager::MODE	m_mode;
	static FADE				m_fade;
};
#endif // !_FADE_H_
