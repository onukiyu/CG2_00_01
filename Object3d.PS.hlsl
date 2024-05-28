struct PixelSheaderOutput{
    float32_t4 color : SV_TARGET0;
};

PixelSheaderOutput main(){
    PixelSheaderOutput output;
    output.color = float32_t4(1.0, 1.0, 1.0, 1.0);
    return output;
}