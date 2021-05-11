//--------------------------
//シーン2D処理[scene2d.h]
//--------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "main.h"
#include "scene.h"
#include "manager.h"

//--------------------------
//前方宣言
//--------------------------
class CManager;

class CScene2D :public CScene
{
public:
	CScene2D();//コンストラクタ
	~CScene2D();//デストラクタ

	static CScene2D *Create(float nPosX, float nPosY);//生成処理

	HRESULT Init(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);//テクスチャの設定
	void SetPosition(D3DXVECTOR3 pos);		//位置
	void SetAnimation(int nPatternAnim);	//アニメーション
	void SetAlpha(int alpha);						//アルファ値
	void SetColor(int col);							//カラー

	D3DXVECTOR3 GetPosition(void);			//位置の取得

	void SetRotVertex(float sizeX,float sizeY,float fAngle);//角度のセット
	void SetEnemyTex(float texX1,float texX2,float texY1, float texY2);//エネミーのテクスチャセット
private:	
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	int						m_PolygonWidth;			// ポリゴンの幅
	int						m_PolygonHeight;			// ポリゴンの高さ
	int 					m_Alpha;						// アルファ値
	int						m_Color;						// カラー値
	float					m_angleX, m_angleY;		// 角度
};
#endif // !_SCENE2D_H_