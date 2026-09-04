#ifndef __INCLUDE_DAHUA_STREAMSVR_DHSEPARATOR_H__
#define __INCLUDE_DAHUA_STREAMSVR_DHSEPARATOR_H__

#include "StreamSeparator.h"

namespace Dahua{
namespace StreamSvr{

///\brief DHAV over RTSP码流分离器
class STREAMSVR_API CDHSeparator : public IStreamSeparator
{
public:
	///\brief 构造函数
	CDHSeparator();

	///\brief 析构函数
	~CDHSeparator();


	///\brief 将从网络上接收到的数据分离，分离的原因是接收的数据既有数据也有信令。
	///\param [in] recvLen-本次接收到的数据长度
	///\return -1-失败, 0-成功	
	int separate(uint32_t recvLen);

	///\brief 获取剩余缓冲指针和剩余大小
	///\param [in] length-剩余缓冲大小
	///\return 剩余缓冲的起始地址
	uint8_t* getBuffer(int &length);
	
private:
	char* get_packet( int& ret_val );
};

}//StreamSvr
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMSVR_DHSEPARATOR_H__

