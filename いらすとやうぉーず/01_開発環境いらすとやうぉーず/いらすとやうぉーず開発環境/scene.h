//--------------------------
//�V�[������[scene.h]
//--------------------------
#ifndef _SCENE_H_
#define _SCENE_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "main.h"

//--------------------------
//�N���X
//--------------------------
class CScene
{
public:
	//�I�u�W�F�N�g�^�C�v�̍\����
	typedef enum
	{
		OBJTYPE_NONE = 0,		//����
		OBJTYPE_PLAYER,		//�v���C���[
		OBJTYPE_FENCE,			//�t�F���X
		OBJTYPE_ENEMY,		//�G�l�~�[
		OBJTYPE_BULLET,		//�e
		OBJTYPE_SCORE,		//�X�R�A
		OBJTYPE_NUMBER,		//�i���o�[
		OBJTYPE_FADE,			//�t�F�[�h
		OBJTYPE_MAX			//�ő�l
	}OBJTYPE;

	CScene(int nPriority=3);//�R���X�g���N�^
	virtual ~CScene();//�f�X�g���N�^

	void SetObjType(OBJTYPE objType);//�I�u�W�F�N�g�^�C�v�̃Z�b�g
	OBJTYPE GetObjType(void) { return m_objType; }//�I�u�W�F�N�g�^�C�v�̎擾
	static CScene *GetScene(int nPriority,int nCnt);//�V�[���̎擾

	virtual HRESULT Init(float nPosX, float nPosY,int nPolygonWidth,int nPolygonHeight)=0;	//����������
	virtual void Uninit(void)=0;	//�I������
	virtual void Update(void)=0;	//�X�V����
	virtual void Draw(void)=0;	//�`�揈��

	static void UpdateAll(void);	//�X�V�܂Ƃ�
	static void DrawAll(void);		//�`��܂Ƃ�
	static void ReleaseAll(void);	//�I���܂Ƃ�

protected:	
	void Release(void);//�����[�X����

private:
	OBJTYPE m_objType;							//�I�u�W�F�N�g�̎��
	static CScene *m_apScene[PRIORITY][MAX_POLYGON];//�V�[���̃|�C���^
	static int m_nNumAll;
	int m_nPriority;//�v���C�I���e�B
	int m_nID;
	static int	m_nCount;
};

#endif // !_RENDERER_H_