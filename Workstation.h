// Name: Chungon Tse
// Seneca Student ID: 154928188
// Seneca email: cotse@myseneca.ca
// Date of completion: 10 Nov 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds
{
	//holds the orders to be placed onto the assembly line at the first station.
	extern std::deque<CustomerOrder> g_pending;
	//holds the orders that have been removed from the last station and have been completely filled.
	extern std::deque<CustomerOrder> g_completed;
	//holds the orders that have been removed from the last station and could not be filled completely.
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station
	{
		//orders that have been placed on this station to receive service (or already received service).
		std::deque<CustomerOrder> m_orders{};
		//a pointer to the next Workstation on the assembly line.
		Workstation* m_pNextStation{ nullptr };
	public:
		Workstation(const std::string str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

		//no copying, no moving
		Workstation(const Workstation&) = delete;
		Workstation& operator=(Workstation&) = delete;
		Workstation(Workstation&&) noexcept = delete;
		Workstation& operator=(Workstation&&) noexcept = delete;
	};

}

#endif //!! SDDS_WORKSTATION_H