//=============================================================================
//
// manacircre�w�b�_ [manacircre.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _MANACIRCRE_H_
#define _MANACIRCRE_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// �}�N����`
//*****************************
#define CIRCLE_MAX 6  // �T�[�N���̍ő吔 

//*****************************
// �N���X��`
//*****************************

// �T�[�N���N���X
class CManaCircle : public CScene3d
{
public:

	//�����o�֐�
	CManaCircle();
	~CManaCircle();
	static CManaCircle *Create(const D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	static void SpawnManager(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//static std::list<CManaCircle*>*GetCirclelist(void) { return &m_circleList; }
	static void SetCircleNum(int nNum) { m_nNumCircle = nNum; }
	static void SetCircleMax(int nNum) { m_nMaxCircle = nNum; }
	static CManaCircle *GetCircle(int nIndex) { return m_apCircle[nIndex]; }
private:
	static D3DXVECTOR3 GetRandCirclePos(void);
	void AnimationManager(void);
	void CollisionCircle(void);
	void LostCircle(void);

	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`��
	static CManaCircle *m_apCircle[CIRCLE_MAX];
	//static std::list<CManaCircle*> m_circleList;  // �T�[�N�����X�g
	static int m_nNumCircle;     // �o�����Ă���T�[�N���̐�
	static int m_nMaxCircle;     // �o������T�[�N���̍ő吔
	int nCntRecovery;   // �T�[�N���ɓ����Ă���Ԃ̃J�E���g
	int m_nIndex;
	bool bInCircle;     // �T�[�N���ɓ����Ă��邩

	int m_nCntAnim;     // �A�j���[�V�����J�E���g
	int m_nAnimX;       // �A�j���[�V����X��
	int m_nAnimY;       // �A�j���[�V����Y��

};

#endif