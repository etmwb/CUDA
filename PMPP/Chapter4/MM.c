__global__
void MatrixMulKernel(float* d_M, float* d_N, float* d_P, int width)
{
    __shared__ float Mds[TILE_WIDTH][TILED_WIDTH];
    __shared__ float Nds[TILE_WIDTH][TILED_WIDTH];
    
    int bx = blockIdx.x; int by = blockIdx.y;
    int tx = threadIdx.x; int ty = threadIdx.y; 
    
    int Row = by * TILE_WIDTH + ty; 
    int Col = bx * TILE_WIDTH + tx; 
    
    float Pvalue = 0; 
    for(int ph = 0; ph < width/TILE_WIDTH; ph++) 
    {
        Mds[ty][tx] = d_M[Row*width + ph*TILE_WIDTH + tx];
        Nds[ty][tx] = d_N[(ph*TILE_WIDTH + ty)*width + Col];
        __syncthreads();
        
        for(int k = 0; k < TILE_WIDTH; k++) 
        {
            Pvalue += Mds[ty][k] * Nds[k][tx]; 
        }
        __syncthreads();
    }
    d_P[Row*width + Col] = Pvalue;
}
