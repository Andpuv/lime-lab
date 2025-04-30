# include "lime-common.h"

# include <stdio.h>
# include <string.h>
# include <inttypes.h>

struct lime_logger {
  FILE *                        file;
  enum lime_logger_level        threshold;
};

LIME_PRIVATE(lime_bool)
logger_initialize (
  struct lime_logger *          self,
  lime_char const *             file_name,
  enum lime_logger_level        threshold
)
{
  lime_assert_rt(lime_pointer_is_valid(self));
  lime_assert_rt(lime_pointer_is_valid(self->file));

  if ( (int)threshold < 0 || (int)threshold >= (int)LIME_LOGGER_N_LEVELS )
    return LIME_FALSE;

  if ( lime_pointer_is_invalid(file_name) ) {
    /* Assuming we want ${stderr}. */
    self->file  = stderr;
  } else if ( 0 == strcmp("${stderr}", file_name) ) {
    self->file  = stderr;
  } else if ( 0 == strcmp("${stdout}", file_name) ) {
    self->file  = stdout;
  } else {
    self->file  = fopen(file_name, "w");

    if ( lime_pointer_is_invalid(self->file) )
      return LIME_FALSE;
  }

  self->threshold       = LIME_LOGGER_LEVEL_INFO;

  lime_logger_log(self,
    "(logger)",
    LIME_LOGGER_LEVEL_INFO,
    "Logger %p has been initialized.",
    self
  );

  self->threshold       = threshold;

  return LIME_TRUE;
}

LIME_PRIVATE(lime_void)
logger_deinitialize (
  struct lime_logger *          self
)
{
  lime_assert_rt(lime_pointer_is_valid(self));
  lime_assert_rt(lime_pointer_is_valid(self->file));

  self->threshold       = LIME_LOGGER_LEVEL_INFO;

  lime_logger_log(self,
    "(logger)",
    LIME_LOGGER_LEVEL_INFO,
    "Logger %p has been deinitialized.",
    self
  );

  int result;

  result        = fflush(self->file);
  lime_assert_rt(0 == result);

  if ( self->file != stderr && self->file != stdout ) {
    result      = fclose(self->file);
    lime_assert_rt(0 == result);
  }

  LIME_VOID(result);
}

LIME_PUBLIC(struct lime_logger *)
lime_logger_construct (
  lime_char const *             file_name,
  enum lime_logger_level        threshold
)
{
  struct lime_logger * self     =
    (struct lime_logger *)lime_memory_allocate(
      lime_size_of(*self)
    );

  if ( lime_pointer_is_invalid(self) )
    return self;

  lime_bool is_okay     = logger_initialize(self,
    file_name,
    threshold
  );

  if ( is_okay )
    return self;

  lime_memory_deallocate(
    self,
    lime_size_of(*self)
  );
  return (struct lime_logger *)LIME_POINTER_INVALID;
}

LIME_PUBLIC(lime_void)
lime_logger_deconstruct (
  struct lime_logger *          self
)
{
  logger_deinitialize(self);

  lime_memory_deallocate(
    self,
    lime_size_of(*self)
  );
}

LIME_PRIVATE(lime_bool)
logger_valog (
  struct lime_logger *          self,
  lime_char const *             prompt,
  enum lime_logger_level        level,
  lime_char const *             format,
  va_list                       arguments
)
{
  lime_assert_rt(lime_pointer_is_valid(self));
  lime_assert_rt(lime_pointer_is_valid(self->file));
  lime_assert_rt(0 <= (int)level && (int)level <= (int)LIME_LOGGER_N_LEVELS);

  lime_bool is_fatal    = level == LIME_LOGGER_LEVEL_FATAL;

  if ( self->threshold < level && !is_fatal )
    return is_fatal;

  int result;

  lime_char time_stamp [
    LIME_USIZE(4) + /* <year>          */
    LIME_USIZE(1) + /* "-"             */
    LIME_USIZE(2) + /* <month>         */
    LIME_USIZE(1) + /* "-"             */
    LIME_USIZE(2) + /* <month-day>     */
    LIME_USIZE(1) + /* " "             */
    LIME_USIZE(2) + /* <hour>          */
    LIME_USIZE(1) + /* ":"             */
    LIME_USIZE(2) + /* <minutes>       */
    LIME_USIZE(1) + /* ":"             */
    LIME_USIZE(2) + /* <seconds>       */
    LIME_USIZE(1) + /* "."             */
    LIME_USIZE(6) + /* <microseconds>  */
    LIME_USIZE(1)   /* <end-of-string> */
  ];

  struct lime_time time;
  lime_bool is_okay     = lime_time_get_absolute(&time);
  lime_assert_rt(is_okay);

  time_t time_seconds   = (time_t)time.seconds;
  struct tm * time_expanded;
  time_expanded = localtime(&time_seconds);

  result        = (int)strftime(
    (char *)time_stamp,
    (size_t)lime_size_of(time_stamp),
    "%Y-%m-%d %H:%M:%S",
    time_expanded
  );
  lime_assert_rt(0 < result && (int)result < (int)lime_size_of(time_stamp));

  result        = snprintf(
    (char *)( time_stamp + result ),
    (size_t)( lime_size_of(time_stamp) - result ),
    ".%06" PRIu64,
    (uint64_t)( time.nanoseconds / LIME_UINT64(1000) )
  );
  lime_assert_rt(
    0 < result && (int)result < (int)lime_size_of(time_stamp) - result
  );

  lime_char const * levels [] = {
    [ LIME_LOGGER_LEVEL_FATAL ] = "FATAL",
    [ LIME_LOGGER_LEVEL_ERROR ] = "ERROR",
    [ LIME_LOGGER_LEVEL_ALERT ] = "ALERT",
    [ LIME_LOGGER_LEVEL_INFO  ] = "INFO ",
    [ LIME_LOGGER_LEVEL_NOTE  ] = "NOTE ",
    [ LIME_LOGGER_LEVEL_HINT  ] = "HINT ",
    [ LIME_LOGGER_LEVEL_DEBUG ] = "DEBUG",
    [ LIME_LOGGER_LEVEL_TRACE ] = "TRACE"
  };

  result        = fprintf(self->file,
    "%s %s [ %s ] ",
    (char const *)time_stamp,
    (char const *)prompt,
    (char const *)levels[ level ]
  );
  lime_assert_rt(0 != result);

  result        = vfprintf(self->file,
    (char const *)format,
    arguments
  );
  lime_assert_rt(0 != result);

  result        = fprintf(self->file,
    "\n"
  );
  lime_assert_rt(0 != result);

  LIME_VOID(result);
  return is_fatal;
}

LIME_PUBLIC(lime_void)
lime_logger_valog (
  struct lime_logger *          self,
  lime_char const *             prompt,
  enum lime_logger_level        level,
  lime_char const *             format,
  va_list                       arguments
)
{
  lime_bool is_fatal    = logger_valog(self,
    prompt,
    level,
    format,
    arguments
  );

  if ( !is_fatal )
    return;

  exit(EXIT_FAILURE);
}

LIME_PUBLIC(lime_void)
lime_logger_log (
  struct lime_logger *          self,
  lime_char const *             prompt,
  enum lime_logger_level        level,
  lime_char const *             format,
  ...
)
{
  lime_assert_rt(lime_pointer_is_valid(self));
  lime_assert_rt(lime_pointer_is_valid(self->file));

  va_list arguments;
  va_start(arguments, format);

  lime_bool is_fatal    = logger_valog(self,
    prompt,
    level,
    format,
    arguments
  );

  va_end(arguments);

  if ( !is_fatal )
    return;

  exit(EXIT_FAILURE);
}