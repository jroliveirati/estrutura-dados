#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>

#define REPEAT 100.0

void insertionSort(int *v,int n){
	int i,k,j;

    for(i = 1; i < n; i++)
    {
        k = v[i];
        j = i - 1;

        while(j >= 0 && k < v[j]){
            v[j + 1] = v[j];
            j--;    
        }
        
        v[j + 1] = k;
    } 
}

int *vetor (unsigned int n){
    int i;
    int *v;

    v = (int*)malloc(n*sizeof(int));

    for(i = 0; i < n; i++)
        v[i] = rand() % n+1;
    
    return v;
}

int main(){
	int n,i;
	int *v;
	double t;
	struct timeval a,b;

	for(n = 1000; n <= 10000; n += 1000)
    {
		t = 0;
		for(i = 0; i < REPEAT; i++)
		{
            v = vetor(n);
			gettimeofday(&b,NULL);

			insertionSort(v,n);

			gettimeofday(&a,NULL);
			t = t + ((a.tv_sec * 1000000.0 + a.tv_usec) - (b.tv_sec * 1000000.0 + b.tv_usec));
		}
		printf("%d %f\n", n, t / REPEAT);
		free(v);
	}

	return 0;
}
