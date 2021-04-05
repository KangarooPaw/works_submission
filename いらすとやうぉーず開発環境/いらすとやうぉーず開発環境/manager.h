#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"

//前方宣言
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CPlayer;
class CSound;
class CTransition;
class CTitle;
class CResult;
class CFade;
class COperation;
class CScore;

//マネージャークラス
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE=0,
		MODE_OPERATION,
		MODE_GAME,
		MODE_RESULT,
		MODE_END
	}MODE;

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindouw);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void LoadAll(void);
	void UnloadAll(void);
	CPlayer *GetPlayer(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void);

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputMouse *GetInputMouse(void);
	static CSound *GetSound(void);
	static CFade *GetFade(void);

private:
	typedef enum
	{
		DIRECTION_UP=0,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
		DIRECTION_MAX
	}DIRECTION;
	static CPlayer *m_pPlayer;
	static CTransition *m_pTransition;
	static CTitle *m_pTitle;
	static CFade *m_pFade;
	static COperation *m_pOperation;
	static CResult *m_pResult;
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputMouse *m_pInputMouse;
	static CScore *m_pScore;
	static CSound *m_pSound;
	static MODE m_mode;
	int m_enemyPopTime;
	int m_PopSpeed;
	static int m_saveScore;

	int nPosX;
	int nPosY;			
};	




#endif // !_MANAGER_H_
