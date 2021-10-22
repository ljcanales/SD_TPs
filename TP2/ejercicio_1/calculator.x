struct Operands {
    int op1;
    int op2;
};

program CALCULATOR {
    version CALCULATOR_VER {
        double SUMAR(Operands) = 1;
        double RESTAR(Operands) = 2;
        double MULTIPLICAR(Operands) = 3;
        double DIVIDIR(Operands) = 4;
    } = 1;
} = 0x20000001;
