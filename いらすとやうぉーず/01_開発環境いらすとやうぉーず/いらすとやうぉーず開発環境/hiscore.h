//--------------------------
//�n�C�X�R�A����[hiscore.h]
//--------------------------
#ifndef _HISCORE_H_
#define _HISCORE_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "scene.h"
#include "main.h"

//--------------------------
//�O���錾
//--------------------------
class CNumber;
class CScene2D;

//--------------------------
//�N���X
//--------------------------
class CHiscore :public CScene
{
public:
	CHiscore(int nPriority = 5);	//�R���X�g���N�^
	~CHiscore();						//�f�X�g���N�^

	static HRESULT Load(void);					//�e�N�X�`���̓ǂݍ���
	static void Unload(void);						// �e�N�X�`���̔j��

	static CHiscore *Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//��������

	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��

	void SetHiScore();//�n�C�X�R�A���Z�b�g

	void FileLoad();//�t�@�C���̓ǂݍ���
	void FileSave();//�t�@�C���̏�������

	void compareHiScore(int nScore);//�X�R�A�ƃn�C�X�R�A���ׂ�

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���̃|�C���^
	CScene2D *m_pScene2D;		//�V�[���̃|�C���^

	CNumber *m_apNumber[MAX_NUMBER];//�����̃|�C���^
	int m_nHiScore;								//�n�C�X�R�A���

	FILE* m_fp;//�t�@�C���|�C���^
};
#endif // !_HISCORE_H_
