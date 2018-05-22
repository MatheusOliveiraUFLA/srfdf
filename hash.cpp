#include <iostream>
#include <string.h>

using namespace std;

const int primo = 5;

int funcaoHash(int chave, int capacidade){
	long h=0;
	h=(primo+ chave)%capacidade;
	return h;
}

class noh{
	friend class tabelaHash;
	public:
		noh(){
			id = -1;
			nome[0] = '%';
			tipo[0] = '%';
			estado[0] = '%';
			descricao[0]='%';
			populacao = -1;
			}
	private:
		int populacao;
		int id;
		char nome[50];
		char tipo[20];
		char estado[30];
		char descricao[200];
		noh* proximo = NULL;
	
	};
	
class tabelaHash{
	public:
		tabelaHash(int cap=100);
		~tabelaHash();
		void insere(char n[], char t[], char e[], char d[], int _id, int p);
		void percorre();
		int recupera(int _id);
		void altera(char n[], char t[], char e[], char d[], int _id, int p);
		private:
			noh** elementos;
			int capacidade;
	
	};
	
tabelaHash::tabelaHash(int cap){
    elementos = new noh*[cap];
    capacidade=cap;
    for(int i=0; i<cap; i++)
        elementos[i]=NULL;
}

tabelaHash::~tabelaHash(){
    for (int i = 0; i < capacidade; i++){
        noh* atual = elementos[i];
        while(atual != NULL){
            noh* aux=atual;
            atual=atual->proximo;
            delete aux;
        }
    }
    delete[] elementos;   
}

	
void tabelaHash::insere(char n[], char t[], char e[], char d[], int _id,int p){
		int h;
		h=funcaoHash(_id,capacidade);
		if(recupera(_id)==-1){
			if (elementos[h]==NULL)
			{
				elementos[h]= new noh;
				strcpy(elementos[h]->nome,n);
				strcpy(elementos[h]->tipo,t);
				strcpy(elementos[h]->estado,e);
				strcpy(elementos[h]->descricao,d);
				elementos[h]->id=_id;
				elementos[h]->populacao=p;
				
			}
			else
			{
				noh* atual = elementos[h];
				while (atual->proximo!=NULL){
					atual = atual->proximo;
				}
				noh* novo = new noh;
				strcpy(novo->nome,n);
				strcpy(novo->tipo,t);
				strcpy(novo->estado,e);
				strcpy(novo->descricao,d);
				novo->id=_id;
				novo->populacao=p;
				atual->proximo=novo;
	}
	
	}
		else
		{
			cout << "Valor já existe na Tabela" << endl;
		}
		
	}
	
int tabelaHash::recupera(int _id){
    int h;
    h=funcaoHash(_id,capacidade);
    if((elementos[h] != NULL) and (elementos[h]->id==_id))
        return 0;
    else{
        noh* atual = elementos[h];
        while((atual != NULL) and (atual->id !=_id))
            atual = atual->proximo;
        if((atual != NULL) and (atual->id ==_id))
            return 0;
        else{
            return -1;}
    }
}
	
void tabelaHash::percorre(){
	noh* atual;
	for (int i = 0; i <capacidade ; i++){
		cout<<i<<":";
		atual= elementos[i];
		while(atual != NULL){
			cout<<"Nome: "<< atual->nome<<" Tipo: "<< atual->tipo<<" Estado: " << atual->estado << " Descricao: " << atual->descricao << endl;
			atual=atual->proximo;
		}
		cout<<"NULL " << endl;
	}
	
}

void tabelaHash::altera(char n[], char t[], char e[], char d[], int _id, int p){

    int h=funcaoHash(_id,capacidade);
    
    if((elementos[h]!= NULL) and (elementos[h]->id==_id)) {
			strcpy(elementos[h]->nome,n);
			strcpy(elementos[h]->tipo,t);
			strcpy(elementos[h]->estado,e);
			strcpy(elementos[h]->descricao,d);
			elementos[h]->id=_id;
			elementos[h]->populacao=p;
	}
	else{
		noh* atual= elementos[h];
		while ((atual != NULL)and (atual->id != _id)){
			atual= atual->proximo;
		}
		if ((atual!=NULL)and (atual->id == _id)){
				strcpy(atual->nome,n);
				strcpy(atual->tipo,t);
				strcpy(atual->estado,e);
				strcpy(atual->descricao,d);
				atual->id=_id;
				atual->populacao=p;}
		else
			cerr<<"ERRO NA ALTERAÇÃO!"<<endl;
		
	}
}


	
	

	
int main(){
	tabelaHash th(16);
	char n[50];
	char t[20];
	char e[30];
	char d[200];
	int _id;
	int p;
	int tam;
	cin >> tam;
	
	for (int i = 0; i < tam; i++){
		cin >> n >> t >> e >> d >> _id >> p;
		th.insere(n,t,e,d,_id,p);
	}
	th.percorre();
	cin >> n >> t >> e >> d >> _id >> p;
	th.altera(n,t,e,d,_id,p);
	
	
	
	th.percorre();
}
