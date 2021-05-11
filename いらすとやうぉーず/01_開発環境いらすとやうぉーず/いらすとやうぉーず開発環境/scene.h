//--------------------------
//シーン処理[scene.h]
//--------------------------
#ifndef _SCENE_H_
#define _SCENE_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "main.h"

//--------------------------
//クラス
//--------------------------
class CScene
{
public:
	//オブジェクトタイプの構造体
	typedef enum
	{
		OBJTYPE_NONE = 0,		//無し
		OBJTYPE_PLAYER,		//プレイヤー
		OBJTYPE_FENCE,			//フェンス
		OBJTYPE_ENEMY,		//エネミー
		OBJTYPE_BULLET,		//弾
		OBJTYPE_SCORE,		//スコア
		OBJTYPE_NUMBER,		//ナンバー
		OBJTYPE_FADE,			//フェード
		OBJTYPE_MAX			//最大値
	}OBJTYPE;

	CScene(int nPriority=3);//コンストラクタ
	virtual ~CScene();//デストラクタ

	void SetObjType(OBJTYPE objType);//オブジェクトタイプのセット
	OBJTYPE GetObjType(void) { return m_objType; }//オブジェクトタイプの取得
	static CScene *GetScene(int nPriority,int nCnt);//シーンの取得

	virtual HRESULT Init(float nPosX, float nPosY,int nPolygonWidth,int nPolygonHeight)=0;	//初期化処理
	virtual void Uninit(void)=0;	//終了処理
	virtual void Update(void)=0;	//更新処理
	virtual void Draw(void)=0;	//描画処理

	static void UpdateAll(void);	//更新まとめ
	static void DrawAll(void);		//描画まとめ
	static void ReleaseAll(void);	//終了まとめ

protected:	
	void Release(void);//リリース処理

private:
	OBJTYPE m_objType;							//オブジェクトの種類
	static CScene *m_apScene[PRIORITY][MAX_POLYGON];//シーンのポインタ
	static int m_nNumAll;
	int m_nPriority;//プライオリティ
	int m_nID;
	static int	m_nCount;
};

#endif // !_RENDERER_H_