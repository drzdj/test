#include <bits/stdc++.h>
using namespace std;
const int N = 233;
const int M = 1000;
char s1[1024], s2[1024];

int getR(int x){
    return double(rand()) / RAND_MAX * M;
}

void genRandomAlphaStr(int len){
    for(int f1, f2, i = 0; i < len; i ++){
        f1 = rand() % 2;
        f2 = rand() % 26;
        if(f1) s1[i] = 'a' + f2;
        else s1[i] = 'A' + f2; 
    }
    s1[len] = 0;
}

void gen(){
    int len = 0;
    for(int tlen, par = 0; par < 3; par ++){
        if(par > 0) s2[len] = '.', len ++;
        tlen = rand() % 7 + 1;
        genRandomAlphaStr(tlen);
        strcpy(s2 + len, s1);
        len += tlen;
    }
    s2[len] = 0;
    return;
}

int main(){
    srand(time(NULL));
    FILE * fp;
    fp = fopen("testcase.in", "w");
    for(int tim, i = 0; i < N; i ++){
        gen();
        tim = getR(M);
        for(int j = 0; j < tim; j ++)
            fprintf(fp, "%s ", s2);
    }
    return 0;
}