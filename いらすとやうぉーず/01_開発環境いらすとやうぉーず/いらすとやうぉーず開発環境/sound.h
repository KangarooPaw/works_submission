//=============================================================================
// サウンド処理 [sound.h]
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//--------------------------
//インクルードファイル
//--------------------------
#include "main.h"
#include <xaudio2.h>

//--------------------------
//クラス
//--------------------------
class CSound
{
public:	
	
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;	
	
	typedef enum
	{
		BGM_TITLE=0,		//タイトル
		BGM_MAIN,			//メイン1
		BGM_FENCEBREAK,	//メイン2
		SE_SHOT,				// 弾発射音
		SE_BREAK,			//破壊音
		SE_EXPLOSION,		// ヒット
		SE_RESULT,			//リザルト
		MAX,//最大値
	} LABEL;

	CSound();//コンストラクタ
	~CSound();//デストラクタ

	// 各音素材のパラメータ
	static PARAM g_aParam[MAX];

	HRESULT Init(HWND hWnd);//初期化処理
	void Uninit(void);//終了処理
	HRESULT Play(LABEL label);//再生
	void Stop(LABEL label);//停止
	void Stop(void);//停止

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);//チャンクのチェック
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);//チャンクデータ

private:
	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;	// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[MAX];	// ソースボイス
	BYTE *m_apDataAudio[MAX];					// オーディオデータ
	DWORD m_aSizeAudio[MAX];					// オーディオデータサイズ
};
#endif