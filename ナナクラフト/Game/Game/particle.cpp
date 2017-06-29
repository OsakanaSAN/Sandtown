#include "stdafx.h"
#include "particle.h"
#include "Camera.h"

particle::particle()
{
	m_random.Init((unsigned long)time(NULL));
}


particle::~particle()
{
}

bool particle::Start()
{
	return true;
}

void particle::Update()
{

}

void particle::Render(CRenderContext&renderContext)
{

}

void particle::Particle(CVector3 target, int ParticleNumber)
{
	if (m_particle != nullptr) { return; }
	switch (ParticleNumber)
	{
	case ATTACK://�U��


				//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);

		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/Particle/burn.png",						//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 0.0f, 0.0f },							//!<�����x�B
			0.3f,											//!<�����B�P�ʂ͕b�B
			0.5f,											//!<�������ԁB�P�ʂ͕b�B
			3.5f,											//!<�p�[�e�B�N���̕��B
			3.5f,											//!<�p�[�e�B�N���̍����B
			{ 0.0f, 0.0f,0.0f },							//!<�����ʒu�̃����_�����B
			{ 0.0f, 0.0f,0.0f },							//!<�����x�̃����_�����B
			{ 1.0f, 1.0f,1.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
			{
				{ 0.0f, 0.0f,0.25f, 0.25f },//0.25,0.5,0.75,1U��V�̈ʒu
				{ 0.0f, 0.0f, 0.0f, 0.0f }, //X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			1,												//!<UV�e�[�u���̃T�C�Y�B
			{ 0.0f, 0.0f, 0.0f },							//!<�d�́B
			true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
			0.3f,											//!<�t�F�[�h���鎞�ԁB
			2.0f,											//!<�����A���t�@�l�B
			true,											//!<�r���{�[�h�H
			3.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
			1,												//!<0�����������A1���Z�����B
			{ 1.0f, 1.0f, 1.0f },							//!<��Z�J���[�B
		},
			target);//�p�[�e�B�N���𐶐�������W�@CVector3�^�H
		break;
	case HEAL://��

		//�p�[�e�B�N���̐���
		m_particle = NewGO<CParticleEmitter>(0);
		m_particle->Init(m_random, g_gameCamera->GetCamera(),
		{
			"Assets/Particle/Heal.tga",		//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 1.4f, 0.0f },							//!<�����x�B
			0.5f,											//!<�����B�P�ʂ͕b�B
			0.1f,											//!<�������ԁB�P�ʂ͕b�B
			0.25f,											//!<�p�[�e�B�N���̕��B
			0.25f,											//!<�p�[�e�B�N���̍����B
			{ 0.2f, 0.2f, 0.2f },							//!<�����ʒu�̃����_�����B
			{ 0.0f, 2.0f, 0.0f },							//!<�����x�̃����_�����B
			{ 1.0f, 1.0f, 1.0f },							//!<���x�̐ϕ��̂Ƃ��̃����_�����B
			{
				{ 0.0f, 0.0f, 1.0f, 1.0f },//0.25,0.5,0.75,1U��V�̈ʒu
				{ 0.0f, 0.0f, 0.0f, 0.0f }, //X,Y,X,Y
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			1,												//!<UV�e�[�u���̃T�C�Y�B
			{ 0.0f, 0.0f, 0.0f },							//!<�d�́B
			true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
			0.3f,											//!<�t�F�[�h���鎞�ԁB
			2.0f,											//!<�����A���t�@�l�B
			true,											//!<�r���{�[�h�H
			3.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
			1,												//!<0�����������A1���Z�����B
			{ 1.0f, 1.0f, 1.0f },							//!<��Z�J���[�B
		},
			target);//�p�[�e�B�N���𐶐�������W�@CVector3�^�H
		break;

	}
}


void particle::ParticleDelete()
{
	//if (m_particle == nullptr) { return; }

	DeleteGO(m_particle);
	m_particle = nullptr;

}
