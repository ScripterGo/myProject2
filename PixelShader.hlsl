

struct VS_OUTPUT {
	float4 pos : SV_Position;
	float3 color : Color;
};

float4 main(VS_OUTPUT input) : SV_Target {
	return float4(input.color.r, input.color.g, input.color.b, 1.0f);
}