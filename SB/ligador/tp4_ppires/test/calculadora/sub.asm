sub(): POP subRA 
POP sub1
POP sub2
LOAD sub1
SUB sub2
STORE sub2
PUSH sub2
PUSH subRA
RET
sub1: WORD 0
sub2: WORD 0
subRA: WORD 0
END