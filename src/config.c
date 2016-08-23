#include "config.h"

int parse_ini_file(char * ini_name)
{
    config = malloc(sizeof (Config));
    
    config->config_file = (char*)malloc(1024 * sizeof(char));
    config->config_file[0] = '\0';

    if(getcwd(config->config_file, 1024) == NULL){
       fprintf(stderr,"getcwd() error\n");
       return EXIT_FAILURE;
    }

    strcat(config->config_file, ini_name);

    config->ini = iniparser_load(config->config_file);

    if (config->ini==NULL) {
        fprintf(stderr,"Cannot parse file: %s\n", ini_name);
        return EXIT_FAILURE;
    }

    printf("Loading config...\n");

    config->device              = iniparser_getstring(config->ini, "device:name", NULL); 
    config->event_file          = iniparser_getstring(config->ini, "device:eventfile", NULL); 
    config->command_template    = iniparser_getstring(config->ini, "shell:command", NULL); 

    config->command = (char*)malloc(strlen(config->command_template) + (32 * sizeof(char)));

    return EXIT_SUCCESS;
}
