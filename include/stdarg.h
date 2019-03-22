#ifndef MURLOC_OS_STDARG_H
#define MURLOC_OS_STDARG_H

#define va_start(v,l)   __builtin_va_start(v,l)
#define va_arg(v,l)     __builtin_va_arg(v, l)
#define va_end(v)       __builtin_va_end(v)

typedef __builtin_va_list va_list;

#endif //MURLOC_OS_STDARG_H
