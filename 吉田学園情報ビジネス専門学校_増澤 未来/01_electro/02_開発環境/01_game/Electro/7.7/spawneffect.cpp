//===================================================
//
//    �G�l�~�[�N���X�̏���[enemy.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
//�C���N���[�h
//**********************************
#include "spawneffect.h"
#include "particle.h"

//**********************************
//�}�N����`
//**********************************
#define PARTICLE_SIZE D3DXVECTOR3(50.0f,50.0f,0.0f) // �p�[�e�B�N���T�C�Y
#define PARTICLE_COL D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) // �p�[�e�B�N�������J���[
#define PARTICLE_DISTANCE 80                        // �p�[�e�B�N���̏o������
#define PARTICLE_SPEED 4                            // �p�[�e�B�N���̈ړ��X�s�[�h
#define PARTICLE_LIFE 20                            // �p�[�e�B�N���̗L���t���[��
#define PARTICLE_RATE (1.0f/(float)PARTICLE_LIFE)      // �W��

#define COLOR_YELLOW D3DXCOLOR(1.0f,1.0f,0.0f,1.0f)	// ���F
#define COLOR_PURPLE D3DXCOLOR(1.0f,0.0f,1.0f,1.0f) // ��
#define COLOR_RED D3DXCOLOR(1.0f,0.0f,0.0f,1.0f)    // ��

//==================================
// �R���X�g���N�^
//==================================
CEnemySpawn::CEnemySpawn() :CScene(OBJTYPE_PARTICLE)
{
	// �����o�ϐ��̃N���A
	memset(&m_pParticle, 0, sizeof(m_pParticle));
	m_enemyType = CEnemy::ENEMYTYPE_YELLOW;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntFrame = 0;
}

//==================================
// �f�X�g���N�^
//==================================
CEnemySpawn::~CEnemySpawn()
{
}

//==================================
// �N���G�C�g
//==================================
CEnemySpawn * CEnemySpawn::Create(const D3DXVECTOR3 pos, const CEnemy::ENEMYTYPE type)
{
	// �������̊m��
	CEnemySpawn *pEnemySpawn = new CEnemySpawn;

	// ���W�̐ݒ�
	pEnemySpawn->m_pos = pos;
	// �^�C�v�ݒ�
	pEnemySpawn->m_enemyType = type;
	
	// ������
	pEnemySpawn->Init();
	
	return pEnemySpawn;
}


//==================================
// ����������
//==================================
HRESULT CEnemySpawn::Init(void)
{
	// �p�[�e�B�N����Z��������
	for (int nCntPart = 0; nCntPart < ENEMYSPAWN_PARTICLE_NUM; nCntPart++)
	{
		// ���W�̐ݒ�
		D3DXVECTOR3 partPos;
		// 6����
		partPos.x = m_pos.x + cosf(nCntPart* D3DXToRadian(360 / ENEMYSPAWN_PARTICLE_NUM))*PARTICLE_DISTANCE;
		partPos.y = m_pos.y + sinf(nCntPart* D3DXToRadian(360 / ENEMYSPAWN_PARTICLE_NUM))*PARTICLE_DISTANCE;
		partPos.z = m_pos.z;

		// ���S�Ɍ������Ĉړ�
		D3DXVECTOR3 partMove;
		partMove = m_pos - partPos;
		D3DXVec3Normalize(&partMove, &partMove);
		// �X�s�[�h��������
		partMove *= PARTICLE_SPEED;

		// �p�[�e�B�N���̐���
		m_pParticle[nCntPart] = CParticle::Create(partPos, partMove, PARTICLE_SIZE, PARTICLE_LIFE, PARTICLE_COL);
		// ���݂̐F
		m_col = PARTICLE_COL;
	}

	m_nCntFrame = 0;
	return S_OK;
}

//==================================
// �I������
//==================================
void CEnemySpawn::Uninit(void)
{
	// �I������
	for (int nCntPart = 0; nCntPart < ENEMYSPAWN_PARTICLE_NUM; nCntPart++)
	{
		if (m_pParticle[nCntPart] != NULL)
		{
			//m_pParticle[nCntPart]->Uninit();
			m_pParticle[nCntPart] = NULL;
		}
	}
	Release();
}

//==================================
// �X�V����
//==================================
void CEnemySpawn::Update(void)
{
	
	for (int nCntPart = 0; nCntPart < ENEMYSPAWN_PARTICLE_NUM; nCntPart++)
	{
		// �p�x��0�x�Ɍ������Ď���������

		// �p�x�̎擾
		float fAngele = m_pParticle[nCntPart]->GetAngle();
		// 0�x�Ɍ�������
		fAngele += (0.0f - fAngele)*PARTICLE_RATE;
		// �p�x�̃Z�b�g
		m_pParticle[nCntPart]->SetAngle(fAngele);

		// ������G�̎�ނɂ���ĐF�𕪂���

		if (m_nCntFrame >= 8)
		{
			// �G�̎�ނŕ���
			switch (m_enemyType)
			{
			case CEnemy::ENEMYTYPE_YELLOW:
				// ���F
				m_col.r += (COLOR_YELLOW.r - m_col.r)*PARTICLE_RATE;
				m_col.g += (COLOR_YELLOW.g - m_col.g)*PARTICLE_RATE;
				m_col.b += (COLOR_YELLOW.b - m_col.b)*PARTICLE_RATE;

				break;
			case CEnemy::ENEMYTYPE_PURPLE:
				// ��
				m_col.r += (COLOR_PURPLE.r - m_col.r)*PARTICLE_RATE;
				m_col.g += (COLOR_PURPLE.g - m_col.g)*PARTICLE_RATE;
				m_col.b += (COLOR_PURPLE.b - m_col.b)*PARTICLE_RATE;
				break;
			case CEnemy::ENEMYTYPE_RED:
				// ��
				m_col.r += (COLOR_RED.r - m_col.r)*PARTICLE_RATE;
				m_col.g += (COLOR_RED.g - m_col.g)*PARTICLE_RATE;
				m_col.b += (COLOR_RED.b - m_col.b)*PARTICLE_RATE;
				break;
			default:
				break;
			}
			// �F�̃Z�b�g
			m_pParticle[nCntPart]->SetColor(m_col);
		}
	}

	// �J�E���g��i�߂�
	m_nCntFrame++;

	// �J�E���g���p�[�e�B�N���̃��C�t��肿����ƒႢ�Ƃ�
	if (m_nCntFrame >= PARTICLE_LIFE - 2)
	{
		// �G�l�~�[�̐���
		CEnemy::Create(m_pos, m_enemyType);
		// �I������
		Uninit();
	}

	
}

//==================================
// �`�揈��
//==================================
void CEnemySpawn::Draw(void)
{

}