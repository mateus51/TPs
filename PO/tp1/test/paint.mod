param warehouse;  # number of warehouses
param customer;  # number of customers

  #transportation cost from warehouse i
  #to customer j
param cost{i in 1..warehouse, j in 1..customer};

param supply{i in 1..warehouse};    #supply at warehouse i
param demand{i in 1..customer};     #demand at customer j

var amount{i in 1..warehouse, j in 1..customer};

minimize Cost:
  sum{i in 1..warehouse, j in 1..customer} cost[i,j]*amount[i,j];


subject to Supply {i in 1..warehouse}:
  sum{j in 1..customer} amount[i,j] = supply[i];
subject to Demand {j in 1..customer}:
  sum{i in 1..warehouse} amount[i,j] = demand[j];
subject to positive{i in 1..warehouse, j in 1..customer}:
  amount[i,j]>=0;
