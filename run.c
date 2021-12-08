/*
Compile and run C or C++ code.
Run [run] help for more info.

Params: [sudo] (run said file with sudo permission) [run] [-d] (debug mode) [file].c[pp] [params] (params to be parsed to file.c[pp])

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int sigInts = 0;

int file = 1;

// Variables for cleanup
int compiled = 0;
char* filename;

void cleanup() 
{

    if (compiled == 1) {
        remove(filename);
    }
    printf("%s\n", "Done cleaning up");
    exit(-1);
    return;

}

void sigInt(int signal) 
{
    sigInts = sigInts+1;

    if (sigInts == 1) 
    {
        printf("\n%s\n", "Cleaning up. Press ^C one more time to force quit.");
        cleanup();

    } else 
    {
        printf("\n%s\n", "Sorry to see you go!");
        exit(-1);
        return;
    }
}

char* findChars(char* string, char ch) 
{
    char* value = calloc(strlen(string), sizeof(char));

    for (long unsigned int i = 0; i < strlen(string); i++) {
        if (string[i] != ch) {
            strncat(value, &string[i], 1);
        } else {
            break;
        }

    }
    return value;
    free(value);
}


int main(int argc, char** argv)
{
    if (access("/usr/bin/gcc", F_OK) == -1) {
        printf("\n%s\n\n%s\n\n", "GCC not found, but can be installed with:", "sudo apt install gcc");
        return -1;
    }

    signal(SIGINT, sigInt);

    if (argc == 2 && strcmp(argv[1], "help") == 0) {
        printf("%s%s%s\n", "Paramaters: [sudo] (run said program with elevated privileges) ", argv[0], " [-d] (debug) [program].c [arguments] to run the specified program.");
        return 0;
    }

    if (argc == 1) {
        printf("%s%i%s%s%s\n", "Missing paramaters! Expects 1, got ", argc-1, ". Try ", argv[0], " help for more info.");
        return -1;
    }
    
    if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0) {
        file = 2;
        if (argc > 3) {
            printf("%s\n", "Warning: Paramaters won't be passed to GDB during debug mode.");
        }
    }

    if (strlen(argv[file]) > 499) 
    {
        printf("%s\n", "Please enter a filename under 500 characters.");
        return -1;
    }

    if (access(argv[file], F_OK ) != -1) 
    {
    
        for (long unsigned int i = 0; i <= strlen(argv[file]); i++)
        {

            if(argv[file][i] == '.')  
            {
                break;
            }
            
            if (strlen(argv[file]) == i) {

                printf("%s%s%s%s%s\n", "No file extension found on ", argv[file], ". Run ", argv[0], " help for more info.");
                return -1;

            }
        }

        char* extensions = strpbrk(argv[file], ".");

        if (strcmp(extensions, ".c") != 0 && strcmp(extensions, ".cpp") != 0) {
            printf("%s%s%s%s%s\n", "File extension ", extensions, " is not compatible. Run ", argv[0], " help for more info.");
            return -1;
        }
    
        // If all checks are passed, their code is piped to GCC

        char* buff = calloc(strlen(argv[file])+200, sizeof(char));
        char* result = calloc(strlen(argv[file])+200, sizeof(char));

        if (!buff)
        {
            printf("%s\n", "Error allocating memory!");
            return -1;
        }

        if (file == 1) {
            sprintf(buff, "%s%s%s%s", "gcc ", argv[file], " -o ", findChars(argv[file], '.'));
        } else {
            sprintf(buff, "%s%s%s%s", "gcc -g ", argv[file], " -o ", findChars(argv[file], '.'));
        }

        compiled = 1;

        FILE* command = popen(buff, "r");

        fgets(result, sizeof(result), command);

        pclose(command);
        
        compiled = 0;

        if (access(findChars(argv[file], '.'), F_OK) == -1) {
            return -1;
        }

        if (file == 2) 
        {
            char* cmd = calloc(strlen(findChars(argv[file], '.'))+strlen(argv[file]+200), sizeof(char));
            if (!cmd) {
                printf("%s\n", "Error allocating memory!");
                return -1;
            }
            sprintf(cmd, "%s%s", "gdb -q ", findChars(argv[file], '.'));
            system(cmd);
            return 0;
        }

        char* cmd = calloc(strlen(findChars(argv[file], '.'))+200, sizeof(char));
        if (!cmd) {
            printf("%s\n", "Error allocating memory!");
            return -1;
        }

        if (argc > 2) {
        char* args = calloc(1024, sizeof(char));

        if (!args) {
                printf("%s\n", "Error allocating memory!");
                return -1;
            }
        for (int i = 2; i < argc; i++) {
            args = realloc(args, strlen(args)+strlen(argv[i])+20);

            if (!args) {
                printf("%s\n", "Error allocating memory!");
                return -1;
            }

            cmd = realloc(cmd, strlen(cmd)+strlen(argv[i])+200);

            if (!cmd) {
                printf("%s\n", "Error allocating memory!");
                return -1;
            }
            char* argstemp = args;
            sprintf(args, "%s%s%s%s", argstemp, "\"", argv[i], "\" ");
        }
            if (geteuid() == 0) {
            sprintf(cmd, "%s%s%s%s", "sudo ./", findChars(argv[file], '.'), " ", args);
            } else {
                sprintf(cmd, "%s%s%s%s", "./", findChars(argv[file], '.'), " ", args);
            }
        } else {
            if (geteuid() == 0) {
                sprintf(cmd, "%s%s", "sudo ./", findChars(argv[file], '.'));
            } else {
                sprintf(cmd, "%s%s", "./", findChars(argv[file], '.'));
            }
        }

        free(buff);
        free(result);

        int ret = system(cmd);
        
        return WEXITSTATUS(ret);


    } else {
    printf("%s%s%s\n", "File ", argv[file], " doesn't exist.");
    return -1;
}


}
