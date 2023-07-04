// Name: Chungon Tse
// Seneca Student ID: 154928188
// Seneca email: cotse@myseneca.ca
// Date of completion: 25 Nov 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <deque>
#include "LineManager.h"

namespace sdds
{
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;
	/*The file contains the linkage between workstation pairs. The format of each record in the file is WORKSTATION|NEXT_WORKSTATION. The records themselves are not in any particular order.*/
	LineManager::LineManager(const std::string& fileName, const std::vector<Workstation*>& stations)
	{
		Utilities localtoken;
		std::ifstream file(fileName);
		size_t localpos = 0;
		bool localmore = true;
		std::string localstr;
		//This function stores the workstations in the order received from the file in the m_activeLine instance variable.
		//It loads the contents of the file, stores the address of the next workstation in each element of the collection
		Workstation* currentStn{};
		Workstation* nextStn{};//a pointer
		Workstation* firstStation{};//
		std::string current{}, next{};
		if (!file) {
			throw "Cannot open file!!";
		}
		else {
			while (getline(file, localstr)) {
				current = localtoken.extractToken(localstr, localpos, localmore);
				//next = localmore ? localtoken.extractToken(localstr, localpos, localmore) : "";
				/*https://cplusplus.com/reference/algorithm/find_if/
				Find element in range
				Returns an iterator to the first element in the range[first, last) for which pred returns true.
				If no such element is found, the function returns last.*/
				currentStn = *find_if(stations.begin(), stations.end(), [&](const Workstation* wkstn) {
					return (wkstn->getItemName() == current);
					});
				m_activeLine.push_back(currentStn);

				if (localmore) {
					next = localtoken.extractToken(localstr, localpos, localmore);
					nextStn = *find_if(stations.begin(), stations.end(), [&](const Workstation* wkstn) {//
						return (wkstn->getItemName() == next);
						});
					currentStn->setNextStation(nextStn);
				}
			}
			//identifies the first station in the assembly line and stores its address in the m_firstStation attribute.
			/*There are multiple ways of doing this.
			1. You can use an auto loop and use none_of.
			2. You can use for_each and then find_if the m_activeLine contains the first station.
			3. Here, it means, find_if there is the first station
			https://cplusplus.com/reference/algorithm/none_of/
			Inside find_if, nest a none_of to see if not a single wkstn matches.
			If there is no next station (none_of returns true), then the only station is itself the "first" station.
			*/
			/*m_firstStation = *find_if(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* anyWkstn) {
				return (none_of(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* wkstn) {
					return (wkstn->getNextStation() == anyWkstn); }));
				});*/
			for_each(stations.begin(), stations.end(), [&](Workstation* station) {
				firstStation = *find_if(stations.begin(), stations.end(), [&](Workstation* anyWkStn) {
					return anyWkStn->getNextStation() == firstStation;
					});
				});//1 Dec
				
			m_firstStation = firstStation;//

			//This function also updates the attribute that holds the total number of orders in the g_pending queue.
			m_cntCustomerOrder = g_pending.size();
			file.close();
		}
	}
	void LineManager::reorderStations()
	{
		Workstation* local = m_firstStation;
		std::vector<Workstation*> wkstn;//m_activeLine
		while (local) {
			wkstn.push_back(local);
			//Adds a new element at the end of the vector, after its current last element.
			//The content of val is copied (or moved) to the new element.

			local = local->getNextStation();
		}
		this->m_activeLine = wkstn;//stores the reordered collection in the same instance variable
	}
	bool LineManager::run(std::ostream& os)
	{
		static size_t local = 0;
		os << "Line Manager Iteration: " << ++local << std::endl;
		if (!g_pending.empty()) {
			*m_activeLine.front() += std::move(g_pending.front());
			//moves the order at the front of the g_pending queue to the m_firstStation and remove it from the queue.
			//This function moves only one order to the line on a single iteration.
			g_pending.pop_front();
		}
		for (auto& eachStn : m_activeLine) {
			eachStn->fill(os);
		}
		for (auto* eachStn : m_activeLine) {
			eachStn->attemptToMoveOrder();
		}
		bool ok = false;
		m_cntCustomerOrder == g_completed.size() + g_incomplete.size() ? ok = true : ok = false;
		return ok;
	}
	void LineManager::display(std::ostream& os) const
	{
		std::for_each(m_activeLine.cbegin(), m_activeLine.cend(), [&](Workstation* wkstn) {
			wkstn->display(os);
			});
	}
}