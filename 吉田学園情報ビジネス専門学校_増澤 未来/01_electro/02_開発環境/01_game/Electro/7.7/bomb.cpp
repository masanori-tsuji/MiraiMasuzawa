////////////////////////////////////////////////////
//
//    bombクラスの処理[bomb.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "bomb.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "sound.h"
#include "score.h"
#include "game.h"
#include "boss.h"
#include "particle.h"
#include "bullet.h"
#include "score.h"

//*****************************
// マクロ定義
//*****************************
#define BOMB_TEXTURE_PATH "./data/Textures/bomb000.png" //テクスチャのパス
#define BOMB_RATE_SIZE 0.1f // ボムのサイズ加算時の係数

//******************************
// 静的メンバ変数宣言
//******************************
LPDIRECT3DTEXTURE9 CBomb::m_pTexture = NULL; // テクスチャポインタ

//******************************
// コンストラクタ
//******************************
CBomb::CBomb():CScene(OBJTYPE_BOMB)
{
	// 変数のクリア
	m_bHitBoss = false;
	m_fMaxsize = 0.0f;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//******************************
// デストラクタ
//******************************
CBomb::~CBomb()
{
}

//******************************
// クリエイト
//******************************
CBomb * CBomb::Create(const D3DXVECTOR3 pos, const float fMaxsize)
{
	// メモリの確保
	CBomb *pBomb;
	pBomb = new CBomb;
	// 初期化
	pBomb->Init();

	// 各値の代入・セット
	pBomb->m_pos = pos;             // 座標
	pBomb->m_fMaxsize = fMaxsize;   // 最大サイズ

	// SEの再生
	CManager::GetSound()->Play(CSound::LABEL_SE_BOMB);

	return pBomb;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CBomb::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BOMB_TEXTURE_PATH, &m_pTexture);


	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CBomb::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CBomb::Init(void)
{
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f); // サイズ
	SetObjType(OBJTYPE_BOMB);               // オブジェクトタイプ

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CBomb::Uninit(void)
{
	Release();
}

//******************************
// 更新処理
//******************************
void CBomb::Update(void)
{

	m_size.x += ((m_fMaxsize + 3.0f) - m_size.x)*BOMB_RATE_SIZE;
	m_size.y += ((m_fMaxsize + 3.0f) - m_size.y)*BOMB_RATE_SIZE;

	// 当たり判定

	// エネミーリストの取得
	std::list<CEnemy*>::iterator enemyIteretor;
	for (enemyIteretor = CEnemy::GetEnemylist()->begin(); enemyIteretor != CEnemy::GetEnemylist()->end(); enemyIteretor++)
	{

		D3DXVECTOR3 size = m_size/2;  // ボムのサイズ

		D3DXVECTOR3 enemyPos = (*enemyIteretor)->GetPos();   // 敵の座標
		D3DXVECTOR3 enemySize = (*enemyIteretor)->GetSize(); // 敵のサイズ

		if (m_pos.x - size.x <= enemyPos.x + enemySize.x &&
			m_pos.x + size.x >= enemyPos.x - enemySize.x &&
			m_pos.y - size.y <= enemyPos.y + enemySize.y &&
			m_pos.y + size.y >= enemyPos.y - enemySize.y)
		{
			// エネミー爆発SE
			CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION);

			// エネミーを消す
			(*enemyIteretor)->HitAttack(5);
			// スコア加算
			CScore::AddScore(50);
			break;

		}
	}

	// バレットリストの取得
	std::list<CBullet*>::iterator bulletIteretor;
	for (bulletIteretor = CBullet::GetBulletlist()->begin(); bulletIteretor != CBullet::GetBulletlist()->end(); )
	{
		if ((*bulletIteretor)->GetUser() == CBullet::BULLETUSER_ENEMY)
		{
			D3DXVECTOR3 size = m_size / 2;  // ボムのサイズ

			D3DXVECTOR3 bulletPos = (*bulletIteretor)->GetPos();   // 弾の座標
			D3DXVECTOR3 bulletSize = (*bulletIteretor)->GetSize(); // 弾のサイズ

			if (m_pos.x - size.x <= bulletPos.x + bulletSize.x &&
				m_pos.x + size.x >= bulletPos.x - bulletSize.x &&
				m_pos.y - size.y <= bulletPos.y + bulletSize.y &&
				m_pos.y + size.y >= bulletPos.y - bulletSize.y)
			{				
				CBullet*pBullet = *bulletIteretor;
				bulletIteretor = CBullet::GetBulletlist()->erase(bulletIteretor);
				//	弾を消す
				pBullet->Uninit();

				// スコア加算
				CScore::AddScore(10);
			}
			else
			{
				bulletIteretor++;
			}
		}
		else
		{
			bulletIteretor++;
		}
	}

	if (CBoss::IsAlive())
	{
		if (!m_bHitBoss)
		{
			// ボスへの当たり判定
			D3DXVECTOR3 size = m_size / 2;  // ボムのサイズ

			D3DXVECTOR3 bossPos = CGame::GetBoss()->GetPos();   // ボスの座標
			D3DXVECTOR3 bossSize = CGame::GetBoss()->GetSize(); // ボスのサイズ

			if (m_pos.x - size.x/2 <= bossPos.x + bossSize.x / 2 &&
				m_pos.x + size.x/2 >= bossPos.x - bossSize.x / 2 &&
				m_pos.y - size.y/2 <= bossPos.y + bossSize.y / 2 &&
				m_pos.y + size.y/2 >= bossPos.y - bossSize.y / 2)
			{
				// エネミー爆発SE
				CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION);

				// エネミーを消す
				CGame::GetBoss()->HitAttack(5);
				// スコア加算
				CScore::AddScore(50);
				m_bHitBoss = true;
			}
		}
	}
	int nRnd = rand() % 10 + 5;
	for (int nCntparticle = 0; nCntparticle < nRnd; nCntparticle++)
	{
		// ランダムな距離
		float fRandDistance = (float)(rand() % 500 - 250) / 100;
		// ランダムな角度
		int nRandAngle = rand() % 360;
		
		// ランダムな座標
		D3DXVECTOR3 randPos;
		randPos.x = m_pos.x + cosf(D3DXToRadian(nRandAngle))*(m_size.x/2 + fRandDistance);
		randPos.y = m_pos.y + sinf(D3DXToRadian(nRandAngle))*(m_size.y/2 + fRandDistance);
		randPos.z = 0.0f;
	
		if (m_fMaxsize >= 500)
		{// アイテムのボム

			// ランダムなサイズ
			int nRandSize = rand() % 30 + 20;
			// パーティクルの生成
			CParticle::Create(randPos, 
				D3DXVECTOR3((float)(rand() % 3 - 1),
				(float)(rand() % 3 - 1), 0.0f), 
				D3DXVECTOR3((float)nRandSize, (float)nRandSize, 0.0f),
				rand() % 10 + 10,
				D3DXCOLOR((float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f, 1.0f));
		}
		else
		{// マナサークルのボム

			// ランダムなサイズ
			int nRandSize = rand() % 20 + 15;
			// パーティクルの生成
			CParticle::Create(randPos,
				D3DXVECTOR3((float)(rand() % 3 - 1),
				(float)(rand() % 3 - 1), 0.0f),
				D3DXVECTOR3((float)nRandSize, (float)nRandSize, 0.0f),
				rand() % 10 + 10,
				D3DXCOLOR((float)(rand() % 100) / 100.0f, (float)(rand() % 100) / 100.0f, 1.0f, 1.0f));
		}
	}
	
	// 最大サイズに到達したら消す
	if (m_size.x > m_fMaxsize)
	{
		Uninit();
		return;
	}
}

//******************************
// 描画処理
//******************************
void CBomb::Draw(void)
{
}

