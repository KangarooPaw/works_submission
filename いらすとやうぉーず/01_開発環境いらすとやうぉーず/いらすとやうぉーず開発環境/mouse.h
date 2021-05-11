//--------------------------
//�}�E�X����[mouse.h]
//--------------------------
#ifndef	_MOUSE_H_
#define _MOUSE_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "input.h"

//--------------------------
//�N���X
//--------------------------
class CInputMouse : public CInput 
{
public:
	typedef struct _MSTATE {
		RECT    moveRect;     // ��ʏ�œ�����͈�
		int     x;            // X���W
		int     y;            // Y���W
		bool    lButton;      // ���{�^��
		bool    rButton;      // �E�{�^��
		bool    cButton;      // �^�񒆃{�^��
		int     moveAdd;      // �ړ���
		RECT    imgRect;      // �}�E�X�p�摜��`
		int     imgWidth;     // �}�E�X�摜��
		int     imgHeight;    // �}�E�X�摜����
	} MSTATE;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����

	static MSTATE *GetMouse(void);//�}�E�X�擾
	//���N���b�N
	bool GetMouseTriggerLeft(void);
	bool GetMousePressLeft(void);
	bool GetMouseReleaseLeft(void);
	//�E�N���b�N
	bool GetMouseTriggerRight(void);
	bool GetMouseReleaseRight(void);

private:
	DIMOUSESTATE2 m_dIMouseState;
	static CInputMouse::MSTATE m_MState;
};

#endif