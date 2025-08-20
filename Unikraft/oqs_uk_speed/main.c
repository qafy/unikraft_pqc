
#include <stdio.h>
#include <string.h>
#include <sys/random.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

int main_speed_kem(int argc, char **argv);
int main_speed_sig(int argc, char **argv);
int main_speed_common(int argc, char **argv);


void print_usage()
{
    printf("Usage: ./test [sig | kem | common] args...\n");
}

int main(int argc, char **argv)
{
        
    if (argc < 2)
    {
        fprintf(stderr, "To few arguments\n");
        print_usage();
        return 1;
    }
    else if (!strcmp(argv[1], "kem"))
    {
        main_speed_kem(argc - 1, argv + 1);
        return 0;
    }
    else if (!strcmp(argv[1], "sig"))
    {
        main_speed_sig(argc - 1, argv + 1);
        return 0;
    }
    else if (!strcmp(argv[1], "common"))
    {
        main_speed_common(argc - 1, argv + 1);
        return 0;
    }
    else
    {
        fprintf(stderr, "Did not provide a test suite sig/kem/common\n");
        print_usage();
        return 1;
    }
}