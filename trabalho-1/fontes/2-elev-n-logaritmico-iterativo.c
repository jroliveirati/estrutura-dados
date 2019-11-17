#include <stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>

#define REPEAT 100.0

int power2(int n){
	int res = 2, i = n, contador = 0;
    int *v, *w;
    v = (int *)malloc(n * sizeof(int));

    if(i < 2)
        return n + 1;

    while(i > 1){
        if(i % 2 == 0){
            i /= 2;
            v[contador] = 2;
            contador++;
        }else {
            i = (i-1) / 2;
            v[contador] = 1;
            contador++;
        }
    }

    w = (int *)malloc(contador * sizeof(int));  
    int aux = contador - 1;

    for(i = 0; i < contador; i++){
        w[aux] = v[i];
        aux--;
    }

    for(i = 0; i < contador; i++){
        if(w[i] == 2)
            res = res * res;
        else
            res = res * res * 2;
    }

	return res;
}

int main(){
	int n,i;
	double t;
	struct timeval a,b;

	for(n = 1; n <= 100000; n*=2){
        t = 0;
		for(i = 0; i < REPEAT;i++){
			gettimeofday(&b,NULL);
				
			power2(n);
			
			gettimeofday(&a,NULL);
			t = t + ((a.tv_sec * 1000000.0 + a.tv_usec) - (b.tv_sec * 1000000.0 + b.tv_usec));
		}
		printf("%d %f\n", n, t / REPEAT);
	}

	return 0;
}
