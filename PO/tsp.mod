
        set S ordered;
        param n := card {S};

        set SS := 0 .. (2**n - 1);

        set POW {k in SS} := {i in S: (k div 2**(ord(i)-1)) mod 2 = 1};


        set LINKS := {i in S, j in S: ord(i) < ord(j)};

        param cost {LINKS} >= 0;
        var X {LINKS} binary;

        minimize TotCost: sum {(i,j) in LINKS} cost[i,j] * X[i,j];

        subj to Tour {i in S}:
           sum {(i,j) in LINKS} X[i,j] + sum {(j,i) in LINKS} X[j,i] = 2;

        subj to SubtourElim {k in SS diff {0,2**n-1}}:
           sum {i in POW[k], j in S diff POW[k]: (i,j) in LINKS} X[i,j] +
           sum {i in POW[k], j in S diff POW[k]: (j,i) in LINKS} X[j,i] >= 2;


        data;

        set S := a b c d ;

        param cost:  a   b   c   d :=
                a    .  43  21  19
                b    .   .  21  12
                c    .   .   .  39
                d    .   .   .   . ;

