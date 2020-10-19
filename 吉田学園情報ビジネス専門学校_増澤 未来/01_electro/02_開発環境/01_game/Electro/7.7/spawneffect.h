//=============================================================================
//
// enemy�w�b�_ [enemy.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ENEMYSPAWN_H_
#define _ENEMYSPAWN_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"
#include "enemy.h"

//*****************************
// �O���錾
//*****************************
class CParticle;

//*****************************
// �}�N����`
//*****************************
#define ENEMYSPAWN_PARTICLE_NUM 6

//*****************************
// �N���X��`
//*****************************

// �G�l�~�[�X�|�[�����o�̃N���X
class CEnemySpawn : public CScene
{
public:

	//�����o�֐�
	CEnemySpawn();
	~CEnemySpawn();

	static CEnemySpawn *Create(const D3DXVECTOR3 pos, const CEnemy::ENEMYTYPE type);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_pos;                              // ���W
	CParticle*m_pParticle[ENEMYSPAWN_PARTICLE_NUM]; // �p�[�e�B�N���̃|�C���^
	CEnemy::ENEMYTYPE m_enemyType;                  // �G�l�~�[�^�C�v
	int m_nCntFrame;                                // �t���[���J�E���g�p
	D3DXCOLOR m_col;                                // �F
};

#endif