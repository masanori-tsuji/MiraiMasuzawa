//=============================================================================
//
// game�w�b�_ [game.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _GAME_H_
#define _GAME_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// �O���錾
//=============================
class CRenderer;
class CInputKeyboard;
class CInputJoypad;
class CInputMouse;
class CSound;
class CPlayer;
class CCursor;
class CCamera;
class CStage;
class CBoss;

//*****************************
//�N���X��`
//*****************************

//�Q�[���N���X
class CGame : public CScene
{
public:
	typedef enum
	{
		WAVE_NORMAL = 0,
		WAVE_BOSS,
		WAVE_MAX,
	}GAME_WAVES;

	// �����o�֐�
	CGame();
	~CGame();
	static CGame *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetWave(GAME_WAVES wave);

	static CPlayer *GetPlayer(void) { return m_pPlayer; }                  // �v���C���[�̎擾����
	static CCursor *GetCursor(void) { return m_pCursor; }                  // �J�[�\���̎擾����
	static CCamera *GetCamera(void) { return m_pCamera; }                  // �J�����̎擾����
	static CStage *GetStage(void) { return m_pStage; }                     // �X�e�[�W
	static CBoss *GetBoss(void) { return m_pBoss; }                        // �{�X
	static GAME_WAVES GetWave(void) { return m_wave; }
private:
	// �����o�ϐ�
	static CPlayer*m_pPlayer;                // �v���C���[�|�C���^
	static CCursor*m_pCursor;                // �J�[�\���|�C���^
	static CCamera*m_pCamera;                // �J����
	static CStage*m_pStage;                  // �X�e�[�W
	static CBoss*m_pBoss;                    // �{�X
	static GAME_WAVES m_wave;                // WAVE���Ǘ��p
};

#endif