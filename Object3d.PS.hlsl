struct Material{
    float32_t4 color;
};

ConstantBuffer<Material> gMaterial : register(b0);

struct PixelSheaderOutput{
    float32_t4 color : SV_TARGET0;
};

PixelSheaderOutput main(){
    PixelSheaderOutput output;
    output.color = gMaterial.color;
    return output;
}