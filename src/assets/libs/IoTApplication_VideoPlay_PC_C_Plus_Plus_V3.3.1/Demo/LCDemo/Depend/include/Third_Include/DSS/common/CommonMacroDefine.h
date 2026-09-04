
#ifndef NULL
#define NULL 0
#endif

#define SAFE_DELETE(x)				    {if((x)!=NULL) {delete (x);       (x) = NULL;}} 
#define SAFE_DELETE_ARRAY(x)			{if((x)!=NULL) {delete[] (x);     (x) = NULL;}}
#define SAFE_CLOSE_HANDLE(x)			{if((x)!=NULL) {::CloseHandle(x); (x) = NULL;}}
#define SAFE_RELEASE(x)				    {if((x)!=NULL} {(x)->Release();   (x) = NULL;}}


#define RET_IF_NULL(checkVal)						{if((checkVal) == NULL){return;}}
#define RET_V_IF_NULL(checkVal, ret)				{if((checkVal) == NULL){return (ret);}}

#define RET_IF_NOT_NULL(checkVal)					{if((checkVal) != NULL){return;}}
#define RET_V_IF_NOT_NULL(checkVal, ret)			{if((checkVal) != NULL){return (ret);}}

#define RET_IF_NOT_EQUAL(val1, val2)				{if((val1) != (val2)){return;}}
#define RET_V_IF_NOT_EQUAL(val1, val2, ret)			{if((val1) != (val2)){return (ret);}}

#define RET_IF_EQUAL(val1, val2)					{if((val1) == (val2)){return;}}
#define RET_V_IF_EQUAL(val1, val2, ret)				{if((val1) == (val2)){return (ret);}}

#define RET_IF_BIGGER(val1, val2)					{if((val1) > (val2)){return;}}
#define RET_V_IF_BIGGER(val1, val2, ret)			{if((val1) > (val2)){return (ret);}}

#define RET_IF_BIGGER_OR_EQUAL(val1, val2)			{if((val1) >= (val2)){return;}}
#define RET_V_IF_BIGGER_OR_EQUAL(val1, val2, ret)	{if((val1) >= (val2)){return (ret);}}

#define RET_IF_SMALLER(val1, val2)					{if((val1) < (val2)){return;}}
#define RET_V_IF_SMALLER(val1, val2, ret)			{if((val1) < (val2)){return (ret);}}

#define RET_IF_SMALLER_OR_EQUAL(val1, val2)			{if((val1) <= (val2)){return;}}
#define RET_V_IF_SMALLER_OR_EQUAL(val1, val2, ret)	{if((val1) <= (val2)){return (ret);}}


#define RET_IF_FALSE(checkVal)						{if(!(checkVal)){return;}}
#define RET_V_IF_FALSE(checkVal, ret)				{if(!(checkVal)){return (ret);}}


#define RET_IF_TRUE(checkVal)						{if((checkVal)){return;}}
#define RET_V_IF_TRUE(checkVal, ret)				{if((checkVal)){return (ret);}}

#define IN
#define OUT
