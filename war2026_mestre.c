#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===== STRUCT =====
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ===== MISSÕES =====

void atribuirMissao(char *destino, char *missoes[], int total) {
    int i = rand() % total;
    strcpy(destino, missoes[i]);
}

void exibirMissao(char *missao) {
    printf("\n=== SUA MISSÃO ===\n%s\n", missao);
}

// Lógica simples
int verificarMissao(char *missao, Territorio *mapa, int n) {

    // conquistar 3 territórios AZUL
    if (strstr(missao, "3 territorios") != NULL) {
        int cont = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                cont++;
        }
        return cont >= 3;
    }

    // eliminar vermelhos
    if (strstr(missao, "vermelhas") != NULL) {
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0)
                return 0;
        }
        return 1;
    }

    return 0;
}

// ===== MAPA =====

void inicializarMapa(Territorio *mapa) {

    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, "Azul");
    mapa[0].tropas = 5;

    strcpy(mapa[1].nome, "Argentina");
    strcpy(mapa[1].cor, "Vermelho");
    mapa[1].tropas = 3;

    strcpy(mapa[2].nome, "EUA");
    strcpy(mapa[2].cor, "Azul");
    mapa[2].tropas = 4;

    strcpy(mapa[3].nome, "Alemanha");
    strcpy(mapa[3].cor, "Vermelho");
    mapa[3].tropas = 2;

    strcpy(mapa[4].nome, "Japao");
    strcpy(mapa[4].cor, "Neutro");
    mapa[4].tropas = 1;
}

void exibirMapa(Territorio *mapa, int n) {
    printf("\n=== MAPA DO MUNDO ===\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ===== ATAQUE =====

void atacar(Territorio *atk, Territorio *def) {

    if (strcmp(atk->cor, def->cor) == 0) {
        printf("Ataque inválido!\n");
        return;
    }

    int dAtk = rand() % 6 + 1;
    int dDef = rand() % 6 + 1;

    printf("\nAtaque: %d x %d\n", dAtk, dDef);

    if (dAtk > dDef) {
        printf("Atacante venceu!\n");

        strcpy(def->cor, atk->cor);

        int tropas = atk->tropas / 2;
        if (tropas < 1) tropas = 1;

        def->tropas = tropas;
        atk->tropas -= tropas;

    } else {
        printf("Defensor venceu!\n");
        if (atk->tropas > 0)
            atk->tropas--;
    }
}

// ===== MEMÓRIA =====

void liberarMemoria(Territorio *mapa, char *missao) {
    free(mapa);
    free(missao);
}

// ===== MAIN =====

int main() {

    srand(time(NULL));

    int n = 5;

    // ===== MISSÕES =====
    char *missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar todas as tropas vermelhas",
        "Dominar o mapa inteiro",
        "Ter 10 tropas em um territorio",
        "Conquistar 2 territorios seguidos"
    };

    // ===== ALOCAÇÃO =====
    Territorio *mapa = (Territorio *) calloc(n, sizeof(Territorio));
    char *missao = (char *) malloc(100 * sizeof(char));

    if (!mapa || !missao) {
        printf("Erro de memória!\n");
        return 1;
    }

    // ===== INICIALIZAÇÃO =====
    inicializarMapa(mapa);
    atribuirMissao(missao, missoes, 5);

    // ===== INÍCIO DO JOGO =====
    exibirMapa(mapa, n);
    exibirMissao(missao);

    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int a, d;

            printf("Atacante: ");
            scanf("%d", &a);

            printf("Defensor: ");
            scanf("%d", &d);

            if (a >= 0 && a < n && d >= 0 && d < n) {
                atacar(&mapa[a], &mapa[d]);

                // verificação automática
                if (verificarMissao(missao, mapa, n)) {
                    printf("\n🎉 MISSÃO CUMPRIDA! VOCÊ VENCEU! 🎉\n");
                    break;
                }

            } else {
                printf("Índices inválidos!\n");
            }

        } else if (opcao == 2) {

            if (verificarMissao(missao, mapa, n)) {
                printf("Missão já foi cumprida!\n");
            } else {
                printf("Missão ainda não concluída.\n");
            }
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missao);

    return 0;
}