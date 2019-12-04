#include "program.h"

#include <cstdio>
#include <fstream>

namespace
{
	void print_usage()
	{
		std::printf("usage: aoc2019 <program> <input-path>\n"
			"\n"
			"\tThe program name is usually of the format 'D', where D is a day between 1 and 30.\n");
	}
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::fprintf(stderr, "fatal: Invalid arguments!\n"
			"\n"
		);
		print_usage();
		return 1;
	}

	char const* const program_name = argv[1];

	if (!kab::programs.has_program(program_name))
	{
		std::fprintf(stderr, "fatal: Could not find program '%s'\n", program_name);
		return 1;
	}

	char const* const input_path = argv[2];

	std::ifstream input(input_path);
	if (!input)
	{
		std::fprintf(stderr, "fatal: Could not find input '%s'\n", input_path);
		return 1;
	}

	std::printf("Running program '%s'\n\n", program_name);
	kab::programs.run_program(program_name, input);
}