#pragma once

#include <iostream>
#include <string_view>
#include <string>

namespace kab
{
	template<typename T, typename CharT=char, class Traits=std::char_traits<CharT>>
	class istream_joined_iterator
	{
		std::istream* m_stream;
		char m_separator;
		T m_value;
	public:
		istream_joined_iterator()
			: m_stream(nullptr)
		{
			
		}
		
		istream_joined_iterator(std::istream& i, char separator)
			: m_stream(&i)
			, m_separator(separator)
		{
			if(!(*m_stream >> m_value))
			{
				m_stream = nullptr;
			}
		}
		
		using value_type = T;
		using reference = const T&;
		using pointer = const T*;
		using iterator_category = std::input_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using char_traits = Traits;
		using istream_type = std::basic_istream<CharT, Traits>;

		reference operator*() const noexcept
		{
			return m_value;
		}

		pointer operator->() const noexcept
		{
			return &m_value;
		}

		istream_joined_iterator& operator++()
		{
			char separator;
			if (m_stream != nullptr &&
				(
					!(*m_stream >> separator)
					|| separator != m_separator
					|| !(*m_stream >> m_value)
				)
			)
			{
				m_stream = nullptr;
			}
			return *this;
		}

		istream_joined_iterator operator++(int)
		{
			istream_joined_iterator other = *this;
			++(*this);
			return other;
		}

		bool operator==(istream_joined_iterator const& rhs) noexcept
		{
			return m_stream == rhs.m_stream;
		}

		bool operator!=(istream_joined_iterator const& rhs) noexcept
		{
			return m_stream != rhs.m_stream;
		}
	};

	template<typename CharT, class Traits>
	class istream_joined_iterator<std::string, CharT, Traits>
	{
		std::istream* m_stream;
		char m_separator;
		std::string m_value;
	public:
		istream_joined_iterator()
			: m_stream(nullptr)
		{

		}

		istream_joined_iterator(std::istream& i, char separator)
			: m_stream(&i)
			, m_separator(separator)
		{
			if (!std::getline(*m_stream, m_value, m_separator))
			{
				m_stream = nullptr;
			}
		}

		using value_type = std::string;
		using reference = const std::string&;
		using pointer = const std::string*;
		using iterator_category = std::input_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using char_traits = Traits;
		using istream_type = std::basic_istream<CharT, Traits>;

		reference operator*() const noexcept
		{
			return m_value;
		}

		pointer operator->() const noexcept
		{
			return &m_value;
		}

		istream_joined_iterator& operator++()
		{
			char separator;
			if (m_stream != nullptr &&
				(
					!(*m_stream >> separator)
					|| separator != m_separator
					|| !std::getline(*m_stream, m_value, m_separator)
					)
				)
			{
				m_stream = nullptr;
			}
			return *this;
		}

		istream_joined_iterator operator++(int)
		{
			istream_joined_iterator other = *this;
			++(*this);
			return other;
		}

		bool operator==(istream_joined_iterator const& rhs) noexcept
		{
			return m_stream == rhs.m_stream;
		}

		bool operator!=(istream_joined_iterator const& rhs) noexcept
		{
			return m_stream != rhs.m_stream;
		}
	};
}