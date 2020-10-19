//=============================================================================
//
// TCP�ڑ���t�̏��� [tcp_listener.h]
// Author : ���V ����
//
//=============================================================================
#ifndef _TCPLISTENER_H_
#define _TCPLISTENER_H_

#include <winsock2.h>
#include "main.h"

//*********************************************************
// �O���錾
//*********************************************************
class CTcpClient;

//*********************************************************
// TCP�ڑ���t�N���X
//*********************************************************
class CTcpListener
{
public:
	static CTcpListener* Create(int nPortNum); //�N���G�C�g
	CTcpListener();                            //�R���X�g���N�^
	~CTcpListener();                           //�f�X�g���N�^
	bool Init(int nPortNum);                   //������
	CTcpClient* Accept();                      //�ڑ�
	void Release();                            //�����[�X
	void Close();                              //�ؒf

	char* GetIP(void) { return inet_ntoa(m_addrClient.sin_addr); }//�N���C�A���g��IP�A�h���X�̎擾

private:
	SOCKET m_sockServer;//�T�[�o�[�p�\�P�b�g
	struct  sockaddr_in m_addrClient;//�N���C�A���g���
};

#endif
