#include "stream.h"
#include "program.h"

namespace kab
{
	namespace
	{
		void run_program(std::vector<size_t>& current_memory)
		{
			auto mem_it = current_memory.begin();
			while (mem_it != current_memory.end())
			{
				size_t const operation = mem_it[0];
				if (operation == 1)
				{
					size_t const input_position_1 = mem_it[1];
					size_t const input_position_2 = mem_it[2];
					size_t const output_position = mem_it[3];
					current_memory[output_position] = current_memory[input_position_1] + current_memory[input_position_2];
					mem_it += 4;
				} else if (operation == 2)
				{
					size_t const input_position_1 = mem_it[1];
					size_t const input_position_2 = mem_it[2];
					size_t const output_position = mem_it[3];
					current_memory[output_position] = current_memory[input_position_1] * current_memory[input_position_2];
					mem_it += 4;
				} else if (operation == 99)
				{
					break;
				} else
				{
					throw std::runtime_error("Invalid input!");
				}
			}
		}
		
		class day2 : public program
		{
			std::string_view get_name() const noexcept override { return "2"; }
			void run(std::istream& input) override
			{
				std::vector<size_t> const original_memory{ istream_joined_iterator<size_t>(input, ','), istream_joined_iterator<size_t>() };

				{
					std::vector<size_t> current_memory = original_memory;

					current_memory[1] = 12;
					current_memory[2] = 2;
					
					run_program(current_memory);

					std::printf("Memory 0: %llu\n", current_memory[0]);
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