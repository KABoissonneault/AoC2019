#include "program.h"

#include <algorithm>

namespace kab
{
	program_manager programs;

	void program_manager::register_program(program& p)
	{
		m_programs.push_back(&p);
	}

	std::vector<program*>::const_iterator program_manager::find_program(std::string_view name) const noexcept
	{
		return std::find_if(m_programs.begin(), m_programs.end(), [name](program* p)
		{
			return p->get_name() == name;
		});
	}

	bool program_manager::has_program(std::string_view name) const noexcept
	{
		return find_program(name) != m_programs.end();
	}

	void program_manager::run_program(std::string_view name, std::istream& input)
	{
		auto const it_found = find_program(name);

		if (it_found == m_programs.end())
		{
			throw std::runtime_error(std::string("Could not find program: ").append(name));
		}

		program& p = **it_found;
		p.run(input);
	}
}