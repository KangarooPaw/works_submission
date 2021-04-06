//--------------------------
//�V�[������[scene.h]
//--------------------------
#ifndef _SCENE_H_
#define _SCENE_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "main.h"

//�I�u�W�F�N�g�N���X
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_FENCE,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_SCORE,
		OBJTYPE_NUMBER,
		OBJTYPE_FADE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority=3);
	virtual ~CScene();

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }
	static CScene *GetScene(int nPriority,int nCnt);
	virtual HRESULT Init(float nPosX, float nPosY,int nPolygonWidth,int nPolygonHeight)=0;	//����������
	virtual void Uninit(void)=0;	//�I������
	virtual void Update(void)=0;	//�X�V����
	virtual void Draw(void)=0;		//�`�揈��

	static void UpdateAll(void);	//�X�V�܂Ƃ�
	static void DrawAll(void);		//�`��܂Ƃ�
	static void ReleaseAll(void);	//�I���܂Ƃ�

protected:	
	void Release(void);

private:
	OBJTYPE m_objType;							//�I�u�W�F�N�g�̎��
	static CScene *m_apScene[PRIORITY][MAX_POLYGON];
	static int m_nNumAll;
	int m_nPriority;
	int m_nID;
	static int	m_nCount;
};

#endif // !_RENDERER_H_