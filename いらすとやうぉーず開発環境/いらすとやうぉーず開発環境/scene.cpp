//=============================================================================
//�V�[������[scene.cpp]
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "scene2d.h"
#include "enemy.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
CScene *CScene::m_apScene[PRIORITY][MAX_POLYGON] = {};
int CScene::m_nNumAll = 0;
int CScene::m_nCount = 0;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
	{
		if (m_apScene[nPriority][nCount] == NULL)
		{
			m_apScene[nPriority][nCount] = this;
			m_objType = OBJTYPE_NONE;
			m_nPriority = nPriority;
			m_nID = nCount;
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//�I�u�W�F�N�g�ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}


//=============================================================================
//�V�[���擾
//=============================================================================
CScene * CScene::GetScene(int nPriority,int nCnt)
{
	return m_apScene[nPriority][nCnt];
}

//=============================================================================
//�����[�X�����܂Ƃ�
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		// �|���S���̏I������
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nCountpriority][nCount] != NULL)
			{
				if (m_apScene[nCountpriority][nCount]->GetObjType() != OBJTYPE_FADE)
				{
					m_apScene[nCountpriority][nCount]->Uninit();
				}
			}
		}
	}
}

//=============================================================================
//�X�V�����܂Ƃ�
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		// �|���S���̍X�V����
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nCountpriority][nCount] != NULL)
			{
				m_apScene[nCountpriority][nCount]->Update();
			}
		}
	}
}

//=============================================================================
//�`�揈���܂Ƃ�
//=============================================================================
void CScene::DrawAll(void)
{	
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		// �|���S���̕`�揈��
		for (int nCount = 0; nCount < MAX_POLYGON; nCount++)
		{
			if (m_apScene[nCountpriority][nCount] != NULL)
			{
				if (m_apScene[nCountpriority][nCount]->GetObjType() != OBJTYPE_FADE)
				{
					m_apScene[nCountpriority][nCount]->Draw();
				}
			}
		}
	}
}

//=============================================================================
//�����[�X����
//=============================================================================
void CScene::Release(void)
{
	//�������̉��
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}