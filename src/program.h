#pragma once

#include <string_view>
#include <vector>

namespace kab
{
	class program 
	{
	public:
		virtual std::string_view get_name() const noexcept = 0;
		virtual void run(std::istream& input) = 0;
	};

	class program_manager 
	{
		std::vector<program*> m_programs;

		std::vector<program*>::const_iterator find_program(std::string_view name) const noexcept;
	public:
		void register_program(program& p);
		bool has_program(std::string_view name) const noexcept;
		void run_program(std::string_view name, std::istream& input);
	};

	extern program_manager programs;
}