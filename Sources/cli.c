#include "core.h"

#include <stdio.h>

int main(int argc, char ** argv)
{	
	hash_pass_t passphrase = hash_pass_create_from_user_input("Passphrase");
	hash_pass_set_salt(&passphrase, BASE_SALT);
	hash_pass_t tag = hash_pass_create_from_user_input("Tag");
	hash_pass_set_salt(&tag, BASE_SALT);
	
	hash_pass_process(&passphrase);
	hash_pass_process(&tag);

	hash_pass_t final_hash = hash_pass_create_manually(passphrase.output);
	hash_pass_set_salt(&final_hash, tag.output);
	hash_pass_process(&final_hash);
	
	if (argc > 1)
	{
		puts("Hash 1 :");
		hash_pass_print(&passphrase);
		puts("");
		puts("Hash 2 :");
		hash_pass_print(&tag);
		puts("");
	}

	puts("Password : ");
	hash_pass_print(&final_hash);

	hash_pass_clean(&passphrase);
	hash_pass_clean(&tag);
	hash_pass_clean(&final_hash);
	
	check_run_from_console();
	
	return 0;
}