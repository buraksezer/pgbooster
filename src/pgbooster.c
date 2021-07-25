#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

#include "log.h"

#define PGBOOSTER_VERSION "0.1.0"
#define PGBOOSTER_CONFIG_FILE "pgbooster.conf"

void help() {
    printf("Query cache and connection pool for PostgreSQL\n\n");
    printf("pgbooster [OPTION]...\n\n");
    printf("Options:\n");
    printf("-h  --help    Show this help, then exit.\n");
    printf("-v  --version Output version information, then exit.\n");
    printf("-c  --config  Sets configuration file path.\n");
}

char * get_config_file() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // + 2 because of the '/' and the terminating 0
        char *buf = malloc( strlen(cwd) + strlen(PGBOOSTER_CONFIG_FILE) + 2);
        sprintf(buf, "%s/%s", cwd, PGBOOSTER_CONFIG_FILE);
        return buf;
    }
    return NULL;
}

int main(int argc, char *argv[]){
    char *config_file;

    int i;
    for (i=1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            help();
            return 0;
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            printf("pgbooster %s\n", PGBOOSTER_VERSION);
            return 0;
        } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--config") == 0) {
            if (argc <= i+1) {
                log_fatal("no config file");
                return 1;
            }
            config_file = argv[i+1];
            i++;
        } else {
            log_fatal("unknown command: %s", argv[i]);
            return 1;
        }
    }

    if (config_file != NULL) {
        log_info("config_file: %s", config_file);
    } else {
        char * buf_config_file = get_config_file();
        log_info("config file: %s", buf_config_file);
        free(buf_config_file);
    }

    return 0;
}
