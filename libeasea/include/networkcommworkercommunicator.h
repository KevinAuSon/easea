/*
 *    Copyright (C) 2013 Waldo Cancino

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef NETWORKCOMMWORKERCOMMUNICATOR_H
#define NETWORKCOMMWORKERCOMMUNICATOR_H


#include "commworkercomunitaror.h"


/**
 * @brief Manages the network communications for a worker
 * 
 */
class NetworkCommWorkerCommunicator : public CommWorkerCommunicator
{
  private:
    int ServerSocket; // listen socket
    /**
     * @brief determine ip address from a worker
     */
    int determine_ipaddress();
public:
  int init();
  NetworkCommWorkerCommunicator(CommWorker *w, std::queue<std::string> *d, int db = 1):CommWorkerCommunicator(w,d,db) {};
  int receive();
  int send(char* individual, CommWorker& destination);
};

#endif // NETWORKCOMMWORKERCOMMUNICATOR_H
