//=============================================================================
// �T�E���h���� [sound.h]
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "main.h"
#include <xaudio2.h>

//--------------------------
//�N���X
//--------------------------
class CSound
{
public:	
	
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;	
	
	typedef enum
	{
		BGM_TITLE=0,		//�^�C�g��
		BGM_MAIN,			//���C��1
		BGM_FENCEBREAK,	//���C��2
		SE_SHOT,				// �e���ˉ�
		SE_BREAK,			//�j��
		SE_EXPLOSION,		// �q�b�g
		SE_RESULT,			//���U���g
		MAX,//�ő�l
	} LABEL;

	CSound();//�R���X�g���N�^
	~CSound();//�f�X�g���N�^

	// �e���f�ނ̃p�����[�^
	static PARAM g_aParam[MAX];

	HRESULT Init(HWND hWnd);//����������
	void Uninit(void);//�I������
	HRESULT Play(LABEL label);//�Đ�
	void Stop(LABEL label);//��~
	void Stop(void);//��~

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);//�`�����N�̃`�F�b�N
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);//�`�����N�f�[�^

private:
	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;	// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};
#endif