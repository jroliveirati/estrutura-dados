#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>

#define REPEAT 100.0

int partition(int* v, int s, int e){
    int aux,k;    
    int i = s-1;

    for (k = s; k <= e-1; k++){
        if (v[k] < v[e]){
            i = i+1;
            aux = v[i];
            v[i] = v[k];
            v[k] = aux;
        }
    }

    aux = v[e];
    v[e] = v[i+1];
    v[i+1] = aux;

    return i+1;
}

void quickSort(int* v,int s,int e){
    int p;

    if (s < e) {
        p = partition (v, s, e);
        quickSort(v,s,p-1);
        quickSort(v,p+1,e);
    }
}

int *vetor (unsigned int n){
    int i;
    int *v;

    v = (int*)malloc(n*sizeof(int));

    for(i = 0; i < n; i++)
        v[i] = i;
    
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

			quickSort(v,0,n-1);

			gettimeofday(&a,NULL);
			t = t + (a.tv_sec * 1000000.0 + a.tv_usec) - (b.tv_sec * 1000000.0 + b.tv_usec);
		}
		printf("%d %f\n", n, t / REPEAT);
		free(v);
	}

	return 0;
}
