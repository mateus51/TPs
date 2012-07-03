/* 
 * File:   floyd.h
 * Author: Grupo 7
 *
 * Created on 28 de Junho de 2012, 16:08
 */

#ifndef FLOYD_H
#define FLOYD_H

class floyd
{
public:
    floyd(double ** a, int n, bool blank);
    floyd(double **a, int n);
private:
    void AdjacencyMatrix( double **a,int n);
    double min( double x, double y);
    void floyds( double **a,int n);

};

#endif // FLOYD_H
