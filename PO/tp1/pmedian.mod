# numero de madianas a serem encontradas
param p;

# tamanho da matriz de custos
param n;

# matriz de custos (distancias)
param d{i in 1..n, j in 1..n} integer;

# matriz de alocação
var x{i in 1..n, j in 1..n} binary;



minimize dist: sum{i in 1..n, j in 1..n} d[i, j] * x[i, j];

subject to r1 {j in 1..n}: sum{i in 1..n} x[i, j] = 1;
subject to r2: sum{i in 1..n} x[i, i] = p;
subject to r3 {i in 1..n, j in 1..n}: x[i, j] <= x[i, i];

