//
//  main.cpp
//  test
//
//  Created by 黄鸣宇 on 2017/2/7.
//  Copyright © 2017年 黄鸣宇. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <memory.h>
#include <math.h>
#include <algorithm>
#include<vector>
using namespace std;
int a[100];
int main()
{
    for (int i=0; i<3; i++) {
        cin>>a[i];
    }
    do {
        for (int i=0; i<3; i++) {
            cout<<a[i];
        }
        cout<<endl;
    } while (next_permutation(a, a+3));
    return 0;
}
