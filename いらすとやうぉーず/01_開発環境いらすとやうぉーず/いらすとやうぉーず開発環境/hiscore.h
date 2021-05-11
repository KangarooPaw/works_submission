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

//--------------------------
//�N���X
//--------------------------
class CHiscore :public CScene
{
public:
	CHiscore(int nPriority = 5);	//�R���X�g���N�^
	~CHiscore();						//�f�X�g���N�^

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
	CNumber *m_apNumber[MAX_NUMBER];//�����̃|�C���^
	int m_nHiScore;								//�n�C�X�R�A���

	FILE* m_fp;//�t�@�C���|�C���^
};
#endif // !_HISCORE_H_
