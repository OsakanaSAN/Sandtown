#pragma once
class BattleMenu : public IGameObject
{
public:
	BattleMenu();
	~BattleMenu();
	bool Start()override;
	void Update();
	void Render(CRenderContext& renderContext);
	//�v���C���[�o�g���p��HP�\�����v�Z
	void MaxPlayerHp();
	void PlayerHp();

	void SetHp(int sethp)
	{
		HP = sethp;
		PlayerHp();
	}

	//�G�l�~�[�o�g���p��HP�\�����v�Z
	void MaxEnemyHp();
	void EnemyHp();

private:

	////////////////////////////////////////////
	
	CSprite    PlayerIconSprite;
	CTexture   PlayerIconTex;


	//���݂�HP
	CSprite     HpSeatSprite[4];
	CTexture    HpSeatTexture[4];
	CVector2    Hpseatpos = { 600.0f,-450.0f };
	int         HP = 100;
	char        HpTexName[255];

	//�ő�HP
	CSprite     MaxHpSeatSprite[4];
	CTexture    MaxHpSeatTexture[4];
	CVector2    MaxHpseatpos = { 700.0f,-450.0f };

	//���݂̃G�l�~�[HP
	CSprite     EnemyHpSeatSprite[4];
	CTexture    EnemyHpSeatTexture[4];
	CVector2    EnemyHpseatpos = { 600.0f,450.0f };
	int         EnemyHP = 100;
	char        EnemyHpTexName[255];

	//�ő�G�l�~�[HP
	CSprite     EnemyMaxHpSeatSprite[4];
	CTexture    EnemyMaxHpSeatTexture[4];
	CVector2    EnemyMaxHpseatpos = { 700.0f,450.0f };

	//�o�b�N�V�[�g
	CSprite    BakeTexSprite;
	CTexture   BakeTexTexture;
	CVector2   Bakepos = { 600.0f,-450.0f };

	//�o�b�N�V�[�g
	CSprite    EnemyBakeTexSprite;
	CTexture   EnemyBakeTexTexture;
	CVector2   EnemyBakepos = { 600.0f,450.0f };

	////////////////////////////////////////////
	

};

