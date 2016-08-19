
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/types.h>
#include <linux/kd.h>

#include "config.h"

int main(int argc, char* argv[])
{
    int     file_desc   = -1;
    int     result      = 0;
    char    digit       = 0;
    char    *output;

    struct  input_event ev[64];

    if(parse_ini_file("config.ini", config) == EXIT_FAILURE){
        printf("Missing config file,\nCopy config->ini.example as config->ini\n");
        return EXIT_FAILURE;
    }

    file_desc = open(config->event_file, O_RDONLY);
    if (file_desc == -1) {
        printf("Failed to open event device.\nTry again, with \"sudo\"\n");
        return EXIT_FAILURE;
    }

    printf ("Reading From : %s (%s)\n", config->event_file, config->device);

    printf("Getting exclusive access: ");
    result = ioctl(file_desc, EVIOCGRAB, 1);
    if(result != 0) {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    printf("SUCCESS\n");

    // disable buffering
    //setbuf(stdout, NULL);

    output  = malloc(32 * sizeof(char));

    while (1)
    {
        // if it crashes then break
        if ((read(file_desc, ev, sizeof ev)) < sizeof(struct input_event)) {
            break;
        }

        // if key pressed and released
        if (ev[1].value == 1 && ev[1].type == EV_KEY) {

        // https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/tree/include/uapi/linux/input-event-codes.h
            switch (ev[1].code) {
                case KEY_0:     digit = '0';  break;
                case KEY_1:     digit = '1';  break;
                case KEY_2:     digit = '2';  break;
                case KEY_3:     digit = '3';  break;
                case KEY_4:     digit = '4';  break;
                case KEY_5:     digit = '5';  break;
                case KEY_6:     digit = '6';  break;
                case KEY_7:     digit = '7';  break;
                case KEY_8:     digit = '8';  break;
                case KEY_9:     digit = '9';  break;
                default:        digit = '\0';
            }

            if(digit != '\0'){
                strncat(output, &digit, 1);
            }

            //if enter key is received, read is completed then 
            if(ev[1].code == KEY_ENTER){
                printf("%s\n", output);

                sprintf(config->command, config->command_template, output);
                system(config->command);
                // reset output string
                output[0] = '\0'; 
            }
        }
    }

    // free device file
    result = ioctl(file_desc, EVIOCGRAB, 0);
    close(file_desc);
    return EXIT_SUCCESS;
}
