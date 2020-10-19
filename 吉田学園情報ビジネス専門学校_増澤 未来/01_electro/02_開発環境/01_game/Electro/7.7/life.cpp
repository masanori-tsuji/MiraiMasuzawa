//===================================================
//
//    ���C�t�N���X�̏���[life.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
// �C���N���[�h
//**********************************
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "player.h"
#include "game.h"
#include "boss.h"

//**********************************
// �}�N����`
//**********************************
#define  LIFE_TEXTURE_PATH "./data/Textures/HPBar.png" //�e�N�X�`��

// �v���C���[
#define PLAYER_LIFE_WIDTH 250.0f // HP�o�[�̉����̍ő�
#define PLAYER_LIFE_HEGHT 15     // HP�o�[�̏c��
#define PLAYER_LIFE_POS_X 150.0f // X�ʒu
#define PLAYER_LIFE_POS_Y 650.0f // Y�ʒu

// �{�X
#define BOSS_LIFE_WIDTH 500.0f                               // HP�o�[�̉����̍ő�
#define BOSS_LIFE_HEGHT 10                                   // HP�o�[�̏c��
#define BOSS_LIFE_POS_X SCREEN_WIDTH/2 - (BOSS_LIFE_WIDTH/2) // X�ʒu
#define BOSS_LIFE_POS_Y 100.0f                               // Y�ʒu

#define REDBAR_RATE 0.02f // �Ԃ��o�[�����X�Ɍ����Ă����̌W��

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;
//int CLife::m_nLife = MAX_LIFE;

//==================================
// �R���X�g���N�^
//==================================
CLife::CLife()
{
	// �ϐ��̃N���A
	memset(m_apPolygon, 0, sizeof(m_apPolygon));
	m_fRedLife = 0;
	m_fBarWidht = 0.0f;
	m_fBarHeight = 0.0f;
	m_leftPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMaxLife = 0;
}

//==================================
// �f�X�g���N�^
//==================================
CLife::~CLife()
{
}

//==================================
// �N���G�C�g
//==================================
CLife * CLife::Create(LIFE_USER user)
{
	// �������̊m��
	CLife *pLife;
	pLife = new CLife;

	// ���[�U�[�̐ݒ�
	pLife->m_user = user;
	// ������
	pLife->Init();
	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	pLife->SetObjType(OBJTYPE_UI);
	

	return pLife;
}

//==================================
// �e�N�X�`���̃��[�h
//==================================
HRESULT CLife::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, LIFE_TEXTURE_PATH, &m_pTexture);

	return S_OK;
}

//==================================
// �e�N�X�`���̃A�����[�h
//==================================
void CLife::Unload(void)
{
	// �e�N�X�`���̉��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==================================
// ����������
//==================================
HRESULT CLife::Init(void)
{
	// ���C�t�o�[�̒��_�̐ݒ�
	float fWidth = 0.0f; 
	switch (m_user)
	{
	case USER_PLAYER:
		m_leftPos = D3DXVECTOR3(PLAYER_LIFE_POS_X, PLAYER_LIFE_POS_Y, 0.0f); // ���[
		m_fBarWidht = PLAYER_LIFE_WIDTH;                                     // HP�o�[�̕�
		m_fBarHeight = PLAYER_LIFE_HEGHT;                                    // HP�o�[�̍���
		m_nMaxLife = PLAYER_MAX_LIFE;                                        // �ő僉�C�t��
		fWidth = m_fBarWidht * CGame::GetPlayer()->GetLife() / m_nMaxLife;   // ���̌v�Z
		m_fRedLife = CGame::GetPlayer()->GetLife();                          // �ԃQ�[�W�̃��C�t��
		break;
	case USER_BOSS:
		m_leftPos = D3DXVECTOR3(BOSS_LIFE_POS_X, BOSS_LIFE_POS_Y, 0.0f);    // ���[
		m_fBarWidht = BOSS_LIFE_WIDTH;									    // HP�o�[�̕�
		m_fBarHeight = BOSS_LIFE_HEGHT;									    // HP�o�[�̍���
		m_nMaxLife = BOSS_MAX_LIFE;										    // �ő僉�C�t��
		fWidth = m_fBarWidht * CGame::GetBoss()->GetLife() / m_nMaxLife;    // ���̌v�Z
		m_fRedLife = CGame::GetBoss()->GetLife();						    // �ԃQ�[�W�̃��C�t��
		break;
	default:
		break;
	}

	// �v���C���[�̃Q�[�W
	for (int nCntLife = 0; nCntLife < BAR_PARTS_MAX; nCntLife++)
	{
		// �|���S���̐���
		m_apPolygon[nCntLife] = CPolygon::Create(
			m_leftPos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		
		
		D3DXVECTOR3 vtxPos[NUM_VERTEX];

		vtxPos[0] = D3DXVECTOR3(m_leftPos.x         , m_leftPos.y - m_fBarHeight, 0.0f);
		vtxPos[1] = D3DXVECTOR3(m_leftPos.x + fWidth, m_leftPos.y - m_fBarHeight, 0.0f);
		vtxPos[2] = D3DXVECTOR3(m_leftPos.x         , m_leftPos.y + m_fBarHeight, 0.0f);
		vtxPos[3] = D3DXVECTOR3(m_leftPos.x + fWidth, m_leftPos.y + m_fBarHeight, 0.0f);

		m_apPolygon[nCntLife]->SetVertexPos(vtxPos);
		//m_apPolygon[nCntLife]->SetTexture(m_pTexture);
	}

	
	m_apPolygon[BAR_RED]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_apPolygon[BAR_GREEN]->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	m_apPolygon[BAR_FRAME]->SetTexture(m_pTexture);


	return S_OK;
}

//==================================
// �I������
//==================================
void CLife::Uninit(void)
{
	// ���C�t�̍ő吔���|���S���̏I������
	for (int nCntLife = 0; nCntLife < BAR_PARTS_MAX; nCntLife++)
	{
		if (m_apPolygon[nCntLife] != NULL)
		{
			// �I������
			m_apPolygon[nCntLife]->Uninit();
			// �������̉��
			delete m_apPolygon[nCntLife];
			m_apPolygon[nCntLife] = NULL;
		}
	}

	// �J������
	Release();
}

//==================================
// �X�V����
//==================================
void CLife::Update(void)
{
	int nPlayerLife = CGame::GetPlayer()->GetLife();

	// ���C�t�o�[�̒��_�̐ݒ�

	// ���̌v�Z
	float fWidth = 0.0f;
	switch (m_user)
	{
	case USER_PLAYER:
		if (CPlayer::IsAlive())
		{
			// �΃Q�[�W
			fWidth = m_fBarWidht * CGame::GetPlayer()->GetLife() / m_nMaxLife;
			// �ԃQ�[�W
			m_fRedLife += (CGame::GetPlayer()->GetLife() - m_fRedLife)*REDBAR_RATE;
		}
		else
		{
			m_fRedLife = 0.0f;
		}
		break;

	case USER_BOSS:
		if (CBoss::IsAlive())
		{
			// �΃Q�[�W
			fWidth = m_fBarWidht * CGame::GetBoss()->GetLife() / m_nMaxLife;
			// �ԃQ�[�W
			m_fRedLife += (CGame::GetBoss()->GetLife() - m_fRedLife)*REDBAR_RATE;
		}
		else
		{
			m_fRedLife = 0.0f;
		}
		break;

	default:
		break;
	}
	

	// ���_���W�̐ݒ�
	D3DXVECTOR3 vtxPos[NUM_VERTEX];

	vtxPos[0] = D3DXVECTOR3(m_leftPos.x         , m_leftPos.y - m_fBarHeight, 0.0f);
	vtxPos[1] = D3DXVECTOR3(m_leftPos.x + fWidth, m_leftPos.y - m_fBarHeight, 0.0f);
	vtxPos[2] = D3DXVECTOR3(m_leftPos.x         , m_leftPos.y + m_fBarHeight, 0.0f);
	vtxPos[3] = D3DXVECTOR3(m_leftPos.x + fWidth, m_leftPos.y + m_fBarHeight, 0.0f);
	
	m_apPolygon[BAR_GREEN]->SetVertexPos(vtxPos);

	

	// ���̌v�Z
	fWidth = m_fBarWidht * m_fRedLife / m_nMaxLife;

	// ���_���W�̐ݒ�
	vtxPos[0] = D3DXVECTOR3(m_leftPos.x         , m_leftPos.y - m_fBarHeight, 0.0f);
	vtxPos[1] = D3DXVECTOR3(m_leftPos.x + fWidth, m_leftPos.y - m_fBarHeight, 0.0f);
	vtxPos[2] = D3DXVECTOR3(m_leftPos.x         , m_leftPos.y + m_fBarHeight, 0.0f);
	vtxPos[3] = D3DXVECTOR3(m_leftPos.x + fWidth, m_leftPos.y + m_fBarHeight, 0.0f);

	m_apPolygon[BAR_RED]->SetVertexPos(vtxPos);

	// �|���S���̍ő吔���X�V����
	for (int nCntLife = 0; nCntLife < BAR_PARTS_MAX; nCntLife++)
	{
		if (m_apPolygon[nCntLife] != NULL)
		{
			m_apPolygon[nCntLife]->Update();
		}
	}


}

//==================================
// �`�揈��
//==================================
void CLife::Draw(void)
{
	// ���݂̃��C�t���`��
	for (int nCntLife = 0; nCntLife < BAR_PARTS_MAX; nCntLife++)
	{
		if (m_apPolygon[nCntLife] != NULL)
		{
			m_apPolygon[nCntLife]->Draw();
		}
	}
}
