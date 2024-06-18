//Arquitetura de Computadores 1
//Aluno: José Henrique Cintra de Souza Barros
//Professor: Max

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
int verity_label(char *);
int verify_VAR(char *var);

char *Decimal_para_Binario(int n){
  int a, b, c;
  char *p;
  c = 0;
  p = (char*)malloc(16+1);
  if (p == NULL)
    exit(EXIT_FAILURE);
  for (a = 15 ; a >= 0 ; a--){
    b = n >> a;
    if (b & 1)
      *(p+c) = 1 + '0';
    else
      *(p+c) = 0 + '0';
    c++;
  }
  *(p+c) = '\0';
  return  p;
}
//Fim primeira Parte

char *Decimal_para_Binario_seg_var(int n, int l){
  int a, b, c;
  char *p;

  c = 0;
  p = (char*)malloc(l+1);

  if (p == NULL)
    exit(EXIT_FAILURE);

  for (a = l-1 ; a >= 0 ; a--){
    b = n >> a;
    if (b & 1)
      *(p+c) = 1 + '0';
    else
      *(p+c) = 0 + '0';
    c++;
  }
  *(p+c) = '\0';
  return  p;
}
//Fim segunda Parte
//Tudo OK
FILE * read_file(char *argv[0]){
  setlocale(LC_ALL,""); //Acentuação
  clock_t inicio = clock(); //Tempo de execução
  FILE *fp;
  char linha[40];

  fp = fopen(argv[1], "r");
  if (!fp) {
   printf("\nNão foi possível abrir o arquivo");
    exit(0);
  }

  printf("Arquivo aberto com sucesso!\n");

  //Mostrar tempo de execução
  clock_t parada = clock();
  double elapsed = (double)(parada - inicio) * 1000.0 / clocks_por_seg;
  printf("Tempo de execução %.5fms\n", elapsed);
  return(fp);
}
//Fim terceira Parte

FILE * create_file(char *argv[0]){
  setlocale(LC_ALL,""); //Acentuação
  clock_t inicio = clock(); //Tempo de execução
  FILE *fp;
  char linha[40];

  fp = fopen(argv[2] ? argv[2] : "memoria.dat", "w");
  if (!fp) {
    printf("\nNão foi possível criar o arquivo");
    exit(0);
  }

  printf("Arquivo \"%s\" criado com sucesso!\n\n", argv[2] ? argv[2] : "memoria.dat");

  //Mostrar tempo de execução
  clock_t parada = clock();
  double elapsed = (double)(parada - inicio) * 1000.0 / clocks_por_seg;
  printf("Tempo de execução %.5fms\n\n", elapsed);
  return(fp);
}

int verity_label(char *label){
  int i;
   for(i = 0; label[i] != '\0'; i++){
      if(label[i] == ':'){
        return 1;
      }
    }
    return 0;
}

int verif_Tipo(char *command){
  char instrucoes_R[7][4] = {"add","sub", "and", "or", "xor", "slt", "jr"};
  char instrucoes_I[5][5] = {"addi", "beq", "bne", "lw", "sw"};
  char instrucoes_J[2][4] = {"j", "jal"};
  int i;

  for(i = 0; i <= sizeof(instrucoes_R); i++){
    if(!strcmp(command, instrucoes_R[i]))
      return 1;
  }
  for(i = 0; i <= sizeof(instrucoes_R); i++){
    if(!strcmp(command, instrucoes_I[i]))
      return 2;
  }
  for(i = 0; i <= sizeof(instrucoes_R); i++){
    if(!strcmp(command, instrucoes_J[i]))
      return 3;
  }
  
  printf("\"%s\" instrucao nao reconhecida.", command);
  exit(0);
}

int verify_VAR(char *var){
//Lista com todos os Registradores aceitos
  char registradores[31][6] = {"$at", "$v0", "$v1", "$a0", "$a1", "$a3" ,"$t0" , "$t1" , "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra", "$zero"};
  int i;
  for(i = 0; i < sizeof(registradores);i++){
    if(!strcmp(var, registradores[i])){
     //printf("~~~~ %s == %s\n", var, registradores[i]);
      return 1;
    }
  }
  printf("Registrador \"%s\" não encontrado\n", var);
  exit(2);
}

//código MAIN
int main(int argc, char *argv[]) {
    char word[33];
    char instrucoes_R[7][4] = {"add","sub", "and", "or", "xor", "slt", "jr"};
    char * opcode_R = "000000";
    char funct_R[7][7] = {"100000", "100010", "100100", "100101", "100110", "	101010",  "001000"};
    char instrucoes_I[5][5] = {"addi", "beq", "bne", "lw", "sw"};
    char opcode_I[5][7] = {"001000", "000100", "000101", "100011", "101011"};
    char instrucoes_J[2][4] = {"j", "jal"};
    char opcode_J[2][7] = {"000010", "000011"};
    char registradores[32][6] = {"$zero","$at", "$v0", "$v1", "$a0", "$a1","$a2", "$a3" ,"$t0" , "$t1" , "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra" };
    char Regist_Num[32][6] = {"00000", "00001", "00010", "00011", "00100", "00101", "00110", "00111", "01000", "01001", "01010", "01011", "01100", "01101", "01110", "01111", "10000", "10001", "10010", "10011", "10100", "10101", "10110", "10111", "11000", "11001", "11010", "11011", "11100", "11101", "11110", "11111"};
    char linha[BUFFER], aux[11], label[11], command[5], Res_1[10], Res_2[10], Res_3[10];


    FILE * fp = read_file(&argv[0]);
    FILE *criado_arquivo_fp = create_file(&argv[0]);



    int i;
    while(fgets(linha, BUFFER, fp)){
    //printf("%s\n", linha);
    sscanf(linha, "%[^#]s", linha);
    if(linha[0] =='#'){
      continue;
    }
    sscanf(linha, "%s %s %s %s %s", label, command, Res_1, Res_2, Res_3);
    if (verity_label(label)){
      strcpy(aux, label);
      strcpy(label, command);
      strcpy(command, Res_1);
      strcpy(Res_1, Res_2);
      strcpy(Res_2, Res_3);
      strcpy(Res_3, aux);
    }
    int Tipo = verif_Tipo(label);
   //printf("Instrucao do Tipo %c.\n\n", Tipo == 1 ? 'R': Tipo == 2 ? 'I': 'J');

    
   //printf(">>%s\n", label);
   //printf(">>%s\n", command);
   //printf(">>%s\n", Res_1);
   //printf(">>%s\n", Res_2);
   //printf(">>%s\n\n", Res_3);
    if(Tipo == 1 && verify_VAR(command) && verify_VAR(Res_1) && verify_VAR(Res_2)){
      int offset;
      // opcode
      strcat(word, &opcode_R[0]);
      word[0] = '0';
     //printf(" op added, word: %s\n\n", word);
      if(strcmp(label, "jr")){
        // rs
        for(offset = 0; offset <= sizeof(registradores); offset++){
        if(!strcmp(Res_1, registradores[offset])){
          strcat(word, Regist_Num[offset]);
         //printf(" rs added, word: %s\n\n", word);
          break;
        }
      }
      // rt
        for(offset = 0; offset <= sizeof(registradores); offset++){
        if(!strcmp(Res_2, registradores[offset])){
          strcat(word, Regist_Num[offset]);
         //printf(" rt added, word: %s\n\n", word);
          break;
          }
        }
      // rd
      for(offset = 0; offset <= sizeof(registradores); offset++){
        if(!strcmp(command, registradores[offset])){
          strcat(word, Regist_Num[offset]);
         //printf(" rd added, word: %s\n\n", word);
          break;
        }
      }
      //Shamt
      strcat(word,"00000");
     //printf(" sh added, word: %s\n\n", word);
      for(offset = 0; offset <= sizeof(instrucoes_R); offset++){
        if(!strcmp(label, instrucoes_R[offset])){
          strcat(word, funct_R[offset]);
         //printf(" ft added, word: %s\n\n", word);
          break;
          }
        }
      }else{
        for(offset = 0; offset <= sizeof(instrucoes_R); offset++){
          if(!strcmp(command, registradores[offset])){
            strcat(word, Regist_Num[offset]);
           //printf(" rs added, word: %s\n\n", word);
            break;
          }
        }
        strcat(word, "000000000000000001000");
      }
     //printf(" pr ended, word: %s\n\n", word);
     //printf("formatted word:\n\n");
      int k;
      for(k = 24; word[k] != '\0'; k++){
          fprintf(criado_arquivo_fp, "%c", word[k]);
      }
        fprintf(criado_arquivo_fp,"\n");
      for(k = 16; k < 24; k++){
          fprintf(criado_arquivo_fp, "%c", word[k]);
      }
        fprintf(criado_arquivo_fp,"\n");
      for(k = 8; k < 16; k++){
          fprintf(criado_arquivo_fp, "%c", word[k]);
      }
        fprintf(criado_arquivo_fp,"\n");
      for(k = 0; k < 8; k++){
          fprintf(criado_arquivo_fp, "%c", word[k]);
      }
        fprintf(criado_arquivo_fp,"\n");
    }
    if(Tipo == 2){
      // addi
        int imm = atoi(Res_2), offset;
        char auxNumber[30];
        char word[33]={""}, strimm[17];
        strcpy(word, "");
        if(!strcmp(label, "addi")){
          strcat(word, "001000");
        }else if(!strcmp(label, "beq")){
          strcat(word, "000100");
        }else if(!strcmp(label, "bne")){
          strcat(word, "000101");
        }else if(!strcmp(label, "lw")){
          int k;
          char auxrs[4]={""};
          for (k = 1; Res_1[k] != '\0'; k++){
            auxNumber[k] = Res_1[k-1];
            if(Res_1[k] == '('){
              auxrs[0] = Res_1[k+1];
              auxrs[1] = Res_1[k+2];
              auxrs[2] = Res_1[k+3];
              break;
            }
          }
          k = atoi(Res_1);
          strcpy(Res_1, auxrs);
          strcpy(auxNumber, Decimal_para_Binario(k));
          strcat(word, "100011");
        }else if(!strcmp(label, "sw")){
          int k;
          char auxrs[4]={""};
          for (k = 1; Res_1[k] != '\0'; k++){
            auxNumber[k] = Res_1[k-1];
            if(Res_1[k] == '('){
              auxrs[0] = Res_1[k+1];
              auxrs[1] = Res_1[k+2];
              auxrs[2] = Res_1[k+3];
            }
          }
          strcpy(Res_1, auxrs);
          k = atoi(auxNumber);
          strcpy(auxNumber, Decimal_para_Binario(k));
          strcat(word, "101011");
        }
       //printf("%s\n", word);
        // rs
        for(offset = 0; offset <= sizeof(registradores); offset++){
          if(!strcmp(Res_1, registradores[offset])){
            strcat(word, Regist_Num[offset]);
           //printf(" rs added, word: %s\n\n", word);
            break;
          }
        }
        // rt
        for(offset = 0; offset <= sizeof(registradores); offset++){
          if(!strcmp(command, registradores[offset])){
            strcat(word, Regist_Num[offset]);
           //printf(" rt added, word: %s\n\n", word);
            break;
          }
        }
        // Imm
        if(!strcmp(label, "sw") || !strcmp(label, "lw")){
          strcat(word, auxNumber);
        }else{
          strcat(word, Decimal_para_Binario(imm));
        }
       //printf("imm/offset added, word: %s\n\n", word);
       //printf(" pr ended, word: %s\n\n", word);
       //printf("formatted word:\n\n");
        int k;
        for(k = 24; word[k] != '\0'; k++){
          fprintf(criado_arquivo_fp, "%c", word[k]);
        }
        fprintf(criado_arquivo_fp,"\n");
        for(k = 16; k < 24; k++){
          fprintf(criado_arquivo_fp, "%c", word[k]);
        }
        fprintf(criado_arquivo_fp,"\n");
        for(k = 8; k < 16; k++){
          fprintf(criado_arquivo_fp, "%c", word[k]);
        }
        fprintf(criado_arquivo_fp,"\n");
        for(k = 0; k < 8; k++){
          fprintf(criado_arquivo_fp, "%c", word[k]);
        }
        fprintf(criado_arquivo_fp,"\n");
      // bne, beq
      // lw, sw
    }
    if(Tipo == 3){
      char word[33]={""};
      if(!strcmp(label, "j")){
          strcat(word, "000010");
      }else{
          strcat(word, "000011");
      }
      int k = atoi(command);
      strcat(word, Decimal_para_Binario_seg_var(k, 26));
     //printf(" pr ended, word: %s\n\n", word);

       //printf("formatted word:\n\n");
        for(k = 24; word[k] != '\0'; k++){
          fprintf(criado_arquivo_fp, "%c", word[k]);
        }
        fprintf(criado_arquivo_fp,"\n");
        for(k = 16; k < 24; k++){
          fprintf(criado_arquivo_fp,"%c", word[k]);
        }
        fprintf(criado_arquivo_fp,"\n");
        for(k = 8; k < 16; k++){
          fprintf(criado_arquivo_fp,"%c", word[k]);
        }
        fprintf(criado_arquivo_fp,"\n");
        for(k = 0; k < 8; k++){
          fprintf(criado_arquivo_fp,"%c", word[k]);
        }
        fprintf(criado_arquivo_fp,"\n");
    }
    strcpy(label, "");
    strcpy(command, "");
    strcpy(Res_1, "");
    strcpy(Res_2, "");
    strcpy(Res_3, "");
    strcpy(word, "");
  }
    fclose(criado_arquivo_fp);
}