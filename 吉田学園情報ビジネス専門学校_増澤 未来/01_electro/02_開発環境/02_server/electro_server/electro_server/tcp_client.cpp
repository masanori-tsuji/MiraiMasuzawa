//=============================================================================
//
// TCP����M�̏��� [tcp_client.cpp]
// Author : ���V�@����
//
//=============================================================================
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "tcp_client.h"

//=============================================================================
// CTcpClient���� (connect�ɂ��ڑ�)
//=============================================================================
CTcpClient* CTcpClient::Create(const char* pHostName, int nPortNum)
{
	//�������̊m��
	CTcpClient*pTcpClient = new CTcpClient;

	if (pTcpClient != NULL)
	{
		//������
		if (!pTcpClient->Init(pHostName, nPortNum))
		{
			pTcpClient->Close();
			pTcpClient = NULL;
		}
	}
	else
	{
		printf("�������̊m�ۂɎ��s���܂����B\n");
		return NULL;
	}
	return pTcpClient;

}

//=============================================================================
// CTcpClient���� (accept�ɂ��ڑ�)
//=============================================================================
CTcpClient* CTcpClient::Create(SOCKET sock)
{
	// TCP����M�N���X�̃C���X�^���X����
	CTcpClient*pTcpClient = new CTcpClient;

	if (pTcpClient != NULL)
	{
		//����������
		if (!pTcpClient->Init(sock))
		{
			pTcpClient->Release();
			pTcpClient = NULL;
		}
	}
	else
	{
		printf("�������̊m�ۂɎ��s���܂����B\n");
	}
	return pTcpClient;

}

//=============================================================================
// CTcpClient�R���X�g���N�^
//=============================================================================
CTcpClient::CTcpClient()
{
	m_sock = -1;
}

//=============================================================================
// CTcpClient�f�X�g���N�^
//=============================================================================
CTcpClient::~CTcpClient()
{
}

//=============================================================================
// ����������
//=============================================================================
bool CTcpClient::Init(const char* pHostName, int nPortNum)
{
	//�ϐ��錾
	struct sockaddr_in addr;

	//�ڑ���t���̐ݒ�
	addr.sin_family = AF_INET;                           //IPv4
	addr.sin_port = htons(nPortNum);                     //�|�[�g�ԍ�
	addr.sin_addr.S_un.S_addr = inet_addr(pHostName);  //�T�[�o�[��IP

													   //�ڑ��p�\�P�b�g�̐���
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == INVALID_SOCKET)
	{
		printf("socket:%d\n", WSAGetLastError());
		return 1;
	}

	//�R�l�N�g
	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("connect:%dan", WSAGetLastError());

		//�L�[���͑҂�
		rewind(stdin);
		getchar();

		closesocket(m_sock);
		return false;
	}

	return true;

}

//=============================================================================
// ����������
//=============================================================================
bool CTcpClient::Init(SOCKET sock)
{
	m_sock = sock;
	return true;
}

//=============================================================================
// ���M����
//=============================================================================
int CTcpClient::Send(char* pSendData, int nSendDataSize)
{
	if (m_sock < 0)
	{
		return 0;
	}

	//���͂���������̑��M
	return send(m_sock, &pSendData[0], nSendDataSize, 0);

}

//=============================================================================
// ��M����
//=============================================================================
int CTcpClient::Recv(char* pRecvData, int nRecvBufferSize)
{
	if (m_sock < 0) {
		return 0;
	}
	//�������[��0�N���A
	memset(pRecvData, 0, nRecvBufferSize);

	//�f�[�^�̎�M
	return recv(m_sock, pRecvData, nRecvBufferSize, 0);

}

//=============================================================================
// �j������
//=============================================================================
void CTcpClient::Release()
{
	//�ؒf����
	Close();
	//�������̉��
	delete this;
}

//=============================================================================
// �N���[�Y����
//=============================================================================
void CTcpClient::Close()
{
	if (m_sock < 0)
	{
		return;
	}
	closesocket(m_sock);
	m_sock = -1;

}