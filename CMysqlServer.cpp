/*
 * CMysqlServer.cpp
 *
 *  Created on: 2014-9-2
 *      Author: yukai
 */

#include "CMysqlServer.h"
#include "CMysqlFieldPacket.h"
#include "CMysqlEofPacket.h"

CMysqlServer::CMysqlServer():port_(2345),work_threads_count_(4),connection_max_count_(300) {

}

CMysqlServer::~CMysqlServer() {

}

int CMysqlServer::start() {
	Logs::log("启动cliams mysql server...");
	int ret;
	int rc;

	initialize();

	threadpool_ = new ThreadPool();
	if (threadpool_->Thread_Pool_init(work_threads_count_) == false){
		Logs::elog("thread pool init failed.");
		return 0;
	}


	if(listen_port(port_) == C_ERROR){
		return 0;
	}

	int epoll_fd;
	if ((epoll_fd = epoll_create(connection_max_count_)) == -1){
		Logs::elog("%s. create epoll failed.", strerror(errno));
		close(listening_fd);
		return 0;
	}

	epoll_event event_list[connection_max_count_];

	epoll_event event;
	event.events = EPOLL_IN|EPOLL_ET;
	event.data.fd = epoll_fd;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listening_fd, &event)){
		Logs::elog("%s. register epoll failed. ", strerror(errno));
		close(listening_fd);
		close(epoll_fd);
		return 0;
	}
	while (1){
		if ((ret = epoll_wait(epoll_fd, event_list, connection_max_count_, EPOLLTIMEOUT)) == -1){
			Logs::elog("%s. wait epoll failed. ", strerror(errno));
			break;
		}
		else if (ret == 0){
			Logs::log("time out, keep waiting...");
		}
		else{
			for (int i = 0; i < ret; ++i){
				// exit abnormally
				int ready_fd = event_list[i].data.fd;
				if ((event_list[i].events & EPOLLERR) || (event_list[i].events & EPOLLHUP) || !(event_list[i].events & EPOLLIN))
				{
					sockaddr_in temp = fd_to_session.at(ready_fd)->get_addr();
					Logs::elog("%s.%d exit abnormally.\n",inet_ntoa(temp.sin_addr), ntohs(temp.sin_port));
					close(ready_fd);
					epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ready_fd, NULL);	// unregister this fd
					delete fd_to_session.at(ready_fd);
					fd_to_session.erase(ready_fd);
					continue;
				}

				Logs::log("listen fd is:	%d", listen_fd);
				Logs::log("available fd is:	%d", ready_fd);
				if (ready_fd == listening_fd){
					AcceptConnection(epoll_fd, listen_fd);
				}
				else{
					if (ReceiveData(event_list[i].data.fd) == true){

//						SendMessageBack(event_list[i].data.fd);
					}
				}
			}
		}
	}

}

int CMysqlServer::initialize() {
	Logs::log("初始化服务器！");
	set_work_threads_count();
	set_port();
	set_connection_max_count();

	return 0;
}

int CMysqlServer::listen_port(port){
	if ((listening_fd = socket(AF_INT, SOCKET_STREAM, 0)) == -1){
		Logs::elog("%s. can't create socket.", strerror(errno));
		return C_ERROR;
	}

	sockaddr_in addr;

	bzero(&addr, sizeof(addr));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if (bind(listening_fd, (sockaddr*)&addr, sizeof(addr)) == -1){
		Logs::elog("%s. can't bind socket.", strerror(errno));
		close(listening_fd);
		return C_ERROR;
	}

	if (listen(listening_fd, connection_max_count_) == -1){
		Logs::elog("%s. can't listen socket.", strerror(errno));
		close(listening_fd);
		return C_ERROR;
	}
	return C_SUCCESS;
}

bool CMysqlServer::AcceptConnection(int epoll_fd, int fd)
{
	Logs::log("in AcceptConnection function");
	sockaddr_in connected_socket;
	bzero(&connected_socket, sizeof(connected_socket));

	socklen_t length = sizeof(connected_socket);
	int connected_fd = accept(fd, (sockaddr*)&connected_socket, &length);
	if (connected_fd < 0){
		Logs::elog("%s. accept socket failed.", strerror(errno));
		return false;
	}
	else{
		Logs::log("server fd is %d",connected_fd);
		Logs::log("accept socket connection from %s:%d\n", inet_ntoa(connected_socket.sin_addr), ntohs(connected_socket.sin_port));
//		fd_to_adddr.insert(pair<int, sockaddr_in>(connected_fd, connected_socket));
		fd_to_session.insert(pair<int, Session*>(fd, new Session(fd)));
	}

	// register new socket to epoll
	epoll_event event;
	event.events = EPOLLIN|EPOLLET;
	//make sure this fd equal with connected socket fd returned from accept()
	event.data.fd = connected_fd;
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connected_fd, &event);

	return true;
}

bool CMysqlServer::ReceiveData(inf fd)
{
	Logs::log("in ReceiveData function");
	Session *s;
	if (fd_to_session.find(fd) == fd_to_session.end()){
		Logs::elog("fd is not in map");
	}
	else{
		s = fd_to_session.find(fd);
	}

	memset(buf, 0, sizeof(buf));
	int recv_count = recv(fd, buf, MESSAGE_LENGTH_MAX, 0);
	if (recv_count < 0){
		Logs::elog(" read data failed.");
		return false;
	}
	else if (recv_count == 0){
		Logs::elog("received nothing . maybe client close normally\n");
		return false;
	}

	sockaddr_in client_addr = fd_to_session.at(fd)->get_addr();
	Logs::log("receive content:%s\n		------from %s:%d\n", buf, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	return true;
}
