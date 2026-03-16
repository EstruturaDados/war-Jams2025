#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Essa estrutura armazena as informações de cada território
struct Territorio {
char nome[30]; // Nome do território
char cor[10]; // Cor do exército
int tropas; // Quantidade de tropas
};

int main() {

// Vetor de structs para armazenar até 5 territórios
struct Territorio territorios[5];

int i;

printf("=== Vamos cadastrar os 5 territorios iniciais do nosso mundo. ===\n\n");

// Laço para entrada de dados dos territórios
for(i = 0; i < 5; i++) {

printf("Cadastrando Territorio %d\n", i + 1);

// Leitura do nome do território
printf("Digite o nome do territorio: ");
scanf("%s", territorios[i].nome);

// Leitura da cor do exército
printf("Digite a cor do exercito: ");
scanf("%s", territorios[i].cor);

// Leitura da quantidade de tropas
printf("Digite a quantidade de tropas: ");
scanf("%d", &territorios[i].tropas);

printf("\n");
}

// Exibição dos dados cadastrados
printf("\n=== MAPA DO MUNDO - ESTADO ATUAL ===\n\n");

for(i = 0; i < 5; i++) {

printf("Territorio %d\n", i + 1);
printf("Nome: %s\n", territorios[i].nome);
printf("Cor do exercito: %s\n", territorios[i].cor);
printf("Quantidade de tropas: %d\n", territorios[i].tropas);
printf("-----------------------------\n");
}

return 0;
}