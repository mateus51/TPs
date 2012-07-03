/* 
 * File:   bruteforce.h
 * Author: Vitor
 *
 * Created on July 1, 2012, 9:10 PM
 */

#ifndef BRUTEFORCE_H
#define	BRUTEFORCE_H

class bruteforce {
public:
    void printSolucaoEncontrada();
    void printNodosSol(int n);
    bruteforce(double** matrix, int n, int medians);
     
protected:

private:  

    void brute(int number, bool isIn, int iter, int c[1000]);
    

     
    int p;
    double *AccPtoP;
    int N;
    double **mat;
    bool *sol;
    bool *solMelhor;
    

    
    long double solValueMelhor;
    
};

#endif	/* BRUTEFORCE_H */

