//
//  SimType.h
//  email:mawei1100@163.com
//
//  Created by mawei on 2017/10/29.
//  Copyright © 2017年 mawei. All rights reserved.
//
#ifndef SimType_h
#define SimType_h

typedef enum SIM_TYPE
{
	SIM_SUCCESS = 0,
	SIM_HANDL_ERROR = -1,
	SIM_UN_SUPPORT_FORMAT = -2,
	SIM_FILE_CAN_NOT_READ = -3,
	SIM_DIR_CAN_NOT_WRITE = -4,
	SIM_TASK_NOT_EXIST = -5,
	

	SIM_MALLOC_ERROR = -6,
	SIM_OPEN_FILE_ERROR = -7,
	SIM_WRITE_FILE_ERROR = -8,
	SIM_MEDIA_ERROR = -9,
	SIM_UNKNOWN_ERROR = -100,
	
	
    //Transform status
	SIM_TRANS_WAIT = 4,					
    SIM_TRANS_ING = 6,					
	SIM_TRANS_INITIATIVE_EXIT = 7,		
    SIM_TRANS_END = 8,					
};

/**
 * 转换回调，由调用者创建，不可阻塞
 *
 * @param taskId  任务id
 * @param tsFileName 完成的ts文件名称
 */
typedef void (*SimHLS_Callback)(int64_t taskId,const char* m3u8FileName,const char* tsFileName);

#endif //SimType_h
