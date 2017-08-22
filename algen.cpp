#include <bits/stdc++.h>

using namespace std;

#define tam_pop 100
#define taxa_cross 100
typedef struct individuo {
	int nota, dna[10]; // o individuo possui nota (fit) e a solucao (vetor de int) 
} individuo;

void avalia_ind ( individuo *x ){ // agrega nota ao individuo
	int send = x->dna[0]*1000+x->dna[1]*100+x->dna[2]*10+ x->dna[3];
	int more = x->dna[5]*1000+x->dna[6]*100+x->dna[7]*10+x->dna[1];
	int money = x->dna[5]*10000+x->dna[6]*1000+x->dna[2]*100+x->dna[1]*10+x->dna[4];
	x->nota = abs (send + more - money); 		
}

int ja_existe ( individuo r[tam_pop] , individuo x , int num){	
	for ( int y=0; y<num; y++){
		if(r[y].nota == x.nota ){ // verifica primeiro pela nota para ganhar tempo
			int y=0;
			for ( int e=0; e<10; e++){
				if(r[y].dna[e]!=x.dna[e]) y++;	// verifica o vetor 
			}
			if (!y) return 1; 
		}
	}
	return 0;
} 

int torneio ( individuo r[tam_pop] ){
	int u1 = rand()%tam_pop, u2 = rand()%tam_pop, u3 = rand()%tam_pop ;
	if ( r[u1].nota >= r[u2].nota &&  r[u1].nota >= r[u3].nota ) return u1;
	if ( r[u1].nota <= r[u2].nota && r[u3].nota <= r[u2].nota ) return u2;
	return u3;
}

void cruzamento ( individuo pais[tam_pop], int news, individuo filhos[tam_pop] ){	
	for (int y=0; y<news; y++){
		int a1=torneio(r), a2=torneio(r);	
		while( a1!=a2 ) a1=torneio(r); //sorteandos os pais 
		int ind=rand()%10; // indice para comecar o crossover
		individuo f1, f2;
		int p[10], i=0;
		for ( int o =0; o<10;o++){
			f1.dna[o]=r[a1].dna[o];
			f2.dna[o]=r[a2].dna[o];
		}
		while ( 
		
	}
	
}

void gera_pop ( individuo r[tam_pop] ){ // gera a populacao inicial 
	for ( int y=0; y<tam_pop; y++){
		memset( r[y].dna, -1, sizeof(r[y].dna)); // "limpa" o individuo 
		for ( int i=0; i<10; i++){
			while ( true ) {
				int u = rand()%10;
				if ( r[y].dna[u]==-1){
					r[y].dna[u]=i;	// gera a aleatoriedade do individuo
					break;
				}
			}
		}	
		avalia_ind ( &r[y] ); // avalia cada individuo
		y=y-ja_existe(r, r[y], y); // se o individuo ja existir gera um novo
	}	
}



void mostra_pop ( individuo r[tam_pop]){ // funcao de controle apenas para mostrar a populacao
	for ( int i =0; i< tam_pop; i++){
		printf ("Individuo %d:\n", i+1);	
		for ( int y=0; y<10; y++){
			printf ("%d ",r[i].dna[y]); // mostra o dna
		}
		printf ("\n%d\n", r[i].nota); // mostra a nota
	}
}


int main (){
	individuo populacao[tam_pop];
	printf ("O vetor de DNA esta organizado da seguinte forma : S E N D Y M O R * * \n");
	printf ("Os * nao representam nada, apenas facilita a execucao dos algoritmos. \n");
	srand( (unsigned)time(NULL) ); // inicializa o rand()
	gera_pop(populacao);
	mostra_pop(populacao);
}
