//=======================================================================================
//
//�^�C�g�����j���[���� [titlemenu.cpp]
// Author : Masuzawa Mirai
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "pause.h"
#include "polygon.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "tcp_client.h"
#include "fade.h"
#include "joypad.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define BACK_SIZE D3DXVECTOR3(200.0f,180.0f,0.0f)                  // �w�ʃT�C�Y
#define BACK_POS D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f)  // �w�ʍ��W

#define STRING_SIZE D3DXVECTOR3(150.0f,50.0f,0.0f)                                           // �����e�N�X�`���̃T�C�Y
#define RESUME_POS  D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y - (STRING_SIZE.y + 25),0.0f) // ������̍��W
#define RESTART_POS D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y,0.0f)                        // ���X�^�[�g�̍��W
#define EXIT_POS   	D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y + (STRING_SIZE.y + 25),0.0f) // �I���̍��W

#define MENU_ENTER_COL D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f)     // �I��ł郁�j���[�̐F
#define MENU_NOT_ENTER_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) // �I��łȂ����j���[�̐F

//=======================================================================================
// �O���錾
//=======================================================================================
LPDIRECT3DTEXTURE9 CPause::m_apTexture[CPause::PARTS_MAX] = {}; //�e�N�X�`��

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CPause::CPause()
{
	// �ϐ��̃N���A
	memset(&m_pPolygon, 0, sizeof(m_pPolygon));
	m_nMenu = RESUME;
	m_bMove = true;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CPause::~CPause()
{

}

//=======================================================================================
// �N���G�C�g
//=======================================================================================
CPause* CPause::Create(void)
{
	// �������̊m��
	CPause* pPause = new CPause();
	// ����������
	pPause->Init();

	return pPause;
}

//=======================================================================================
// �e�N�X�`���̃��[�h
//=======================================================================================
HRESULT CPause::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_back.png"   , &m_apTexture[BACK]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_resume.png" , &m_apTexture[RESUME]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_restart.png", &m_apTexture[RESTART]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_exit.png" , &m_apTexture[EXIT]);

	return S_OK;
}
//=======================================================================================
// �e�N�X�`���̃A�����[�h
//=======================================================================================
void CPause::UnLoad(void)
{

	for (int nCntTex = 0; nCntTex < PARTS_MAX; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
//=======================================================================================
// ����������
//=======================================================================================
HRESULT CPause::Init(void)
{
	// �|���S������

	// ���̂��
	m_pPolygon[BACK] = CPolygon::Create(BACK_POS, BACK_SIZE);
	m_pPolygon[BACK]->SetTexture(m_apTexture[BACK]);
	// �ĊJ�̂��
	m_pPolygon[RESUME] = CPolygon::Create(RESUME_POS, STRING_SIZE);
	m_pPolygon[RESUME]->SetTexture(m_apTexture[RESUME]);
	// ���X�^�[�g�̂��
	m_pPolygon[RESTART] = CPolygon::Create(RESTART_POS, STRING_SIZE);
	m_pPolygon[RESTART]->SetTexture(m_apTexture[RESTART]);
	// EXIT�̂��
	m_pPolygon[EXIT] = CPolygon::Create(EXIT_POS, STRING_SIZE);
	m_pPolygon[EXIT]->SetTexture(m_apTexture[EXIT]);
	

	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CPause::Uninit(void)
{
	for (int nCntTex = 0; nCntTex < PARTS_MAX; nCntTex++)
	{
		if (m_pPolygon[nCntTex] != NULL)
		{
			//�I������
			m_pPolygon[nCntTex]->Uninit();
			// �������̉��
			delete m_pPolygon[nCntTex];
			m_pPolygon[nCntTex] = NULL;
		}
	}
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CPause::Update(void)
{
	// �I��ł郁�j���[�ŐF����
	for (int nCntMenu = RESUME; nCntMenu < PARTS_MAX; nCntMenu++)
	{
		if (m_nMenu == nCntMenu)
		{// �I��ł�Ƃ�
			m_pPolygon[nCntMenu]->SetColor(MENU_ENTER_COL);
		}
		else
		{// �I��łȂ��Ƃ�
			m_pPolygon[nCntMenu]->SetColor(MENU_NOT_ENTER_COL);
		}
	}
	DIJOYSTATE jy = CManager::GetJoypad()->GetStick(0);
	// ���j���[����
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_W) || CManager::GetKeyboard()->GetKeyTrigger(DIK_UP) || m_bMove && jy.lY <= -600)
	{// ��
		m_nMenu--;
		m_bMove = false;
	}
	else if (CManager::GetKeyboard()->GetKeyTrigger(DIK_S) || CManager::GetKeyboard()->GetKeyTrigger(DIK_DOWN) || m_bMove && jy.lY >= 600)
	{// ��
		m_nMenu++;
		m_bMove = false;
	}

	// �X�e�B�b�N�p�t���O�̏�����
	if (jy.lY <= 500 && jy.lY >= -500)
	{
		m_bMove = true;
	}

	// �͈͊O�ɍs���Ȃ��悤��
	if (m_nMenu > EXIT)
	{
		m_nMenu = RESUME;
	}
	else if (m_nMenu < RESUME)
	{
		m_nMenu = EXIT;
	}

	// ���j���[�R�}���h
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetJoypad()->GetJoystickTrigger(3, 0))
	{
		switch (m_nMenu)
		{
		case RESUME:
			// ������
			CManager::SetActivePause(false);
			break;
		case RESTART:
			// ���X�^�[�g
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
			break;
		case EXIT:
			// EXIT
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
			break;
		default:
			break;
		}
	}
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CPause::Draw(void)
{
	// ���ׂẴp�[�c���`��
	for (int nCntPolygon = 0; nCntPolygon < PARTS_MAX; nCntPolygon++)
	{
		if (m_pPolygon[nCntPolygon] != NULL)
		{
			m_pPolygon[nCntPolygon]->Draw();
		}
	}
}