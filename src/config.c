#include "config.h"

int parse_ini_file(char * ini_name)
{
    config = malloc(sizeof (Config));
    
    config->ini = iniparser_load(ini_name);

    if (config->ini==NULL) {
        printf("Cannot parse file: %s\n", ini_name);
        return EXIT_FAILURE;
    }

    printf("Loading config...\n");

    config->device              = iniparser_getstring(config->ini, "device:name", NULL); 
    config->event_file          = iniparser_getstring(config->ini, "device:eventfile", NULL); 
    config->command_template    = iniparser_getstring(config->ini, "shell:command", NULL); 

    config->command = malloc(strlen(config->command_template) + 32 * sizeof(char));

    return EXIT_SUCCESS;
}
