//===================================================
//
//    �Q�[�W�N���X�̏���[gage.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
// �C���N���[�h
//**********************************
#include "remain.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "number.h"
#include "game.h"
#include "player.h"

//**********************************
// �}�N����`
//**********************************
#define REMAIN_SIZE_X 30.0f
#define REMAIN_SIZE_Y 20.0f
#define REMAIN_SIZE D3DXVECTOR3(REMAIN_SIZE_X, REMAIN_SIZE_Y, 0.0f)
#define REMAIN_TEXTURE_PATH "./data/Textures/remain000.png" //�e�N�X�`��

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
LPDIRECT3DTEXTURE9 CRemain::m_pTexture = NULL;
//int CRemain::m_nRemain = MAX_GAGE;

//==================================
// �R���X�g���N�^
//==================================
CRemain::CRemain() :CScene(OBJTYPE_UI)
{
	// �ϐ��̃N���A
	//memset(m_apPolygon, 0, sizeof(m_apPolygon));
	m_pPolygon = NULL;
	m_pNumber = NULL;
	m_nRemain = 1;
}

//==================================
// �f�X�g���N�^
//==================================
CRemain::~CRemain()
{
}

//==================================
// �N���G�C�g
//==================================
CRemain * CRemain::Create(void)
{
	// �������̊m��
	CRemain *pRemain;
	pRemain = new CRemain;

	// ������
	pRemain->Init();
	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	pRemain->SetObjType(OBJTYPE_UI);

	return pRemain;
}

//==================================
// �e�N�X�`���̃��[�h
//==================================
HRESULT CRemain::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, REMAIN_TEXTURE_PATH, &m_pTexture);

	return S_OK;
}

//==================================
// �e�N�X�`���̃A�����[�h
//==================================
void CRemain::Unload(void)
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
HRESULT CRemain::Init(void)
{
	// �|���S������
	if (m_pPolygon == NULL)
	{
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(50, 100, 0.0f), REMAIN_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pPolygon->SetTexture(m_pTexture);
	}
	// �i���o�[����
	if (m_pNumber == NULL)
	{
		m_pNumber = CNumber::Create(m_nRemain, D3DXVECTOR3(50 + REMAIN_SIZE_X +10, 105, 0.0f), D3DXVECTOR3(15, 15, 0.0f), D3DXCOLOR(0.8f, 0.01f, 0.05f, 1.0f));
	}

	return S_OK;
}

//==================================
// �I������
//==================================
void CRemain::Uninit(void)
{
	// �|���S���̏I������
	if (m_pPolygon != NULL)
	{
		// �I������
		m_pPolygon->Uninit();
		// �������̉��
		delete m_pPolygon;
		m_pPolygon = NULL;
	}

	// �i���o�[�̏I������
	if (m_pNumber != NULL)
	{
		// �I������
		m_pNumber->Uninit();
		// �������̉��
		delete m_pNumber;
		m_pNumber = NULL;
	}

	// �J������
	Release();
}

//==================================
// �X�V����
//==================================
void CRemain::Update(void)
{
	//m_pNumber->SetNumber(CGame::GetPlayer()->GetRemain());
}

//==================================
// �`�揈��
//==================================
void CRemain::Draw(void)
{
	// ���݂̃��C�t���`��

	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
	if (m_pNumber != NULL)
	{
		m_pNumber->Draw();
	}

}