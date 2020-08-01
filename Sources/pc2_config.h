#ifndef PC2_CONFIG_H
#define PC2_CONFIG_H

#define PC2_OS_UNDEFINED 0
#define PC2_OS_WINDOWS 1
#define PC2_OS_LINUX 2
#define PC2_OS_MACOS 3

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define PC2_OS_IS_WINDOWS
#define PC2_OS PC2_OS_WINDOWS
#else
#define PC2_OS PC2_OS_UNDEFINED
#endif


#define PC2_HASHLEN 32
#define PC2_SALTLEN PC2_HASHLEN
#define PC2_BASE_SALT "b2TiMYqHl8rRL9foPwAQgKD3k8LsbS19"
#define PC2_ITERAT_COST 4
#define PC2_MEM_COST (1 << 16)
#define PC2_PARRALEL_COST 32
#define PC2_VERSION "0.3"
#define PC2_PROG_EXEC_NAME "PassCoder2"

void pc2_set_verbose(int p_value);
int pc2_get_verbose();

#endif // PC2_CONFIG_H