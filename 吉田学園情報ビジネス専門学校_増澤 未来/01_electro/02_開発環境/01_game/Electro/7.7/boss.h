//=============================================================================
//
// boss�w�b�_ [boss.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _BOSS_H_
#define _BOSS_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
//�}�N����`
//*****************************
#define BOSS_MAX_LIFE 100  // �{�X�̗̑�
#define BOSS_SPAWN_SEC 60  //�{�X���킭�b��

//*****************************
// �N���X��`
//*****************************

//�{�X�N���X
class CBoss : public CScene3d
{
public:

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX,
	}STATE;

	//�����o�֐�
	CBoss();
	~CBoss();

	static CBoss *Create(const D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	static bool IsAlive(void) { return m_bIsAlive; }

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetLife(void) { return m_nLife; }
	void HitAttack(int nDamage);

private:
	void AttackManager(void);

	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���̃|�C���^
	static bool m_bIsAlive;               // ��������

	int m_nRandAttack;     // �U���p�^�[���̃����_��
	int m_nLife;          // ���C�t
	float m_fBulletAngle; // �e�����p�x
	int m_nCntBullet;     // �e�̊Ԋu�m�ۗp
	STATE m_state;        // �X�e�[�g
	int m_nStateCount;    // �X�e�[�g�J�ڗp
	int m_nCntAnim;       // �A�j���[�V�����J�E���g
	int m_nAnimX;         // �A�j���[�V����X��
	int m_nAnimY;         // �A�j���[�V����Y��
	bool m_bAttack;       // �U�����Ȃ��^�C�~���O�����p
};

#endif