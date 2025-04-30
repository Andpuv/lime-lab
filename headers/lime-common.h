# ifndef __LIME_COMMON_H__
#   define __LIME_COMMON_H__

#   define _lime_quote(expr)          #expr
#   define lime_quote(expr)           _lime_quote(expr)

#   define _lime_paste(lexpr, rexpr)  lexpr##rexpr
#   define lime_paste(lexpr, rexpr)   _lime_paste(lexpr, rexpr)

#   if defined(__cplusplus)
#     define __LIME_ENTER__     extern "C" {
#     define __LIME_LEAVE__     }
#   else
#     define __LIME_ENTER__
#     define __LIME_LEAVE__
#   endif

#   if defined(__x86_64__) || defined(__x86_64)
#     define __LIME_X64__
#   else
#     define __LIME_X32__
#   endif

#   if defined(__clang__) || defined(__GNUC__)
#     define __LIME_EXPORT__    __attribute__((visibility("default"))) // __attribute__((dllexport))
#     define __LIME_IMPORT__    __attribute__((visibility("default"))) // __attribute__((dllimport))
#   elif defined(_MSC_VER)
#     define __LIME_EXPORT__    __declspec(dllexport)
#     define __LIME_IMPORT__    __declspec(dllimport)
#   else
#     define __LIME_EXPORT__
#     define __LIME_IMPORT__
#   endif

#   if defined(__LIME_EXPORT__)
#     define LIME_PRIVATE(type) static type
#     define LIME_PROTECT(type) __LIME_EXPORT__ type
#     define LIME_PUBLIC(type)  __LIME_EXPORT__ type
#   else
#     define LIME_PRIVATE(type) type
#     define LIME_PROTECT(type) __LIME_IMPORT__ type
#     define LIME_PUBLIC(type)  __LIME_IMPORT__ type
#   endif

__LIME_ENTER__

typedef void                    lime_void;

#   define LIME_VOID(expr)      ( (lime_void)(expr) )

#   define LIME_KiB(N)          ( (N) << 10 )
#   define LIME_MiB(N)          ( (N) << 20 )
#   define LIME_GiB(N)          ( (N) << 30 )
#   define LIME_TiB(N)          ( (N) << 40 )
#   define LIME_PiB(N)          ( (N) << 50 )
#   define LIME_EiB(N)          ( (N) << 60 )

#   include <limits.h>

typedef unsigned int            lime_uint;

#   define LIME_UINT(N)         N ## U
#   define LIME_UINT_MIN        0 ## U
#   define LIME_UINT_MAX        UINT_MAX

typedef signed int              lime_sint;

#   define LIME_SINT(N)         N ## U
#   define LIME_SINT_MIN        INT_MIN
#   define LIME_SINT_MAX        INT_MAX

#   include <stdint.h>

typedef uint8_t                 lime_uint8;

#   define LIME_UINT8(N)        UINT8_C(N)
#   define LIME_UINT8_MIN       UINT8_C(0)
#   define LIME_UINT8_MAX       UINT8_MAX

typedef int8_t                  lime_sint8;

#   define LIME_SINT8(N)        INT8_C(N)
#   define LIME_SINT8_MIN       INT8_MIN
#   define LIME_SINT8_MAX       INT8_MAX

typedef uint16_t                lime_uint16;

#   define LIME_UINT16(N)       UINT16_C(N)
#   define LIME_UINT16_MIN      UINT16_C(0)
#   define LIME_UINT16_MAX      UINT16_MAX

typedef int16_t                 lime_sint16;

#   define LIME_SINT16(N)       INT16_C(N)
#   define LIME_SINT16_MIN      INT16_MIN
#   define LIME_SINT16_MAX      INT16_MAX

typedef uint32_t                lime_uint32;

#   define LIME_UINT32(N)       UINT32_C(N)
#   define LIME_UINT32_MIN      UINT32_C(0)
#   define LIME_UINT32_MAX      UINT32_MAX

typedef int32_t                 lime_sint32;

#   define LIME_SINT32(N)       INT32_C(N)
#   define LIME_SINT32_MIN      INT32_MIN
#   define LIME_SINT32_MAX      INT32_MAX

typedef uint64_t                lime_uint64;

#   define LIME_UINT64(N)       UINT64_C(N)
#   define LIME_UINT64_MIN      UINT64_C(0)
#   define LIME_UINT64_MAX      UINT64_MAX

typedef int64_t                 lime_sint64;

#   define LIME_SINT64(N)       INT64_C(N)
#   define LIME_SINT64_MIN      INT64_MIN
#   define LIME_SINT64_MAX      INT64_MAX

#   include <float.h>

typedef float                   lime_float32;

#   define LIME_FLOAT32(N)      N ## F
#   define LIME_FLOAT32_MIN     FLT_MIN
#   define LIME_FLOAT32_MAX     FLT_MAX
#   define LIME_FLOAT32_EPSILON FLT_EPSILON

typedef double                  lime_float64;

#   define LIME_FLOAT64(N)      N
#   define LIME_FLOAT64_MIN     DBL_MIN
#   define LIME_FLOAT64_MAX     DBL_MAX
#   define LIME_FLOAT64_EPSILON DBL_EPSILON

#   define LIME_ADDR_KiB(N)     LIME_KiB(N)
#   define LIME_ADDR_MiB(N)     LIME_MiB(N)
#   define LIME_ADDR_GiB(N)     LIME_GiB(N)
#   define LIME_ADDR_TiB(N)     LIME_TiB(N)
#   define LIME_ADDR_PiB(N)     LIME_PiB(N)
#   define LIME_ADDR_EiB(N)     LIME_EiB(N)

#   if defined(__LIME_X64__)
#     define __lime_uaddr       lime_uint64
#     define __LIME_UADDR(N)    LIME_UINT64(N)
#     define __LIME_UADDR_MIN   LIME_UINT64_MIN
#     define __LIME_UADDR_MAX   LIME_UINT64_MAX
#     define __lime_saddr       lime_sint64
#     define __LIME_SADDR(N)    LIME_SINT64(N)
#     define __LIME_SADDR_MIN   LIME_SINT64_MIN
#     define __LIME_SADDR_MAX   LIME_SINT64_MAX
#   else
#     define __lime_uaddr       lime_uint32
#     define __LIME_UADDR(N)    LIME_UINT32(N)
#     define __LIME_UADDR_MIN   LIME_UINT32_MIN
#     define __LIME_UADDR_MAX   LIME_UINT32_MAX
#     define __lime_saddr       lime_sint32
#     define __LIME_SADDR(N)    LIME_SINT32(N)
#     define __LIME_SADDR_MIN   LIME_SINT32_MIN
#     define __LIME_SADDR_MAX   LIME_SINT32_MAX
#   endif

typedef __lime_uaddr            lime_uaddr;

#   define LIME_UADDR(N)        __LIME_UADDR(N)
#   define LIME_UADDR_MIN       __LIME_UADDR_MIN
#   define LIME_UADDR_MAX       __LIME_UADDR_MAX

#   if defined(__LIME_X64__)
#     define LIME_UADDR_KiB(N)  LIME_ADDR_KiB(LIME_UADDR(N))
#     define LIME_UADDR_MiB(N)  LIME_ADDR_MiB(LIME_UADDR(N))
#     define LIME_UADDR_GiB(N)  LIME_ADDR_GiB(LIME_UADDR(N))
#     define LIME_UADDR_TiB(N)  LIME_ADDR_TiB(LIME_UADDR(N))
#     define LIME_UADDR_PiB(N)  LIME_ADDR_PiB(LIME_UADDR(N))
#     define LIME_UADDR_EiB(N)  LIME_ADDR_EiB(LIME_UADDR(N))
#   else
#     define LIME_UADDR_KiB(N)  LIME_ADDR_KiB(LIME_UADDR(N))
#     define LIME_UADDR_MiB(N)  LIME_ADDR_MiB(LIME_UADDR(N))
#     define LIME_UADDR_GiB(N)  LIME_ADDR_GiB(LIME_UADDR(N))
#   endif

typedef __lime_saddr            lime_saddr;

#   define LIME_SADDR(N)        __LIME_SADDR(N)
#   define LIME_SADDR_MIN       __LIME_SADDR_MIN
#   define LIME_SADDR_MAX       __LIME_SADDR_MAX

#   if defined(__LIME_X64__)
#     define LIME_SADDR_KiB(N)  LIME_ADDR_KiB(LIME_SADDR(N))
#     define LIME_SADDR_MiB(N)  LIME_ADDR_MiB(LIME_SADDR(N))
#     define LIME_SADDR_GiB(N)  LIME_ADDR_GiB(LIME_SADDR(N))
#     define LIME_SADDR_TiB(N)  LIME_ADDR_TiB(LIME_SADDR(N))
#     define LIME_SADDR_PiB(N)  LIME_ADDR_PiB(LIME_SADDR(N))
#     define LIME_SADDR_EiB(N)  LIME_ADDR_EiB(LIME_SADDR(N))
#   else
#     define LIME_SADDR_KiB(N)  LIME_ADDR_KiB(LIME_SADDR(N))
#     define LIME_SADDR_MiB(N)  LIME_ADDR_MiB(LIME_SADDR(N))
#     define LIME_SADDR_GiB(N)  LIME_ADDR_GiB(LIME_SADDR(N))
#   endif

#   define LIME_SIZE_KiB(N)     LIME_KiB(N)
#   define LIME_SIZE_MiB(N)     LIME_MiB(N)
#   define LIME_SIZE_GiB(N)     LIME_GiB(N)
#   define LIME_SIZE_TiB(N)     LIME_TiB(N)
#   define LIME_SIZE_PiB(N)     LIME_PiB(N)
#   define LIME_SIZE_EiB(N)     LIME_EiB(N)

#   if defined(__LIME_X64__)
#     define __lime_usize       lime_uint64
#     define __LIME_USIZE(N)    LIME_UINT64(N)
#     define __LIME_USIZE_MIN   LIME_UINT64_MIN
#     define __LIME_USIZE_MAX   LIME_UINT64_MAX
#     define __lime_ssize       lime_sint64
#     define __LIME_SSIZE(N)    LIME_SINT64(N)
#     define __LIME_SSIZE_MIN   LIME_SINT64_MIN
#     define __LIME_SSIZE_MAX   LIME_SINT64_MAX
#   else
#     define __lime_usize       lime_uint32
#     define __LIME_USIZE(N)    LIME_UINT32(N)
#     define __LIME_USIZE_MIN   LIME_UINT32_MIN
#     define __LIME_USIZE_MAX   LIME_UINT32_MAX
#     define __lime_ssize       lime_sint32
#     define __LIME_SSIZE(N)    LIME_SINT32(N)
#     define __LIME_SSIZE_MIN   LIME_SINT32_MIN
#     define __LIME_SSIZE_MAX   LIME_SINT32_MAX
#   endif

typedef __lime_usize            lime_usize;

#   define LIME_USIZE(N)        __LIME_USIZE(N)
#   define LIME_USIZE_MIN       __LIME_USIZE_MIN
#   define LIME_USIZE_MAX       __LIME_USIZE_MAX

#   if defined(__LIME_X64__)
#     define LIME_USIZE_KiB(N)  LIME_SIZE_KiB(LIME_USIZE(N))
#     define LIME_USIZE_MiB(N)  LIME_SIZE_MiB(LIME_USIZE(N))
#     define LIME_USIZE_GiB(N)  LIME_SIZE_GiB(LIME_USIZE(N))
#     define LIME_USIZE_TiB(N)  LIME_SIZE_TiB(LIME_USIZE(N))
#     define LIME_USIZE_PiB(N)  LIME_SIZE_PiB(LIME_USIZE(N))
#     define LIME_USIZE_EiB(N)  LIME_SIZE_EiB(LIME_USIZE(N))
#   else
#     define LIME_USIZE_KiB(N)  LIME_SIZE_KiB(LIME_USIZE(N))
#     define LIME_USIZE_MiB(N)  LIME_SIZE_MiB(LIME_USIZE(N))
#     define LIME_USIZE_GiB(N)  LIME_SIZE_GiB(LIME_USIZE(N))
#   endif

typedef __lime_ssize            lime_ssize;

#   define LIME_SSIZE(N)        __LIME_SSIZE(N)
#   define LIME_SSIZE_MIN       __LIME_SSIZE_MIN
#   define LIME_SSIZE_MAX       __LIME_SSIZE_MAX

#   if defined(__LIME_X64__)
#     define LIME_SSIZE_KiB(N)  LIME_SIZE_KiB(LIME_SSIZE(N))
#     define LIME_SSIZE_MiB(N)  LIME_SIZE_MiB(LIME_SSIZE(N))
#     define LIME_SSIZE_GiB(N)  LIME_SIZE_GiB(LIME_SSIZE(N))
#     define LIME_SSIZE_TiB(N)  LIME_SIZE_TiB(LIME_SSIZE(N))
#     define LIME_SSIZE_PiB(N)  LIME_SIZE_PiB(LIME_SSIZE(N))
#     define LIME_SSIZE_EiB(N)  LIME_SIZE_EiB(LIME_SSIZE(N))
#   else
#     define LIME_SSIZE_KiB(N)  LIME_SIZE_KiB(LIME_SSIZE(N))
#     define LIME_SSIZE_MiB(N)  LIME_SIZE_MiB(LIME_SSIZE(N))
#     define LIME_SSIZE_GiB(N)  LIME_SIZE_GiB(LIME_SSIZE(N))
#   endif

#   include <stdbool.h>

typedef bool                    lime_bool;

#   define LIME_FALSE           false
#   define LIME_TRUE            true
#   define LIME_BOOL(expr)      ( !!(expr) )

typedef lime_uint               lime_ubool;

#   define LIME_UFALSE          LIME_UINT(0)
#   define LIME_UTRUE           LIME_UINT(+1)
#   define LIME_UBOOL(expr)     ( !!(expr) ? LIME_UTRUE : LIME_UFALSE )

typedef lime_sint               lime_sbool;

#   define LIME_SFALSE          LIME_SINT(0)
#   define LIME_STRUE           LIME_SINT(-1)
#   define LIME_SBOOL(expr)     ( !!(expr) ? LIME_STRUE : LIME_SFALSE )

#   include <limits.h>

typedef char                    lime_char;

#   define LIME_CHAR(N)         N
#   define LIME_CHAR_MIN        CHAR_MIN
#   define LIME_CHAR_MAX        CHAR_MAX

typedef unsigned char           lime_uchar;

#   define LIME_UCHAR(N)        N ## U
#   define LIME_UCHAR_MIN       0 ## U
#   define LIME_UCHAR_MAX       UCHAR_MAX

typedef signed char             lime_schar;

#   define LIME_SCHAR(N)        N
#   define LIME_SCHAR_MIN       SCHAR_MIN
#   define LIME_SCHAR_MAX       SCHAR_MAX

#   define lime_nop()                                                          \
  do {                                                                         \
    /* Nothing to be done. */                                                  \
  } while ( LIME_FALSE )

#   include <assert.h>

#   if defined(__LIME_DEBUG__)
#     define lime_assert_ct(expr) _Static_assert((expr), #expr)
#     define lime_assert_rt(expr) assert((expr))
#   else
#     define lime_assert_ct(expr) _Static_assert((expr), #expr)
#     define lime_assert_rt(expr) lime_nop()
#   endif

#   include <stddef.h>
#   include <stdlib.h>

typedef lime_void *             lime_pointer;
typedef lime_void const *       lime_pointer_const;

#   define LIME_POINTER_INVALID NULL

static inline
lime_bool lime_pointer_is_invalid (
  lime_pointer_const            self
)
{
  return LIME_POINTER_INVALID == self;
}

static inline
lime_bool lime_pointer_is_valid (
  lime_pointer_const            self
)
{
  return LIME_POINTER_INVALID != self;
}

static inline
lime_void lime_pointer_invalidate (
  lime_pointer *                self
)
{
  *self = LIME_POINTER_INVALID;
}

#   define lime_pointer_invalidate(self)                                       \
  lime_pointer_invalidate((lime_pointer *)(self))

static inline
lime_pointer lime_memory_allocate (
  lime_usize                    new_size
)
{
  return (lime_pointer)malloc((size_t)new_size);
}

static inline
lime_pointer lime_memory_reallocate (
  lime_pointer                  old_data,
  lime_usize                    old_size,
  lime_usize                    new_size
)
{
  LIME_VOID(old_size);
  return (lime_pointer)realloc((void *)old_data, (size_t)new_size);
}

static inline
lime_void lime_memory_deallocate (
  lime_pointer                  old_data,
  lime_usize                    old_size
)
{
  lime_assert_rt(lime_pointer_is_valid(old_data));

  LIME_VOID(old_size);
  free((void *)old_data);
}

#   define lime_size_of(value)                                                 \
  (                                                                            \
    (lime_usize)sizeof(value)                                                  \
  )
#   define lime_count_of(values)                                               \
  (                                                                            \
    lime_size_of(values) / lime_size_of(values[ 0 ])                           \
  )

#   define LIME_TIME_NS(N)      ( (N) * 1 )
#   define LIME_TIME_US(N)      ( (N) * 1000 )
#   define LIME_TIME_MS(N)      ( (N) * 1000000 )
#   define LIME_TIME_S(N)       ( (N) * 1000000000 )

#   if defined(__LIME_X64__)
#     define __lime_utime       lime_uint64
#     define __LIME_UTIME(N)    LIME_UINT64(N)
#     define __LIME_UTIME_MIN   LIME_UINT64_MIN
#     define __LIME_UTIME_MAX   LIME_UINT64_MAX
#     define __lime_stime       lime_sint64
#     define __LIME_STIME(N)    LIME_SINT64(N)
#     define __LIME_STIME_MIN   LIME_SINT64_MIN
#     define __LIME_STIME_MAX   LIME_SINT64_MAX
#   else
#     define __lime_utime       lime_uint32
#     define __LIME_UTIME(N)    LIME_UINT32(N)
#     define __LIME_UTIME_MIN   LIME_UINT32_MIN
#     define __LIME_UTIME_MAX   LIME_UINT32_MAX
#     define __lime_stime       lime_sint32
#     define __LIME_STIME(N)    LIME_SINT32(N)
#     define __LIME_STIME_MIN   LIME_SINT32_MIN
#     define __LIME_STIME_MAX   LIME_SINT32_MAX
#   endif

typedef __lime_utime            lime_utime;

#   define LIME_UTIME(N)        __LIME_UTIME(N)
#   define LIME_UTIME_MIN       __LIME_UTIME_MIN
#   define LIME_UTIME_MAX       __LIME_UTIME_MAX

#   define LIME_UTIME_NS(N)     LIME_TIME_NS(LIME_UTIME(N))
#   define LIME_UTIME_US(N)     LIME_TIME_US(LIME_UTIME(N))
#   define LIME_UTIME_MS(N)     LIME_TIME_MS(LIME_UTIME(N))
#   define LIME_UTIME_S(N)      LIME_TIME_S(LIME_UTIME(N))

typedef __lime_stime            lime_stime;

#   define LIME_STIME(N)        __LIME_STIME(N)
#   define LIME_STIME_MIN       __LIME_STIME_MIN
#   define LIME_STIME_MAX       __LIME_STIME_MAX

#   define LIME_STIME_NS(N)     LIME_TIME_NS(LIME_STIME(N))
#   define LIME_STIME_US(N)     LIME_TIME_US(LIME_STIME(N))
#   define LIME_STIME_MS(N)     LIME_TIME_MS(LIME_STIME(N))
#   define LIME_STIME_S(N)      LIME_TIME_S(LIME_STIME(N))

struct lime_time {
  lime_utime                    seconds;
  lime_utime                    nanoseconds;
};

#   if defined(__linux__) || defined(__linux) || defined(linux)
#     if !defined(__USE_POSIX199309)
#       define __USE_POSIX199309
#     endif

#     include <time.h>

static inline
lime_bool lime_time_get_clock (
  struct lime_time *            self,
  int                           clock_id
)
{
  lime_assert_rt(lime_pointer_is_valid(self));

  struct timespec ts;

  int result    = clock_gettime(clock_id, &ts);

  if ( result != 0 )
    return LIME_FALSE;

  self->seconds         = ts.tv_sec;
  self->nanoseconds     = ts.tv_nsec;

  return LIME_TRUE;
}

static inline
lime_bool lime_time_get_relative (
  struct lime_time *            self
)
{
  return lime_time_get_clock(self, CLOCK_MONOTONIC);
}

static inline
lime_bool lime_time_get_absolute (
  struct lime_time *            self
)
{
  return lime_time_get_clock(self, CLOCK_REALTIME);
}
#   elif defined(_WIN32) || defined(_WIN64)
#     include <windows.h>

static inline
lime_bool lime_time_get_relative (
  struct lime_time * self
)
{
  lime_assert_rt(lime_pointer_is_valid(self));

  LARGE_INTEGER counter;
  LARGE_INTEGER frequency;

  if (
    !QueryPerformanceCounter(&counter) ||
    !QueryPerformanceFrequency(&frequency)
  )
    return LIME_FALSE;

  uint64_t ticks      = (uint64_t)counter.QuadPart;
  uint64_t frequency  = (uint64_t)frequency.QuadPart;

  self->seconds       =
    (lime_uint64)( ticks / frequency );
  self->nanoseconds   =
    (lime_uint64)( ticks % frequency ) * LIME_UINT64(1000000000) / frequency;

  return LIME_TRUE;
}

static inline
lime_bool lime_time_get_absolute (
  struct lime_time *            self
)
{
  lime_assert_rt(lime_pointer_is_valid(self));

  self->seconds         = (lime_utime)time((time_t *)NULL);
  self->nanoseconds     = LIME_UTIME(0);

  return LIME_TRUE;
}
#   else
#     include <time.h>

static inline
lime_bool lime_time_get_clock (
  struct lime_time *            self,
  int                           clock_id
)
{
  LIME_VOID(clock_id);

  lime_assert_rt(lime_pointer_is_valid(self));

  self->seconds         = (lime_utime)time((time_t *)NULL);
  self->nanoseconds     = LIME_UTIME(0);

  return LIME_TRUE;
}

static inline
lime_bool lime_time_get_absolute (
  struct lime_time *            self
)
{
  return lime_time_get_clock(self, 0);
}

static inline
lime_bool lime_time_get_relative (
  struct lime_time *            self
)
{
  return lime_time_get_clock(self, 0);
}
#   endif

#   define LIME_SUPER(type)                                                    \
  struct lime_paste(lime_, type)  lime_paste(_super_, type)
#   define lime_super_of(type, self)                                           \
  (                                                                            \
    (self)->lime_paste(_super_, type)                                          \
  )
#   define lime_super_ref_of(type, self)                                       \
  (                                                                            \
    &(self)->lime_paste(_super_, type)                                         \
  )

#   include <stdarg.h>

enum lime_logger_level {
  LIME_LOGGER_LEVEL_FATAL,
  LIME_LOGGER_LEVEL_ERROR,
  LIME_LOGGER_LEVEL_ALERT,
  LIME_LOGGER_LEVEL_INFO,
  LIME_LOGGER_LEVEL_NOTE,
  LIME_LOGGER_LEVEL_HINT,
  LIME_LOGGER_LEVEL_DEBUG,
  LIME_LOGGER_LEVEL_TRACE,

  LIME_LOGGER_N_LEVELS
};

struct lime_logger;

LIME_PUBLIC(struct lime_logger *)
lime_logger_construct (
  lime_char const *             file_name,
  enum lime_logger_level        threshold
);

LIME_PUBLIC(lime_void)
lime_logger_deconstruct (
  struct lime_logger *          self
);

LIME_PUBLIC(lime_void)
lime_logger_valog (
  struct lime_logger *          self,
  lime_char const *             prompt,
  enum lime_logger_level        level,
  lime_char const *             format,
  va_list                       arguments
);

LIME_PUBLIC(lime_void)
lime_logger_log (
  struct lime_logger *          self,
  lime_char const *             prompt,
  enum lime_logger_level        level,
  lime_char const *             format,
  ...
);

#   define lime_logger_log_fatal(self, prompt, ...) lime_logger_log((self), (prompt), LIME_LOGGER_LEVEL_FATAL, __VA_ARGS__)
#   define lime_logger_log_error(self, prompt, ...) lime_logger_log((self), (prompt), LIME_LOGGER_LEVEL_ERROR, __VA_ARGS__)
#   define lime_logger_log_alert(self, prompt, ...) lime_logger_log((self), (prompt), LIME_LOGGER_LEVEL_ALERT, __VA_ARGS__)
#   define lime_logger_log_note(self, prompt, ...)  lime_logger_log((self), (prompt), LIME_LOGGER_LEVEL_INFO,  __VA_ARGS__)
#   define lime_logger_log_info(self, prompt, ...)  lime_logger_log((self), (prompt), LIME_LOGGER_LEVEL_NOTE,  __VA_ARGS__)
#   define lime_logger_log_hint(self, prompt, ...)  lime_logger_log((self), (prompt), LIME_LOGGER_LEVEL_HINT,  __VA_ARGS__)

#   if defined(__LIME_DEBUG__)
#     define lime_logger_log_debug(self, prompt, ...) lime_logger_log((self), (prompt), LIME_LOGGER_LEVEL_DEBUG, __VA_ARGS__)
#     define lime_logger_log_trace(self, prompt, ...) lime_logger_log((self), (prompt), LIME_LOGGER_LEVEL_TRACE, __VA_ARGS__)
#   else
#     define lime_logger_log_debug(self, prompt, ...) lime_nop()
#     define lime_logger_log_trace(self, prompt, ...) lime_nop()
#   endif

__LIME_LEAVE__

# endif /* __LIME_COMMON_H__ */