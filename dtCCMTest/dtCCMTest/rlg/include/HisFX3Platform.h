//
#ifndef HISFX3PLATFORM_H
#define HISFX3PLATFORM_H

#include <vector>
#include <string>
#include "HisGlobalDefine.h"

#define _HISFX3PLATFORM_EXPORT_DUXIN
#define _HISFX3PLATFORM_EXPORT_HYVISION
 
#ifdef HISFX3PLATFORM_LIB
#define HISFX3PLATFORM_EXPORT /*extern "C"*/ __declspec(dllexport)
#else
#define HISFX3PLATFORM_EXPORT /*extern "C"*/ __declspec(dllimport)
#endif
 
//!  软龙格图像采集工装封装类
/*! 电脑配置建议在WIN7以上系统， 4G以上内存， INTEL I3以上处理器
*/

struct _RolongoXMLOtherSectionItem
{
	std::string key;
	std::string value;
};

class HISFX3PLATFORM_EXPORT CHisFX3Platform
{
public:
	CHisFX3Platform(void);
	~CHisFX3Platform(void);
	//!  打开工装， 在执行其他操作之间必须打开工装
	/*! 建议在程序一开始的时候打开工装，程序结束时关闭工装
	\param[in] usPID USB3.0设备PID， 此参数暂时保留，请固定设为0
	\param[in] usVID USB3.0设备VID， 此参数暂时保留，请固定设为0
	\param[in] pstrFriendlyName USB3.0设备描述名称， 此参数暂时保留，请固定设为0
	\param[in] ucDeviceIndex USB3.0设备序号， 此参数暂时保留，请固定设为0xFF
	\param[in] puiKey 工装唯一序列号， 当puiKey==NULL,函数打开连接到电脑的任一工装； 
	                         当puiKey是指向 unsigned int[4]数组的指针时，函数打开和输入序列号匹配的工装。
							 此参数主要用于1个电脑连接多个工装的情况。
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3CloseDevice()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3OpenDevice(unsigned short usPID=0, unsigned short usVID=0, char* pstrFriendlyName=NULL, unsigned char ucDeviceIndex=0xFF, unsigned int* puiKey = NULL, unsigned int uiTransformDelay = 110);

	//!  获取工装数量
	/*! 
	\return 工装数量
	*/
	unsigned int HisFX3DeviceCount();

	//!  关闭工装
	/*! 
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3OpenDevice()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3CloseDevice();

	//! 通道1开始出图
	/*! 如果是双摄工装，此函数操作的是通道1
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3_PreviewStruct， HisFX3StopPreview()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3StartPreview(struct _HisFX3_PreviewStruct* pstPrama);

	//! 通道1停止出图
	/*! 如果是双摄工装，此函数操作的是通道1
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3StopPreview();

	//! 通道2开始出图
	/*! 只有在双摄工装上， 此函数才有效
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3_PreviewStruct， HisFX3StopPreview_S2()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3StartPreview_S2(struct _HisFX3_PreviewStruct* pstPrama);

	//! 通道2停止出图
	/*! 只有在双摄工装上， 此函数才有效
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview_S2()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3StopPreview_S2();

	int reStartPreview(struct _HisFX3_PreviewStruct* pstPrama);

	//! 通道1抓图
	/*! 如果是双摄工装，此函数操作的是通道1
	\param[out] ppucBuffer 接收图像数据的buffer指针，必须用_aligned_malloc(size, _HisCacheLine_Aligned)申请内存空间。
										  如果传入NULL, 则只会返回ui64FramIndex。
	\param[in] uiBufBytes ppucBuffer申请的内存大小，必须大于一帧图像所需的内存大小
	\param[out] ui64FramIndex 当前帧索引，开始出图之后的第一帧为1，以此类推
	\param[in] uiTimeOut 获取新的一帧的timeout时间
	\param[in] uiConvertFlag 1:[raw10][raw12] 返回[width*height*5/4][width*height*3/2] byte  0: [raw10][raw12] 返回width*height byte
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3GrabFrame(unsigned char **ppucBuffer, unsigned int uiBufBytes, unsigned __int64& ui64FramIndex, unsigned int uiTimeOut = 3000, unsigned int uiConvertFlag=0);

	//! 通道2抓图
	/*! 如果是双摄工装，此函数操作的是通道2
	\param[out] ppucBuffer 接收图像数据的buffer指针，必须用_aligned_malloc(size, _HisCacheLine_Aligned)申请内存空间。
										  如果传入NULL, 则只会返回ui64FramIndex。
	\param[in] uiBufBytes ppucBuffer申请的内存大小，必须大于一帧图像所需的内存大小
	\param[out] ui64FramIndex 当前帧索引，开始出图之后的第一帧为1，以此类推
	\param[in] uiTimeOut 获取新的一帧的timeout时间
	\param[in] uiConvertFlag 1:[raw10][raw12] 返回[width*height*5/4][width*height*3/2] byte  0: [raw10][raw12] 返回width*height byte
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()， _HisFX3Platform_ErrorCode
	*/
	int HisFX3GrabFrame_S2(unsigned char **ppucBuffer, unsigned int uiBufBytes, unsigned __int64& ui64FramIndex, unsigned int uiTimeOut = 3000, unsigned int uiConvertFlag=0);

	//! 工装是否已打开
	/*! 
	\return true: 已打开  false: 还未打开
	\sa HisFX3isstart()， HisFX3OpenDevice, HisFX3CloseDevice
	*/
	bool HisFX3isopen();

	//! 通道1数据流是否已开启
	/*! 
	\return true: 已开启  false: 未开启
	\sa HisFX3isopen()， HisFX3StartPreview(), HisFX3StopPreview()
	*/ 
	bool HisFX3isstart();

	//! 通道2数据流是否已开启
	/*!  只有在双摄工装上， 此函数才有效
	\return true: 已开启  false: 未开启
	\sa HisFX3isopen()， HisFX3StartPreview_S2(), HisFX3StopPreview_S2()
	*/
	bool HisFX3isstart_S2();

	//! 获取当前open工装的唯一序列号
	/*!  只有在成功调用HisFX3OpenDevice之后才能调用此函数
	\param puiKey 指向unsigned int[4], 如果函数成功， 会复制设备唯一序列号到此数组空间
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa getHardwareKeyList, HisFX3OpenDevice()， HisFX3CloseDevice(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetHardwareKey(unsigned int* puiKey);

	//! 获取电脑上所有工装的唯一序列号
	/*!  只有在HisFX3OpenDevice之前才能调用此函数
	\param[out] puiKey 指向unsigned int, 如果函数成功， 会复制设备唯一序列号到此数组空间
	\param[out] uiKeyCount  返回有多少组序列号，一组序列号用4个unsigned int表示
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetHardwareKey, HisFX3OpenDevice()， HisFX3CloseDevice(), _HisFX3Platform_ErrorCode
	*/
	int getHardwareKeyList(unsigned int* puiKeyList, unsigned int& uiKeyCount);
	
	//! 操作通道1 RST信号
	/*!  
	\param bPullHigh true: 置为高电平  false:置为低电平
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PullPWND(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullReset(bool bPullHigh);

	//! 操作通道2 RST信号
	/*!    只有在双摄工装上， 此函数才有效
	\param bPullHigh true: 置为高电平  false:置为低电平
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PullPWND_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullReset_S2(bool bPullHigh);

	//! 操作通道1 PWDN信号
	/*!  
	\param bPullHigh true: 置为高电平  false:置为低电平
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PullReset(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullPWND(bool bPullHigh);

	//! 操作通道2 PWDN信号
	/*!    只有在双摄工装上， 此函数才有效
	\param bPullHigh true: 置为高电平  false:置为低电平
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PullReset_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullPWND_S2(bool bPullHigh);

	//! 单条写IIC
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] ui64Data 要写入的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
							 支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] back  true: 判断ACK  false:不判断ACK(耗时更少，但更不安全)
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3WriteIIC(unsigned char ucSlave, unsigned int uiReg, unsigned __int64 ui64Data, unsigned short usType, bool back=true);

	//! 单条写通道2 IIC
	/*!    只有在双摄工装上， 此函数才有效
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] ui64Data 要写入的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
							 支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] back  true: 判断ACK  false:不判断ACK(耗时更少，但更不安全)
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3WriteIIC_S2(unsigned char ucSlave, unsigned int uiReg, unsigned __int64 ui64Data, unsigned short usType, bool back=true);

	//! 单条读IIC
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[out] pui64Data 读出来的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
							 支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3ReadI2C(unsigned char ucSlave, unsigned int uiReg, unsigned __int64* pui64Data, unsigned short usType); 

	//! 单条读IIC(通道2)
	/*!    只有在双摄工装上， 此函数才有效
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[out] pui64Data 读出来的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
							 支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3ReadI2C_S2(unsigned char ucSlave, unsigned int uiReg, unsigned __int64* pui64Data, unsigned short usType); 

	//! 批量写入IIC
	/*! 
	\param[in] uiCount  要写入的IIC的条数
	\param[in] pucSlave 设备地址数组指针
	\param[in] puiReg 寄存器地址数组指针
	\param[in] puiData 数据数组指针
	\param[in] pusType 格式数组指针, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
							 支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay 命令之间的间隔时间，单位: us
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC(), HisFX3ReadIIC(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchWriteIICNoLimit(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay=10);

	//! 批量写入IIC(通道2)
	/*! 
	\param[in] uiCount  要写入的IIC的条数
	\param[in] pucSlave 设备地址数组指针
	\param[in] puiReg 寄存器地址数组指针
	\param[in] puiData 数据数组指针
	\param[in] pusType 格式数组指针, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
							 支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay 命令之间的间隔时间，单位: us
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC_S2(), HisFX3ReadIIC_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchWriteIICNoLimit_S2(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay=10);
	
	//! 批量读取IIC
	/*! 
	\param[in] uiCount  要写入的IIC的条数
	\param[in] pucSlave 设备地址数组指针
	\param[in] puiReg 寄存器地址数组指针
	\param[out] puiData 数据数组指针
	\param[in] pusType 格式数组指针, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
							 支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay 命令之间的间隔时间，单位: us
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC(), HisFX3ReadIIC(), HisFX3BatchWriteIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchReadIICNoLimit(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay=10);
	
	//! 批量读取IIC(通道2)
	/*! 
	\param[in] uiCount  要写入的IIC的条数
	\param[in] pucSlave 设备地址数组指针
	\param[in] puiReg 寄存器地址数组指针
	\param[out] puiData 数据数组指针
	\param[in] pusType 格式数组指针, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
							 支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay 命令之间的间隔时间，单位: us
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC_S2(), HisFX3ReadIIC_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchReadIICNoLimit_S2(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay=10);

	//! Page写入IIC
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[in] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] usDelay 每个BYTE延时usDelay *0.5个始终周期
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned short usDelay = 4);

	//! Page模式写入IIC(通道2)
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[in] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] usDelay 每个BYTE延时usDelay *0.5个始终周期
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C_S2(), HisFX3WriteI2C_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIIC_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned short usDelay = 4);
	
	//! Page模式读取IIC
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[out] pucData 数据数组指针
	\param[in] uiDataSize 要读取的数据长度，单位:byte
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize);
	
	//! Page模式读取IIC(通道2)
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[out] pucData 数据数组指针
	\param[in] uiDataSize 要读取的数据长度，单位:byte
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C_S2(), HisFX3WriteI2C_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIIC_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize);

	//! Page写入IIC, 无长度限制(通道1)
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[in] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] uiPageSize 一个Page的大小，需要查阅EEPROM的规格书，一般是128,256,512,1024...
	\param[in] usByteDelay 每个BYTE延时usDelay *0.5个始终周期
	\param[in] uiPageDelay 每个Page写入之间的延时，单位:ms
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PageWriteIIC(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIICNoLimit(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned short usByteDelay = 4, unsigned int uiPageDelay= 100);
	
	//! Page写入IIC, 无长度限制(通道2)
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[in] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] uiPageSize 一个Page的大小，需要查阅EEPROM的规格书，一般是128,256,512,1024...
	\param[in] usByteDelay 每个BYTE延时usDelay *0.5个始终周期
	\param[in] uiPageDelay 每个Page写入之间的延时，单位:ms
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PageWriteIIC_S2(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIICNoLimit_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned short usByteDelay = 4, unsigned int uiPageDelay= 100);

	//! Page模式读取IIC, 无长度限制(通道1)
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[out] pucData 数据数组指针
	\param[in] uiDataSize 要读取的数据长度，单位:byte
	\param[in] uiPageSize 一个Page的大小，需要查阅EEPROM的规格书，一般是128,256,512,1024...
	\param[in] uiPageDelay 每个Page读取之间的延时，单位:ms
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PageReadIIC(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIICNoLimit(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned int uiPageDelay = 0);

	//! Page模式读取IIC, 无长度限制(通道2)
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[out] pucData 数据数组指针
	\param[in] uiDataSize 要读取的数据长度，单位:byte
	\param[in] uiPageSize 一个Page的大小，需要查阅EEPROM的规格书，一般是128,256,512,1024...
	\param[in] uiPageDelay 每个Page读取之间的延时，单位:ms
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3PageReadIIC_S2(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIICNoLimit_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned int uiPageDelay = 0);

	//! Page模式写入SPI
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[in] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] bCSLow 设置操作SPI时的CS信号电平。 true:低电平； false:高电平
	\param[in] bLowFirst true: 低位在前； false:高位在前
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3PageReadSPI(), HisFX3WriteSPI(), HisFX3ReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteSPI(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, bool bCSLow=true, bool bLowFirst=true);
	
	//! Page模式读取SPI
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] uiRegSize 寄存器地址字节长度，1,2,4可选
	\param[out] pucData 数据数组指针
	\param[in] uiDataSize 要写入的数据长度，单位:byte
	\param[in] bCSLow 设置操作SPI时的CS信号电平。 true:低电平； false:高电平
	\param[in] bLowFirst true: 低位在前； false:高位在前
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3PageWriteSPI(), HisFX3WriteSPI(), HisFX3ReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadSPI(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, bool bCSLow=true, bool bLowFirst=true);

	//! 单条写SPI
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[in] ui64Data 要写入的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
							 支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] bCSLow 设置操作SPI时的CS信号电平。 true:低电平； false:高电平
	\param[in] bLowFirst true: 低位在前； false:高位在前
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3ReadSPI(), HisFX3PageWriteSPI(), HisFX3PageReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3WriteSPI(unsigned char ucSlave, unsigned int uiReg, unsigned __int64 ui64Data, unsigned short usType, bool bCSLow=true, bool bLowFirst=true);
	
	//! 单条读取SPI
	/*!    
	\param[in] ucSlave 从机设备地址
	\param[in] uiReg 寄存器地址
	\param[out] pui64Data 读取的数据
	\param[in] usType 寄存器和数据格式, eg:0x1608-表示地址位写入16bit, 数据位写入8bit。
							 支持的格式:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] bCSLow 设置操作SPI时的CS信号电平。 true:低电平； false:高电平
	\param[in] bLowFirst true: 低位在前； false:高位在前
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3WriteSPI(), HisFX3PageWriteSPI(), HisFX3PageReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3ReadSPI(unsigned char ucSlave, unsigned int uiReg, unsigned __int64* pui64Data, unsigned short usType, bool bCSLow=true, bool bLowFirst=true);

	//! 向下兼容API, 建议不使用
	int HisFX3BatchWriteIIC(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short usType, unsigned short usDelay=10);
	
	//! 向下兼容API, 建议不使用
	int HisFX3BatchReadIIC(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short usType, unsigned short usDelay=10);
	
	//! 向下兼容API, 建议不使用
	int HisFX3BatchWriteIIC_V2(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay);
	
	//! 向下兼容API, 建议不使用
	int HisFX3BatchReadIIC_V2(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay);

	//! 设置IIC通信速度
	/*!    
	\param[in] us1kMultiple 10KHz~1MHz范围可调
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetIICSpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetIICSpeed(unsigned short us1kMultiple);

	//! 设置IIC通信速度(通道2)
	/*!    
	\param[in] us1kMultiple 10KHz~1MHz范围可调
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetIICSpeed_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetIICSpeed_S2(unsigned short us1kMultiple);

	//! 获取当前IIC通信速度
	/*!    
	\param[out] pus1kMultiple 单位：KHz
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetIICSpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetIICSpeed(unsigned short* pus1kMultiple);

	//! 获取当前IIC通信速度(通道2)
	/*!    
	\param[out] pus1kMultiple 单位：KHz
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetIICSpeed_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetIICSpeed_S2(unsigned short* pus1kMultiple);

	//! 设置SPI通信速度
	/*!    
	\param[in] us1kMultiple 10KHz~25MHz范围可调, 单位: KHz
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetSPISpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetSPISpeed(unsigned short us1kMultiple);

	//! 获取当前SPI通信速度
	/*!    
	\param[out] pus1kMultiple 单位：KHz
	\return 0:成功  非0:失败的错误代码, 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetSPISpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetSPISpeed(unsigned short* pus1kMultiple);

	//! 侦测通道1的从设备地址响应
	/*!    
	\param[in] ucSlave 从设备的设备地址
	\return 0:有响应  非0:未响应, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3SlaveResponds(unsigned char ucSlave);

	//! 侦测通道2的从设备地址响应
	/*!    
	\param[in] ucSlave 从设备的设备地址
	\return 0:有响应  非0:未响应, 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3SlaveResponds_S2(unsigned char ucSlave);

	//! 保留
	int HisFX3GetMIPIDataType(_HisFX3_ImageSenor_DataType* pDataType);

	//! 开关5V12V电压输出【R5】
	/*!    
	\param[in] uiV5 0：5V关闭  1：5V打开  2：5V不设置
	\param[in] uiV12 0：12V关闭  1：12V打开  2：12V不设置
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetVolt, HisFX3SetVolt_S2, _HisFX3Platform_ErrorCode
	*/
	int HisFX3Set5V12V(unsigned int uiV5 = 2, unsigned int uiV12 = 2);

	//! 设置通道1电压
	/*!    
	\param[in] flDOVDD 0.0V~3.5V范围可调, 实际所设电压= flDOVDD *flMultiple
	\param[in] flAVDD 0.0V~3.5V范围可调, 实际所设电压= flAVDD *flMultiple
	\param[in] flDVDD 0.0V~3.5V范围可调, 实际所设电压= flDVDD *flMultiple
	\param[in] flAF 0.0V~3.5V范围可调, 实际所设电压= flAF *flMultiple
	\param[in] flVFuse 0.0V~10.0V范围可调, 实际所设电压= flVFuse *flMultiple
	\param[in] flPOW 0.0V~3.5V范围可调【R5】【R3X】【R5X】, 实际所设电压= flPOW *flMultiple
	\param[in] flIODD 0.0V~3.5V范围可调【板卡内部IO电平】【R5】, 实际所设电压= flIODD *flMultiple
	\param[in] usSwitch 设置电压开关， _HisFX3_Platform_VoltFlag，
									  eg,设置AVDD和DVDD电压， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] flMultiple 电压值系数
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3Set5V12V, HisFX3SetVolt_S2, HisFX3GetVolt, _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetVolt(float flDOVDD=0.0f, float flAVDD=0.0f, float flDVDD=0.0f, float flAF = 0.0f, float flVFuse=0.0f, float flPOW=0.0f, float flIODD = 0.0f, unsigned short usSwitch=0xFF, float flMultiple = 0.1f);
	
	//! 设置通道2电压
	/*!    
	\param[in] flDOVDD 0.0V~3.5V范围可调, 实际所设电压= flDOVDD *flMultiple
	\param[in] flAVDD 0.0V~3.5V范围可调, 实际所设电压= flAVDD *flMultiple
	\param[in] flDVDD 0.0V~3.5V范围可调, 实际所设电压= flDVDD *flMultiple
	\param[in] flAF 0.0V~3.5V范围可调, 实际所设电压= flAF *flMultiple
	\param[in] flVFuse 0.0V~10.0V范围可调, 实际所设电压= flVFuse *flMultiple
	\param[in] flPOW 0.0V~3.5V范围可调【R5】, 实际所设电压= flPOW *flMultiple
	\param[in] flIODD 0.0V~3.5V范围可调【板卡内部IO电平】【R5】, 实际所设电压= flIODD *flMultiple
	\param[in] usSwitch 设置电压开关， _HisFX3_Platform_VoltFlag，
									  eg,设置AVDD和DVDD电压， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] flMultiple 电压值系数
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3Set5V12V, HisFX3SetVolt, HisFX3GetVolt_S2, _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetVolt_S2(float flDOVDD=0, float flAVDD=0, float flDVDD=0, float flAF = 0, float flVFuse=0, float flPOW=0, float flIODD = 0, unsigned short usSwitch=0xFF, float flMultiple=0.1f);

	//! 获取通道1当前设置电压
	/*!    
	\param[out] pflDOVDD 当前DOVDD设置电压
	\param[out] pflAVDD 当前AVDD设置电压
	\param[out] pflDVDD 当前DVDD设置电压
	\param[out] pflAF 当前AF设置电压
	\param[out] pflVFuse 当前VFuse设置电压
	\param[out] pflPOW 当前POW设置电压
	\param[out] pflIODD 当前IODD设置电压
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3SetVolt,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetVolt(float* pflDOVDD=NULL, float* pflAVDD=NULL, float* pflDVDD=NULL, float* pflAF=NULL, float* pflVFuse=NULL, float* pflPOW=NULL, float* pflIODD=NULL);

	//! 获取通道2当前设置电压
	/*!    
	\param[out] pflDOVDD 当前DOVDD设置电压
	\param[out] pflAVDD 当前AVDD设置电压
	\param[out] pflDVDD 当前DVDD设置电压
	\param[out] pflAF 当前AF设置电压
	\param[out] pflVFuse 当前VFuse设置电压
	\param[out] pflPOW 当前POW设置电压
	\param[out] pflIODD 当前IODD设置电压
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3SetVolt_S2,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetVolt_S2(float* pflDOVDD=NULL, float* pflAVDD=NULL, float* pflDVDD=NULL, float* pflAF=NULL, float* pflVFuse=NULL, float* pflPOW=NULL, float* pflIODD=NULL);

	//! 废弃
	int HisFX3SetVFuseVolt(unsigned char ucVFUSE);

	//! 废弃
	int HisFX3GetVFuseVolt(float* pflVFUSE = NULL);

	//! 设置通道1 MCLK时钟
	/*!    
	\param[in] flMCLK 0~136MHz可调， 单位: MHz
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3GetMCLK,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetMCLK(float flMCLK);

	//! 设置通道2 MCLK时钟
	/*!    
	\param[in] flMCLK 0~136MHz可调， 单位: MHz
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3GetMCLK_S2,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetMCLK_S2(float flMCLK);

	//! 获取通道1当前MCLK设置时钟
	/*!    
	\param[out] pflMCLK 单位: MHz
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3SetMCLK,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetMCLK(float* pflMCLK);

	//! 获取通道2当前MCLK设置时钟
	/*!    
	\param[out] pflMCLK 单位: MHz
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3SetMCLK_S2,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetMCLK_S2(float* pflMCLK);

	//! 设置通道1 Sensor数据格式
	/*! 
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetMIPILane, _HisFX3_MIPILane_Stream
	*/
	int HisFX3SetMIPILane(unsigned char ucLane);

	//! 设置通道2 Sensor数据格式
	/*! 
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetMIPILane, _HisFX3_MIPILane_Stream
	*/
	int HisFX3SetMIPILane_S2(unsigned char ucLane);

	//! 获取当前设置的通道1 Sensor数据格式
	/*! 
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetMIPILane, _HisFX3_MIPILane_Stream
	*/
	int HisFX3GetMIPILane(unsigned char* pucLane);	

	//! 获取当前设置的通道2 Sensor数据格式
	/*! 
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetMIPILane_S2, _HisFX3_MIPILane_Stream
	*/
	int HisFX3GetMIPILane_S2(unsigned char* pucLane);

	//! 设置并口VS, HS同步信号
	/*! 一般只需要设置VS信号， HS信号保持默认
	\param[in] bDVP_VS_ActiveHigh VS信号， true:高电平数据有效， false: 低电平数据有效
	\param[in] bDVP_HS_ActiveHigh HS信号， true:高电平数据有效， false: 低电平数据有效
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3GetDVPHSVS, _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetDVPHSVS(bool bDVP_VS_ActiveHigh=false, bool bDVP_HS_ActiveHigh=true);

	//! 获取当前设置的并口VS, HS同步信号
	/*! 
	\param[out] pbDVP_VS_ActiveHigh VS信号
	\param[out] pbDVP_HS_ActiveHigh HS信号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa HisFX3SetDVPHSVS, _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetDVPHSVS(bool* pbDVP_VS_ActiveHigh=NULL, bool* pbDVP_HS_ActiveHigh=NULL);

	//! 设置并口采集同步信号相移
	/*! 
	\param[in] sCountPs18  0:不相移;  1: 90度;  2: 180度;  3: 270度;
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3DVPPCLKPhaseShift(short sCountPs18);

	//! 获取FPGA程序版本号
	/*!    
	\param[out] puiversion 版本号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3OpenDevice,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetHardwareVersion(unsigned int* puiversion);

	//! 获取开短路程序版本号
	/*!    
	\param[out] pusversion 版本号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3OpenDevice,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetOSVersion(unsigned short* pusversion);

	//! 获取FX3程序版本号
	/*!    
	\param[out] pusversion 版本号
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3OpenDevice,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetFX3Version(unsigned short* pusversion);

	//! 保留
	int HisFX3GetHardGeneration(unsigned int* puiGernation);

	int HisFX3CurrentCalibration(unsigned int* puiKey, _HisFX3_Current_Calibration* pstCal);
	int HisFX3CurrentCalibration_S2(unsigned int* puiKey, _HisFX3_Current_Calibration* pstCal);

	int HisFX3SetCurrentCalData(_HisFX3_Current_Calibration* pstCal);
	int HisFX3SetCurrentCalData_S2(_HisFX3_Current_Calibration* pstCal);

	//! 测量通道1工作电流
	/*!    
	\param[out] flAVDD 返回的AVDD电流
	\param[out] flDVDD 返回的DVDD电流
	\param[out] flDOVDD 返回的DOVDD电流
	\param[out] flAF 返回的AF电流
	\param[out] flVFuse 返回的VFuse电流
	\param[out] flPOW 返回的POW电流【R5】【R3X】【R5X】
	\param[in] uiFlag 设置要测哪些路的电流值， _HisFX3_Platform_VoltFlag，
									 eg,要测AVDD和DVDD电流， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] uiAverageTimes 取uiAverageTimes次数据，然后求平均
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3GetStandbyCurrent,  HisFX3GetWorkCurrent_S2, HisFX3GetStandbyCurrent_S2, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetWorkCurrent(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flVFuse, float& flPOW, unsigned int uiFlag=0xFF, unsigned int uiAverageTimes = 17);

	//! 测量通道2工作电流
	/*!    
	\param[out] flAVDD 返回的AVDD电流
	\param[out] flDVDD 返回的DVDD电流
	\param[out] flDOVDD 返回的DOVDD电流
	\param[out] flAF 返回的AF电流
	\param[out] flVFuse 返回的VFuse电流
	\param[out] flPOW 返回的POW电流【R5】【R3X】【R5X】
	\param[in] uiFlag 设置要测哪些路的电流值， _HisFX3_Platform_VoltFlag，
									 eg,要测AVDD和DVDD电流， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] uiAverageTimes 取uiAverageTimes次数据，然后求平均
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3GetStandbyCurrent,  HisFX3GetWorkCurrent, HisFX3GetStandbyCurrent_S2, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetWorkCurrent_S2(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flVFuse, float& flPOW, unsigned int uiFlag=0xFF, unsigned int uiAverageTimes = 17);
	
	//! 测量通道1静态电流
	/*!    
	\param[out] flAVDD 返回的AVDD电流
	\param[out] flDVDD 返回的DVDD电流
	\param[out] flDOVDD 返回的DOVDD电流
	\param[out] flAF 返回的AF电流
	\param[out] flPOW 返回的POW电流【R5】【R3X】【R5X】
	\param[in] uiFlag 设置要测哪些路的电流值， _HisFX3_Platform_VoltFlag，
									 eg,要测AVDD和DVDD电流， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] bPWND	true:拉PWND进入待机模式，  false:无需拉PWND信号
	\param[in] bReset	true:拉RST进入待机模式，  false:无需拉RST信号
	\param[in] bMCLK	true:MCLK设为0MHz进入待机模式，  false:无需把MCLK始终设为0MHz
	\param[in] bDVDD	true:DVDD设为0V进入待机模式，  false:无需把DVDD进入0V
	\param[in] uiDelay	进入待机模式后延时uiDelay ms之后再测待机电流
	\param[in] uiAverageTimes 取uiAverageTimes次数据，然后求平均
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3GetWorkCurrent,  HisFX3GetWorkCurrent_S2, HisFX3GetStandbyCurrent_S2, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetStandbyCurrent(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flPOW, unsigned int uiFlag=0xFF, \
		bool bPWND=true, bool bReset=true,  bool bMCLK=true, bool bDVDD=false, unsigned int uiDelay=5000, unsigned int uiAverageTimes = 7);

	//! 测量通道2静态电流
	/*!    
	\param[out] flAVDD 返回的AVDD电流
	\param[out] flDVDD 返回的DVDD电流
	\param[out] flDOVDD 返回的DOVDD电流
	\param[out] flAF 返回的AF电流
	\param[out] flPOW 返回的POW电流【R5】【R3X】【R5X】
	\param[in] uiFlag 设置要测哪些路的电流值， _HisFX3_Platform_VoltFlag，
									 eg,要测AVDD和DVDD电流， _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] bPWND	true:拉PWND进入待机模式，  false:无需拉PWND信号
	\param[in] bReset	true:拉RST进入待机模式，  false:无需拉RST信号
	\param[in] bMCLK	true:MCLK设为0MHz进入待机模式，  false:无需把MCLK始终设为0MHz
	\param[in] bDVDD	true:DVDD设为0V进入待机模式，  false:无需把DVDD进入0V
	\param[in] uiDelay	进入待机模式后延时uiDelay ms之后再测待机电流
	\param[in] uiAverageTimes 取uiAverageTimes次数据，然后求平均
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa   HisFX3GetStandbyCurrent,  HisFX3GetWorkCurrent_S2, HisFX3GetWorkCurrent, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetStandbyCurrent_S2(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flPOW, unsigned int uiFlag=0xFF, \
		bool bPWND=true, bool bReset=true,  bool bMCLK=true, bool bDVDD=false, unsigned int uiDelay=5000, unsigned int uiAverageTimes = 7);
	
	int HisFX3VlotageCalibration(unsigned int* puiKey, _HisFX3_Voltage_Calibration* pstCal);
	int HisFX3VlotageCalibration_S2(unsigned int* puiKey, _HisFX3_Voltage_Calibration* pstCal);
	int HisFX3SetVoltageCalData(_HisFX3_Voltage_Calibration* pstCal);
	int HisFX3SetVoltageCalData_S2(_HisFX3_Voltage_Calibration* pstCal);

	//! 正向对地开路测试
	/*!
	\param[in] ucSwitch   0：测试第一路MIPI  1：测试并口	2：测试第二路MIPI
	\param[inout]   vectorConfigconst  配置要进行开路测试的PIN脚
	\param[in] cuiCurrentWaitTime 电流稳定时间：cuiCurrentWaitTime (ms)
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3OSNegtiveTest,  HisFX3OSShortTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSPositiveTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Positive_Item>& vectorConfigconst, const unsigned int cuiCurrentWaitTime=4);

	//! 负向对DOVDD开路测试
	/*!
	\param[in] ucSwitch   0：测试第一路MIPI  1：测试并口	2：测试第二路MIPI
	\param[inout]   vectorConfig  配置要进行测试的PIN脚
	\param[in] cuiCurrentWaitTime 电流稳定时间：cuiCurrentWaitTime (ms)
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSShortTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSNegtiveTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Negtive_Item>& vectorConfig, const unsigned int cuiCurrentWaitTime=4);

	//! 短路测试
	/*!
	\param[in] ucSwitch   0：测试第一路MIPI  1：测试并口	2：测试第二路MIPI
	\param[inout]   vectorConfig  配置要进行测试的PIN脚
	\param[in] cuiCurrentWaitTime 电流稳定时间：cuiCurrentWaitTime (ms)
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSNegtiveTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSShortTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Short_Item>& vectorConfig, const unsigned int cuiCurrentWaitTime=4);

	//! 开路测试
	/*!
	\param[in] ucSwitch   0：测试MIPI  1：测试并口
	\param[inout]   vectorConfig  配置要进行测试的PIN脚
	\param[in] cuiCurrentWaitTime 电流稳定时间：cuiCurrentWaitTime (ms)
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSNegtiveTest, HisFX3OSShortTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSOpenTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Open_Item>& vectorConfig, unsigned int cuiCurrentWaitTime);


	//! 阻值测试
	/*!
	\param[in] ucSwitch   0：测试第一路MIPI  1：测试并口	2：测试第二路MIPI
	\param[inout]   stConfig  配置要进行测试的PIN脚
	\param[in] flCurrent 测试阻值时所用的电流， 设为0.0则为1.3mA, 一般可以保持默认值
	\param[in] cuiCurrentWaitTime 电流稳定时间：cuiCurrentWaitTime (ms)
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSNegtiveTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSOhmTest(unsigned char ucSwitch, _HisFX3OS_OHM_Item& stConfig, float flCurrent = 0.0f, const unsigned int cuiCurrentWaitTime=4);

	int measureExteralVoltage(unsigned int uiChannel, float& flVolt);

	//! 设置通道1的输出IO的电平
	/*!
	\param[in] uiStatus  Bit0: 设置Out0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要设置Out0电平 1-要设置，0-不设置； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortRead, HisFX3IO_InPortRead
	*/
	int HisFX3IO_OutPortWrite(unsigned int uiStatus, unsigned int uiFlag = 0xFF);

	//! 设置通道2的输出IO的电平
	/*!
	\param[in] uiStatus  Bit0: 设置Out0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要设置Out0电平 1-要设置，0-不设置； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortRead_S2, HisFX3IO_InPortRead_S2
	*/
	int HisFX3IO_OutPortWrite_S2(unsigned int uiStatus, unsigned int uiFlag = 0xFF);

	//! 获取通道1输出IO口的电平状态
	/*!
	\param[in] uiStatus  Bit0: Out0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要获取Out0电平 1-要获取，0-不获取； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite, HisFX3IO_InPortRead
	*/
	int HisFX3IO_OutPortRead(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	//! 获取通道2输出IO口的电平状态
	/*!
	\param[in] uiStatus  Bit0: Out0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要获取Out0电平 1-要获取，0-不获取； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite_S2, HisFX3IO_InPortRead_S2
	*/
	int HisFX3IO_OutPortRead_S2(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	//! 获取通道1输入IO口的电平状态
	/*!
	\param[in] uiStatus  Bit0: In0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要获取In0电平 1-要获取，0-不获取； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite, HisFX3IO_OutPortRead
	*/
	int HisFX3IO_InPortRead(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	//! 获取通道2输入IO口的电平状态
	/*!
	\param[in] uiStatus  Bit0: In0电平 1-高电平，0-低电平； 以此类推...
	\param[in] uiFlag  Bit0: 是否要获取In0电平 1-要获取，0-不获取； 以此类推...
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite_S2, HisFX3IO_OutPortRead_S2
	*/
	int HisFX3IO_InPortRead_S2(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	int HisFX3LedControl(bool bOn, unsigned int* puiKey = 0);

	int HisFX3BuzzerControl(bool bOn, unsigned int* puiKey = 0);

	int getOSPinNameList(unsigned char ucSwitch, std::vector<std::string>& vecOSPin);
	int getOSPositiveGNDPinName(unsigned char ucSwitch, std::vector<std::string>& vecOSPin);
	int getOSNegtiveDOVDDPinName(unsigned char ucSwitch, std::vector<std::string>& vecOSPin);
	
	//! 保留
	int HisFX3R2OSSwitch(bool bOS);

	int HisFX3R2OSCalibration(unsigned int* puiKey, _HisFX3R2_OSCal_Item* pstCal, unsigned int uiItemCount);
	int HisFX3SetOSCalData(_HisFX3R2_OSCal_Item* pstCal, unsigned int uiItemCount);
	 
	//! 保留
	int HisFX3GetLInfo(unsigned char* pucGeneration, unsigned char* pucApplication, \
		unsigned char* pucFactory, unsigned char* pucAuthorization, unsigned char* pucReserve1, unsigned char* pucReserve2);
	 
	//! 保留
	int HisFX3WriteOSIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiData, unsigned short usType);

	//! 保留
	int HisFX3ReadOSIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int* puiData, unsigned short usType);

	//! 保留
	int HisFX3WriteCurrentIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiData, unsigned short usType);

	//! 保留
	int HisFX3ReadCurrentI2C(unsigned char ucSlave, unsigned int uiReg, unsigned int* puiData, unsigned short usType);

/*
	int HisFX3GetContinusFrames(bool bC1, bool bC2, unsigned int& uiFrameCount, unsigned int uiBufByte1=0, unsigned char** ppBuffer1=0, unsigned int uiBufByte2=0, unsigned char** ppBuffer2=0);
*/

	int HIsFX3ReadVoltageValue(float* pflDOVDD=0, float* pflAVDD=0, float* pflDVDD=0, float* pflAF=0, float* pflVFuse=0, float* pflPOW=0);
	int HIsFX3ReadVoltageValue_S2(float* pflDOVDD=0, float* pflAVDD=0, float* pflDVDD=0, float* pflAF=0, float* pflVFuse=0, float* pflPOW=0);

	//! 保留
	bool isDataStreaming(unsigned int uiTimeOut = 25);

	//! 保留
	bool isDataStreaming_S2(unsigned int uiTimeOut = 25);

	//! 保留
	int HisFX3VoltMonitorPin8(float* pflVoltage, unsigned short usFlag);

	int HisFX3UpdateFPGA(wchar_t* pwstrPath);
	int HisFX3SetOffLineMode(bool bEnable, wchar_t* pwstrPath);
	bool HisFX3GetOfflineModeInfo(unsigned int* puiWidth, unsigned int* puiHeight, _HisFX3_BaylorMode* pucDataformat, unsigned int* puiFrameByte);
	int HisFX3SetOffLineMode_S2(bool bEnable, wchar_t* pwstrPath);
	bool HisFX3GetOfflineModeInfo_S2(unsigned int* puiWidth, unsigned int* puiHeight, _HisFX3_BaylorMode* pucDataformat, unsigned int* puiFrameByte);
	void getFPGADecodeInfo(std::string& strInfo);
	void getFPGADecodeInfo_S2(std::string& strInfo);
	int GetTemperature(double* fpgaT);
	void getProtocalSupported(std::vector<unsigned int>& vecList, bool bChannel1 = true);
	int getDataFormatSupported(std::vector<_HisFX3_BaylorMode>& vecDataFormat);
	bool isWorkCurrentSupported(unsigned int uiFlag, bool bChannel1 = true);
	bool isStandbyCurrentSupported(unsigned int uiFlag, bool bChannel1 = true); 
	bool isOpenShortSupported(bool* bAllPin);
	bool getVoltageSupported(float& flmin, float& flmax, unsigned int uiFlag, bool bChannel1 = true);
	bool getCommunicationProtocalSupported(unsigned int uiFlag, bool bChannel1 = true);
	void getMCLKSupported(float& flmin, float& flmax);
	bool getDDRSupported();
	unsigned int getCameraCountSupported();
	_HisFX3_Platform_Type getCurrentPlatformType();

	//! 设置USB包的大小
	/*!
	\param[in] lsize   单位：Byte  范围：256*1024~4*1024*1024  注意必须是256*1024的整数倍
	\sa  getCurrentBulkTransformSize
	*/
	void setBulkTransformSize(LONG lsize);

	//! 设置当前USB包的大小
	/*!
	\return 包的大小，单位：Byte
	\sa  setBulkTransformSize
	*/
	LONG getCurrentBulkTransformSize();

	//! 获取通道1摄像头Sensor输出端帧索引
	/*!
	\return 帧索引
	\sa  getSensorFrameIndex_S2, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getSensorFrameIndex();

	//! 获取通道2摄像头Sensor输出端帧索引
	/*!
	\return 帧索引
	\sa  getSensorFrameIndex, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getSensorFrameIndex_S2();

	//! 获取通道1摄像头Sensor错误帧索引
	/*!
	\return 帧索引
	\sa  getSensorFrameIndex_S2, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getErrorFrameIndex();

	//! 获取通道1摄像头Sensor错误帧索引
	/*!
	\return 帧索引
	\sa  getSensorFrameIndex_S2, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getErrorFrameIndex_S2();

	//! 获取通道1上传帧索引
	/*!
	\return 帧索引
	\sa  getUploadFrameIndex_S2, getSensorFrameIndex, getSensorFrameIndex_S2
	*/
	unsigned __int64 getUploadFrameIndex();

	//! 获取通道2上传帧索引
	/*!
	\return 帧索引
	\sa  getUploadFrameIndex, getSensorFrameIndex, getSensorFrameIndex_S2
	*/
	unsigned __int64 getUploadFrameIndex_S2();


	void testComputerCompatibility(float* pflErrorRate, float* pflErrorRead);
	void setCurrentPlatformType(_HisFX3_Platform_Type platformType);

	//! 设置USB传输速率
	/*!
	\param[in] uiDelay   范围：10~240 时钟周期， 越小速率越大
	\return 0:成功  非0:失败 请参考_HisFX3Platform_ErrorCode
	\sa  _HisFX3Platform_ErrorCode
	*/
	int setUSBSpeed(unsigned int uiDelay);

	int LedControl(bool bOn);
	int BuzzerControl(bool bOn);

	int HisFX3StartAudio();
	int HisFX3StopAudio();
	int HisFX3GrabAudioBuffer(_HisPlatformAudio_Buffer* pstBuf, unsigned int uiTimeOut = 1500);
	int UVCSetProperty(int aProperty, float aValue, int aAuto = 0);

	//! 获取错误信息的字符串描述
	/*! 如果 属性->C/C++ ->语言->将WChar_t视为内置类型 设为否，则调用此函数；设为是，则调用GetLastErrorMB
	\return 错误信息字符串指针
	\sa  GetLastErrorMB, ClearError
	*/
	const wchar_t* GetLastError(void);

	bool HisFX3IsOpenLight();

	//! 获取错误信息的字符串描述
	/*! 如果 属性->C/C++ ->语言->将WChar_t视为内置类型 设为是，则调用此函数；设为否，则调用GetLastError
		 eg. wchar_t* pstrError = (wchar_t*)GetLastErrorMB();
	\return 错误信息字符串指针
	\sa  GetLastError, ClearError
	*/
	unsigned short* GetLastErrorMB(void);

	//! 清除错误信息
	/*! 
	\sa  GetLastError, GetLastErrorMB
	*/
	void ClearError(void);


	int DothinkeyINI2Rolongo(char* pstrRolongoIniPath, _HisFX3_PreviewStruct& stPreivewConfig);

	int decodeRolongoXML_A(char* pstrPath, _HisFX3_PreviewStruct& previewConfig, std::vector<_RolongoXMLOtherSectionItem>& vecPair);

	//! 保留
	void test();

	//! 保留
	bool checkSenseShieldEnabled(unsigned int uiLincenseID, unsigned char ucClient, unsigned char ucProduct);

	//! 保留
	int getPlatformType(unsigned short usPID, unsigned short usVID, char* pstrFriendlyName, unsigned char ucDeviceIndex, unsigned int* puiKey);

	//内部使用，不要操作***
	std::wstring wstrLastError;
	void* classInterLayer;

private:
	void* classRTSP;

	bool bOfflineMode;
	std::wstring wstrOfflineImagePath;
	unsigned __int64 ui64OfflineFrameIndex; 

	bool bOfflineMode_S2;
	std::wstring wstrOfflineImagePath_S2;
	unsigned __int64 ui64OfflineFrameIndex_S2; 

	//1: construct class fail

	std::string strSensorName;
	

	int HisFX3SetDataMode(unsigned char ucdataformat, unsigned int uiWidth, unsigned int uiHeight);
	int HisFX3ResetVolt();
	int getFPGADSN(unsigned char* ucnumber, unsigned int* puiFX3SerialNumber);

	 
#ifdef _HisFX3_Platform_Jigboard
	HMODULE Jig_m_hDllHandle;
	int HisFX3OpenDevice_Jigboard(wchar_t* szYB);
	int HisFX3CloseDevice_Jigboard();
	int HisFX3StartPreview_Jigboard();
	int HisFX3StopPreview_Jigboard();
	int HisFX3GrabFrame_Jigboard(unsigned char **ppucBuffer, unsigned int uiBufBytes, unsigned __int64& ui64FramIndex);
	unsigned __int64 Jig_ui64FramIndex;
	wchar_t Jig_strIniPath[MAX_PATH];
#endif
};

//!  设置USB包的大小
/*! 当类对象析构的时候，会自动设回原来的大小
*/
class HISFX3PLATFORM_EXPORT QHisFX3PlatformAutoTransformSize
{
public:
	QHisFX3PlatformAutoTransformSize(CHisFX3Platform* classPlatform2, LONG lNewSize);
	~QHisFX3PlatformAutoTransformSize(void);

private:
	LONG lOriginalSize;
	CHisFX3Platform* classPlatform;
};

#ifdef _HISFX3PLATFORM_EXPORT_DUXIN
typedef struct _SensorTab_RLG
{
	/// @brief SENSOR宽度
	USHORT width;          ///<SENSOR宽度
	/// @brief SENSOR高度
	USHORT height;         ///<SENSOR高度
	/// @brief SENSOR数据类型
	BYTE type;             ///<SENSOR数据类型
	/// @brief SENSOR的RESET和PWDN引脚设置
	BYTE pin;              ///<SENSOR的RESET和PWDN引脚设置
	/// @brief SENSOR的器件地址
	BYTE SlaveID;          ///<SENSOR的器件地址
	/// @brief SENSOR的I2C模式
	BYTE mode;						 ///<SENSOR的I2C模式
	/// @brief SENSOR标志寄存器1.
	USHORT FlagReg;				 ///<SENSOR标志寄存器1.
	/// @brief SENSOR标志寄存器1的值
	USHORT FlagData;			 ///<SENSOR标志寄存器1的值
	/// @brief SENSOR标志寄存器1的掩码值
	USHORT FlagMask;			 ///<SENSOR标志寄存器1的掩码值
	/// @brief SENSOR标志寄存器2.
	USHORT FlagReg1;			 ///<SENSOR标志寄存器2.
	/// @brief SENSOR标志寄存器2的值
	USHORT FlagData1;			 ///<SENSOR标志寄存器2的值
	/// @brief SENSOR标志寄存器2的掩码值
	USHORT FlagMask1;			 ///<SENSOR标志寄存器2的掩码值
	/// @brief SENSOR的名称
	char name[64];				///<SENSOR的名称

	/// @brief 初始化SENSOR数据表
	USHORT* ParaList;			///<初始化SENSOR数据表
	/// @brief 初始化SENSOR数据表大小，单位字节
	USHORT  ParaListSize; ///<初始化SENSOR数据表大小，单位字节

	/// @brief SENSOR进入PLATFORMSHARE::Sleep模式的参数表
	USHORT* SleepParaList;	///<SENSOR进入PLATFORMSHARE::Sleep模式的参数表
	/// @brief SENSOR进入PLATFORMSHARE::Sleep模式的参数表大小，单位字节
	USHORT  SleepParaListSize;///<SENSOR进入PLATFORMSHARE::Sleep模式的参数表大小，单位字节

	/// @brief SENSOR输出数据格式，YUV//0:YCbYCr;	//1:YCrYCb;	//2:CbYCrY;	//3:CrYCbY.
	BYTE outformat;         ///<SENSOR输出数据格式，YUV//0:YCbYCr;	//1:YCrYCb;	//2:CbYCrY;	//3:CrYCbY.
	/// @brief SENSOR的输入时钟MCLK，0:12M; 1:24M; 2:48M.
	int mclk;               ///<SENSOR的输入时钟MCLK，0:12M; 1:24M; 2:48M.
	/// @brief SENSOR的AVDD电压值
	BYTE avdd;              ///<SENSOR的AVDD电压值
	/// @brief SENSOR的DOVDD电压值
	BYTE dovdd;             ///<SENSOR的DOVDD电压值
	/// @brief SENSOR的DVDD电压值		
	BYTE dvdd;							///<SENSOR的DVDD电压值

	/// @brief SENSOR的数据接口类型
	BYTE port; 							///<SENSOR的数据接口类型
	USHORT Ext0;
	USHORT Ext1;
	USHORT Ext2; 

	/// @brief AF初始化参数表
	USHORT* AF_InitParaList;        ///<AF初始化参数表
	/// @brief AF初始化参数表大小，单位字节
	USHORT  AF_InitParaListSize;		///<AF初始化参数表大小，单位字节

	/// @brief AF_AUTO参数表
	USHORT* AF_AutoParaList;				///<AF_AUTO参数表
	/// @brief AF_AUTO参数表大小，单位字节
	USHORT  AF_AutoParaListSize;		///<AF_AUTO参数表大小，单位字节

	/// @brief AF_FAR参数表
	USHORT* AF_FarParaList;					///<AF_FAR参数表
	/// @brief AF_FAR参数表大小，单位字节
	USHORT  AF_FarParaListSize;			///<AF_FAR参数表大小，单位字节

	/// @brief AF_NEAR参数表
	USHORT* AF_NearParaList;				///<AF_NEAR参数表
	/// @brief AF_NEAR参数表大小，单位字节
	USHORT  AF_NearParaListSize;		///<AF_NEAR参数表大小，单位字节

	/// @brief 曝光参数表
	USHORT* Exposure_ParaList;      ///<曝光参数表
	/// @brief 曝光参数表大小，单位字节
	USHORT  Exposure_ParaListSize;	///<曝光参数表大小，单位字节

	/// @brief 增益参数表
	USHORT* Gain_ParaList;          ///<增益参数表
	/// @brief 增益参数表大小，单位字节
	USHORT	Gain_ParaListSize;			///<增益参数表大小，单位字节 

	_SensorTab_RLG()
	{
		width=0;
		height=0;
		type=0;
		pin=0;
		SlaveID=0;
		mode=0;
		FlagReg=0;
		FlagData=0;
		FlagMask=0;
		FlagReg1=0;
		FlagData1=0;
		FlagMask1=0;
		memset(name,0,sizeof(name));

		ParaList=NULL;
		ParaListSize=0;
		SleepParaList=NULL;
		SleepParaListSize=0;

		outformat=0;
		mclk=0;               //0:12M; 1:24M; 2:48M.
		avdd=0;               // 
		dovdd=0;              //
		dvdd=0;

		port=0; 	
		Ext0=0;
		Ext1=0;
		Ext2=0; 

		AF_InitParaList=NULL;        //AF_InitParaList
		AF_InitParaListSize=0;

		AF_AutoParaList=NULL;
		AF_AutoParaListSize=0;

		AF_FarParaList=NULL;
		AF_FarParaListSize=0;

		AF_NearParaList=NULL;
		AF_NearParaListSize=0;

		Exposure_ParaList=NULL;      //曝光
		Exposure_ParaListSize=0;

		Gain_ParaList=NULL;          //增益
		Gain_ParaListSize=0;
	}
}SensorTab_RLG, *pSensorTab_RLG;

extern "C"
{	

namespace RLGDX
{
	HISFX3PLATFORM_EXPORT int EnumerateDevice(char *DeviceName[],int iDeviceNumMax,int *pDeviceNum);
	HISFX3PLATFORM_EXPORT BOOL IsDevConnect( int CurDev=-1);
	HISFX3PLATFORM_EXPORT int OpenDevice(const char *pszDeviceName,int *pDevID,int CurDev=0);
	HISFX3PLATFORM_EXPORT void CloseDevice( int CurDev=-1);
	HISFX3PLATFORM_EXPORT CHisFX3Platform* GetPlatformPoniter(int CurDev=-1);
	HISFX3PLATFORM_EXPORT void SetCurrentDeviceObject( int CurDev = 0);
	HISFX3PLATFORM_EXPORT void SetAlarm(USHORT beeptime, BYTE beepcount, int CurDev=-1);	
	HISFX3PLATFORM_EXPORT DWORD GetKitType( int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int SetSensorI2cRate( BOOL  b400K,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int SetSensorI2cRate_S2( BOOL  b400K,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int WriteSensorReg(UCHAR  uAddr,  USHORT  uReg,  USHORT  uValue,  BYTE  byMode,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int WriteSensorReg_S2(UCHAR  uAddr,  USHORT  uReg,  USHORT  uValue,  BYTE  byMode,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int ReadSensorReg(UCHAR  uAddr,  USHORT  uReg,  USHORT *  pValue,  BYTE  byMode,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int ReadSensorReg_S2(UCHAR  uAddr,  USHORT  uReg,  USHORT *  pValue,  BYTE  byMode,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int WriteSensorI2c(UCHAR  uDevAddr,  USHORT  uRegAddr,  UCHAR  uRegAddrSize,  BYTE *  pData,  USHORT  uSize,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int WriteSensorI2c_S2(UCHAR  uDevAddr,  USHORT  uRegAddr,  UCHAR  uRegAddrSize,  BYTE *  pData,  USHORT  uSize,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int ReadSensorI2c(UCHAR  uDevAddr,  USHORT  uRegAddr,  UCHAR  uRegAddrSize,  BYTE *  pData,  USHORT  uSize,  BOOL  bNoStop = FALSE,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int ReadSensorI2c_S2(UCHAR  uDevAddr,  USHORT  uRegAddr,  UCHAR  uRegAddrSize,  BYTE *  pData,  USHORT  uSize,  BOOL  bNoStop = FALSE,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int SetSensorClock( BOOL  bOnOff,  USHORT  uHundKhz,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int SetSensorClock_S2( BOOL  bOnOff,  USHORT  uHundKhz,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int SetSpiRate( int  Rate,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int PmuSetVoltage(unsigned int Power[],  int  Voltage[],  int  iCount,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int PmuGetVoltage(unsigned int  Power[],  int  Voltage[],  int  iCount,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int PmuGetCurrent(unsigned int  Power[],  int  Current[],  int  iCount,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int SensorEnable(BYTE  byPin,  BOOL  bEnable,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int SensorEnable_S2(BYTE  byPin,  BOOL  bEnable,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int SetGrabTimeout(ULONG  uTimeOut,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int SetGrabTimeout_S2(ULONG  uTimeOut,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int GrabFrame(BYTE *  pInBuffer,  ULONG  uBufferSize,  ULONG *  pGrabSize = 0,  unsigned __int64*  p64FrameIndex = 0,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int GrabFrame_S2(BYTE *  pInBuffer,  ULONG  uBufferSize,  ULONG *  pGrabSize = 0,  unsigned __int64*  p64FrameIndex = 0,  int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int DXPara2RLGPara(SensorTab_RLG *  pInfo,  _HisFX3_PreviewStruct* pstPreviewInfo); 
	HISFX3PLATFORM_EXPORT void AddGernerPreviewPara(_HisFX3_PreviewStruct* pstPreviewInfo, bool bDebug=false, bool bUseDDR=false, bool bCheckDeviceAck=false, \
		_HisFX3_ImageSenor_Factory sensorFactory=_HisFX3_ImageSenor_Factory_OV, unsigned char ucCommProtocal=0,unsigned short usI2CSpeed=100,unsigned short usI2CIntervalTime=100, \
		unsigned char ucMIPILane=_HisFX3_MIPILane_Stream_Lane4_FPGA);
	HISFX3PLATFORM_EXPORT void AddDVPPreviewPara(_HisFX3_PreviewStruct* pstPreviewInfo, bool bDVP_VS_ActiveHigh=false, bool bDVP_HS_ActiveHigh=true,unsigned char ucDVP_LineFormat =1, unsigned char ucDVP_PhaseShift =0);
	HISFX3PLATFORM_EXPORT void AddLVDSPreviewPara(_HisFX3_PreviewStruct* pstPreviewInfo, bool bSPICSLow=true,bool bSPILittleEndian=false, unsigned char ucLaneNum=10, \
		bool bOutputXSVS=true, unsigned int uiLVDS_XHS=1152,unsigned int uiLVDS_XVS=3125,unsigned short usLVDSAlign=0x0);
	HISFX3PLATFORM_EXPORT int StartPreview(_HisFX3_PreviewStruct*  pstPreviewInfo, int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int StartPreview_S2(_HisFX3_PreviewStruct*  pstPreviewInfo, int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int StopPreview(int  iDevID = -1);
	HISFX3PLATFORM_EXPORT int StopPreview_S2(int  iDevID = -1);
}

}
#endif

#ifdef _HISFX3PLATFORM_EXPORT_HYVISION
extern "C"
{	
	namespace RLGHV
	{
		HISFX3PLATFORM_EXPORT CHisFX3Platform* GetPlatformPonit(int nBoard=0);
		HISFX3PLATFORM_EXPORT int OpenDAQDevice(char **DeviceName = 0);
		HISFX3PLATFORM_EXPORT BOOL CloseDAQDevice(void);
		HISFX3PLATFORM_EXPORT BOOL  LVDS_Init_Mul_Key(const char *pszDeviceName,int *pDevID);
		HISFX3PLATFORM_EXPORT BOOL  LVDS_Init_Mul(int nBoard);
		HISFX3PLATFORM_EXPORT BOOL  LVDS_GetVersion_Mul(int nBoard, int *nFpgaVer, int *nFirmVer);
		HISFX3PLATFORM_EXPORT BOOL  LVDS_SetDataMode_Mul(int nBoard, int nMode);
		HISFX3PLATFORM_EXPORT BOOL  I2C_SYS_Read_Mul(int nBoard, BYTE slAddr, DWORD nAddrLen, DWORD nAddr, DWORD nCnt, unsigned char* buf);
		HISFX3PLATFORM_EXPORT BOOL  I2C_SYS_Write_Mul(int nBoard, BYTE slAddr, DWORD nAddrLen, DWORD nAddr, DWORD nCnt, unsigned char* buf);
		HISFX3PLATFORM_EXPORT BOOL  LVDS_GetResolution_Mul(int nBoard, DWORD *xRes, DWORD *yRes);
		HISFX3PLATFORM_EXPORT BOOL  LVDS_Start_Mul(int nBoard);
		HISFX3PLATFORM_EXPORT BOOL  LVDS_Stop_Mul(int nBoard);
		HISFX3PLATFORM_EXPORT BOOL  LVDS_GetFrame_Mul(int nBoard, DWORD* nCnt, unsigned char* buf);
		//ch_index  0:DVDD 1:AVDD 2:DOVDD 3:AF  4:OTP 
		HISFX3PLATFORM_EXPORT int	_stdcall Program_PowerSetM(int ch_index, float fvolt, int index);
		HISFX3PLATFORM_EXPORT int	_stdcall	Program_PowerOnOff_Fix36M(BOOL bPowerOn, int index);
		HISFX3PLATFORM_EXPORT int	_stdcall 	IOlevel_SetM(float fvolt, int index); //1.6 ~ 3.5 range 棺 table 荐沥. (2006. 3/13)
		HISFX3PLATFORM_EXPORT int	_stdcall 	Program_PowerOffM(int ch_index, int index);
		HISFX3PLATFORM_EXPORT int	_stdcall 	Program_PowerOffAllM(int index);
		HISFX3PLATFORM_EXPORT int	_stdcall	Program_PowerIOSetAllM(float fch0volt, float fch1volt, float fch2volt, float fch3volt, float fch4volt, BOOL bch5on, float fIOvolt, int index);		  //Power: 1.2~3.0V, IO:1.6~3.0V
		HISFX3PLATFORM_EXPORT int	_stdcall	DynamicMeasureM(int ch_index, int offset_value, float *measure_value, int iMeasureConut=17, int index=0);
		HISFX3PLATFORM_EXPORT int	_stdcall	StandbyMeasureM(int ch_index, int offset_value, float *measure_value, int iMeasureConut=7, int index=0);
		HISFX3PLATFORM_EXPORT BOOL CLK_Set_Mul(int nBoard, DWORD val);
		HISFX3PLATFORM_EXPORT DWORD CLK_Get_Mul(int nBoard);
		HISFX3PLATFORM_EXPORT BOOL  SEN_Reset_Mul(int nBoard, BOOL bReset);
		HISFX3PLATFORM_EXPORT BOOL  SEN_Enable_Mul(int nBoard, BOOL bEnble);
	}
}
#endif

#endif

