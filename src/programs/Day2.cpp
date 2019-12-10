#include "stream.h"
#include "program.h"

namespace kab
{
	namespace
	{
		void run_add(std::vector<size_t>& memory, std::vector<size_t>::iterator& pointer)
		{
			size_t const input_position_1 = pointer[1];
			size_t const input_position_2 = pointer[2];
			size_t const output_position = pointer[3];
			memory[output_position] = memory[input_position_1] + memory[input_position_2];
			pointer += 4;
		}

		void run_multiply(std::vector<size_t>& memory, std::vector<size_t>::iterator& pointer)
		{
			size_t const input_position_1 = pointer[1];
			size_t const input_position_2 = pointer[2];
			size_t const output_position = pointer[3];
			memory[output_position] = memory[input_position_1] * memory[input_position_2];
			pointer += 4;
		}
		
		void run_program(std::vector<size_t>& current_memory)
		{
			bool done = false;
			auto mem_it = current_memory.begin();
			while (!done)
			{
				size_t const operation = mem_it[0];
				switch(operation)
				{
				case 1: run_add(current_memory, mem_it); break;
				case 2: run_multiply(current_memory, mem_it); break;
				case 99: done = true; break;
				default: throw std::runtime_error("Invalid input!");
				}
			}
		}

		size_t compute_program(std::vector<size_t> program, size_t noun, size_t verb)
		{
			program[1] = noun;
			program[2] = verb;

			run_program(program);

			return program[0];
		}
		
		class day2 : public program
		{
			std::string_view get_name() const noexcept override { return "2"; }
			void run(std::istream& input) override
			{
				std::vector<size_t> const memory{ istream_joined_iterator<size_t>(input, ','), istream_joined_iterator<size_t>() };

				std::printf("1202 result: %llu\n", compute_program(memory, 12, 2));

				for(size_t noun = 0; noun < 100; ++noun)
				{
					for(size_t verb = 0; verb < 100; ++verb)
					{
						if(compute_program(memory, noun, verb) == 19690720)
						{
							std::printf("Program with the result 19690720: noun=%llu, verb=%llu", noun, verb);
						}
					}
				}
			}
		public:
			day2()
			{
				programs.register_program(*this);
			}
		} program;
	}
}