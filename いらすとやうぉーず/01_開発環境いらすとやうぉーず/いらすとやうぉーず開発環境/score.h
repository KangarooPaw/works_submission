//--------------------------
//スコア処理[score.h]
//--------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "scene.h"
#include "main.h"

//--------------------------
//前方宣言
//--------------------------
class CNumber;

//--------------------------
//クラス
//--------------------------
class CScore:public CScene
{
public:
	CScore(int nPriority = 5);//コンストラクタ
	~CScore();//デストラクタ

	static CScore *Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//生成処理

	HRESULT Init(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理

	void SetScore(int nScore);//スコアのセット
	void AddScore(int nValue);//スコアの加算

	int GetScore(void);//スコアの取得
	int SaveScore(void);//スコアのセーブ
private:
	CNumber *m_apNumber[MAX_NUMBER];//数字のポインタ
	int m_nScore;//スコアの情報
};
#endif // !_SCORE_H_