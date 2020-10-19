//=============================================================================
//
// cursor�w�b�_ [cursor.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _CURSOR_H_
#define _CURSOR_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene2d.h"

//*****************************
// �N���X��`
//*****************************

// �J�[�\���N���X
class CCursor : public CScene2d
{
public:
	//�����o�֐�
	CCursor();
	~CCursor();
	static CCursor *Create(const D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos3d(void);

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���̃|�C���^
<<<<<<< HEAD
=======
	float m_fRotAngle;                       // ��]�p�x
>>>>>>> 1f4259f10d71f719b19dc40ae4c297906db09178
	int m_nCntAnim;     // �A�j���[�V�����J�E���g
	int m_nAnimX;       // �A�j���[�V����X��
	int m_nAnimY;       // �A�j���[�V����Y��
};

#endif