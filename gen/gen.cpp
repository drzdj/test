#include <bits/stdc++.h>
using namespace std;
const int N = 1000;
const int M = 100000000;
char s1[1024], s2[1024];

int getR(int x){
    return double(rand()) / RAND_MAX * x;
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

vector<char*> vs;

void pushStr(char * s){
    char * ns = new char [strlen(s) + 1];
    strcpy(ns, s);
    vs.push_back(ns);
    return;
}

int main(){
    srand(time(NULL));
    FILE * fp;
    fp = fopen("testcase2.in", "w");
    for(int i = 1; i <= N; i ++){
        gen();
        pushStr(s2);
    }
    // for(auto p: vs)
    //     printf("%s\n", p);

    for(int i = 0; i < M; i ++)
        fprintf(fp, "%s ", vs[getR(N - 1)]);
    fclose(fp);
    return 0;
}