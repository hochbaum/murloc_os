#ifndef MURLOC_OS_STDIO_H
#define MURLOC_OS_STDIO_H

#include "stdarg.h"

/*!
 * A very basic implementation of printf!
 * Tokens in the format will be replaced and printed.
 *
 * So far, this does only support strings and % escaping.
 *
 * %s: Replaces a string.
 * %%: Prints a %-sign.
 *
 * @param fmt The format to use.
 * @param ... The replacements for the format.
 */
void printf(char *fmt, ...);

#endif //MURLOC_OS_STDIO_H
