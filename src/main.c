#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

const char *helpmsg = "uidlc - the uidl bytecode compiler\n"
    "usage:\nuidlc [-h] [-o <outfile>] <infile>\n";

int 
main (
    int argc,
    char **argv
)
{
    char *input_filename;
    char *output_filename = "out.uib";

    int c;

    while ((c = getopt (argc, argv, "ho:")) != -1) switch (c) 
    {
        case 'h':
        fputs(helpmsg, stderr);
        exit(0);
        break;

        case 'o':
        output_filename = optarg;
        break;

        case '?':
        fputs(helpmsg, stderr);
        exit(1);
        
        default:
        abort();
    }

    if (optind >= argc)
    {
        fputs("error: missing input file\n", stderr);
        return 1;
    }

    input_filename = argv[optind++];

    if (optind < argc)
    {
        fputs("error: too many arguments\n", stderr);
        return 1;
    }

    FILE *infile = fopen(input_filename, "w");
    
    if (!infile)
    {
        fputs("error: input file not found", stderr);
        return 1;
    }







}