//--------------------------
//�V�[��2D����[scene2d.h]
//--------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "main.h"
#include "scene.h"
#include "manager.h"

//--------------------------
//�O���錾
//--------------------------
class CManager;

class CScene2D :public CScene
{
public:
	CScene2D();//�R���X�g���N�^
	~CScene2D();//�f�X�g���N�^

	static CScene2D *Create(float nPosX, float nPosY);//��������

	HRESULT Init(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);//�e�N�X�`���̐ݒ�
	void SetPosition(D3DXVECTOR3 pos);		//�ʒu
	void SetAnimation(int nPatternAnim);	//�A�j���[�V����
	void SetAlpha(int alpha);						//�A���t�@�l
	void SetColor(int col);							//�J���[

	D3DXVECTOR3 GetPosition(void);			//�ʒu�̎擾

	void SetRotVertex(float sizeX,float sizeY,float fAngle);//�p�x�̃Z�b�g
	void SetEnemyTex(float texX1,float texX2,float texY1, float texY2);//�G�l�~�[�̃e�N�X�`���Z�b�g
private:	
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �|���S���̈ʒu
	int						m_PolygonWidth;			// �|���S���̕�
	int						m_PolygonHeight;			// �|���S���̍���
	int 					m_Alpha;						// �A���t�@�l
	int						m_Color;						// �J���[�l
	float					m_angleX, m_angleY;		// �p�x
};
#endif // !_SCENE2D_H_