
from subprocess import call
import sys
import math

call(["rm","saida.txt"])
for i in xrange(0,25):
    for o in xrange(0,5):
        call(["./cliente","localhost","5432","in.txt."+str(i+1),"256"])

arquivo = open("saida.txt","r");
saida = open("testes/media.txt","w")

for i in xrange(0,25):
    tempo = []
    desv = 0.0
    throughput = 0.0
    soma = 0.0
    for o in xrange(0,5):
        linha = arquivo.readline().split()
        tamanho = linha[0]
        mensagens = linha[1]
        bufcliente = linha[2]
        throughput += float(linha[3])
        soma+= float(linha[4])
        tempo.append(float(linha[4]))

    media = soma/5
    
    for oi in tempo:
        desv+= (oi-media)**2
    desv = desv/5

    desv = math.sqrt(desv)
    

    throughput = int(tamanho)/float(media)
    
    saida.write(tamanho)
    saida.write(" ")
    saida.write(mensagens)
    saida.write(" ")
    saida.write(bufcliente)
    saida.write(" ")
    saida.write(str(throughput))
    saida.write(" ")
    saida.write(str(media))
    saida.write(" ")
    saida.write(str(desv))
    saida.write("\n")

