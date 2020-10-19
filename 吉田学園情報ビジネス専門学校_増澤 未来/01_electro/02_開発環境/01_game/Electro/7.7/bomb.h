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
class CBomb : public CScene3d
{
public:

	//�����o�֐�
	CBomb();
	~CBomb();
	static CBomb *Create(const D3DXVECTOR3 pos, const float fMaxsize , const D3DCOLOR col);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`��
	int m_nCntAnim;  // �A�j���[�V�����J�E���g
	int m_nAnimX;    // �A�j���[�V����X��
	int m_nAnimY;    // �A�j���[�V����Y��
	bool m_bHitBoss; // �{�X�ɑ��i�q�b�g���Ȃ��悤�Ƀt���O
	float m_fMaxsize; // �ő�T�C�Y

};

#endif