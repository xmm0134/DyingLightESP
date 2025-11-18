
struct VSInput
{
    float3 position : POSITION;
    float3 color : COLOR0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float3 color : COLOR0;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput) 0;
    output.position = float4((input.position.x * 2.0f) / 1920 - 1, (input.position.y * 2.0f) / 1080 - 1, input.position.z, 1.0); // View Port transform
    output.color = input.color;
    return output;
}
