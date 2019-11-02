#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
 
typedef struct codelist CodeList; 
 
struct codelist{ 
     int n;
     CodeList *prox;
};

CodeList *cria_listaCL(void){
	CodeList *l = (CodeList*) malloc (sizeof(CodeList));
	l = NULL;
	return l;
}

CodeList *insereCL(CodeList *cList, int num)
{
     CodeList *aux;
     aux = (CodeList*)malloc(sizeof(CodeList));
     aux -> n = num;
     aux -> prox = cList;
     return aux;
}

int comparar(char *palavra){
	int i;
	char *palavras[] = {"principal()", "escreva()", "testar()", "repetir()", "ler()", "verdadeiro" , "falso", "caracter", "real", "inteiro"};
	
	for(i = 0; i < 10; i++){
		if((strcmp(palavra, palavras[i])) == 0 ){		
			return 1;
			break;
		}
	}		
}

void validaCaracter(CodeList *cLista){
    CodeList *meio, *fim = cLista; //listas auxiliares
    char c;
    char *linha = (char*)malloc(100);
    memset(linha,0,100);
      
    while (fim -> prox != NULL){ //percorre ate o final da lista
		fim = fim -> prox;
	}
    
    while (meio != fim){ //enquanto a lista nao chegar ao final
    	if(meio -> prox == fim){ 
    		if(fim -> n >= 32 && fim -> n <= 126){ //verifica se o caracter atual pertence a tabela ASCII
    				printf(" %c  OK\n", fim -> n);
    				c = (char) fim -> n;
				if(c != '{' && c != ' '){
					sprintf(linha, "%s%c", linha, c);
				}else if(fim -> n == 32){
					if(comparar(linha) == 1){
						printf(" Palavra valida: %s \n", linha);
						memset(linha,0,100);
					}else{
						printf("Palavra invalida: %s \n", linha);
						memset(linha,0,100);
					}
				}				    				
				fim = meio;
     			meio = cLista;
			}else{
				if(fim -> n == 10 || fim -> n == 13){
				printf(" %c  Quebra de linha\n", fim -> n);	
					if(comparar(linha) == 1){
						printf(" Palavra valida: %s \n", linha);
						memset(linha,0,100);
					}else{
						printf("Palavra invalida: %s \n", linha);
						memset(linha,0,100);
					}					
				fim = meio;
     			meio = cLista;     			
     		}else{
     			sprintf(linha, "%s%c", linha, c);
     			printf(" %c  X\n", fim -> n);
				fim = meio;
     			meio = cLista;
				}				
			}
		}else meio = meio -> prox;
	}
}
 
int main()
{ 
    int num;
    CodeList *listaC= (CodeList*) malloc(sizeof(CodeList));	
    listaC = cria_listaCL();
    FILE *codigo;
    codigo = fopen("teste.txt","r"); 
    
    //Lista de caracter
    if (codigo){ //se o arquivo é valido
          do{
               fscanf(codigo,"%c", &num);  //recebe cada caracter do arquivo em código ASCII
               listaC = insereCL(listaC, num); //insere na lista
          }while(!feof(codigo));  //enquanto existe caracter no arquivo
	}      
    
    validaCaracter(listaC);
    fclose(codigo);
    system("pause");
}
