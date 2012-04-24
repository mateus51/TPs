mult(): LOAD cte0
STORE mult_result
POP multRA
POP mult1
POP mult2
mult_start: LOAD mult2
SUB cte1
JPL mult_end
LOAD mult_result
ADD mult1
STORE mult_result
LOAD mult2
SUB cte1
STORE mult2
JMP mult_start
mult_end: PUSH mult_result
PUSH multRA
RET
mult1: WORD 0
mult2: WORD 0
mult_result: WORD 0
multRA: WORD 0
END