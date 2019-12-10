#include "program.h"
#include "stream.h"

#include <sstream>

namespace kab
{
	struct vector2i
	{
		int x, y;
	};

	vector2i& operator+=(vector2i& lhs, vector2i const& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		
		return lhs;
	}
	
	struct line2i
	{
		vector2i position;
		vector2i direction;
	};
	
	enum class direction
	{
		up,
		left,
		down,
		right,
	};
	
	vector2i get_direction_vector(direction d, int magnitude = 1)
	{
		switch(d)
		{
		case direction::up: return vector2i{ 0, magnitude };
		case direction::left : return vector2i{ -magnitude, 0 };
		case direction::down: return vector2i{ 0, -magnitude };
		case direction::right: return vector2i{ magnitude, 0 };
		}
		throw std::runtime_error("what");
	}

	direction to_direction(char c)
	{
		switch(c)
		{
		case 'U': return direction::up;
		case 'L': return direction::left;
		case 'D': return direction::down;
		case 'R': return direction::right;
		}
		throw std::runtime_error("Wrong input, dude");
	}

	int to_integer(char c)
	{
		return c - '0';
	}

	struct program_token
	{
		direction dir;
		int magnitude;
	};

	std::istream& operator>>(std::istream& i, program_token& token)
	{
		char c;
		if(!(i >> c))
		{
			return i;
		}

		token.dir = to_direction(c);

		i >> token.magnitude;

		return i;
	}

	struct program_input
	{
		std::vector<line2i> wire1;
		std::vector<line2i> wire2;
	};
	
	std::vector<line2i> tokens_to_lines(std::vector<program_token> const& tokens)
	{
		std::vector<line2i> lines;		
		lines.reserve(lines.size());
		vector2i position{0, 0};
		for(program_token const& token : tokens)
		{
			vector2i const direction_vector = get_direction_vector(token.dir, token.magnitude);
			lines.push_back(line2i{ position, direction_vector });
			position += direction_vector;
		}
		return lines;
	}

	std::vector<program_token> get_tokens(std::string const& line)
	{
		std::stringstream ss;
		ss << line;
		return std::vector<program_token>{ istream_joined_iterator<program_token>(ss, ','), istream_joined_iterator<program_token>() };
	}

	program_input make_program_input(std::istream& i)
	{
		std::string line1, line2;
		std::getline(i, line1);
		std::getline(i, line2);

		return program_input
		{
			tokens_to_lines(get_tokens(line1)),
			tokens_to_lines(get_tokens(line2)),
		};		
	}

	bool intersect(line2i const& lhs, line2i const& rhs)
	{
		
	}

	std::vector<vector2i> get_intersection_points(program_input const& input)
	{
		for(line2i const& wire1_line : input.wire1)
		{
			for(line2i const& wire2_line : input.wire2)
			{
				
			}
		}
	}
	
	class day3 : public program
	{		
		std::string_view get_name() const noexcept override { return "3"; }
		void run(std::istream& i) override
		{
			program_input const input = make_program_input(i);

			
		}
	} p;
}