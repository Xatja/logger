#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../source/logger.h"

static void console__info(void **state) {
    (void) state;

    LOG_LEVEL info = INFO;
    LOG_TYPE type = CONSOLE_LOGGER;
    Logger* logger = Logger__ctor(info, type);
    Logger__info(logger, "Hello, World!");
    Logger__debug(logger, "Hello, World!");
    Logger__warning(logger, "Hello, World!");
    Logger__error(logger, "Hello, World!");
    Logger__dtor(logger);
}

static void file__info(void **state) {
    (void) state;

    LOG_LEVEL info = INFO;
    LOG_TYPE type = FILE_LOGGER;
    Logger* logger = Logger__ctor(info, type);
    Logger__info(logger, "Hello, World!");
    Logger__debug(logger, "Hello, World!");
    Logger__warning(logger, "Hello, World!");
    Logger__error(logger, "Hello, World!");
    Logger__dtor(logger);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(console__info),
        cmocka_unit_test(file__info),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}