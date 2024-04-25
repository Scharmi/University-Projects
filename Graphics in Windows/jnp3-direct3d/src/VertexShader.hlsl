cbuffer vs_const_buffer_t {
	float4x4 matWorldViewProj;
	float4x4 matWorldView;
	float4x4 matView;
	float4 colLight[4];
	float4 posLight[4];
	float4 padding;
};


struct vs_output_t {
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

vs_output_t main(
    float3 pos : POSITION, float4 col : COLOR, float2 tex : TEXCOORD, float3 normal : NORMAL
) {
	vs_output_t result;
	float4 NW = mul(float4(-normal, 0.0f), matWorldView);
	result.position = mul(float4(pos, 1.0f), matWorldViewProj);
	result.color = 0.5f * col;
	for(int i = 0; i < 4; i++) {
		FLOAT dist = length(posLight[i] - pos);
		float3 diff = posLight[i] - pos;
		diff = normalize(diff);
		float4 LW = mul(diff, matView);
		float4 add_col = mul(
 			max(-dot(normalize(LW), normalize(NW)), 0.0f), 
 			colLight[i] * 2.0f * col / (1.0f + 0.1f * dist));
		result.color += add_col;

	}
	result.tex = tex;
	return result;

}