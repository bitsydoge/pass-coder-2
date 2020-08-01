﻿#ifndef PC2_CONFIG_H
#define PC2_CONFIG_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define PC2_OS_IS_WINDOWS
#endif

#define PC2_HASHLEN 32
#define PC2_SALTLEN PC2_HASHLEN
#define PC2_BASE_SALT "b2TiMYqHl8rRL9foPwAQgKD3k8LsbS19"
#define PC2_ITERAT_COST 4
#define PC2_MEM_COST (1 << 16)
#define PC2_PARRALEL_COST 32

#endif // PC2_CONFIG_H