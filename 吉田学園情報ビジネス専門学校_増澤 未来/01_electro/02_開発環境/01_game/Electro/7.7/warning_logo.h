//=============================================================================
//
// warning_logo�w�b�_ [warning_logo.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _WARNING_LOGO_H_
#define _WARNING_LOGO_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//=============================
// �O���錾
//=============================
class CPolygon;

//*****************************
//�N���X��`
//*****************************

//���[�j���O���S�N���X
class CWarningLogo : public CScene3d
{
public:
	// �����o�֐�
	CWarningLogo();
	~CWarningLogo();

	static CWarningLogo *Create(void);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;        // �e�N�X�`���ւ̃|�C���^
};

#endif