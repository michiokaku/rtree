#include "dataStruct.h"

__host__ __device__ void printBox(box b)
{
	std::cout <<"xMax:" <<b.xMax << "; yMax:" << b.yMax << "; zMax:" << b.zMax << "; xMin:" << b.xMin << "; yMin:" << b.yMin << "; zMin:" << b.zMin << "\n";
}


void debugBox(int length, box *b, int start, int end)
{
	box *bhost = (box*)malloc(length * sizeof(box));
	cudaMemcpy(bhost, b, length * sizeof(box), cudaMemcpyDeviceToHost);
	for (int i = start;i < end;i++)
	{
		printBox(bhost[i]);
	}
	free(bhost);
}

float time_elapsed = 0;
cudaEvent_t start, stop;
bool eventInit = false;

void cudaEventInit()
{
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaEventRecord(start, 0);
}

void spendTime()
{

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(start);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&time_elapsed, start, stop);
	std::cout << "spend time = " << time_elapsed << "ms \n";

	cudaEventDestroy(start);
	cudaEventDestroy(stop);

}