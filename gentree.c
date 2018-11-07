#include <stdio.h>
#include <stdlib.h>

#include "adjlist.h"
#include "treatment.h"

int main(int argc, char **argv)
{
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
    Graph *g = recvOriginGraph(infile);
    fclose(infile);
    infile = NULL;


    printGraph(g, outfile);
