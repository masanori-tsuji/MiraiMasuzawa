//===================================================
//
//    �Q�[�W�N���X�̏���[gage.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
// �C���N���[�h
//**********************************
#include "gage.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "player.h"
#include "game.h"
#include "boss.h"

//**********************************
// �}�N����`
//**********************************
#define  GAGE_TEXTURE_PATH "./data/Textures/HPBar.png" //�e�N�X�`��

// �v���C���[(HP)
#define PLAYER_LIFE_WIDTH 300.0f // HP�o�[�̉����̍ő�
#define PLAYER_LIFE_HEGHT 15      // HP�o�[�̏c��
#define PLAYER_LIFE_POS_X 150.0f // X�ʒu
#define PLAYER_LIFE_POS_Y 618.0f // Y�ʒu
// �v���C���[(MP)
#define PLAYER_MP_WIDTH 300.0f // HP�o�[�̉����̍ő�
#define PLAYER_MP_HEGHT 12      // HP�o�[�̏c��
#define PLAYER_MP_POS_X 150.0f // X�ʒu
#define PLAYER_MP_POS_Y 645.0f // Y�ʒu

// �{�X
#define BOSS_HP_WIDTH 500.0f                               // HP�o�[�̉����̍ő�
#define BOSS_HP_HEGHT 10                                   // HP�o�[�̏c��
#define BOSS_HP_POS_X SCREEN_WIDTH/2 - (BOSS_HP_WIDTH/2) // X�ʒu
#define BOSS_HP_POS_Y 100.0f                               // Y�ʒu

#define REDBAR_RATE 0.02f // �Ԃ��o�[�����X�Ɍ����Ă����̌W��

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
LPDIRECT3DTEXTURE9 CGage::m_pTexture = NULL; // �e�N�X�`��

//==================================
// �R���X�g���N�^
//==================================
CGage::CGage() :CScene(OBJTYPE_UI)
{
	// �ϐ��̃N���A
	memset(m_apPolygon, 0, sizeof(m_apPolygon));
	m_fRedLife = 0;
	m_fBarWidht = 0.0f;
	m_fBarHeight = 0.0f;
	m_leftPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMaxNum = 0;
}

//==================================
// �f�X�g���N�^
//==================================
CGage::~CGage()
{
}

//==================================
// �N���G�C�g
//==================================
CGage * CGage::Create(GAGE_TYPE type)
{
	// �������̊m��
	CGage *pGage;
	pGage = new CGage;

	// ���[�U�[�̐ݒ�
	pGage->m_gageType = type;
	// ������
	pGage->Init();
	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	pGage->SetObjType(OBJTYPE_UI);
	

	return pGage;
}

//==================================
// �e�N�X�`���̃��[�h
//==================================
HRESULT CGage::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, GAGE_TEXTURE_PATH, &m_pTexture);

	return S_OK;
}

//==================================
// �e�N�X�`���̃A�����[�h
//==================================
void CGage::Unload(void)
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
HRESULT CGage::Init(void)
{
	// ���C�t�o�[�̒��_�̐ݒ�
	float fWidth = 0.0f;
	D3DXCOLOR frontCol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	switch (m_gageType)
	{
	case GAGE_PLAYER_HP:
		m_leftPos = D3DXVECTOR3(PLAYER_LIFE_POS_X, PLAYER_LIFE_POS_Y, 0.0f); // ���[
		m_fBarWidht = PLAYER_LIFE_WIDTH;                                     // HP�o�[�̕�
		m_fBarHeight = PLAYER_LIFE_HEGHT;                                    // HP�o�[�̍���
		m_nMaxNum = PLAYER_MAX_HP;                                        // �ő僉�C�t��
		fWidth = m_fBarWidht * CGame::GetPlayer()->GetLife() / m_nMaxNum;   // ���̌v�Z
		m_fRedLife = CGame::GetPlayer()->GetLife();                          // �ԃQ�[�W�̃��C�t��
		break;
	case GAGE_PLAYER_MP:
		m_leftPos = D3DXVECTOR3(PLAYER_MP_POS_X, PLAYER_MP_POS_Y, 0.0f); // ���[
		m_fBarWidht = PLAYER_MP_WIDTH;                                     // HP�o�[�̕�
		m_fBarHeight = PLAYER_MP_HEGHT;                                    // HP�o�[�̍���
		m_nMaxNum = PLAYER_MAX_MP;                                           // �ő�
		fWidth = m_fBarWidht * CGame::GetPlayer()->GetMp() / m_nMaxNum;      // ���̌v�Z
		m_fRedLife = 0;                                                      // �ԃQ�[�W�̗�

		frontCol = D3DXCOLOR(0.0f, 0.75f, 1.0f, 1.0f);
		break;
	case GAGE_BOSS_HP:
		m_leftPos = D3DXVECTOR3(BOSS_HP_POS_X, BOSS_HP_POS_Y, 0.0f);    // ���[
		m_fBarWidht = BOSS_HP_WIDTH;									    // HP�o�[�̕�
		m_fBarHeight = BOSS_HP_HEGHT;									    // HP�o�[�̍���
		m_nMaxNum = BOSS_MAX_LIFE;										    // �ő�
		fWidth = m_fBarWidht * CGame::GetBoss()->GetLife() / m_nMaxNum;     // ���̌v�Z
		m_fRedLife = CGame::GetBoss()->GetLife();						    // �ԃQ�[�W�̗�
		break;
	default:
		break;
	}

	// �v���C���[�̃Q�[�W
	for (int nCntGage = 0; nCntGage < BAR_PARTS_MAX; nCntGage++)
	{
		// �|���S���̐���
		m_apPolygon[nCntGage] = CPolygon::Create(
			m_leftPos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		
		// ���_���W�̐ݒ�
		D3DXVECTOR3 vtxPos[NUM_VERTEX];

		vtxPos[0] = D3DXVECTOR3(m_leftPos.x         , m_leftPos.y - m_fBarHeight, 0.0f);
		vtxPos[1] = D3DXVECTOR3(m_leftPos.x + fWidth, m_leftPos.y - m_fBarHeight, 0.0f);
		vtxPos[2] = D3DXVECTOR3(m_leftPos.x         , m_leftPos.y + m_fBarHeight, 0.0f);
		vtxPos[3] = D3DXVECTOR3(m_leftPos.x + fWidth, m_leftPos.y + m_fBarHeight, 0.0f);

		m_apPolygon[nCntGage]->SetVertexPos(vtxPos);
	}

	// �ԃQ�[�W�̐F
	m_apPolygon[BAR_RED]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	// �΃Q�[�W�̐F
	m_apPolygon[BAR_FRONT]->SetColor(frontCol);
	// �Q�[�W�̃t���[���̃e�N�X�`�����蓖��
	m_apPolygon[BAR_FRAME]->SetTexture(m_pTexture);

	return S_OK;
}

//==================================
// �I������
//==================================
void CGage::Uninit(void)
{
	// ���C�t�̍ő吔���|���S���̏I������
	for (int nCntGage = 0; nCntGage < BAR_PARTS_MAX; nCntGage++)
	{
		if (m_apPolygon[nCntGage] != NULL)
		{
			// �I������
			m_apPolygon[nCntGage]->Uninit();
			// �������̉��
			delete m_apPolygon[nCntGage];
			m_apPolygon[nCntGage] = NULL;
		}
	}

	// �J������
	Release();
}

//==================================
// �X�V����
//==================================
void CGage::Update(void)
{
	// ���C�t�o�[�̒��_�̐ݒ�

	// ���̌v�Z

	float fWidth = 0.0f;
	switch (m_gageType)
	{
	case GAGE_PLAYER_HP:
		if (CPlayer::IsAlive())
		{
			// �΃Q�[�W
			fWidth = m_fBarWidht * CGame::GetPlayer()->GetLife() / m_nMaxNum;
			// �ԃQ�[�W
			m_fRedLife += (CGame::GetPlayer()->GetLife() - m_fRedLife)*REDBAR_RATE;
		}
		else
		{
			m_fRedLife = 0.0f;
		}
		break;
	case GAGE_PLAYER_MP:
		if (CPlayer::IsAlive())
		{
			// �΃Q�[�W
			fWidth = m_fBarWidht * CGame::GetPlayer()->GetMp() / m_nMaxNum;
			// �ԃQ�[�W
			m_fRedLife = 0.0f;
		}

		break;

	case GAGE_BOSS_HP:
		if (CBoss::IsAlive())
		{
			// �΃Q�[�W
			fWidth = m_fBarWidht * CGame::GetBoss()->GetLife() / m_nMaxNum;
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
	
	m_apPolygon[BAR_FRONT]->SetVertexPos(vtxPos);

	// ���̌v�Z
	fWidth = m_fBarWidht * m_fRedLife / m_nMaxNum;

	// ���_���W�̐ݒ�
	vtxPos[0] = D3DXVECTOR3(m_leftPos.x         , m_leftPos.y - m_fBarHeight, 0.0f);
	vtxPos[1] = D3DXVECTOR3(m_leftPos.x + fWidth, m_leftPos.y - m_fBarHeight, 0.0f);
	vtxPos[2] = D3DXVECTOR3(m_leftPos.x         , m_leftPos.y + m_fBarHeight, 0.0f);
	vtxPos[3] = D3DXVECTOR3(m_leftPos.x + fWidth, m_leftPos.y + m_fBarHeight, 0.0f);

	m_apPolygon[BAR_RED]->SetVertexPos(vtxPos);

	// �|���S���̍ő吔���X�V����
	for (int nCntGage = 0; nCntGage < BAR_PARTS_MAX; nCntGage++)
	{
		if (m_apPolygon[nCntGage] != NULL)
		{
			m_apPolygon[nCntGage]->Update();
		}
	}
}

//==================================
// �`�揈��
//==================================
void CGage::Draw(void)
{
	// �O�p�[�c���`��
	for (int nCntGage = 0; nCntGage < BAR_PARTS_MAX; nCntGage++)
	{
		if (m_apPolygon[nCntGage] != NULL)
		{
			m_apPolygon[nCntGage]->Draw();
		}
	}
}
