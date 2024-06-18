#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <regex.h>

#define BUFFER 400
#define regexp ".+?(?=#)"

char * Decimal_para_Binario(int n);
FILE * read_file(char *argv[]);
FILE * create_file(char *argv[]);
int verity_label(char *label);
int verify_VAR(char *var);

char * Decimal_para_Binario(int n) {
    int a, b, c;
    char *p;
    c = 0;
    p = (char *)malloc(16 + 1);
    if (p == NULL)
        exit(EXIT_FAILURE);
    for (a = 15; a >= 0; a--) {
        b = n >> a;
        if (b & 1)
            *(p + c) = 1 + '0';
        else
            *(p + c) = 0 + '0';
        c++;
    }
    *(p + c) = '\0';
    return p;
}

char * Decimal_para_Binario_seg_var(int n, int l) {
    int a, b, c;
    char *p;
    c = 0;
    p = (char *)malloc(l + 1);
    if (p == NULL)
        exit(EXIT_FAILURE);
    for (a = l - 1; a >= 0; a--) {
        b = n >> a;
        if (b & 1)
            *(p + c) = 1 + '0';
        else
            *(p + c) = 0 + '0';
        c++;
    }
    *(p + c) = '\0';
    return p;
}

FILE * read_file(char *argv[]) {
    setlocale(LC_ALL, ""); // Acentuação
    clock_t inicio = clock(); // Tempo de execução
    FILE *fp;
    char linha[BUFFER];

    fp = fopen(argv[1], "r");
    if (!fp) {
        printf("\nNão foi possível abrir o arquivo %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("Arquivo aberto com sucesso!\n");

    // Mostrar tempo de execução
    clock_t parada = clock();
    double elapsed = (double)(parada - inicio) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo de execução %.5fms\n", elapsed);
    return fp;
}

FILE * create_file(char *argv[]) {
    setlocale(LC_ALL, ""); // Acentuação
    clock_t inicio = clock(); // Tempo de execução
    FILE *fp;

    fp = fopen(argv[2] ? argv[2] : "memoria.dat", "w");
    if (!fp) {
        printf("\nNão foi possível criar o arquivo %s\n", argv[2] ? argv[2] : "memoria.dat");
        exit(EXIT_FAILURE);
    }

    printf("Arquivo \"%s\" criado com sucesso!\n\n", argv[2] ? argv[2] : "memoria.dat");

    // Mostrar tempo de execução
    clock_t parada = clock();
    double elapsed = (double)(parada - inicio) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo de execução %.5fms\n\n", elapsed);
    return fp;
}

int verity_label(char *label) {
    int i;
    for (i = 0; label[i] != '\0'; i++) {
        if (label[i] == ':') {
            return 1;
        }
    }
    return 0;
}

int verif_Tipo(char *command) {
    char instrucoes_R[7][4] = {"add", "sub", "and", "or", "xor", "slt", "jr"};
    char instrucoes_I[5][5] = {"addi", "beq", "bne", "lw", "sw"};
    char instrucoes_J[2][4] = {"j", "jal"};
    int i;

    for (i = 0; i < 7; i++) {
        if (!strcmp(command, instrucoes_R[i]))
            return 1;
    }
    for (i = 0; i < 5; i++) {
        if (!strcmp(command, instrucoes_I[i]))
            return 2;
    }
    for (i = 0; i < 2; i++) {
        if (!strcmp(command, instrucoes_J[i]))
            return 3;
    }

    printf("\"%s\" instrução não reconhecida.\n", command);
    exit(EXIT_FAILURE);
}

int verify_VAR(char *var) {
    // Lista com todos os Registradores aceitos
    char registradores[31][6] = {"$at", "$v0", "$v1", "$a0", "$a1", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra", "$zero"};
    int i;
    for (i = 0; i < 31; i++) {
        if (!strcmp(var, registradores[i])) {
            return 1;
        }
    }
    printf("Registrador \"%s\" não encontrado\n", var);
    exit(EXIT_FAILURE);
}

// Código MAIN
int main(int argc, char *argv[]) {
    char word[33] = ""; // Inicializa a string para construção da palavra binária
    char instrucoes_R[7][4] = {"add", "sub", "and", "or", "xor", "slt", "jr"};
    char *opcode_R = "000000";
    char funct_R[7][7] = {"100000", "100010", "100100", "100101", "100110", "101010", "001000"};
    char instrucoes_I[5][5] = {"addi", "beq", "bne", "lw", "sw"};
    char opcode_I[5][7] = {"001000", "000100", "000101", "100011", "101011"};
    char instrucoes_J[2][4] = {"j", "jal"};
    char opcode_J[2][7] = {"000010", "000011"};
    char registradores[32][6] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};
    char Regist_Num[32][6] = {"00000", "00001", "00010", "00011", "00100", "00101", "00110", "00111", "01000", "01001", "01010", "01011", "01100", "01101", "01110", "01111", "10000", "10001", "10010", "10011", "10100", "10101", "10110", "10111", "11000", "11001", "11010", "11011", "11100", "11101", "11110", "11111"};
    char label[32], command[32], var[32], register1[32], register2[32], address[32], immediate[32];
    int a, b, c, d, e, f, g, h, i, j, k, l, w, x, y, z;
    regex_t exp1;
    regcomp(&exp1, regexp, REG_EXTENDED);
    FILE * fp = read_file(argv);
    FILE * criado_arquivo_fp = create_file(argv);
    while (fgets(word, 33, fp) != NULL) {
        x = 1;
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        while (x) {
            a = regexec(&exp1, word, 0, NULL, 0);
            if (!a) {
                regexec(&exp1, word, 1, &exp1, 0);
                word[exp1.rm_so] = '\0';
            } else {
                x = 0;
            }
        }
        if (strlen(word)) {
            word[32] = '\0';
        }
    }
    while (fgets(word, 33, fp) != NULL) {
        x = 1;
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        while (x) {
            a = regexec(&exp1, word, 0, NULL, 0);
            if (!a) {
                regexec(&exp1, word, 1, &exp1, 0);
                word[exp1.rm_so] = '\0';
            } else {
                x = 0;
            }
        }
        if (strlen(word)) {
            word[32] = '\0';
        }
    }
    while (fgets(word, 33, fp) != NULL) {
        x = 1;
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        while (x) {
            a = regexec(&exp1, word, 0, NULL, 0);
            if (!a) {
                regexec(&exp1, word, 1, &exp1, 0);
                word[exp1.rm_so] = '\0';
            } else {
                x = 0;
            }
        }
        if (strlen(word)) {
            word[32] = '\0';
        }
    }
    while (fgets(word, 33, fp) != NULL) {
        x = 1;
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        while (x) {
            a = regexec(&exp1, word, 0, NULL, 0);
            if (!a) {
                regexec(&exp1, word, 1, &exp1, 0);
                word[exp1.rm_so] = '\0';
            } else {
                x = 0;
            }
        }
        if (strlen(word)) {
            word[32] = '\0';
        }
    }
    while (fgets(word, 33, fp) != NULL) {
        x = 1;
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        while (x) {
            a = regexec(&exp1, word, 0, NULL, 0);
            if (!a) {
                regexec(&exp1, word, 1, &exp1, 0);
                word[exp1.rm_so] = '\0';
            } else {
                x = 0;
            }
        }
        if (strlen(word)) {
            word[32] = '\0';
        }
    }
    while (fgets(word, 33, fp) != NULL) {
        x = 1;
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        while (x) {
            a = regexec(&exp1, word, 0, NULL, 0);
            if (!a) {
                regexec(&exp1, word, 1, &exp1, 0);
                word[exp1.rm_so] = '\0';
            } else {
                x = 0;
            }
        }
        if (strlen(word)) {
            word[32] = '\0';
        }
    }
    while (fgets(word, 33, fp) != NULL) {
        x = 1;
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        while (x) {
            a = regexec(&exp1, word, 0, NULL, 0);
            if (!a) {
                regexec(&exp1, word, 1, &exp1, 0);
                word[exp1.rm_so] = '\0';
            } else {
                x = 0;
            }
        }
        if (strlen(word)) {
            word[32] = '\0';
        }
    }
    while (fgets(word, 33, fp) != NULL) {
        x = 1;
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        while (x) {
            a = regexec(&exp1, word, 0, NULL, 0);
            if (!a) {
                regexec(&exp1, word, 1, &exp1, 0);
                word[exp1.rm_so] = '\0';
            } else {
                x = 0;
            }
        }
        if (strlen(word)) {
            word[32] = '\0';
        }
    }
    while (fgets(word, 33, fp) != NULL) {
        x = 1;
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        while (x) {
            a = regexec(&exp1, word, 0, NULL, 0);
            if (!a) {
                regexec(&exp1, word, 1, &exp1, 0);
                word[exp1.rm_so] = '\0';
            } else {
                x = 0;
            }
        }
        if (strlen(word)) {
            word[32] = '\0';
        }
    }
    return 0;
}
