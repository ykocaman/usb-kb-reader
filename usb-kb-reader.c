#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/types.h>
#include <linux/kd.h>

int main(int argc, char* argv[])
{
    int     fd          = -1;
    int     result      = 0;
    int     rd          = 0;
    char     digit      = 0;

    char    output  [32];
    char    name    [256]   = "Unknown";
    char    device  [256];

    struct  input_event ev[64];

    if(argc > 1){
        strcpy(device,argv[1]);
    }else{
        printf("Missing parameter, give a event file as parameter, \nex: usb-kb-reader /dev/input/event14\n");
        printf("\n\e[38;5;196mAvailable keyboard inputs:\n");
        printf("\e[0mgrep -E 'Name|Handlers|EV' /proc/bus/input/devices | grep 'EV=120013' -B2\n");
        printf("\n\e[38;5;196mExample usage of USB Reader with Keyboard:\n");
        printf("\e[0musb-kb-reader /dev/input/$(grep -E 'Name|Handlers|EV' /proc/bus/input/devices | grep 'EV=120013' -B2 | grep 'Reader' -A2 | grep -Eo 'event[0-9]+')\n\n");

        return 0;
    }

    fd = open(device, O_RDONLY);
    if (fd == -1) {
        printf("Failed to open event device.\nTry again, with \"sudo\"\n");
        return EXIT_FAILURE;
    }

    ioctl ( fd, KDSKBMODE, K_MEDIUMRAW);

    result = ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf ("Reading From : %s (%s)\n", device, name);

    printf("Getting exclusive access: ");
    result = ioctl(fd, EVIOCGRAB, 1);
    if(result != 0) {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    printf("SUCCESS\n");

    // disable buffering
    //setbuf(stdout, NULL);

    while (1)
    {
        // if it crashes then break
        if ((rd = read(fd, ev, sizeof ev)) < sizeof(struct input_event)) {
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

                // reset output string
                output[0] = '\0'; 
            }
        }
    }

    // free device file
    result = ioctl(fd, EVIOCGRAB, 0);
    close(fd);
    return 0;
}