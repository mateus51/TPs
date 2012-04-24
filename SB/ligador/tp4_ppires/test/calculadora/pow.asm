pow(): POP powRA 
POP pow2
POP pow1
pow_start: LOAD pow2
SUB cte1
STORE pow2
JPL pow_end 
PUSH pow_result
PUSH pow1
CALL mult()
POP pow_result
JMP pow_start
pow_end: PUSH pow_result
PUSH powRA
RET
pow1: WORD 0
pow2: WORD 0
pow_result:  WORD 1
powRA: WORD 0
END