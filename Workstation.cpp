// Name: Chungon Tse
// Seneca Student ID: 154928188
// Seneca email: cotse@myseneca.ca
// Date of completion: 13 Nov 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"

namespace sdds
{
	//passes it to the Station base class.
	Workstation::Workstation(const std::string str) : Station(str) {}

	//this modifier fills the order at the front of the queue if there are CustomerOrders in the queue
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder()
	{
		bool moved = false;
		//https://cplusplus.com/reference/deque/deque/front/
		//https://cplusplus.com/reference/list/list/pop_front/
		if (m_orders.size() > 0) {
			//if the order requires no more service at this station or cannot be filled (not enough inventory),
			//move it to the next station; otherwise do nothing
			if (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() == 0) {
				if (m_pNextStation) {
					m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
				}
				else if (m_orders.front().isOrderFilled()) {
					g_completed.push_back(std::move(m_orders.front()));
				}
				else {
					g_incomplete.push_back(std::move(m_orders.front()));
				}
				m_orders.pop_front();
				moved = true;
			}
			//if there is no next station in the assembly line,
			//then the order is moved into g_completed or g_incomplete queue
		}
		return moved;
	}
	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const
	{
		//this query inserts the name of the Item for which the current object is responsible into stream
		if (m_pNextStation) {
			os << getItemName() << " --> " << m_pNextStation->getItemName() << '\n';
		}
		else {//last workstation
			os << getItemName() << " --> End of Line" << '\n';
		}
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}