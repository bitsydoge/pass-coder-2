#include "pc2_core.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rlutil.h"

#if defined(PC2_OS_IS_WINDOWS)
#include <windows.h>
#endif

#if defined(PC2_OS_IS_WINDOWS)
#define STRDUP _strdup
#else
#define STRDUP strdup
#endif

char symbole[] = PC2_SYMBOLES;

pc2_password_t pc2_password_generate(pc2_hash_pass_t* hp)
{
	pc2_password_t final = { 0 };
	for (int i = 0; i < PC2_HASHLEN; i += 1)
	{
		final.array[i] = symbole[hp->output[i] % PC2_SYMBOLES_LEN];
	}
	return final;
}

pc2_hash_pass_t pc2_hash_pass_create_from_user_input(char* field_name)
{
	setColor(GREEN);
	printf("%s : ", field_name);
	resetColor();
	char input_buffer[4096];
	fflush(stdin);
	fgets(input_buffer, sizeof(input_buffer), stdin);
	input_buffer[strcspn(input_buffer, "\n")] = 0;
	pc2_hash_pass_t hp = { 0 };
	hp.input = (uint8_t*)STRDUP(input_buffer);
	hp.input_len = strlen((char*)hp.input);
	return hp;
}

pc2_hash_pass_t pc2_hash_pass_create_manually(uint8_t* r_input)
{
	pc2_hash_pass_t hp = { 0 };
	hp.input = (uint8_t*)STRDUP((char*)r_input);
	hp.input_len = strlen((char*)hp.input);
	return hp;
}

void pc2_hash_pass_set_salt(pc2_hash_pass_t* r_hp, uint8_t* r_salt)
{
	memcpy((char*)r_hp->salt, (char*)r_salt, PC2_SALTLEN);
}

void pc2_hash_pass_print(pc2_hash_pass_t* r_hp)
{
	for (int i = 0; i < PC2_HASHLEN; ++i) printf("%02x", r_hp->output[i]);
}
void pc2_hash_pass_process(pc2_hash_pass_t* r_hp)
{
	argon2i_hash_raw(
		PC2_ITERAT_COST,
		PC2_MEM_COST,
		PC2_PARRALEL_COST,
		r_hp->input,
		r_hp->input_len,
		r_hp->salt,
		PC2_SALTLEN,
		r_hp->output,
		PC2_HASHLEN
	);
}
void pc2_hash_pass_clean(pc2_hash_pass_t* r_hp)
{
	free(r_hp->input);
}

pc2_hash_pass_t pc2_hash_pass_get_final(pc2_hash_pass_t* r_hp_passphrase, pc2_hash_pass_t* r_hp_tag)
{
	pc2_hash_pass_process(r_hp_passphrase);
	pc2_hash_pass_process(r_hp_tag);
	pc2_hash_pass_t final_hash = pc2_hash_pass_create_manually(r_hp_passphrase->output);
	pc2_hash_pass_set_salt(&final_hash, r_hp_tag->output);
	
	pc2_hash_pass_process(&final_hash);
	return final_hash;
}

#if defined(PC2_OS_IS_WINDOWS)
void pc2_check_run_from_console()
{
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