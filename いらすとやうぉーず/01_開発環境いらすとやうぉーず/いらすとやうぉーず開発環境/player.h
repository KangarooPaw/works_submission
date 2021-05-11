//--------------------------
//�v���C���[����[player.h]
//--------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "scene2d.h"

//--------------------------
//�O���錾
//--------------------------
class CManager;

//--------------------------
//�N���X
//--------------------------
class CPlayer :public CScene2D
{
public:
	CPlayer(int nPriority = 9);//�R���X�g���N�^
	~CPlayer();//�f�X�g���N�^

	static HRESULT Load(void);//�e�N�X�`���̓ǂݍ���
	static void Unload(void);//�e�N�X�`���̔j��
		
	static CPlayer*Create(float nPosX, float nPosY);//��������
	
	HRESULT Init(float nPosX, float nPosY);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`���̃|�C���^
	float	m_move;//�ړ����x
	int		m_bulletTime;//�ˌ����x
};
#endif // !_PLAYER_H_
