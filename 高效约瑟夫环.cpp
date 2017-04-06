//
//  main.cpp
//  test
//
//  Created by 黄鸣宇 on 2017/2/7.
//  Copyright © 2017年 黄鸣宇. All rights reserved.
//
#include <iostream>
#include <memory.h>
#include <math.h>
#include <algorithm>
using namespace std;
int main(void)
{
    long long  n, k, i, x = 1, y;
    scanf( "%lld%lld", &n, &k );
    for( i = 2; i <= k && i <= n; ++i ){
        x = ( x + k ) % i;
        if (x==0) {
            x=i;
        }
    }
    for( i=i-1; i < n; ) {
        y=(i-x)/k;
        if (y+i>n) {
            y=n-i;
        }
        x=k*y+x;
        i+=y;
        if (!y) {
            i++;
            x = ( x + k ) % i;
            if (x==0) {
                x=i;
            }
        }
    }
    printf( "%lld\n", x );
    return 0;
}
