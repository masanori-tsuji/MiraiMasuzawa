//=============================================================================
//
// TitleLogo�w�b�_ [TitleLogo.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene2d.h"

//*****************************
//�N���X��`
//*****************************

//�^�C�g�����S�N���X
class CTitleLogo : public CScene2d
{
public:
	// �����o�֐�
	CTitleLogo();
	~CTitleLogo();
	static CTitleLogo *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;        // �e�N�X�`���ւ̃|�C���^
	int m_nCntAnim;       // �A�j���[�V�����J�E���g
	int m_nAnimX;         // �A�j���[�V����X��
	int m_nAnimY;         // �A�j���[�V����Y��
	int m_nCntSetAnim;    
	bool m_bAnim;
};

#endif