#pragma once

class HUD :public IGameObject
{
public:
	HUD();
	~HUD();
	bool Start()override;
	void Update();
	void Render(CRenderContext& renderContext);
	void ReeseTex();
	void SetTex();
	void Damage(int Attak)
	{
		HP -= Attak;

	}

private:

	enum HpColor
	{
		Green,
		Read,
	};

	CSprite       Hudsprite;
	CTexture      Hudtexture;
	CVector2      Hudpos = { -960,-560 };

	CSprite       Hudsprite1;
	CTexture      Hudtexture1;

	CSprite       HudspriteNumber;
	CTexture      HudtextureNumber;

	CSprite       HudspriteHP;
	CTexture      HudtextureHP;

	int           iteme = 1;
	char           iName[256];
	float            HP = 500;
	HpColor          hpcolor = Green;

};

