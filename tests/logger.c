# include "lime.h"

/* NOTE(Andpuv): THIS IS NOT A REAL TEST SUITE, JUST AN EXAMPLE! */

/* ${CC} -o ${OUTPUT} sources/lime-common.c sources/lime.c tests/logger.c -I${PATH}/lime-lab/headers */

int main ( int argc, char ** argv )
{
  struct lime_logger * logger = lime_logger_construct(
    "my-log-file-1.log",
    LIME_LOGGER_LEVEL_ALERT
  );

  lime_logger_log_error(logger,
    "(test error)",
    "Just an error (ID = 0x%04X) that should be displayed by the logger.",
    0x0123
  );

  lime_logger_log_alert(logger,
    "(test alert)",
    "Just an alert (ID = 0x%04X) that should be displayed by the logger.",
    0x3210
  );

  lime_logger_log_note(logger,
    "(test alert)",
    "Just a note (ID = 0x%04X) that should not be displayed by the logger.",
    0x1032
  );

  lime_logger_deconstruct(logger);
  return 0;
}