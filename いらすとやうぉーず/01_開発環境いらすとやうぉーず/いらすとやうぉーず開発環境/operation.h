//--------------------------
//��������`�揈��[operation.h]
//--------------------------
#ifndef _OPERATION_H_
#define _OPERATION_H_

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
class COperation
{
public:
	COperation();										//�R���X�g���N�^
	~COperation();										//�f�X�g���N�^
	static HRESULT Load(void);						//�e�N�X�`���̓ǂݍ���
	static void Unload(void);							// �e�N�X�`���̔j��
	static COperation *Create(float nPosX, float nPosY);	//��������
	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);			//����������
	void Uninit(void);								//�I������	
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	CScene2D *m_pScene2D;							//�V�[���̃|�C���^
};
#endif // !_OPERATION_H_