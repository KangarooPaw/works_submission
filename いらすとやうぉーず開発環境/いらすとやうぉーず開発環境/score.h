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

class CScore:public CScene
{
public:
	CScore(int nPriority = 5);
	~CScore();
	static CScore *Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);

	HRESULT Init(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetScore(int nScore);
	void AddScore(int nValue);

	int GetScore(void);
	int SaveScore(void);
private:
	CNumber *m_apNumber[MAX_NUMBER];
	int m_nScore;
};
#endif // !_SCORE_H_
