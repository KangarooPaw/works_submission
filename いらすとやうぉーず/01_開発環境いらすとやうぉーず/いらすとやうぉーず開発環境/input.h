//--------------------------
//����[input.h]
//--------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "main.h"

//--------------------------
//�N���X
//--------------------------
class CInput
{
public:
	CInput();//�R���X�g���N�^
	virtual ~CInput();//�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);//����������
	virtual void Uninit(void);//�I������
	virtual void Update(void) = 0;//�X�V����
protected:
	static LPDIRECTINPUT8 m_pInput;//�C���v�b�g�̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pInputDevice;//�C���v�b�g�f�o�C�X�̃|�C���^
};
#endif // !_INPUT_H_