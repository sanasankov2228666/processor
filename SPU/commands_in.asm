IN; Ввод числа n
POPREG AX; Сохраняем n в регистр AX

PUSH 1; Загружаем начальное значение факториала = 1
POPREG BX; Сохраняем в BX (результат)

PUSH 2
POPREG CX; counter

CALL :factorial

CALL :end_out

:factorial

    PUSHREG AX; Проверяем AX > 1
    PUSH 1
    JB :end_out
    
    PUSHREG BX; BX = BX * AX
    PUSHREG CX
    MULT
    POPREG BX
    
    PUSHREG CX; CX++
    PUSH 1
    ADD
    POPREG CX
    
    PUSHREG CX
    PUSHREG AX
    JBE :factorial
    RET

:end_out

    PUSHREG BX; Выводим результат
    OUT
    HLT