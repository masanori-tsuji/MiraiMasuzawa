//=============================================================================
//
// time�w�b�_ [time.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TIME_H_
#define _TIME_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//�O���錾
//*****************************
class CNumber;

//*****************************
//�}�N����`
//*****************************
#define MAX_TIME_NUM 4 // �^�C���ɕK�v�ȃi���o�[�̐�

//*****************************
//�N���X��`
//*****************************

//�^�C���N���X
class CTime : public CScene
{
public:
	// �����o�֐�
	CTime();
	~CTime();
	static CTime *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static int GetTime(void) { return m_nTime; }
	static void SetPauseTime(void) { m_nPauseCurrentTime = timeGetTime(); }
private:
	// �����o�ϐ�
	CNumber* m_apNumber[MAX_TIME_NUM]; // �^�C���`��p�̃|���S��
	static int m_nTime;                // �o�ߎ���
	static int m_nPauseCurrentTime;           // �|�[�Y�ɓ���������
	int m_nPauseTime;                  // �|�[�Y��ʒ��̃^�C��
	int m_nCurrentTime;                // �J�n����
};

#endif