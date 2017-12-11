//
//  main.c
//  email-mawei1100@163.com
//
//  Created by mawei on 2017/10/29.
//  Copyright © 2017年 mawei. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include "SimHLSTrans.h"

#ifdef _WIN32
#include <windows.h>
#else
#define SIM_API
#define SIM_APICALL
#endif

#define MAX_STR 1024
#define MAX_PATH 256
#define MAX_NAME 64
#define MAX_INPUT 32
#define RTSP_HEAD "rtsp://"
typedef struct _input_info
{
	char file_name[MAX_PATH];
	char root_dir[MAX_PATH];
	char sub_dir[MAX_NAME];
	char media_name[MAX_NAME];
	unsigned int target_duration;

	int64_t task_id;
}input_info;


int getInputInfo(const char* filename,input_info *infos)
{
	char data[MAX_STR];
	int i = 0;
	FILE *fp = fopen(filename, "r");
	if (!fp)
	{
		printf("can't open file\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s %s %d", &infos[i].file_name, &infos[i].root_dir, &infos[i].sub_dir, &infos[i].media_name, &infos[i].target_duration);
		printf("%s %s %s %s %d", infos[i].file_name, infos[i].root_dir, infos[i].sub_dir, infos[i].media_name, infos[i].target_duration);
		printf("\n");
		i++;
	}
	printf("\n");
	fclose(fp);
	return i;
}
void HLS_Callback(int64_t taskId,const char* m3u8FileName,const char* tsFileName)
{
    //警告！！！！此函数阻塞会影响转换性能
    printf("SimHLS_Callback:taskId:%lld,m3u8FileName:%s,tsFileName:%s\n",taskId,m3u8FileName,tsFileName);
    
}

int main(int argv,char *argc[])
{
	int i = 0;
	const char *input_name;
	input_info infos[MAX_INPUT];
	int input_count;
	SIM_HLS_Handle handle;
	
	if (argv < 2)
	{
		printf("miss input name\n");
		return 0;
	}

	input_name = argc[1];
	input_count = getInputInfo(input_name, infos);

	printf("SimHLS_Version:%s...\n", SimHLS_Version());
    int nThreads = 4;
	handle = SimHLS_Init(nThreads);

	printf("press any key to transfer...\n");
	getchar();

	for (i = 0; i < input_count; i++)
	{
		int64_t task_id;

		if (strncmp(infos[i].file_name, RTSP_HEAD,strlen(RTSP_HEAD)) != 0)
		{
			task_id = SimHLS_FileTrans(handle, infos[i].file_name, infos[i].root_dir, infos[i].sub_dir, infos[i].media_name, infos[i].target_duration,HLS_Callback);
		}
		else
		{
			task_id = SimHLS_RtspTrans(handle, infos[i].file_name, infos[i].root_dir, infos[i].sub_dir, infos[i].media_name, infos[i].target_duration,HLS_Callback);
		}
		printf("strFileName:%s,task_id:%lld\n", infos[i].file_name, task_id);

		if (task_id < 0)
		{
			infos[i].task_id = 0;
			continue;
		}
		infos[i].task_id = task_id;
	}

	printf("press any key to get playurl...\n");
	getchar();
	for (i = 0; i < input_count; i++)
	{
		int ret;
		char playurl[MAX_STR];
		memset(playurl, 0, MAX_STR);

		ret = SimHLS_PalyUrl(handle, infos[i].task_id, (char**)&playurl);
		printf("SimHLS_PalyUrl ret=%d,strFileName:%s,id:%lld,playurl:%s\n", ret, infos[i].file_name,infos[i].task_id, playurl);
	}

	printf("press any key to get trans status...\n");
	int a= getchar();

	for (i = 0; i < input_count; i++)
	{
		int stataus = 0;
		int percent = 0;
		stataus = SimHLS_TranStatus(handle, infos[i].task_id, &percent);
		printf("SimHLS_PalyUrl stataus=%d,strFileName:%s,id:%lld,percent:%d\n", stataus, infos[i].file_name, infos[i].task_id, percent);
	}



	printf("press any key to stop all task...\n");
	getchar();
	for (i = 0; i < input_count; i++)
	{
		int ret;
		ret = SimHLS_Stop(handle, infos[i].task_id);
		printf("SimHLS_Stop ret=%d,strFileName:%s,id:%lld\n", ret, infos[i].file_name, infos[i].task_id);
	}
	
	printf("press any key to end test...\n");
	getchar();

	SimHLS_Release(handle);

    return 0;
}
