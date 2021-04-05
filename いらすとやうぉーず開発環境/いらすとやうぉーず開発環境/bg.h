//--------------------------
//�w�i�w�b�_�[
//--------------------------
#ifndef _BG_H_
#define _BG_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "scene.h"

//--------------------------
//�O���錾
//--------------------------
class CScene2D;

class CBg :public CScene
{
public:
	CBg(int nPriority=4);											//�R���X�g���N�^
	~CBg();											//�f�X�g���N�^
	static HRESULT Load(void);						//�e�N�X�`���̓ǂݍ���
	static void Unload(void);						// �e�N�X�`���̔j��
	static CBg *Create(float nPosX, float nPosY);	//��������
	HRESULT Init(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight);			//����������
	void Uninit(void);								//�I������	
	void Update(void);
	void Draw(void);								//�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ϐ�
	CScene2D *m_pScene2D;
	float m_TexPos;
};

#endif // !_BG_H_


