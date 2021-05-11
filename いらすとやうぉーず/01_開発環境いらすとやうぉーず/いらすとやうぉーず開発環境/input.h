//--------------------------
//処理[input.h]
//--------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "main.h"

//--------------------------
//クラス
//--------------------------
class CInput
{
public:
	CInput();//コンストラクタ
	virtual ~CInput();//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);//初期化処理
	virtual void Uninit(void);//終了処理
	virtual void Update(void) = 0;//更新処理
protected:
	static LPDIRECTINPUT8 m_pInput;//インプットのポインタ
	LPDIRECTINPUTDEVICE8 m_pInputDevice;//インプットデバイスのポインタ
};
#endif // !_INPUT_H_