#include "pc2_core.h"

#include <stdio.h>

#include "rlutil.h"
#include "argtable3.h"

#if defined(PC2_USE_VLD) && defined(_DEBUG) && PC2_OS == PC2_OS_WINDOWS
#include "vld.h"
#endif

pc2_hash_pass_t pc2_argtable_config(int argc, char** argv);

int pc2_is_verbose = 0;

int main(int argc, char ** argv)
{
	saveDefaultColor();
	pc2_hash_pass_t hash_final = pc2_argtable_config(argc, argv);

	if(hash_final.is_empty == 0)
	{
		if (pc2_is_verbose)
		{
			setColor(CYAN);
			printf("Hash Password \t: ");
			resetColor();
			pc2_hash_pass_print(&hash_final);
			puts("");
		}
		setColor(GREEN);
		printf("Password : ");
		resetColor();
		const pc2_password_t password_formated = pc2_password_generate(&hash_final);
		for(int j = 0; j < PC2_HASHLEN; j++)
			printf("%c", password_formated.array[j]);
		pc2_hash_pass_clean(&hash_final);
		puts("");
	}
	pc2_check_run_from_console();
	resetColor();
	return 0;
}

pc2_hash_pass_t pc2_argtable_config(int argc, char** argv)
{
	struct arg_str* phrase, * tag;
	struct arg_lit* verbose, * help, * version;
	struct arg_end* end;
	void* argtable[] =
	{
		tag = arg_strn(NULL, NULL, "<tag>", 0, 1, "target tag"),
		phrase = arg_strn("p", "phrase", "<phrase>", 0, 1, "private phrase"),
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
			printf("usage: %s%s", PC2_PROG_EXEC_NAME, PC2_OS == PC2_OS_WINDOWS ? ".exe" : "");
			arg_print_syntax(stdout, argtable, "\n\n");
			arg_print_glossary(stdout, argtable, "  %-25s %s\n");
			puts("");
		}
		// VERSION
		if (version->count > 0)
		{
			printf("%s version : %s\n", PC2_PROG_EXEC_NAME, PC2_VERSION);
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
				printf("%s%s --help", PC2_PROG_EXEC_NAME, PC2_OS == PC2_OS_WINDOWS ? "exe" : "");
				resetColor();
				printf("' for more information.");
			}
		}
		else
		{
			pc2_is_verbose = verbose->count > 0 ? 1 : 0;
			pc2_hash_pass_t hp_phrase;
			pc2_hash_pass_t hp_tag;
			if(phrase->count == 0)
				hp_phrase = pc2_hash_pass_create_from_user_input("Phrase");
			else
				hp_phrase = pc2_hash_pass_create_manually((uint8_t*)phrase->sval[0]);
			pc2_hash_pass_set_salt(&hp_phrase, PC2_BASE_SALT);
			if (tag->count == 0)
				hp_tag = pc2_hash_pass_create_from_user_input("Tag");
			else
				hp_tag = pc2_hash_pass_create_manually((uint8_t*)tag->sval[0]);
			pc2_hash_pass_set_salt(&hp_tag, PC2_BASE_SALT);

			const pc2_hash_pass_t final_hash = pc2_hash_pass_get_final(&hp_phrase, &hp_tag);

			if (pc2_is_verbose)
			{
				setColor(CYAN);
				printf("Hash Phrase \t: ");
				resetColor();
				pc2_hash_pass_print(&hp_phrase);
				puts("");
				setColor(CYAN);
				printf("Hash Tag \t: ");
				resetColor();
				pc2_hash_pass_print(&hp_tag);
				puts("");
			}

			pc2_hash_pass_clean(&hp_phrase);
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