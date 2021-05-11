//--------------------------
//�����`�揈��[number.h]
//--------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "main.h"

//--------------------------
//�N���X
//--------------------------
class CNumber
{
public:
	CNumber();		//�R���X�g���N�^
	~CNumber();		//�f�X�g���N�^

	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);			//�e�N�X�`���̔j��

	static CNumber *Create(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight);//��������

	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void SetNumber(int nNumber);//�����̃Z�b�g
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//���_�o�b�t�@
	int m_nNumber;//�������
};
#endif