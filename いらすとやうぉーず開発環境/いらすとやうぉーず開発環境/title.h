//--------------------------
//�^�C�g������[title.h]
//--------------------------
#ifndef _TITLE_H_
#define _TITLE_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "renderer.h"

class CScene2D;

class CTitle
{
public:
	CTitle();											//�R���X�g���N�^
	~CTitle();											//�f�X�g���N�^
	static HRESULT Load(void);						//�e�N�X�`���̓ǂݍ���
	static void Unload(void);						// �e�N�X�`���̔j��
	static CTitle *Create(float nPosX, float nPosY);	//��������
	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);			//����������
	void Uninit(void);								//�I������	
	void Update(void);
	void Draw(void);								//�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ϐ�
	CScene2D *m_pScene2D;
};
#endif // !_TITLE_H_
