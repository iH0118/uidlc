#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "uib_application.h"
#include "uib_structs.h"
#include "uidl_application.h"
#include "uidlc.h"

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
        exit(1);
    }

    input_filename = argv[optind++];

    if (optind < argc)
    {
        fputs("error: too many arguments\n", stderr);
        exit(1);
    }

    FILE *infile = fopen(input_filename, "r");
    if (!infile)
    {
        fprintf(stderr, "error: input file \"%s\" not found\n", input_filename);
        exit(1);
    }

    fseek(infile, 0L, SEEK_END);
    int infilesize = ftell(infile);
    rewind(infile);
    char *infile_text = malloc(infilesize);
    fread(infile_text, sizeof(char), infilesize, infile);
    fclose(infile);

    char *token = infile_text;

    uib_application_struct_t *application;
    uidlc_return_t status = uidl_parse_application_struct(&token, &application);

    uidlc_report_status(status);

    free(infile_text);

    FILE *outfile = fopen(output_filename, "w");
    if (!outfile)
    {
        fprintf(stderr, "error: could not write to \"%s\"\n", output_filename);
        exit(1);
    }

    fputs("UIB", outfile);
    status = uib_output_application_struct(outfile, application);

    uidlc_report_status(status);

    return 0;
}