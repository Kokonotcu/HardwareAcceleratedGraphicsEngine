cbuffer CBuf
{
    float4 face_colors[12];
};

float4 main(uint tid : SV_PrimitiveID) : SV_Target
{
    return face_colors[tid/2];
}