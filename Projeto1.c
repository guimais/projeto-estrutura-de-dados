#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Apoio.h"

int main()
{
    Lista *L = CriaLista();
    int Opcao, valor;

    do{
        system("cls");
        printf("**************************************************************");
        printf("\n Gerenciador de Manutencao de Equipamentos de um Laboratorio");

        printf("\n\n\tDigite 1 - NOVA SOLICITACAO");
        printf("\n\tDigite 2 - REMOVER SOLICITACAO");
        printf("\n\tDigite 3 - CONSULTAR SOLICITACAO");
        printf("\n\tDigite 4 - ALTERAR PRIORIDADE E/OU PERIODO DE SOLICITACAO");
        printf("\n\tDigite 5 - ORDEM DA REALIZACAO DA MANUTENCAO");
        printf("\n\tDigite 6 - TODAS SOLICITACOES");
        printf("\n\tDigite 0 - SAIR");

        printf("\n\n**************************************************************\n");

        scanf("%d", &Opcao);

        switch(Opcao){
            case 1: {
                valor = LeCodigo(L);
                Solicitacao novasolicitacao = preencher(valor);
                insereCodigo(L, novasolicitacao);
                printf("Solicitacao %d inserida.\n", valor);
                break;
            }
            case 2:

                break;
            case 3:
                printf("Digite o codigo da solicitacao: ");
                scanf("%d", &valor);
                    if (L -> inicio == NULL) {
                    printf("Nenhuma solicitacao cadastrada.\n");
                } else {
                    imprimirinformacao(L, valor);
                }
                break;
            case 4:
                if (L -> inicio == NULL) {
                    printf("Nenhuma solicitacao cadastrada.\n");
                } else {
                    alterarSolicitacao(L);
                }
                break;
            case 5:
                break;
            case 6:
                if (L -> inicio == NULL) {
                    printf("Nenhuma solicitacao cadastrada.\n");
                } else {
                    imprimir(L);
                }
                break;
            case 0:
                break;
            default:
                printf("Seu numero e invalido. Digite novamente\n");
                break;
        }
        if (Opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            while (getchar() != '\n');
            getchar();
        }
    }
    while (Opcao != 0);


    return 0;
}
