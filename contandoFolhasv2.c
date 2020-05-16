#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct No{
  char *valor;
  int tam;
  struct No* esq;
  struct No* dir;
}No;

typedef struct Arvore{
  No* raiz;
}Arvore;

/* Função cria uma árvore vazia */
Arvore * cria_arvore(){
	Arvore *nova = (Arvore*)malloc(sizeof(Arvore));
	nova->raiz = NULL;
	return nova;
}

/* Função cria um novo nó com a palavra */
No * cria_no(char *palavra){
  No* novo = (No*)malloc(sizeof(No));
  novo->esq = NULL;
  novo->dir = NULL;
  novo->tam = strlen(palavra) + 1;
  novo->valor = (char*)malloc(novo->tam * sizeof(char));
  
  int i;
  for(i = 0; i < novo->tam-1; i++){
    novo->valor[i] = palavra[i];
  }
  novo->valor[i] = '\0';

  return novo;
}

/* Função insere novo nó na árvore, em ordem alfabética */
void insere_no(No* pai, No * n){
	if(pai != NULL){
		if(strcmp(n->valor, pai->valor) < 0){
			if(pai->esq == NULL){
				pai->esq = n;
			}
			else{
				insere_no(pai->esq, n);
			}
		}
		if(strcmp(n->valor, pai->valor) > 0){
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

void insere(Arvore* A, No* novo){
	//No* novo = (No*)malloc(sizeof(No));
	//strcpy(novo->valor, v);
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

/* Imprime inordem */
void imprime_inordem(No* n){
	if(n != NULL){
    imprime_inordem(n->esq);
	  printf("%s ", n->valor);
	  imprime_inordem(n->dir);
  }
}

void inordem(Arvore* A){
	imprime_inordem(A->raiz);
	return;
}

/* Conta total de nós da árvore */
int contaNos(No *n){
  if(n != NULL){
    return (contaNos(n->esq) + contaNos(n->dir) + 1);
  }
  else{
    return 0;
  }
}

/* Conta total de nós folha da árvore */
int contaFolhas(No *n){
  if(n == NULL){
    return 0;
  }    
  else{
    if(n->esq == n->dir){
      return 1;
    }
    else{
      return contaFolhas(n->esq) + contaFolhas(n->dir);
    }
  }
    
}

int main(void) {  
  char str[1000];
  char *p;
    
 while(fgets(str, 1000, stdin)){ 
  Arvore * a1 = cria_arvore();
  int i;

  for(i = 0; i < strlen(str); i++){    
    str[i] = tolower(str[i]);
  }
   
   p = strtok(str, "\0"); 
   p = strtok(str, "\n");   
   p = strtok(str, " ");

   while(p != NULL){
     No *novo = cria_no(p);
     insere(a1, novo);
     p = strtok(NULL, " ");
   }
   
   /*inordem(a1);
   printf("\n");*/
   printf("%d %d\n", contaFolhas(a1->raiz), contaNos(a1->raiz) - contaFolhas(a1->raiz));
   /*printf("Quantidade de nós: %d\n", contaNos(a1->raiz));
   printf("Quantidade de folhas: %d\n", contaFolhas(a1->raiz));*/
   free(a1);

    
  }

  
  
  return 0;
}
