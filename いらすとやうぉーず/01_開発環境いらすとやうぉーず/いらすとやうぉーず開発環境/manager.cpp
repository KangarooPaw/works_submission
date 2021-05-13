//=============================================================================
// �}�l�[�W���[���� [manager.cpp]
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "mouse.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "sound.h"
#include "score.h"
#include "hiscore.h"
#include "number.h"
#include "transition.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "fence.h"
#include "operation.h"
#include "bomb.h"
#include "reticule.h"
#include "game.h"

//=============================================================================
//�X�^�e�B�b�N�ϐ�������
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CSound *CManager::m_pSound = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;
CTransition *CManager::m_pTransition = NULL;
CTitle *CManager::m_pTitle=NULL;
CResult *CManager::m_pResult=NULL;
CFade *CManager::m_pFade = NULL;
COperation *CManager::m_pOperation=NULL;
CScore*CManager::m_pScore = NULL;
CHiscore*CManager::m_pHiscore = NULL;
CGame*CManager::m_pGame = NULL;
int CManager::m_saveScore = 0;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
//����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
{
	//�����_�����O�N���X����	// ����������	
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, TRUE);
	//�}�E�X�N���X����
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);
	//�T�E���h�N���X����
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//TEXTURE�̃��[�h
	LoadAll();
	//�t�F�[�h�N���X����
	m_pFade = CFade::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	//�J��
	CFade::SetFade(m_mode);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CManager::Uninit(void)
{
	CScene::	ReleaseAll();
	//TEXTURE�̏I������
	UnloadAll();
	//�}�E�X�I������
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}
	//�����_���[�̏I��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	//�}�E�X
	m_pInputMouse->Update();
	//�����_���[
	m_pRenderer->Update();
	//�J�ڗp�����X�V
	if (m_pTransition != NULL)
	{
		m_pTransition->Update();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pInputMouse->GetMouseTriggerLeft())
		{
			//�J��
			CFade::SetFade(MODE_OPERATION);
		}
		break;

	case MODE_OPERATION:
		if (m_pInputMouse->GetMouseTriggerLeft())
		{
			//�J��
			CFade::SetFade(MODE_GAME);
		}
		break;

	case MODE_GAME:
		if(m_pGame!=NULL)m_pGame->Update();
		break;

	case MODE_RESULT:
		if (m_pInputMouse->GetMouseTriggerLeft())
		{
			//�J��
			CFade::SetFade(MODE_TITLE);
		}
		break;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//=============================================================================
//�e�N�X�`���̓ǂݍ��݂܂Ƃ�
//=============================================================================
void CManager::LoadAll(void)
{
	CTransition::Load();
	CTitle::Load();
	COperation::Load();
	CResult::Load();
	CFade::Load();
	CBg::Load();
	CPlayer::Load();
	CFence::Load();
	CEnemy::Load();
	CBullet::Load();
	CExplosion::Load();
	CNumber::Load();
	CBomb::Load();
	CReticule::Load();
}

//=============================================================================
//�e�N�X�`���̔j���܂Ƃ�
//=============================================================================
void CManager::UnloadAll(void)
{
	CReticule::Unload();
	CBomb::Unload();
	CNumber::Unload();
	CExplosion::Unload();
	CBullet::Unload();
	CEnemy::Unload();
	CFence::Unload();
	CPlayer::Unload();
	CBg::Unload();
	CFade::Unload();
	CResult::Unload();
	COperation::Unload();
	CTitle::Unload();
	CTransition::Unload();
}

//=============================================================================
//�v���C���[�̎󂯎�菈��
//=============================================================================
CPlayer *CManager::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
//���[�h�ύX����
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_mode = mode;
	switch (m_mode)
	{
	case MODE_TITLE:
		//���U���g�I������
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		//�X�R�A�I������
		if (m_pScore != NULL)
		{
			m_pScore->Uninit();
		}
		//�n�C�X�R�A�I������
		if (m_pHiscore != NULL)
		{
			m_pHiscore->Uninit();
		}
		//�^�C�g������
		m_pTitle = CTitle::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		//�J�ڗp��������
		m_pTransition = CTransition::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		//�T�E���h�Đ�
		m_pSound->Play(CSound::BGM_TITLE);
		break;

	case MODE_OPERATION:
		//�^�C�g���I������
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		//��������
		m_pOperation = COperation::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		break;

	case MODE_GAME:
		//�����I������
		if (m_pOperation != NULL)
		{
			m_pOperation->Uninit();
			delete m_pOperation;
			m_pOperation = NULL;
		}
		//�J�ڗp�����I��
		if (m_pTransition != NULL)
		{
			m_pTransition->Uninit();
			delete m_pTransition;
			m_pTransition = NULL;
		}
		//�T�E���h��~
		if (m_pSound != NULL)
		{
			m_pSound->Stop(CSound::BGM_TITLE);
		}
		//�Q�[���N���X����
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;
			m_pGame->Init();
		}
		//�T�E���h�Đ�
		m_pSound->Play(CSound::BGM_MAIN);
		//�X�R�A����
		m_pScore=CScore::Create(SCREEN_WIDTH - SCORE_WIDTH, SCORE_HEIGHT,SCORE_WIDTH,SCORE_HEIGHT);
		break;

	case MODE_RESULT:
		//�Q�[���̏I��
		if (m_pGame != NULL)
		{
			delete m_pGame;
			m_pGame = NULL;
		}
		//�T�E���h��~
		if (m_pSound != NULL)
		{
			m_pSound->Stop();
		}
		//�T�E���h�Đ�
		m_pSound->Play(CSound::SE_RESULT);
		//�X�R�A�Z�[�u
		m_saveScore = m_pScore->SaveScore();
		//�����[�X
		CScene::ReleaseAll();	
		//�J�[�\���\��
		ShowCursor(true);
		//���U���g����
		m_pResult = CResult::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		//�X�R�A����
		m_pScore=CScore::Create(SCREEN_CENTER_X+SCORE_WIDTH*7, SCREEN_CENTER_Y, SCORE_WIDTH*3, SCORE_HEIGHT*3);
		//�Z�[�u�����X�R�A���Z�b�g
		m_pScore->SetScore(m_saveScore);
		//�n�C�X�R�A����
		m_pHiscore = CHiscore::Create(SCREEN_CENTER_X + SCORE_WIDTH * 7,125, SCORE_WIDTH * 3, SCORE_HEIGHT * 3);
		//�n�C�X�R�A�ƃX�R�A���ׂ�
		m_pHiscore->compareHiScore(m_saveScore);
		break;
	}
}


//=============================================================================
//���[�h�̎󂯎��
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
//�����_���[�̎󂯎��
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;	
}

//=============================================================================
//�}�E�X�̎󂯎��
//=============================================================================
CInputMouse * CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//=============================================================================
//�T�E���h�̎󂯎��
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
//�t�F�[�h�̎󂯎��
//=============================================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}