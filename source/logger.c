#include "logger.h"

struct logger {
    LOG_LEVEL log_level;
    FILE *log_file;
    time_t time;
    struct tm *t;
    char* formatted_time;
    void (*log_info)(Logger*, const char*);
    void (*log_debug)(Logger*, const char*);
    void (*log_warning)(Logger*, const char*);
    void (*log_error)(Logger*, const char*);
};

const char* DEFAULT = "%d/%m/%y (%H:%M:%S)"; 

void format_current_time(Logger* logger, const char* format) {
    logger->time = time(NULL);
    logger->t = localtime(&(logger->time));
    strftime(logger->formatted_time, 255, format, logger->t);
}

void console_info(Logger* logger, const char* message) {
    format_current_time(logger, DEFAULT);
    fprintf(stdout, "%s [info]: %s\n", logger->formatted_time, message);
}

void console_debug(Logger* logger, const char* message) {
    format_current_time(logger, DEFAULT);
    fprintf(stdout, "%s [debug]: %s\n", logger->formatted_time, message);
}

void console_warning(Logger* logger, const char* message) {
    format_current_time(logger, DEFAULT);
    fprintf(stderr, "%s [warning]: %s\n", logger->formatted_time, message);
}

void console_error(Logger* logger, const char* message) {
    format_current_time(logger, DEFAULT);
    fprintf(stderr, "%s [error]: %s\n", logger->formatted_time, message);
}

void file_info(Logger* logger, const char* message) { 
    format_current_time(logger, DEFAULT);
    if (logger->log_level > INFO) return;
    if (logger->log_file != NULL) {
        fprintf(logger->log_file, "%s [info]: %s\n", logger->formatted_time, message);
    }
}

void file_debug(Logger* logger, const char* message) {
    format_current_time(logger, DEFAULT);
    if (logger->log_level > DEBUG) return;
    if (logger->log_file != NULL) {
        fprintf(logger->log_file, "%s [debug]: %s\n", logger->formatted_time, message);
    }
}

void file_warning(Logger* logger, const char* message) {
    format_current_time(logger, DEFAULT);
    if (logger->log_level > WARNING) return;
    if (logger->log_file != NULL) {
        fprintf(logger->log_file, "%s [warning]: %s\n", logger->formatted_time, message);
    }
}

void file_error(Logger* logger, const char* message) {
    format_current_time(logger, DEFAULT);
    if (logger->log_level > ERROR) return;
    if (logger->log_file != NULL) {
        fprintf(logger->log_file, "%s [error]: %s\n", logger->formatted_time, message);
    }
}

Logger* Logger__ctor(LOG_LEVEL log_level, LOG_TYPE log_type) {
    Logger* result = (Logger*) malloc(sizeof(Logger));
    result->log_level = log_level;
    result->formatted_time = (char*) malloc(255 * sizeof(char));
    char* log_file_name = (char*) malloc(255 * sizeof(char));

    switch(log_type) {
        case CONSOLE_LOGGER:
            result->log_file = NULL;
            result->log_info = console_info;
            result->log_debug = console_debug;
            result->log_warning = console_warning;
            result->log_error = console_error;
            break;
        case FILE_LOGGER:
            format_current_time(result, "%d_%m_%y");
            sprintf(log_file_name, "./logs/log_%s", result->formatted_time);
            result->log_file = fopen(log_file_name, "a");
            result->log_info = file_info;
            result->log_debug = file_debug;
            result->log_warning = file_warning;
            result->log_error = file_error;
            break;
        default:
            return NULL;
            break;
    }
    free(log_file_name);
    return result;
}

void Logger__dtor(Logger* logger) {
    if (!logger) {
        fclose(logger->log_file);
        free(logger->t);
        free(logger->formatted_time);
        free(logger);
    }
}

void Logger__info(Logger* logger, const char* message) {
    if (logger->log_level > INFO) return;
    logger->log_info(logger, message);
}

void Logger__debug(Logger* logger, const char* message) {
    if (logger->log_level > DEBUG) return;
    logger->log_debug(logger, message);
}

void Logger__warning(Logger* logger, const char* message) {
    if (logger->log_level > WARNING) return;
    logger->log_warning(logger, message);
}

void Logger__error(Logger* logger, const char* message) {
    if (logger->log_level > ERROR) return;
    logger->log_error(logger, message);
}