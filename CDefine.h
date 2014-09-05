#ifndef C_DEFINE_H_
#define C_DEFINE_H_

#include <stdint.h>
#include <sys/types.h>

typedef signed char		int8_t;
typedef short int			int16_t;
typedef int					int32_t;
# if __WORDSIZE == 64
typedef long int			int64_t;
# else
__extension__
typedef long long int	int64_t;
#endif

const int64_t TIMEOUT= 30 * 3600;	// timeout is 30 minutes
const int64_t EPOLLTIMEOUT = 1000;	// epoll timeout

/////////////////////////////////////////////////////////////

#define int1store(T,A)       do { *((uint8_t *)(T)) = (uint8_t)(A); } while (0)
#define int2store(T,A)       do { uint def_temp= (uint) (A) ;   \
    *((uint8_t*) (T))=  (uint8_t)(def_temp);                    \
    *((uint8_t*) (T)+1)=(uint8_t)((def_temp >> 8));             \
  } while(0)
#define int3store(T,A)       do { /*lint -save -e734 */ \
    *((uint8_t*)(T))=(uint8_t) ((A));                   \
    *((uint8_t*) (T)+1)=(uint8_t) (((A) >> 8));         \
    *((uint8_t*)(T)+2)=(uint8_t) (((A) >> 16));         \
    /*lint -restore */} while(0)
#define int4store(T,A)       do { *((char *)(T))=(char) ((A));  \
    *(((char *)(T))+1)=(char) (((A) >> 8));                     \
    *(((char *)(T))+2)=(char) (((A) >> 16));                    \
    *(((char *)(T))+3)=(char) (((A) >> 24)); } while(0)
#define int8store(T,A)       do { uint def_temp= (uint) (A), def_temp2= (uint) ((A) >> 32); \
    int4store((T),def_temp);                                            \
    int4store((T+4),def_temp2); } while(0)

#define uint3korr(A)	(uint32_t) (((uint32_t) ((uint8_t) (A)[0])) +   \
                                    (((uint32_t) ((uint8_t) (A)[1])) << 8) + \
                                    (((uint32_t) ((uint8_t) (A)[2])) << 16))
#define uint4korr(A)	(uint32_t) (((uint32_t) ((uint8_t) (A)[0])) +   \
                                    (((uint32_t) ((uint8_t) (A)[1])) << 8) + \
                                    (((uint32_t) ((uint8_t) (A)[2])) << 16) + \
                                    (((uint32_t) ((uint8_t) (A)[3])) << 24))
#define uint1korr(A)    (*((uint8_t *)A))


#define C_SUCCESS 0

#define C_ERROR 1

#define C_SIZE_OVERFLOW -1

const int C_MYSQL_PACKET_HEADER_SIZE = 4;

#endif
