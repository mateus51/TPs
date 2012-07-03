/* 
 * File:   main.cpp
 * Author: Grupo 7
 *
 * Created on 28 de Junho de 2012, 16:04
 */
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "tabu.h"
#include "floyd.h"
//#include "simple.h"

int main()
{
    clock_t t0, tf;
    double tempo_gasto;
    t0 = clock();
   
    
    std::cout << "Digite o nome do arquivo fonte" << std::endl;
    char filename[100];
    int n, p;
    scanf("%s", filename);
    std::cout << "Digite o numero de nodos" << std::endl;
    scanf("%d",&n);
    //n = 50;
    std::cout << "Digite o numero de medianas" << std::endl;
    scanf("%d",&p);
    //p = 5;
    
    //teste
    FILE *fp = fopen(filename,"r");
    double flo;
    //Alocação da matriz que decidi ser feita de fora de outras funções
    double ** a;
    a = ( double**)malloc(n*sizeof( double*));
    for(int i = 0; i<n; i++)
        a[i] = ( double*)malloc(n*sizeof( double));

    
    for(int i = 0; i<n;i++)
       for(int j = 0; j<n; j++){
           fscanf(fp, "%lf", &flo);
           a[i][j] = flo;
       }

    //Aplicação do algoritmo de floyd que vai calcular os caminhos mínimos
    //floyd f(a, n);
    
    //Inicialização das otimizações
    tabu t(a, n, p, 20, 3, ((int)ceil(0.25*p)), 5);
    
    //Função que imprime o valor da solução
    t.printSolucaoEncontrada();
    //função que imprime os nodos escolhidos como mediana na solução encontrada
    std::cout << "Nodos medianas:" << std::endl;
    t.printNodosSol(n);
        
    
    tf = clock();
    tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;
    printf("Tempo gasto: %lf s\n", tempo_gasto);
    std::cout << "Digite qualque coisa para sair" << std::endl;
    //esse cin ta ai só pro programa não fechar automaticamente no windows
    int x;
    std::cin >> x;
    return 0;
}    
