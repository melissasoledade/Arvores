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

Arvore * cria_arvore(){
	Arvore *nova = (Arvore*)malloc(sizeof(Arvore));
	nova->raiz = NULL;
	return nova;
}

void insere_no(No* pai, No * n){
	if(pai != NULL){
		if(n->valor < pai->valor){
			if(pai->esq == NULL){
				pai->esq = n;
			}
			else{
				insere_no(pai->esq, n);
			}
		}
		if(n->valor > pai->valor){
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

void imprime_preordem(No* n){
  if(n != NULL){
    printf("%d ", n->valor);
    imprime_preordem(n->esq);
    imprime_preordem(n->dir);
  }
}

void preordem(Arvore *A){
  imprime_preordem(A->raiz);
  return;
}

void imprime_posordem(No *n){
  if(n != NULL){
    imprime_posordem(n->esq);
    imprime_posordem(n->dir);
    printf("%d ", n->valor);
  }
}

void posordem(Arvore *A){
  imprime_posordem(A->raiz);
  return;
}

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

No* busca_valor(No *n, int k){
  if(n == NULL || n->valor == k){
    return n;
  }
  if(n->valor > k){
    return busca_valor(n->esq, k);
  }
  else{
    return busca_valor(n->dir, k);
  }
}

char * busca(Arvore *A, int k){
  No* n = (No*)malloc(sizeof(No));
  n = busca_valor(A->raiz, k);

  if(n != NULL){
    return "SIM";
  }
  else{
    return "NAO";
  }
}

No* retira_no(No *n, int k){
  if(n == NULL){
    return NULL;
  }
  else if(n->valor > k){
    n->esq = retira_no(n->esq, k);
  }
  else if(n->valor < k){
    n->dir = retira_no(n->dir, k);
  }
  else{
    if(n->esq == NULL && n->dir == NULL){
      free (n);
      n = NULL;
    }
    else if(n->esq == NULL){
      No* p = n;
      n = n->dir;
      free (p);
    }
    else if(n->dir == NULL){
      No* p = n;
      n = n->esq;
      free (p);
    }
    else{
      No* p = n->esq;
      while (p->dir != NULL) {        
        p = p->dir;
      }
      n->valor = p->valor; 
      p->valor = k;
      n->esq = retira_no(n->esq,k);
    }
  }
  return n;
}

No * retira(Arvore *A, int k){
  No* n = retira_no(A->raiz, k);
  return n;
}


int main(void) {
  Arvore * a1 = cria_arvore();
  Arvore * a2 = cria_arvore();
  char oper;
  int num;

  while(scanf("%c", &oper) != EOF){
    if(oper == 'I'){
      scanf("%d", &num);
      insere(a1, num);
    }
    if(oper == 'P'){
      preordem(a1);
      printf("\n");
    }
    if(oper == 'S'){
      posordem(a1);
      printf("\n");
    }
    if(oper == 'N'){
      inordem(a1);
      printf("\n");
    }
    if(oper == 'H'){
      printf("%d\n", altura(a1->raiz));
    }
    if(oper == 'B'){
      scanf("%d", &num);
      printf("%s\n", busca(a1, num));
    }
    if(oper == 'R'){
      scanf("%d", &num);
      a1->raiz = retira(a1, num);
    }
  }

  free(a1);
  free(a2);
 

  return 0;
}