////////////////////////////////////////////////////
//
//    �Q�[���N���X�̏���[game.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "number.h"
#include "score.h" 
#include "gage.h"
#include "effect.h"
#include "mouse.h"
#include "cursor.h"
#include "stage.h"
#include "camera.h"
#include "minimap.h"
#include "boss.h"
#include "fade.h"
#include "item.h"
#include "bomb.h"
#include "bomb_ui.h"
#include "manacircle.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"

//=============================
// �ÓI�����o�ϐ��錾
//=============================
CPlayer *CGame::m_pPlayer = NULL;   // �v���C���[
CCursor *CGame::m_pCursor = NULL;   // �J�[�\��
CCamera *CGame::m_pCamera = NULL;   // �J����
CStage  *CGame::m_pStage  = NULL;   // �X�e�[�W
CBoss   *CGame::m_pBoss   = NULL;   // �{�X
CGame::GAME_WAVES CGame::m_wave = CGame::WAVE_NORMAL; // Wave��

//=============================
// �R���X�g���N�^
//=============================
CGame::CGame()
{
}

//=============================
// �f�X�g���N�^
//=============================
CGame::~CGame()
{
}

//=============================
// �N���G�C�g
//=============================
CGame * CGame::Create(void)
{
	// �������̊m��
	CGame *pGame = new CGame;
	// ������
	pGame->Init();
	return pGame;
}

//=============================
// ����������
//=============================
HRESULT CGame::Init(void)
{
	// �^�C���N���X�̐���
	CTime::Create();
	// �w�i����
	CBg::Create();
	// �X�e�[�W�̐���
	m_pStage = CStage::Create();
	
	// �v���C���[����
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0, -400.0f, 0.0f));
	//// �J�[�\������
	m_pCursor = CCursor::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));

	// Wave�̏�����
	m_wave = WAVE_NORMAL;
	SetWave(m_wave);

	// �J�����̐���
	m_pCamera = CCamera::Create();

	// �X�R�A����
	CScore::Create();
	// �Q�[�W����
	CGage::Create(CGage::GAGE_PLAYER_HP);
	CGage::Create(CGage::GAGE_PLAYER_MP);
	// �~�j�}�b�v�̐���
	CMiniMap::Create();
	// �{��UI�̐���
	CBombUi::Create();

	// �T�[�N���̐��̏�����
	CManaCircle::SetCircleNum(0);

	// �|�[�Y�̏�����
	CManager::SetActivePause(false);
	return S_OK;
}

//=============================
// �I������
//=============================
void CGame::Uninit(void)
{
	// �J������
	CCamera::Release();

	// �J������
	Release();
}


//=============================
// �X�V����
//=============================
void CGame::Update(void)
{
	// �T�[�N�����̊Ǘ�
	CManaCircle::SpawnManager();

	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	
	if (m_wave == WAVE_NORMAL)
	{
		CEnemy::SpawnManager();
	}

#ifdef _DEBUG
	// �f�o�b�N�R�}���h
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F1))
	{
		SetWave(WAVE_BOSS);
	}

#endif // _DEBUG

}


//=============================
// �`�揈��
//=============================
void CGame::Draw(void)
{
	CGame::GetCamera()->SetCamera();
}

//=============================
// WAVE�Z�b�g
//=============================
void CGame::SetWave(GAME_WAVES wave)
{
	m_wave = wave;

	if (m_wave == WAVE_BOSS)
	{
		// �{�X�̐���
		m_pBoss = CBoss::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		CGage::Create(CGage::GAGE_BOSS_HP);
	}
}
