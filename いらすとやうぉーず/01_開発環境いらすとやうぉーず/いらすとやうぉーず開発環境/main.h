//--------------------------
//���C������[main.h]
//--------------------------
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION 0x0800

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "windows.h"
#include "d3dx9.h"
#include <dinput.h>
#include <time.h>
#include <stdio.h>

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"���炷�Ƃ₤���[��"	// �E�C���h�E�̃L���v�V������

#define SCREEN_WIDTH	(1280)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W

#define PRIORITY		(10)
#define NUM_VERTEX		(4)
#define NUM_POLYGON		(2)

#define MAX_POLYGON		(2048)
#define MAX_NUMBER		(4)
#define ENEMY_CONCURRENT (5)	//�G�̓�������

#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//�|���S���T�C�Y
#define PLAYER_WIDTH	 (50)			//player
#define PLAYER_HEIGHT	 (50)
#define FENCE_WIDTH		 (60)			//fence
#define FENCE_HEIGHT	 (200)
#define ENEMY_WIDTH		 (50)			//enemy
#define ENEMY_HEIGHT	 (50)
#define BG_WIDTH		 (SCREEN_WIDTH)	//bg
#define BG_HEIGHT		 (SCREEN_HEIGHT)
#define TRANSITION_WIDTH (1000)			//transition
#define TRANSITION_HEIGHT (100)
#define SCORE_WIDTH		 (25)			//score
#define SCORE_HEIGHT	 (25)
#define NUMBER_WIDTH	 (25)			//number
#define NUMBER_HEIGHT	 (25)
#define EXPLOSION_WIDTH	 (25)			//explosion
#define EXPLOSION_HEIGHT (25)
#define	BULLET_WIDTH	 (25)			//bullet
#define BULLET_HEIGHT	 (25)
#define BOMB_WIDTH		 (150)			//bomb
#define BOMB_HEIGHT		 (150)
#define RETICULE_WIDTH	 (100)			//reticule
#define RETICULE_HEIGHT	 (100)

//�e�N�X�`��
#define TEXTURE_PLAYER			"data/TEXTURE/player.png"
#define TEXTURE_ENEMY			"data/TEXTURE/enemy.png"
#define TEXTURE_BULLET			"data/TEXTURE/bullet.png"
#define TEXTURE_EXPLOSION		"data/TEXTURE/explosion.png"
#define TEXTURE_FENCE1			"data/TEXTURE/fence1.png"
#define TEXTURE_FENCE2			"data/TEXTURE/fence2.png"
#define TEXTURE_BG				"data/TEXTURE/bg.png"
#define TEXTURE_TITLE			"data/TEXTURE/title.png"
#define TEXTURE_OPERATION		"data/TEXTURE/operation.png"
#define TEXTURE_RESULT			"data/TEXTURE/result.png"
#define TEXTURE_TRANSITON		"data/TEXTURE/transition.png"
#define TEXTURE_FADE			"data/TEXTURE/fade.png"
#define TEXTURE_NUMBER			"data/TEXTURE/number.png"
#define TEXTURE_BOMB			"data/TEXTURE/bomb.png"
#define TEXTURE_RETICULE		"data/TEXTURE/reticule.png"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

#endif