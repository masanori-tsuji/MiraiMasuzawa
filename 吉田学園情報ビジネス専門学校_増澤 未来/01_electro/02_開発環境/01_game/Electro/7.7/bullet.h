//=============================================================================
//
// bullet�w�b�_ [bullet.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// �}�N����`
//*****************************
#define BULLET_SPEED_PLAYER 8    // ���x(�v���C���[�̒e)
#define BULLET_SPEED_ENEMY 4     // ���x(�G�l�~�[�̒e)
#define BULLET_SIZE 15    // �T�C�Y

//*****************************
// �N���X��`
//*****************************

// �e�N���X
class CBullet : public CScene3d
{
public:
	typedef enum
	{
		BULLETUSER_PLAYER,
		BULLETUSER_ENEMY,
		BULLETUSER_MAX,
	}BULLETUSER;

	//�����o�֐�
	CBullet();
	~CBullet();
	static CBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const int nLife, const  BULLETUSER user, const D3DCOLOR col);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static std::list<CBullet*>*GetBulletlist(void) { return &m_bulletList; }
	void SetUser(BULLETUSER user) { m_user = user; }
	BULLETUSER GetUser(void) { return m_user; }
protected:
	void CollisionBullet(BULLETUSER user);
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`��
private:
	// �����o�ϐ�
	static std::list<CBullet*> m_bulletList;  // ���X�g
	D3DXVECTOR3 m_move; // �ړ���
	int m_nLife;        // ����
	BULLETUSER m_user; // �o���b�g���[�U�[
};

#endif