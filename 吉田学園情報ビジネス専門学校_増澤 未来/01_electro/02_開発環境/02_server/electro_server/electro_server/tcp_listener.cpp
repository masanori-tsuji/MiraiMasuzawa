//=============================================================================
//
// TCP�ڑ���t�̏��� [tcp_listener.cpp]
// Author : ���V�@����
//
//=============================================================================
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "tcp_listener.h"
#include "tcp_client.h"

//=============================================================================
// CTcpListener����
//=============================================================================
CTcpListener* CTcpListener::Create(int nPortNum)
{
	CTcpListener*pListener;

	// TCP�ڑ���t�N���X�̃C���X�^���X����
	pListener = new CTcpListener;

	if (pListener != NULL)
	{
		//������
		if (!pListener->Init(nPortNum))
		{
			pListener = NULL;
		}
	}
	else
	{
		printf("�������̊m�ۂɎ��s���܂����B\n");
	}


	return pListener;
}

//=============================================================================
// CTcpListener�R���X�g���N�^
//=============================================================================
CTcpListener::CTcpListener()
{
	m_sockServer = -1;
}

//=============================================================================
// CTcpListener�f�X�g���N�^
//=============================================================================
CTcpListener::~CTcpListener()
{
}

//=============================================================================
// ����������
//=============================================================================
bool CTcpListener::Init(int nPortNum)
{
	struct  sockaddr_in addr;

	//�ڑ���t�p�\�P�b�g�̍쐬
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);

	//�ڑ���t���̐ݒ�
	addr.sin_family = AF_INET;               //IPv4
	addr.sin_port = htons(SERVER_PORT_NUM);  //�|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = INADDR_ANY;  //���ׂĂ̐ڑ��󂯕t����

											 //�\�P�b�g��IP�A�h���X�ƃ|�[�g�ԍ���ݒ肷��
	bind(m_sockServer, (struct sockaddr*)&addr, sizeof(addr));

	//�ڑ��v����t���J�n����
	listen(m_sockServer, MAX_ACCEPT_CONN);

	return true;
}

//=============================================================================
// �ڑ���t����
//=============================================================================
CTcpClient* CTcpListener::Accept()
{


	if (m_sockServer < 0) {
		return NULL;
	}

	//�\�P�b�g�ڑ����󂯕t����i�󂯕t����܂Ńv���O�����̓u���b�N�����j
	int nAddrLength = sizeof(m_addrClient);

	CTcpClient*pClient = NULL;
	// �ڑ���t����
	pClient = CTcpClient::Create(accept(m_sockServer, (struct sockaddr*)&m_addrClient, &nAddrLength));
	printf("connect:[%s]\n", inet_ntoa(m_addrClient.sin_addr));

	return pClient;
}

//=============================================================================
// �j������
//=============================================================================
void CTcpListener::Release()
{
	// �ؒf����
	Close();

	// �C���X�^���X�폜
	delete this;
}

//=============================================================================
// �N���[�Y����
//=============================================================================
void CTcpListener::Close()
{
	if (m_sockServer < 0) {
		return;
	}

	//�ؒf����
	closesocket(m_sockServer);
	m_sockServer = -1;
}


