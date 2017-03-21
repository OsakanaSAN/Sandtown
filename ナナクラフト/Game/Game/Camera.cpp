#include "stdafx.h"
#include "Camera.h"

extern Player* g_player;


Camera::Camera()
{

	tag = g_player->Getpos();
}


Camera::~Camera()
{
}
bool Camera::Start()
{
	
	camera.SetPosition(pos); //�v���C���[�̐^���ւ�
	camera.SetTarget(tag);   //�v���C���[�̍��W

	return true;

}

void Camera::Update()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		pos.z += 0.3f;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		pos.z -= 0.3f;
	}

	camera.SetPosition(pos);

	camera.Update();

}
