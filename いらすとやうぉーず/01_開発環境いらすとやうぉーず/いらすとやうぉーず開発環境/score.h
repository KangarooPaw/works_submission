//--------------------------
//�X�R�A����[score.h]
//--------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

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
class CScore:public CScene
{
public:
	CScore(int nPriority = 5);//�R���X�g���N�^
	~CScore();//�f�X�g���N�^

	static CScore *Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//��������

	HRESULT Init(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��

	void SetScore(int nScore);//�X�R�A�̃Z�b�g
	void AddScore(int nValue);//�X�R�A�̉��Z

	int GetScore(void);//�X�R�A�̎擾
	int SaveScore(void);//�X�R�A�̃Z�[�u
private:
	CNumber *m_apNumber[MAX_NUMBER];//�����̃|�C���^
	int m_nScore;//�X�R�A�̏��
};
#endif // !_SCORE_H_