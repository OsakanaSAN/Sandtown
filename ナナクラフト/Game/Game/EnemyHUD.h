#pragma once
class EnemyHUD :public IGameObject
{
public:
	EnemyHUD();
	~EnemyHUD();
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



	CSprite       HudspriteHP;
	CTexture      HudtextureHP;

	int           iteme = 1;
	char           iName[256];
	float            HP = 500;
	HpColor          hpcolor = Green;

};

