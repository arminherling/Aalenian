
#ifndef AALTEST_API_H
#define AALTEST_API_H

#ifdef AALTEST_STATIC_DEFINE
#  define AALTEST_API
#  define AALTEST_NO_EXPORT
#else
#  ifndef AALTEST_API
#    ifdef AalTest_EXPORTS
        /* We are building this library */
#      define AALTEST_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define AALTEST_API __declspec(dllimport)
#    endif
#  endif

#  ifndef AALTEST_NO_EXPORT
#    define AALTEST_NO_EXPORT 
#  endif
#endif

#ifndef AALTEST_DEPRECATED
#  define AALTEST_DEPRECATED __declspec(deprecated)
#endif

#ifndef AALTEST_DEPRECATED_EXPORT
#  define AALTEST_DEPRECATED_EXPORT AALTEST_API AALTEST_DEPRECATED
#endif

#ifndef AALTEST_DEPRECATED_NO_EXPORT
#  define AALTEST_DEPRECATED_NO_EXPORT AALTEST_NO_EXPORT AALTEST_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef AALTEST_NO_DEPRECATED
#    define AALTEST_NO_DEPRECATED
#  endif
#endif

#endif /* AALTEST_API_H */
