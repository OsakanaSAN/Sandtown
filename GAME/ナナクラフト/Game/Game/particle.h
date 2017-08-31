#pragma once
#include "tkEngine/particle/tkParticleEmitter.h"
class particle :
	public IGameObject
{
public:
	particle();
	~particle();
	bool Start()override;
	void Update();
	void Render(CRenderContext&renderContext);
	void Particle(CVector3 target, int ParticleNumber);
	void ParticleDelete();

private:

	enum ParticleState {
		ATTACK,
		HEAL,
		STOP,
	};

	ParticleState currentParticle = ATTACK;

	CParticleEmitter		*m_particle;
	CRandom					 m_random;
};

extern particle* g_particle;

