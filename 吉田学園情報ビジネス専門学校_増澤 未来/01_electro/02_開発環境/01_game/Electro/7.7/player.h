//=============================================================================
//
// player�w�b�_ [player.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// �}�N����`
//*****************************
#define PLAYER_MAX_MP 50
#define PLAYER_MAX_HP 8

//*****************************
// �N���X��`
//*****************************

//�v���C���[�N���X
class CPlayer : public CScene3d
{
public:

	// ��ԗ�
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DAMAGE,
		STATE_SPAWN,
		STATE_GAMEOVER,
		STATE_MAX,
	}STATE;

	// �e�N�X�`���̔�������V��
	typedef enum
	{
		DIRECTION_DOWN = 0,   // ��
		DIRECTION_LEFT,		  // ��
		DIRECTION_RIGHT,	  // �E
		DIRECTION_UP,		  // ��
		DIRECTION_LEFT_DOWN,  // ����
		DIRECTION_LEFT_UP,	  // ����
		DIRECTION_RIGHT_DOWN, // �E��
		DIRECTION_RIGHT_UP,	  // �E��
		DIRECTION_MAX,
	}DIRECTION;

	//�����o�֐�
	CPlayer();
	~CPlayer();

	static CPlayer *Create(const D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	static bool IsAlive(void) { return m_bAlive;}

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetMove(void) { return m_move; }
	// �X�e�[�g�̎擾�E�Z�b�g
	STATE GetState(void) { return m_state;}
	void SetState(const STATE state) { m_state = state; }

	void HitAttack(int nDamage);
	void RecoveryLife(const int nRecovery);
	// �{���t���O�̃Z�b�g�E�擾
	void SetBomb(const bool bBomb) { m_bBomb = bBomb; }
	bool HaveBomb(void) { return m_bBomb; }
	// �c�@���̂̃Z�b�g�E�擾
	void SetRemain(const int nRemain) { m_nRemain = nRemain; }
	int GetRemain(void) { return m_nRemain; }
	//MP�̂̃Z�b�g�E�擾
	void SetMp(const float fMp) { m_fMp = fMp; }
	float GetMp(void) { return m_fMp; }
	void RecoveryMp(float fRecoveryMp);
	// HP�̃Z�b�g�E�擾�E��
	void SetLife(const int nLife) { m_nLife = nLife; }
	int GetLife(void) { return m_nLife; }

private:
	void StateManager(void);
	void ControlManager(void);
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;

	D3DXVECTOR3 m_move;   // �ړ���
	int m_nCntBullet;     // �e�̊Ԋu�m�ۗp
	int m_nStateCount;    // �X�e�[�g�J�ڗp
	STATE m_state;        // �X�e�[�g
	bool m_bBomb;         // �{���������Ă��邩
	static bool m_bAlive; // ��������
	int m_nRemain;        // �c�@
	float m_fMp;            // MP
	int m_nLife;          // �̗�
	float m_fRotAngle;      // ��]�p�x
	float m_fRotAngleDist;  // ��]�p�x�̖ڕW�l
};

#endif