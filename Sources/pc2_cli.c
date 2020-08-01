#include "pc2_core.h"

#include <stdio.h>

#include "rlutil.h"
#include "argtable3.h"

#if defined(PC2_USE_VLD) && defined(_DEBUG) && defined(PC2_OS_IS_WINDOWS)
#include "vld.h"
#endif

pc2_hash_pass_t pc2_argtable_config(int argc, char** argv);

int main(int argc, char ** argv)
{
	saveDefaultColor();
	pc2_hash_pass_t password = pc2_argtable_config(argc, argv);

	if(password.is_empty == 0)
	{
		pc2_hash_pass_print(&password);
		pc2_hash_pass_clean(&password);
	}
	
	pc2_check_run_from_console();
	resetColor();
	return 0;
}

pc2_hash_pass_t pc2_argtable_config(int argc, char** argv)
{
	struct arg_str* passphrase, * tag;
	struct arg_lit* verbose, * help, * version;
	struct arg_end* end;
	void* argtable[] =
	{
		tag = arg_strn(NULL, NULL, "<tag>", 0, 1, "target tag"),
		passphrase = arg_strn("p", "pass", "<passphrase>", 0, 1, "private passphrase"),
		help = arg_litn("h", "help", 0, 1, "display this help and exit"),
		verbose = arg_litn("v", "verbose", 0, 1, "verbose output and exit"),
		version = arg_litn(NULL, "version", 0, 1, "display version info and exit"),
		end = arg_end(1),
	};
	const int nerrors = arg_parse(argc, argv, argtable);

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
			setColor(RED);
			arg_print_errors(stdout, end, PC2_PROG_EXEC_NAME);
			resetColor();
			if (help->count == 0)
			{
				printf("Try '");
				setColor(GREEN);
				printf("%s --help", PC2_PROG_EXEC_NAME);
				resetColor();
				printf("' for more information.\n");
			}
				
		}
		else
		{
			pc2_set_verbose(verbose->count > 0 ? 1 : 0);
			pc2_hash_pass_t hp_passphrase;
			pc2_hash_pass_t hp_tag;
			if(passphrase->count == 0)
				hp_passphrase = hash_pass_create_from_user_input("Passphrase");
			else
				hp_passphrase = hash_pass_create_manually((uint8_t*)passphrase->sval[0]);
			pc2_hash_pass_set_salt(&hp_passphrase, PC2_BASE_SALT);
			if (tag->count == 0)
				hp_tag = hash_pass_create_from_user_input("Tag");
			else
				hp_tag = hash_pass_create_manually((uint8_t*)tag->sval[0]);
			pc2_hash_pass_set_salt(&hp_tag, PC2_BASE_SALT);

			pc2_hash_pass_t final_hash = pc2_hash_pass_get_final(&hp_passphrase, &hp_tag);

			if (pc2_get_verbose())
			{
				puts("Hash 1 :");
				pc2_hash_pass_print(&hp_passphrase);
				puts("");
				puts("Hash 2 :");
				pc2_hash_pass_print(&hp_tag);
				puts("");
			}

			pc2_hash_pass_clean(&hp_passphrase);
			pc2_hash_pass_clean(&hp_tag);
			
			arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
			return final_hash;
		}
	}
	
	// No Options
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	pc2_hash_pass_t empty = { 0 };
	empty.is_empty = 1;
	return empty;
}
