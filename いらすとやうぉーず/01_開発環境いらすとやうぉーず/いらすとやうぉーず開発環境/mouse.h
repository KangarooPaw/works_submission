//--------------------------
//マウス処理[mouse.h]
//--------------------------
#ifndef	_MOUSE_H_
#define _MOUSE_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "input.h"

//--------------------------
//クラス
//--------------------------
class CInputMouse : public CInput 
{
public:
	typedef struct _MSTATE {
		RECT    moveRect;     // 画面上で動ける範囲
		int     x;            // X座標
		int     y;            // Y座標
		bool    lButton;      // 左ボタン
		bool    rButton;      // 右ボタン
		bool    cButton;      // 真ん中ボタン
		int     moveAdd;      // 移動量
		RECT    imgRect;      // マウス用画像矩形
		int     imgWidth;     // マウス画像幅
		int     imgHeight;    // マウス画像高さ
	} MSTATE;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理

	static MSTATE *GetMouse(void);//マウス取得
	//左クリック
	bool GetMouseTriggerLeft(void);
	bool GetMousePressLeft(void);
	bool GetMouseReleaseLeft(void);
	//右クリック
	bool GetMouseTriggerRight(void);
	bool GetMouseReleaseRight(void);

private:
	DIMOUSESTATE2 m_dIMouseState;
	static CInputMouse::MSTATE m_MState;
};

#endif