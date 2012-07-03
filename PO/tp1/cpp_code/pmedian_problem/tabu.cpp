/* 
 * File:   tabu.cpp
 * Author: Grupo 7
 * 
 * Created on 28 de Junho de 2012, 16:08
 * 
 * Implementação da busca local TABU e busca global simples
 */

#include "tabu.h"
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <iostream>


#define INF 10000000000.00

//Funçoes auxiliares:
int tabu::max(int i, int j){
    if(i > j)
        return i;
    else return j;
}
int tabu::min(int i, int j){
    if(i < j)
        return i;
    else return j;
}
void tabu::printSolucaoEncontrada(){
    std::cout << solValueMelhor << std::endl;
}
void tabu::printNodosSol(int n){
    for(int i = 0; i<n; i++)
        if(solMelhor[i] == true)
            std::cout << i+1 << std::endl;
}
void tabu::checkTabu(int T){
    int c=0;
    for(int i = 0; i<N; i++)
        if(setTabu[i] == true)
            c++;

    if(c > T){
      for(int j = 0; j< (c-T); j++){
        srand ( time(NULL) );
        int i = -1;
        int s = (rand()%(c-j)) + 1;
        while (s > 0){
            i++;
            if(setTabu[i] == true)
                s--;
        }
        setTabu[i] = false;
        
      }
    }
}

void tabu::greedy(){
    //solução 1-mediana para o começo de tudo
    solAcc = new long double[N];
    for(int i = 0; i<N; i++)
        solAcc[i] = 0.00;
    
    for(int j = 0; j < N; j++)
        for(int i = 0; i < N; i++){
            solAcc[j] += mat[i][j];
            if(solAcc[j] > INF)
                solAcc[j] = INF;
        }
    solValue = solAcc[0];
    int aux = 0;
    for(int i = 1; i<N; i++)
        if(solAcc[i] < solValue){
            solValue = solAcc[i];
            aux = i;
        }
    
    sol[aux] = true;
    solValueMelhor = solValue;
    solMelhor[aux] = true;
    AccPtoP = new double[N];
    for(int i = 0; i<N; i++)
        AccPtoP[i] = mat[aux][i];
    
    for(int i = 1; i < p; i++){
        // reset no accumulador para soluçoes com um numero qualquer
        for(int i = 0; i< N; i++)
                solAcc[i] = 0.00;

        for(int i = 0; i<N; i++){
                if (setTabu[i]==false && sol[i] == false){
                        long double acc = 0;
                        for(int j = 0; j<N; j++)
                                if(mat[i][j] < AccPtoP[j]){
                                        acc += (mat[i][j]-AccPtoP[j]);
                                        if(acc > INF)
                                                acc = INF;
                                }

                        solAcc[i] = acc;
                }
         }
        // pega o menor solAcc;
        long double acc = solAcc[0];
        int aux = 0;
        for(int i = 1; i<N; i++)
                if(solAcc[i] <= acc && sol[i] == false && setTabu[i]==false){
                        acc = solAcc[i];
                        aux = i;
                }

        //quando ele acha o nodo com menor solAcc ele adiciona ao conjunto soluçao
        //e atualiza a solução atual e o accPtoP
        sol[aux] = true;
        solMelhor[aux] = true;
        acc = 0;
        for(int i = 0; i<N; i++){
                if (mat[aux][i] < AccPtoP[i])
                        AccPtoP[i] = mat[aux][i];
                acc += AccPtoP[i];
                if(acc > INF)
                        acc = INF;
        }
        solValue = acc;
        solValueMelhor = acc;   
    
   
    
    }
         
}

tabu::tabu(double** matrix, int n, int medians, int maxIter, int swapModifier, int maxTabu, int maxDepth) {
    mat = matrix;
    N = n;
    p = medians;
    sol = new bool[n];
    solMelhor = new bool[n];
    setTabu = new bool[n];
    for(int i = 0; i<n; i++){
        setTabu[i] = false;
        solMelhor[i] = false;
        sol[i] = false;
    }
    int swapCount = 1;
    int D = 0;
    int i = 0;
    
    //+++++++++++++++++++++++++++++++++++++++++++++++++++//
    
    //acha uma solução inicial:
    this->greedy();
    
    //busca tabu:
    
    if(p > 1 && p < N){
      while(i<maxIter){
          for(int j = 0; j<swapCount; j++)
              this->DROP();          
          for(int j = 0; j<swapCount; j++)
              this->ADD();
          this->checkTabu(maxTabu);
          if(solValue < solValueMelhor){
              solValueMelhor = solValue;
              for(int u = 0; u < N; u++)
                  solMelhor[u] = sol[u];
              i = 0;
              D = 0;
          }
          else{
              if(maxDepth == 0){
                  i++;
              }
              else{
                  D++;
                  if(D == maxDepth){
                      D = 0;
                      i++;
                      solValue = solValueMelhor;
                      for(int u = 0; u < N; u++)
                           sol[u] = solMelhor[u];
                  }
              }
                  
          }
          swapCount = this->max(1,this->min((i*swapModifier),(p-2)));
          
      }
      
      
      //busca por trocas possíveis que possam melhorar o sistema
      
      bool dontStop = true;
      while(dontStop == true){
        
        for(int i = 0; i < N; i++){
            if(solMelhor[i] == true){
                for(int j = 0; j < N; j++){
                    if(solMelhor[j] == false){
                        dontStop = this->SWAP(i,j);
                        if(dontStop == true)
                            break;
                    }
                }
            }
            else
                continue;
            if(dontStop == true)
                break;
        }
        
      }
    }
    std::cout <<"Achei uma resposta"<<std::endl;

}

void tabu::DROP(){
    newTABU:
    // reset no accumulador para soluçoes com um numero qualquer
    for(int u = 0; u< N; u++)
        solAcc[u] = INF;
    //avaliação do quanto é aumentada a solução se nodo permanecer e todos outros
    //fossem excluidos, resultados em solAcc
    for(int m = 0; m<N; m++){
        if (setTabu[m]==false && sol[m] == true){
            sol[m] = false;
            long double acc = 0;
            //atualização da resposta
            for(int i = 0; i < N; i++)
                AccPtoP[i] = INF;
            acc = 0;
            for(int i = 0; i<N; i++)
                if(sol[i] == true)
                    for(int j = 0; j<N; j++)
                        if (mat[i][j] < AccPtoP[j])
                              AccPtoP[j] = mat[i][j];

            for(int i = 0; i<N; i++){
                acc += AccPtoP[i];
            if(acc > INF)
                acc = INF;
            }
            solAcc[m] = acc;
            sol[m] = true;
          
        }
    }

    // pega o maior solAcc 
    //o maior solAcc indica o quão maior são as distâncias deste nó para os outros
    //comparado com as melhores distâncias da solução atual. Esta estratégia da
    //uma visão de confiabilidade no nodo, o menos confiavel deve sair.
    long double acc = INF;
    int aux = N;
    for(int i = 0; i<N; i++){
        if(solAcc[i] < acc && sol[i] == true && setTabu[i]==false){
            acc = solAcc[i];
            aux = i;
        }
        
    }

    //quando ele acha o nodo com maior solAcc ele o remove do conjunto soluçao
    //e atualiza a solução atual e o accPtoP
    if (aux < N){
        //std::cout << aux << std::endl;
        sol[aux] = false;
        //atualização da resposta
        for(int i = 0; i < N; i++)
        AccPtoP[i] = INF;
        acc = 0;
        for(int i = 0; i<N; i++)
            if(sol[i] == true)
                for(int j = 0; j<N; j++)
                    if (mat[i][j] < AccPtoP[j])
                        AccPtoP[j] = mat[i][j];

        for(int i = 0; i<N; i++){
            acc += AccPtoP[i];
            if(acc > INF)
                acc = INF;
        }
        solValue = acc;
        
    }
    else{
        for(int i = 0; i < N; i++)
            setTabu[i] = false;
        goto newTABU;
    
    }

}

void tabu::ADD(){
    // reset no accumulador para soluçoes com um numero qualquer
    for(int i = 0; i< N; i++)
        solAcc[i] = 0.00;
    //avaliação do quanto é reduzida a solução se nodo for adicionado, resultados em solAcc
    for(int i = 0; i<N; i++){
        if (setTabu[i]==false && sol[i] == false){
            long double acc = 0;
            for(int j = 0; j<N; j++)
                if(mat[i][j] < AccPtoP[j]){
                    acc += (mat[i][j]-AccPtoP[j]);
                    if(acc > INF)
                        acc = INF;
                }

            solAcc[i] = acc;
        }
    }
    // pega o menor solAcc, como sõe numeros negativos, 
    //o menor solAcc é maior absoluto e promove uma maior redução na solução
    long double acc = 0;
    int aux = N;
    for(int i = 1; i<N; i++)
        if(sol[i] == false && setTabu[i] == false && solAcc[i] < acc){
            acc = solAcc[i];
            aux = i;
        }

    //quando ele acha o nodo com menor solAcc ele adiciona ao conjunto soluçao
    //e atualiza a solução atual e o accPtoP
    if (aux < N){
        //nesta rotina o elemento adicionado vira tabu
        setTabu[aux] = true;        
        sol[aux] = true;
        //atualização da resposta
        acc = 0;
        for(int i = 0; i<N; i++){
            if (mat[aux][i] < AccPtoP[i])
                AccPtoP[i] = mat[aux][i];
            acc += AccPtoP[i];
            if(acc > INF)
                acc = INF;
        }
        solValue = acc;
    }
    else{
        for(int i = 0; i< N; i++){
            if(sol[i] == false && setTabu[i] == false){
                sol[i] = true;
                setTabu[i] = true;
                //atualização da resposta
                acc = 0;
                for(int u = 0; u<N; u++){
                        if (mat[i][u] < AccPtoP[u])
                                AccPtoP[u] = mat[i][u];
                        acc += AccPtoP[u];
                        if(acc > INF)
                                acc = INF;
                }
                solValue = acc;
                
                break;
            }         
        }
    }
}

bool tabu::SWAP(int i, int j){
    solMelhor[i] = false;
    solMelhor[j] = true;
    //atualização da resposta
    for(int u = 0; u < N; u++)
        AccPtoP[u] = INF;
    for(int u = 0; u<N; u++)
         if(solMelhor[u] == true)
                for(int y = 0; y<N; y++)
                    if (mat[u][y] < AccPtoP[y])
                        AccPtoP[y] = mat[u][y];

    long double acc = 0;
    for(int u = 0; u<N; u++){
        acc += AccPtoP[u];
        if(acc > INF)
                acc = INF;
    }
    solValue = acc;
    //Se a solução com a troca for melhor a finção atualilza o melhor resultado e retorna true
    if(solValue < solValueMelhor){
        //achada melhor resposta
        solValueMelhor = solValue;
        return true;
    }
    //Se a solução com troca não é melhor então hé a destroca e função retorna false
    else{
        solMelhor[i] = true;
        solMelhor[j] = false;
        return false;
    }
}


