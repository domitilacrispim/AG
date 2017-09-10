#include <bits/stdc++.h>

using namespace std;
#define geracao 50
#define tam_pop 100
#define taxa_cross 60
#define taxa_mut 10
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
	for ( int y=0; y<=num; y++){
		//printf("%d %d %d\n \n", x.nota, r[y].nota, y);
		if(r[y].nota == x.nota ){ // verifica pela nota para ganhar tempo
			return 0;
		}
	}
	return 1;
}
void mutacao ( individuo r[tam_pop] ){
	for ( int u=0; u<tam_pop; u++){
		int prob = rand()%tam_pop;
		if ( prob <= taxa_mut ) {
			int ind = rand()%tam_pop;
			int r1=rand()%10, aux, r2=rand()%10;
			while(r1==r2) r2=rand()%10;
			aux=r[ind].dna[r1];
			r[ind].dna[r1]=r[ind].dna[r2];
			r[ind].dna[r2]=aux;
			avalia_ind(&r[ind]);
		}
	}

}

int torneio ( individuo r[tam_pop] ){
	int u1 = rand()%tam_pop, u2 = rand()%tam_pop, u3 = rand()%tam_pop ;
	//printf("%d %d %d\n", u1, u2, u3);
	//printf("%d %d %d", r[u1].nota, r[u2].nota, r[u3].nota);
	if ( r[u1].nota <= r[u2].nota &&  r[u1].nota <= r[u3].nota ){
		//printf("->%d\n"	, u1);
		return u1;
	}
	if ( r[u1].nota >= r[u2].nota && r[u3].nota >= r[u2].nota ){
		//printf("->%d\n"	, u2);
		 return u2;
	}
	//printf("->%d\n"	, u3);
	return u3;
}

void cruzamento ( individuo r[tam_pop], double tx, individuo filhos[tam_pop]){
	double aux = (tam_pop*tx)/100.0;
	int news = aux/2.0, tam=0, pais[2][tam_pop];
	for (int y=0; y<news; y++){
		int a1=torneio(r), a2=torneio(r);
		while( a1==a2  ) a1=torneio(r); //sorteandos os pais
		individuo f1, f2;
		//printf("%d %d\n", a1, a2);
		for ( int o =0; o<10;o++){
			f1.dna[o]=r[a1].dna[o];
			f2.dna[o]=r[a2].dna[o];
		}
		int ind=0;
		int vis[10], p=rand()%10, pro[10];
		memset ( vis, 0, sizeof ( vis));
		memset ( pro, 0, sizeof ( pro));
		while(!vis[p]){
			vis [p]=1;
			pro[ind]=f1.dna[p];
			ind++;
			pro[ind]=f2.dna[p];
			for ( int y=0; y<10; y++){
				if(f1.dna[y]==pro[ind] ) { p=y; break; }
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
			f2.dna[re]=abs(f1.dna[re]-10)%10;
			//printf("f1 %d f2 %d\n", f1.dna[re],f2.dna[re]);
		}
		avalia_ind(&f1);
		if(ja_existe(filhos, f1, tam-1)){	 //printf("%d NAO existe\n", ja_existe(filhos, f1, tam-1));
			filhos[tam]=f1;
			tam++;
			filhos[tam]=f2;
			avalia_ind(&filhos[tam]);
			tam++;
		}
		else {
			y--;
		}
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

int reinsercao ( individuo r[tam_pop], individuo t[tam_pop]){
	int y=0, i=0, o1=0, o2=0;
	individuo o[tam_pop];
	while(i<tam_pop){
		if(r[o1].nota==0 || t[o2].nota==0){
			y=1;
		}
		if(r[o1].nota<t[o2].nota ){
			if (  ja_existe(o,r[o1],i-1)){
				o[i]=r[o1]; o1++; i++;
				//printf("1");
			}
			else o1++;
		}
		else {
			if (  ja_existe(o,t[o2],i-1)){
				o[i]=t[o2]; o2++; i++;
				//printf("2");
			}
			else o2++;
		}

	}
	//printf("*****************************\n");
	//	mostra_pop(o);
		for ( int po=0; po<tam_pop; po++){
			r[po]=o[po];
		}
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

int main (){
	individuo populacao[tam_pop], auxs[tam_pop];
	//printf ("O vetor de DNA esta organizado da seguinte forma : S E N D Y M O R * * \n");
	//printf ("Os * nao representam nada, apenas facilita a execucao dos algoritmos. \n");
	srand( (unsigned)time(NULL) ); // inicializa o rand()
    for ( int vezww=0; vezww<1000; vezww++){
	gera_pop(populacao);
	//mostra_pop(populacao);
     clock_t start, stop;
     start = clock();
     double diff; int bugg=0;
	//printf("Entre com o numero de geracoes:\n");
	int ger;
	qsort (populacao,tam_pop, sizeof(individuo), ord_pop);
	//mostra_pop(populacao);
    ger=geracao;
	int tam=0;
	//printf ("--------------------------------\n");
	while(ger){
		tam++;
		cruzamento(populacao, taxa_cross, auxs);
		ger--;
		qsort (auxs, (tam_pop*taxa_cross)/100, sizeof(individuo), ord_pop);
		//mostra_pop(auxs	);
		//printf ("===============================\n");
		int teste=reinsercao(populacao, auxs);
		mutacao(populacao);
		//mostra_pop(populacao);
		//printf ("--------------------------------\n");
		qsort (populacao,tam_pop, sizeof(individuo), ord_pop);
		if( populacao[0].nota==0 ) {
			//printf ( "individuo perfeito encontrado \n");
		//	for ( int idna=0; idna<10; idna++){
			//	printf("%d ", populacao[0].dna[idna]);
			//}
			printf ("%d  ", tam);
            stop = clock();
            diff = difftime( stop,start);
            printf("; %.0lf ; ",diff); bugg=1;
			break;
		}
	}
 stop = clock();
  diff = difftime( stop,start);
  if(!bugg){
    printf("     -1 ; ");
    printf(" %.0lf ; ",diff);
 }
    }
}

