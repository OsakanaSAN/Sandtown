#include "stdafx.h"
#include "EnemyHUD.h"


EnemyHUD::EnemyHUD()
{
}


EnemyHUD::~EnemyHUD()
{
}

bool EnemyHUD::Start() {
	HudtextureHP.Load("Assets/UI/HP1.png");
	HudspriteHP.SetPosition({ 300.0f,530 });
	HudspriteHP.SetPivot({ 0.0f,1.0f });
	HudspriteHP.Init(&HudtextureHP);
	HudspriteHP.SetSize({ HP,20.0f });

	return true;
}

void EnemyHUD::Update()
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

void EnemyHUD::Render(CRenderContext& renderContext)
{

	HudspriteHP.Draw(renderContext);
}

void EnemyHUD::ReeseTex()
{
	
	HudtextureHP.Release();
}