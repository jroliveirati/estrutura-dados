#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>

#define REPEAT 100.0

int min(int *v, int n){
    int vMin = v[0];

    for(int i = 1; i < n; i++)
        if(v[i] < vMin)
            vMin = v[i];

    return vMin;
}

int max(int *v, int n){
    int vMax = v[0];

    for(int i = 1; i < n; i++)
        if(v[i] > vMax)
            vMax = v[i];

    return vMax;
}

void distributionSort(int *v, int n){
    int s, b, j;
    int *f, *w;

	s = min(v, n);
	b = max(v, n);

	w = (int *) malloc(n * sizeof(int));
	f = (int *) malloc((b - s + 1) * sizeof(int));

	for(int k = 0; k <= (b - s); k++)
		f[k] = 0;

	for(int i = 0; i < n; i++)
		f[v[i] - s] = f[v[i] - s] + 1;

	for(int k = 1; k <= (b - s); k++)
		f[k] = f[k] + f[k - 1];

	for(int i = 0; i < n; i++){
		j = v[i] - s;
		w[f[j] - 1] = v[i];
		f[j] = f[j] - 1;
	}

	for(int i = 0; i < n; i++)
		v[i] = w[i];
}

int *vetor (unsigned int n){
    int i,contador = n - 1;
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

			distributionSort(v,n);

			gettimeofday(&a,NULL);
			t = t + (a.tv_sec * 1000000.0 + a.tv_usec) - (b.tv_sec * 1000000.0 + b.tv_usec);
		}
		printf("%d %f\n", n, t / REPEAT);
		free(v);
	}

	return 0;
}
