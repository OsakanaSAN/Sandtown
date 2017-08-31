 /*!
 * @brief	フィードバックブラー
 */


struct VS_INPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};
float4x4 mRot;			//回転行列。
float2 g_sceneTexSize;	//シーンテクスチャのサイズ。
float g_combineRate;	//合成率。

//現在のシーンのテクスチャ。
texture g_scene;
sampler SceneSampler = sampler_state
{
	Texture = <g_scene>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
    AddressV = CLAMP;
};

texture g_lastScene;
sampler LastSceneSampler = sampler_state
{
	Texture = <g_lastScene>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
    AddressV = CLAMP;
};


float g_blendRate;		//ブレンド率。
/*!
 *@brief	頂点シェーダー。
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = mul(In.pos, mRot);
	Out.uv = In.uv + float2( 0.5/g_sceneTexSize.x, 0.5/g_sceneTexSize.y);
	return Out;
}


/*!
 *@brief	ピクセルシェーダー。
 */
float4 PSMain( VS_OUTPUT In ) : COLOR0
{
	return tex2D(SceneSampler, In.uv);	
}

/*!
 *@brief	合成用の頂点シェーダー。
 */
VS_OUTPUT VSCombineMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = In.pos;
	Out.uv = In.uv + float2( 0.5/g_sceneTexSize.x, 0.5/g_sceneTexSize.y);
	return Out;
}
struct PSOutput
{
	float4	color	: COLOR0;
	float4	color2	: COLOR1;
};

/*!
 *@brief	合成用のピクセルシェーダー。
 */
PSOutput PSCombineMain( VS_OUTPUT In )
{
	float4 color = tex2D(SceneSampler, In.uv) * g_combineRate + tex2D(LastSceneSampler, In.uv) * (1.0f- g_combineRate);

	PSOutput psOut;
	psOut.color = color;
	psOut.color2 = color;
	return psOut;	
}


technique Default
{
	pass p0
	{
		VertexShader	= compile vs_3_0 VSMain();
		PixelShader		= compile ps_3_0 PSMain();
	}
}
technique Combine
{
	pass p0
	{
		VertexShader	= compile vs_3_0 VSCombineMain();
		PixelShader		= compile ps_3_0 PSCombineMain();
	}
}

