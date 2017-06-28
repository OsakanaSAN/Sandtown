#pragma once
#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"
class shop :
	public IGameObject
{
public:
	shop();
	~shop();
	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void GetGoldTex(int GetGold);
	void GetGoldTex2(int GetGold);
	void Setpos(CVector3 a)
	{
		LightPos2 = a;
	}

	bool GetShop()
	{
		return Shopflg;
	}
	
private:

	CSoundSource*	m_sound_select;

	CLight              Maplight;
	CVector3            LightPos2;
	CVector3            Pointpos;
	enum WeaponState
	{
		Weapon,
		Weapon1,
		Weapon2,
	};
	WeaponState weaponState = Weapon;

	CSprite		m_ComandBGSprite1;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture1;		//!<戦闘画面の選択のテクスチャ。

	CSprite		m_ComandBGSprite2;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture2;		//!<戦闘画面の選択のテクスチャ。


	CSprite		m_ComandBGSprite3;		//!<戦闘画面の選択のスプライト。
	CTexture	m_ComandBGTexture3;		//!<戦闘画面の選択のテクスチャ。
	
	CSprite		m_CasolBGSprite;		//!<戦闘画面の選択のスプライト。
	CTexture	m_CasolBGTexture;		//!<戦闘画面の選択のテクスチャ。

	CSprite     m_GoldSeatSprite[3];
	CTexture    m_GoldSeatTexture[3];
	CVector2    m_Goldseatpos = { -300,300 };
	char        m_GoldTexName[255];

	CSprite     m_GoldSeatSprite2[3];
	CTexture    m_GoldSeatTexture2[3];
	CVector2    m_Goldseatpos2 = { -300,180};
	char        m_GoldTexName2[255];

	CSprite     m_GoldSeatSprite3[2];
	CTexture    m_GoldSeatTexture3[2];
	CVector2    m_Goldseatpos3 = { -30,280 };
	char        m_GoldTexName3[255];

	CSkinModel				skinModel;		//スキンモデル。
	CSkinModelDataHandle	skinModelData;	//スキンモデルデータ。
	CMeshCollider			meshCollider;	//メッシュコライダー。
	CRigidBody				rigidBody;		//剛体。
	int nedan1 = 100;
	int nedan2 = 300;

	bool Shopflg = false;
};

extern shop* g_shop;
