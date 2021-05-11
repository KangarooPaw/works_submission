//=============================================================================
//�t�F���X����[fence.cpp]
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fence.h"
#include "enemy.h"
#include "scene2d.h"
#include "renderer.h"
#include "bullet.h"
#include "sound.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CFence::m_pTexture[2] = {};
int	 CFence::m_fanceCnt = 0;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CFence::CFence(int nPriority)
{
	m_Deathflag = false;
	m_type = 0;
	m_Life = 5;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CFence::~CFence()
{

}

//=============================================================================
//��������
//=============================================================================
CFence *CFence::Create(float nPosX, float nPosY,int type)
{
	CFence *pFence;
	pFence = new CFence;
	pFence->m_type = type;
	pFence->Init(nPosX, nPosY);
	pFence->BindTexture(m_pTexture[pFence->m_type]);
	return pFence;
}

//=============================================================================
//�e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CFence::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FENCE1,					// �t�@�C���̖��O
		&m_pTexture[0]);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FENCE2,					// �t�@�C���̖��O
		&m_pTexture[1]);
	return S_OK;
}

//=============================================================================
//�e�N�X�`���̔j��
//=============================================================================
void CFence::Unload(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//����������
//=============================================================================
HRESULT CFence::Init(float nPosX, float nPosY)
{
	//���E�̃t�F���X��z�u
	if (m_type == 0)
	{
		CScene2D::Init(nPosX, nPosY, FENCE_WIDTH, FENCE_HEIGHT);
	}
	//�㉺�̃t�F���X��z�u
	else if (m_type == 1)
	{
		CScene2D::Init(nPosX, nPosY, FENCE_HEIGHT, FENCE_WIDTH);
	}
	CScene2D::BindTexture(m_pTexture[m_type]);
	SetObjType(CScene::OBJTYPE_FENCE);
	//�t�F���X�̃J�E���g
	m_fanceCnt++;
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CFence::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CFence::Update(void)
{
	//�ʒu���擾
	D3DXVECTOR3 pos = GetPosition();
	//Sound���擾
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();

	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			//Scene2D�̎擾
			CScene2D *pScene2D = (CScene2D*)GetScene(nCountpriority, nCntScene);
			//pScene2D��NULL�Ȃ�R���e�B�j���[
			if (pScene2D == NULL)continue;
			//OBJTYPE���G�l�~�[�ȊO�Ȃ�R���e�B�j���[
			if (pScene2D->GetObjType() != CEnemy::OBJTYPE_ENEMY)continue;
			//�G�l�~�[�̈ʒu�擾
			D3DXVECTOR3 posEnemy = pScene2D->GetPosition();
			//���E�̃t�F���X
			if (m_type == 0)
			{
				//�����蔻��
				if (pos.x - 10 >= posEnemy.x - (ENEMY_WIDTH / 2) && pos.x + 10 <= posEnemy.x + (ENEMY_WIDTH / 2) &&
					pos.y + (FENCE_HEIGHT / 2) >= posEnemy.y - (ENEMY_HEIGHT / 2) && pos.y - (FENCE_HEIGHT / 2) <= posEnemy.y + (ENEMY_HEIGHT / 2))
				{
					//�G�l�~�[�̃q�b�g����
					((CEnemy*)pScene2D)->HitObject();
					//�t�F���X�̗̑͂��f�N�������g
					m_Life--;
					//0���̗͂�������΃R���e�B�j���[
					if (m_Life > 0)continue;
					//���݂���t�F���X�̌�
					m_fanceCnt--;
					//���S�t���O
					m_Deathflag = true;
				}
			}
			//�㉺�̃t�F���X
			else if (m_type == 1)
			{
				//�����蔻��
				if (pos.x + (FENCE_HEIGHT / 2) >= posEnemy.x - (ENEMY_WIDTH / 2) && pos.x - (FENCE_HEIGHT / 2) <= posEnemy.x + (ENEMY_WIDTH / 2) &&
					pos.y + (ENEMY_WIDTH / 2) >= posEnemy.y - (ENEMY_HEIGHT / 2) && pos.y - (ENEMY_WIDTH / 2) <= posEnemy.y + (ENEMY_HEIGHT / 2))
				{
					//�G�l�~�[�̃q�b�g����
					((CEnemy*)pScene2D)->HitObject();
					//�t�F���X�̗̑͂��f�N�������g
					m_Life--;
					//0���̗͂�������΃R���e�B�j���[
					if (m_Life > 0)continue;
					//���݂���t�F���X�̌�
					m_fanceCnt--;
					//���S�t���O
					m_Deathflag = true;
				}
			}
		}
	}
	if (m_fanceCnt <= 0)
	{
		//�t�F���X���Ȃ��Ȃ��BGM�ύX
		pSound->Stop(CSound::BGM_MAIN);
		pSound->Play(CSound::BGM_FENCEBREAK);
	}

	//���S�t���O��true�Ȃ�return
	if (m_Deathflag != true)return;
	//�j��SE�Đ�
	pSound->Play(CSound::SE_BREAK);
	//�I������
	Uninit();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CFence::Draw(void)
{
	CScene2D::Draw();
}