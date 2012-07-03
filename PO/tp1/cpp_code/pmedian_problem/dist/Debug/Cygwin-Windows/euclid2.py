#!/usr/bin/python
# -*- coding: utf-8 -*-

import math

if __name__ == '__main__':
  #a1 = "pmedian3282.txt"
  a1 = "pmedian324.txt"
  #a1 = "pmedian818.txt"
  
  #a2 = "result3282.txt"
  a2 = "result324.txt"
  #a2 = "result818.txt"
  a = 1
  arqEnt = open(a1, "r")
  arqSaida = open(a2, "w")
  aux = 325
  pointsx = []
  pointsy = []
  for line in arqEnt:
    x, y = line.split(" ")
    pointsx.append(int(x))
    pointsy.append(int(y))

  for i in range(0, aux-1):
    for j in range(0, aux-1):       
      if i == j:
        dist = 0
      else:
        dist = math.sqrt(math.pow((pointsx[j]-pointsx[i]), 2) + math.pow((pointsy[j]-pointsy[i]), 2))
      arqSaida.write("%.2f " % dist)
    arqSaida.write("\n")
  arqSaida.write(";")

  arqEnt.close()
  arqSaida.close()
