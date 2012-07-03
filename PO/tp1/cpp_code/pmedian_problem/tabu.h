/* 
 * File:   tabu.h
 * Author: Grupo 7
 *
 * Created on 28 de Junho de 2012, 16:08
 */

#ifndef TABU_H
#define TABU_H
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <iostream>

class tabu
{
public:
    tabu(double** matrix, int n, int medians, int maxIter, int swapModifier, int maxTabu, int maxDepth);
    void printSolucaoEncontrada();
    void printNodosSol(int n);
   
     
protected:

private:  
    void greedy();
    int max(int i, int j);
    int min(int i, int j);
    void DROP();
    void ADD();
    bool SWAP(int i, int j);
    void checkTabu(int T);

      
    int p;
    double *AccPtoP;
    int N;
    double **mat;
    bool *sol;
    bool *solMelhor;
    bool *setTabu;

    long double solValue;
    long double solValueMelhor;
    long double *solAcc;

};

#endif // TABU_H
