//=============================================================================
//
// bombヘッダ [bomb.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _BOMB_H_
#define _BOMB_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// クラス定義
//*****************************

// ボムクラス
class CBomb : public CScene
{
public:

	//メンバ関数
	CBomb();
	~CBomb();
	static CBomb *Create(const D3DXVECTOR3 pos, const float fMaxsize);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture; // テクスチャ
	int m_nCntAnim;     // アニメーションカウント
	int m_nAnimX;       // アニメーションX軸
	int m_nAnimY;       // アニメーションY軸
	bool m_bHitBoss;    // ボスに多段ヒットしないようにフラグ
	float m_fMaxsize;   // 最大サイズ
	D3DXVECTOR3 m_pos;  // ボムの座標
	D3DXVECTOR3 m_size; // ボムのサイズ
};

#endif