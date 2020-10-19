//=============================================================================
//
// メインヘッダ [main.h]
// Author : 増澤 未来
//
//=============================================================================

//*****************************************************************************
//エラー除け
//*****************************************************************************
#ifndef _MAIN_H_ 
#define _MAIN_H_ 

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <WinSock2.h>
#include <stdio.h>
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SERVER_PORT_NUM 12345   //接続先サーバーの接続先ポート
#define MAX_ACCEPT_CONN 100     //接続受付最大数
#define BUFFER_NUM 128          //送受信バッファーサイズ

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************

#pragma comment (lib, "ws2_32.lib")

#endif