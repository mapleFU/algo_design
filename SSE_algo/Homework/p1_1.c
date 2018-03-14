#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <math.h>

int gcd_Euclid(int m, int n) ;
int gcd_ConsecutInteger (int m, int n);
time_t count_time(int gcd_func(int m, int n), int m, int n, int* pvalue );


int main() {

    // int euclid = gcd_Euclid(31415, 14142);
    // int consecut = gcd_ConsecutInteger(31415, 14142);
    int euclid, consecut;
    time_t t1 = count_time(gcd_Euclid, 31415, 14142, &euclid);
    time_t t2 = count_time(gcd_ConsecutInteger, 31415, 14142, &consecut);
    printf("v1:%d, v2:%d\n", euclid, consecut);
    printf("E:%ld, C:%ld\n", (long)t1, (long)t2);
    
    return 0;
}

int gcd_Euclid(int m, int n) {
    while (1) {
        int tmp = m % n;
        if (tmp == 0) 
            return n;
        m = n;
        n = tmp;
    }
}

int gcd_ConsecutInteger (int m, int n) {
    int v = fmin(m , n);
    while(1) {
        if (m % v == 0 && n % v == 0)
            return v;
        --v;
    }
}

time_t count_time(int gcd_func(int m, int n),
                 int m, int n, int* pvalue ) {
    if (pvalue == NULL) {
        printf("Error!");
        return 0;
    }
    time_t t1 = clock();
    int value = gcd_func(m, n);
    time_t t2 = clock();
    *pvalue = value;
    return t2 - t1;
}
