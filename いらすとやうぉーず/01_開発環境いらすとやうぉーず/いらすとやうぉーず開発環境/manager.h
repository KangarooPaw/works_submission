//--------------------------
//�}�l�[�W���[����[manager.h]
//--------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "main.h"

//--------------------------
//�O���錾
//--------------------------
class CRenderer;
class CInputMouse;
class CPlayer;
class CSound;
class CTransition;
class CTitle;
class CResult;
class CFade;
class COperation;
class CScore;
class CHiscore;
class CGame;

//--------------------------
//�N���X
//--------------------------
class CManager
{
public:
	//���[�h�̍\����
	typedef enum
	{
		MODE_TITLE=0,		//�^�C�g��
		MODE_OPERATION,	//����
		MODE_GAME,			//�Q�[��
		MODE_RESULT,		//���U���g
		MODE_END			//�I��
	}MODE;

	CManager();		//�R���X�g���N�^
	~CManager();	//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindouw);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��

	void LoadAll(void);//�e�N�X�`���̓ǂݍ��݂܂Ƃ�
	void UnloadAll(void);//�e�N�X�`���̔j���܂Ƃ�
	CPlayer *GetPlayer(void);//�v���C���[�̎擾

	static void SetMode(MODE mode);//���[�h�̃Z�b�g
	static MODE GetMode(void);//���[�h�̎擾

	static CRenderer *GetRenderer(void);//�����_���[�̎擾
	static CInputMouse *GetInputMouse(void);//�}�E�X�̎擾
	static CSound *GetSound(void);//�T�E���h�̎擾
	static CFade *GetFade(void);//�t�F�[�h�̎擾

private:
	//�����̍\����
	typedef enum
	{
		DIRECTION_UP=0,//��
		DIRECTION_DOWN,//��
		DIRECTION_LEFT,//��
		DIRECTION_RIGHT,//�E
		DIRECTION_MAX//�ő�l
	}DIRECTION;

	//�|�C���^
	static CRenderer *m_pRenderer;//�����_���[
	static CInputMouse *m_pInputMouse;//�}�E�X
	static MODE m_mode;//���[�h
	static CFade *m_pFade;//�t�F�[�h
	static CTransition *m_pTransition;//�J��
	static CTitle *m_pTitle;//�^�C�g��
	static COperation *m_pOperation;//����
	static CResult *m_pResult;//���U���g
	static CPlayer *m_pPlayer;//�v���C���[
	static CScore *m_pScore;//�X�R�A
	static CHiscore *m_pHiscore;//�n�C�X�R�A
	static CSound *m_pSound;//�T�E���h
	static CGame *m_pGame;//�Q�[�����C��

	static int m_saveScore;//�X�R�A���̃Z�[�u
};	
#endif // !_MANAGER_H_