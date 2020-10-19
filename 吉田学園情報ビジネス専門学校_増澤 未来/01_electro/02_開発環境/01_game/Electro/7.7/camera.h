//=============================================================================
//
// camera�w�b�_ [camera.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene2d.h"

//*****************************
// �N���X��`
//*****************************

//�J�����N���X
class CCamera
{
public:
	//�����o�֐�
	CCamera();
	~CCamera();

	static CCamera *Create();
	static void Release(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetPos(void) { return m_posV; }
	
	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }
	D3DXMATRIX GetProjectionMtx(void) { return m_mtxProjection; }

	float GetCameraWidth(void) { return (float)(SCREEN_WIDTH * 2) + m_fViewAriaX; }
	float GetCameraHeight(void) { return (float)(SCREEN_HEIGHT * 2) + m_fViewAriaY; }
private:
	// �����o�ϐ�
	static CCamera *m_pCamera;
	D3DXVECTOR3 m_posV;//�J�����̍��W
	D3DXVECTOR3 m_posR;//�����_
	D3DXVECTOR3 m_vecU;//������x�N�g��
	D3DXMATRIX  m_mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX  m_mtxView;//�r���[�}�g���b�N�X
	float       m_fViewAriaX; // ����̍L������p
	float       m_fViewAriaY; // ����̍L������p
};

#endif