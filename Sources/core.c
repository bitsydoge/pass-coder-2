#include "core.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(OS_IS_WINDOWS)
#include <windows.h>
#endif

#if defined(OS_IS_WINDOWS)
#define STRDUP _strdup
#else
#define STRDUP strdup
#endif

hash_pass_t hash_pass_create_from_user_input(char* field_name)
{
	printf("%s : ", field_name);
	char input_buffer[4096];
	fflush(stdin);
	fgets(input_buffer, sizeof(input_buffer), stdin);
	hash_pass_t hp = { 0 };
	hp.input = (uint8_t*)STRDUP(input_buffer);
	hp.input_len = strlen((char*)hp.input);
	return hp;
}

hash_pass_t hash_pass_create_manually(uint8_t* r_input)
{
	hash_pass_t hp = { 0 };
	hp.input = (uint8_t*)STRDUP((char*)r_input);
	hp.input_len = strlen((char*)hp.input);
	return hp;
}

void hash_pass_set_salt(hash_pass_t* r_hp, uint8_t* r_salt)
{
	memcpy((char*)r_hp->salt, (char*)r_salt, SALTLEN);
}

void hash_pass_print(hash_pass_t* r_hp)
{
	for (int i = 0; i < HASHLEN; ++i) printf("%02x", r_hp->output[i]);
}
void hash_pass_process(hash_pass_t* r_hp)
{
	argon2i_hash_raw(
		ITERAT_COST,
		MEM_COST,
		PARRALEL_COST,
		r_hp->input,
		r_hp->input_len,
		BASE_SALT,
		SALTLEN,
		r_hp->output,
		HASHLEN
	);
}
void hash_pass_clean(hash_pass_t* r_hp)
{
	free(r_hp->input);
}

#if defined(OS_IS_WINDOWS)
void check_run_from_console()
{
	puts("");
	HWND console_wnd = GetConsoleWindow();
	DWORD dw_process_id;
	GetWindowThreadProcessId(console_wnd, &dw_process_id);
	if (GetCurrentProcessId() == dw_process_id)
	{
		printf("Press Any Key to Quit\n");
		getchar();
	}
}
#endif