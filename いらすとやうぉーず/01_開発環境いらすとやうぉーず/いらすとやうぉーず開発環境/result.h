//--------------------------
//���U���g����[result.h]
//--------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "renderer.h"

//--------------------------
//�O���錾
//--------------------------
class CScene2D;

class CResult 
{
	public:
		CResult(int nPriority = 4);											//�R���X�g���N�^
		~CResult();											//�f�X�g���N�^
		static HRESULT Load(void);						//�e�N�X�`���̓ǂݍ���
		static void Unload(void);						// �e�N�X�`���̔j��
		static CResult *Create(float nPosX, float nPosY);	//��������
		HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);			//����������
		void Uninit(void);								//�I������	
		void Update(void);								//�X�V����
		void Draw(void);								//�`�揈��

	private:
		static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ϐ�
		CScene2D *m_pScene2D;
};
#endif // !_RESULT_H_
