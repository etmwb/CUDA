__global__ 
void blurKernel(unsigned char* Pout, unsigned char* Pin, 
                int width, int height)
{
    int Col = threadIdx.x + blockIdx.x * blockDim.x; 
    int Row = threadIdx.y + blockIdx.y * blockDim.y; 
    if (Col < width && Row < height)
    {
        int pixVal = 0;
        int pixels = 0;
        for(int blurRow=-BLUR_SIZE; blurRow <= BLUR_SIZE; blurRow++) 
            for(int blurCol=-BLUR_SIZE; blurCol <= BLUR_SIZE; blurCol++) 
        {
            {
                int curRow = Row + blurRow; 
                int curCol = Col + blurCol; 
                if(curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                {
                    pixVal += Pin[curRow*width + curCol]; 
                    pixels += 1 
                }
            }
        }
        Pout[Row*width + Col] = (unsigned char)(pixVal / pixels);
    }
}
