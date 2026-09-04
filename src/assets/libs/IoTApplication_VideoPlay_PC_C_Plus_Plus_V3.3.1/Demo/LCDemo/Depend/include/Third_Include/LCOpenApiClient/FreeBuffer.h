/************************************************************************/
/* FreeBuffer                                                           */
/************************************************************************/
#ifndef _HSVIEW_CLIENT_FREE_BUFFER_H_
#define _HSVIEW_CLIENT_FREE_BUFFER_H_

#include <stdlib.h>
#include "basedef.h"
#include "ConstString.h"


// 日志输出等级
enum
{
	LOG_ERROR = 0,
	LOG_WARN,
	LOG_INFO,
	LOG_DEBUG,
	LOG_VERBOSE
};

/** FreeBuffer */
typedef struct
{
	char *ptr;
	size_t length;
	size_t size;
	int count;
} free_buffer_t;

C_API void free_buffer_init(free_buffer_t *buf);
C_API void free_buffer_append(free_buffer_t *buf, void *data, size_t len);
C_API void free_buffer_clear(free_buffer_t *buf);
C_API void free_buffer_destroy(free_buffer_t *buf);

struct StringArr{
	char **pString;
	int nLen;
	int nCount;
};

C_API void init_arr(struct StringArr *pArr,int len);
C_API void sort_arr(struct StringArr *pArr);
C_API void append_arr(struct StringArr *pArr,char *strInfo);
C_API void arrToBuf(struct StringArr *pArr,char *outBuffer);
C_API void removeServerName(char* src, char* outBuffer);

/** List */
#define DECLARE_LIST(TYPE) \
struct { \
	TYPE *array; \
	size_t _buffer_length; \
	size_t _buffer_size; \
	int size; \
}

#define LIST_INIT(list)				free_buffer_init((free_buffer_t *)(void *)&list)
#define LIST_ADD(list, obj)			free_buffer_append((free_buffer_t *)(void *)&list, &obj, sizeof(obj))
#define LIST_CLEAR(list)			free_buffer_destroy((free_buffer_t *)(void *)&list)

#define LIST_ADD_INT(list, s)		{ int i = s; free_buffer_append((free_buffer_t *)(void *)&list, &i, sizeof(i)); }
#define LIST_ADD_LONG(list, s)		{ int64 i = s; free_buffer_append((free_buffer_t *)(void *)&list, &i, sizeof(i)); }
#define LIST_ADD_BOOL(list, s)		{ BOOL b = s; free_buffer_append((free_buffer_t *)(void *)&list, &b, sizeof(b)); }
#define LIST_ADD_STR(list, s)		{ CSTR cstr = CS(s); free_buffer_append((free_buffer_t *)(void *)&list, &cstr, sizeof(cstr)); }
#define LIST_ADD_DOUBLE(list, s)	{ double f = s; free_buffer_append((free_buffer_t *)(void *)&list, &f, sizeof(f)); }
#define LIST_ADD_OBJ(list, s)		LIST_ADD(list, s)
#define LIST_ADD_EMPTY_OBJ(list)	free_buffer_append((free_buffer_t *)(void *)&list, NULL, sizeof(*list.array))

#endif
