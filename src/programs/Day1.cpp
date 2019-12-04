#include "program.h"

#include <vector>
#include <iterator>
#include <numeric>

namespace kab
{
	namespace
	{
		int get_fuel_requirement(int weight)
		{
			return (weight / 3) - 2;
		}

		int get_fuel_requirement_recursive(int weight, int total=0)
		{
			const int additional = get_fuel_requirement(weight);
			if (additional <= 0)
			{
				return total;
			}

			return get_fuel_requirement_recursive(additional, total + additional);
		}

		class day1 : program
		{
			std::string_view get_name() const noexcept override { return "1"; }
			void run(std::istream& input) override
			{
				std::vector<int> const numbers{ std::istream_iterator<int>(input), std::istream_iterator<int>() };

				auto const fuel_requirement = std::accumulate(numbers.begin(), numbers.end(), 0, [](int sum, int current)
				{
					return sum + get_fuel_requirement(current);
				});

				std::printf("Total fuel: %d\n", fuel_requirement);

				auto const fuel_requirement_adjusted = std::accumulate(numbers.begin(), numbers.end(), 0, [](int sum, int current)
				{
					return sum + get_fuel_requirement_recursive(current);
				});

				std::printf("Adjusted fuel: %d\n", fuel_requirement_adjusted);
			}

		public:
			day1()
			{
				programs.register_program(*this);
			}
		};

		day1 program;

	}
}