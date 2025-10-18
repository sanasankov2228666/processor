IN
IN
IN
POPREG CX
POPREG BX
POPREG AX

PUSH 0
PUSHREG AX
JE :1;      проверка на линейность уравнения

PUSHREG AX
PUSHREG CX
PUSH 4
MULT
MULT; 4ac
PUSHREG BX
PUSHREG BX
MULT;       b^2
SUB
POPREG DX

PUSHREG DX
PUSH 0
JB :2;      проверка на дискриминант меньше 0 -> D < 0 {ADRES 2

PUSHREG BX
PUSH 0
SUB; -b
PUSHREG DX
SQRT; SQRT(D)
ADD; -b + sqrt(D)
PUSH 2
PUSHREG AX
MULT
DIV
POPREG EX

PUSHREG DX
SQRT; SQRT(D)
PUSHREG BX
PUSH 0; //////////////////////////////////////////
SUB; -b
SUB; -b - sqrt(D)
PUSH 2
PUSHREG AX
MULT
DIV
POPREG FX

PUSHREG EX
PUSHREG FX
OUT
OUT
JUMP :3; 2 roots end ->  {ADRES END

:1
PUSHREG CX; линейный случай <- a = 0  ADRES 1} 
PUSHREG BX
PUSH 0
SUB; -b
DIV; с / -b
POPREG EX; корень
PUSHREG EX
OUT; вывод одного кода
JUMP :3; -> 1 root end {ADRES END

:2
PUSH -1; <- D < 0    ADRES 2}
OUT

:3
HLT; конец  <- 2 roots end <- 1 root end  ADRES END }