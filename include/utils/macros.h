#ifndef MACROS_H
#define MACROS_H

#define FAIL(msg) do { perror(msg); goto cleanup; } while(0)

#endif