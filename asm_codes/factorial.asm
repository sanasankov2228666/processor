IN; Ввод числа n
POPREG AX

CALL :factorial

OUT
HLT

:factorial
    PUSHREG AX

    PUSHREG AX
    PUSH 1
    JE :end_out

    PUSH 1
    PUSHREG AX
    SUB
    POPREG AX

    CALL :factorial

    MULT

    :end_out
    RET
