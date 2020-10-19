//=============================================================================
//
// item�w�b�_ [item.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ITEME_H_
#define _ITEME_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// �N���X��`
//*****************************

//�A�C�e���N���X
class CItem : public CScene3d
{
public:

	// ��ԗ�
	typedef enum
	{
		ITEMTYPE_RECOVERY = 0,
		ITEMTYPE_BOMB,
		ITEMTYPE_MAX,
	}ITEMTYPE;

	//�����o�֐�
	CItem();
	~CItem();

	static CItem *Create(const D3DXVECTOR3 pos, const ITEMTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static std::list<CItem*>*GetItemlist(void) { return &m_itemList; }
private:
	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[ITEMTYPE_MAX]; // �e�N�X�`��
	static std::list<CItem*> m_itemList;  // �G�l�~�[���X�g
	ITEMTYPE m_itemType;                  // �A�C�e���^�C�v
};

#endif