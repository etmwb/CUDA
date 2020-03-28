int dev_count; 
cudaGetDeviceCount(&dev_count);
cudaDeviceProp dev_prop;
for(int i=0; i < dev_count; i++) 
{
    cudaGetDevicePropoties(&dev_prop, i);
}
