//=============================================================================
//
// bomb�w�b�_ [bomb.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _BOMB_H_
#define _BOMB_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// �N���X��`
//*****************************

// �{���N���X
<<<<<<< HEAD
class CBomb : public CScene
=======
class CBomb : public CScene3d
>>>>>>> 1f4259f10d71f719b19dc40ae4c297906db09178
{
public:

	//�����o�֐�
	CBomb();
	~CBomb();
<<<<<<< HEAD
	static CBomb *Create(const D3DXVECTOR3 pos, const float fMaxsize );
=======
	static CBomb *Create(const D3DXVECTOR3 pos, const float fMaxsize , const D3DCOLOR col);
>>>>>>> 1f4259f10d71f719b19dc40ae4c297906db09178
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`��
<<<<<<< HEAD
	int m_nCntAnim;     // �A�j���[�V�����J�E���g
	int m_nAnimX;       // �A�j���[�V����X��
	int m_nAnimY;       // �A�j���[�V����Y��
	bool m_bHitBoss;    // �{�X�ɑ��i�q�b�g���Ȃ��悤�Ƀt���O
	float m_fMaxsize;   // �ő�T�C�Y
	D3DXVECTOR3 m_pos;  // �{���̍��W
	D3DXVECTOR3 m_size; // �{���̃T�C�Y
=======
	int m_nCntAnim;  // �A�j���[�V�����J�E���g
	int m_nAnimX;    // �A�j���[�V����X��
	int m_nAnimY;    // �A�j���[�V����Y��
	bool m_bHitBoss; // �{�X�ɑ��i�q�b�g���Ȃ��悤�Ƀt���O
	float m_fMaxsize; // �ő�T�C�Y

>>>>>>> 1f4259f10d71f719b19dc40ae4c297906db09178
};

#endif