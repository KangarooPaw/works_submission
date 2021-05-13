//--------------------------
//マネージャー処理[manager.h]
//--------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "main.h"

//--------------------------
//前方宣言
//--------------------------
class CRenderer;
class CInputMouse;
class CPlayer;
class CSound;
class CTransition;
class CTitle;
class CResult;
class CFade;
class COperation;
class CScore;
class CHiscore;
class CGame;

//--------------------------
//クラス
//--------------------------
class CManager
{
public:
	//モードの構造体
	typedef enum
	{
		MODE_TITLE=0,		//タイトル
		MODE_OPERATION,	//説明
		MODE_GAME,			//ゲーム
		MODE_RESULT,		//リザルト
		MODE_END			//終了
	}MODE;

	CManager();		//コンストラクタ
	~CManager();	//デストラクタ

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindouw);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理

	void LoadAll(void);//テクスチャの読み込みまとめ
	void UnloadAll(void);//テクスチャの破棄まとめ
	CPlayer *GetPlayer(void);//プレイヤーの取得

	static void SetMode(MODE mode);//モードのセット
	static MODE GetMode(void);//モードの取得

	static CRenderer *GetRenderer(void);//レンダラーの取得
	static CInputMouse *GetInputMouse(void);//マウスの取得
	static CSound *GetSound(void);//サウンドの取得
	static CFade *GetFade(void);//フェードの取得

private:
	//方向の構造体
	typedef enum
	{
		DIRECTION_UP=0,//上
		DIRECTION_DOWN,//下
		DIRECTION_LEFT,//左
		DIRECTION_RIGHT,//右
		DIRECTION_MAX//最大値
	}DIRECTION;

	//ポインタ
	static CRenderer *m_pRenderer;//レンダラー
	static CInputMouse *m_pInputMouse;//マウス
	static MODE m_mode;//モード
	static CFade *m_pFade;//フェード
	static CTransition *m_pTransition;//遷移
	static CTitle *m_pTitle;//タイトル
	static COperation *m_pOperation;//説明
	static CResult *m_pResult;//リザルト
	static CPlayer *m_pPlayer;//プレイヤー
	static CScore *m_pScore;//スコア
	static CHiscore *m_pHiscore;//ハイスコア
	static CSound *m_pSound;//サウンド
	static CGame *m_pGame;//ゲームメイン

	static int m_saveScore;//スコア情報のセーブ
};	
#endif // !_MANAGER_H_