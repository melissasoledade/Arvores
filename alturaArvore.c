#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct No{
	int valor;
	struct No* esq;
	struct No* dir;
}No;

typedef struct Arvore{
	No* raiz;
}Arvore;

/* Cria árvore vazia */

Arvore * cria_arvore(){
	Arvore *nova = (Arvore*)malloc(sizeof(Arvore));
	nova->raiz = NULL;
	return nova;
}

/* Inserção de novo nó */

void insere_no(No* pai, No * n){
	if(pai != NULL){
		if(n->valor <= pai->valor){
			if(pai->esq == NULL){
				pai->esq = n;
			}
			else{
				insere_no(pai->esq, n);
			}
		}
		else{
			if(pai->dir == NULL){
				pai->dir = n;
			}
			else{
				insere_no(pai->dir, n);
			}			
		}
		
	}
	return;
}

void insere(Arvore* A, int v){
	No* novo = (No*)malloc(sizeof(No));
	novo->valor = v;
	novo->esq = NULL;
	novo->dir = NULL;
	
	if(A->raiz == NULL){
		A->raiz = novo;
	}
	else{
		insere_no(A->raiz, novo);
	}
	return;	
}

/* Imprime ordenado - inordem */

void imprime_inordem(No* n){
	if(n != NULL){
    imprime_inordem(n->esq);
	  printf("%d ", n->valor);
	  imprime_inordem(n->dir);
  }
}

void inordem(Arvore* A){
	imprime_inordem(A->raiz);
	return;
}

/* Calcula altura da árvore */

int altura(No* n){
  int esq, dir;

  if(n == NULL){
    return -1;
  }
  else{
    esq = altura(n->esq);
    dir = altura(n->dir);

    if(esq > dir){
      return esq+1;
    }
    else{
      return dir+1;
    }
  }
}

int main(void) {
  Arvore * a1 = cria_arvore();
  int num;

  while(scanf("%d", &num) != EOF){
    insere(a1, num);
  }
	
  printf("%d\n", altura(a1->raiz));

 

  return 0;
}