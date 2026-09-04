#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Objbase.h>
#include "LCOpenApi_Common.h"
#include "algorithm/LCOpenApi_algorithm.h"

namespace LCOpenApi {
#ifdef WIN32
#define snprintf _snprintf
#define gmtime_r(t, tm)			gmtime_s(tm ,t)
#endif

#define JSON_OBJECT_KEY_LEN		100

	/************************************************************************/
	/* utils                                                                */
	/************************************************************************/
	static void random_buffer(char *buf, int len)
	{
		GUID guid;

		if (CoCreateGuid(&guid))
		{
			fprintf(stderr, "create guid error\n");
			return;
		}

		_snprintf(buf, len,
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		return;
	}

	static void make_datetime(char *buf, int size)
	{
		time_t t = time(NULL);
		struct tm tempTm;
		gmtime_r(&t, &tempTm);
		//strftime(buf, size, "%Y-%m-%dT%H:%M:%SZ", &tempTm);
		snprintf(buf, size - 1, "%ld", t);
	}

	static void wsse_calc_digest(char *outbuf, const char *nonce, const char *created, const char *password)
	{
		char data[256] = { 0 };
		char sha1_buf[32] = { 0 };

		snprintf(data, sizeof(data), "%s%s%s", nonce, created, password);
		common_algorithm_sha1(data, (int)strlen(data), sha1_buf);
		common_algorithm_base64(sha1_buf, 20, outbuf);
	}

	static void hmacsha1_base64(char *outbuf, const char *sbuf, const char *password)
	{
		char sha1buf[32] = { 0 };
		common_algorithm_hmacsha1((char *)sbuf, (int)strlen(sbuf), (char *)password, (int)strlen(password), sha1buf);
		common_algorithm_base64(sha1buf, 20, outbuf);
	}

	/************************************************************************/
	/* civil                                                                */
	/************************************************************************/
	CSTR lcopenapi_request_build(LCOpenApi_LCOpenApiRequest *p, void *obj, metainfo_t *mi, char *isSys)
	{
		CSTR cs;
		char msgId[20] = { 0 };
		cJSON *json = cJSON_CreateObject();
		cJSON *data = object_to_jsonobject(obj, mi);

		if (isSys && !strcmp(isSys, "T"))
		{
			cJSON *jsonSys = cJSON_CreateObject();
			cJSON_AddStringToObject(jsonSys, "ver", LCOpenApi_lcopenapi_client_get_version().cstr);
			cJSON_AddStringToObject(jsonSys, "appId", LCOpenApi_lcopenapi_client_get_appId().cstr);

			cJSON_AddItemToObject(json, "system", jsonSys);
			snprintf(msgId, sizeof(msgId) - 1, "%u", LCOpenApi_lcopenapi_client_get_serialNo());
			p->messageId = CS(msgId);
			cJSON_AddStringToObject(json, "id", msgId);

		}

		cJSON_AddItemToObject(json, "params", data);

		cs.cstr = cJSON_Print(json);

		p->params.cstr = cJSON_Print(data);
		cJSON_Delete(json);

		return cs;
	}

	int lcopenapi_response_parse(LCOpenApi_LCOpenApiResponse *p, void *obj, metainfo_t *mi)
	{
		cJSON *json;
		cJSON *json_ret;
		cJSON *json_code;
		cJSON *json_msg;
		cJSON *json_data;
		cJSON *json_id;

		if (p->content_length > 0)
		{
			json = cJSON_Parse(p->content.cstr);
			if (json == NULL)
			{
				return -1;
			}
			json_ret = cJSON_GetObjectItem(json, "result");
			if (!json_ret)
			{
				return -1;
			}
			json_code = cJSON_GetObjectItem(json_ret, "code");
			json_msg = cJSON_GetObjectItem(json_ret, "msg");
			json_data = cJSON_GetObjectItem(json_ret, "data");
			if (!json_code || !json_msg/* || !json_data*/)
			{
				cJSON_Delete(json);
				return -1;
			}
			if (json_code->type != cJSON_String || json_msg->type != cJSON_String || (json_data && json_data->type != cJSON_Object))
			{
				cJSON_Delete(json);
				return -1;
			}


			p->ret_code = CS(json_code->valuestring);
			p->ret_msg = CS(json_msg->valuestring);
			json_id = cJSON_GetObjectItem(json, "id");
			if (json_id && json_id->type == cJSON_String)
			{
				p->id = CS(json_id->valuestring);
			}

			if (json_data)
			{
				object_from_jsonobject(obj, mi, json_data);
			}

			cJSON_Delete(json);
		}

		return 0;
	}

	int lcopenapi_jsonObject_getKeys(cJSON *json, char(*keyArray)[JSON_OBJECT_KEY_LEN], int *size)
	{

		char tmp[JSON_OBJECT_KEY_LEN] = { 0 };
		int iSize;
		int i, j;
		i = j = 0;
		iSize = 0;
		if (json)
		{
			json = json->child;
		}

		while (json)
		{
			strcpy(keyArray[iSize++], json->string);
			json = json->next;

		}

		//quick sort or bubble
		for (i = 0; i < iSize - 1; i++)
		{
			for (j = 0; j < iSize - i - 1; j++)
			{
				if (strcmp(keyArray[j], keyArray[j + 1]) > 0)
				{
					strcpy(tmp, keyArray[j]);
					strcpy(keyArray[j], keyArray[j + 1]);
					strcpy(keyArray[j + 1], tmp);
				}
			}
		}
		*size = iSize;
		return iSize;

	}
	int lcopenapi_request_sign(LCOpenApi_LCOpenApiRequest *p, const char *appId, const char *appSecret, const char *time)
	{
		char utctime[32] = { 0 };
		int i = 0;
		cJSON *json;
		cJSON *jsonBody;
		cJSON *jsonSys;
		int size = 0;
		char keyArray[50][JSON_OBJECT_KEY_LEN];
		char signOrg[4 * 1024] = { 0 };
		char nonce[33] = { 0 };
		char signMd5[33] = { 0 };

		if (!time)
		{
			make_datetime(utctime, 32);
			time = utctime;
		}
		//calculate original signature
		//append time
		p->time = CS(time);
		strcat(signOrg, "time:");
		strcat(signOrg, time);
		strcat(signOrg, ",");

		//append nonce
		random_buffer(nonce, 32);
		p->nonce = CS(nonce);
		strcat(signOrg, "nonce:");
		strcat(signOrg, nonce);
		strcat(signOrg, ",");
		//append appsecret
		strcat(signOrg, "appSecret:");
		strcat(signOrg, LCOpenApi_lcopenapi_client_get_appSecret().cstr);

		myPrint("chenjian test signOrg[%s]\n", signOrg);


		common_algorithm_md5_lowercase(signOrg, signMd5);
		p->signMd5 = CS(signMd5);
		//end

		//append body
		jsonBody = cJSON_Parse(p->body.cstr);
		if (jsonBody)
		{
			jsonSys = cJSON_GetObjectItem(jsonBody, "system");
			if (jsonSys)
			{
				cJSON_AddStringToObject(jsonSys, "time", p->time.cstr);
				cJSON_AddStringToObject(jsonSys, "nonce", p->nonce.cstr);
				cJSON_AddStringToObject(jsonSys, "sign", p->signMd5.cstr);
			}

		}
		//end
		CS_CLEAR(p->body);
		p->body.cstr = cJSON_Print(jsonBody);

		cJSON_Delete(jsonBody);
		return 0;
	}
}