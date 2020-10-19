//=============================================================================
//
// gage�w�b�_ [gage.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _REMAIN_H_
#define _REMAIN_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//�O���錾
//*****************************
class CPolygon;
class CNumber;

//*****************************
//�N���X��`
//*****************************

//�c�@�N���X
class CRemain : public CScene
{
public:

	// �����o�֐�
	CRemain();
	~CRemain();
	static CRemain *Create(void);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���ւ̃|�C���^
	CPolygon* m_pPolygon; // ���C�t�`��p�̃|���S��
	CNumber *m_pNumber;
	int m_nRemain;
};

#endif