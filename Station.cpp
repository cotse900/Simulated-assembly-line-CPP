// Name: Chungon Tse
// Seneca Student ID: 154928188
// Seneca email: cotse@myseneca.ca
// Date of completion: 9 Nov 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& str)
	{
		Utilities ut;
		size_t localnextpos = 0;
		bool localmore = false;
		stationid = ++id_generator;
		//name, serial, qty, desc
		itemname = ut.extractToken(str, localnextpos, localmore);
		serial = std::stoi(ut.extractToken(str, localnextpos, localmore));
		qtyitems = std::stoi(ut.extractToken(str, localnextpos, localmore));
		if (m_widthField < ut.getFieldWidth()) {
			m_widthField = ut.getFieldWidth();
		}
		description = ut.extractToken(str, localnextpos, localmore);
	}
	const std::string& Station::getItemName() const
	{
		return itemname;
	}
	std::size_t Station::getNextSerialNumber()
	{
		return serial++;
	}
	std::size_t Station::getQuantity() const
	{
		return qtyitems;
	}
	void Station::updateQuantity()
	{
		qtyitems < 0 ? 0 : qtyitems--;
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setfill('0') << std::setw(3) << std::right << stationid << " | ";
		os << std::setw(m_widthField) << std::left << std::setfill(' ') << itemname << " | ";
		os << std::setw(6) << std::setfill('0') << std::right << serial << " | ";
		if (full) {
			os << std::setfill(' ') << std::setw(4) << qtyitems << " | " << description;
		}
		os << "\n";
	}
}