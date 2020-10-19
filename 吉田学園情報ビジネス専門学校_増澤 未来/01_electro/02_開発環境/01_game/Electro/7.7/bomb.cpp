////////////////////////////////////////////////////
//
//    bomb�N���X�̏���[bomb.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "bomb.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "sound.h"
#include "score.h"
#include "game.h"
#include "boss.h"
#include "particle.h"
#include "bullet.h"
#include "score.h"

//*****************************
// �}�N����`
//*****************************
#define BOMB_TEXTURE_PATH "./data/Textures/bomb000.png" //�e�N�X�`���̃p�X
#define BOMB_RATE_SIZE 0.1f;

//******************************
// �ÓI�����o�ϐ��錾
//******************************
LPDIRECT3DTEXTURE9 CBomb::m_pTexture = NULL; // �e�N�X�`���|�C���^

//******************************
// �R���X�g���N�^
//******************************
CBomb::CBomb():CScene(OBJTYPE_BOMB)
{
	// �ϐ��̃N���A
	m_bHitBoss = false;
	m_fMaxsize = 0.0f;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//******************************
// �f�X�g���N�^
//******************************
CBomb::~CBomb()
{
}

//******************************
// �N���G�C�g
//******************************
CBomb * CBomb::Create(const D3DXVECTOR3 pos, const float fMaxsize)
{
	// �������̊m��
	CBomb *pBomb;
	pBomb = new CBomb;
	// ������
	pBomb->Init();

	// �e�l�̑���E�Z�b�g
	pBomb->m_pos = pos;             // ���W
	pBomb->m_fMaxsize = fMaxsize;   // �ő�T�C�Y

	// SE�̍Đ�
	CManager::GetSound()->Play(CSound::LABEL_SE_BOMB);

	return pBomb;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CBomb::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BOMB_TEXTURE_PATH, &m_pTexture);


	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CBomb::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//******************************
// ����������
//******************************
HRESULT CBomb::Init(void)
{
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f); // �T�C�Y
	SetObjType(OBJTYPE_BOMB);               // �I�u�W�F�N�g�^�C�v

	return S_OK;
}

//******************************
// �I������
//******************************
void CBomb::Uninit(void)
{
	Release();
}

//******************************
// �X�V����
//******************************
void CBomb::Update(void)
{

	m_size.x += ((m_fMaxsize + 3.0f) - m_size.x)*BOMB_RATE_SIZE;
	m_size.y += ((m_fMaxsize + 3.0f) - m_size.y)*BOMB_RATE_SIZE;

	// �����蔻��

	// �G�l�~�[���X�g�̎擾
	std::list<CEnemy*>::iterator enemyIteretor;
	for (enemyIteretor = CEnemy::GetEnemylist()->begin(); enemyIteretor != CEnemy::GetEnemylist()->end(); enemyIteretor++)
	{

		D3DXVECTOR3 size = m_size/2;  // �{���̃T�C�Y

		D3DXVECTOR3 enemyPos = (*enemyIteretor)->GetPos();   // �G�̍��W
		D3DXVECTOR3 enemySize = (*enemyIteretor)->GetSize(); // �G�̃T�C�Y

		if (m_pos.x - size.x <= enemyPos.x + enemySize.x &&
			m_pos.x + size.x >= enemyPos.x - enemySize.x &&
			m_pos.y - size.y <= enemyPos.y + enemySize.y &&
			m_pos.y + size.y >= enemyPos.y - enemySize.y)
		{
			// �����̐���
			//CExplosion::Create(enemyPos, D3DXVECTOR3(160, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			// �G�l�~�[����SE
			CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION);

			// �G�l�~�[������
			(*enemyIteretor)->HitAttack(5);
			// �X�R�A���Z
			CScore::AddScore(50);
			break;

		}
	}

	// �o���b�g���X�g�̎擾
	std::list<CBullet*>::iterator bulletIteretor;
	for (bulletIteretor = CBullet::GetBulletlist()->begin(); bulletIteretor != CBullet::GetBulletlist()->end(); )
	{
		if ((*bulletIteretor)->GetUser() == CBullet::BULLETUSER_ENEMY)
		{
			D3DXVECTOR3 size = m_size / 2;  // �{���̃T�C�Y

			D3DXVECTOR3 bulletPos = (*bulletIteretor)->GetPos();   // �G�̍��W
			D3DXVECTOR3 bulletSize = (*bulletIteretor)->GetSize(); // �G�̃T�C�Y

			if (m_pos.x - size.x <= bulletPos.x + bulletSize.x &&
				m_pos.x + size.x >= bulletPos.x - bulletSize.x &&
				m_pos.y - size.y <= bulletPos.y + bulletSize.y &&
				m_pos.y + size.y >= bulletPos.y - bulletSize.y)
			{
				// �����̐���
				//CExplosion::Create(enemyPos, D3DXVECTOR3(160, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				
				CBullet*pBullet = *bulletIteretor;
				bulletIteretor = CBullet::GetBulletlist()->erase(bulletIteretor);
				//	�e������
				pBullet->Uninit();
				//// ���X�g�̏�����
				//bulletIteretor = CBullet::GetBulletlist()->begin();

				// �X�R�A���Z
				CScore::AddScore(10);
			}
			else
			{
				bulletIteretor++;
			}
		}
		else
		{
			bulletIteretor++;
		}
	}

	if (CBoss::IsAlive())
	{
		if (!m_bHitBoss)
		{
			// �{�X�ւ̓����蔻��
			D3DXVECTOR3 size = m_size / 2;  // �{���̃T�C�Y

			D3DXVECTOR3 bossPos = CGame::GetBoss()->GetPos();   // �G�̍��W
			D3DXVECTOR3 bossSize = CGame::GetBoss()->GetSize(); // �G�̃T�C�Y

			if (m_pos.x - size.x/2 <= bossPos.x + bossSize.x / 2 &&
				m_pos.x + size.x/2 >= bossPos.x - bossSize.x / 2 &&
				m_pos.y - size.y/2 <= bossPos.y + bossSize.y / 2 &&
				m_pos.y + size.y/2 >= bossPos.y - bossSize.y / 2)
			{
				// �����̐���
				//CExplosion::Create(enemyPos, D3DXVECTOR3(160, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				// �G�l�~�[����SE
				CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION);

				// �G�l�~�[������
				CGame::GetBoss()->HitAttack(5);
				// �X�R�A���Z
				CScore::AddScore(50);
				m_bHitBoss = true;
			}
		}
	}
	int nRnd = rand() % 10 + 5;
	for (int nCntparticle = 0; nCntparticle < nRnd; nCntparticle++)
	{
		// �����_���ȋ���
		float fRandDistance = (float)(rand() % 500 - 250) / 100;
		// �����_���Ȋp�x
		int nRandAngle = rand() % 360;
		
		// �����_���ȍ��W
		D3DXVECTOR3 randPos;
		randPos.x = m_pos.x + cosf(D3DXToRadian(nRandAngle))*(m_size.x/2 + fRandDistance);
		randPos.y = m_pos.y + sinf(D3DXToRadian(nRandAngle))*(m_size.y/2 + fRandDistance);
		randPos.z = 0.0f;
	
		if (m_fMaxsize >= 500)
		{// �A�C�e���̃{��

			// �����_���ȃT�C�Y
			int nRandSize = rand() % 30 + 20;
			// �p�[�e�B�N���̐���
			CParticle::Create(randPos, 
				D3DXVECTOR3((float)(rand() % 3 - 1),
				(float)(rand() % 3 - 1), 0.0f), 
				D3DXVECTOR3((float)nRandSize, (float)nRandSize, 0.0f),
				rand() % 10 + 10,
				D3DXCOLOR((float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f, 1.0f));
		}
		else
		{// �}�i�T�[�N���̃{��

			// �����_���ȃT�C�Y
			int nRandSize = rand() % 20 + 15;
			// �p�[�e�B�N���̐���
			CParticle::Create(randPos,
				D3DXVECTOR3((float)(rand() % 3 - 1),
				(float)(rand() % 3 - 1), 0.0f),
				D3DXVECTOR3((float)nRandSize, (float)nRandSize, 0.0f),
				rand() % 10 + 10,
				D3DXCOLOR((float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f, 1.0f, 1.0f));
		}
	}
	
	// �ő�T�C�Y�ɓ��B���������
	if (m_size.x > m_fMaxsize)
	{
		Uninit();
		return;
	}
}

//******************************
// �`�揈��
//******************************
void CBomb::Draw(void)
{
}

