//=============================================================================
//�X�R�A����[score.cpp]
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "score.h"
#include "number.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nScore = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
//��������
//=============================================================================
CScore * CScore::Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	CScore *pScore;
	pScore = new CScore;
	pScore->Init(nPosX, nPosY, nPolygonWidth, nPolygonHeight);
	pScore->SetObjType(OBJTYPE_SCORE);
	return pScore;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CScore::Init(float nPosX, float nPosY,int nPolygonWidth, int nPolygonHeight)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create(nPosX-((nPolygonWidth *2)*nCount),nPosY, nPolygonWidth, nPolygonHeight);
	}
	m_nScore = 0;
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Uninit();
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CScore::Update(void)
{
	SetScore(m_nScore);
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Update();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//=============================================================================
//�X�R�A�̐ݒ�
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
	m_apNumber[nCount]->SetNumber(m_nScore % (int)pow(10, nCount + 1) / (int)pow(10, nCount));
	}
}

//=============================================================================
//�X�R�A�����Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->SetNumber(m_nScore % (int)pow(10, nCount + 1) / (int)pow(10, nCount));
	}
}

//=============================================================================
//�X�R�A�̎擾
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//=============================================================================
//�X�R�A��ۑ�
//=============================================================================
int CScore::SaveScore(void)
{
	return m_nScore;
}
