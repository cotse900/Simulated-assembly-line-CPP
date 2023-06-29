// Name: Chungon Tse
// Seneca Student ID: 154928188
// Seneca email: cotse@myseneca.ca
// Date of completion: 10 Nov 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include "CustomerOrder.h"

namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const std::string& coStr)
	{
		/*vector and STL algo approach*/
		Utilities ut;
		bool localmore = true;
		size_t localnextpos = 0;
		//Cust Name
		m_name = ut.extractToken(coStr, localnextpos, localmore);
		//Prod Name
		m_product = ut.extractToken(coStr, localnextpos, localmore);

		//start vec
		std::vector<Item*> pushItems;
		Item* newItem;

		while (localmore) {
			newItem = new Item(ut.extractToken(coStr, localnextpos, localmore));
			pushItems.push_back(newItem);
		}
		m_cntItem = pushItems.size();
		m_lstItem = new Item * [m_cntItem];

		size_t i{};//for the loop below
		std::for_each(pushItems.begin(), pushItems.end(), [&](Item* addItem) {
			m_lstItem[i++] = addItem;
			});

		if (m_widthField < ut.getFieldWidth()) {
			m_widthField = ut.getFieldWidth();
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& src)
	{
		throw std::string("No copying is allowed!!!!");
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& move) noexcept
	{
		*this = std::move(move);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& move) noexcept
	{
		if (this != &move) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_name = move.m_name;
			m_product = move.m_product;
			m_cntItem = move.m_cntItem;
			m_lstItem = move.m_lstItem;

			move.m_name = "";
			move.m_product = "";
			move.m_cntItem = 0;
			move.m_lstItem = nullptr;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) filled = false;//if not all filled then false
		}
		return filled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName)
				filled = m_lstItem[i]->m_isFilled;
			//true only when all filled 
		}
		return filled;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool flag = true;
		for (size_t i = 0; i < m_cntItem && flag; i++)
		{
			if (station.getItemName() == m_lstItem[i]->m_itemName && m_lstItem[i]->m_isFilled == false)//
			{
				if (station.getQuantity() > 0)
				{
					flag = false;//when you already count itemName x, turn this flag to false
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();//update serial
					m_lstItem[i]->m_isFilled = true;//update bool filled
					station.updateQuantity();//subtracts 1 from inventory

					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {

			os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - ";
			m_lstItem[i]->m_isFilled ? os << "FILLED" : os << "TO BE FILLED";
			os << std::endl;

		}
	}
}