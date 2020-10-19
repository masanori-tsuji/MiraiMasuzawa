//=======================================================================================
//
//タイトルメニュー処理 [titlemenu.cpp]
// Author : Masuzawa Mirai
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "pause.h"
#include "polygon.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "tcp_client.h"
#include "fade.h"
#include "joypad.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define BACK_SIZE D3DXVECTOR3(200.0f,180.0f,0.0f)                  // 背面サイズ
#define BACK_POS D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f)  // 背面座標

#define STRING_SIZE D3DXVECTOR3(150.0f,50.0f,0.0f)                                           // 文字テクスチャのサイズ
#define RESUME_POS  D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y - (STRING_SIZE.y + 25),0.0f) // 続けるの座標
#define RESTART_POS D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y,0.0f)                        // リスタートの座標
#define EXIT_POS   	D3DXVECTOR3(SCREEN_WIDTH/2, 35 + BACK_POS.y + (STRING_SIZE.y + 25),0.0f) // 終了の座標

#define MENU_ENTER_COL D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f)     // 選んでるメニューの色
#define MENU_NOT_ENTER_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) // 選んでないメニューの色

//=======================================================================================
// 前方宣言
//=======================================================================================
LPDIRECT3DTEXTURE9 CPause::m_apTexture[CPause::PARTS_MAX] = {}; //テクスチャ

//=======================================================================================
// コンストラクタ
//=======================================================================================
CPause::CPause()
{
	// 変数のクリア
	memset(&m_pPolygon, 0, sizeof(m_pPolygon));
	m_nMenu = RESUME;
	m_bMove = true;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CPause::~CPause()
{

}

//=======================================================================================
// クリエイト
//=======================================================================================
CPause* CPause::Create(void)
{
	// メモリの確保
	CPause* pPause = new CPause();
	// 初期化処理
	pPause->Init();

	return pPause;
}

//=======================================================================================
// テクスチャのロード
//=======================================================================================
HRESULT CPause::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_back.png"   , &m_apTexture[BACK]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_resume.png" , &m_apTexture[RESUME]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_restart.png", &m_apTexture[RESTART]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/pause_exit.png" , &m_apTexture[EXIT]);

	return S_OK;
}
//=======================================================================================
// テクスチャのアンロード
//=======================================================================================
void CPause::UnLoad(void)
{

	for (int nCntTex = 0; nCntTex < PARTS_MAX; nCntTex++)
	{
		// テクスチャの開放
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CPause::Init(void)
{
	// ポリゴン生成

	// 後ろのやつ
	m_pPolygon[BACK] = CPolygon::Create(BACK_POS, BACK_SIZE);
	m_pPolygon[BACK]->SetTexture(m_apTexture[BACK]);
	// 再開のやつ
	m_pPolygon[RESUME] = CPolygon::Create(RESUME_POS, STRING_SIZE);
	m_pPolygon[RESUME]->SetTexture(m_apTexture[RESUME]);
	// リスタートのやつ
	m_pPolygon[RESTART] = CPolygon::Create(RESTART_POS, STRING_SIZE);
	m_pPolygon[RESTART]->SetTexture(m_apTexture[RESTART]);
	// EXITのやつ
	m_pPolygon[EXIT] = CPolygon::Create(EXIT_POS, STRING_SIZE);
	m_pPolygon[EXIT]->SetTexture(m_apTexture[EXIT]);
	

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CPause::Uninit(void)
{
	for (int nCntTex = 0; nCntTex < PARTS_MAX; nCntTex++)
	{
		if (m_pPolygon[nCntTex] != NULL)
		{
			//終了処理
			m_pPolygon[nCntTex]->Uninit();
			// メモリの解放
			delete m_pPolygon[nCntTex];
			m_pPolygon[nCntTex] = NULL;
		}
	}
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CPause::Update(void)
{
	// 選んでるメニューで色分け
	for (int nCntMenu = RESUME; nCntMenu < PARTS_MAX; nCntMenu++)
	{
		if (m_nMenu == nCntMenu)
		{// 選んでるとき
			m_pPolygon[nCntMenu]->SetColor(MENU_ENTER_COL);
		}
		else
		{// 選んでないとき
			m_pPolygon[nCntMenu]->SetColor(MENU_NOT_ENTER_COL);
		}
	}
	DIJOYSTATE jy = CManager::GetJoypad()->GetStick(0);
	// メニュー操作
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_W) || CManager::GetKeyboard()->GetKeyTrigger(DIK_UP) || m_bMove && jy.lY <= -600)
	{// ↑
		m_nMenu--;
		m_bMove = false;
	}
	else if (CManager::GetKeyboard()->GetKeyTrigger(DIK_S) || CManager::GetKeyboard()->GetKeyTrigger(DIK_DOWN) || m_bMove && jy.lY >= 600)
	{// ↓
		m_nMenu++;
		m_bMove = false;
	}

	// スティック用フラグの初期化
	if (jy.lY <= 500 && jy.lY >= -500)
	{
		m_bMove = true;
	}

	// 範囲外に行かないように
	if (m_nMenu > EXIT)
	{
		m_nMenu = RESUME;
	}
	else if (m_nMenu < RESUME)
	{
		m_nMenu = EXIT;
	}

	// メニューコマンド
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetJoypad()->GetJoystickTrigger(3, 0))
	{
		switch (m_nMenu)
		{
		case RESUME:
			// 続ける
			CManager::SetActivePause(false);
			break;
		case RESTART:
			// リスタート
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
			break;
		case EXIT:
			// EXIT
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
			break;
		default:
			break;
		}
	}
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CPause::Draw(void)
{
	// すべてのパーツ分描画
	for (int nCntPolygon = 0; nCntPolygon < PARTS_MAX; nCntPolygon++)
	{
		if (m_pPolygon[nCntPolygon] != NULL)
		{
			m_pPolygon[nCntPolygon]->Draw();
		}
	}
}