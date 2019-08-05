#include <iostream>
#include <cstring>
using namespace std;

long int TamArq(string name_arq)
{
    FILE *arq = fopen(name_arq.c_str(), "r");
    long int tam = 0;
    if(arq != NULL)
    {
        fseek(arq, 0, SEEK_END);
        tam = ftell(arq);
    }
    fclose(arq);
    return tam;
}

char *ReadFile(string nome_arq, long int tam)
{
    char *str = new char[tam];
    if(tam > 0)
    {
        FILE *arq = fopen(nome_arq.c_str(), "r");
        for (long int i = 0; i < tam; i++)
        {
            char aux;
            fscanf(arq, "%c", &aux);
            aux = tolower(aux);
            if(aux != '\n')
                str[i] = aux;
        }
        fclose(arq);
    }
    return str;
}

void WriteFile(string nome_arq, char* str, long int tam)
{
    if(tam > 0)
    {
        FILE *arq = fopen(nome_arq.c_str(), "w");
        for (long int i = 0; i < tam; i++)
        {
            fprintf(arq, "%c", str[i]);
        }
        fclose(arq);
    }
}

void Desloca(char *alf)
{
    char aux = alf[25];
    for(int i=25; i > 0; i--)
        alf[i] = alf[i-1];
    alf[0] = aux;
}

void DescolaAlfabeto(char *alf, int cod)
{
    if(cod > 0)
    for(int i=0; i < cod; i++)
        Desloca(alf);
}

int PosicaoLetra(char* alf, char c)
{
    int i;
    for(i=0; i<25; i++)
        if(c == alf[i])
            return i;
    return -1;
}

void Criptografa(char *text, char* alf, long int tam)
{
    char aux[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    for(long int i=0; i< tam; i++)
    {
        int p = PosicaoLetra(alf, text[i]);
        if(p >= 0) text[i] = aux[p];
        else text[i] = ' ';
    }
}

void Descriptografa(char *text, char* alf, long int tam)
{
    char aux[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    for(long int i=0; i < tam; i++)
    {
        int p = PosicaoLetra(aux, text[i]);
        if(p >= 0) text[i] = alf[p];
        else text[i] = ' ';   
    }
}

void help()
{
    cout << endl << "           Cifra de Cesar - HELP" << endl << endl;
    cout << "       ./cesar cod arq.in op arq.out" << endl << endl;
    cout << "   cod              -> Valor de deslocamento" << endl;
    cout << "   arq.in e arq.out -> arquivos de entrada e saída" << endl;
    cout << "   op               -> 1 para criptografar e 0 para descriptografar" << endl << endl;
}

int main(int argc, char *argv[])
{
    char alf[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int cod, op;

    string arq, arq_out;
    char *text;

    if(argc == 5)
    {
        cod = atoi(argv[1]);
        arq = argv[2];
        op = atoi(argv[3]);
        arq_out = argv[4];

        if(cod >= 0)
        {
            long int tam = TamArq(arq);
            text = ReadFile(arq, tam);

            DescolaAlfabeto(alf, cod);

            cout << "Original: " << endl;
            cout << text << endl;
            
            if(op == 0)
                Criptografa(text, alf, tam);
            else
                Descriptografa(text, alf, tam);
            
            WriteFile(arq_out, text, tam);

            cout << endl << "Porcessado: " << endl;
            cout << text << endl;

            cout << endl << "Palavras: " << tam << endl;
            
        }
    }
    else 
    {
        help();
    }
    return 0;
}