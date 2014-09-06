AM_CPPFLAGS = -fPIC

AM_LDFLAGS = -pthread -g


bin_PROGRAMS = server

server_SOURCES = \
	CMysqlServer.cpp	CMysqlUtil.cpp \
	CSession.cpp	ThreadPool.cpp \
	TestMain.cpp
	
noinst_HEADERS = \
	CMysqlServer.h	CMysqlUtil.h \
	CSession.h		ThreadPool.h \
	CDefine.h		Logs.h

server_LDADD = packet/libpacket.a

SUBDIRS = packet
DIST_SUBDIRS = packet
