
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DTCCM_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DTCCM_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//20120224 added Dual DemoKit work support.. should set CurDev to your need....
/*
OpenCamera
1.bCreatDeviceObject( int CurDev=-1);   //create device handle...
2.bFX2IsMe(TRUE, int CurDev=-1);         //judge the device is connected or not?
3.SetWorkMode(0, int CurDev=-1);         //set work mode to image 
4.SetModulePin( int CurDev=-1);         //set soft pin 
5.SetSensorVoltage()      //set sensor voltage
6.SetSensorPowerOnOff()   //power on sensor
7.SetSoftPinPullUp(IO_PULLUP, int CurDev=-1); //pull up soft pin...
8.SetSensorMClk(m_mclki)       //set mclk on   
9.SetPMURange(PMU1_1, PMU2_1, PMU3_1, PMU4_1, PMU5_1, int CurDev=-1); //set PMU measure range...
10.SetI2CRate(m_I2CRate, int CurDev=-1); //400K                       //set I2C rate
11.bSensorEnable()
12.bFindSensorAndInit( int CurDev=-1);                               //find sensor and init
13.SetSensorOutPort(CurrentSensor.port, int CurDev=-1);               //set sensor port to current sensor's need...   
14.SetPreviewMode(m_PreviewMode, int CurDev=-1);                      //should call this to set the receiver 
15.SetBufIOVoltage()                                   //set receiver buf io voltage to be compatible with DOVDD,sensor...
16.buffer memory ..                                    //should set memory buffer...
17.OpenVideo()...                                      //open video....
18.open thread to capture and display...               //start to capture and display it...

//Close sequence...
1.close thread to stop...
2.CancelIoWait()
3.CloseVideo()
4,Kill buffer memory..
5.bSensorEnable()  .....set reset and pwdn to standby state...
6.SetSensorMclkEnable(OFF)  //close mclk...
7.SetPMURange(PMU1_2, PMU2_2, PMU3_2, PMU4_2, PMU5_2, int CurDev=-1);
8.bDeleteDeviceObject()
CloseCamera.
*/

#ifndef _DTCCM_H_
#define _DTCCM_H_


#define _DTCALL_  



#include "imagekit.h"

#ifdef DTCCM_EXPORTS

	#define DTCCM_API extern "C"  __declspec(dllexport)

#else

	#define DTCCM_API extern "C"  __declspec(dllimport)

#endif

/*! \mainpage DOTHINKEY ImageKit API Manual
*
* \section 产品介绍
*
* - USB2.0系列
* -# HS128
* -# HS280
* -# HS300
* -# HS300D
* -# HV810
* -# HV810D
* -# HV910
* -# HV910D
* - PCIE系列
* -# PE300
* -# PE300D
* -# PE810
* -# PE810D
* -# PE910
* -# PE910D
* - USB3.0系列
* -# UT300
* -# UO300
* -# UV910
* -# UF910
* -# UH910
* -# DTLC2
*
*
* \section  公司网址
* http://www.dothinkey.com
* 
* 
*
* \section 文档发布版本记录
*
* -# 2014/5/15 生成DTCC2APIGuide；\n


*			   DTCCM2APIGuide版本为：1.0.0.0；
*
* -# 2014/5/30 新增加复位SENSOR图像数据接口函数ResetSensorPort；\n
*              DTCCM2APIGuide版本为：1.0.1.1；
*
*/

/******************************************************************************
设备信息相关
******************************************************************************/
/** @defgroup group1 设备信息相关
@{

*/
//////////////////////////////////////////////////////////////////////////
//You can call this after calling bFX2IsMe(), this will tell the demokit true sn.
/*
Name :GetDeviceSN
Function : get the sn.(sn is 8bytes..),
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 获取设备的序列号。
///
/// @param pSN：返回的设备序列号
DTCCM_API void _DTCALL_ GetDeviceSN(BYTE *pSN, int CurDev=-1);

//return firmware version
/// @brief 返回设备功能ID。
/// 
/// @retval 0x1180：HS128测试板
/// @retval 0x1280：HS230测试板
/// @retval 0x1330：HS300测试板
/// @retval 0x1332：HS300D测试板
/// @retval 0x1380：HV810测试板
/// @retval 0x1382：HV810D测试板
/// @retval 0x1390：HV910测试板
/// @retval 0x1392：HV910D测试板
///
/// @retval 0x1330：PE300测试板
/// @retval 0x1332：PE300D测试板
/// @retval 0x1380：PE810测试板
///	@retval 0x1382：PE810D测试板
/// @retval 0x1390：PE910测试板
///	@retval 0x1392：PE910D测试板
///
///	@retval 0x1332：UT300测试板
/// @retval 0x1333：UO300测试板
///	@retval 0x1393：UV910测试板
///	@retval 0x1392：UF910测试板
///	@retval 0x1392：UH910测试板
///	@retval 0x13A2：DTLC2测试板
DTCCM_API DWORD _DTCALL_ GetFWVersion( int CurDev=-1);

/// @brief 返回设备的型号，区分不同的测试板。
///
/// @retval 0x0010：HS128测试板
/// @retval 0x0020：HS230测试板
/// @retval 0x0030：HS300测试板
/// @retval 0x0031：HS300D测试板
/// @retval 0x0082：HV810测试板
/// @retval 0x0083：HV810D测试板
/// @retval 0x0092：HV910测试板
/// @retval 0x0093：HV910D测试板
///
/// @retval 0x0130：PE300测试板
/// @retval 0x0131：PE300D测试板
/// @retval 0x0180：PE810测试板
///	@retval 0x0181：PE810D测试板
/// @retval 0x0190：PE910测试板
///	@retval 0x0191：PE910D测试板
///
///	@retval 0x0231：UT300测试板
///	@retval 0x0232：UO300测试板
///	@retval 0x0291：UV910测试板
///	@retval 0x0292：UF910测试板
///	@retval 0x0293：UH910测试板
///	@retval 0x02A1：DTLC2测试板
DTCCM_API DWORD _DTCALL_ GetKitType(int CurDev=-1);

//return lib version;
/// @brief 获取本类的版本编号，派生类可以返回自己的版本编号。
///
/// @retval 返回本类的版本号
DTCCM_API DWORD _DTCALL_ GetLibVersion( int CurDev=-1);

/// @brief 获取FPGA版本号。
///
/// @retval 返回FPGA版本号
DTCCM_API DWORD _DTCALL_ GetFPGAVersion(int CurDev=-1);

/// @brief 获取FPGA版本ID。
///
/// @param Chip：为0:PCI-E采集卡上的FPGA，1：主板上的FPGA;
/// 
/// @retval 返回FPGA版本ID
/// 
/// @note 仅PE系列支持改函数
DTCCM_API DWORD _DTCALL_ GetFPGAID(int Chip,int CurDev=-1);

//return Hardware Version...
//pBuf : Version string in ASCII code buffer
//length:version string length..
/// @brief 获取硬件版本号。
///
/// @param pBuf：返回的硬件版本号
/// @param length：硬件版本号字节长度
/// 
/// @retval TRUE：获取硬件版本号成功
/// @retval FALSE：获取硬件版本号失败
DTCCM_API BOOL  _DTCALL_ GetHardwareVersion(BYTE* pBuf, BYTE length, int CurDev=-1);
/** @} */ // end of group1

/******************************************************************************
ISP相关
******************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Image Data process..
//////////////////////////////////////////////////////////////////////////
/** @defgroup group2 ISP相关


* @{

*/
/// @brief 此函数不支持
DTCCM_API int _DTCALL_ GetCenterAreaFocusValue(BYTE* pData, int width, int height, int CurDev=-1);

//mode should be 0-3;
//Set YUV422 mode, 
//0:YCbYCr;
//1:YCrYCb;
//2:CbYCrY;
//3:CrYCbY;
/// @brief 设置YUV格式，参见枚举类型“YUV_FORMAT”。
///
/// @param byYuvMode：YUV格式设置
///
/// @see YUV_FORMAT
DTCCM_API void _DTCALL_ SetYUV422Mode(BYTE mode, int CurDev=-1);

//mode should be 0-3;
//Set RGB raw mode, 
//0:RGGB; first line is RGRG.... ;second line is GBGB....;
//1:GRBG; first line is GRGR.... ;second line is BGBG....; 
//2:GBRG; first line is GBGB.... ;second line is RGRG....; 
//3:BGGR; first line is BGBG.... ;second line is GRGR....; 

/// @brief 设置RAW格式，参见枚举类型“RAW_FORMAT”。
///
/// @param byRawMode：RAW格式设置
///
/// @see RAW_FORMAT
DTCCM_API void _DTCALL_ SetRawMode(BYTE mode, int CurDev=-1);

//change the captured from usb(sensor) to RGB24 bmp data..
//pIn: usb data buffer pointer
//pOut:RGB24 data buffer pointer
//width:Image source width
//height Image source height
//type: sensor type. should be 0:10bit raw ;1:8bit raw;2:YUV422 data;3:16bit raw.

/// @brief RAW/YUV转RGB，源数据格式由ImgFormat指定。
///
/// @param pIn：源数据
/// @param pOut：转为RGB24的数据
/// @param width：图像数据宽度
/// @param height：图像数据高度
/// @param type：源数据的格式，0：10bit raw；1：8bit raw；2：YUV422 data；3：16bit raw
DTCCM_API void _DTCALL_ USBDataToRGB24(BYTE* pIn, BYTE* pOut, USHORT width, USHORT height, BYTE type, int CurDev=-1);

//RGB24 to YUV422 (YcbYcr mode)
//pBmp24 :RGB24 data pointer;
//pOut   :YUV422 pointer
//width  :Image width;
//height :Image height;

/// @brief RGB24转YUV422。
///
/// @param pBmp24：RGB24数据
/// @param pOut：YUV422数据
/// @param width：图像数据宽度
/// @param height：图像数据高度
DTCCM_API void _DTCALL_ RGB24ToYUV422(BYTE* pBmp24, BYTE* pOut, int width, int height, int CurDev=-1);

//RGB24 to YUV444 (Ycbcr )
//pBmp24 :RGB24 data pointer;
//pOut   :YUV422 pointer
//width  :Image width;
//height :Image height;

/// @brief RGB24转YUV444。
///
/// @param pBmp24：RGB24数据
/// @param pOut：YUV422数据
/// @param width：图像数据宽度
/// @param height：图像数据高度
DTCCM_API void _DTCALL_ RGB24ToYUV444(BYTE *pBmp24, BYTE *pOut, int width, int height, int CurDev=-1);

//Raw data to YUV422 (YcbYcr Mode)
//pRaw : RGB raw data pointer;
//width: Image width;
//height:Image height;
//two steps:1. change to RGB24, call USBDataToRGB24()
//          2. change RGB24 to YUV422 data format ,call RGB24ToYUV422()

/// @brief RAW转YUV422（YcbYcr Mode）。
///
/// @param pRaw：RAW数据
/// @param width：图像数据宽度
/// @param height：图像数据高度
DTCCM_API void _DTCALL_ RawToYUV422(BYTE *pRaw, int width, int height, int type, int CurDev=-1);

//verticl flip or not.

/// @brief 开启或关闭图像垂直反向。
///
/// @param bEnable：图像垂直反向使能，为TRUE开启垂直反向，为FALSE关闭垂直反向
DTCCM_API void _DTCALL_ SetVFlip(BOOL bEnable, int CurDev=-1);

//horizontal flip or not...

/// @brief 开启或关闭图像水平反向。
///
/// @param bEnable：图像水平反向使能，为TRUE开启水平反向，为FALSE关闭水平反向
DTCCM_API void _DTCALL_ SetHFlip(BOOL bEnable, int CurDev=-1);

//horizontal flip

/// @brief 水平翻转
/// 
/// @param pData：待翻转的数据
/// @param nWidth：图像数据宽度
/// @param nHeight：图像数据高度
DTCCM_API BOOL _DTCALL_ HFlipBuf(BYTE *pData, LONG nWidth, LONG nHeight, int CurDev=-1);
//vertical flip

/// @brief 垂直翻转
/// 
/// @param inbuf：待翻转的数据
/// @param widthBytes：图像数据宽度
/// @param height：图像数据高度
DTCCM_API BOOL _DTCALL_ VFlipBuf(BYTE *inbuf, UINT widthBytes, UINT height, int CurDev=-1);


//decode data... 
//code data is for usb2.0 bug...,here should decode it before process...
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ BitUnSwizzling(BYTE* pBuffer, ULONG size, int CurDev=-1);
//Edge enhancement...
/// @brief 此函数不支持
DTCCM_API void  _DTCALL_ SetEdge(BYTE THflat, BYTE THedge, double EdgeGain, BOOL EdgeEnable, int CurDev=-1);

//////////////////////////////////////////////////////////////////////////
//color balance control :digital control.
//////////////////////////////////////////////////////////////////////////
//White balance and digital gain control function
// Set the AWB Gain Coefficent.
//default Red,Blue are 1.0f;1.0f.
//enable auto white balance or disable it..


/// @brief 开启或关闭白平衡。
///
/// @param bAWBEn：白平衡使能，为TRUE开启白平衡，为FALSE关闭白平衡
DTCCM_API void _DTCALL_ SetAWB(BOOL bAWBEn, int CurDev=-1);

// check the now AWB state:AWB is ON or OFF.

/// @brief 获取白平衡开启状态。
///
/// @param pAwb：返回的白平衡状态
DTCCM_API BOOL _DTCALL_ GetAWB( int CurDev=-1);

//set the digital gain..

/// @brief 设置RGB数字增益。
///
/// @param fRGain：R增益值
/// @param fGGain：G增益值
/// @param fBGain：B增益值
DTCCM_API void _DTCALL_ SetDigitalGain(int RGain,int GGain,int BGain , int CurDev=-1);


DTCCM_API int _DTCALL_ SetMatrixEnable(BOOL bEnable, int CurDev=-1);

//get the current gain..

/// @brief 获取RGB数字增益。
/// 
/// @param pRGain：返回的R数字增益值
/// @param pGGain：返回的G数字增益值
/// @param pBGain：返回的B数字增益值
DTCCM_API void _DTCALL_ GetDigitalGain(int* pRGain,int* pGGain,int* pBGain , int CurDev=-1);

//////////////////////////////////////////////////////////////////////////
//Set Gamma /Contrast/Saturation parameter...
//////////////////////////////////////////////////////////////////////////
/// @brief 设置GAMMA值。
///
/// @param gamma：设置的GAMMA值
DTCCM_API void _DTCALL_ SetGamma(BYTE gamma, int CurDev=-1);

/// @brief 获取GAMMA设置值。
/// 
/// @retval GAMMA设置值
DTCCM_API BYTE _DTCALL_ GetGamma( int CurDev=-1);

//set the contrast value of the video... only for rgb raw data

/// @brief 设置对比度。
///
/// @param value：设置对比度值
DTCCM_API void _DTCALL_ SetContrast(BYTE value, int CurDev=-1);
//get the contrast value of the video... only for rgb raw data

/// @brief 获取对比度设置值。
///
/// @retval 返回对比度设置值
DTCCM_API BYTE _DTCALL_ GetContrast( int CurDev=-1);

//set the saturation of the video only for rgb raw data

/// @brief 设置饱和度。
///
/// @param value：设置饱和度值
DTCCM_API void _DTCALL_ SetSaturation(BYTE value, int CurDev=-1);

//get the saturation value of the video... only for rgb raw data

/// @brief 获取饱和度设置值。
///
/// @retval 返回饱和度设置值
DTCCM_API BYTE _DTCALL_ GetSaturation( int CurDev=-1);

/// @brief 设置锐度。
///
/// @param iSharpness：设置锐度值
DTCCM_API int _DTCALL_ SetSharpness(int iSharpness, int CurDev=-1);

/// @brief 获取锐度设置值。
///
/// @param pSharpness：返回的锐度设置值
DTCCM_API int _DTCALL_ GetSharpness(int *pSharpness, int CurDev=-1);

/// @brief 设置噪声。
///
/// @param iLevel：设置噪声值
DTCCM_API int _DTCALL_ SetNoiseReduction(int iLevel, int CurDev=-1);

/// @brief 获取设置噪声值。
/// 
/// @param pLevel：返回设置的噪声值
DTCCM_API int _DTCALL_ GetNoiseReduction(int *pLevel, int CurDev=-1);

/// @brief 开启或关闭消死点。
/// 
/// @param bDeadPixCleanEn：为TRUE开启消死点，为FALSE关闭消死点
DTCCM_API int _DTCALL_ SetDeadPixelsClean(BOOL bDeadPixCleanEn,int CurDev=-1);

/// @brief 获取消死点开启或关闭状态。
/// 
/// @param pbDeadPixCleanEn：返回消死点使能值
DTCCM_API int _DTCALL_ GetDeadPixelsClean(BOOL *pbDeadPixCleanEn, int CurDev=-1);

DTCCM_API int _DTCALL_ SetHotCpth(int iHotCpth, int CurDev=-1);

DTCCM_API int _DTCALL_ GetHotCpth(int *pHotCpth, int CurDev=-1);

DTCCM_API int _DTCALL_ SetDeadCpth(int iDeadCpth, int CurDev=-1);

DTCCM_API int _DTCALL_ GetDeadCpth(int *pDeadCpth, int CurDev=-1);

/// @brief 设置raw转rgb算法。
///
/// @param Algrithm：ram转rgb算法设置值,参见宏定义“RAW转RGB算法定义”
DTCCM_API int _DTCALL_ SetRaw2RgbAlgorithm(BYTE Algrithm, int CurDev=-1);


/// @brief 获取raw转rgb算法设置值。
///
/// @param 返回raw转rgb算法设置值
DTCCM_API int _DTCALL_ GetRaw2RgbAlgorithm(BYTE *pAlgrithm, int CurDev=-1);

//get the color matrix correction enable or disable state...
//set the color matrix enable or disbale .

/// @brief 对RAW图像数据进行图像处理(MONO,WB,ColorChange,Gamma,Contrast)。
///
/// @param pRaw：RAW图像数据
/// @param pBmp24：经过图像处理后的数据
/// @param nWidth：图像数据宽度
/// @param nHeight：图像数据高度
DTCCM_API void _DTCALL_ ImageProcess(BYTE *pRaw, BYTE *pBmp24, int nWidth, int nHeight, int CurDev=-1);

/// @brief 对RGB图像数据进行图像处理(MONO,WB,ColorChange,Gamma,Contrast)
/// 
/// @param pBmp24：RGB数据
/// @param width：图像数据宽度
/// @param height：图像数据高度
/// @param type：无用的参数
DTCCM_API void _DTCALL_ ImageISP(BYTE *pBmp24, int width, int height, BYTE type, int CurDev=-1);

//set yuv color matrix...
/// @brief 设置YUV转RGB时的一些系数。
///
///	@param Y=(Y-yoff)*ycoef
///	@param r=Y+(cr-128)*bdif
///	@param g=Y-cbcoef*(cb-128)-crcoef*(cr-128)
///	@param b=Y+(cb-128)*rdif
DTCCM_API void _DTCALL_ setyuvcoefficient (int yoff, float ycoef, float cbcoef, float crcoef,float rdif, float bdif, int CurDev=-1);

/// @brief 此函数不支持
DTCCM_API int _DTCALL_ GetMatrixData(BYTE color,BYTE channel, int CurDev=-1);

/// @brief 设置颜色矩阵。
DTCCM_API void _DTCALL_ SetMatrixData(int R00, int R01, int R02, int G00, int G01, int G02, int B00, int B01, int B02, int CurDev=-1);

/// @brief 此函数不支持
DTCCM_API void _DTCALL_ CopySoftGridData(BYTE *pBmp24, int CurDev=-1);
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ DisplaySoftGrid(BYTE* pData, int CurDev=-1);
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ SetSoftGrid(BOOL sg_en, 
									int lux0, int luy0, int rux0, int ruy0, int ldx0, int ldy0, int rdx0, int rdy0, 
									int corner_h, int corner_v, 
									int ctx0, int cty0, 
									int ct_h, int ct_v, int CurDev=-1);


//init the display handle and the image source width and height and also sensor type.
//hWnd: the display video window handle.
//ImgWidth: image source width;
//ImgHeight:image source height;
//SensorType:Sensor output format,should be 0:10bit raw ;1:8bit raw;2:YUV422 data;3:16bit raw.

/// @brief 初始化显示。
///
/// @param hWnd：显示A通道图像的窗口句柄
/// @param ImgWidth：图像数据宽度
/// @param ImgHeight：图像数据高度
/// @param SensorType：图像数据格式，0：10bit raw；1：8bit raw；2：YUV422 data；3:16bit raw
DTCCM_API void _DTCALL_ InitDisplay(HWND hWnd, USHORT ImgWidth, USHORT ImgHeight, BYTE SensorType, int CurDev=-1);

//display the RGB24 image data.
//pBmp24: RGB24 bmp data buffer pointer.

/// @brief 显示RGB图像数据。
///
/// @param pBmp24：待显示的RGB24格式的数据
DTCCM_API void _DTCALL_ DisplayRGB24(BYTE* pBmp24, int CurDev=-1);

//display the usb data
//two steps:
//1: call USBDataToRGB24() to change the usb data to the RGB24 data format.
//2: call DisplayRGB24() to display it...

/// @brief 显示RAW/YUV图像数据，源数据格式由Init函数中的byImgFormat参数指定。
///
/// @param pData：待显示的图像数据
DTCCM_API void _DTCALL_ bDisplayVideo(BYTE* pData, int CurDev=-1);

DTCCM_API int DisplayVideoEx(BYTE *pData,FrameInfo *pInfo,int CurDev=-1);


/// @brief 此函数不支持
DTCCM_API void _DTCALL_ DisplayRGB24_roi(BYTE* pBmp24, int x0, int y0, int CurDev=-1);
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ bDisplayVideo_roi(BYTE *pData, int x0, int y0, int CurDev=-1);
//////////////////////////////////////////////////////////////////////////
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ VertFlipBuf(BYTE *inbuf, UINT widthBytes, UINT height, int CurDev=-1);
/*
DTCCM_API void _DTCALL_ GetDPSOffset(int *avdd_offset, int *dovdd_offset, int *dvdd_offset, int *afvcc_offset, int *vpp_offset, int CurDev = -1);
DTCCM_API void _DTCALL_ SetDPSOffset(int avdd_offset, int dovdd_offset, int dvdd_offset, int afvcc_offset, int vpp_offset, int CurDev = -1);

DTCCM_API BOOL _DTCALL_ bReadDPSOffsetFromEEPROM(int *avdd_offset, int *dovdd_offset, int *dvdd_offset, int * afvcc_offset, int *vpp_offset, int CurDev = -1);
DTCCM_API BOOL _DTCALL_ bWriteDPSOffsetToEEPROM(int avdd_offset, int dovdd_offset, int dvdd_offset, int afvcc_offset, int vpp_offset, int CurDev = -1);
*/

//for PE300/PE810/PE910
//before close video, first cancel the IO wait operation....
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ CancelIoWait( int CurDev=-1);
/* 获取正确帧/错误帧计数/最后一帧图像的大小 */
/// @brief 此函数不支持
DTCCM_API BOOL _DTCALL_ GetLoadInfo(UINT *FrameOk,UINT *FrameErr,UINT *LastSize, int CurDev=-1);
//malloc bmp and raw data buffer...

/// @brief 动态内存分配
/// 
/// @param pBuf：待分配内存的指针
/// @param Size：分配内存大小
/// 
/// @retval TRUE：动态内存分配成功
/// @retval FALSE：动态内存分配失败
DTCCM_API BOOL _DTCALL_ MallocBuffer(LPBYTE *pBuf, ULONG Size, int CurDev=-1);
//delete bmp and raw data buffer...
/// @brief 释放内存空间
/// 
/// @param Buf：待释放的内存
DTCCM_API void _DTCALL_ DeleteBuffer(LPBYTE Buf, int CurDev=-1);


///////////////////////////////////////////////////////////////////////////////////////////
//set mono or color mode...

/// @brief 开启或关闭MONO模式。
///
/// @param bEnable：MONO模式使能，为TRUE开启MONO模式，为FALSE关闭MONO模式
DTCCM_API void _DTCALL_ SetMonoMode(BOOL bEnable, int CurDev=-1);

//change from color to gray(mono) bmp24

/// @brief 转灰度图像。
/// 
/// @param pData：待转为灰度图像的数据
/// @param nWidth：图像宽度
/// @param nHeight：图像高度
DTCCM_API void _DTCALL_ Gray(BYTE* pData, LONG nWidth, LONG nHeight, int CurDev=-1);

//show cross on image

/// @brief 在图像上画上“十”字线
/// 
/// @param pBmp：图像数据
/// @param width：图像宽度
/// @param height：图像高度
DTCCM_API void _DTCALL_ ShowCrossOnImage(BYTE * pBmp, int width, int height, int CurDev=-1);

//enable cross on or off on the video....

/// @brief 开启或关闭“十”字线。
///
/// @param bEnable：“十”字线使能，为TRUE开启十字线，为FALSE关闭十字线
DTCCM_API void _DTCALL_ SetCrossOn(BOOL bEnable, int CurDev=-1);
/** @} */ // end of group2
/******************************************************************************
SENSOR相关
*******************************************************************************/
/** @defgroup group3 SENSOR相关


* @{

*/
/*
Name :SetSensorMclkEnable
Function : enable or disable mclk....
bOn : 1, mclk running; 0:close..
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/ 

/// @brief 开启或关闭SENSOR输入时钟
/// 
/// @param bOn：为TRUE开启SENSOR输入时钟，为FALSE关闭SENSOR输入时钟
///
/// @retval DT_ERROR_OK：设置SENSOR输入时钟成功
/// @retval DT_ERROR_FAILED：设置SENSOR输入时钟失败
DTCCM_API BYTE _DTCALL_ SetSensorMclkEnable(BOOL bOn, int CurDev=-1);

/*
Name :set sensor MClk in Mhz.
Function : set the mclk frequency....(unit is Mhz),but can use float directly...
like:you can set 33.3Mhz. SetSensorMClk(33.3)
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 设置SENSOR输入时钟值
/// 
/// @param mhz：SENSOR输入时钟值，单位为Mhz
DTCCM_API void _DTCALL_ SetSensorMClk(double mhz, int CurDev=-1);
/*
Name :set sensor MClk in 0.1Mhz.
Function : set the mclk frequency....(unit is 0.1Mhz)
like:you can set 33.3Mhz. SetSensorMClk(333)
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 设置SENSOR输入时钟值
/// 
/// @param hundkhz：SENSOR输入时钟值，单位为100Khz
DTCCM_API void _DTCALL_ SetSensorClock(USHORT hundkhz, int CurDev=-1);
//mclk output setup.. in enum mode...
//can use SetSensorClock directly....
//this is used to be compatible with the old program.
/*
Name :set sensor MClk in enum mode.
enum MCLKOUT
{
MCLK_6M = 0,
MCLK_8M,
MCLK_10M,
MCLK_11M4,
MCLK_12M,
MCLK_12M5,
MCLK_13M5,
MCLK_15M,
MCLK_18M,
MCLK_24M,
MCLK_25M,
MCLK_27M,
MCLK_30M,
MCLK_32M,
MCLK_36M,
MCLK_40M,
MCLK_45M,
MCLK_48M,
MCLK_50M,
MCLK_60M,
MCLK_DEFAULT,
};
Function : set the mclk frequency....(unit is 0.1Mhz)
like:you can set 32M. SetSensorMClk(MCLK_32M)
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ SetFX2Clkout(BYTE mode, int CurDev=-1);

//no use here....
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ SetGPIOInOrOut(BYTE IoFlag, int CurDev=-1);

//Parameter is output GPIO value,return is Get value of the GPIO input..
//this function is used to control 45PIN(Sensor interface) if you set the pin to GPO state....
//return value is no use now...
/*
Function : GPIOInOut :only useful in HS100 and HS200. other demokit is no use....
outvalue: BIT0-BIT3 to control PO0-3(you should define it in the PIN definition)
outvalue.BIT0 ----PO0
outvalue.BIT1 ----PO1
outvalue.BIT2 ----PO2
outvalue.BIT3 ----PO3

CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 此函数不支持
DTCCM_API BYTE _DTCALL_ GPIOInOut(BYTE outvalue, int CurDev=-1); 

//Set Extend IO input or ouput.
//if bit[x] is 1, then IO[X] is output
//if bit[x] is 0, then IO[X] is input...
/*
Function : SetExtendIOFlag
inout: input or output flag. 1:output; 0: input
inout.BIT[x] ----IO[X] 1:output; 0: input
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 设置外部扩展GPIO方向（输入或输出）
/// 
/// @param inout：bit[x]为1, IO[X]为输出；bit[x]为0, IO[X]为输入
DTCCM_API void _DTCALL_ SetExtendIOFlag(BYTE inout, int CurDev=-1);
//write value to extend IO
/*
Function : WriteExtendIO
value: output value.
value.BIT[x] ----IO[X] 1:high level; 0: low level
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 设置外部扩展GPIO电平
/// @param value：BIT[x] ----IO[X] 1：高电平；0：低电平
DTCCM_API void _DTCALL_ WriteExtendIO(BYTE value, int CurDev=-1);
//Read Extend IO level....
/*
Function : ReadExtendIO
return value: input value.
return value.BIT[x] ----IO[X] 1:high level; 0: low level
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 获取外部扩展GPIO的电平。
/// 
/// @retval 返回外部扩展GPIO的电平，BIT[x] ----IO[X] 1：高电平；0：低电平
DTCCM_API BYTE _DTCALL_ ReadExtendIO( int CurDev=-1);

/*
Function : ReadSoftPin
return value: Read GPIO[26:1] value..
return [25:0] is sensor interface GPIO[26:1]'s level state.... 
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 获取柔性接口电平，每BIT对应一个管脚，bit0对应PIN_1。
/// 
/// @retval 返回柔性接口电平
DTCCM_API ULONG _DTCALL_ ReadSoftPin( int CurDev=-1);

//write PO4-1...	
//this IO is in sensor port...
//you should define it in pin definition.. that means this 4 pin is in GPIO26-GPIO1.
//write value to extend IO
/*
Function : WriteIO
value: output value.
value.BIT0 ----PO0
value.BIT1 ----PO1
value.BIT2 ----PO2
value.BIT3 ----PO3
value.BIT[x] ----IO[X] 1:high level; 0: low level
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 设置多个GPIO的电平，Pin中存储的编号值从1开始，1表示GPIO1。
///
/// @param value：BIT[x] ----IO[X] 1：高电平；0：低电平
DTCCM_API void _DTCALL_ WriteIO(BYTE value, int CurDev=-1);

//set GPIO[26:1] pullup or not...
//before search the sensor, should set pullup to 1...
//normally use ,just pull up... 
/*
Function : SetSoftPinPullUp
pullup: pull up or no. 1:pull up; 0: pull low;
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 设置柔性接口是否使能上拉电阻。
///
/// @param pullup：柔性接口上拉使能，bPullup=1使能上拉电阻，bPullup=0关闭上拉电阻
///
/// @retval DT_ERROR_OK：设置成功
/// @retval DT_ERROR_FAILED：设置失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetSoftPinPullUp(BYTE pullup, int CurDev=-1);

//此函数不支持
//this fucntion is no use now,just for kill error report...
DTCCM_API void _DTCALL_ SetVideoDataWidth(BYTE WordWidth, int CurDev=-1); 
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//I2C related function  main for sensor or AF motor driver IC...
//Reset I2C bus and related register..
/*
Function : bResetI2CBus
reset I2C bus
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 复位与Sensor通讯的I2C总线。
///
/// @retval TRUE：复位I2C操作成功
/// @retval FALSE：复位I2C操作失败
DTCCM_API BOOL _DTCALL_ bResetI2CBus( int CurDev=-1);
//b400K = 1, 400K I2C rate...; 0:100K rate...
/*
Function : SetI2CRate
b400k : 1:400K rate... 0:100K rate...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 设置与SENSOR通讯的I2C总线速率，400Kbps或100Kbps。
///
/// @param b400K：b400K=TURE，400Kbps；b400K=FALSE,100Kbps						 
DTCCM_API void _DTCALL_ SetI2CRate(BOOL b400k, int CurDev=-1);

/// @brief 设置与SENSOR通讯的I2C总线速率，范围10Khz-2Mhz。
///
/// @param uKpbs：设置I2C总线速率，范围值为10-2000
///							 
/// @retval DT_ERROR_OK：设置总线速率操作成功
DTCCM_API int _DTCALL_ SetSensorI2cRateEx(UINT uKpbs,int CurDev=-1);

//select I2C channel 0:sensor port; 1:extend port...
//default is sensor port.
/*
Function : SetI2CChannel
chan : 0:Sensor interface I2C channel; 1: extend I2C channel...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
//此函数不支持
DTCCM_API void _DTCALL_ SetI2CChannel(BYTE chan, int CurDev=-1);
//interval time between I2C bytes...
/*
Function : SetI2CInterval
nDly : delay ms between I2C bytes...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 设置I2C通讯ACK超时等待时间。
/// 
/// @param nUsWait：设置ACK超时等待时间，单位us
///
/// @retval DT_ERROR_OK：设置I2C通讯ACK超时等待时间成功
DTCCM_API int _DTCALL_ SetSensorI2cAckWait(UINT uAckWait,int CurDev=-1);

DTCCM_API void _DTCALL_ SetI2CInterval(BYTE nDly, int CurDev=-1);
//
//useful for slave device which will pull scl to low to tell the master it is busy...
/*
Function : SetI2CSclMode
bOutput 1 :outputmode ; 0:tristate mode, pulled up by resistor...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 使能与SENSOR通讯的I2C总线为Rapid模式。
///
/// @param  bRapid=TRUE表示，i2c管脚为高电平时，管脚输出灌电流，=FALSE，I2C管脚为输入状态，借助外部上拉变成高电平
///							 
/// @retval DT_ERROR_OK：设置总线速率操作成功
DTCCM_API void _DTCALL_ SetI2CSclMode(BOOL bOutput, int CurDev=-1);

/// @brief sensor i2c外部上拉电阻选择
/// 
/// @param byPullupResistorSel=PULLUP_RESISTOR_1_5K,表示1.5K；=PULLUP_RESISTOR_4_7K，表示4.7K；=PULLUP_RESISTOR_0_88K表示0.88K
///
/// @retval DT_ERROR_OK：设置成功
/// @retval DT_ERROR_PARAMETER_INVALID：byPullupResistorSel参数无效
/// @retval DT_ERROR_TIME_OUT：通讯超时
DTCCM_API int _DTCALL_ SetSensorI2cPullupResistor(BYTE byPullupResistorSel,int CurDev=-1);


//read i2c register.
/*
Function : bFX2ReadSensor
addr, I2C addr(8bit). don't care r/w, the firmware will adjust when reading.
reg, I2C reg.
value, read I2C value,
enum I2CMODE
{
I2CMODE_NORMAL=0,  //8 bit addr,8 bit value 
I2CMODE_SAMSUNG, //8 bit addr,8 bit value,Stopen
I2CMODE_MICRON,  //8 bit addr,16 bit value,
I2CMODE_STMICRO, //16 bit addr,8 bit value, (eeprom also)
I2CMODE_MICRON2, //16 bit addr,16 bit value,
};
mode, I2C mode, I2CMODE_NORMAL,I2CMODE_SAMSUNG ,I2CMODE_MICRON, I2CMODE_STMICRO,I2CMODE_MICRON2

CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 读SESNOR寄存器,I2C通讯模式byI2cMode的设置值见I2CMODE定义。
///
/// @param addr：从器件地址
/// @param reg：寄存器地址
/// @param value：读到的寄存器的值
/// @param mode：I2C模式
/// @param bNoStop：是否发出I2C的STOP命令，一般情况下默认为FALSE，bNoStop=TRUE表示读的过程不会有I2C的停止命令，bNoStop=FALSE有I2C的停止命令
///
/// @retval 1：读SENSOR寄存器操作成功
/// @retval 0：读SENSOR寄存器操作失败
///
/// @see I2CMODE
DTCCM_API BOOL _DTCALL_ bFX2ReadSensor(USHORT addr, USHORT reg, USHORT* value, BYTE mode=0,int CurDev=-1);
//write i2c register.
/*
Function : bFX2WriteSensor
addr, I2C addr(8bit). don't care r/w, the firmware will adjust when reading.
reg, I2C reg.
value, write I2C value,
enum I2CMODE
{
I2CMODE_NORMAL=0,  //8 bit addr,8 bit value 
I2CMODE_SAMSUNG, //8 bit addr,8 bit value,Stopen
I2CMODE_MICRON,  //8 bit addr,16 bit value,
I2CMODE_STMICRO, //16 bit addr,8 bit value, (eeprom also)
I2CMODE_MICRON2, //16 bit addr,16 bit value,
};
mode, I2C mode, I2CMODE_NORMAL,I2CMODE_SAMSUNG ,I2CMODE_MICRON, I2CMODE_STMICRO,I2CMODE_MICRON2

CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 写SENSOR寄存器,I2C通讯模式byI2cMode的设置值见I2CMODE定义。
/// 
/// @param addr：从器件地址
/// @param reg：寄存器地址
/// @param value：写入寄存器的值
/// @param mode：I2C模式
///
/// @retval 1：写SENSOR寄存器操作成功
/// @retval 0：写SENSOR寄存器操作失败
///
/// @see I2CMODE
DTCCM_API BOOL _DTCALL_ bFX2WriteSensor(USHORT addr, USHORT reg, USHORT value, BYTE mode=0, int CurDev=-1);   

/// @brief 写SENSOR寄存器，支持向多个寄存器写入数据（最大支持16个寄存器）。
///
/// @param uAddr：从器件地址
/// @param byI2cMode：I2C模式
/// @param uRegNum：写入寄存器个数，最大16
/// @param RegAddr[]：寄存器地址数组
/// @param RegData[]：写入寄存器的数据
/// @param RegDelay[]：写完一组寄存器与下一组寄存器之间的延时，单位us
///
/// @retval DT_ERROR_OK：完成写SENSOR寄存器操作成功
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_INVALID：uSize参数无效
/// @retval DT_ERROR_TIME_OUT：通讯超时
/// @retval DT_ERROR_INTERNAL_ERROR：内部错误
DTCCM_API int _DTCALL_ WriteSensorMultiRegsWithDelay(UCHAR uAddr, BYTE byI2cMode, USHORT uRegNum, USHORT RegAddr[], USHORT RegData[],USHORT RegDelay[],int CurDev=-1);


//multi bytes read
//called by user....
//write i2c register.
/*
Function : FX2I2CMultiBytesRead :multi bytes read...
addr, I2C addr(8bit). don't care r/w, the firmware will adjust when reading.
reg, I2C reg.
regsize, 0:no reg;1= BYTE;2:WORD;
ParaList,return bytes data buffer.
Length: data length...

CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 读SENSOR寄存器，支持向一个寄存器读出一个数据块（不超过255字节）。
///
/// @param Addr：从器件地址
/// @param reg：寄存器地址
/// @param regsize：寄存器地址的字节数
/// @param ParaList：读到寄存器的值
/// @param Length：读出寄存器的数据块的字节数（不超过255字节）
/// @param bNoStop：是否发出I2C的STOP命令，一般情况下默认为FALSE，bNoStop=TRUE表示读的过程不会有I2C的停止命令，bNoStop=FALSE有I2C的停止命令
///
/// @retval 1：读SENSOR寄存器块操作成功
/// @retval 0：读SENSOR寄存器块操作失败
DTCCM_API BYTE _DTCALL_ FX2I2CMultiBytesRead(USHORT Addr, USHORT reg, BYTE regsize, BYTE *ParaList, USHORT Length,BOOL bNoStop=FALSE, int CurDev=-1);

//multi bytes write
//called by user....
//write i2c register.
/*
Function : FX2I2CMultiBytesWrite :multi bytes write...
addr, I2C addr(8bit). don't care r/w, the firmware will adjust when reading.
reg, I2C reg.
regsize, 0:no reg;1= BYTE;2:WORD;
ParaList,write bytes data buffer.
Length: data length...

CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 写SENSOR寄存器，支持向一个寄存器写入一个数据块（不超过255字节）。
///
/// @param Addr：从器件地址
/// @param reg：寄存器地址
/// @param regsize：寄存器地址的字节数
/// @param ParaList：写入寄存器的数据块
/// @param Length：写入寄存器的数据块的字节数（不超过255字节(HS300/HS300D/HV910/HV910D一次不能超过253字节)）
///
/// @retval 1：写SENSOR寄存器块操作成功
/// @retval 0：写SENSOR寄存器块操作失败
DTCCM_API BYTE _DTCALL_ FX2I2CMultiBytesWrite(USHORT Addr, USHORT reg, BYTE regsize, BYTE *ParaList, USHORT Length,  int CurDev=-1);

//set sensor PWDN or RESET pin. PWDN is data.0,RESET is data.1
//enable=1 set to data
//enable=0,set t0 ~data.
/*
Function : bSensorEnable :set sensor reset pin and pwdn pin
data: data.1 reset pin; data.0 pwdn pin.
enable: 1: sensor reset pin = data.1; sensor pwdn pin = data.0;
0: sensor reset pin = ~data.1;sensor pwdn pin = ~data.0;   
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 通过Reset,PWDN管脚开启或关闭SENSOR。
///
/// @param byPin：Reset，PWDN，PWDN2
/// @param bEnable：开启或关闭SENSOR
///
/// @retval TRUE：开启或关闭SENSOR操作成功
/// @retval FALSE：开启或关闭SENSOR操作失败
DTCCM_API BOOL _DTCALL_ bSensorEnable(BYTE data, BYTE enable=1, int CurDev=-1); 
//read the version register as Info specified,then check whether is or not.
/*
Function : bSensorEnable :set sensor reset pin and pwdn pin
Info: Sensor information according to the info/dat lib..
bReset: if want to reset the sensor, set to 1,else set to 0.
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 检查插上的SENSOR是不是当前指定的，并且可以同时给SENSOR进行一次复位。
///
/// @param Info：SENSOR信息，参见SensorTab结构体
/// @param bReset：给SENSOR复位
///
/// @retval DT_ERROR_OK：找到SENSOR
/// @retval DT_ERROR_FAILED：没有找到SENSOR
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SensorIsMe(SensorTab *Info, BOOL bReset = TRUE, int CurDev=-1);  
//Dual Camera camera = 1,init the 1st camera; = 2 init the second,other return.
/*
Function : SensorIsMe_Dual :set sensor reset pin and pwdn pin
Info: Sensor information according to the info/dat lib..
Camera: 1: camera #1; 2:Camera #2.
bReset: if want to reset the sensor, set to 1,else set to 0.
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
DTCCM_API int _DTCALL_ SensorIsMe_Dual(SensorTab *Info, int Camera ,BOOL bReset = TRUE, int CurDev=-1);

//Triple Camera, camera = 1,init the 1st camera; = 2 init the second,=3,init the third.
//this is no use now...since no people use three camera....
/*
Function : SensorIsMe_Dual :set sensor reset pin and pwdn pin
Info: Sensor information according to the info/dat lib..
Camera: 1: camera #1; 2:Camera #2.3:Camera 3;
bReset: if want to reset the sensor, set to 1,else set to 0.
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
// 此函数不支持
DTCCM_API int _DTCALL_ SensorIsMe_Triple(SensorTab *Info, int Camera, BOOL bReset = TRUE, int CurDev=-1);
////init the sensor register...
/*
Function : bInitSensor :set sensor reset pin and pwdn pin
Info: Sensor information according to the info/dat lib..
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 初始化SENSOR。
///
/// @param addr：SENSOR器件地址
/// @param ParaList：SENSOR的参数列表
/// @param Length：pParaList的大小
/// @param mode：访问SENSOR的I2C模式，参见枚举类型I2CMODE
///
/// @retval DT_ERROR_OK：初始化SENSOR成功
/// @retval DT_ERROR_FAILED：初始化SENSOR失败
///
/// @see I2CMODE
DTCCM_API BOOL _DTCALL_ bInitSensor(USHORT addr, USHORT* ParaList, USHORT Length, BYTE mode=0, int CurDev=-1); 

DTCCM_API int _DTCALL_ SensorIsMe_Dual2(SensorTab2 *Info, int Camera ,BOOL bReset = TRUE, int CurDev=-1);

/// @brief 初始化SENSOR。
///
/// @param addr：SENSOR器件地址
/// @param ParaList：SENSOR的参数列表
/// @param Length：pParaList的大小
/// @param mode：访问SENSOR的I2C模式，参见枚举类型I2CMODE
///
/// @retval DT_ERROR_OK：初始化SENSOR成功
/// @retval DT_ERROR_FAILED：初始化SENSOR失败
///
/// @see I2CMODE
DTCCM_API BOOL _DTCALL_ bInitSensor2(UINT addr, UINT* ParaList, UINT Length, UINT mode=0, int CurDev=-1); 

//check reset or power down pin ok or not...
/// @brief 检查Reset,PWDN管脚是否对SENSOR起作用。
///
/// @param pInfo：SENSOR的参数信息
/// @param bRstChkEn：使能检查Reset
/// @param bPwdnChkEn：使能检查PWDN
/// @param byChannel：A/B通道选择
/// @param pErrorx：返回的Reset和PWDN的检查信息
///
/// @retval DT_ERROR_OK：操作成功
DTCCM_API BYTE _DTCALL_ CheckRstPwdnPin2(SensorTab2 *Info, BOOL RstChkEn, BOOL PwdnChkEn, BYTE CurCam = 0, int CurDev=-1);

//set sensor port type:MIPI /Parallel/MTK/SPI/TEST...

/// @brief 获取当前设置的图像数据接口类型
///
/// @retval 返回当前设置的图像数据接口类型
DTCCM_API BYTE _DTCALL_ GetSensorOutPort( int CurDev=-1);

//type = 0 : MIPI
//type = 1 : Parallel
//type = 2 : MTK
//type = 3 : SPI
//type = 4 : test

/// @brief 设置SENSOR图像数据接口类型。
///
/// @param type：SENSOR图像数据接口类型，参见枚举类型“SENSOR_PORT”
///
/// @see SENSOR_PORT
DTCCM_API void _DTCALL_ SetSensorOutPort(BYTE type, int CurDev=-1);

/// @brief 复位SENSOR图像数据接口
/// 
/// @param byPort：SENSOR图像数据接口类型，参见枚举类型“SENSOR_PORT”
///
/// @retval DT_ERROR_OK：ROI设置成功
/// @retval DT_ERROR_FAILD：ROI设置失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
///
/// @see SENSOR_PORT
DTCCM_API int _DTCALL_ ResetSensorPort(BYTE byPort,int CurDev=-1);

//for correct mipi receiver, should set this to enable ....
// if disable ,no clk_n or no clk_p can output image...
// 此函数不支持
DTCCM_API void _DTCALL_ CheckMIPIClk(BOOL bEnable, int CurDev=-1);

//using this function to check MIPI siginals whether link to GND or not...
//should set MIPI sensor to LP state or reset state or Pwdn state firstly... 
//BIT7-0 DATA N P
//BIT9-8 CLK N P
// 此函数不支持
DTCCM_API USHORT _DTCALL_ ReadMIPIPortInLPState(int CurDev=-1);

//set mipi clock continous or not...
// this only support some ....
/// @brief 设置MIPI接收非连续时钟
/// 
/// @param bContinous：为TRUE则MIPI接收非连续时钟，为FALSE则MIPI接收连续时钟
DTCCM_API void _DTCALL_ SetMIPIClk(BOOL bContinous, int CurDev=-1);

//20111202 to output long packet information like line flag and crc data...
//when power up ,it is 0.
/// @brief 设置MIPI接收完整数据包输出，包括包头和CRC16校验
/// 
/// @param bEnable：为TRUE设置MIPI接收完整数据包输出，默认为FALSE
DTCCM_API void _DTCALL_ SetMIPILongPacketOut(BOOL bEnable = 0, int CurDev=-1);

/// @brief 设置虚拟通道号
/// 
/// @param uVC：设置接收的图像通道号，0/1/2/3
/// @param bVCFileterEn：使能过滤其他的虚拟通道
///
/// @retval DT_ERROR_OK：设置MIPI接口控制器成功
/// @retval DT_ERROR_FAILED：设置MIPI接口控制器失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetMipiImageVC(UINT uVC, BOOL bVCFilterEn, BYTE byChannel=CHANNEL_A, int CurDev=-1);


/// @brief 过滤MIPI包,指定要过滤的包的ID号及过滤的包个数
///
/// @param PackID[]：设置要过滤的包的ID号
/// @param iCount：过滤的包ID的个数，DMU950最大64
///
/// @retval DT_ERROR_OK：ROI设置成功
/// @retval DT_ERROR_FAILD：ROI设置失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetMipiPacketFilter(int PackID[],int iCount,int CurDev=-1);

/// @brief 获取过滤的包的ID号
///
/// @param PackID[]：返回的过滤的包的ID号
/// @param pCount：返回过滤包的个数
/// @param MaxCount：设置要获取的包ID的最大数，DMU950最大64
///
/// @retval DT_ERROR_OK：ROI设置成功
/// @retval DT_ERROR_FAILD：ROI设置失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ GetMipiPacketFilter(int PackID[], int *pCount, int MaxCount,int CurDev=-1);

//Get MIPI clock phase

/// @brief 获取MIPI接口接收器时钟相位值。
///
/// @retval 返回MIPI接口接收器时钟相位值
DTCCM_API BYTE _DTCALL_ GetMIPIClkPhase(int CurDev=-1);

//Set MIPI clock phase

/// @brief 设置MIPI接口接收器时钟相位。
///
/// @param phase：MIPI接口接收器时钟相位（可以设置的值是0-7）
DTCCM_API void _DTCALL_ SetMIPIClkPhase(BYTE phase, int CurDev=-1);

/// @brief 设置MIPI管脚使能信号
///
/// @param bEnable：为False时MIPI进入HS状态，为TRUE进入LP状态
///
/// @retval DT_ERROR_OK：ROI设置成功
/// @retval DT_ERROR_FAILD：ROI设置失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetMipiEnable(BOOL bEnable, int CurDev=-1);

//read mipi crc count...
//only when crc count is not changed. then the mipi decode is ok...

/// @brief 获取MIPI接口接收器CRC错误计数。
///
/// @retval 返回MIPI接口接收器CRC错误计数值
DTCCM_API USHORT _DTCALL_ ReadMIPICRC(int CurDev=-1);

//get mipi clock in Mhz ...

/// @brief 获取MIPI接口的同步时钟频率。
///
/// @param freq：设置的MIPI接口的同步时钟频率值
///
/// @retval TRUE：获取MIPI接口的同步时钟频率成功
/// @retval FALSE：获取MIPI接口的同步时钟频率失败
DTCCM_API BOOL _DTCALL_ GetMIPIClkFrequency(ULONG *freq, int CurDev = -1);


/// @brief 获取MIPI接口的LOCK状态。
///
/// @param pMipiLockState：获取MIPI接口的LOCK状态，从bit0-bit3依次表示LANE1、LANE2、LANE3、LANE4
///
/// @retval DT\：获取MIPI接口的同步时钟频率成功
/// @retval FALSE：获取MIPI接口的同步时钟频率失败
DTCCM_API int _DTCALL_ GetMipiLockState(DWORD *pMipiLockState,BYTE byChannel,int CurDev = -1);


//set the Pclk and Hsync polarity;
//0 is invert the clk. 1 is postive clk...
//Vsync = -1; auto.default
//Vsync = 0; when 0 output valid hsync 
//Vsync = 1; when 1 output valid hsync 
/// @brief 设置PCLK、Hsync、Vsync极性
DTCCM_API BOOL _DTCALL_ bSetPClkHSync(BOOL bPClk, BOOL bHSync, char Vsync = -1, int CurDev=-1);

//in snap mode, run this will trigger the snap...

/// @brief 启动一次抓拍
DTCCM_API void _DTCALL_ TriggerSnap( int CurDev=-1);

//snap_en : 1: enable the capture image.
//snap_count: the snap count number...

/// @brief 图像抓拍设置，设置使能和一次抓拍的帧数。
/// 
/// @param snap_en：使能捕获图像，为TRUE使能捕获图像，为FALSE关闭
/// @param snap_count：捕获图像的帧数
DTCCM_API void _DTCALL_ SetSnap(BOOL snap_en, BYTE snap_count, int CurDev=-1);

//roi mode...
//roi_x0 roi start x;
//roi_y0 roi stat y;
//roi_hw roi horizontal width
//roi_vw roi vertical height.
//roi_hb roi horizontal blank width
//roi_bw roi_vertical blank height
//roi_hnum roi horizontal total count...
//roi_vnum roi vertical total count....
//type:sensor type...

/// @brief 设置ROI。
///
/// @param roi_x0：起始点水平坐标，单位字节
/// @param roi_y0：起始点垂直坐标，单位字节
/// @param roi_hw：水平方向ROI图像宽度，单位字节
/// @param roi_vw：垂直方向ROI图像高度，单位字节
/// @param roi_hb：水平方向blank宽度，单位字节
/// @param roi_vb：水平方向blank高度，单位字节
/// @param roi_hnum：水平方向ROI数量，单位字节
/// @param roi_vnum：垂直方向ROI数量，单位字节
/// @param type：SENSOR类型
/// @param roi_en：ROI使能
///
/// @retval DT_ERROR_OK：ROI设置成功
/// @retval DT_ERROR_FAILD：ROI设置失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
///
/// @note 该函数中指定宽度和水平位置是以字节为单位，并且保证宽度为4字节的整数倍。
///
/// @image html roi.png
DTCCM_API void _DTCALL_ SetROI(USHORT roi_x0, USHORT roi_y0, USHORT roi_hw,USHORT roi_vw, USHORT roi_hb, USHORT roi_vb, USHORT roi_hnum, USHORT roi_vnum, BYTE type,BOOL roi_en = TRUE, int CurDev=-1);
//set preview width and height and type....
//width :video image width in bytes.
//height:video image height in btes.
//type:sensor type.
//isp_en:use hardware isp or not. 1:enable; 0:disable. HS300 don't have hardware isp,
//bEnMono:use hardware single mono output or not. 1:use; 0:disable;  HS300/HV810/HV910 don't have hardware mono output function.

/// @brief 设置预览图像的宽度、高度、sensor类型等
/// 
/// @param width：图像宽度
/// @param height：图像高度
/// @param type：sensor类型
/// @param isp_en：硬件ISP使能，为1使能，为0关闭，默认关闭（暂时不支持该功能）
/// @param bEnMono：mono模式使能，为1使能，为0关闭，默认关闭（暂时不支持该功能）
/// 
/// @param TRUE:设置成功
/// @param FALSE：设置失败
DTCCM_API BOOL _DTCALL_ SetPreview(USHORT width, USHORT height, BYTE type, BOOL isp_en = FALSE,BOOL bEnMono = FALSE, int CurDev=-1);

//multicam mode
/// @brief 此函数不支持
DTCCM_API BYTE _DTCALL_ GetMultiCamMode( int CurDev=-1);//
//set multicam mode...
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ SetMultiCamMode(BYTE mode, int CurDev=-1);

//these functions only useful in HS100 HS200...
//soft pin definion..
/// @brief 设置柔性接口。
///
/// @param PinList：柔性接口配置定义
DTCCM_API void _DTCALL_ SetFPGAPin(BYTE* PinList, int CurDev=-1);
//set fpga to spi serial mode...
//no use for HS130 HS300 HV810 HV910....
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ SetFPGAToSPI(BOOL bEnable, int CurDev=-1);
//set fpga to mtk serial mode...
//no use for HS130 HS300 HV810 HV910....
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ SetFPGAToMTKSerial(BOOL bEnable, int CurDev=-1);

/// @brief 此函数不支持
DTCCM_API void _DTCALL_ SetFPGAPclkIn(BYTE clk, int CurDev=-1);
//20120901 added....
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ ClearUSBFIFO(int CurDev = -1);

/// @brief I2C读写函数。
///
/// @param rw：为0是写，为1是读
/// @param DevAddr：设备地址
/// @param RegAddr：寄存器地址
/// @param RegAddrSize：寄存器地址大小
/// @param Data：读或者写数据buffer
/// @param DataSize：读或者写数据字节数
/// 
/// @retval TRUE：操作成功
/// @retval FALSE：操作失败
/// 
/// @note 仅PE系列支持
DTCCM_API BOOL  _DTCALL_ I2cRW(UCHAR rw,UCHAR DevAddr,USHORT RegAddr,UCHAR RegAddrSize,UCHAR *Data,UCHAR DataSize, int CurDev = -1);

//check reset or power down pin ok or not...
/// @brief 检查Reset,PWDN管脚是否对SENSOR起作用。
///
/// @param pInfo：SENSOR的参数信息
/// @param bRstChkEn：使能检查Reset
/// @param bPwdnChkEn：使能检查PWDN
/// @param byChannel：A/B通道选择
/// @param pErrorx：返回的Reset和PWDN的检查信息
///
/// @retval DT_ERROR_OK：操作成功
DTCCM_API BYTE _DTCALL_ CheckRstPwdnPin(SensorTab *Info, BOOL RstChkEn, BOOL PwdnChkEn, BYTE CurCam = 0, int CurDev=-1);


/****************************************************************************************
SPI总线
*****************************************************************************************/

/// @brief uPort:SPI控制器选择
/// 
/// @brief pSPIConfig:SPI配置结构体，参见imagekit.h
/// 
/// @retval DT_ERROR_OK：SPI配置成功
/// @retval DT_ERROR_FAILD：SPI配置失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ MasterSpiConfig(UCHAR uPort,MasterSpiConfig_t *pSPIConfig,int CurDev=-1);

/// @brief SPI控制器接口，支持三线或四线通讯，支持单字节传输和多字节连续传输，支持读写要求。
///
/// @param bStart：为True片选信号拉低，为False片选信号不拉低
/// @param bStop：为True片选信号拉高，为False片选信号不拉高
/// @param bMsb：为True是高位先出，为False是低位先出
/// @param TxData：写入的数据BUFFER
/// @param RxData：读回的数据BUFFER
/// @param TxLen：写入数据的大小，字节数
/// @param RxLen：读取数据的大小，字节数

/// @retval DT_ERROR_OK：操作成功
/// @retval DT_ERROR_FAILD：操作失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SensorSpiRW(BOOL bStart,BOOL bStop,BOOL bMsb,UCHAR *TxData,UCHAR *RxData,UCHAR TxLen,UCHAR RxLen,int CurDev=-1);

/// @brief SPI控制器使能、速度、模式设置（UT300/UV910），注意：在操作SensorSpiRW之前必须使能SPI总线，如果不操作必须关闭SPI总线，以免影响SENSOR i2c的访问。
/// 
/// @param bEnable：为True是开启SPI总线，为False是关闭SPI总线
/// @param iRate：为True是500Kbps 为False是250Kbps
/// @param bType：三线或四线通讯选择，为False是三线SPI通讯，为True是四线SPI通讯
///
/// @retval DT_ERROR_OK：操作成功
///
/// @note 在操作SensorSpiRW之前必须使能SPI总线，如果不操作必须关闭SPI总线，以免影响SENSOR i2c的访问
DTCCM_API int _DTCALL_ SensorSpiInit(BOOL bEnable, int iRate, BOOL bType, int CurDev=-1);
/****************************************************************************************
柔性接口时钟输出
*****************************************************************************************/
/// @brief 柔性接口可调节时钟，支持柔性管脚输出0-200Khz可调节时钟
///
/// @param uHz：输出时钟大小，单位Hz，0-200Khz可调节
/// @param bOnOff：可调节时钟输出使能，True为输出使能，False为关闭输出
///
/// @retval DT_ERROR_OK：设置时钟输出成功
/// @retval DT_ERROR_FAILD：设置时钟输出失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetSoftPinAdjClk1(UINT uHz,BOOL bOnOff,int CurDev=-1);

/// @brief 柔性接口可调节时钟，支持柔性管脚输出0-18Mhz可调节时钟
/// 
/// @param uHundkHz：设置输出时钟大小，单位100KHz，0-18Mhz可调节
/// @param bOnOff：可调节时钟输出使能，True为输出使能，False为关闭输出
///
/// @retval DT_ERROR_OK：设置时钟输出成功
/// @retval DT_ERROR_FAILD：设置时钟输出失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetSoftPinAdjClk2(USHORT uHundkHz,BOOL bOnOff,int CurDev=-1);
/** @} */ // end of group3
/******************************************************************************
图像数据采集相关
******************************************************************************/

/** @defgroup group4 图像数据采集相关


* @{

*/
//////////////////////////////////////////////////////////////////////////
// USB function.
//////////////////////////////////////////////////////////////////////////

/*
Name :FX2OpenVideo
Function : set demokit to start to receive the video data from the sensor.
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 开启图像数据采集。
DTCCM_API void _DTCALL_ FX2OpenVideo( int CurDev=-1);  
/*
Name :FX2CloseVideo
Function : set demokit to stop to receive the video data from the sensor.
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/    
//set FX2 to stop the video data from sensor..

/// @brief 关闭图像数据采集。
DTCCM_API void _DTCALL_ FX2CloseVideo( int CurDev=-1);

/// @brief 校准sensor接收，建议openvideo之后调用，校准成功再进行抓帧操作
/// 
/// @param uTimeOut：校准超时时间设置，单位ms
/// 
/// @retval DT_ERROR_OK：校准成功，可以采集图像
/// @retval DT_ERROR_TIME_OUT：校准超时
DTCCM_API int _DTCALL_ CalibrateSensorPort(ULONG uTimeOut,int CurDev=-1);


/// @brief 设置采集一帧数据量
/// 
/// @param uGrabFrameSize：设置一帧的数据量大小，单位字节
DTCCM_API int _DTCALL_ SetGrabFrameSize(ULONG uGrabFrameSize,int CurDev=-1);


/// @brief 设置采集数据超时，单位：ms，如果该事件内没有采集到图像数据，GrabFrame函数将返回超时错误。
///
/// @param uTimeOut：采集数据超时时间设置，单位ms
DTCCM_API int _DTCALL_ SetGrabTimeout(ULONG uTimeOut,int CurDev=-1);

/// @brief 设置grabframe模式
///
/// @param byMode：ISP处理模式，0为normal，1为S2DFAST，2为S2DFAST GPU
DTCCM_API int _DTCALL_ SetImageProcessMode(BYTE byMode,int CurDev=-1);

/// @brief S2DFAST模式抓取数据，得到的是RGB数据
///
/// @param pBuf: 帧buffer
/// 
/// retval:DT_ERROR_FAILED:抓取失败，得到错误帧
/// retval:DT_ERROR_TIMEOUT:抓取超时，没有抓到数据
DTCCM_API int _DTCALL_ S2DfastDirectGrabFrame(BYTE **pBuf,int CurDev=-1);

DTCCM_API int _DTCALL_ S2DfastReleaseBuffer(BYTE *pBuf,int CurDev=-1);


/// @brief 配置FrameBuffer
/// 
/// @param pConfig：FrameBuffer配置结构体,该结构体说明参见imagekit.h头文件
DTCCM_API int _DTCALL_ SetFrameBufferConfig(FrameBufferConfig *pConfig,int CurDev=-1);

/// @brief 获取FrameBuffer的配置信息
/// 
/// @param pConfig：FrameBuffer配置结构体,该结构体说明参见imagekit.h头文件
DTCCM_API int _DTCALL_ GetFrameBufferConfig(FrameBufferConfig *pConfig,int CurDev=-1);

/// @brief 设置时间点，设置成功后，设备的时间戳值将从该时间点开始计时（单位us）
/// 
/// @param uTimeStamp: 时间点
/// 
/// @retval DT_ERROR_OK：设置成功
/// @retval DT_ERROR_FAILD：设置失败 
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetTimerClock(double uTime, int CurDev=-1);

/// @brief 获取时间戳(单位us)
/// 
/// @param pTimeStamp: 时间戳值
/// 
/// @retval DT_ERROR_OK：设置成功
/// @retval DT_ERROR_FAILD：设置失败 
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ GetTimeStamp(double *pTimeStamp, int CurDev=-1);

/// @brief 清空测试盒的缓存
/// 
/// @retval DT_ERROR_OK：清空成功
/// @retval DT_ERROR_FAILD：清空失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ ResetFrameBuffer(int CurDev=-1);

/// @brief 采集一帧图像，并且返回帧的一些信息。
///
/// @param pInBuffer：采集图像BUFFER
/// @param uBufferSize：采集图像BUFFER大小，单位字节
/// @param pGrabSize：实际抓取的图像数据大小，单位字节
/// @param pInfo：返回的图像数据信息
///
/// @retval DT_ERROR_OK：采集一帧图像成功
/// @retval DT_ERROR_FAILD：采集一帧图像失败，可能不是完整的一帧图像数据
/// @retval DT_ERROR_TIME_OUT：采集超时
/// @retval DT_ERROR_INTERNAL_ERROR：内部错误 
/// 
/// @note 调用该函数之前，请先根据图像大小获取到足够大的缓存区用于装载图像数据。\n
/// 同时，缓存区的大小也需要作为参数传入到GrabFrameEx函数，以防止异常情况下导致的内存操作越界问题。 
DTCCM_API int _DTCALL_ GrabFrameEx(BYTE *pInBuffer, ULONG uBufferSize,ULONG *pGrabSize,FrameInfo *pInfo,int CurDev=-1);

/*
Name :bGrabFrame
Function : capture the image data from the defined device...,
inbuffer : the image data buffer.
buffersize: data size to capture..
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 采集一帧图像。
///
/// @param inbuffer：采集图像BUFFER
/// @param buffersize：采集图像BUFFER大小，单位字节
///
/// @retval 1：采集一帧图像成功
/// @retval 0：采集一帧图像失败，可能不是完整的一帧图像数据
/// @retval -1：采集超时或者内部错误
/// 
/// @note 调用该函数之前，请先根据图像大小获取到足够大的缓存区用于装载图像数据。\n
/// 同时，缓存区的大小也需要作为参数传入到GrabFrame函数，以防止异常情况下导致的内存操作越界问题。 

DTCCM_API int _DTCALL_ bGrabFrame(BYTE* inbuffer, ULONG buffersize, int CurDev=-1);


//set async read wait time....
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ SetWaitTime(ULONG tmS, BOOL WaitEn = FALSE, int CurDev=-1);

//20111223 added...
//if transfer failed, can call this to ask usb to send the data from usb buffer to pc... 
/// @brief 重发上一帧图像
DTCCM_API void _DTCALL_ ReSendImage( int CurDev=-1);
//get the sensor ouput frame count....
/// @brief 此函数不支持
DTCCM_API WORD _DTCALL_ GetSensorVideoFrameCount(int CurDev = -1);

//get the image data width in the video in bytes...
/// @brief 返回图像数据宽度。
///
/// @retval 返回图像数据宽度
DTCCM_API WORD _DTCALL_ GetSensorVideoWidth( int CurDev=-1);

//get the image data height in the video in bytes...

/// @brief 返回图像数据高度。
///
/// @retval 返回图像数据高度
DTCCM_API WORD _DTCALL_ GetSensorVideoHeight( int CurDev=-1);

/// @brief 返回实际抓取图像数据的大小（单位字节）。
/// 
/// @param pGrabSize：返回实际抓取图像数据大小
DTCCM_API int _DTCALL_ CalculateGrabSize(ULONG *pGrabSize,int CurDev=-1);

//get the bmp buffer pointer....
/// @brief 返回Bmp数据buffer。
DTCCM_API BYTE* _DTCALL_ GetBmpBuffer( int CurDev=-1);
/** @} */ // end of group4
/******************************************************************************
电源管理单元相关
******************************************************************************/
/** @defgroup group5 电源管理单元相关


* @{

*/
/*
*  对应位为1 过流，为0无过流
*  OverBuf[0].0位是AVDD;   OverBuf[0].1位是DOVDD;  OverBuf[0].2位是DVDD；
*  OverBuf[0].3位是AFVCC;  OverBuf[0].4位是VPP;
*  OverBuf[0]是当前过流值，
*  OverBuf[1]是当前过流值，无过流时保持上次值
*  OverBuf[2]是OverBuf[1]上一次过流值，
OVER-C1=AVDD，OVER-C2=DOVDD，OVER-C3=DVDD，OVER-C4=AFVCC，OVER-C5=VPP	
*/

/// @brief 获取电流过流。
/// 
/// @param OverBuf：对应位为1过流，为0无过流；
///					OverBuf[0].0位是AVDD；OverBuf[0].1位是DOVDD；OverBuf[0].2位是DVDD；\n
///					OverBuf[0].3位是AFVCC；OverBuf[0].4位是VPP；\n
///					OverBuf[0]是当前过流值；\n
///					OverBuf[1]是当前过流值，无过流时保持上次值；\n
///					OverBuf[2]是OverBuf[1]上一次过流值；\n
///					OVER-C1=AVDD，OVER-C2=DOVDD，OVER-C3=DVDD，OVER-C4=AFVCC，OVER-C5=VPP
///
/// @retval DT_ERROR_OK：获取成功
/// @retval DT_ERROR_FAILD：获取失败
/// 
/// @note 仅PE系列和HS系列支持该函数
DTCCM_API int _DTCALL_ GetCurrentOverload(BYTE *OverBuf, int CurDev=-1);

//set device beep time and beep count...

/// @brief 设置蜂鸣器。
///
/// @param beeptime：蜂鸣器鸣叫时间，单位为mS
/// @param beepcount：蜂鸣器鸣叫次数
DTCCM_API void _DTCALL_ SetAlarm(USHORT beeptime, BYTE beepcount, int CurDev=-1);	
//PMU....
/// @brief 此函数不支持
DTCCM_API int _DTCALL_ ResetPMU( int CurDev=-1);

//set PMU range.... AVDD, DOVDD, DVDD, AFVCC, VPP...

/// @brief 设置电源量程
//#define PMU1_1						0x11	0.1mA
//#define PMU1_2						0x10	1uA
//#define PMU1_3						0x12	0.01uA
//#define PMU2_1						0x21
//#define PMU2_2						0x20
//#define PMU2_3						0x22
//#define PMU3_1						0x31
//#define PMU3_2						0x30
//#define PMU3_3						0x32
//#define PMU4_1						0x41
//#define PMU4_2						0x40
//#define PMU4_3						0X42
//#define PMU5_1						0x51
//#define PMU5_2						0x50
//#define PMU5_3						0X52

DTCCM_API BYTE _DTCALL_ SetPMURange(BYTE pmu1, BYTE pmu2, BYTE pmu3, BYTE pmu4, BYTE pmu5, int CurDev=-1);
//should set to 0,if get current
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ SetPMUSelfTestRange(BYTE range, int CurDev=-1);
//Enable PMU or not....
/// @brief 此函数不支持
DTCCM_API BYTE _DTCALL_ SetPMUOnOff(BOOL bOn, int CurDev=-1);

//get the Current Value.
/// @brief 此函数不支持
DTCCM_API int _DTCALL_ GetPMUData(BYTE *pBuf, BYTE length, int CurDev=-1);

/// @brief PMU复位，有可能导致系统电源重启，所有模块重新上电。
///
/// @retval DT_ERROR_OK：PMU复位成功
/// @retval DT_ERROR_FAILD：PMU复位失败
/// @retval DT_ERROR_INTERNAL_ERROR：内部错误
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ PmuReset(int CurDev=-1);

/// @brief 获取系统电源状态(电压，电流)。
///
/// @param Power：系统电源类型，参见枚举类型“SYS_POWER”
/// @param Voltage：获取的系统电压值，单位mV
/// @param Current：获取的系统电流值，单位mA
/// @param iCount：要获取的系统电源的路数
///
/// @retval DT_ERROR_OK：获取系统电源状态成功
///	@retval DT_ERROR_COMM_ERROR：通讯错误
///
/// @see SYS_POWER
/// 
/// @note 该函数仅UV910/DTLC2/UH910/UH920/UF920/PE350/PE950支持。
DTCCM_API int _DTCALL_ PmuGetSysPowerVA(SYS_POWER Power[],int Voltage[],int Current[],int iCount,int CurDev=-1);

/// @brief 设置电源模式。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param Mode：电源模式，参见枚举类型“POWER_MODE”
/// @param iCount：电源路数
/// 
/// @retval DT_ERROR_OK：设置电源模式成功
/// @retval DT_ERROR_FAILD：设置电源模式失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
/// @see POWER_MODE
/// 
/// @note 该函数仅UV910/DTLC2/UH910/UH920/UF920/PE350/PE950支持。
DTCCM_API int _DTCALL_ PmuSetMode(SENSOR_POWER Power[],POWER_MODE Mode[],int iCount,int CurDev=-1);

/// @brief 设置电源电压。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param Voltage：设置的电源电压值，单位mV
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：设置电源电压成功
/// @retval DT_ERROR_FAILD：设置电源电压失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
DTCCM_API int _DTCALL_ PmuSetVoltage(SENSOR_POWER Power[],int Voltage[],int iCount,int CurDev=-1);

/// @brief 设置电源电流量程。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param Range：电源电流量程，参见枚举类型“CURRENT_RANGE”
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：设置电源电流量程成功
/// @retval DT_ERROR_FAILD：设置电源电流量程失败
///
/// @see SENSOR_POWER
/// @see CURRENT_RANGE
///
/// @note 该函数仅UV910/DTLC2/UH910/UH920/UF920/PE350/PE950支持。
DTCCM_API int _DTCALL_ PmuSetCurrentRange(SENSOR_POWER Power[],CURRENT_RANGE Range[],int iCount,int CurDev=-1);

/// @brief 设置电压上升沿，设定值(Rise)单位:mV/mS。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param Rise：电压上升沿值，单位:mV/mS
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：设置电压上升沿成功
/// @retval DT_ERROR_FAILD：设置电压上升沿失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
/// 
/// @note 该函数仅UV910/DTLC2/UH910/UH920/UF920/PE350/PE950支持。
DTCCM_API int _DTCALL_ PmuSetRise(SENSOR_POWER Power[],int Rise[],int iCount,int CurDev=-1);



/// @brief 设置电源开关状态。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param OnOff：设置电源开关状态，TRUE为开启，FALSE为关闭
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：设置电源开关状态成功
/// @retval DT_ERROR_FAILD：设置电源开关状态失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
DTCCM_API int _DTCALL_ PmuSetOnOff(SENSOR_POWER Power[],BOOL OnOff[],int iCount,int CurDev=-1);

/// @brief 获取电源开关状态。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param OnOff：获取电源开关状态，TRUE为开启，FALSE为关闭
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：获取电源开关状态成功
/// @retval DT_ERROR_FAILD：获取电源开关状态失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
DTCCM_API int _DTCALL_ PmuGetOnOff(SENSOR_POWER Power[],BOOL OnOff[],int iCount,int CurDev=-1);

/// @brief 设置OCP延时(过流时间的累加),设定值(Delay)单位:mS。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param Delay：OCP延时设定值
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：设置OCP延时成功
/// @retval DT_ERROR_FAILD：设置OCP延时失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
/// 
/// @note 该函数仅UV910/DTLC2/UH910/UH920/UF920/PE350/PE950支持。
DTCCM_API int _DTCALL_ PmuSetOcpDelay(SENSOR_POWER Power[],int Delay[],int iCount,int CurDev=-1);

/// @brief 设置OCP关断时间(被判断过流保护后，关断一段时间),设定值(Hold)单位:mS。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param Hold：OCP关断时间
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：设置OCP关断时间成功
/// @retval DT_ERROR_FAILD：设置OCP关断时间失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
/// 
/// @note 该函数仅UV910/DTLC2/UH910/UH920/UF920/PE350/PE950支持。
DTCCM_API int _DTCALL_ PmuSetOcpHold(SENSOR_POWER Power[],int Hold[],int iCount,int CurDev=-1);

/// @brief 获取过流状态,返回信息(State)TRUE:过流保护,FALSE:正常。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param State：获取到的过流状态
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：设置OCP关断时间成功
/// @retval DT_ERROR_FAILD：设置OCP关断时间失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
/// 
/// @note 该函数仅UV910/DTLC2/UH910/UH920/UF920/PE350/PE950支持。
DTCCM_API int _DTCALL_ PmuGetOcpState(SENSOR_POWER Power[],BOOL State[],int iCount,int CurDev=-1);


//获取电源电流，用于代替GetPMUData函数，GetPMUData函数不再有效
//数值(Current)单位:nA

/// @brief 获取电源电流。
///
/// @param Current：电流值,单位nA
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：获取电源电流成功
/// @retval DT_ERROR_FAILD：获取电源电流失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @note 该函数仅PE910/PE910D/HV910/HV910D/UV910/DTLC2/UH910支持。
DTCCM_API int _DTCALL_ PmuGetCurrent(int Current[],int iCount=5,int CurDev=-1);

/// @brief 设置过流保护的电流限制,设定值(CurrentLimit)单位:mA。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param CurrentLimit：设置过流保护的电流限制值，单位mA
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：设置过流保护的电流限制成功
/// @retval DT_ERROR_FAILD：设置过流保护的电流限制失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
DTCCM_API int _DTCALL_ PmuSetOcpCurrentLimit(SENSOR_POWER Power[],int CurrentLimit[],int iCount,int CurDev=-1);

/// @brief 设置电流采集速度，设定值(SampleSpeed)10-200。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param SampleSpeed：电流采集速度，范围10-200
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：设置电流采集速度成功
/// @retval DT_ERROR_FAILD：设置电流采集速度失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
/// 
/// @note 该函数仅UV910/DTLC2/UH910/UH920/UF920/PE350/PE950支持。
DTCCM_API int _DTCALL_ PmuSetSampleSpeed(SENSOR_POWER Power[],int SampleSpeed[],int iCount,int CurDev=-1);

//set sensor current limit. max_100ma = 1, maxium current is 100mA. else 300mA.
//if the current exceed the limit, the system will beep ...

/// @brief 设置限流值
///
/// @param max_100ma：为1最大限流值为100mA，为0最大限流值为300mA
DTCCM_API void _DTCALL_ SetSensorCurrentLimit(BYTE max_100ma, int CurDev=-1);

//set sensor working voltage.. 
//2011 05 14 added afvcc settings.
//default afvcc is 2.8V...

/// @brief 设置电压值
/// 
/// @param avdd：AVDD电压设置值，参见宏定义“SENSOR电源电压选择定义”
/// @param dovdd：DOVDD电压设置值，参见宏定义“SENSOR电源电压选择定义”
/// @param dvdd：DVDD电压设置值，参见宏定义“SENSOR电源电压选择定义”
/// @param afvcc：AFVCC电压设置值，默认设置为2.8V，参见宏定义“SENSOR电源电压选择定义”
DTCCM_API void _DTCALL_ SetSensorVoltage(BYTE avdd, BYTE dovdd, BYTE dvdd, BYTE afvcc=AFVCC_28, int CurDev=-1);

//Sensor Power (AVDD DOVDD DVDD AFVCC) / VPP on or off....

/// @brief 设置电源电压开关。
///
/// @param bSensorPowerOn：AVDD、DOVDD、DVDD、AFVCC电压开关，为TRUE全部开启，为FALSE全部关闭
/// @param bVPPOn：VPP电压开关，为TRUE开启，为FALSE关闭
DTCCM_API BYTE _DTCALL_ SetSensorPowerOnOff(BOOL bSensorPowerOn, BOOL bVPPOn = 0, int CurDev=-1);

//sensor power on or off...
//BYTE SetSensorPowerOnOff(BOOL bOn, int CurDev=-1);
//VPP voltage 0.5-9V

/// @brief 设置VPP电压值。
///
/// @param vol：VPP电压设置值，单位V
/// 
/// @retval 0：设置失败
/// @retval 1：设置成功
DTCCM_API BYTE _DTCALL_ SetSensorVPPVoltage(double vol, int CurDev=-1);

////only useful in PE320/PE820/PE920 voltage setup all at one time
//unit is mv.
//if avdd set to 3.3V, here should set avdd parameter to 3300(mv).

/// @brief 设置电压值。
/// 
/// @param avdd：AVDD设置值，单位mV
/// @param dovdd：DOVDD设置值，单位mV
/// @param dvdd：DVDD设置值，单位mV
/// @param afvcc：AFVCC设置值，单位mV
/// @param vpp：VPP设置值,单位mV
DTCCM_API void _DTCALL_ SetDPS(double avdd, double dovdd, double dvdd, double afvcc, double vpp, int CurDev=-1);

//only useful in PE320/PE820/PE920 voltage setup in one channel
//unit is mv.
//channel 0 : avdd; (0-3300mv)
//channel 1 : dovdd;(0-3300mv)
//channel 2 : dvdd; (0-3300mv)
//channel 3 : afvcc;(0-3300mv)
//channel 4 : vpp;  (0-9000mv)
//channel 5 : bak1  (0-3300mv) 
//channel 6 : bak2  (0-3300mv)

/// @brief 设置单个通道电压值。
/// 
/// @param channel：设置通道，0为AVDD，1为DOVDD，2为DVDD，3为AFVCC，4为VPP
/// @param mv：设置的电压值，单位mV
DTCCM_API BOOL _DTCALL_ SetDPSInChannel(BYTE channel, double mv, int CurDev=-1);

//only useful in PE320/PE820/PE920 setup power switch all at once....
//avdd_sw 1:avdd on; 0:avdd off
//dovdd_sw 1:dovdd on; 0: dovdd off
//dvdd_sw 1:dvdd on; 0:dvdd off
//afvcc_sw 1:afvcc on; 0: afvccoff.
//vpp_sw 1:vpp on; 0:vpp off

/// @brief 设置电源开关状态。
/// 
/// @param avdd_sw：AVDD开关，为TRUE开启，为FALSE关闭
/// @param dovdd_sw：DOVDD开关，为TRUE开启，为FALSE关闭
/// @param dvdd_sw：DVDD开关，为TRUE开启，为FALSE关闭
/// @param afvcc_sw：AFVCC开关，为TRUE开启，为FALSE关闭
/// @param vpp_sw：VPP开关，为TRUE开启，为FALSE关闭
DTCCM_API void _DTCALL_ SetDPSOnOff(BOOL avdd_sw, BOOL dovdd_sw, BOOL dvdd_sw, BOOL afvcc_sw, BOOL vpp_sw, int CurDev=-1);

//set receiver buffer voltage.
//this should set to same as DOVDD normally, but you can set it to your need...
//this can be used to remove noise problem....
//跟随DOVDD
/// @brief 此函数不支持
DTCCM_API void _DTCALL_ SetBufIOVoltage(BYTE bufio, int CurDev=-1);

/// @brief 获取电源电压，如果能获取检测到的，尽量使用检测到的数据，否则返回电压设置值。
///
/// @param Power：电源类型，参见枚举类型“SENSOR_POWER”
/// @param Voltage：获取的电源电压值，单位mV
/// @param iCount：电源路数
///
/// @retval DT_ERROR_OK：设置电源电压成功
/// @retval DT_ERROR_FAILD：设置电源电压失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND：参数超出了范围
///
/// @see SENSOR_POWER
DTCCM_API int _DTCALL_ PmuGetVoltage(SENSOR_POWER Power[],int Voltage[],int iCount,int CurDev=-1);
/** @} */ // end of group5

/******************************************************************************
初始化，控制相关
******************************************************************************/
/** @defgroup group6 初始化控制相关


* @{

*/
/// @brief 枚举设备，获得设备名及设备数。
///
/// @param DeviceName：枚举的设备名
/// @param iDeviceNumMax：枚举设备的最大个数
/// @param pDeviceNum：枚举的设备数
///
/// @retval DT_ERROR_OK：枚举操作成功
/// @retval DT_ERROR_FAILED:枚举操作失败
/// @retval DT_ERROR_INTERNAL_ERROR:内部错误
///
/// @note 获取的设备名称字符串需要用户程序调用GlobalFree()逐个释放。
DTCCM_API int _DTCALL_ EnumerateDevice(char *DeviceName[],int iDeviceNumMax,int *pDeviceNum);

/// @brief 打开设备，只有打开成功后，设备才能操作;设备对象跟给的ID对应起来iDevID=1 则创建设备对象m_device[1]，iDevID=0 则创建设备对象m_device[0]；
///
/// @param pszDeviceName：打开设备的名称
/// @param pDevID：返回打开设备的ID号
///
/// @retval DT_ERROR_OK：打开设备成功
/// @retval DT_ERROR_FAILD：打开设备失败
/// @retval DT_ERROR_INTERNAL_ERROR：内部错误
/// @retval DT_ERROR_PARAMETER_INVALID：参数无效
DTCCM_API int _DTCALL_ OpenDevice(const char *pszDeviceName,int *pDevID,int CurDev=0);

/****************************************
Name：bOpenDevice
Function: Open the device instance for use
Parameters：CurDev current Device Number.default is -1.means to notify the sdk to use default demokit.
            CurDev = -1, Default
			CurDev = 0, DemoKit #1
			CurDev = 1, DemoKit #2
before you control the usb device ,you should create this.then the link to usb created....
****************************************/

/// @brief 创建设备对象
/// 
/// @retval 1：创建成功
/// @retval 0：创建失败
DTCCM_API int _DTCALL_ bCreatDeviceObject( int CurDev=-1);




/****************************************
Name：bDeleteDevice
Function: delete the device instance if you don't use
Parameters：CurDev
CurDev = -1, Default
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
before you exit the control of usb device, you should delete this 
****************************************/

/// @brief 删除设备对象
DTCCM_API void _DTCALL_ bDeleteDeviceObject( int CurDev=-1);

/// @brief 重新连接设备，usb3.0设备有效
///
/// @retval DT_ERROR_OK：打开设备成功
/// @retval DT_ERROR_FAILD：打开设备失败
DTCCM_API int _DTCALL_ DeviceReset(int CurDev=-1);

//////////////////////////////////////////////////////////////////////////
/*
Name :SetCurrentDeviceObject
Function : Set The default Device to your need.
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
//if have two demokit. just set current device to your need...

/// @brief 设置需要的设备对象（通过ID号对应）
DTCCM_API void _DTCALL_ SetCurrentDeviceObject( int CurDev = 0);

//////////////////////////////////////////////////////////////////////////
//check the current device is open or not.....
/*
Name :bCheckDeviceObject
Function : Check the current Device is created or not...
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 检查当前设备是否打开
/// 
/// @retval TRUE：当前设备打开
/// @retval FALSE：当前设备没有打开
DTCCM_API BOOL _DTCALL_ bCheckDeviceObject( int CurDev=-1);

//////////////////////////////////////////////////////////////////////////
//to check whether the demo board is which we needed or or not.if ok,you can init it...
/*
Name :bFX2IsMe
Function : check the demokit is online or what we need...,
bInit = 1,if it is what we need,init the device.
bInit = 0,just only check and return.
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 检查设备是否存在并且是否初始化设备
/// 
/// @param bInit：为TRUE检查设备是否存在并且初始化设备，为False仅检查设备是否存在
/// 
/// @retval TRUE：操作成功
/// @retval FALSE：操作失败
DTCCM_API BOOL _DTCALL_ bFX2IsMe(BOOL bInit = TRUE, int CurDev=-1);


//get key info...
/*
Function : GetKey
return the key input...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 获取设备上按钮的按键值。
///
/// @retval 返回设备上按钮的按键值
DTCCM_API WORD _DTCALL_ GetKey( int CurDev=-1);     
/** @} */ // end of group6

/******************************************************************************
AF相关
******************************************************************************/

/** @defgroup group7 AF相关


* @{

*/

//AF write /read.
//value:read value
//return TRUE:success;FALSE:fail
//this function is not working properly now.don't call this..
/// @brief 此函数不支持
DTCCM_API BOOL _DTCALL_ bReadDAValue(USHORT addr, USHORT* value, int CurDev=-1);
//return TRUE:success;FALSE:fail
/*
Function : bWriteDAValue :set sensor reset pin and pwdn pin
addr:motor AF IC I2C addr.
value: motor AF IC position value;
mode: motor AF IC mode...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 此函数不支持
DTCCM_API BOOL _DTCALL_ bWriteDAValue(USHORT addr, USHORT value, BYTE mode = 0, int CurDev=-1);

//get the AD value for Current /Voltage Test...
//get the AF device I2C address 8bit
/*
Function : GetAFAddr :
return motor AF IC address.
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 获取当前AF芯片的器件地址。
///
/// @retval 返回当前AF芯片的器件地址
DTCCM_API USHORT _DTCALL_ GetAFAddr( int CurDev=-1);

//find the AF device use 0x18 or 0x1c.
/*
Function : bFindAFDevice :auto search the motor AF IC 
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 搜索AF器件中的D/A芯片。
///
/// @retval TRUE：搜索AF器件中的D/A芯片成功
/// @retval FALSE：搜索AF器件中的D/A芯片失败
DTCCM_API BOOL _DTCALL_ bFindAFDevice( int CurDev=-1);

//write AF value.
/*
Function : bWriteAFValue :set the motor AF IC to driver the motor position..
value: motor pos:(0-1023)<<4
mode: motor AF IC mode;;;
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief 设置AF器件的D/A的输出值。
///
/// @param value：设置的AF器件的D/A输出值
/// @param mode：AF器件IC的模式
///
/// @retval TRUE：设置AF器件的D/A的输出值成功
/// @retval FALSE：设置AF器件的D/A的输出值失败
DTCCM_API BOOL _DTCALL_ bWriteAFValue(USHORT value, BYTE mode = 0, int CurDev=-1);
//set AF address such as 0x18 or 0x1c.
/*
Function : SetAFAddr :
Set motor AF IC address. normally is 0x18 or 0x1c...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief 设置AF器件的器件地址。
///
/// @param addr：设置AF器件的D/A器件地址
DTCCM_API void _DTCALL_ SetAFAddr(USHORT addr, int CurDev=-1);

/// @brief 获取AF器件的D/A芯片型号和器件地址。
///
/// @retval 返回AF器件的D/A芯片型号
DTCCM_API BYTE GetAFDevType(int CurDev = -1);

/// @brief 设置AF器件的D/A芯片型号。
///
/// @param type：设置AF器件的D/A芯片型号
DTCCM_API void SetAFDevType(BYTE type, int CurDev = -1);

/** @} */ // end of group7

/****************************************************************************************
LC/OS相关
****************************************************************************************/

/** @defgroup group8 LC/OS相关


* @{

*/

//OS test....
/// @brief OS参数配置。
/// 
/// @param osmaskl：有效管脚标识，每bit对应一个管脚，如果这些bit为1，表示对应的管脚将参与测试
/// @param osmaskh：有效管脚标识，每bit对应一个管脚，如果这些bit为1，表示对应的管脚将参与测试
/// @param kc：控制快冲开关，为1打开快充，为0关闭快充
/// @param oseasy：OS简单测试，不为0时MCU就给判断好送到AP
/// @param openStd：OS开路标准值
/// @param shortStd：OS开路标准值
/// 
/// @retval DT_ERROR_OK：OS测试参数配置成功
/// @retval DT_ERROR_FAILD：OS测试参数配置失败
/// 
/// @note 仅支持HV910/HV910D/PE910/PE910D
DTCCM_API int _DTCALL_ DTOS_OpenTest(ULONG osmaskl, ULONG osmaskh, BYTE kc, BYTE oseasy, USHORT openStd, USHORT shortStd, int CurDev=-1);

//reset OS 
/// @brief 复位OS模块
DTCCM_API void _DTCALL_ DTOS_Reset( int CurDev=-1);

//return -3 communication error...
//return -2 not finished...
//return -1 no error...
//return 0 no error...
//else return OS result 

/// @brief 返回OS测试结果。
/// 
/// @param pResult：开短路测试结果
/// @param MaxWaitms：设置OS测试最大等待时间
/// 
/// @note 仅支持HV910/HV910D/PE910/PE910D
DTCCM_API int _DTCALL_ DTOS_WaitTestFinished(BYTE* pResult, USHORT MaxWaitms, int CurDev=-1);
//Current overload....


//set to image mode or dtos mode...
//for HV910 . mode = 1, dtos mode; mode = 0, image mode...
//other system , this is no use...

/// @brief 设置进入图像模式或者OS模式。
/// 
/// @param mode：=1，OS模式；=0，图像模式
/// 
/// @note 仅支持HV910/HV910D/PE910/PE910D
DTCCM_API void _DTCALL_ SetWorkMode(BYTE mode, int CurDev=-1);


/// @brief LC/OS测试操作配置。
/// 
/// @param Command：操作码，参见宏定义“OS/LC测试配置定义”
/// @param IoMask：有效管脚标识位，每字节的每bit对应一个管脚，如果这些bit为1，表示对应的管脚将参与测试
/// @param PinNum：管脚数，这个决定IoMask数组大小，一般情况下IoMask的字节数为：PinNum/8+(PinNum%8!=0)
///
/// @retval DT_ERROR_OK：LC/OS测试操作配置成功
/// @retval DT_ERROR_FAILD：LC/OS测试操作配置失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ LC_OS_CommandConfig(DWORD Command, UCHAR IoMask[], int PinNum, int CurDev=-1);


/// @brief OS测试参数配置。
///
/// @param Voltage：测试电压，单位uV
/// @param HighLimit：Open测试标准数组，测试之前应该把每一个测试pin的开路标准初始化好，单位uV
/// @param LowLimit：Short测试标准数组，测试之前应该把每一个测试pin的开路标准初始化好，单位uV
/// @param PinNum：管脚数，这个决定HighLimit、LowLimit数组大小
/// @param PowerCurrent：电源pin电流，单位uA
/// @param GpioCurrent：GPIOpin电流，单位uA
///
/// @retval DT_ERROR_OK：OS测试参数配置成功
/// @retval DT_ERROR_FAILD：OS测试参数配置失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ OS_Config(int Voltage, int HighLimit[], int LowLimit[], int PinNum, int PowerCurrent, int GpioCurrent, int CurDev=-1);


/// @brief OS测试结果读取。
///
/// @param VoltageH：正向pos测试结果，单位uV
/// @param VoltageH：反向pos测试结果，单位uV
/// @param Result：开短路测试结果，参见宏定义“OS测试结果定义”
/// @param PosEn：正向测试使能 
/// @param NegEn：反向测试使能
/// @param PinNum：管脚数，这个决定VoltageH、VoltageL，Result数组大小
/// 
/// @retval DT_ERROR_OK：OS测试结果读取成功
/// @retval DT_ERROR_FAILD：OS测试结果读取失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ OS_Read(int VoltageH[], int VoltageL[], UCHAR Result[], BOOL PosEn, BOOL NegEn, int PinNum, int CurDev=-1);

/// @brief LC测试参数配置。
///
/// @param Voltage：LC测试电压，单位mV
/// @param Range：LC精度设置，Range为0精度是1uA，Range为1精度是10nA
///
/// @retval DT_ERROR_OK：LC参数参数配置成功
/// @retval DT_ERROR_FAILD：LC测试参数配置失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ LC_Config(USHORT Voltage, UCHAR Range, int CurDev=-1);

/// @brief LC测试结果读取。
///
/// @param CurrentH：正向测试结果单位nA
/// @param CurrentL：反向测试结果单位nA
/// @param PinNum：管脚数，这个决定CurrentH、CurrentL，数组大小
///
/// @retval DT_ERROR_OK：LC测试结果读取成功
/// @retval DT_ERROR_FAILD：LC测试结果读取失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ LC_Read(ULONG CurrentH[],ULONG CurrentL[],int PinNum,int CurDev=-1);

/// @brief 开关状态值读取。
///
/// @param Result：返回开关状态值
/// @param PinNum：管脚数，这个决定CurrentH、CurrentL，数组大小
///
/// @retval DT_ERROR_OK：LC开关状态值读取成功
/// @retval DT_ERROR_FAILD：LC开关状态值读取失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ LC_ReadSwitch(UCHAR Result[],int PinNum,int CurDev=-1);
/** @} */ // end of group8

/** @defgroup group9 扩展IO


* @{

*/
/************************************************************************
扩展IO                                                                     
************************************************************************/
/// @brief 设置外部扩展的3.3V电压输出。
///
/// @param bEnable：扩展电压输出使能
///
/// @retval DT_ERROR_OK：设置外部扩展的3.3V电压输出成功
/// @retval DT_ERROR_FAILD：设置外部扩展的3.3V电压输出失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetExtPowerEnable(BOOL bEnable,int CurDev=-1);

/// @brief 设置外部扩展的时钟输出。
///
/// @param bOnOff：使能时钟输出
/// @param uHundKhz：设置时钟输出值,单位Khz
///
/// @retval DT_ERROR_OK：设置外部扩展时钟输出成功
/// @retval DT_ERROR_FAILD：设置外部扩展时钟输出失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetExtClock(BOOL bOnOff,USHORT uHundKhz,int CurDev=-1);

/// @brief 设置外部扩展GPIO模式。
///
/// @param Pin[]：GPIO编号，参见宏定义“EXT_GPIO”
/// @param Mode[]：模式设置，参见枚举类型“EXT_GPIO_MODE”
/// @param iCount：设置IO个数
///
/// @retval DT_ERROR_OK：设置外部扩展GPIO模式成功
/// @retval DT_ERROR_FAILD：设置外部扩展GPIO模式失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetExtIoMode(EXT_GPIO Pin[],EXT_GPIO_MODE Mode[],int iCount,int CurDev=-1);

/// @brief 恒定电平输出模式时设置外部扩展GPIO电平。
///
/// @param Pin[]：GPIO编号，参见宏定义“EXT_GPIO”
/// @param Level[]：GPIO的电平值，FALSE为低电平，TRUE为高电平
/// @param iCount：设置IO个数
///
/// @retval DT_ERROR_OK：设置外部扩展GPIO电平成功
/// @retval DT_ERROR_FAILD：设置外部扩展GPIO电平失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetExtIoLevel(EXT_GPIO Pin[],BOOL Level[],int iCount,int CurDev=-1);

/// @brief 获取外部扩展GPIO的电平。
/// 
/// @param Pin[]：GPIO编号，参见宏定义“EXT_GPIO”
/// @param Level[]：GPIO的电平值，FALSE为低电平，TRUE为高电平
/// @param iCount：设置IO个数
///
/// @retval DT_ERROR_OK：获取外部扩展GPIO电平成功
/// @retval DT_ERROR_FAILD：获取外部扩展GPIO电平失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ GetExtIoLevel(EXT_GPIO Pin[],BOOL Level[],int iCount,int CurDev=-1);

/// @brief 扩展GPIO为高低电平交互输出时，高、低电平时间设置。
/// 
/// @param Pin[]：GPIO编号，参见宏定义“EXT_GPIO”
/// @param HighLevelTime[]：对应扩展GPIO高电平时间，单位us
/// @param LowLevelTime[]：对应扩展GPIO低电平时间，单位us
/// @param iCount：设置IO个数
///
/// @retval DT_ERROR_OK：设置外部扩展GPIO高低电平时间成功
/// @DT_ERROR_FAILD设置外部扩展GPIO高低电平时间失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetExtIoLevelTime(EXT_GPIO Pin[],int HighLevelTime[],int LowLevelTime[],int iCount,int CurDev=-1);

/// @brief 外部扩展I2C写
///
/// @param uDevAddr：设备地址
/// @param uRegAddr：设备寄存器
/// @param uRegAddrSize：寄存器地址的字节数
/// @param pData：写入寄存器的数据块
/// @param uSize：写入寄存器的数据块大小,最大为60个字节
/// 
/// @retval DT_ERROR_OK：写成功
/// @retval DT_ERROR_FAILD：写失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ ExtI2cWrite(UCHAR uDevAddr,USHORT uRegAddr,UCHAR uRegAddrSize,BYTE *pData,USHORT uSize,int CurDev=-1);

/// @brief 外部扩展I2C读
///
/// @param uDevAddr：设备地址
/// @param uRegAddr：设备寄存器
/// @param uRegAddrSize：寄存器地址的字节数
/// @param pData：读寄存器的数据块
/// @param uSize：读寄存器的数据块大小,最大为60个字节
/// @param bNoStop：是否发出I2C的STOP命令，一般情况下默认为FALSE，bNoStop=TRUE表示写的过程不会有I2C的停止命令，bNoStop=FALSE有I2C的停止命令
/// 
/// @retval DT_ERROR_OK：读成功
/// @retval DT_ERROR_FAILD：读失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ ExtI2cRead(UCHAR uDevAddr,USHORT uRegAddr,UCHAR uRegAddrSize,BYTE *pData,USHORT uSize,BOOL bNoStop=FALSE,int CurDev=-1);

/// @brief 设置外部触发输出接口电平
/// 
/// @param iTriggerOutPin：触发输出接口编号（当前美鸥力产品提供一个触发输出IO）
/// @param bTriggerOutFollowEnable：触发输出接口跟随使能信号，若为1则跟随TriggerIn信号电平，为0则为设置电平值
/// @param bLevel：电平值（0为输出低电平，1为输出高电平）
///
/// @retval DT_ERROR_OK：读成功
/// @retval DT_ERROR_FAILD：读失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ SetTriggerOutLevel(int iTriggerOutPin,BOOL bFollowTrigIn,BOOL bLevel,int CurDev=-1);

/// @brief 获取外部触发输入接口电平
/// 
/// @param iTriggerInPin：触发输入接口编号（当前美鸥力产品提供一个触发输出IO）
/// @param pLevel：返回的电平值（0为输出低电平，1为输出高电平）
///
/// @retval DT_ERROR_OK：读成功
/// @retval DT_ERROR_FAILD：读失败
/// @retval DT_ERROR_COMM_ERROR：通讯错误
DTCCM_API int _DTCALL_ GetTriggerInLevel(int iTriggerInPin,BOOL *pLevel,int CurDev=-1);


/** @} */ // end of group9

/*************************************************************************
温度传感器相关
*************************************************************************/

// 设置温度传感器上下限温度
DTCCM_API int _DTCALL_ SetTempRange(int iUpperLimit, int iLowerLimit, BOOL bEnable,int CurDev=-1);

// 读取当前温度值
DTCCM_API int _DTCALL_ GetCurrentTemp(int *pTemp,int CurDev=-1);

// 读取当前设置的温度范围
DTCCM_API int _DTCALL_ GetTempRange(int *pUpperLimit, int *pLowLimit,int CurDev=-1);

// 内部状态信息界面
DTCCM_API int _DTCALL_ ShowInternalStatusDialog(HWND hwnd,int CurDev=-1);

DTCCM_API int _DTCALL_ ShowFrameBufferControlDialog(HWND hwnd ,HWND *pRethwnd,int CurDev=-1);

DTCCM_API int _DTCALL_ ShowPropertyPage(HWND hwnd ,HWND *pRethwnd,int CurDev=-1);

/****************************************************************************************
其他
****************************************************************************************/
// 扩展控制接口
// dwCtrl:	控制码，可能由派生类定义
// dwParam:	控制码相关参数
// pIn:		读取的数据
// pInSize:	读取数据的大小，字节数，调用者指定要求读取的字节数，如果成功，返回实际读取的字节数
// pOut:	写入的数据
// pOutSize:写入数据的大小，字节数，调用者指定要求写入的字节数，如果成功，返回实际写入的字节数
DTCCM_API int _DTCALL_ ExCtrl(DWORD dwCtrl,DWORD dwParam,PVOID pIn,int *pInSize,PVOID pOut,int *pOutSize,int CurDev=-1);

#endif