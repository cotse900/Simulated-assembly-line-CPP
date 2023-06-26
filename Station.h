// Name: Chungon Tse
// Seneca Student ID: 154928188
// Seneca email: cotse@myseneca.ca
// Date of completion: 5 Nov 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

namespace sdds
{
	class Station
	{
		size_t stationid{};
		std::string itemname{};
		std::string description{};
		unsigned serial{};
		unsigned qtyitems{};

		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string&);
		const std::string& getItemName() const;
		std::size_t getNextSerialNumber();
		std::size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};

}

#endif //!! SDDS_STATION_H