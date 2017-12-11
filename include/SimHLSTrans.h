//
//  SimHLSTrans.h
//  email-mawei1100@163.com
//
//  Created by mawei on 2017/10/29.
//  Copyright © 2017年 mawei. All rights reserved.
//

#ifndef SimHLSTrans_h
#define SimHLSTrans_h

#include <stdio.h>
#include <stdint.h>
#include "SimType.h"
#ifdef _WIN32
#define SIM_API  __declspec(dllexport)
#define SIM_APICALL  __stdcall
#else
#define SIM_API
#define SIM_APICALL
#endif

#define SIM_HLS_Handle void*

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	* 获取版本号
	*
	* @return 版本号
	*/
	SIM_API const char* SIM_APICALL SimHLS_Version(void);
 
    /**
     * 初始化
     * @param nThreads 线程数，一般为cpu支持的最大线程数
     * @return sdk句柄，供后续调用
     */
    SIM_API SIM_HLS_Handle SIM_APICALL SimHLS_Init(int nThreads);
    
    /**
     * 文件转码，非阻塞接口，返回为任务id
     *
     * @param handle sdk句柄
     * @param strFileName  文件名，包括完整路径
     * @param strRootDir  存放的目录路径，一般为nginx服务路径
     * @param strSubDir  子目录名称，为nginx服务子目录
     * @param strMediaName  媒体名称，为m3u8文件名
     * @param nTargetDuration ts分片文件时间，单位秒
	 * @param cb 转换回调，每一个ts片完成回调一次，此函数不能阻塞
	 *
     * @return 任务id
     *
     */
    SIM_API int64_t SIM_APICALL SimHLS_FileTrans(SIM_HLS_Handle handle,const char *strFileName, const char * strRootDir, const char* strSubDir, const char* strMediaName, unsigned int nTargetDuration,SimHLS_Callback cb);
    
    /**
     * rtsp视频流转码，非阻塞接口，返回为任务id
     *
     * @param handle sdk句柄
     * @param strUrl  rtsp流地址,一般为rtsp://admin:12345@192.0.0.64:554/h264/ch1/main/av_stream
     * @param strRootDir  存放的目录路径，一般为nginx服务路径
     * @param strSubDir  子目录名称，为nginx服务子目录
     * @param strMediaName  媒体名称，为m3u8文件名
     * @param nTargetDuration ts分片文件时间，单位秒
  	 * @param cb 转换回调，每一个ts片完成回调一次，此函数不能阻塞
	 *
     * @return 任务id
     *
     */
    SIM_API int64_t SIM_APICALL SimHLS_RtspTrans(SIM_HLS_Handle handle, const char *strUrl,const char * strRootDir, const char* strSubDir, const char* strMediaName, unsigned int nTargetDuration,SimHLS_Callback cb);
    
    /**
     * 获取任务的播放地址
     *
     * @param handle sdk句柄
     * @param taskId  任务id，一般为SimHLS_FileTrans，SimHLS_RtspTrans返回
     * @param strPlayUrl 返回参数，播放地址
     *
     * @return 成功为0，其他失败
     *
     */
    SIM_API int SIM_APICALL SimHLS_PalyUrl(SIM_HLS_Handle handle, int64_t taskId,char **strPlayUrl);


	/**
	* 获取任务的转换状态
	*
	* @param handle sdk句柄
	* @param taskId  任务id，一般为SimHLS_FileTrans，SimHLS_RtspTrans返回
	* @param percent 返回参数，转换百分比0-100，一般为文件转换使用
	*
	* @return 成功为转换状态，失败为-1
	*
	*/
	SIM_API int SIM_APICALL SimHLS_TranStatus(SIM_HLS_Handle handle, int64_t taskId, int *percent);
    
    /**
     * 任务停止
     *
     * @param handle sdk句柄
     * @param taskId  任务id，一般为SimHLS_FileTrans，SimHLS_RtspTrans返回
     * @return 成功为0，其他失败
     *
     */
    SIM_API int SIM_APICALL SimHLS_Stop(SIM_HLS_Handle handle, int64_t taskId);
    
    /**
     * 释放句柄
     *
     * @param handle sdk句柄
     *
     *
     */
    SIM_API void SIM_APICALL SimHLS_Release(SIM_HLS_Handle handle);
    
#ifdef __cplusplus
}
#endif



#endif /* SimHLSTrans_h */
