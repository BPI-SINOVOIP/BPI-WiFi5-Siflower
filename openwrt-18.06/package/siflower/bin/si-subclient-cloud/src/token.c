#include "local_stub.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <shadow.h>
#include <regex.h>
#include "cJSON.h"
#include "cloud_common.h"
#include "local_http.h"
#include "local_storage.h"
#include "remote_https.h"
#include "mtd.h"

char token[256];
static const char *XCLOUD_TOKEN_FORMAT = "{\"sn\": \"%s\",\"mac\":\"%s\" }";
int8_t TokenInit();
#define XCLOUD_TOKEN "getToken"

char macaddr[32];
char routersn[64];

int32_t postHttpsForToken(char *url,void *data,void *response)
{
    struct HttpResonseData *response_tmp = (struct HttpResonseData *)response;
    response_tmp->data = NULL;
    response_tmp->size = 0;
    CURL* curl = curl_easy_init();
    if(NULL == curl) return CURLE_FAILED_INIT;

    long time1 = time(NULL);
    struct curl_slist *slist = NULL;
    char header[100] = "";
    slist = curl_slist_append(slist, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 );
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnHttpReponseData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_tmp);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 6);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    int32_t res = curl_easy_perform(curl);

    response_tmp->data = realloc(response_tmp->data, response_tmp->size+1);
    ((char *)(response_tmp->data))[response_tmp->size] = '\0';

    long responseCode;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
    if((responseCode % 200) > 100 || responseCode >= 400){
        LOG("postHttpsForToken request fail %d \n",(int)responseCode);
        res = -1;
    }
    LOG("postHttpsForToken %ld cost %ld s url: %s\n",responseCode,time(NULL) - time1,url);
    curl_easy_cleanup(curl);
    curl_slist_free_all(slist);
    return 0;
}

int8_t GetToken(){
	char url[256] = "";
	char data[256] = "";
	int8_t ret;
	struct HttpResonseData response;
	int32_t retcode;

	response.size = 0;

	if(strlen(routersn) == 0){
		TokenInit();
		if(strlen(routersn) == 0){
			return 0;
		}
	}

	sprintf(data, XCLOUD_TOKEN_FORMAT, routersn, macaddr);
	sprintf(url,"%s%s",XCLOUD_REMOTE_ADDR, XCLOUD_TOKEN);

	ret = postHttpsForToken(url, (void *)data, (void *)&response);
	LOG("token response is %s\n",(char *)response.data);
	if (ret == 0){
		parseIntFromData("code", response.data, &retcode);
		if (retcode == 0){
			parseStringFromData("data", response.data, token);
			LOG("token is %s\n",token);
		}else{
			LOG("get token fail\n");
		}
	}

	if(response.size > 0)
		free(response.data);

	return ret;
}

int8_t TokenInit(){
	uint8_t base_mac[6] = "";

	get_router_macaddr(base_mac);
	sprintf(macaddr,"%02x:%02x:%02x:%02x:%02x:%02x",base_mac[0],base_mac[1],base_mac[2],base_mac[3],base_mac[4],base_mac[5]);
    getSfHardwareConfig("sn",routersn);

	LOG("sn is %s, mac addr is %s", routersn, macaddr);

	return 0;
}