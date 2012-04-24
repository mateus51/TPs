div(): POP divRA
POP div2
POP div1
div_start: LOAD div1
STORE resto
SUB div2
JPL div_end
STORE div1
LOAD div_result
ADD cte1
STORE div_result
JMP div_start
div_end: PUSH resto
PUSH div_result
PUSH divRA
RET
div1: WORD 0
div2: WORD 0
div_result: WORD 0
resto: WORD 0
divRA: WORd 0