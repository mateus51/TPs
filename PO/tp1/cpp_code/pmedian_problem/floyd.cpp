/* 
 * File:   floyd.cpp
 * Author: Grupo 7
 * 
 * Created on 28 de Junho de 2012, 16:08
 * 
 * Implementação básica do algoritmo de Floyd para distâncias mínimas
 */
#include "floyd.h"
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <iostream>

floyd::floyd(double ** a, int n, bool blank)
{
        FILE *fp = fopen("floyds.txt","w"); /* imprime as matrizes em um arquivo*/

        /*a = ( int**)malloc(n*sizeof( int*));
        for(int i = 0; i<n; i++)
            a[i] = ( int*)malloc(n*sizeof( int));*/

        AdjacencyMatrix(a,n);


        fprintf(fp,"\t\tAdjacency a of the graph\n"); /* PRINT ADJACENCY a */
        for(int i = 0;i < n; i++){
            for(int j = 0;j < n; j++)
                fprintf(fp,"\t%.2f",a[i][j]);
            fprintf(fp,"\n");
        }


        floyds(a,n);

        fprintf(fp,"\n Shortest distance a\n"); /*PRINT SHORTEST DISTANCE a*/
        for(int i = 0;i < n; i++){
            for(int j = 0;j < n; j++)
                fprintf(fp,"\t%.2f",a[i][j]);
            fprintf(fp,"\n");
        }

        fprintf(fp,"}\n\n");

        fclose(fp);


}

floyd::floyd(double **a,int n)
{
        FILE *fp = fopen("floyds.txt","w"); /* imprime as matrizes em um arquivo*/

        fprintf(fp,"\t\tAdjacency Matrix of the graph\n"); /* PRINT ADJACENCY matrix */
        for(int i = 0;i < n; i++){
            for(int j = 0;j < n; j++)
                fprintf(fp,"\t%.2f",a[i][j]);
            fprintf(fp,"\n");
        }

        floyds(a,n);

        fprintf(fp,"\n Shortest distance Matrix\n"); /*PRINT SHORTEST DISTANCE matrix*/
        for(int i = 0;i < n; i++){
            for(int j = 0;j < n; j++)
                fprintf(fp,"\t%.2f",a[i][j]);
            fprintf(fp,"\n");
        }

        fprintf(fp,"}\n\n");

        fclose(fp);
}

double floyd::min( double x,  double y)
{
    if(x < y)
    return x;
    else
    return y;
}

void floyd::floyds( double **a,int n)
{
    int i,j,k;
    for(k = 0;k < n ; k++)
        for(i = 0;i < n; i++)
            for(j = 0;j < n ; j++)
                a[i][j] = min (a[i][j], a[i][k] + a[k][j]);
}

void floyd::AdjacencyMatrix( double **a,int n){ //To generate adjacency matrix for given nodes
   for(int i = 0;i < n; i++)
        for(int j = 0;j <= n; j++)
            a[i][j] = 0.00;
    srand ( time(NULL) );
    for(int i = 1; i < n; i++)
        for(int j = 0; j < i; j++){
            a[i][j] = (double)(rand()%10000 + 1)/100;
            a[j][i] = a[i][j];}
}

