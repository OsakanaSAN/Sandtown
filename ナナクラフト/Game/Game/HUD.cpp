#include "stdafx.h"
#include "HUD.h"
#include "Player.h"
#include "Scene/BattleScene.h"
#include "Scene/GameScene.h"
#include "Fade.h"


HUD::HUD()
{
	

}


HUD::~HUD()
{
}

bool HUD::Start()
{


	return true;
}

void HUD::Update()
{
	LVUp();
	
}
void HUD::Render(CRenderContext& renderContext)
{
}


//�_���[�W�̔���
void HUD::Damage(int damage)
{
	MaxpHP -= damage;

}
void HUD::LVUp()
{
	if (pExp >= NextExp)
	{
		LV++;
		NextExp = NextExp * 2;
	}

}
