#include <stdio.h>
#include <stdlib.h>

#include "adjlist.h"

int main(int argc, char **argv)
{
    //  Abre o arquivo de entrada
    FILE *outfile = NULL;
    if(argc == 2)
        outfile = stdout;
    else if(argc == 3)  {
        outfile = fopen(argv[2], "w");
        if(outfile == NULL) {
            fprintf(stderr, "Erro ao criar o arquivo de saída.\n");
            return 1;
        }
    }
    else    {
        fprintf(stderr, "Utilização:\n\t./executavel entrada.txt saida.txt\n");
        return 1;
    }
    FILE *infile = fopen(argv[1], "r");
    if(infile == NULL)  {
        fprintf(stderr, "Erro ao abrir arquivo de entrada.\n");
        return 1;
    }

    //  Gera o grafo recebido no arquivo de entrada
    Graph *g = recvOriginGraph(infile);
    fclose(infile);
    infile = NULL;
    
    //  Gera a arvore minima e escreve no arquivo de saida
    PrimMST(g, outfile);
    if(outfile != stdout)
        fclose(outfile);
    
    return 0;
}

