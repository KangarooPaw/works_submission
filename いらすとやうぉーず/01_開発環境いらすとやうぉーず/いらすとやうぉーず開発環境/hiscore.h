//--------------------------
//ハイスコア処理[hiscore.h]
//--------------------------
#ifndef _HISCORE_H_
#define _HISCORE_H_


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
class CHiscore :public CScene
{
public:
	CHiscore(int nPriority = 5);	//コンストラクタ
	~CHiscore();						//デストラクタ

	static CHiscore *Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//生成処理

	HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理

	void SetHiScore();//ハイスコアをセット

	void FileLoad();//ファイルの読み込み
	void FileSave();//ファイルの書き込み

	void compareHiScore(int nScore);//スコアとハイスコアを比べる

private:
	CNumber *m_apNumber[MAX_NUMBER];//数字のポインタ
	int m_nHiScore;								//ハイスコア情報

	FILE* m_fp;//ファイルポインタ
};
#endif // !_HISCORE_H_
