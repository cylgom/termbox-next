#include <stdarg.h>
#include <stdio.h>
#include "termbox.h"

void print_tb(const char* str, int x, int y, uint32_t fg, uint32_t bg)
{
	while (*str)
		{
			uint32_t uni;
			str += utf8_char_to_unicode(&uni, str);
			tb_change_cell(x, y, uni, fg, bg);
			x++;
		}
}

void printf_tb(int x, int y, uint32_t fg, uint32_t bg, const char* fmt, ...)
{
	char buf[4096];
	va_list vl;
	va_start(vl, fmt);
	vsnprintf(buf, sizeof(buf), fmt, vl);
	va_end(vl);
	print_tb(buf, x, y, fg, bg);
}

void print_line(int x, int y, uint32_t format)
{
	printf_tb(x, y, TB_YELLOW | format, TB_BLACK, "Hello, World! (0x%08x)", format);
}

int main()
{
	tb_init();
	tb_clear();

	print_line(0, 0, 0);

	print_line(0, 2, TB_BOLD);
	print_line(0, 3, TB_UNDERLINE);
	print_line(0, 4, TB_REVERSE);
	print_line(0, 5, TB_ITALIC);

	print_line(0, 7, TB_BOLD | TB_UNDERLINE);
	print_line(0, 8, TB_BOLD | TB_REVERSE);
	print_line(0, 9, TB_BOLD | TB_ITALIC);

	print_line(30, 0, TB_UNDERLINE | TB_REVERSE);
	print_line(30, 1, TB_UNDERLINE | TB_ITALIC);

	print_line(30, 3, TB_REVERSE | TB_ITALIC);

	print_line(30, 5, TB_BOLD | TB_UNDERLINE | TB_REVERSE);
	print_line(30, 6, TB_BOLD | TB_UNDERLINE | TB_ITALIC);
	print_line(30, 7, TB_BOLD | TB_REVERSE | TB_ITALIC);
	print_line(30, 8, TB_UNDERLINE | TB_REVERSE | TB_ITALIC);

	print_line(30, 10, TB_BOLD | TB_UNDERLINE | TB_REVERSE | TB_ITALIC);

	tb_present();

	while (1)
		{
			struct tb_event ev;
			int t = tb_poll_event(&ev);

			if (t == -1)
				{
					break;
				}

			if (t == TB_EVENT_KEY)
				{
					break;
				}
		}

	tb_shutdown();
	return 0;
}
