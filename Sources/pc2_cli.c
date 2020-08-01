#include "pc2_core.h"
#include <argtable3.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	pc2_hash_pass_t passphrase = hash_pass_create_from_user_input("Passphrase");
	pc2_hash_pass_set_salt(&passphrase, PC2_BASE_SALT);
	pc2_hash_pass_t tag = hash_pass_create_from_user_input("Tag");
	pc2_hash_pass_set_salt(&tag, PC2_BASE_SALT);
	
	pc2_hash_pass_process(&passphrase);
	pc2_hash_pass_process(&tag);

	pc2_hash_pass_t final_hash = hash_pass_create_manually(passphrase.output);
	pc2_hash_pass_set_salt(&final_hash, tag.output);
	pc2_hash_pass_process(&final_hash);
	
	if (argc > 1)
	{
		puts("Hash 1 :");
		pc2_hash_pass_print(&passphrase);
		puts("");
		puts("Hash 2 :");
		pc2_hash_pass_print(&tag);
		puts("");
	}

	puts("Password : ");
	pc2_hash_pass_print(&final_hash);

	pc2_hash_pass_clean(&passphrase);
	pc2_hash_pass_clean(&tag);
	pc2_hash_pass_clean(&final_hash);
	
	pc2_check_run_from_console();
	
	return 0;
}