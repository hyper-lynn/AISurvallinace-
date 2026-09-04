/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceInfo_H_
#define _LC_OPENAPI_CLIENT_DeviceInfo_H_

#include "LCOpenApiDefine.h"
#include "LCOpenApiRequest.h"
#include "LCOpenApiResponse.h"

/** DESCRIPTION: 
获取单个设备的信息

 */

namespace Dahua{
namespace LCOpenApi{
	using namespace std;
	class DeviceInfoRequest : public LCOpenApiRequest
	{
	public:
		class DeviceInfoRequestData
		{
		public:
			DeviceInfoRequestData();
			~DeviceInfoRequestData();
			
		public:
			/** 授权token(userToken或accessToken) */
			string token;
		public:
			/** 设备ID */
			string deviceId;

		};
	public:
		DeviceInfoRequest();
		~DeviceInfoRequest();
	public:
		virtual int build();
	public:
		DeviceInfoRequestData data;
	};

	
	typedef DeviceInfoRequest::DeviceInfoRequestData DeviceInfoRequestData;


	class DeviceInfoResponse : public LCOpenApiResponse
	{
	public:
		class DeviceInfoResponseData
		{
		public:
			DeviceInfoResponseData();
			~DeviceInfoResponseData();
			
		public:
			/** [int]平台类型 */
			int platForm;
		public:
			/** define a list with struct of DeviceInfoResponseData_ChannelsElement */
			class DeviceInfoResponseData_ChannelsElement : public LCOpenApiBase
			{
			public:
				DeviceInfoResponseData_ChannelsElement();
				~DeviceInfoResponseData_ChannelsElement();
			public:
				/** [int]报警布撤防状态，0-撤防，1-布防 */
				int alarmStatus;
			public:
				/** 通道名称 */
				string channelName;
			public:
				/** [O]通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙设备协议 */
				string channelAbility;
			public:
				/** 缩略图URL */
				string channelPicUrl;
			public:
				/** [int]通道号 */
				int channelId;
			public:
				/** [bool]是否在线 */
				bool channelOnline;
			public:
				/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
				int csStatus;
			};
		public:
			LCOpenApiVector<DeviceInfoResponseData_ChannelsElement> channels;
		public:
			/** [O]设备型号 */
			string deviceModel;
		public:
			/** [bool]是否有新版本可以升级 */
			bool canBeUpgrade;
		public:
			/** [int]加密模式 */
			int encryptMode;
		public:
			/** 设备ID */
			string deviceId;
		public:
			/** [int]总的视频通道数，包含未接入的通道 */
			int channelNum;
		public:
			/** [int]p2p拉流端口 */
			int streamPort;
		public:
			/** 设备登陆用户名 */
			string devLoginName;
		public:
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙设备协议 */
			string ability;
		public:
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
		public:
			/** 设备登陆密码 */
			string devLoginPassword;
		public:
			/** 设备名称 */
			string name;
		public:
			/** 设备软件版本号 */
			string version;

		};
	public:
		DeviceInfoResponse();
		~DeviceInfoResponse();
	public:
		virtual int parse();
	public:
		DeviceInfoResponseData data;
	};

	
	typedef DeviceInfoResponse::DeviceInfoResponseData DeviceInfoResponseData;
	typedef DeviceInfoResponse::DeviceInfoResponseData::DeviceInfoResponseData_ChannelsElement DeviceInfoResponseData_ChannelsElement;

}
}

#endif
