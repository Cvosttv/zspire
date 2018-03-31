#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdarg.h"
#include "../includes/zs-logger.h"
FILE* outfile;
bool useFile = false;

void ZSpire::close_outputFile(){
	if (useFile == true) {
		fclose(outfile);
	}
}

void ZSpire::open_outputFile(const char* fpath) {
	useFile = true;
	outfile = fopen(fpath, "w");
	
}

	void ZSpire::Log(uint TYPE, const char *format, ...)
	{
		switch (TYPE)
		{
		case TYPE_ERROR:
		{printf("%s", "ERROR: "); 
		if (useFile == true) {
			fprintf(outfile, "%s", "ERROR: ");
		}
		}break;

		case TYPE_OPENGL:
		{printf("%s", "OPENGL: "); 
		if (useFile == true) {
			fprintf(outfile, "%s", "OPENGL: ");
		}
		}break;

		case TYPE_LOG:
		{printf("%s", "LOG: "); 
		if (useFile == true) {
			fprintf(outfile, "%s", "LOG: ");
		}
		}break;

		case TYPE_ENGINE:
		{printf("%s", "ENGINE: ");
		if (useFile == true) {
			fprintf(outfile, "%s", "ENGINE: ");
		}
		}break;
	
		case TYPE_SCRIPTERROR:
		{printf("%s", "LUA ERROR: "); 
		if (useFile == true) {
			fprintf(outfile, "%s", "LUA ERROR: ");
		}
		}break;
	}

		va_list arglist;
		va_start(arglist, format);
		int i;
		for (i = 0; format[i]; i++)
		{
			if (format[i] == '%')
			{
				i++;
				switch (format[i])
				{
				case 'i':
				{
					int i = va_arg(arglist, int);

					printf("%i", i);
					if (useFile == true) {
						fprintf(outfile, "%i", i);
					}
					}; break;
				case 'd':
				{
					double d = va_arg(arglist, double);
					printf("%f", d);

				}; break;
				case 'c':
				{
					char c = va_arg(arglist, int);
					printf("%c", c);
				}; break;
				case 'p':
				{
					void *p = va_arg(arglist, void*);
					printf("%p", p);
				}; break;

				case 'm':
				{
					printf(" ");
				}; break;

				case 'k':
				{
					printf("\n");
				}; break;

				case 's':
				{
					char *p = va_arg(arglist, char*);
					printf("%s", p);
					if (useFile == true) {
						fprintf(outfile, "%s", p);
					}
					}; break;
				default:


					break;
				}
			}


		}
		printf("%s", "\n");
		if (useFile == true) {
			fprintf(outfile, "%s", "\n");
		}
	}
