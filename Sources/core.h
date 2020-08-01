#ifndef CORE_H
#define CORE_H

#include <argon2.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define OS_IS_WINDOWS
#endif

#define HASHLEN 32
#define SALTLEN HASHLEN
#define BASE_SALT "b2TiMYqHl8rRL9foPwAQgKD3k8LsbS19"
#define ITERAT_COST 4
#define MEM_COST (1 << 16)
#define PARRALEL_COST 32

struct hash_pass
{
	uint8_t* input;
	uint32_t input_len;
	uint8_t output[HASHLEN];
	uint8_t salt[SALTLEN];

}; typedef struct hash_pass hash_pass_t;

hash_pass_t hash_pass_create_from_user_input(char* field_name);
hash_pass_t hash_pass_create_manually(uint8_t* r_input);
void hash_pass_set_salt(hash_pass_t* r_hp, uint8_t* r_salt);
void hash_pass_print(hash_pass_t* r_hp);
void hash_pass_process(hash_pass_t* r_hp);
void hash_pass_clean(hash_pass_t* r_hp);

#if defined(OS_IS_WINDOWS)
void check_run_from_console();
#else
#define check_run_from_console()
#endif

#endif // CORE_H