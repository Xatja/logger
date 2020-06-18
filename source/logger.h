#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct  logger Logger;

typedef enum {
    INFO = 0, 
    DEBUG = 1, 
    WARNING = 2, 
    ERROR = 3, 
} LOG_LEVEL;

typedef enum {
    CONSOLE_LOGGER, 
    FILE_LOGGER,
} LOG_TYPE;

Logger*         Logger__ctor(LOG_LEVEL log_level, LOG_TYPE log_type);
void            Logger__dtor(Logger* logger);

void            Logger__info(Logger* logger, const char* message);
void            Logger__debug(Logger* logger, const char* message);
void            Logger__warning(Logger* logger, const char* message);
void            Logger__error(Logger* logger, const char* message);

#endif /* !LOGGER_H */