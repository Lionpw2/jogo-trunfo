#include <stdio.h>

// Estrutura das cartas
typedef struct {
    char nome[50];
    int forca;
    int velocidade;
    int inteligencia;
} Carta;

// Função para comparar um atributo
void compararCartas(Carta carta1, Carta carta2, int atributo) {
    int valor1, valor2;

    switch (atributo) {
        case 1:
            valor1 = carta1.forca;
            valor2 = carta2.forca;
            break;
        case 2:
            valor1 = carta1.velocidade;
            valor2 = carta2.velocidade;
            break;
        case 3:
            valor1 = carta1.inteligencia;
            valor2 = carta2.inteligencia;
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }

    // Exibe o resultado
    if (valor1 > valor2) {
        printf("%s venceu!\n", carta1.nome);
    } else if (valor2 > valor1) {
        printf("%s venceu!\n", carta2.nome);
    } else {
        printf("Empate!\n");
    }
}

// Função para comparação de dois atributos combinados
void compararDoisAtributos(Carta carta1, Carta carta2, int atributo1, int atributo2) {
    int soma1 = 0, soma2 = 0;

    switch (atributo1) {
        case 1: soma1 += carta1.forca; soma2 += carta2.forca; break;
        case 2: soma1 += carta1.velocidade; soma2 += carta2.velocidade; break;
        case 3: soma1 += carta1.inteligencia; soma2 += carta2.inteligencia; break;
    }
    
    switch (atributo2) {
        case 1: soma1 += carta1.forca; soma2 += carta2.forca; break;
        case 2: soma1 += carta1.velocidade; soma2 += carta2.velocidade; break;
        case 3: soma1 += carta1.inteligencia; soma2 += carta2.inteligencia; break;
    }

    // Exibe o vencedor com base na soma dos dois atributos
    if (soma1 > soma2) {
        printf("%s venceu!\n", carta1.nome);
    } else if (soma2 > soma1) {
        printf("%s venceu!\n", carta2.nome);
    } else {
        printf("Empate!\n");
    }
}

// Menu interativo
int main() {
    Carta carta1 = {"Dragão", 90, 70, 60};
    Carta carta2 = {"Cavaleiro", 80, 80, 75};
    
    int opcao, atributo1, atributo2;

    do {
        printf("\n===== SUPER TRUNFO =====\n");
        printf("1 - Comparar um atributo\n");
        printf("2 - Comparar dois atributos\n");
        printf("3 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Escolha um atributo para comparar:\n");
                printf("1 - Força\n2 - Velocidade\n3 - Inteligência\n");
                scanf("%d", &atributo1);
                compararCartas(carta1, carta2, atributo1);
                break;

            case 2:
                printf("Escolha dois atributos para comparar:\n");
                printf("1 - Força\n2 - Velocidade\n3 - Inteligência\n");
                printf("Escolha o primeiro atributo: ");
                scanf("%d", &atributo1);
                printf("Escolha o segundo atributo: ");
                scanf("%d", &atributo2);
                compararDoisAtributos(carta1, carta2, atributo1, atributo2);
                break;

            case 3:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 3);

    return 0;
}
