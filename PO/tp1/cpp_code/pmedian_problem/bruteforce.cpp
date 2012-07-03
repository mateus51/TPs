/* 
 * File:   bruteforce.cpp
 * Author: Vitor
 * 
 * Created on July 1, 2012, 9:10 PM
 */

#include "bruteforce.h"
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <iostream>
#define INF 10000000000.00

bruteforce::bruteforce(double** matrix, int n, int medians){
    
    mat = matrix;
    N = n;
    p = medians;
    solValueMelhor = INF;
    solMelhor = new bool[n];
    for(int i = 0; i<n; i++)
        solMelhor[i] = false;
    //recursive bruteforce
    int c[1000];
    for(int i = 0; i < 1000; i++)
        c[i] = 0;
    
    this->brute(0, false, 0, c);
    this->brute(0, true, 0, c);
    
}

void bruteforce::brute(int number, bool isIn, int iter, int c[1000]){
    int g = number + 1;
    std::cout <<g << std::endl;
    if(number == p){
        
        //atualização da resposta
        long double acc;
        for(int i = 0; i < N; i++)
                AccPtoP[i] = INF;
        acc = 0;
        for(int i = 0; i<N; i++)
            if(c[i] == 1)
                for(int j = 0; j<N; j++)
                    if (mat[i][j] < AccPtoP[j])
                        AccPtoP[j] = mat[i][j];

        for(int i = 0; i<N; i++){
            acc += AccPtoP[i];
            if(acc > INF)
                acc = INF;
        }
        if(acc < solValueMelhor){
            solValueMelhor = acc;
            for(int i = 0; i<N; i++){
                if(c[i] == 1)
                        solMelhor[i] = true;
                else solMelhor[i] = false;
            }
        }
    }
    else if(isIn == true){
        c[iter] = 1;
        this->brute(g, false, (iter+1), c);
        this->brute(g, true, (iter+1), c);
    }
    else if(isIn == false){
        this->brute(number, false, (iter+1), c);
        this->brute(number, true, (iter+1), c);
    }
}
void bruteforce::printSolucaoEncontrada(){
    std::cout << solValueMelhor << std::endl;
}
void bruteforce::printNodosSol(int n){
    for(int i = 0; i<n; i++)
        if(solMelhor[i] == true)
            std::cout << i+1 << std::endl;
}