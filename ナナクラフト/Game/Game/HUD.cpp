#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
}


HUD::~HUD()
{
}

bool HUD::Start()
{

	Hudtexture.Load("Assets/UI/ui1.png");
	Hudsprite.SetPosition(Hudpos);
	Hudsprite.SetPivot({ 0.0f,0.0f });
	Hudsprite.Init(&Hudtexture);
	Hudsprite.SetSize({ 300.0f,300.0f });

	Hudtexture1.Load("Assets/UI/Lv.png");
	Hudsprite1.SetPosition({ -960.0f,-260.0f });
	Hudsprite1.SetPivot({ 0.0f,1.0f });
	Hudsprite1.Init(&Hudtexture1);
	Hudsprite1.SetSize({ 50.0f,80.0f });

	HudtextureNumber.Load("Assets/UI/0.png");
	HudspriteNumber.SetPosition({ -910.0f,-260.0f });
	HudspriteNumber.SetPivot({ 0.0f,1.0f });
	HudspriteNumber.Init(&HudtextureNumber);
	HudspriteNumber.SetSize({ 50.0f,80.0f });

	HudtextureHP.Load("Assets/UI/HP.png");
	HudspriteHP.SetPosition({ -960.0f,530 });
	HudspriteHP.SetPivot({ 0.0f,1.0f });
	HudspriteHP.Init(&HudtextureHP);
	HudspriteHP.SetSize({ HP,20.0f });

	return true;
}

void HUD::Update()
{
	if (GetAsyncKeyState('Y') && HP > 0)
	{
		HP -= 10;
	}
	if (GetAsyncKeyState('U') && HP < 500)
	{
		HP += 10;
	}
	if (HP < 100 && hpcolor == Green)
	{
		HudtextureHP.Load("Assets/UI/HP1.png");
		hpcolor = Read;
	}
	if (HP >= 100 && hpcolor == Read)
	{
		HudtextureHP.Load("Assets/UI/HP.png");
		hpcolor = Green;
	}


	HudspriteHP.SetSize({ HP,20.0f });
}
void HUD::Render(CRenderContext& renderContext)
{
	Hudsprite.Draw(renderContext);
	HudspriteNumber.Draw(renderContext);
	Hudsprite1.Draw(renderContext);
	HudspriteHP.Draw(renderContext);
}

void HUD::ReeseTex()
{
	Hudtexture.Release();
	Hudtexture1.Release();
	HudtextureHP.Release();
}

void HUD::SetTex()
{

	HudtextureNumber.Release();
	if (iteme < 10) {
		sprintf(iName,"Assets/UI/%d.png", iteme);
		HudtextureNumber.Load(iName);
		iteme++;
	}
	
}