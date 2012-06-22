reset;
option solver cplex;
model pmedian.mod;
data pmedian.dat;
solve;
display x;

