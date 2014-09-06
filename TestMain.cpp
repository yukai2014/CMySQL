/*
 * TestMain.cpp
 *
 *  Created on: 2014-9-6
 *      Author: imdb
 */
#include <iostream>
#include "CMysqlServer.h"
using namespace std;

int main()
{
	CMysqlServer *server = new CMysqlServer();
	server->initialize();
	server->start();
}
