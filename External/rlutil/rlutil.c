#include "rlutil.h"

const RLUTIL_STRING_T ANSI_CLS = "\033[2J\033[3J";
const RLUTIL_STRING_T ANSI_CONSOLE_TITLE_PRE = "\033]0;";
const RLUTIL_STRING_T ANSI_CONSOLE_TITLE_POST = "\007";
const RLUTIL_STRING_T ANSI_ATTRIBUTE_RESET = "\033[0m";
const RLUTIL_STRING_T ANSI_CURSOR_HIDE = "\033[?25l";
const RLUTIL_STRING_T ANSI_CURSOR_SHOW = "\033[?25h";
const RLUTIL_STRING_T ANSI_CURSOR_HOME = "\033[H";
const RLUTIL_STRING_T ANSI_BLACK = "\033[22;30m";
const RLUTIL_STRING_T ANSI_RED = "\033[22;31m";
const RLUTIL_STRING_T ANSI_GREEN = "\033[22;32m";
const RLUTIL_STRING_T ANSI_BROWN = "\033[22;33m";
const RLUTIL_STRING_T ANSI_BLUE = "\033[22;34m";
const RLUTIL_STRING_T ANSI_MAGENTA = "\033[22;35m";
const RLUTIL_STRING_T ANSI_CYAN = "\033[22;36m";
const RLUTIL_STRING_T ANSI_GREY = "\033[22;37m";
const RLUTIL_STRING_T ANSI_DARKGREY = "\033[01;30m";
const RLUTIL_STRING_T ANSI_LIGHTRED = "\033[01;31m";
const RLUTIL_STRING_T ANSI_LIGHTGREEN = "\033[01;32m";
const RLUTIL_STRING_T ANSI_YELLOW = "\033[01;33m";
const RLUTIL_STRING_T ANSI_LIGHTBLUE = "\033[01;34m";
const RLUTIL_STRING_T ANSI_LIGHTMAGENTA = "\033[01;35m";
const RLUTIL_STRING_T ANSI_LIGHTCYAN = "\033[01;36m";
const RLUTIL_STRING_T ANSI_WHITE = "\033[01;37m";
const RLUTIL_STRING_T ANSI_BACKGROUND_BLACK = "\033[40m";
const RLUTIL_STRING_T ANSI_BACKGROUND_RED = "\033[41m";
const RLUTIL_STRING_T ANSI_BACKGROUND_GREEN = "\033[42m";
const RLUTIL_STRING_T ANSI_BACKGROUND_YELLOW = "\033[43m";
const RLUTIL_STRING_T ANSI_BACKGROUND_BLUE = "\033[44m";
const RLUTIL_STRING_T ANSI_BACKGROUND_MAGENTA = "\033[45m";
const RLUTIL_STRING_T ANSI_BACKGROUND_CYAN = "\033[46m";
const RLUTIL_STRING_T ANSI_BACKGROUND_WHITE = "\033[47m";