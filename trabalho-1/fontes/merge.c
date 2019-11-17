#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>

#define REPEAT 100.0

void merge(int *v, int s, int m, int e){
    int i, *w, k, j, n = e-s+1;

    w = (int *)malloc(n * sizeof(int));

    i = s;
    j = m + 1;

    for(k = 0; k < n; k++){
        if(j > e || (i <= m && v[i] < v[j])){
            w[k] = v[i];
            i++;
        }else{
            w[k] = v[j];
            j++;
        }
    }

    for(k = 0; k < n; k++)
        v[s+k] = w[k];

    free(w);
}

void mergeSort(int *v, int s, int e){
    int m;    

	if(s < e){
        m = (s + e) / 2;
        mergeSort(v,s,m);
        mergeSort(v,m+1,e);
        merge(v,s,m,e);
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

			mergeSort(v,0,n-1);

			gettimeofday(&a,NULL);
			t = t + ((a.tv_sec * 1000000.0 + a.tv_usec) - (b.tv_sec * 1000000.0 + b.tv_usec));
		}
		printf("%d %f\n", n, t / REPEAT);
		free(v);
	}

	return 0;
}
