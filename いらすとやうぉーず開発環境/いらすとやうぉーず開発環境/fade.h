#ifndef _FADE_H_
#define _FADE_H_
#include "renderer.h"
#include "manager.h"

class CScene2D;
class CFade
{
public:
	typedef enum
	{
		FADE_NONE=0,
		FADE_IN,
		FADE_OUT
	}FADE;

	CFade();											//コンストラクタ
	~CFade();											//デストラクタ
	static HRESULT Load(void);
	static void Unload(void);
	static CFade *Create(float nPosX, float nPosY);	//生成処理
	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);			//初期化処理
	void Uninit(void);								//終了処理	
	void Update(void);
	void Draw(void);								//描画処理
	static void SetFade(CManager::MODE mode);
	void FadeIn(void);
	void FadeOut(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	int						m_PolygonWidth;
	int						m_PolygonHeight;
	CScene2D				*m_pScene2D;
	float					m_TexPos;
	int						m_nFade;
	static CManager::MODE	m_mode;
	static FADE				m_fade;
};
#endif // !_FADE_H_
