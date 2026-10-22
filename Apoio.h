#ifndef APOIO_H_INCLUDED
#define APOIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int  CodigoDeSolicitacao;
    char CodigoEquipamentos[7];
    char nome[20];
    int  prioridade;
    int  periodo;
} Solicitacao;

typedef struct no {
    Solicitacao info;
    struct no *prox;
} No;

typedef struct lista {
    No *inicio;
} Lista;

Lista* CriaLista()
{
    Lista *aux;
    aux=(Lista *)malloc(sizeof(Lista));
    aux->inicio = NULL;
    return aux;
}
int busca(Lista *L, int num)
{
    No *aux = L -> inicio;
    while(aux!=NULL){
        if(aux -> info.CodigoDeSolicitacao == num ){
            return 1;
        }
        aux = aux -> prox;
    }
    return 0;
}

int LeCodigo(Lista *L) {
    int codigoQuatro = 0;
    while (codigoQuatro < 1000 || codigoQuatro > 9999 || busca(L, codigoQuatro) == 1) {
        printf("Escreva um codigo de quatro digitos: ");
        scanf("%d", &codigoQuatro);
        if (codigoQuatro < 1000 || codigoQuatro > 9999) {
            printf("Numero invalido.\n");
        }
        else if (busca(L, codigoQuatro) == 1) {
            printf("Este codigo ja esta em uso\n");
        }
    }
    return codigoQuatro;
}


void insereCodigo(Lista *L, Solicitacao novaSolicitacao) {
    No *novo = (No*)malloc(sizeof(No));
    novo -> info = novaSolicitacao;
    novo -> prox = NULL;

    if (L -> inicio == NULL || L -> inicio -> info.CodigoDeSolicitacao >= novaSolicitacao.CodigoDeSolicitacao) {
        novo -> prox = L -> inicio;
        L -> inicio = novo;
        return;
    }

    No *atual = L->inicio;
    while (atual -> prox != NULL && atual -> prox -> info.CodigoDeSolicitacao < novaSolicitacao.CodigoDeSolicitacao) {
        atual = atual -> prox;
    }
    novo -> prox = atual -> prox;
    atual -> prox = novo;
}

void imprimeSolicitacao(Solicitacao *s) {
    printf("Codigo: %d\n", s->CodigoDeSolicitacao);
    printf("Equipamento: %s\n", s->CodigoEquipamentos);
    printf("Nome: %s\n", s->nome);
    printf("Prioridade: %d\n", s->prioridade);
    printf("Periodo (dias): %d\n", s->periodo);
}

No *BuscaLista(Lista *L, int cod) {
    No *aux = L->inicio;
    while (aux != NULL && aux->info.CodigoDeSolicitacao != cod) {
        aux = aux->prox;
    }
    return aux;
}

void imprimirinformacao(Lista *L, int valor) {
    No *encontrado = BuscaLista(L, valor);
    if (encontrado != NULL) {
        imprimeSolicitacao(&encontrado->info);
    } else {
        printf("Solicitacao com codigo %d nao encontrada.\n", valor);
    }
}

void imprimir(Lista *L) {
    No *aux = L->inicio;
    while (aux != NULL) {
        imprimeSolicitacao(&aux->info);
        aux = aux->prox;
    }
}

Solicitacao preencher(int codigoQuatro){
    Solicitacao atual;
    atual.CodigoDeSolicitacao = codigoQuatro;
    while (getchar() != '\n');
    printf("Qual o nome do equipamento?");
    fgets(atual.nome, 20, stdin);
    atual.nome[strcspn(atual.nome, "\n")] = '\0';

    int flag = 0;
    while (flag == 0) {
        printf("Codigo do Equipamento (Ex: OSC023): ");
        scanf("%6s", atual.CodigoEquipamentos);
        while (getchar() != '\n');

        flag = 1;
        for (int i = 0; i < 3; i++) {
            if (!isalpha(atual.CodigoEquipamentos[i])) {
                flag = 0;
            }
        }

        for (int i = 3; i < 6; i++) {
            if (!isdigit(atual.CodigoEquipamentos[i])) {
                flag = 0;
            }
        }

        if (flag == 0) {
            printf("Codigo invalido! Use 3 letras e 3 numeros.\n");
        }
    }

    atual.prioridade = 0;
    while (atual.prioridade < 1 || atual.prioridade > 3) {
        printf("Qual a prioridade?");
        scanf("%d",&atual.prioridade);
        switch (atual.prioridade) {
            case 1:
            case 2:
            case 3:
                break;
            default:
                printf("Digite uma prioridade de 1 a 3\n");
        }
    }
    flag = 0;
    while (flag == 0) {
        printf("Qual o periodo?");
        scanf("%d",&atual.periodo);
        switch (atual.prioridade) {
            case 1:
                if (atual.periodo >= 1 && atual.periodo <= 7) {
                    flag = 1;
                }
                break;
            case 2:
                if (atual.periodo >= 1 && atual.periodo <= 15) {
                    flag = 1;
                }
                break;
            case 3:
                if (atual.periodo >= 1 && atual.periodo <= 20) {
                    flag = 1;
                }
                break;
        }
        if (flag == 0) {
            printf("Periodo invalido para a prioridade %d. Tente novamente.\n", atual.prioridade);
        }
    }
    return atual;
}

void alterarSolicitacao(Lista *L) {
    int cod, novaPrioridade, novoPeriodo, limite;
    No *encontrado = NULL;

    do {
        printf("Digite o codigo da solicitacao que deseja alterar (0 para cancelar): ");
        scanf("%d", &cod);

        if (cod == 0) {
            printf("Alteracao cancelada.\n");
            return;
        }

        encontrado = BuscaLista(L, cod);
        if (encontrado == NULL) {
            printf("Solicitacao com codigo %d nao encontrada. Tente novamente.\n", cod);
        }
    } while (encontrado == NULL);

    do {
        printf("Nova prioridade (1 a 3): ");
        scanf("%d", &novaPrioridade);
        switch (novaPrioridade) {
            case 1:
                limite = 7;
                break;
            case 2:
                limite = 15;
                break;
            case 3:
                limite = 20;
                break;
            default:
                limite = 0;
                printf("Prioridade invalida! Digite uma prioridade de 1 a 3.\n");
        }
    } while (limite == 0);

    do {
        printf("Novo periodo (1 a %d dias): ", limite);
        scanf("%d", &novoPeriodo);
        if (novoPeriodo < 1 || novoPeriodo > limite) {
            printf("Periodo invalido para a prioridade %d. Tente novamente.\n", novaPrioridade);
        }
    } while (novoPeriodo < 1 || novoPeriodo > limite);

    encontrado->info.prioridade = novaPrioridade;
    encontrado->info.periodo = novoPeriodo;

    printf("\nSolicitacao alterada com sucesso!\n");
    imprimeSolicitacao(&encontrado->info);
}

void removerSolicitacao(Lista *L, int codigoQuatro) {
    if (L->inicio == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }
    No *aux1 = L->inicio;
    No *aux2 = NULL;
    while (aux1 != NULL && aux1->info.CodigoDeSolicitacao != codigoQuatro) {
        aux2 = aux1;
        aux1 = aux1->prox;
    }
    if (aux2 == NULL) {
        L->inicio = aux1->prox;
    } else {
        aux2->prox = aux1->prox;
    }

    free(aux1);
    printf("Solicitacao removida \n");
}

int vemAntes(No *novo, No *atual) {
	if (novo->info.periodo < atual->info.periodo) {
		return 1;
	}
	if (novo->info.periodo == atual->info.periodo) {
		if (novo->info.CodigoDeSolicitacao < atual->info.CodigoDeSolicitacao) {
			return 1;
		}
	}
	return 0;
}

void insereOrdemManutencao(Lista *L, Solicitacao s) {
	No *novo;
	No *atual;
	No *anterior;

	novo = (No*)malloc(sizeof(No));
	novo->info = s;
	novo->prox = NULL;

	if (L->inicio == NULL) {
		L->inicio = novo;
		return;
	}

	anterior = NULL;
	atual = L->inicio;

	for (; atual != NULL; atual = atual->prox) {
		if (vemAntes(novo, atual) == 1) {
			break;
		}
		anterior = atual;
	}

	if (anterior == NULL) {
		novo->prox = L->inicio;
		L->inicio = novo;
		return;
	}

	novo->prox = atual;
	anterior->prox = novo;
}

void liberaLista(Lista *L) {
	No *aux;
	No *temp;

	aux = L->inicio;
	for (; aux != NULL; ) {
		temp = aux;
		aux = aux->prox;
		free(temp);
	}
	free(L);
}

void ordemManutencao(Lista *L) {
	Lista *lista1;
	Lista *lista2;
	Lista *lista3;
	Lista *listaAtual;
	No *aux;
	int i;

	if (L->inicio == NULL) {
		printf("A lista esta vazia.\n");
		return;
	}

	lista1 = CriaLista();
	lista2 = CriaLista();
	lista3 = CriaLista();

	for (aux = L->inicio; aux != NULL; aux = aux->prox) {
		switch (aux->info.prioridade) {
			case 1:
				insereOrdemManutencao(lista1, aux->info);
				break;
			case 2:
				insereOrdemManutencao(lista2, aux->info);
				break;
			case 3:
				insereOrdemManutencao(lista3, aux->info);
				break;
		}
	}

	printf("Ordem de manutencao\n");

	for (i = 1; i <= 3; i++) {
		switch (i) {
			case 1:
				printf("\nPrioridade 1 - Alta\n");
				listaAtual = lista1;
				break;
			case 2:
				printf("\nPrioridade 2 - Media\n");
				listaAtual = lista2;
				break;
			case 3:
				printf("\nPrioridade 3 - Baixa\n");
				listaAtual = lista3;
				break;
		}
		if (listaAtual->inicio == NULL) {
			printf("Nenhuma solicitacao.\n");
		}
		imprimir(listaAtual);
	}

	liberaLista(lista1);
	liberaLista(lista2);
	liberaLista(lista3);
}

#endif
