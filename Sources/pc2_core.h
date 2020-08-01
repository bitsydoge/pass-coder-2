#ifndef PC2_CORE_H
#define PC2_CORE_H

#include <argon2.h>

#include "pc2_config.h"

#define PC2_SYMBOLES "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$%&*+,-.:;?^~()"
#define PC2_SYMBOLES_LEN sizeof(PC2_SYMBOLES)

struct pc2_password
{
	char array[PC2_HASHLEN];
}; typedef struct pc2_password pc2_password_t;

struct pc2_hash_pass
{
	int is_empty;
	uint8_t* input;
	uint32_t input_len;
	uint8_t output[PC2_HASHLEN];
	uint8_t salt[PC2_SALTLEN];

}; typedef struct pc2_hash_pass pc2_hash_pass_t;

pc2_password_t pc2_password_generate(pc2_hash_pass_t* hp);
pc2_hash_pass_t pc2_hash_pass_create_from_user_input(char* field_name);
pc2_hash_pass_t pc2_hash_pass_create_manually(uint8_t* r_input);
pc2_hash_pass_t pc2_hash_pass_get_final(pc2_hash_pass_t* r_hp_passphrase, pc2_hash_pass_t* r_hp_tag);
void pc2_hash_pass_set_salt(pc2_hash_pass_t* r_hp, uint8_t* r_salt);
void pc2_hash_pass_print(pc2_hash_pass_t* r_hp);
void pc2_hash_pass_process(pc2_hash_pass_t* r_hp);
void pc2_hash_pass_clean(pc2_hash_pass_t* r_hp);

#if defined(PC2_OS_IS_WINDOWS)
void pc2_check_run_from_console();
#else
#define pc2_check_run_from_console()
#endif

#endif // PC2_CORE_H