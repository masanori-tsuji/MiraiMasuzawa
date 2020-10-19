//=============================================================================
//
// TitleLogo�w�b�_ [TitleLogo.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _PRESSLOGO_H_
#define _PRESSLOGO_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "title_logo.h"

//*****************************
//�N���X��`
//*****************************

//�v���X���S�N���X
class CPressLogo : public CTitleLogo
{
public:
	// �����o�֐�
	CPressLogo();
	~CPressLogo();
	static CPressLogo *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;        // �e�N�X�`���ւ̃|�C���^

};

#endif