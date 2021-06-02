//=============================================================================
//�n�C�X�R�A����[hiscore.cpp]
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "hiscore.h"
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CHiscore::m_pTexture = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CHiscore::CHiscore(int nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_nHiScore = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CHiscore::~CHiscore()
{

}

HRESULT CHiscore::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_HISCORE,								// �t�@�C���̖��O
		&m_pTexture);
	return S_OK;
}

void CHiscore::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//��������
//=============================================================================
CHiscore * CHiscore::Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	CHiscore *pHiScore;
	pHiScore = new CHiscore;
	pHiScore->Init(nPosX, nPosY, nPolygonWidth, nPolygonHeight);
	pHiScore->SetObjType(OBJTYPE_SCORE);
	return pHiScore;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CHiscore::Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	//�n�C�X�R�A�����\��
	m_pScene2D = new CScene2D;
	m_pScene2D->Init(HISCORE_WIDTH, nPosY, HISCORE_WIDTH, HISCORE_HEIGHT);
	m_pScene2D->BindTexture(m_pTexture);
	//�n�C�X�R�A���l�\��
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create(nPosX - ((nPolygonWidth * 2)*nCount), nPosY, nPolygonWidth, nPolygonHeight);
	}
	//�n�C�X�R�A�̓ǂݍ���
	FileLoad();
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CHiscore::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		//m_apNumber��NULL�Ȃ�R���e�B�j���[
		if (m_apNumber[nCount] == NULL)continue;
		m_apNumber[nCount]->Uninit();
		delete m_apNumber[nCount];
		m_apNumber[nCount] = NULL;
	}
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CHiscore::Update(void)
{
	SetHiScore();
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Update();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CHiscore::Draw(void)
{
	m_pScene2D->Draw();
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}

//=============================================================================
//�X�R�A�̐ݒ�
//=============================================================================
void CHiscore::SetHiScore()
{
	for (int nCount = 0; nCount < MAX_NUMBER; nCount++)
	{
		m_apNumber[nCount]->SetNumber(m_nHiScore % (int)pow(10, nCount + 1) / (int)pow(10, nCount));
	}
}

//=============================================================================
//�o�C�i���t�@�C���ǂݍ���
//=============================================================================
void CHiscore::FileLoad()
{
	//�t�@�C�����J��
	m_fp = fopen("data/hiscore.bin", "rb");
	//m_fp��NULL�Ȃ�return
	if (m_fp == NULL)return;
	//m_nHiScore�Ƀt�@�C�������擾
	fscanf(m_fp, "%d", &m_nHiScore);
	//�t�@�C�������
	fclose(m_fp);
}

//=============================================================================
//�o�C�i���t�@�C����������
//=============================================================================
void CHiscore::FileSave()
{
	//�t�@�C�����J��
	m_fp = fopen("data/hiscore.bin", "wb");
	//m_fp��NULL�Ȃ�return
	if (m_fp == NULL)return;
	//m_nHiScore�̒l���t�@�C���ɏ㏑��
	fprintf(m_fp, "%d", m_nHiScore);
	//�t�@�C�������
	fclose(m_fp);
}

//=============================================================================
//�n�C�X�R�A�Ƃ̔�r
//=============================================================================
void CHiscore::compareHiScore(int nScore)
{
	//�X�R�A���n�C�X�R�A���z���Ȃ����return
	if (m_nHiScore >= nScore)return;
	//�n�C�X�R�A���X�V
	m_nHiScore = nScore;
	//�o�C�i���t�@�C���㏑��
	FileSave();
}