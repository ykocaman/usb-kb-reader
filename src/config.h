#ifndef _USB_KB_READER_CONFIG_H_
#define _USB_KB_READER_CONFIG_H_

#include "iniparser.h"

typedef struct _config {
    const char *device;
    const char *command_template;
    const char *event_file;
    char *command;
    dictionary  *ini;
} Config;

// Global config variable
Config *config;


#endif
