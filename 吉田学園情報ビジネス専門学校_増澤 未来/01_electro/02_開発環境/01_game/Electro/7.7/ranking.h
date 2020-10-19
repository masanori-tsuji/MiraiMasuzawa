//=============================================================================
//
// �����L���O�w�b�_ [ranking.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _RANKING_H_
#define _RANKING_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"
#include "score.h"

//*****************************
//�O���錾
//*****************************
class CNumber;

//*****************************
//�}�N����`
//*****************************
#define MAX_RANK 8

//*****************************
//�N���X��`
//*****************************

//�����L���O�N���X
class CRanking : public CScene
{
public:
	// �����o�֐�
	CRanking();
	~CRanking();
	static CRanking *Create(void);
	static void GetRanking(void);
	static int SetRanking(void);
	static void SetRanking(int nScore);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
private:
	// �����o�ϐ�
	CNumber* m_apRankNumber[MAX_RANK];                   // �����L���O
	CNumber* m_apScoreNumber[MAX_RANK][MAX_SCORE_DIGIT]; // �X�R�A�|���S��
	static int m_nNowScore;                              // ���̃v���C�̃X�R�A
	static CNumber* m_pNowScore[MAX_SCORE_DIGIT];        // �X�R�A�|���S��
	static int m_nRanking[MAX_RANK];                     // �X�R�A�f�[�^
	int m_nCntFlash;

};

#endif