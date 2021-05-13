//--------------------------
//ハイスコア処理[hiscore.h]
//--------------------------
#ifndef _GAME_H_
#define _GAME_H_

//--------------------------
//クラス
//--------------------------
class CGame
{
public:
	CGame();		//コンストラクタ
	~CGame();	//デストラクタ

	void Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理

private:
	//方向の構造体
	typedef enum
	{
		DIRECTION_UP = 0,//上
		DIRECTION_DOWN,//下
		DIRECTION_LEFT,//左
		DIRECTION_RIGHT,//右
		DIRECTION_MAX//最大値
	}DIRECTION;

	int m_enemyPopTime;//エネミー生成タイミング
	int m_PopSpeed;//エネミー生成速度
	int nPosX, nPosY;//エネミー生成時の座標
};
#endif //_GAME_H_