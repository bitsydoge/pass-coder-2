#include "pc2_core.h"
#include <argtable3.h>
#include <stdio.h>

void pc2_run();
void pc2_argtable_config(int* argc, char*** argv);

int main(int argc, char ** argv)
{
	pc2_argtable_config(&argc, &argv);
	return 0;
}

void pc2_run()
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

	if (get_verbose())
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
}

void pc2_argtable_config(int* argc, char*** argv)
{
	struct arg_lit* verbose, * help, * version;
	struct arg_end* end;
	void* argtable[] =
	{
		help = arg_litn("h", "help", 0, 1, "display this help"),
		version = arg_litn(NULL, "version", 0, 1, "display version info and exit"),
		verbose = arg_litn("v", "verbose", 0, 1, "verbose output and exit"),
		end = arg_end(1),
	};
	const int nerrors = arg_parse(*argc, *argv, argtable);

	if (version->count != 0 || help->count != 0)
	{
		// HELP -v
		if (help->count > 0)
		{
			printf("usage: %s", PC2_PROG_EXEC_NAME);
			arg_print_syntax(stdout, argtable, "\n\n");
			arg_print_glossary(stdout, argtable, "  %-25s %s\n");
			puts("");
		}
		// VERSION
		if (version->count > 0)
		{
			printf("Version : %s\n", PC2_VERSION);
		}
	}
	else
	{
		// ERROR
		if (nerrors > 0)
		{
			arg_print_errors(stdout, end, PC2_PROG_EXEC_NAME);
			if (help->count == 0)
				printf("Try '%s --help' for more information.\n", PC2_PROG_EXEC_NAME);
		}
		else
		{
			set_verbose(verbose->count > 0 ? 1 : 0);
			pc2_run();
		}
	}
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
}
