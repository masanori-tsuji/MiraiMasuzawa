//=============================================================================
//
// gage�w�b�_ [gage.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _GAGE_H_
#define _GAGE_H_

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
//�N���X��`
//*****************************

//�Q�[�W�N���X
class CGage : public CScene
{
public:
	// HP�o�[�̃p�[�c��
	typedef enum
	{
		BAR_WHILTE=0,
		BAR_RED,
		BAR_FRONT,
		BAR_FRAME,
		BAR_PARTS_MAX,
	}BAR_PARTS;

	// �N�̃��C�t��
	typedef enum
	{
		GAGE_PLAYER_HP=0,
		GAGE_PLAYER_MP,
		GAGE_BOSS_HP,
		GAGE_MAX,
	}GAGE_TYPE;

	// �����o�֐�
	CGage();
	~CGage();
	static CGage *Create(GAGE_TYPE type);
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
	int m_nMaxNum;                       // ���C�t�̍ő吔
	GAGE_TYPE m_gageType;                     // �N�̃��C�t��
};

#endif