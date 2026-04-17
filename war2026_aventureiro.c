#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir territórios
void exibirTerritorios(Territorio *mapa, int n) {
    printf("\n=== Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- Ataque ---\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf(">>> Atacante venceu!\n");

        // Transferência de controle
        strcpy(defensor->cor, atacante->cor);

        // Transferência de tropas (metade do atacante)
        int tropasTransferidas = atacante->tropas / 2;

        if (tropasTransferidas < 1) tropasTransferidas = 1;

        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {
        printf(">>> Defensor venceu!\n");

        // Atacante perde 1 tropa
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

// Função para liberar memória
void liberarMemoria(Territorio *mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}

int main() {
    int n;

    srand(time(NULL)); // inicializa aleatoriedade

    printf("Quantidade de territórios: ");
    scanf("%d", &n);

    // Alocação dinâmica
    Territorio *mapa = (Territorio *) calloc(n, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    int opcao = 1;

    while (opcao != 0) {
        exibirTerritorios(mapa, n);

        int atk, def;

        printf("\nEscolha o índice do atacante (-1 para sair): ");
        scanf("%d", &atk);

        if (atk == -1) break;

        printf("Escolha o índice do defensor: ");
        scanf("%d", &def);

        // Validações
        if (atk < 0 || atk >= n || def < 0 || def >= n) {
            printf("Índices inválidos!\n");
            continue;
        }

        if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
            printf("Não é possível atacar um território da mesma cor!\n");
            continue;
        }

        if (mapa[atk].tropas < 1) {
            printf("Atacante sem tropas suficientes!\n");
            continue;
        }

        atacar(&mapa[atk], &mapa[def]);
    }

    liberarMemoria(mapa);

    return 0;
}