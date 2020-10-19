//=============================================================================
//
// enemy�w�b�_ [enemy.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// �N���X��`
//*****************************


// �G�l�~�[�N���X
class CEnemy : public CScene3d
{
public:
	// �G�l�~�[�̎��
	typedef enum
	{
		ENEMYTYPE_YELLOW = 0,
		ENEMYTYPE_PURPLE,
		ENEMYTYPE_RED,
		ENEMYTYPE_MAX,
	}ENEMYTYPE;

	// �X�e�[�g
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DAMAGE,
		STATE_MAX,
	}STATE;

	//�����o�֐�
	CEnemy();
	~CEnemy();

	static CEnemy *Create(const D3DXVECTOR3 pos,const ENEMYTYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	static void SpawnManager(void);
	static int GetEnemyNum(void) { return m_nNumEnemy; }                   // �G�l�~�[���̎擾����
	static void PlusEnemy(void) { m_nNumEnemy++; }                         // �G�l�~�[���𑝂₷
	static void MinusEnemy(void) { m_nNumEnemy--; }                        // �G�l�~�[���𑝂₷

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetMove(void) { return m_move; }
	static std::list<CEnemy*>*GetEnemylist(void) { return &m_enemyList; }

	void HitAttack(int nDamage);
private:
	void MoveManager(void);
	void ParticleCreate(void);

	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture[ENEMYTYPE_MAX]; // �e�N�X�`���̃|�C���^
	static std::list<CEnemy*> m_enemyList;  // �G�l�~�[���X�g
	static int m_nCntSpawn;      // �X�|�[���J�E���g
	static int m_nNumEnemy;                  // �G�l�~�[�ƃ{�X�̐��Ǘ��p

	D3DXVECTOR3 m_move;   // �ړ���
	ENEMYTYPE m_type;     // �G�̎��
	STATE m_state;        // �X�e�[�g
	int m_nCntMove;       // �ړ��J�E���g
	int m_nCntBullet;     // �e�̊Ԋu�m�ۗp
	int m_nLife;          // ���C�t
	int m_nStateCount;    // �X�e�[�g�J�ڗp
	int m_nCntEncount;    // �G���J�E���g��ԉ������̃J�E���g�p
	float m_fMoveAngle;   // �ړ��p�x
	bool m_bPlusAngle;    // �W�O�U�O�����G�l�~�[�̊p�x���v���X���邩�}�C�i�X���邩
	
	
};

#endif