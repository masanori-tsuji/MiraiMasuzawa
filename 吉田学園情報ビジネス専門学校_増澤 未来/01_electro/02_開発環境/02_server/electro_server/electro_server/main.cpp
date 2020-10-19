//=============================================================================
//
// ���C�� [main.cpp]
// Author : ���V ����
//
//=============================================================================

//*******************************
// �C���N���[�h
//*******************************
#include "main.h"
#include "protcol_ranking.h"
#include "tcp_client.h"
#include "tcp_listener.h"
#include <thread>

//*******************************
// �}�N����`
//*******************************
#define RANKINGTEXT_PATH "RankingData.txt" // �����L���O�̃p�X

//*******************************
// �v���g�^�C�v�錾
//*******************************
void ReadFile(void);
void WriteFile(void);
int SortRank(void);
int RankUpdate(int  nRankData);
void WorkerThread(CTcpClient*pTcpClient);

//*******************************
// �O���[�o���ϐ�
//*******************************
int g_nRankData[MAX_RANKING + 1] = {};  // �����L���O�f�[�^

//===============================
// ���C���֐�
//===============================
void main(void)
{
	//�ϐ��錾
	WSADATA wsaData;
	SOCKET sockServer;


	//WinSock�̏�����
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);
	if (nErr != 0)
	{
		//���炩�̌����ŏ������Ɏ��s����
		printf("WSAStartup failed\n");
		return ;
	}
	memset(&g_nRankData, 0, sizeof(g_nRankData));
	ReadFile();

	//TcpListener�|�C���^
	CTcpListener *pListener = NULL;

	if (pListener == NULL)
	{
		//�C���X�^���X����
		pListener = CTcpListener::Create(SERVER_PORT_NUM);

		if (pListener != NULL)
		{
			//�T�[�o�[�����[�v
			while (1)
			{
				//�ڑ��̎�t
				CTcpClient*pClient = NULL;

				if (pClient == NULL)
				{
					//�ڑ��҂�
					pClient = pListener->Accept();
					if (pClient != NULL)
					{
						//�����̕���
						std::thread th(WorkerThread, pClient);
						th.detach();
					}
					else
					{
						continue;
					}
				}
			}
		}
		else
		{
			printf("�������̊m�ۂɎ��s���܂����B\n");
			return ;
		}
	}

	pListener->Release();
	//�҂��󂯃\�P�b�g���N���[�Y
	closesocket(sockServer);

	//winsock�I������
	WSACleanup();

}

//===============================
// �t�@�C���ǂݍ���
//===============================
void ReadFile(void)
{
	FILE*pFile = NULL;

	// �t�@�C���ǂݍ���
	pFile = fopen(RANKINGTEXT_PATH, "r");

	if (pFile != NULL)
	{
		// �ǂݍ���
		for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
		{
			fscanf(pFile, "%d", &g_nRankData[nCntRank]);
		}
		fclose(pFile);
	}
}

//===============================
// �t�@�C����������
//===============================
void WriteFile(void)
{
	FILE*pFile = NULL;

	// �t�@�C���ǂݍ���
	pFile = fopen(RANKINGTEXT_PATH, "w");

	if (pFile != NULL)
	{
		// ��������
		for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
		{
			fprintf(pFile, "%d\n", g_nRankData[nCntRank]);
		}
		fclose(pFile);
	}
}

//===============================
// �����L���O�̃\�[�g����
//===============================
int SortRank(void)
{
	int nNum = 11;
	
	for (int nCntRank = 0; nCntRank < MAX_RANKING + 1; nCntRank++)
	{
		for (int nCntSort = nCntRank + 1; nCntSort < MAX_RANKING + 1; nCntSort++)
		{
			
			if (g_nRankData[nCntRank] < g_nRankData[nCntRank])
			{
				// ����ւ�����
				int  nSaveData = g_nRankData[nCntRank];
				g_nRankData[nCntRank] = g_nRankData[nCntSort];
				g_nRankData[nCntSort] = nSaveData;

				if (nCntSort == nNum - 1)
				{
					nNum = nCntRank + 1;
				}
			}
		}
	}

	if (nNum == 11) { nNum = 0; }

	return nNum;
}

//===============================
// �����L���O�̍X�V����
//===============================
int RankUpdate(int  nRankData)
{
	int nRank = -1;

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		// �����N�����܂��ĂȂ�������
		if (g_nRankData[nCntRank] == NULL)
		{
			g_nRankData[nCntRank] = nRankData;
			return nCntRank + 1;
		}

		if (g_nRankData[nCntRank] < nRankData)
		{
			nRank = nCntRank;
			break;
		}
	}

	if (nRank >= 0)
	{
		for (int nCntRank = MAX_RANKING - 1; nCntRank > nRank; nCntRank--)
		{
			g_nRankData[nCntRank] = g_nRankData[nCntRank - 1];
		}
		g_nRankData[nRank] = nRankData;
	}

	return nRank + 1;
}

//===============================
// �����L���O�T�[�o�[�̏���
//===============================
void WorkerThread(CTcpClient * pTcpClient)
{
	char aRecvBuffer[BUFFER_NUM]; // �f�[�^��M�p
	char aSendBuffer[BUFFER_NUM]; // �f�[�^���M�p

	// �f�[�^�̎�M
	int nRecvNum = pTcpClient->Recv(&aRecvBuffer[0], sizeof(aRecvBuffer));
	if (nRecvNum <= 0)
	{
		//�\�P�b�g�ڑ����N���[�Y
		pTcpClient->Release();
		return;
	}

	int nScore;
	int nSendRank;

	switch (aRecvBuffer[0])
	{
	case COMMAND_TYPE_GET_RANKING:
		// �����L���O�擾API
		for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
		{
			
			// �G���f�B�A���ϊ�
			nScore = htonl(g_nRankData[nCntRank]);
			// �^�C���̃R�s�[
			memcpy(&aSendBuffer[nCntRank * sizeof(int)], &nScore, sizeof(int));
		}

		// �����L���O�f�[�^�̑��M
		pTcpClient->Send(aSendBuffer, sizeof(int) * MAX_RANKING);


		break;
	case COMMAND_TYPE_SET_RANKING:
		// �����L���O�ݒ�API

		int  nRankUpdate;
		// ���Ԃ̃R�s�[
		nScore = *(int*)&aRecvBuffer[1];
		nRankUpdate = ntohl(nScore);
		
		//�����L���O�f�[�^�̍X�V
		nSendRank = RankUpdate(nRankUpdate);
		
		// �����L���O�f�[�^�̏�������
		WriteFile();

		memcpy(&aSendBuffer[0], (char*)&nSendRank, sizeof(char));
		// �����L���O�f�[�^�̑��M
		pTcpClient->Send(aSendBuffer, sizeof(char));

		break;
	default:
		break;
	}

	//�\�P�b�g�ڑ����N���[�Y
	pTcpClient->Release();
}
