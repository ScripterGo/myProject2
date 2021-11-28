
struct VS_INPUT {
	float2 pos : Position;
	float3 color : Color;
};

struct VS_OUTPUT {
	float4 pos : SV_POSITION;
	float3 color : Color;
};


VS_OUTPUT main(VS_INPUT input){
	VS_OUTPUT res;
	res.pos.x = input.pos.x;
	res.pos.y = input.pos.y;
	res.pos.z = 0.0f;
	res.pos.w = 1.0f;

	res.color = input.color;
	return res;
}