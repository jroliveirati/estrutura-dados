#include <stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>

#define REPEAT 100.0

int power2(int n){
    int i, res = 1;
	
    if(n == 0)
        return 1;

    for(i = 0; i < n; i++)
        res *= 2;
    
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
