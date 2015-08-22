AM_CPPFLAGS = -fPIC -g3

AM_LDFLAGS = -pthread 


bin_PROGRAMS = server

server_SOURCES = \
	CMysqlDefine.h	CMysqlLoginer.cpp \
	CMysqlServer.cpp	CMysqlConnection.cpp \
	CMysqlState.cpp	CMysqlUtil.cpp \
	TestMain.cpp	ThreadPool.cpp
	
noinst_HEADERS = \
	CMysqlDefine.h 		CMysqlLoginer.h \
	CMysqlServer.h 		CMysqlConnection.h \
	CMysqlState.h 		CMysqlUtil.h \
	Logs.h 	 		ThreadPool.h

server_LDADD = packet/libpacket.a

SUBDIRS = packet
DIST_SUBDIRS = packet


