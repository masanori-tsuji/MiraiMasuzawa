//=============================================================================
//
// life�w�b�_ [life.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _LIFE_H_
#define _LIFE_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//�O���錾
//*****************************
class CPolygon;

//*****************************
//�}�N����`
//*****************************
#define PLAYER_MAX_LIFE 6
#define BOSS_MAX_LIFE 50

//*****************************
//�N���X��`
//*****************************

//2d�|���S���N���X
class CLife : public CScene
{
public:
	// HP�o�[�̃p�[�c��
	typedef enum
	{
		BAR_WHILTE=0,
		BAR_RED,
		BAR_GREEN,
		BAR_FRAME,
		BAR_PARTS_MAX,
	}BAR_PARTS;

	// �N�̃��C�t��
	typedef enum
	{
		USER_PLAYER=0,
		USER_BOSS,
		USER_MAX,
	}LIFE_USER;

	// �����o�֐�
	CLife();
	~CLife();
	static CLife *Create(LIFE_USER user);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���ւ̃|�C���^
	CPolygon* m_apPolygon[BAR_PARTS_MAX]; // ���C�t�`��p�̃|���S��
	float m_fRedLife;                     // �Ԃ��Q�[�W�����񂾂񌸂��Ă����p
	D3DXVECTOR3 m_leftPos;                // ���C�t�̍��[
	float m_fBarWidht;                    // ��
	float m_fBarHeight;                   // ����
	int m_nMaxLife;                       // ���C�t�̍ő吔
	LIFE_USER m_user;                     // �N�̃��C�t��
};

#endif