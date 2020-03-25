__global__ 
void blurKernel(unsigned char* Pout, unsigned char* Pin, 
                int width, int height)
{
    int Col = threadIdx.x + blockIdx.x * blockDim.x; 
    int Row = threadIdx.y + blockIdx.y * blockDim.y; 
    if (Col < width && Row < height)
    {
        int greyOffset = Row * width + Col;
        int rgbOffset = greyOffset * CHANNELS;
        unsigned char r = Pin[rgbOffset    ]; 
        unsigned char g = Pin[rgbOffset + 1]; 
        unsigned char b = Pin[rgbOffset + 2];
        Pout[greyOffset] = 0.21f*r + 0.71f*g + 0.07f*b;
    }
}
