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

void cruzamento ( individuo r[tam_pop], double tx, individuo filhos[tam_pop]){
	double aux = (tam_pop*tx)/100.0;
	int news = aux, tam=0;
	for (int y=0; y<news; y++){
		int a1=torneio(r), a2=torneio(r);	
		while( a1!=a2 ) a1=torneio(r); //sorteandos os pais 
		int ind=rand()%10; // indice para comecar o crossover
		individuo f1, f2;
		for ( int o =0; o<10;o++){
			f1.dna[o]=r[a1].dna[o];
			f2.dna[o]=r[a2].dna[o];
		}
		int vis[10], p= rand()%10, pro[10];
		memset ( vis, 0, sizeof ( vis));
		while(!vis[p]){	
			vis [p]=1;
			pro[ind]=f1.dna[p];
			ind++;
			pro[ind]=f2.dna[p];
			for ( int y=0; y<10; y++){
				if(f1.dna[p]==pro[ind] ) { p=y; break; }
			}
		}  // achou o ciclo de repeticao entre os vetores 
		for ( int re=0; re<10; re++){ // mudar os numeros
			if( vis[re] && p	 ) {
				for ( int o=0; o<=ind; o++){
					if(f1.dna[re]==pro[o]){
						if( o==ind ) f1.dna[re]=pro[0];
						else f1.dna[re]=pro[o]; 				
					}
				}
			}
		}
		
		filhos[tam]=f1;
		avalia_ind(&filhos[tam]);
		tam++;
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

int reinsercao ( individuo r[tam_pop], individuo t[tam_pop]){
	int y=0, o1=0, o2=0;
	individuo o[tam_pop];
	for ( int i=0; i<tam_pop; i++){
		if(r[o1].nota<t[o2].nota) {
			o[i]=r[o1];	
			if(r[o1].nota==0) y=1;	
			o1++;
		}  
		else {
			o[i]=r[o2];	
			if(t[o2].nota==0) y=1;	
			o2++;
		}
	}
	r=o;
	return y;
}
int ord_pop (const void * a , const void * b) {
	individuo h;
	individuo g;
	h=*(individuo*)a;
	g=*(individuo*)b;
	if (h.nota<g.nota){
		return -1;
	}
	else{
		return 1;
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
	individuo populacao[tam_pop], auxs[tam_pop];
	printf ("O vetor de DNA esta organizado da seguinte forma : S E N D Y M O R * * \n");
	printf ("Os * nao representam nada, apenas facilita a execucao dos algoritmos. \n");
	srand( (unsigned)time(NULL) ); // inicializa o rand()
	gera_pop(populacao);
	mostra_pop(populacao);
	printf("Entre com o numero de geracoes:\n");
	int ger;
	scanf ("%d", &ger);
	while(ger){
		cruzamento(populacao, 100, auxs);
		ger--;
		qsort (auxs, tam_pop, sizeof(individuo), ord_pop);  
		qsort (populacao,tam_pop, sizeof(individuo), ord_pop);  
		int teste=reinsercao(populacao, auxs);
		mostra_pop(populacao);
		printf ("--------------------------------\n");
		mostra_pop(auxs	);
		if( teste ) { printf ( "individuo perfeito encontrado \n"); return 0; }	
	}	
	printf ("Nao deu :( \n");
}
