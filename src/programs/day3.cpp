#include "program.h"
#include "stream.h"

#include <sstream>
#include <algorithm>

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

	vector2i operator+(vector2i const& lhs, vector2i const& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}

	vector2i operator-(vector2i const& lhs, vector2i const& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y };
	}

	bool operator==(vector2i const& lhs, vector2i const& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	int manhattan_magnitude(vector2i const& v)
	{
		return std::abs(v.x) + std::abs(v.y);
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

	direction get_direction_type(vector2i const& v)
	{
		if (v.y > 0)
		{
			return direction::up;
		}
		else if (v.x < 0)
		{
			return direction::left;
		}
		else if (v.y < 0)
		{
			return direction::down;
		}
		else if (v.x > 0)
		{
			return direction::right;
		}
		throw std::runtime_error("Err...");
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

	bool is_vertical(line2i const& line)
	{
		return line.direction.x == 0;
	}

	bool is_horizontal(line2i const& line)
	{
		return line.direction.y == 0;
	}

	bool parallel(line2i const& lhs, line2i const& rhs)
	{
		return is_vertical(lhs) == is_vertical(rhs);
	}

	bool intersect(line2i const& lhs, line2i const& rhs)
	{
		if (is_vertical(lhs))
		{
			int const 
				l_x = lhs.position.x
				, l_min_y = std::min(lhs.position.y, lhs.position.y + lhs.direction.y)
				, l_max_y = std::max(lhs.position.y, lhs.position.y + lhs.direction.y)
				, r_min_x = std::min(rhs.position.x, rhs.position.x + rhs.direction.x)
				, r_max_x = std::max(rhs.position.x, rhs.position.x + rhs.direction.x)
				, r_y = rhs.position.y
				;

			return l_x >= r_min_x
				&& l_x <= r_max_x
				&& r_y >= l_min_y
				&& r_y <= l_max_y;
		}
		else
		{
			int const
				l_min_x = std::min(lhs.position.x, lhs.position.x + lhs.direction.x)
				, l_max_x = std::max(lhs.position.x, lhs.position.x + lhs.direction.x)
				, l_y = lhs.position.y
				, r_x = rhs.position.x
				, r_min_y = std::min(rhs.position.y, rhs.position.y + rhs.direction.y)
				, r_max_y = std::max(rhs.position.y, rhs.position.y + rhs.direction.y)
				;

			return r_x >= l_min_x
				&& r_x <= l_max_x
				&& l_y >= r_min_y
				&& l_y <= r_max_y
				;
		}
	}

	vector2i intersection_point(line2i const& lhs, line2i const& rhs)
	{
		if (is_vertical(lhs))
		{
			return { lhs.position.x, rhs.position.y };
		}
		else
		{
			return { rhs.position.x, lhs.position.y };
		}
	}

	struct intersection
	{
		vector2i point;
		int wire1_distance;
		int wire2_distance;
	};

	std::vector<intersection> get_intersection_points(program_input const& input)
	{
		std::vector<intersection> points;
		int travel1 = 0;
		for(line2i const& wire1_line : input.wire1)
		{
			int travel2 = 0;
			for(line2i const& wire2_line : input.wire2)
			{
				if (intersect(wire1_line, wire2_line) && !(wire1_line.position == vector2i{ 0, 0 } && wire2_line.position == vector2i{ 0, 0 }))
				{
					vector2i const point = intersection_point(wire1_line, wire2_line);
					int const wire1_distance = travel1 + manhattan_magnitude(point - wire1_line.position);
					int const wire2_distance = travel2 + manhattan_magnitude(point - wire2_line.position);

					points.push_back({ point, wire1_distance, wire2_distance });
				}

				travel2 += manhattan_magnitude(wire2_line.direction);
			}

			travel1 += manhattan_magnitude(wire1_line.direction);
		}
		return points;
	}
	
	class day3 : public program
	{		
		std::string_view get_name() const noexcept override { return "3"; }
		void run(std::istream& i) override
		{
			program_input const input = make_program_input(i);

			std::vector<intersection> const intersection_points = get_intersection_points(input);

			intersection const nearest_point = *std::min_element(intersection_points.begin(), intersection_points.end(),
				[](intersection const& current, intersection const& smallest) -> bool
			{
				return manhattan_magnitude(current.point) < manhattan_magnitude(smallest.point);
			});

			std::printf("Shortest distance: %d\n", manhattan_magnitude(nearest_point.point));

			intersection const earliest_collision = *std::min_element(intersection_points.begin(), intersection_points.end(),
				[](intersection const& current, intersection const& smallest) -> bool
			{
				return current.wire1_distance + current.wire2_distance < smallest.wire1_distance + smallest.wire2_distance;
			});

			std::printf("Wire travel: %d\n", earliest_collision.wire1_distance + earliest_collision.wire2_distance);
		}

	public:
		day3()
		{
			programs.register_program(*this);
		}
	} p;
}