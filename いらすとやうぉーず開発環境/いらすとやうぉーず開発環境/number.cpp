//=============================================================================
//�����`�揈��[number.cpp]
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "scene.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//-------------------------------------------
//�R���X�g���N�^
//-------------------------------------------
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_nNumber = 0;
}

//-------------------------------------------
//�f�X�g���N�^
//-------------------------------------------
CNumber::~CNumber()
{

}

//-------------------------------------------
//�e�N�X�`���ǂݍ���
//-------------------------------------------
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NUMBER,							// �t�@�C���̖��O
		&m_pTexture);
	return S_OK;
}

//-------------------------------------------
//�e�N�X�`���̔j��
//-------------------------------------------
void CNumber::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-------------------------------------------
//�N���G�C�g
//-------------------------------------------
CNumber * CNumber::Create(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	CNumber *pNumber;
	pNumber = new CNumber;
	pNumber->Init(nPosX,nPosY, nPolygonWidth, nPolygonHeight);
	((CScene*)pNumber)->SetObjType(CScene::OBJTYPE_NUMBER);
	return pNumber;
}

//-------------------------------------------
//����������
//-------------------------------------------
HRESULT CNumber::Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_NUMBER,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = nPosX- nPolygonWidth;
	pVtx[0].pos.y = nPosY- nPolygonHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = nPosX+ nPolygonWidth;
	pVtx[1].pos.y = nPosY- nPolygonHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = nPosX - nPolygonWidth;
	pVtx[2].pos.y = nPosY + nPolygonHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = nPosX + nPolygonWidth;
	pVtx[3].pos.y = nPosY + nPolygonHeight;
	pVtx[3].pos.z = 0.0f;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//-------------------------------------------
//�I������
//-------------------------------------------
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void CNumber::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.1f * m_nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * m_nNumber, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * m_nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * m_nNumber, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//-------------------------------------------
//�Z�b�g�i���o�[
//-------------------------------------------
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;
}
