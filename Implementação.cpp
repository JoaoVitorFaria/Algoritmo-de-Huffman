//Nome: João Vitor de Faria
//Matrícula:2019006030
#include<stdio.h>
#include<stdlib.h>
#include<utility>  
#include<iterator> 
#include<map>
#include <cstring>
#include <queue>
#include<iostream>
using namespace std;

//um map que vai armazenar os caracteres com ocorrencia e suas respectivas frequencias
std::map<char, int> caractEfrequencia;
std::map<char, int>::iterator itr;

//struct que define os nodes da arvore e sua inicializacao
typedef struct node
{
	char caracter;
	int frequencia;
	node *esquerda;
	node *direita;
	node(char caracter, int frequencia)
	{
		esquerda = NULL;
		direita = NULL;
		this->caracter = caracter;
		this->frequencia = frequencia;
	}
} node;

//esse struct define o parametro compare da priority queue
struct retornaFrequencia
{
	//o bool vai retornar qual a maior frequencia
	bool operator()(node* esquerda, node*direita)
	{
		return (esquerda->frequencia > direita->frequencia);
	}
};

//essa funcao percorre a arvore e vai acrescentando 0 ou 1 na string texto
//caso eu vah para um node na esquerda eu acrescento 0
//caso eu vah para um node na direita eu acrescento 1
void contaBits(node* raiz, string bits)
{
	if(!raiz)
		return;
	if(raiz->caracter != '$')
	{
		//aqui eu salvo no me map o caracter e o numero de bits usados para represeta-lo
		caractEfrequencia.insert(std::pair <char,int>(raiz->caracter, bits.length()));
	}
	contaBits(raiz->esquerda, bits + '0');
	contaBits(raiz->direita, bits + '1' );
}

void huffman(char letras[], int frequencia[], int tamanho)
{
	node *esquerda;
	node *direita;
	node *nodeSoma;
	//Declaro uma priority queue e o parametro compare vai indicar se a frequencia do no da esquerda ou direita eh maior
	priority_queue<node*, vector<node*>, retornaFrequencia>arvore;
	//jogo o caractere e sua frequencia para o arvore
	for(int i = 0; i < tamanho; i++)
	{
		arvore.push(new node(letras[i], frequencia[i]));
	}
	//aqui eu começo a juntar os nodes e vou fazer isso enquanto nao chega a um no que possui a soma de todas frequencias
	while(arvore.size() != 1)
	{
		esquerda = arvore.top();
		//printf("\nfrequencia esquerda: %d\n", esquerda->frequencia);
		arvore.pop();
		direita = arvore.top();
		//printf("\nfrequencia direita: %d\n", direita->frequencia);
		arvore.pop();
		//O nodeSoma vai ter a frequencia dos outros nos somados.
		nodeSoma = new node('$', esquerda->frequencia + direita->frequencia);
		nodeSoma->esquerda = esquerda;
		nodeSoma->direita = direita;
		//depois que eu crio o novo node eu jogo ele na arvore para substituir os que ele uniu
		arvore.push(nodeSoma);
	}
	contaBits(arvore.top(), "");
}

int main()
{
	//aqui eu tenho uma variavel que vai contar as ocorrencias dos caracteres, primeiro eu devo zerar todas posicoes
	int contaOcorrenciaCaracteres[95];
	for(int i = 0; i < 95; i++)
	{
		contaOcorrenciaCaracteres[i] = 0;
	}
	//faco leitura da entrada 
	char textoEntrada[5000];
	scanf("%[^\n]", textoEntrada);
	
	//nesse loop eu percorro o texto de entrada e incremento a ocorrencia de cada um
	for(unsigned int  i = 0; i < strlen(textoEntrada); i++)
	{
		contaOcorrenciaCaracteres[textoEntrada[i]-32]++;		
	}
	char caracteresComOcorrencia[5000];
	int frequenciaCaracteresComOcorrencia[5000];
	int contVetorOcorrencia = 0;
	//agora eu percorro o vetor das ocorrencias e salvo em outro vetor só os caracteres que tiveram ocorrencia e sua frequencia
	for(int i = 0; i < 95; i++)
	{
		if(int(contaOcorrenciaCaracteres[i]) > 0)
		{
			//salva os caracteres que tiveram ocorrencia
			caracteresComOcorrencia[contVetorOcorrencia] =(char)i +32;
			//salva a frequencia dos caracteres com ocorrencia
			frequenciaCaracteresComOcorrencia[contVetorOcorrencia] = contaOcorrenciaCaracteres[i];
			contVetorOcorrencia++;
		}
	}
	int numeroTotalBits=0;
	huffman(caracteresComOcorrencia, frequenciaCaracteresComOcorrencia, contVetorOcorrencia);
	
	//essa funcao percorre o map e multiplica a frequencia de cada caracter pela quantidade de bits usados para represeta-lo
	for (itr = caractEfrequencia.begin(); itr != caractEfrequencia.end(); ++itr){
		for (int i=0;i<contVetorOcorrencia;i++){
			if(caracteresComOcorrencia[i]==itr->first){
				numeroTotalBits+=itr->second*frequenciaCaracteresComOcorrencia[i];
			}
		}
	}
	cout<<numeroTotalBits<<endl;
}
