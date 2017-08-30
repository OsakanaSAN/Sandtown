#pragma once


/*!
 *@brief	タイトルシーン。
 */
class TitleScene :
	public IGameObject
{
public:
	
	
	TitleScene();
	
	~TitleScene();
	bool Start() override;
	
	/*!
	 *@brief	更新関数。
	 */
	void Update() override;
	/*!
	*@brief	遅延描画関数。
	@details
	* ポストエフェクトの後で実行されます。HUDなどポストエフェクトの影響を受けたくない描画物はここでレンダリングしてください。
	*@param[in]		renderContext		レンダリングコンテキスト。
	*/
	void PostRender( CRenderContext& renderContext ) override;
private:
	enum EState {
		eStateWaitFadeIn,	//!<フェードイン待ち。
		eStateRun,			//!<実行中。
		eStateWaitFadeOut,	//!<フェードアウト待ち。
	};

	enum Select {
		NO,
		START,
		BREAK,
	};
	Select GAME = START;

	CSoundSource* bgmSource = NULL;

	CSprite		m_titleBGSprite;		//!<タイトル画面の背景のスプライト。
	CTexture	m_titleBGTexture;		//!<タイトル画面の背景のテクスチャ。

	
	CSprite		m_titleBGSprite2;		//!<タイトル画面の背景のスプライト。
	CTexture	m_titleBGTexture2;		//!<タイトル画面の背景のテクスチャ。

	//START
	CSprite		m_titleBGSprite3;		//!<タイトル画面の背景のスプライト。
	CTexture	m_titleBGTexture3;		//!<タイトル画面の背景のテクスチャ。

	EState      m_state = eStateRun;

	CFont       font;
	char       text[256];

	CSoundSource* PushSE = NULL;
	int count = 0;

	
	

	
};

