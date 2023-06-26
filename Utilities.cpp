// Name: Chungon Tse
// Seneca Student ID: 154928188
// Seneca email: cotse@myseneca.ca
// Date of completion: 5 Nov 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"

namespace sdds
{
	//shared by Utilities objects
	char Utilities::m_delimiter = ',';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string localtoken{};
		size_t first_pos = next_pos;
		next_pos = str.find(m_delimiter, first_pos);

		if (first_pos == next_pos) {
			more = false;
			throw "No token found!";
		}
		else if (next_pos == std::string::npos) {
			more = false;
			localtoken = str.substr(first_pos);
		}
		else {
			more = true;
			localtoken = str.substr(first_pos, next_pos - first_pos);
		}
		if (m_widthField < localtoken.length()) {
			m_widthField = localtoken.length();
		}
		next_pos++;
		//trim space
		localtoken.erase(0, localtoken.find_first_not_of(' '));
		localtoken.erase(localtoken.find_last_not_of(' ') + 1);
		return localtoken;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}