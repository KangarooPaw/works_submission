//--------------------------
//レンダラー処理[renderer.h]
//--------------------------
#ifndef _RENDERER_H_
#define _RENDERER_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "main.h"

//--------------------------
//クラス
//--------------------------
class CRenderer
{
public:
	CRenderer();	//コンストラクタ
	~CRenderer();	//デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow);	//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }//デバイスの取得
private:

	void DrawFPS(void);//FPSの描画

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
	LPD3DXFONT				m_pFont = NULL;			// フォントへのポインタ
	int						m_nCountFPS;					// FPSカウンタ
#endif
};
#endif // !_RENDERER_H_