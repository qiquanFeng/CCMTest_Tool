
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
* \section ��Ʒ����
*
* - USB2.0ϵ��
* -# HS128
* -# HS280
* -# HS300
* -# HS300D
* -# HV810
* -# HV810D
* -# HV910
* -# HV910D
* - PCIEϵ��
* -# PE300
* -# PE300D
* -# PE810
* -# PE810D
* -# PE910
* -# PE910D
* - USB3.0ϵ��
* -# UT300
* -# UO300
* -# UV910
* -# UF910
* -# UH910
* -# DTLC2
*
*
* \section  ��˾��ַ
* http://www.dothinkey.com
* 
* 
*
* \section �ĵ������汾��¼
*
* -# 2014/5/15 ����DTCC2APIGuide��\n


*			   DTCCM2APIGuide�汾Ϊ��1.0.0.0��
*
* -# 2014/5/30 �����Ӹ�λSENSORͼ�����ݽӿں���ResetSensorPort��\n
*              DTCCM2APIGuide�汾Ϊ��1.0.1.1��
*
*/

/******************************************************************************
�豸��Ϣ���
******************************************************************************/
/** @defgroup group1 �豸��Ϣ���
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
/// @brief ��ȡ�豸�����кš�
///
/// @param pSN�����ص��豸���к�
DTCCM_API void _DTCALL_ GetDeviceSN(BYTE *pSN, int CurDev=-1);

//return firmware version
/// @brief �����豸����ID��
/// 
/// @retval 0x1180��HS128���԰�
/// @retval 0x1280��HS230���԰�
/// @retval 0x1330��HS300���԰�
/// @retval 0x1332��HS300D���԰�
/// @retval 0x1380��HV810���԰�
/// @retval 0x1382��HV810D���԰�
/// @retval 0x1390��HV910���԰�
/// @retval 0x1392��HV910D���԰�
///
/// @retval 0x1330��PE300���԰�
/// @retval 0x1332��PE300D���԰�
/// @retval 0x1380��PE810���԰�
///	@retval 0x1382��PE810D���԰�
/// @retval 0x1390��PE910���԰�
///	@retval 0x1392��PE910D���԰�
///
///	@retval 0x1332��UT300���԰�
/// @retval 0x1333��UO300���԰�
///	@retval 0x1393��UV910���԰�
///	@retval 0x1392��UF910���԰�
///	@retval 0x1392��UH910���԰�
///	@retval 0x13A2��DTLC2���԰�
DTCCM_API DWORD _DTCALL_ GetFWVersion( int CurDev=-1);

/// @brief �����豸���ͺţ����ֲ�ͬ�Ĳ��԰塣
///
/// @retval 0x0010��HS128���԰�
/// @retval 0x0020��HS230���԰�
/// @retval 0x0030��HS300���԰�
/// @retval 0x0031��HS300D���԰�
/// @retval 0x0082��HV810���԰�
/// @retval 0x0083��HV810D���԰�
/// @retval 0x0092��HV910���԰�
/// @retval 0x0093��HV910D���԰�
///
/// @retval 0x0130��PE300���԰�
/// @retval 0x0131��PE300D���԰�
/// @retval 0x0180��PE810���԰�
///	@retval 0x0181��PE810D���԰�
/// @retval 0x0190��PE910���԰�
///	@retval 0x0191��PE910D���԰�
///
///	@retval 0x0231��UT300���԰�
///	@retval 0x0232��UO300���԰�
///	@retval 0x0291��UV910���԰�
///	@retval 0x0292��UF910���԰�
///	@retval 0x0293��UH910���԰�
///	@retval 0x02A1��DTLC2���԰�
DTCCM_API DWORD _DTCALL_ GetKitType(int CurDev=-1);

//return lib version;
/// @brief ��ȡ����İ汾��ţ���������Է����Լ��İ汾��š�
///
/// @retval ���ر���İ汾��
DTCCM_API DWORD _DTCALL_ GetLibVersion( int CurDev=-1);

/// @brief ��ȡFPGA�汾�š�
///
/// @retval ����FPGA�汾��
DTCCM_API DWORD _DTCALL_ GetFPGAVersion(int CurDev=-1);

/// @brief ��ȡFPGA�汾ID��
///
/// @param Chip��Ϊ0:PCI-E�ɼ����ϵ�FPGA��1�������ϵ�FPGA;
/// 
/// @retval ����FPGA�汾ID
/// 
/// @note ��PEϵ��֧�ָĺ���
DTCCM_API DWORD _DTCALL_ GetFPGAID(int Chip,int CurDev=-1);

//return Hardware Version...
//pBuf : Version string in ASCII code buffer
//length:version string length..
/// @brief ��ȡӲ���汾�š�
///
/// @param pBuf�����ص�Ӳ���汾��
/// @param length��Ӳ���汾���ֽڳ���
/// 
/// @retval TRUE����ȡӲ���汾�ųɹ�
/// @retval FALSE����ȡӲ���汾��ʧ��
DTCCM_API BOOL  _DTCALL_ GetHardwareVersion(BYTE* pBuf, BYTE length, int CurDev=-1);
/** @} */ // end of group1

/******************************************************************************
ISP���
******************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Image Data process..
//////////////////////////////////////////////////////////////////////////
/** @defgroup group2 ISP���


* @{

*/
/// @brief �˺�����֧��
DTCCM_API int _DTCALL_ GetCenterAreaFocusValue(BYTE* pData, int width, int height, int CurDev=-1);

//mode should be 0-3;
//Set YUV422 mode, 
//0:YCbYCr;
//1:YCrYCb;
//2:CbYCrY;
//3:CrYCbY;
/// @brief ����YUV��ʽ���μ�ö�����͡�YUV_FORMAT����
///
/// @param byYuvMode��YUV��ʽ����
///
/// @see YUV_FORMAT
DTCCM_API void _DTCALL_ SetYUV422Mode(BYTE mode, int CurDev=-1);

//mode should be 0-3;
//Set RGB raw mode, 
//0:RGGB; first line is RGRG.... ;second line is GBGB....;
//1:GRBG; first line is GRGR.... ;second line is BGBG....; 
//2:GBRG; first line is GBGB.... ;second line is RGRG....; 
//3:BGGR; first line is BGBG.... ;second line is GRGR....; 

/// @brief ����RAW��ʽ���μ�ö�����͡�RAW_FORMAT����
///
/// @param byRawMode��RAW��ʽ����
///
/// @see RAW_FORMAT
DTCCM_API void _DTCALL_ SetRawMode(BYTE mode, int CurDev=-1);

//change the captured from usb(sensor) to RGB24 bmp data..
//pIn: usb data buffer pointer
//pOut:RGB24 data buffer pointer
//width:Image source width
//height Image source height
//type: sensor type. should be 0:10bit raw ;1:8bit raw;2:YUV422 data;3:16bit raw.

/// @brief RAW/YUVתRGB��Դ���ݸ�ʽ��ImgFormatָ����
///
/// @param pIn��Դ����
/// @param pOut��תΪRGB24������
/// @param width��ͼ�����ݿ��
/// @param height��ͼ�����ݸ߶�
/// @param type��Դ���ݵĸ�ʽ��0��10bit raw��1��8bit raw��2��YUV422 data��3��16bit raw
DTCCM_API void _DTCALL_ USBDataToRGB24(BYTE* pIn, BYTE* pOut, USHORT width, USHORT height, BYTE type, int CurDev=-1);

//RGB24 to YUV422 (YcbYcr mode)
//pBmp24 :RGB24 data pointer;
//pOut   :YUV422 pointer
//width  :Image width;
//height :Image height;

/// @brief RGB24תYUV422��
///
/// @param pBmp24��RGB24����
/// @param pOut��YUV422����
/// @param width��ͼ�����ݿ��
/// @param height��ͼ�����ݸ߶�
DTCCM_API void _DTCALL_ RGB24ToYUV422(BYTE* pBmp24, BYTE* pOut, int width, int height, int CurDev=-1);

//RGB24 to YUV444 (Ycbcr )
//pBmp24 :RGB24 data pointer;
//pOut   :YUV422 pointer
//width  :Image width;
//height :Image height;

/// @brief RGB24תYUV444��
///
/// @param pBmp24��RGB24����
/// @param pOut��YUV422����
/// @param width��ͼ�����ݿ��
/// @param height��ͼ�����ݸ߶�
DTCCM_API void _DTCALL_ RGB24ToYUV444(BYTE *pBmp24, BYTE *pOut, int width, int height, int CurDev=-1);

//Raw data to YUV422 (YcbYcr Mode)
//pRaw : RGB raw data pointer;
//width: Image width;
//height:Image height;
//two steps:1. change to RGB24, call USBDataToRGB24()
//          2. change RGB24 to YUV422 data format ,call RGB24ToYUV422()

/// @brief RAWתYUV422��YcbYcr Mode����
///
/// @param pRaw��RAW����
/// @param width��ͼ�����ݿ��
/// @param height��ͼ�����ݸ߶�
DTCCM_API void _DTCALL_ RawToYUV422(BYTE *pRaw, int width, int height, int type, int CurDev=-1);

//verticl flip or not.

/// @brief ������ر�ͼ��ֱ����
///
/// @param bEnable��ͼ��ֱ����ʹ�ܣ�ΪTRUE������ֱ����ΪFALSE�رմ�ֱ����
DTCCM_API void _DTCALL_ SetVFlip(BOOL bEnable, int CurDev=-1);

//horizontal flip or not...

/// @brief ������ر�ͼ��ˮƽ����
///
/// @param bEnable��ͼ��ˮƽ����ʹ�ܣ�ΪTRUE����ˮƽ����ΪFALSE�ر�ˮƽ����
DTCCM_API void _DTCALL_ SetHFlip(BOOL bEnable, int CurDev=-1);

//horizontal flip

/// @brief ˮƽ��ת
/// 
/// @param pData������ת������
/// @param nWidth��ͼ�����ݿ��
/// @param nHeight��ͼ�����ݸ߶�
DTCCM_API BOOL _DTCALL_ HFlipBuf(BYTE *pData, LONG nWidth, LONG nHeight, int CurDev=-1);
//vertical flip

/// @brief ��ֱ��ת
/// 
/// @param inbuf������ת������
/// @param widthBytes��ͼ�����ݿ��
/// @param height��ͼ�����ݸ߶�
DTCCM_API BOOL _DTCALL_ VFlipBuf(BYTE *inbuf, UINT widthBytes, UINT height, int CurDev=-1);


//decode data... 
//code data is for usb2.0 bug...,here should decode it before process...
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ BitUnSwizzling(BYTE* pBuffer, ULONG size, int CurDev=-1);
//Edge enhancement...
/// @brief �˺�����֧��
DTCCM_API void  _DTCALL_ SetEdge(BYTE THflat, BYTE THedge, double EdgeGain, BOOL EdgeEnable, int CurDev=-1);

//////////////////////////////////////////////////////////////////////////
//color balance control :digital control.
//////////////////////////////////////////////////////////////////////////
//White balance and digital gain control function
// Set the AWB Gain Coefficent.
//default Red,Blue are 1.0f;1.0f.
//enable auto white balance or disable it..


/// @brief ������رհ�ƽ�⡣
///
/// @param bAWBEn����ƽ��ʹ�ܣ�ΪTRUE������ƽ�⣬ΪFALSE�رհ�ƽ��
DTCCM_API void _DTCALL_ SetAWB(BOOL bAWBEn, int CurDev=-1);

// check the now AWB state:AWB is ON or OFF.

/// @brief ��ȡ��ƽ�⿪��״̬��
///
/// @param pAwb�����صİ�ƽ��״̬
DTCCM_API BOOL _DTCALL_ GetAWB( int CurDev=-1);

//set the digital gain..

/// @brief ����RGB�������档
///
/// @param fRGain��R����ֵ
/// @param fGGain��G����ֵ
/// @param fBGain��B����ֵ
DTCCM_API void _DTCALL_ SetDigitalGain(int RGain,int GGain,int BGain , int CurDev=-1);


DTCCM_API int _DTCALL_ SetMatrixEnable(BOOL bEnable, int CurDev=-1);

//get the current gain..

/// @brief ��ȡRGB�������档
/// 
/// @param pRGain�����ص�R��������ֵ
/// @param pGGain�����ص�G��������ֵ
/// @param pBGain�����ص�B��������ֵ
DTCCM_API void _DTCALL_ GetDigitalGain(int* pRGain,int* pGGain,int* pBGain , int CurDev=-1);

//////////////////////////////////////////////////////////////////////////
//Set Gamma /Contrast/Saturation parameter...
//////////////////////////////////////////////////////////////////////////
/// @brief ����GAMMAֵ��
///
/// @param gamma�����õ�GAMMAֵ
DTCCM_API void _DTCALL_ SetGamma(BYTE gamma, int CurDev=-1);

/// @brief ��ȡGAMMA����ֵ��
/// 
/// @retval GAMMA����ֵ
DTCCM_API BYTE _DTCALL_ GetGamma( int CurDev=-1);

//set the contrast value of the video... only for rgb raw data

/// @brief ���öԱȶȡ�
///
/// @param value�����öԱȶ�ֵ
DTCCM_API void _DTCALL_ SetContrast(BYTE value, int CurDev=-1);
//get the contrast value of the video... only for rgb raw data

/// @brief ��ȡ�Աȶ�����ֵ��
///
/// @retval ���ضԱȶ�����ֵ
DTCCM_API BYTE _DTCALL_ GetContrast( int CurDev=-1);

//set the saturation of the video only for rgb raw data

/// @brief ���ñ��Ͷȡ�
///
/// @param value�����ñ��Ͷ�ֵ
DTCCM_API void _DTCALL_ SetSaturation(BYTE value, int CurDev=-1);

//get the saturation value of the video... only for rgb raw data

/// @brief ��ȡ���Ͷ�����ֵ��
///
/// @retval ���ر��Ͷ�����ֵ
DTCCM_API BYTE _DTCALL_ GetSaturation( int CurDev=-1);

/// @brief ������ȡ�
///
/// @param iSharpness���������ֵ
DTCCM_API int _DTCALL_ SetSharpness(int iSharpness, int CurDev=-1);

/// @brief ��ȡ�������ֵ��
///
/// @param pSharpness�����ص��������ֵ
DTCCM_API int _DTCALL_ GetSharpness(int *pSharpness, int CurDev=-1);

/// @brief ����������
///
/// @param iLevel����������ֵ
DTCCM_API int _DTCALL_ SetNoiseReduction(int iLevel, int CurDev=-1);

/// @brief ��ȡ��������ֵ��
/// 
/// @param pLevel���������õ�����ֵ
DTCCM_API int _DTCALL_ GetNoiseReduction(int *pLevel, int CurDev=-1);

/// @brief ������ر������㡣
/// 
/// @param bDeadPixCleanEn��ΪTRUE���������㣬ΪFALSE�ر�������
DTCCM_API int _DTCALL_ SetDeadPixelsClean(BOOL bDeadPixCleanEn,int CurDev=-1);

/// @brief ��ȡ�����㿪����ر�״̬��
/// 
/// @param pbDeadPixCleanEn������������ʹ��ֵ
DTCCM_API int _DTCALL_ GetDeadPixelsClean(BOOL *pbDeadPixCleanEn, int CurDev=-1);

DTCCM_API int _DTCALL_ SetHotCpth(int iHotCpth, int CurDev=-1);

DTCCM_API int _DTCALL_ GetHotCpth(int *pHotCpth, int CurDev=-1);

DTCCM_API int _DTCALL_ SetDeadCpth(int iDeadCpth, int CurDev=-1);

DTCCM_API int _DTCALL_ GetDeadCpth(int *pDeadCpth, int CurDev=-1);

/// @brief ����rawתrgb�㷨��
///
/// @param Algrithm��ramתrgb�㷨����ֵ,�μ��궨�塰RAWתRGB�㷨���塱
DTCCM_API int _DTCALL_ SetRaw2RgbAlgorithm(BYTE Algrithm, int CurDev=-1);


/// @brief ��ȡrawתrgb�㷨����ֵ��
///
/// @param ����rawתrgb�㷨����ֵ
DTCCM_API int _DTCALL_ GetRaw2RgbAlgorithm(BYTE *pAlgrithm, int CurDev=-1);

//get the color matrix correction enable or disable state...
//set the color matrix enable or disbale .

/// @brief ��RAWͼ�����ݽ���ͼ����(MONO,WB,ColorChange,Gamma,Contrast)��
///
/// @param pRaw��RAWͼ������
/// @param pBmp24������ͼ����������
/// @param nWidth��ͼ�����ݿ��
/// @param nHeight��ͼ�����ݸ߶�
DTCCM_API void _DTCALL_ ImageProcess(BYTE *pRaw, BYTE *pBmp24, int nWidth, int nHeight, int CurDev=-1);

/// @brief ��RGBͼ�����ݽ���ͼ����(MONO,WB,ColorChange,Gamma,Contrast)
/// 
/// @param pBmp24��RGB����
/// @param width��ͼ�����ݿ��
/// @param height��ͼ�����ݸ߶�
/// @param type�����õĲ���
DTCCM_API void _DTCALL_ ImageISP(BYTE *pBmp24, int width, int height, BYTE type, int CurDev=-1);

//set yuv color matrix...
/// @brief ����YUVתRGBʱ��һЩϵ����
///
///	@param Y=(Y-yoff)*ycoef
///	@param r=Y+(cr-128)*bdif
///	@param g=Y-cbcoef*(cb-128)-crcoef*(cr-128)
///	@param b=Y+(cb-128)*rdif
DTCCM_API void _DTCALL_ setyuvcoefficient (int yoff, float ycoef, float cbcoef, float crcoef,float rdif, float bdif, int CurDev=-1);

/// @brief �˺�����֧��
DTCCM_API int _DTCALL_ GetMatrixData(BYTE color,BYTE channel, int CurDev=-1);

/// @brief ������ɫ����
DTCCM_API void _DTCALL_ SetMatrixData(int R00, int R01, int R02, int G00, int G01, int G02, int B00, int B01, int B02, int CurDev=-1);

/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ CopySoftGridData(BYTE *pBmp24, int CurDev=-1);
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ DisplaySoftGrid(BYTE* pData, int CurDev=-1);
/// @brief �˺�����֧��
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

/// @brief ��ʼ����ʾ��
///
/// @param hWnd����ʾAͨ��ͼ��Ĵ��ھ��
/// @param ImgWidth��ͼ�����ݿ��
/// @param ImgHeight��ͼ�����ݸ߶�
/// @param SensorType��ͼ�����ݸ�ʽ��0��10bit raw��1��8bit raw��2��YUV422 data��3:16bit raw
DTCCM_API void _DTCALL_ InitDisplay(HWND hWnd, USHORT ImgWidth, USHORT ImgHeight, BYTE SensorType, int CurDev=-1);

//display the RGB24 image data.
//pBmp24: RGB24 bmp data buffer pointer.

/// @brief ��ʾRGBͼ�����ݡ�
///
/// @param pBmp24������ʾ��RGB24��ʽ������
DTCCM_API void _DTCALL_ DisplayRGB24(BYTE* pBmp24, int CurDev=-1);

//display the usb data
//two steps:
//1: call USBDataToRGB24() to change the usb data to the RGB24 data format.
//2: call DisplayRGB24() to display it...

/// @brief ��ʾRAW/YUVͼ�����ݣ�Դ���ݸ�ʽ��Init�����е�byImgFormat����ָ����
///
/// @param pData������ʾ��ͼ������
DTCCM_API void _DTCALL_ bDisplayVideo(BYTE* pData, int CurDev=-1);

DTCCM_API int DisplayVideoEx(BYTE *pData,FrameInfo *pInfo,int CurDev=-1);


/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ DisplayRGB24_roi(BYTE* pBmp24, int x0, int y0, int CurDev=-1);
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ bDisplayVideo_roi(BYTE *pData, int x0, int y0, int CurDev=-1);
//////////////////////////////////////////////////////////////////////////
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ VertFlipBuf(BYTE *inbuf, UINT widthBytes, UINT height, int CurDev=-1);
/*
DTCCM_API void _DTCALL_ GetDPSOffset(int *avdd_offset, int *dovdd_offset, int *dvdd_offset, int *afvcc_offset, int *vpp_offset, int CurDev = -1);
DTCCM_API void _DTCALL_ SetDPSOffset(int avdd_offset, int dovdd_offset, int dvdd_offset, int afvcc_offset, int vpp_offset, int CurDev = -1);

DTCCM_API BOOL _DTCALL_ bReadDPSOffsetFromEEPROM(int *avdd_offset, int *dovdd_offset, int *dvdd_offset, int * afvcc_offset, int *vpp_offset, int CurDev = -1);
DTCCM_API BOOL _DTCALL_ bWriteDPSOffsetToEEPROM(int avdd_offset, int dovdd_offset, int dvdd_offset, int afvcc_offset, int vpp_offset, int CurDev = -1);
*/

//for PE300/PE810/PE910
//before close video, first cancel the IO wait operation....
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ CancelIoWait( int CurDev=-1);
/* ��ȡ��ȷ֡/����֡����/���һ֡ͼ��Ĵ�С */
/// @brief �˺�����֧��
DTCCM_API BOOL _DTCALL_ GetLoadInfo(UINT *FrameOk,UINT *FrameErr,UINT *LastSize, int CurDev=-1);
//malloc bmp and raw data buffer...

/// @brief ��̬�ڴ����
/// 
/// @param pBuf���������ڴ��ָ��
/// @param Size�������ڴ��С
/// 
/// @retval TRUE����̬�ڴ����ɹ�
/// @retval FALSE����̬�ڴ����ʧ��
DTCCM_API BOOL _DTCALL_ MallocBuffer(LPBYTE *pBuf, ULONG Size, int CurDev=-1);
//delete bmp and raw data buffer...
/// @brief �ͷ��ڴ�ռ�
/// 
/// @param Buf�����ͷŵ��ڴ�
DTCCM_API void _DTCALL_ DeleteBuffer(LPBYTE Buf, int CurDev=-1);


///////////////////////////////////////////////////////////////////////////////////////////
//set mono or color mode...

/// @brief ������ر�MONOģʽ��
///
/// @param bEnable��MONOģʽʹ�ܣ�ΪTRUE����MONOģʽ��ΪFALSE�ر�MONOģʽ
DTCCM_API void _DTCALL_ SetMonoMode(BOOL bEnable, int CurDev=-1);

//change from color to gray(mono) bmp24

/// @brief ת�Ҷ�ͼ��
/// 
/// @param pData����תΪ�Ҷ�ͼ�������
/// @param nWidth��ͼ����
/// @param nHeight��ͼ��߶�
DTCCM_API void _DTCALL_ Gray(BYTE* pData, LONG nWidth, LONG nHeight, int CurDev=-1);

//show cross on image

/// @brief ��ͼ���ϻ��ϡ�ʮ������
/// 
/// @param pBmp��ͼ������
/// @param width��ͼ����
/// @param height��ͼ��߶�
DTCCM_API void _DTCALL_ ShowCrossOnImage(BYTE * pBmp, int width, int height, int CurDev=-1);

//enable cross on or off on the video....

/// @brief ������رա�ʮ�����ߡ�
///
/// @param bEnable����ʮ������ʹ�ܣ�ΪTRUE����ʮ���ߣ�ΪFALSE�ر�ʮ����
DTCCM_API void _DTCALL_ SetCrossOn(BOOL bEnable, int CurDev=-1);
/** @} */ // end of group2
/******************************************************************************
SENSOR���
*******************************************************************************/
/** @defgroup group3 SENSOR���


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

/// @brief ������ر�SENSOR����ʱ��
/// 
/// @param bOn��ΪTRUE����SENSOR����ʱ�ӣ�ΪFALSE�ر�SENSOR����ʱ��
///
/// @retval DT_ERROR_OK������SENSOR����ʱ�ӳɹ�
/// @retval DT_ERROR_FAILED������SENSOR����ʱ��ʧ��
DTCCM_API BYTE _DTCALL_ SetSensorMclkEnable(BOOL bOn, int CurDev=-1);

/*
Name :set sensor MClk in Mhz.
Function : set the mclk frequency....(unit is Mhz),but can use float directly...
like:you can set 33.3Mhz. SetSensorMClk(33.3)
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief ����SENSOR����ʱ��ֵ
/// 
/// @param mhz��SENSOR����ʱ��ֵ����λΪMhz
DTCCM_API void _DTCALL_ SetSensorMClk(double mhz, int CurDev=-1);
/*
Name :set sensor MClk in 0.1Mhz.
Function : set the mclk frequency....(unit is 0.1Mhz)
like:you can set 33.3Mhz. SetSensorMClk(333)
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief ����SENSOR����ʱ��ֵ
/// 
/// @param hundkhz��SENSOR����ʱ��ֵ����λΪ100Khz
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
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ SetFX2Clkout(BYTE mode, int CurDev=-1);

//no use here....
/// @brief �˺�����֧��
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
/// @brief �˺�����֧��
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
/// @brief �����ⲿ��չGPIO��������������
/// 
/// @param inout��bit[x]Ϊ1, IO[X]Ϊ�����bit[x]Ϊ0, IO[X]Ϊ����
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
/// @brief �����ⲿ��չGPIO��ƽ
/// @param value��BIT[x] ----IO[X] 1���ߵ�ƽ��0���͵�ƽ
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
/// @brief ��ȡ�ⲿ��չGPIO�ĵ�ƽ��
/// 
/// @retval �����ⲿ��չGPIO�ĵ�ƽ��BIT[x] ----IO[X] 1���ߵ�ƽ��0���͵�ƽ
DTCCM_API BYTE _DTCALL_ ReadExtendIO( int CurDev=-1);

/*
Function : ReadSoftPin
return value: Read GPIO[26:1] value..
return [25:0] is sensor interface GPIO[26:1]'s level state.... 
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief ��ȡ���Խӿڵ�ƽ��ÿBIT��Ӧһ���ܽţ�bit0��ӦPIN_1��
/// 
/// @retval �������Խӿڵ�ƽ
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
/// @brief ���ö��GPIO�ĵ�ƽ��Pin�д洢�ı��ֵ��1��ʼ��1��ʾGPIO1��
///
/// @param value��BIT[x] ----IO[X] 1���ߵ�ƽ��0���͵�ƽ
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
/// @brief �������Խӿ��Ƿ�ʹ���������衣
///
/// @param pullup�����Խӿ�����ʹ�ܣ�bPullup=1ʹ���������裬bPullup=0�ر���������
///
/// @retval DT_ERROR_OK�����óɹ�
/// @retval DT_ERROR_FAILED������ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetSoftPinPullUp(BYTE pullup, int CurDev=-1);

//�˺�����֧��
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
/// @brief ��λ��SensorͨѶ��I2C���ߡ�
///
/// @retval TRUE����λI2C�����ɹ�
/// @retval FALSE����λI2C����ʧ��
DTCCM_API BOOL _DTCALL_ bResetI2CBus( int CurDev=-1);
//b400K = 1, 400K I2C rate...; 0:100K rate...
/*
Function : SetI2CRate
b400k : 1:400K rate... 0:100K rate...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief ������SENSORͨѶ��I2C�������ʣ�400Kbps��100Kbps��
///
/// @param b400K��b400K=TURE��400Kbps��b400K=FALSE,100Kbps						 
DTCCM_API void _DTCALL_ SetI2CRate(BOOL b400k, int CurDev=-1);

/// @brief ������SENSORͨѶ��I2C�������ʣ���Χ10Khz-2Mhz��
///
/// @param uKpbs������I2C�������ʣ���ΧֵΪ10-2000
///							 
/// @retval DT_ERROR_OK�������������ʲ����ɹ�
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
//�˺�����֧��
DTCCM_API void _DTCALL_ SetI2CChannel(BYTE chan, int CurDev=-1);
//interval time between I2C bytes...
/*
Function : SetI2CInterval
nDly : delay ms between I2C bytes...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief ����I2CͨѶACK��ʱ�ȴ�ʱ�䡣
/// 
/// @param nUsWait������ACK��ʱ�ȴ�ʱ�䣬��λus
///
/// @retval DT_ERROR_OK������I2CͨѶACK��ʱ�ȴ�ʱ��ɹ�
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
/// @brief ʹ����SENSORͨѶ��I2C����ΪRapidģʽ��
///
/// @param  bRapid=TRUE��ʾ��i2c�ܽ�Ϊ�ߵ�ƽʱ���ܽ�����������=FALSE��I2C�ܽ�Ϊ����״̬�������ⲿ������ɸߵ�ƽ
///							 
/// @retval DT_ERROR_OK�������������ʲ����ɹ�
DTCCM_API void _DTCALL_ SetI2CSclMode(BOOL bOutput, int CurDev=-1);

/// @brief sensor i2c�ⲿ��������ѡ��
/// 
/// @param byPullupResistorSel=PULLUP_RESISTOR_1_5K,��ʾ1.5K��=PULLUP_RESISTOR_4_7K����ʾ4.7K��=PULLUP_RESISTOR_0_88K��ʾ0.88K
///
/// @retval DT_ERROR_OK�����óɹ�
/// @retval DT_ERROR_PARAMETER_INVALID��byPullupResistorSel������Ч
/// @retval DT_ERROR_TIME_OUT��ͨѶ��ʱ
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

/// @brief ��SESNOR�Ĵ���,I2CͨѶģʽbyI2cMode������ֵ��I2CMODE���塣
///
/// @param addr����������ַ
/// @param reg���Ĵ�����ַ
/// @param value�������ļĴ�����ֵ
/// @param mode��I2Cģʽ
/// @param bNoStop���Ƿ񷢳�I2C��STOP���һ�������Ĭ��ΪFALSE��bNoStop=TRUE��ʾ���Ĺ��̲�����I2C��ֹͣ���bNoStop=FALSE��I2C��ֹͣ����
///
/// @retval 1����SENSOR�Ĵ��������ɹ�
/// @retval 0����SENSOR�Ĵ�������ʧ��
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

/// @brief дSENSOR�Ĵ���,I2CͨѶģʽbyI2cMode������ֵ��I2CMODE���塣
/// 
/// @param addr����������ַ
/// @param reg���Ĵ�����ַ
/// @param value��д��Ĵ�����ֵ
/// @param mode��I2Cģʽ
///
/// @retval 1��дSENSOR�Ĵ��������ɹ�
/// @retval 0��дSENSOR�Ĵ�������ʧ��
///
/// @see I2CMODE
DTCCM_API BOOL _DTCALL_ bFX2WriteSensor(USHORT addr, USHORT reg, USHORT value, BYTE mode=0, int CurDev=-1);   

/// @brief дSENSOR�Ĵ�����֧�������Ĵ���д�����ݣ����֧��16���Ĵ�������
///
/// @param uAddr����������ַ
/// @param byI2cMode��I2Cģʽ
/// @param uRegNum��д��Ĵ������������16
/// @param RegAddr[]���Ĵ�����ַ����
/// @param RegData[]��д��Ĵ���������
/// @param RegDelay[]��д��һ��Ĵ�������һ��Ĵ���֮�����ʱ����λus
///
/// @retval DT_ERROR_OK�����дSENSOR�Ĵ��������ɹ�
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_INVALID��uSize������Ч
/// @retval DT_ERROR_TIME_OUT��ͨѶ��ʱ
/// @retval DT_ERROR_INTERNAL_ERROR���ڲ�����
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
/// @brief ��SENSOR�Ĵ�����֧����һ���Ĵ�������һ�����ݿ飨������255�ֽڣ���
///
/// @param Addr����������ַ
/// @param reg���Ĵ�����ַ
/// @param regsize���Ĵ�����ַ���ֽ���
/// @param ParaList�������Ĵ�����ֵ
/// @param Length�������Ĵ��������ݿ���ֽ�����������255�ֽڣ�
/// @param bNoStop���Ƿ񷢳�I2C��STOP���һ�������Ĭ��ΪFALSE��bNoStop=TRUE��ʾ���Ĺ��̲�����I2C��ֹͣ���bNoStop=FALSE��I2C��ֹͣ����
///
/// @retval 1����SENSOR�Ĵ���������ɹ�
/// @retval 0����SENSOR�Ĵ��������ʧ��
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
/// @brief дSENSOR�Ĵ�����֧����һ���Ĵ���д��һ�����ݿ飨������255�ֽڣ���
///
/// @param Addr����������ַ
/// @param reg���Ĵ�����ַ
/// @param regsize���Ĵ�����ַ���ֽ���
/// @param ParaList��д��Ĵ��������ݿ�
/// @param Length��д��Ĵ��������ݿ���ֽ�����������255�ֽ�(HS300/HS300D/HV910/HV910Dһ�β��ܳ���253�ֽ�)��
///
/// @retval 1��дSENSOR�Ĵ���������ɹ�
/// @retval 0��дSENSOR�Ĵ��������ʧ��
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

/// @brief ͨ��Reset,PWDN�ܽſ�����ر�SENSOR��
///
/// @param byPin��Reset��PWDN��PWDN2
/// @param bEnable��������ر�SENSOR
///
/// @retval TRUE��������ر�SENSOR�����ɹ�
/// @retval FALSE��������ر�SENSOR����ʧ��
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

/// @brief �����ϵ�SENSOR�ǲ��ǵ�ǰָ���ģ����ҿ���ͬʱ��SENSOR����һ�θ�λ��
///
/// @param Info��SENSOR��Ϣ���μ�SensorTab�ṹ��
/// @param bReset����SENSOR��λ
///
/// @retval DT_ERROR_OK���ҵ�SENSOR
/// @retval DT_ERROR_FAILED��û���ҵ�SENSOR
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
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
// �˺�����֧��
DTCCM_API int _DTCALL_ SensorIsMe_Triple(SensorTab *Info, int Camera, BOOL bReset = TRUE, int CurDev=-1);
////init the sensor register...
/*
Function : bInitSensor :set sensor reset pin and pwdn pin
Info: Sensor information according to the info/dat lib..
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief ��ʼ��SENSOR��
///
/// @param addr��SENSOR������ַ
/// @param ParaList��SENSOR�Ĳ����б�
/// @param Length��pParaList�Ĵ�С
/// @param mode������SENSOR��I2Cģʽ���μ�ö������I2CMODE
///
/// @retval DT_ERROR_OK����ʼ��SENSOR�ɹ�
/// @retval DT_ERROR_FAILED����ʼ��SENSORʧ��
///
/// @see I2CMODE
DTCCM_API BOOL _DTCALL_ bInitSensor(USHORT addr, USHORT* ParaList, USHORT Length, BYTE mode=0, int CurDev=-1); 

DTCCM_API int _DTCALL_ SensorIsMe_Dual2(SensorTab2 *Info, int Camera ,BOOL bReset = TRUE, int CurDev=-1);

/// @brief ��ʼ��SENSOR��
///
/// @param addr��SENSOR������ַ
/// @param ParaList��SENSOR�Ĳ����б�
/// @param Length��pParaList�Ĵ�С
/// @param mode������SENSOR��I2Cģʽ���μ�ö������I2CMODE
///
/// @retval DT_ERROR_OK����ʼ��SENSOR�ɹ�
/// @retval DT_ERROR_FAILED����ʼ��SENSORʧ��
///
/// @see I2CMODE
DTCCM_API BOOL _DTCALL_ bInitSensor2(UINT addr, UINT* ParaList, UINT Length, UINT mode=0, int CurDev=-1); 

//check reset or power down pin ok or not...
/// @brief ���Reset,PWDN�ܽ��Ƿ��SENSOR�����á�
///
/// @param pInfo��SENSOR�Ĳ�����Ϣ
/// @param bRstChkEn��ʹ�ܼ��Reset
/// @param bPwdnChkEn��ʹ�ܼ��PWDN
/// @param byChannel��A/Bͨ��ѡ��
/// @param pErrorx�����ص�Reset��PWDN�ļ����Ϣ
///
/// @retval DT_ERROR_OK�������ɹ�
DTCCM_API BYTE _DTCALL_ CheckRstPwdnPin2(SensorTab2 *Info, BOOL RstChkEn, BOOL PwdnChkEn, BYTE CurCam = 0, int CurDev=-1);

//set sensor port type:MIPI /Parallel/MTK/SPI/TEST...

/// @brief ��ȡ��ǰ���õ�ͼ�����ݽӿ�����
///
/// @retval ���ص�ǰ���õ�ͼ�����ݽӿ�����
DTCCM_API BYTE _DTCALL_ GetSensorOutPort( int CurDev=-1);

//type = 0 : MIPI
//type = 1 : Parallel
//type = 2 : MTK
//type = 3 : SPI
//type = 4 : test

/// @brief ����SENSORͼ�����ݽӿ����͡�
///
/// @param type��SENSORͼ�����ݽӿ����ͣ��μ�ö�����͡�SENSOR_PORT��
///
/// @see SENSOR_PORT
DTCCM_API void _DTCALL_ SetSensorOutPort(BYTE type, int CurDev=-1);

/// @brief ��λSENSORͼ�����ݽӿ�
/// 
/// @param byPort��SENSORͼ�����ݽӿ����ͣ��μ�ö�����͡�SENSOR_PORT��
///
/// @retval DT_ERROR_OK��ROI���óɹ�
/// @retval DT_ERROR_FAILD��ROI����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
///
/// @see SENSOR_PORT
DTCCM_API int _DTCALL_ ResetSensorPort(BYTE byPort,int CurDev=-1);

//for correct mipi receiver, should set this to enable ....
// if disable ,no clk_n or no clk_p can output image...
// �˺�����֧��
DTCCM_API void _DTCALL_ CheckMIPIClk(BOOL bEnable, int CurDev=-1);

//using this function to check MIPI siginals whether link to GND or not...
//should set MIPI sensor to LP state or reset state or Pwdn state firstly... 
//BIT7-0 DATA N P
//BIT9-8 CLK N P
// �˺�����֧��
DTCCM_API USHORT _DTCALL_ ReadMIPIPortInLPState(int CurDev=-1);

//set mipi clock continous or not...
// this only support some ....
/// @brief ����MIPI���շ�����ʱ��
/// 
/// @param bContinous��ΪTRUE��MIPI���շ�����ʱ�ӣ�ΪFALSE��MIPI��������ʱ��
DTCCM_API void _DTCALL_ SetMIPIClk(BOOL bContinous, int CurDev=-1);

//20111202 to output long packet information like line flag and crc data...
//when power up ,it is 0.
/// @brief ����MIPI�����������ݰ������������ͷ��CRC16У��
/// 
/// @param bEnable��ΪTRUE����MIPI�����������ݰ������Ĭ��ΪFALSE
DTCCM_API void _DTCALL_ SetMIPILongPacketOut(BOOL bEnable = 0, int CurDev=-1);

/// @brief ��������ͨ����
/// 
/// @param uVC�����ý��յ�ͼ��ͨ���ţ�0/1/2/3
/// @param bVCFileterEn��ʹ�ܹ�������������ͨ��
///
/// @retval DT_ERROR_OK������MIPI�ӿڿ������ɹ�
/// @retval DT_ERROR_FAILED������MIPI�ӿڿ�����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetMipiImageVC(UINT uVC, BOOL bVCFilterEn, BYTE byChannel=CHANNEL_A, int CurDev=-1);


/// @brief ����MIPI��,ָ��Ҫ���˵İ���ID�ż����˵İ�����
///
/// @param PackID[]������Ҫ���˵İ���ID��
/// @param iCount�����˵İ�ID�ĸ�����DMU950���64
///
/// @retval DT_ERROR_OK��ROI���óɹ�
/// @retval DT_ERROR_FAILD��ROI����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetMipiPacketFilter(int PackID[],int iCount,int CurDev=-1);

/// @brief ��ȡ���˵İ���ID��
///
/// @param PackID[]�����صĹ��˵İ���ID��
/// @param pCount�����ع��˰��ĸ���
/// @param MaxCount������Ҫ��ȡ�İ�ID���������DMU950���64
///
/// @retval DT_ERROR_OK��ROI���óɹ�
/// @retval DT_ERROR_FAILD��ROI����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ GetMipiPacketFilter(int PackID[], int *pCount, int MaxCount,int CurDev=-1);

//Get MIPI clock phase

/// @brief ��ȡMIPI�ӿڽ�����ʱ����λֵ��
///
/// @retval ����MIPI�ӿڽ�����ʱ����λֵ
DTCCM_API BYTE _DTCALL_ GetMIPIClkPhase(int CurDev=-1);

//Set MIPI clock phase

/// @brief ����MIPI�ӿڽ�����ʱ����λ��
///
/// @param phase��MIPI�ӿڽ�����ʱ����λ���������õ�ֵ��0-7��
DTCCM_API void _DTCALL_ SetMIPIClkPhase(BYTE phase, int CurDev=-1);

/// @brief ����MIPI�ܽ�ʹ���ź�
///
/// @param bEnable��ΪFalseʱMIPI����HS״̬��ΪTRUE����LP״̬
///
/// @retval DT_ERROR_OK��ROI���óɹ�
/// @retval DT_ERROR_FAILD��ROI����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetMipiEnable(BOOL bEnable, int CurDev=-1);

//read mipi crc count...
//only when crc count is not changed. then the mipi decode is ok...

/// @brief ��ȡMIPI�ӿڽ�����CRC���������
///
/// @retval ����MIPI�ӿڽ�����CRC�������ֵ
DTCCM_API USHORT _DTCALL_ ReadMIPICRC(int CurDev=-1);

//get mipi clock in Mhz ...

/// @brief ��ȡMIPI�ӿڵ�ͬ��ʱ��Ƶ�ʡ�
///
/// @param freq�����õ�MIPI�ӿڵ�ͬ��ʱ��Ƶ��ֵ
///
/// @retval TRUE����ȡMIPI�ӿڵ�ͬ��ʱ��Ƶ�ʳɹ�
/// @retval FALSE����ȡMIPI�ӿڵ�ͬ��ʱ��Ƶ��ʧ��
DTCCM_API BOOL _DTCALL_ GetMIPIClkFrequency(ULONG *freq, int CurDev = -1);


/// @brief ��ȡMIPI�ӿڵ�LOCK״̬��
///
/// @param pMipiLockState����ȡMIPI�ӿڵ�LOCK״̬����bit0-bit3���α�ʾLANE1��LANE2��LANE3��LANE4
///
/// @retval DT\����ȡMIPI�ӿڵ�ͬ��ʱ��Ƶ�ʳɹ�
/// @retval FALSE����ȡMIPI�ӿڵ�ͬ��ʱ��Ƶ��ʧ��
DTCCM_API int _DTCALL_ GetMipiLockState(DWORD *pMipiLockState,BYTE byChannel,int CurDev = -1);


//set the Pclk and Hsync polarity;
//0 is invert the clk. 1 is postive clk...
//Vsync = -1; auto.default
//Vsync = 0; when 0 output valid hsync 
//Vsync = 1; when 1 output valid hsync 
/// @brief ����PCLK��Hsync��Vsync����
DTCCM_API BOOL _DTCALL_ bSetPClkHSync(BOOL bPClk, BOOL bHSync, char Vsync = -1, int CurDev=-1);

//in snap mode, run this will trigger the snap...

/// @brief ����һ��ץ��
DTCCM_API void _DTCALL_ TriggerSnap( int CurDev=-1);

//snap_en : 1: enable the capture image.
//snap_count: the snap count number...

/// @brief ͼ��ץ�����ã�����ʹ�ܺ�һ��ץ�ĵ�֡����
/// 
/// @param snap_en��ʹ�ܲ���ͼ��ΪTRUEʹ�ܲ���ͼ��ΪFALSE�ر�
/// @param snap_count������ͼ���֡��
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

/// @brief ����ROI��
///
/// @param roi_x0����ʼ��ˮƽ���꣬��λ�ֽ�
/// @param roi_y0����ʼ�㴹ֱ���꣬��λ�ֽ�
/// @param roi_hw��ˮƽ����ROIͼ���ȣ���λ�ֽ�
/// @param roi_vw����ֱ����ROIͼ��߶ȣ���λ�ֽ�
/// @param roi_hb��ˮƽ����blank��ȣ���λ�ֽ�
/// @param roi_vb��ˮƽ����blank�߶ȣ���λ�ֽ�
/// @param roi_hnum��ˮƽ����ROI��������λ�ֽ�
/// @param roi_vnum����ֱ����ROI��������λ�ֽ�
/// @param type��SENSOR����
/// @param roi_en��ROIʹ��
///
/// @retval DT_ERROR_OK��ROI���óɹ�
/// @retval DT_ERROR_FAILD��ROI����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
///
/// @note �ú�����ָ����Ⱥ�ˮƽλ�������ֽ�Ϊ��λ�����ұ�֤���Ϊ4�ֽڵ���������
///
/// @image html roi.png
DTCCM_API void _DTCALL_ SetROI(USHORT roi_x0, USHORT roi_y0, USHORT roi_hw,USHORT roi_vw, USHORT roi_hb, USHORT roi_vb, USHORT roi_hnum, USHORT roi_vnum, BYTE type,BOOL roi_en = TRUE, int CurDev=-1);
//set preview width and height and type....
//width :video image width in bytes.
//height:video image height in btes.
//type:sensor type.
//isp_en:use hardware isp or not. 1:enable; 0:disable. HS300 don't have hardware isp,
//bEnMono:use hardware single mono output or not. 1:use; 0:disable;  HS300/HV810/HV910 don't have hardware mono output function.

/// @brief ����Ԥ��ͼ��Ŀ�ȡ��߶ȡ�sensor���͵�
/// 
/// @param width��ͼ����
/// @param height��ͼ��߶�
/// @param type��sensor����
/// @param isp_en��Ӳ��ISPʹ�ܣ�Ϊ1ʹ�ܣ�Ϊ0�رգ�Ĭ�Ϲرգ���ʱ��֧�ָù��ܣ�
/// @param bEnMono��monoģʽʹ�ܣ�Ϊ1ʹ�ܣ�Ϊ0�رգ�Ĭ�Ϲرգ���ʱ��֧�ָù��ܣ�
/// 
/// @param TRUE:���óɹ�
/// @param FALSE������ʧ��
DTCCM_API BOOL _DTCALL_ SetPreview(USHORT width, USHORT height, BYTE type, BOOL isp_en = FALSE,BOOL bEnMono = FALSE, int CurDev=-1);

//multicam mode
/// @brief �˺�����֧��
DTCCM_API BYTE _DTCALL_ GetMultiCamMode( int CurDev=-1);//
//set multicam mode...
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ SetMultiCamMode(BYTE mode, int CurDev=-1);

//these functions only useful in HS100 HS200...
//soft pin definion..
/// @brief �������Խӿڡ�
///
/// @param PinList�����Խӿ����ö���
DTCCM_API void _DTCALL_ SetFPGAPin(BYTE* PinList, int CurDev=-1);
//set fpga to spi serial mode...
//no use for HS130 HS300 HV810 HV910....
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ SetFPGAToSPI(BOOL bEnable, int CurDev=-1);
//set fpga to mtk serial mode...
//no use for HS130 HS300 HV810 HV910....
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ SetFPGAToMTKSerial(BOOL bEnable, int CurDev=-1);

/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ SetFPGAPclkIn(BYTE clk, int CurDev=-1);
//20120901 added....
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ ClearUSBFIFO(int CurDev = -1);

/// @brief I2C��д������
///
/// @param rw��Ϊ0��д��Ϊ1�Ƕ�
/// @param DevAddr���豸��ַ
/// @param RegAddr���Ĵ�����ַ
/// @param RegAddrSize���Ĵ�����ַ��С
/// @param Data��������д����buffer
/// @param DataSize��������д�����ֽ���
/// 
/// @retval TRUE�������ɹ�
/// @retval FALSE������ʧ��
/// 
/// @note ��PEϵ��֧��
DTCCM_API BOOL  _DTCALL_ I2cRW(UCHAR rw,UCHAR DevAddr,USHORT RegAddr,UCHAR RegAddrSize,UCHAR *Data,UCHAR DataSize, int CurDev = -1);

//check reset or power down pin ok or not...
/// @brief ���Reset,PWDN�ܽ��Ƿ��SENSOR�����á�
///
/// @param pInfo��SENSOR�Ĳ�����Ϣ
/// @param bRstChkEn��ʹ�ܼ��Reset
/// @param bPwdnChkEn��ʹ�ܼ��PWDN
/// @param byChannel��A/Bͨ��ѡ��
/// @param pErrorx�����ص�Reset��PWDN�ļ����Ϣ
///
/// @retval DT_ERROR_OK�������ɹ�
DTCCM_API BYTE _DTCALL_ CheckRstPwdnPin(SensorTab *Info, BOOL RstChkEn, BOOL PwdnChkEn, BYTE CurCam = 0, int CurDev=-1);


/****************************************************************************************
SPI����
*****************************************************************************************/

/// @brief uPort:SPI������ѡ��
/// 
/// @brief pSPIConfig:SPI���ýṹ�壬�μ�imagekit.h
/// 
/// @retval DT_ERROR_OK��SPI���óɹ�
/// @retval DT_ERROR_FAILD��SPI����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ MasterSpiConfig(UCHAR uPort,MasterSpiConfig_t *pSPIConfig,int CurDev=-1);

/// @brief SPI�������ӿڣ�֧�����߻�����ͨѶ��֧�ֵ��ֽڴ���Ͷ��ֽ��������䣬֧�ֶ�дҪ��
///
/// @param bStart��ΪTrueƬѡ�ź����ͣ�ΪFalseƬѡ�źŲ�����
/// @param bStop��ΪTrueƬѡ�ź����ߣ�ΪFalseƬѡ�źŲ�����
/// @param bMsb��ΪTrue�Ǹ�λ�ȳ���ΪFalse�ǵ�λ�ȳ�
/// @param TxData��д�������BUFFER
/// @param RxData�����ص�����BUFFER
/// @param TxLen��д�����ݵĴ�С���ֽ���
/// @param RxLen����ȡ���ݵĴ�С���ֽ���

/// @retval DT_ERROR_OK�������ɹ�
/// @retval DT_ERROR_FAILD������ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SensorSpiRW(BOOL bStart,BOOL bStop,BOOL bMsb,UCHAR *TxData,UCHAR *RxData,UCHAR TxLen,UCHAR RxLen,int CurDev=-1);

/// @brief SPI������ʹ�ܡ��ٶȡ�ģʽ���ã�UT300/UV910����ע�⣺�ڲ���SensorSpiRW֮ǰ����ʹ��SPI���ߣ��������������ر�SPI���ߣ�����Ӱ��SENSOR i2c�ķ��ʡ�
/// 
/// @param bEnable��ΪTrue�ǿ���SPI���ߣ�ΪFalse�ǹر�SPI����
/// @param iRate��ΪTrue��500Kbps ΪFalse��250Kbps
/// @param bType�����߻�����ͨѶѡ��ΪFalse������SPIͨѶ��ΪTrue������SPIͨѶ
///
/// @retval DT_ERROR_OK�������ɹ�
///
/// @note �ڲ���SensorSpiRW֮ǰ����ʹ��SPI���ߣ��������������ر�SPI���ߣ�����Ӱ��SENSOR i2c�ķ���
DTCCM_API int _DTCALL_ SensorSpiInit(BOOL bEnable, int iRate, BOOL bType, int CurDev=-1);
/****************************************************************************************
���Խӿ�ʱ�����
*****************************************************************************************/
/// @brief ���Խӿڿɵ���ʱ�ӣ�֧�����Թܽ����0-200Khz�ɵ���ʱ��
///
/// @param uHz�����ʱ�Ӵ�С����λHz��0-200Khz�ɵ���
/// @param bOnOff���ɵ���ʱ�����ʹ�ܣ�TrueΪ���ʹ�ܣ�FalseΪ�ر����
///
/// @retval DT_ERROR_OK������ʱ������ɹ�
/// @retval DT_ERROR_FAILD������ʱ�����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetSoftPinAdjClk1(UINT uHz,BOOL bOnOff,int CurDev=-1);

/// @brief ���Խӿڿɵ���ʱ�ӣ�֧�����Թܽ����0-18Mhz�ɵ���ʱ��
/// 
/// @param uHundkHz���������ʱ�Ӵ�С����λ100KHz��0-18Mhz�ɵ���
/// @param bOnOff���ɵ���ʱ�����ʹ�ܣ�TrueΪ���ʹ�ܣ�FalseΪ�ر����
///
/// @retval DT_ERROR_OK������ʱ������ɹ�
/// @retval DT_ERROR_FAILD������ʱ�����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetSoftPinAdjClk2(USHORT uHundkHz,BOOL bOnOff,int CurDev=-1);
/** @} */ // end of group3
/******************************************************************************
ͼ�����ݲɼ����
******************************************************************************/

/** @defgroup group4 ͼ�����ݲɼ����


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

/// @brief ����ͼ�����ݲɼ���
DTCCM_API void _DTCALL_ FX2OpenVideo( int CurDev=-1);  
/*
Name :FX2CloseVideo
Function : set demokit to stop to receive the video data from the sensor.
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/    
//set FX2 to stop the video data from sensor..

/// @brief �ر�ͼ�����ݲɼ���
DTCCM_API void _DTCALL_ FX2CloseVideo( int CurDev=-1);

/// @brief У׼sensor���գ�����openvideo֮����ã�У׼�ɹ��ٽ���ץ֡����
/// 
/// @param uTimeOut��У׼��ʱʱ�����ã���λms
/// 
/// @retval DT_ERROR_OK��У׼�ɹ������Բɼ�ͼ��
/// @retval DT_ERROR_TIME_OUT��У׼��ʱ
DTCCM_API int _DTCALL_ CalibrateSensorPort(ULONG uTimeOut,int CurDev=-1);


/// @brief ���òɼ�һ֡������
/// 
/// @param uGrabFrameSize������һ֡����������С����λ�ֽ�
DTCCM_API int _DTCALL_ SetGrabFrameSize(ULONG uGrabFrameSize,int CurDev=-1);


/// @brief ���òɼ����ݳ�ʱ����λ��ms��������¼���û�вɼ���ͼ�����ݣ�GrabFrame���������س�ʱ����
///
/// @param uTimeOut���ɼ����ݳ�ʱʱ�����ã���λms
DTCCM_API int _DTCALL_ SetGrabTimeout(ULONG uTimeOut,int CurDev=-1);

/// @brief ����grabframeģʽ
///
/// @param byMode��ISP����ģʽ��0Ϊnormal��1ΪS2DFAST��2ΪS2DFAST GPU
DTCCM_API int _DTCALL_ SetImageProcessMode(BYTE byMode,int CurDev=-1);

/// @brief S2DFASTģʽץȡ���ݣ��õ�����RGB����
///
/// @param pBuf: ֡buffer
/// 
/// retval:DT_ERROR_FAILED:ץȡʧ�ܣ��õ�����֡
/// retval:DT_ERROR_TIMEOUT:ץȡ��ʱ��û��ץ������
DTCCM_API int _DTCALL_ S2DfastDirectGrabFrame(BYTE **pBuf,int CurDev=-1);

DTCCM_API int _DTCALL_ S2DfastReleaseBuffer(BYTE *pBuf,int CurDev=-1);


/// @brief ����FrameBuffer
/// 
/// @param pConfig��FrameBuffer���ýṹ��,�ýṹ��˵���μ�imagekit.hͷ�ļ�
DTCCM_API int _DTCALL_ SetFrameBufferConfig(FrameBufferConfig *pConfig,int CurDev=-1);

/// @brief ��ȡFrameBuffer��������Ϣ
/// 
/// @param pConfig��FrameBuffer���ýṹ��,�ýṹ��˵���μ�imagekit.hͷ�ļ�
DTCCM_API int _DTCALL_ GetFrameBufferConfig(FrameBufferConfig *pConfig,int CurDev=-1);

/// @brief ����ʱ��㣬���óɹ����豸��ʱ���ֵ���Ӹ�ʱ��㿪ʼ��ʱ����λus��
/// 
/// @param uTimeStamp: ʱ���
/// 
/// @retval DT_ERROR_OK�����óɹ�
/// @retval DT_ERROR_FAILD������ʧ�� 
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetTimerClock(double uTime, int CurDev=-1);

/// @brief ��ȡʱ���(��λus)
/// 
/// @param pTimeStamp: ʱ���ֵ
/// 
/// @retval DT_ERROR_OK�����óɹ�
/// @retval DT_ERROR_FAILD������ʧ�� 
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ GetTimeStamp(double *pTimeStamp, int CurDev=-1);

/// @brief ��ղ��ԺеĻ���
/// 
/// @retval DT_ERROR_OK����ճɹ�
/// @retval DT_ERROR_FAILD�����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ ResetFrameBuffer(int CurDev=-1);

/// @brief �ɼ�һ֡ͼ�񣬲��ҷ���֡��һЩ��Ϣ��
///
/// @param pInBuffer���ɼ�ͼ��BUFFER
/// @param uBufferSize���ɼ�ͼ��BUFFER��С����λ�ֽ�
/// @param pGrabSize��ʵ��ץȡ��ͼ�����ݴ�С����λ�ֽ�
/// @param pInfo�����ص�ͼ��������Ϣ
///
/// @retval DT_ERROR_OK���ɼ�һ֡ͼ��ɹ�
/// @retval DT_ERROR_FAILD���ɼ�һ֡ͼ��ʧ�ܣ����ܲ���������һ֡ͼ������
/// @retval DT_ERROR_TIME_OUT���ɼ���ʱ
/// @retval DT_ERROR_INTERNAL_ERROR���ڲ����� 
/// 
/// @note ���øú���֮ǰ�����ȸ���ͼ���С��ȡ���㹻��Ļ���������װ��ͼ�����ݡ�\n
/// ͬʱ���������Ĵ�СҲ��Ҫ��Ϊ�������뵽GrabFrameEx�������Է�ֹ�쳣����µ��µ��ڴ����Խ�����⡣ 
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
/// @brief �ɼ�һ֡ͼ��
///
/// @param inbuffer���ɼ�ͼ��BUFFER
/// @param buffersize���ɼ�ͼ��BUFFER��С����λ�ֽ�
///
/// @retval 1���ɼ�һ֡ͼ��ɹ�
/// @retval 0���ɼ�һ֡ͼ��ʧ�ܣ����ܲ���������һ֡ͼ������
/// @retval -1���ɼ���ʱ�����ڲ�����
/// 
/// @note ���øú���֮ǰ�����ȸ���ͼ���С��ȡ���㹻��Ļ���������װ��ͼ�����ݡ�\n
/// ͬʱ���������Ĵ�СҲ��Ҫ��Ϊ�������뵽GrabFrame�������Է�ֹ�쳣����µ��µ��ڴ����Խ�����⡣ 

DTCCM_API int _DTCALL_ bGrabFrame(BYTE* inbuffer, ULONG buffersize, int CurDev=-1);


//set async read wait time....
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ SetWaitTime(ULONG tmS, BOOL WaitEn = FALSE, int CurDev=-1);

//20111223 added...
//if transfer failed, can call this to ask usb to send the data from usb buffer to pc... 
/// @brief �ط���һ֡ͼ��
DTCCM_API void _DTCALL_ ReSendImage( int CurDev=-1);
//get the sensor ouput frame count....
/// @brief �˺�����֧��
DTCCM_API WORD _DTCALL_ GetSensorVideoFrameCount(int CurDev = -1);

//get the image data width in the video in bytes...
/// @brief ����ͼ�����ݿ�ȡ�
///
/// @retval ����ͼ�����ݿ��
DTCCM_API WORD _DTCALL_ GetSensorVideoWidth( int CurDev=-1);

//get the image data height in the video in bytes...

/// @brief ����ͼ�����ݸ߶ȡ�
///
/// @retval ����ͼ�����ݸ߶�
DTCCM_API WORD _DTCALL_ GetSensorVideoHeight( int CurDev=-1);

/// @brief ����ʵ��ץȡͼ�����ݵĴ�С����λ�ֽڣ���
/// 
/// @param pGrabSize������ʵ��ץȡͼ�����ݴ�С
DTCCM_API int _DTCALL_ CalculateGrabSize(ULONG *pGrabSize,int CurDev=-1);

//get the bmp buffer pointer....
/// @brief ����Bmp����buffer��
DTCCM_API BYTE* _DTCALL_ GetBmpBuffer( int CurDev=-1);
/** @} */ // end of group4
/******************************************************************************
��Դ����Ԫ���
******************************************************************************/
/** @defgroup group5 ��Դ����Ԫ���


* @{

*/
/*
*  ��ӦλΪ1 ������Ϊ0�޹���
*  OverBuf[0].0λ��AVDD;   OverBuf[0].1λ��DOVDD;  OverBuf[0].2λ��DVDD��
*  OverBuf[0].3λ��AFVCC;  OverBuf[0].4λ��VPP;
*  OverBuf[0]�ǵ�ǰ����ֵ��
*  OverBuf[1]�ǵ�ǰ����ֵ���޹���ʱ�����ϴ�ֵ
*  OverBuf[2]��OverBuf[1]��һ�ι���ֵ��
OVER-C1=AVDD��OVER-C2=DOVDD��OVER-C3=DVDD��OVER-C4=AFVCC��OVER-C5=VPP	
*/

/// @brief ��ȡ����������
/// 
/// @param OverBuf����ӦλΪ1������Ϊ0�޹�����
///					OverBuf[0].0λ��AVDD��OverBuf[0].1λ��DOVDD��OverBuf[0].2λ��DVDD��\n
///					OverBuf[0].3λ��AFVCC��OverBuf[0].4λ��VPP��\n
///					OverBuf[0]�ǵ�ǰ����ֵ��\n
///					OverBuf[1]�ǵ�ǰ����ֵ���޹���ʱ�����ϴ�ֵ��\n
///					OverBuf[2]��OverBuf[1]��һ�ι���ֵ��\n
///					OVER-C1=AVDD��OVER-C2=DOVDD��OVER-C3=DVDD��OVER-C4=AFVCC��OVER-C5=VPP
///
/// @retval DT_ERROR_OK����ȡ�ɹ�
/// @retval DT_ERROR_FAILD����ȡʧ��
/// 
/// @note ��PEϵ�к�HSϵ��֧�ָú���
DTCCM_API int _DTCALL_ GetCurrentOverload(BYTE *OverBuf, int CurDev=-1);

//set device beep time and beep count...

/// @brief ���÷�������
///
/// @param beeptime������������ʱ�䣬��λΪmS
/// @param beepcount�����������д���
DTCCM_API void _DTCALL_ SetAlarm(USHORT beeptime, BYTE beepcount, int CurDev=-1);	
//PMU....
/// @brief �˺�����֧��
DTCCM_API int _DTCALL_ ResetPMU( int CurDev=-1);

//set PMU range.... AVDD, DOVDD, DVDD, AFVCC, VPP...

/// @brief ���õ�Դ����
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
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ SetPMUSelfTestRange(BYTE range, int CurDev=-1);
//Enable PMU or not....
/// @brief �˺�����֧��
DTCCM_API BYTE _DTCALL_ SetPMUOnOff(BOOL bOn, int CurDev=-1);

//get the Current Value.
/// @brief �˺�����֧��
DTCCM_API int _DTCALL_ GetPMUData(BYTE *pBuf, BYTE length, int CurDev=-1);

/// @brief PMU��λ���п��ܵ���ϵͳ��Դ����������ģ�������ϵ硣
///
/// @retval DT_ERROR_OK��PMU��λ�ɹ�
/// @retval DT_ERROR_FAILD��PMU��λʧ��
/// @retval DT_ERROR_INTERNAL_ERROR���ڲ�����
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ PmuReset(int CurDev=-1);

/// @brief ��ȡϵͳ��Դ״̬(��ѹ������)��
///
/// @param Power��ϵͳ��Դ���ͣ��μ�ö�����͡�SYS_POWER��
/// @param Voltage����ȡ��ϵͳ��ѹֵ����λmV
/// @param Current����ȡ��ϵͳ����ֵ����λmA
/// @param iCount��Ҫ��ȡ��ϵͳ��Դ��·��
///
/// @retval DT_ERROR_OK����ȡϵͳ��Դ״̬�ɹ�
///	@retval DT_ERROR_COMM_ERROR��ͨѶ����
///
/// @see SYS_POWER
/// 
/// @note �ú�����UV910/DTLC2/UH910/UH920/UF920/PE350/PE950֧�֡�
DTCCM_API int _DTCALL_ PmuGetSysPowerVA(SYS_POWER Power[],int Voltage[],int Current[],int iCount,int CurDev=-1);

/// @brief ���õ�Դģʽ��
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param Mode����Դģʽ���μ�ö�����͡�POWER_MODE��
/// @param iCount����Դ·��
/// 
/// @retval DT_ERROR_OK�����õ�Դģʽ�ɹ�
/// @retval DT_ERROR_FAILD�����õ�Դģʽʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
/// @see POWER_MODE
/// 
/// @note �ú�����UV910/DTLC2/UH910/UH920/UF920/PE350/PE950֧�֡�
DTCCM_API int _DTCALL_ PmuSetMode(SENSOR_POWER Power[],POWER_MODE Mode[],int iCount,int CurDev=-1);

/// @brief ���õ�Դ��ѹ��
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param Voltage�����õĵ�Դ��ѹֵ����λmV
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK�����õ�Դ��ѹ�ɹ�
/// @retval DT_ERROR_FAILD�����õ�Դ��ѹʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
DTCCM_API int _DTCALL_ PmuSetVoltage(SENSOR_POWER Power[],int Voltage[],int iCount,int CurDev=-1);

/// @brief ���õ�Դ�������̡�
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param Range����Դ�������̣��μ�ö�����͡�CURRENT_RANGE��
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK�����õ�Դ�������̳ɹ�
/// @retval DT_ERROR_FAILD�����õ�Դ��������ʧ��
///
/// @see SENSOR_POWER
/// @see CURRENT_RANGE
///
/// @note �ú�����UV910/DTLC2/UH910/UH920/UF920/PE350/PE950֧�֡�
DTCCM_API int _DTCALL_ PmuSetCurrentRange(SENSOR_POWER Power[],CURRENT_RANGE Range[],int iCount,int CurDev=-1);

/// @brief ���õ�ѹ�����أ��趨ֵ(Rise)��λ:mV/mS��
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param Rise����ѹ������ֵ����λ:mV/mS
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK�����õ�ѹ�����سɹ�
/// @retval DT_ERROR_FAILD�����õ�ѹ������ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
/// 
/// @note �ú�����UV910/DTLC2/UH910/UH920/UF920/PE350/PE950֧�֡�
DTCCM_API int _DTCALL_ PmuSetRise(SENSOR_POWER Power[],int Rise[],int iCount,int CurDev=-1);



/// @brief ���õ�Դ����״̬��
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param OnOff�����õ�Դ����״̬��TRUEΪ������FALSEΪ�ر�
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK�����õ�Դ����״̬�ɹ�
/// @retval DT_ERROR_FAILD�����õ�Դ����״̬ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
DTCCM_API int _DTCALL_ PmuSetOnOff(SENSOR_POWER Power[],BOOL OnOff[],int iCount,int CurDev=-1);

/// @brief ��ȡ��Դ����״̬��
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param OnOff����ȡ��Դ����״̬��TRUEΪ������FALSEΪ�ر�
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK����ȡ��Դ����״̬�ɹ�
/// @retval DT_ERROR_FAILD����ȡ��Դ����״̬ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
DTCCM_API int _DTCALL_ PmuGetOnOff(SENSOR_POWER Power[],BOOL OnOff[],int iCount,int CurDev=-1);

/// @brief ����OCP��ʱ(����ʱ����ۼ�),�趨ֵ(Delay)��λ:mS��
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param Delay��OCP��ʱ�趨ֵ
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK������OCP��ʱ�ɹ�
/// @retval DT_ERROR_FAILD������OCP��ʱʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
/// 
/// @note �ú�����UV910/DTLC2/UH910/UH920/UF920/PE350/PE950֧�֡�
DTCCM_API int _DTCALL_ PmuSetOcpDelay(SENSOR_POWER Power[],int Delay[],int iCount,int CurDev=-1);

/// @brief ����OCP�ض�ʱ��(���жϹ��������󣬹ض�һ��ʱ��),�趨ֵ(Hold)��λ:mS��
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param Hold��OCP�ض�ʱ��
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK������OCP�ض�ʱ��ɹ�
/// @retval DT_ERROR_FAILD������OCP�ض�ʱ��ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
/// 
/// @note �ú�����UV910/DTLC2/UH910/UH920/UF920/PE350/PE950֧�֡�
DTCCM_API int _DTCALL_ PmuSetOcpHold(SENSOR_POWER Power[],int Hold[],int iCount,int CurDev=-1);

/// @brief ��ȡ����״̬,������Ϣ(State)TRUE:��������,FALSE:������
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param State����ȡ���Ĺ���״̬
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK������OCP�ض�ʱ��ɹ�
/// @retval DT_ERROR_FAILD������OCP�ض�ʱ��ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
/// 
/// @note �ú�����UV910/DTLC2/UH910/UH920/UF920/PE350/PE950֧�֡�
DTCCM_API int _DTCALL_ PmuGetOcpState(SENSOR_POWER Power[],BOOL State[],int iCount,int CurDev=-1);


//��ȡ��Դ���������ڴ���GetPMUData������GetPMUData����������Ч
//��ֵ(Current)��λ:nA

/// @brief ��ȡ��Դ������
///
/// @param Current������ֵ,��λnA
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK����ȡ��Դ�����ɹ�
/// @retval DT_ERROR_FAILD����ȡ��Դ����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @note �ú�����PE910/PE910D/HV910/HV910D/UV910/DTLC2/UH910֧�֡�
DTCCM_API int _DTCALL_ PmuGetCurrent(int Current[],int iCount=5,int CurDev=-1);

/// @brief ���ù��������ĵ�������,�趨ֵ(CurrentLimit)��λ:mA��
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param CurrentLimit�����ù��������ĵ�������ֵ����λmA
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK�����ù��������ĵ������Ƴɹ�
/// @retval DT_ERROR_FAILD�����ù��������ĵ�������ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
DTCCM_API int _DTCALL_ PmuSetOcpCurrentLimit(SENSOR_POWER Power[],int CurrentLimit[],int iCount,int CurDev=-1);

/// @brief ���õ����ɼ��ٶȣ��趨ֵ(SampleSpeed)10-200��
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param SampleSpeed�������ɼ��ٶȣ���Χ10-200
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK�����õ����ɼ��ٶȳɹ�
/// @retval DT_ERROR_FAILD�����õ����ɼ��ٶ�ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
/// 
/// @note �ú�����UV910/DTLC2/UH910/UH920/UF920/PE350/PE950֧�֡�
DTCCM_API int _DTCALL_ PmuSetSampleSpeed(SENSOR_POWER Power[],int SampleSpeed[],int iCount,int CurDev=-1);

//set sensor current limit. max_100ma = 1, maxium current is 100mA. else 300mA.
//if the current exceed the limit, the system will beep ...

/// @brief ��������ֵ
///
/// @param max_100ma��Ϊ1�������ֵΪ100mA��Ϊ0�������ֵΪ300mA
DTCCM_API void _DTCALL_ SetSensorCurrentLimit(BYTE max_100ma, int CurDev=-1);

//set sensor working voltage.. 
//2011 05 14 added afvcc settings.
//default afvcc is 2.8V...

/// @brief ���õ�ѹֵ
/// 
/// @param avdd��AVDD��ѹ����ֵ���μ��궨�塰SENSOR��Դ��ѹѡ���塱
/// @param dovdd��DOVDD��ѹ����ֵ���μ��궨�塰SENSOR��Դ��ѹѡ���塱
/// @param dvdd��DVDD��ѹ����ֵ���μ��궨�塰SENSOR��Դ��ѹѡ���塱
/// @param afvcc��AFVCC��ѹ����ֵ��Ĭ������Ϊ2.8V���μ��궨�塰SENSOR��Դ��ѹѡ���塱
DTCCM_API void _DTCALL_ SetSensorVoltage(BYTE avdd, BYTE dovdd, BYTE dvdd, BYTE afvcc=AFVCC_28, int CurDev=-1);

//Sensor Power (AVDD DOVDD DVDD AFVCC) / VPP on or off....

/// @brief ���õ�Դ��ѹ���ء�
///
/// @param bSensorPowerOn��AVDD��DOVDD��DVDD��AFVCC��ѹ���أ�ΪTRUEȫ��������ΪFALSEȫ���ر�
/// @param bVPPOn��VPP��ѹ���أ�ΪTRUE������ΪFALSE�ر�
DTCCM_API BYTE _DTCALL_ SetSensorPowerOnOff(BOOL bSensorPowerOn, BOOL bVPPOn = 0, int CurDev=-1);

//sensor power on or off...
//BYTE SetSensorPowerOnOff(BOOL bOn, int CurDev=-1);
//VPP voltage 0.5-9V

/// @brief ����VPP��ѹֵ��
///
/// @param vol��VPP��ѹ����ֵ����λV
/// 
/// @retval 0������ʧ��
/// @retval 1�����óɹ�
DTCCM_API BYTE _DTCALL_ SetSensorVPPVoltage(double vol, int CurDev=-1);

////only useful in PE320/PE820/PE920 voltage setup all at one time
//unit is mv.
//if avdd set to 3.3V, here should set avdd parameter to 3300(mv).

/// @brief ���õ�ѹֵ��
/// 
/// @param avdd��AVDD����ֵ����λmV
/// @param dovdd��DOVDD����ֵ����λmV
/// @param dvdd��DVDD����ֵ����λmV
/// @param afvcc��AFVCC����ֵ����λmV
/// @param vpp��VPP����ֵ,��λmV
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

/// @brief ���õ���ͨ����ѹֵ��
/// 
/// @param channel������ͨ����0ΪAVDD��1ΪDOVDD��2ΪDVDD��3ΪAFVCC��4ΪVPP
/// @param mv�����õĵ�ѹֵ����λmV
DTCCM_API BOOL _DTCALL_ SetDPSInChannel(BYTE channel, double mv, int CurDev=-1);

//only useful in PE320/PE820/PE920 setup power switch all at once....
//avdd_sw 1:avdd on; 0:avdd off
//dovdd_sw 1:dovdd on; 0: dovdd off
//dvdd_sw 1:dvdd on; 0:dvdd off
//afvcc_sw 1:afvcc on; 0: afvccoff.
//vpp_sw 1:vpp on; 0:vpp off

/// @brief ���õ�Դ����״̬��
/// 
/// @param avdd_sw��AVDD���أ�ΪTRUE������ΪFALSE�ر�
/// @param dovdd_sw��DOVDD���أ�ΪTRUE������ΪFALSE�ر�
/// @param dvdd_sw��DVDD���أ�ΪTRUE������ΪFALSE�ر�
/// @param afvcc_sw��AFVCC���أ�ΪTRUE������ΪFALSE�ر�
/// @param vpp_sw��VPP���أ�ΪTRUE������ΪFALSE�ر�
DTCCM_API void _DTCALL_ SetDPSOnOff(BOOL avdd_sw, BOOL dovdd_sw, BOOL dvdd_sw, BOOL afvcc_sw, BOOL vpp_sw, int CurDev=-1);

//set receiver buffer voltage.
//this should set to same as DOVDD normally, but you can set it to your need...
//this can be used to remove noise problem....
//����DOVDD
/// @brief �˺�����֧��
DTCCM_API void _DTCALL_ SetBufIOVoltage(BYTE bufio, int CurDev=-1);

/// @brief ��ȡ��Դ��ѹ������ܻ�ȡ��⵽�ģ�����ʹ�ü�⵽�����ݣ����򷵻ص�ѹ����ֵ��
///
/// @param Power����Դ���ͣ��μ�ö�����͡�SENSOR_POWER��
/// @param Voltage����ȡ�ĵ�Դ��ѹֵ����λmV
/// @param iCount����Դ·��
///
/// @retval DT_ERROR_OK�����õ�Դ��ѹ�ɹ�
/// @retval DT_ERROR_FAILD�����õ�Դ��ѹʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
/// @retval DT_ERROR_PARAMETER_OUT_OF_BOUND�����������˷�Χ
///
/// @see SENSOR_POWER
DTCCM_API int _DTCALL_ PmuGetVoltage(SENSOR_POWER Power[],int Voltage[],int iCount,int CurDev=-1);
/** @} */ // end of group5

/******************************************************************************
��ʼ�����������
******************************************************************************/
/** @defgroup group6 ��ʼ���������


* @{

*/
/// @brief ö���豸������豸�����豸����
///
/// @param DeviceName��ö�ٵ��豸��
/// @param iDeviceNumMax��ö���豸��������
/// @param pDeviceNum��ö�ٵ��豸��
///
/// @retval DT_ERROR_OK��ö�ٲ����ɹ�
/// @retval DT_ERROR_FAILED:ö�ٲ���ʧ��
/// @retval DT_ERROR_INTERNAL_ERROR:�ڲ�����
///
/// @note ��ȡ���豸�����ַ�����Ҫ�û��������GlobalFree()����ͷš�
DTCCM_API int _DTCALL_ EnumerateDevice(char *DeviceName[],int iDeviceNumMax,int *pDeviceNum);

/// @brief ���豸��ֻ�д򿪳ɹ����豸���ܲ���;�豸���������ID��Ӧ����iDevID=1 �򴴽��豸����m_device[1]��iDevID=0 �򴴽��豸����m_device[0]��
///
/// @param pszDeviceName�����豸������
/// @param pDevID�����ش��豸��ID��
///
/// @retval DT_ERROR_OK�����豸�ɹ�
/// @retval DT_ERROR_FAILD�����豸ʧ��
/// @retval DT_ERROR_INTERNAL_ERROR���ڲ�����
/// @retval DT_ERROR_PARAMETER_INVALID��������Ч
DTCCM_API int _DTCALL_ OpenDevice(const char *pszDeviceName,int *pDevID,int CurDev=0);

/****************************************
Name��bOpenDevice
Function: Open the device instance for use
Parameters��CurDev current Device Number.default is -1.means to notify the sdk to use default demokit.
            CurDev = -1, Default
			CurDev = 0, DemoKit #1
			CurDev = 1, DemoKit #2
before you control the usb device ,you should create this.then the link to usb created....
****************************************/

/// @brief �����豸����
/// 
/// @retval 1�������ɹ�
/// @retval 0������ʧ��
DTCCM_API int _DTCALL_ bCreatDeviceObject( int CurDev=-1);




/****************************************
Name��bDeleteDevice
Function: delete the device instance if you don't use
Parameters��CurDev
CurDev = -1, Default
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
before you exit the control of usb device, you should delete this 
****************************************/

/// @brief ɾ���豸����
DTCCM_API void _DTCALL_ bDeleteDeviceObject( int CurDev=-1);

/// @brief ���������豸��usb3.0�豸��Ч
///
/// @retval DT_ERROR_OK�����豸�ɹ�
/// @retval DT_ERROR_FAILD�����豸ʧ��
DTCCM_API int _DTCALL_ DeviceReset(int CurDev=-1);

//////////////////////////////////////////////////////////////////////////
/*
Name :SetCurrentDeviceObject
Function : Set The default Device to your need.
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
//if have two demokit. just set current device to your need...

/// @brief ������Ҫ���豸����ͨ��ID�Ŷ�Ӧ��
DTCCM_API void _DTCALL_ SetCurrentDeviceObject( int CurDev = 0);

//////////////////////////////////////////////////////////////////////////
//check the current device is open or not.....
/*
Name :bCheckDeviceObject
Function : Check the current Device is created or not...
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief ��鵱ǰ�豸�Ƿ��
/// 
/// @retval TRUE����ǰ�豸��
/// @retval FALSE����ǰ�豸û�д�
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
/// @brief ����豸�Ƿ���ڲ����Ƿ��ʼ���豸
/// 
/// @param bInit��ΪTRUE����豸�Ƿ���ڲ��ҳ�ʼ���豸��ΪFalse������豸�Ƿ����
/// 
/// @retval TRUE�������ɹ�
/// @retval FALSE������ʧ��
DTCCM_API BOOL _DTCALL_ bFX2IsMe(BOOL bInit = TRUE, int CurDev=-1);


//get key info...
/*
Function : GetKey
return the key input...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief ��ȡ�豸�ϰ�ť�İ���ֵ��
///
/// @retval �����豸�ϰ�ť�İ���ֵ
DTCCM_API WORD _DTCALL_ GetKey( int CurDev=-1);     
/** @} */ // end of group6

/******************************************************************************
AF���
******************************************************************************/

/** @defgroup group7 AF���


* @{

*/

//AF write /read.
//value:read value
//return TRUE:success;FALSE:fail
//this function is not working properly now.don't call this..
/// @brief �˺�����֧��
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
/// @brief �˺�����֧��
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

/// @brief ��ȡ��ǰAFоƬ��������ַ��
///
/// @retval ���ص�ǰAFоƬ��������ַ
DTCCM_API USHORT _DTCALL_ GetAFAddr( int CurDev=-1);

//find the AF device use 0x18 or 0x1c.
/*
Function : bFindAFDevice :auto search the motor AF IC 
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/

/// @brief ����AF�����е�D/AоƬ��
///
/// @retval TRUE������AF�����е�D/AоƬ�ɹ�
/// @retval FALSE������AF�����е�D/AоƬʧ��
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

/// @brief ����AF������D/A�����ֵ��
///
/// @param value�����õ�AF������D/A���ֵ
/// @param mode��AF����IC��ģʽ
///
/// @retval TRUE������AF������D/A�����ֵ�ɹ�
/// @retval FALSE������AF������D/A�����ֵʧ��
DTCCM_API BOOL _DTCALL_ bWriteAFValue(USHORT value, BYTE mode = 0, int CurDev=-1);
//set AF address such as 0x18 or 0x1c.
/*
Function : SetAFAddr :
Set motor AF IC address. normally is 0x18 or 0x1c...
CurDev = -1, Default.(Set by SetCurrentDeviceObject())
CurDev = 0, DemoKit #1
CurDev = 1, DemoKit #2
*/
/// @brief ����AF������������ַ��
///
/// @param addr������AF������D/A������ַ
DTCCM_API void _DTCALL_ SetAFAddr(USHORT addr, int CurDev=-1);

/// @brief ��ȡAF������D/AоƬ�ͺź�������ַ��
///
/// @retval ����AF������D/AоƬ�ͺ�
DTCCM_API BYTE GetAFDevType(int CurDev = -1);

/// @brief ����AF������D/AоƬ�ͺš�
///
/// @param type������AF������D/AоƬ�ͺ�
DTCCM_API void SetAFDevType(BYTE type, int CurDev = -1);

/** @} */ // end of group7

/****************************************************************************************
LC/OS���
****************************************************************************************/

/** @defgroup group8 LC/OS���


* @{

*/

//OS test....
/// @brief OS�������á�
/// 
/// @param osmaskl����Ч�ܽű�ʶ��ÿbit��Ӧһ���ܽţ������ЩbitΪ1����ʾ��Ӧ�ĹܽŽ��������
/// @param osmaskh����Ч�ܽű�ʶ��ÿbit��Ӧһ���ܽţ������ЩbitΪ1����ʾ��Ӧ�ĹܽŽ��������
/// @param kc�����ƿ�忪�أ�Ϊ1�򿪿�䣬Ϊ0�رտ��
/// @param oseasy��OS�򵥲��ԣ���Ϊ0ʱMCU�͸��жϺ��͵�AP
/// @param openStd��OS��·��׼ֵ
/// @param shortStd��OS��·��׼ֵ
/// 
/// @retval DT_ERROR_OK��OS���Բ������óɹ�
/// @retval DT_ERROR_FAILD��OS���Բ�������ʧ��
/// 
/// @note ��֧��HV910/HV910D/PE910/PE910D
DTCCM_API int _DTCALL_ DTOS_OpenTest(ULONG osmaskl, ULONG osmaskh, BYTE kc, BYTE oseasy, USHORT openStd, USHORT shortStd, int CurDev=-1);

//reset OS 
/// @brief ��λOSģ��
DTCCM_API void _DTCALL_ DTOS_Reset( int CurDev=-1);

//return -3 communication error...
//return -2 not finished...
//return -1 no error...
//return 0 no error...
//else return OS result 

/// @brief ����OS���Խ����
/// 
/// @param pResult������·���Խ��
/// @param MaxWaitms������OS�������ȴ�ʱ��
/// 
/// @note ��֧��HV910/HV910D/PE910/PE910D
DTCCM_API int _DTCALL_ DTOS_WaitTestFinished(BYTE* pResult, USHORT MaxWaitms, int CurDev=-1);
//Current overload....


//set to image mode or dtos mode...
//for HV910 . mode = 1, dtos mode; mode = 0, image mode...
//other system , this is no use...

/// @brief ���ý���ͼ��ģʽ����OSģʽ��
/// 
/// @param mode��=1��OSģʽ��=0��ͼ��ģʽ
/// 
/// @note ��֧��HV910/HV910D/PE910/PE910D
DTCCM_API void _DTCALL_ SetWorkMode(BYTE mode, int CurDev=-1);


/// @brief LC/OS���Բ������á�
/// 
/// @param Command�������룬�μ��궨�塰OS/LC�������ö��塱
/// @param IoMask����Ч�ܽű�ʶλ��ÿ�ֽڵ�ÿbit��Ӧһ���ܽţ������ЩbitΪ1����ʾ��Ӧ�ĹܽŽ��������
/// @param PinNum���ܽ������������IoMask�����С��һ�������IoMask���ֽ���Ϊ��PinNum/8+(PinNum%8!=0)
///
/// @retval DT_ERROR_OK��LC/OS���Բ������óɹ�
/// @retval DT_ERROR_FAILD��LC/OS���Բ�������ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ LC_OS_CommandConfig(DWORD Command, UCHAR IoMask[], int PinNum, int CurDev=-1);


/// @brief OS���Բ������á�
///
/// @param Voltage�����Ե�ѹ����λuV
/// @param HighLimit��Open���Ա�׼���飬����֮ǰӦ�ð�ÿһ������pin�Ŀ�·��׼��ʼ���ã���λuV
/// @param LowLimit��Short���Ա�׼���飬����֮ǰӦ�ð�ÿһ������pin�Ŀ�·��׼��ʼ���ã���λuV
/// @param PinNum���ܽ������������HighLimit��LowLimit�����С
/// @param PowerCurrent����Դpin��������λuA
/// @param GpioCurrent��GPIOpin��������λuA
///
/// @retval DT_ERROR_OK��OS���Բ������óɹ�
/// @retval DT_ERROR_FAILD��OS���Բ�������ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ OS_Config(int Voltage, int HighLimit[], int LowLimit[], int PinNum, int PowerCurrent, int GpioCurrent, int CurDev=-1);


/// @brief OS���Խ����ȡ��
///
/// @param VoltageH������pos���Խ������λuV
/// @param VoltageH������pos���Խ������λuV
/// @param Result������·���Խ�����μ��궨�塰OS���Խ�����塱
/// @param PosEn���������ʹ�� 
/// @param NegEn���������ʹ��
/// @param PinNum���ܽ������������VoltageH��VoltageL��Result�����С
/// 
/// @retval DT_ERROR_OK��OS���Խ����ȡ�ɹ�
/// @retval DT_ERROR_FAILD��OS���Խ����ȡʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ OS_Read(int VoltageH[], int VoltageL[], UCHAR Result[], BOOL PosEn, BOOL NegEn, int PinNum, int CurDev=-1);

/// @brief LC���Բ������á�
///
/// @param Voltage��LC���Ե�ѹ����λmV
/// @param Range��LC�������ã�RangeΪ0������1uA��RangeΪ1������10nA
///
/// @retval DT_ERROR_OK��LC�����������óɹ�
/// @retval DT_ERROR_FAILD��LC���Բ�������ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ LC_Config(USHORT Voltage, UCHAR Range, int CurDev=-1);

/// @brief LC���Խ����ȡ��
///
/// @param CurrentH��������Խ����λnA
/// @param CurrentL��������Խ����λnA
/// @param PinNum���ܽ������������CurrentH��CurrentL�������С
///
/// @retval DT_ERROR_OK��LC���Խ����ȡ�ɹ�
/// @retval DT_ERROR_FAILD��LC���Խ����ȡʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ LC_Read(ULONG CurrentH[],ULONG CurrentL[],int PinNum,int CurDev=-1);

/// @brief ����״ֵ̬��ȡ��
///
/// @param Result�����ؿ���״ֵ̬
/// @param PinNum���ܽ������������CurrentH��CurrentL�������С
///
/// @retval DT_ERROR_OK��LC����״ֵ̬��ȡ�ɹ�
/// @retval DT_ERROR_FAILD��LC����״ֵ̬��ȡʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ LC_ReadSwitch(UCHAR Result[],int PinNum,int CurDev=-1);
/** @} */ // end of group8

/** @defgroup group9 ��չIO


* @{

*/
/************************************************************************
��չIO                                                                     
************************************************************************/
/// @brief �����ⲿ��չ��3.3V��ѹ�����
///
/// @param bEnable����չ��ѹ���ʹ��
///
/// @retval DT_ERROR_OK�������ⲿ��չ��3.3V��ѹ����ɹ�
/// @retval DT_ERROR_FAILD�������ⲿ��չ��3.3V��ѹ���ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetExtPowerEnable(BOOL bEnable,int CurDev=-1);

/// @brief �����ⲿ��չ��ʱ�������
///
/// @param bOnOff��ʹ��ʱ�����
/// @param uHundKhz������ʱ�����ֵ,��λKhz
///
/// @retval DT_ERROR_OK�������ⲿ��չʱ������ɹ�
/// @retval DT_ERROR_FAILD�������ⲿ��չʱ�����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetExtClock(BOOL bOnOff,USHORT uHundKhz,int CurDev=-1);

/// @brief �����ⲿ��չGPIOģʽ��
///
/// @param Pin[]��GPIO��ţ��μ��궨�塰EXT_GPIO��
/// @param Mode[]��ģʽ���ã��μ�ö�����͡�EXT_GPIO_MODE��
/// @param iCount������IO����
///
/// @retval DT_ERROR_OK�������ⲿ��չGPIOģʽ�ɹ�
/// @retval DT_ERROR_FAILD�������ⲿ��չGPIOģʽʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetExtIoMode(EXT_GPIO Pin[],EXT_GPIO_MODE Mode[],int iCount,int CurDev=-1);

/// @brief �㶨��ƽ���ģʽʱ�����ⲿ��չGPIO��ƽ��
///
/// @param Pin[]��GPIO��ţ��μ��궨�塰EXT_GPIO��
/// @param Level[]��GPIO�ĵ�ƽֵ��FALSEΪ�͵�ƽ��TRUEΪ�ߵ�ƽ
/// @param iCount������IO����
///
/// @retval DT_ERROR_OK�������ⲿ��չGPIO��ƽ�ɹ�
/// @retval DT_ERROR_FAILD�������ⲿ��չGPIO��ƽʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetExtIoLevel(EXT_GPIO Pin[],BOOL Level[],int iCount,int CurDev=-1);

/// @brief ��ȡ�ⲿ��չGPIO�ĵ�ƽ��
/// 
/// @param Pin[]��GPIO��ţ��μ��궨�塰EXT_GPIO��
/// @param Level[]��GPIO�ĵ�ƽֵ��FALSEΪ�͵�ƽ��TRUEΪ�ߵ�ƽ
/// @param iCount������IO����
///
/// @retval DT_ERROR_OK����ȡ�ⲿ��չGPIO��ƽ�ɹ�
/// @retval DT_ERROR_FAILD����ȡ�ⲿ��չGPIO��ƽʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ GetExtIoLevel(EXT_GPIO Pin[],BOOL Level[],int iCount,int CurDev=-1);

/// @brief ��չGPIOΪ�ߵ͵�ƽ�������ʱ���ߡ��͵�ƽʱ�����á�
/// 
/// @param Pin[]��GPIO��ţ��μ��궨�塰EXT_GPIO��
/// @param HighLevelTime[]����Ӧ��չGPIO�ߵ�ƽʱ�䣬��λus
/// @param LowLevelTime[]����Ӧ��չGPIO�͵�ƽʱ�䣬��λus
/// @param iCount������IO����
///
/// @retval DT_ERROR_OK�������ⲿ��չGPIO�ߵ͵�ƽʱ��ɹ�
/// @DT_ERROR_FAILD�����ⲿ��չGPIO�ߵ͵�ƽʱ��ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetExtIoLevelTime(EXT_GPIO Pin[],int HighLevelTime[],int LowLevelTime[],int iCount,int CurDev=-1);

/// @brief �ⲿ��չI2Cд
///
/// @param uDevAddr���豸��ַ
/// @param uRegAddr���豸�Ĵ���
/// @param uRegAddrSize���Ĵ�����ַ���ֽ���
/// @param pData��д��Ĵ��������ݿ�
/// @param uSize��д��Ĵ��������ݿ��С,���Ϊ60���ֽ�
/// 
/// @retval DT_ERROR_OK��д�ɹ�
/// @retval DT_ERROR_FAILD��дʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ ExtI2cWrite(UCHAR uDevAddr,USHORT uRegAddr,UCHAR uRegAddrSize,BYTE *pData,USHORT uSize,int CurDev=-1);

/// @brief �ⲿ��չI2C��
///
/// @param uDevAddr���豸��ַ
/// @param uRegAddr���豸�Ĵ���
/// @param uRegAddrSize���Ĵ�����ַ���ֽ���
/// @param pData�����Ĵ��������ݿ�
/// @param uSize�����Ĵ��������ݿ��С,���Ϊ60���ֽ�
/// @param bNoStop���Ƿ񷢳�I2C��STOP���һ�������Ĭ��ΪFALSE��bNoStop=TRUE��ʾд�Ĺ��̲�����I2C��ֹͣ���bNoStop=FALSE��I2C��ֹͣ����
/// 
/// @retval DT_ERROR_OK�����ɹ�
/// @retval DT_ERROR_FAILD����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ ExtI2cRead(UCHAR uDevAddr,USHORT uRegAddr,UCHAR uRegAddrSize,BYTE *pData,USHORT uSize,BOOL bNoStop=FALSE,int CurDev=-1);

/// @brief �����ⲿ��������ӿڵ�ƽ
/// 
/// @param iTriggerOutPin����������ӿڱ�ţ���ǰ��Ÿ����Ʒ�ṩһ���������IO��
/// @param bTriggerOutFollowEnable����������ӿڸ���ʹ���źţ���Ϊ1�����TriggerIn�źŵ�ƽ��Ϊ0��Ϊ���õ�ƽֵ
/// @param bLevel����ƽֵ��0Ϊ����͵�ƽ��1Ϊ����ߵ�ƽ��
///
/// @retval DT_ERROR_OK�����ɹ�
/// @retval DT_ERROR_FAILD����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ SetTriggerOutLevel(int iTriggerOutPin,BOOL bFollowTrigIn,BOOL bLevel,int CurDev=-1);

/// @brief ��ȡ�ⲿ��������ӿڵ�ƽ
/// 
/// @param iTriggerInPin����������ӿڱ�ţ���ǰ��Ÿ����Ʒ�ṩһ���������IO��
/// @param pLevel�����صĵ�ƽֵ��0Ϊ����͵�ƽ��1Ϊ����ߵ�ƽ��
///
/// @retval DT_ERROR_OK�����ɹ�
/// @retval DT_ERROR_FAILD����ʧ��
/// @retval DT_ERROR_COMM_ERROR��ͨѶ����
DTCCM_API int _DTCALL_ GetTriggerInLevel(int iTriggerInPin,BOOL *pLevel,int CurDev=-1);


/** @} */ // end of group9

/*************************************************************************
�¶ȴ��������
*************************************************************************/

// �����¶ȴ������������¶�
DTCCM_API int _DTCALL_ SetTempRange(int iUpperLimit, int iLowerLimit, BOOL bEnable,int CurDev=-1);

// ��ȡ��ǰ�¶�ֵ
DTCCM_API int _DTCALL_ GetCurrentTemp(int *pTemp,int CurDev=-1);

// ��ȡ��ǰ���õ��¶ȷ�Χ
DTCCM_API int _DTCALL_ GetTempRange(int *pUpperLimit, int *pLowLimit,int CurDev=-1);

// �ڲ�״̬��Ϣ����
DTCCM_API int _DTCALL_ ShowInternalStatusDialog(HWND hwnd,int CurDev=-1);

DTCCM_API int _DTCALL_ ShowFrameBufferControlDialog(HWND hwnd ,HWND *pRethwnd,int CurDev=-1);

DTCCM_API int _DTCALL_ ShowPropertyPage(HWND hwnd ,HWND *pRethwnd,int CurDev=-1);

/****************************************************************************************
����
****************************************************************************************/
// ��չ���ƽӿ�
// dwCtrl:	�����룬�����������ඨ��
// dwParam:	��������ز���
// pIn:		��ȡ������
// pInSize:	��ȡ���ݵĴ�С���ֽ�����������ָ��Ҫ���ȡ���ֽ���������ɹ�������ʵ�ʶ�ȡ���ֽ���
// pOut:	д�������
// pOutSize:д�����ݵĴ�С���ֽ�����������ָ��Ҫ��д����ֽ���������ɹ�������ʵ��д����ֽ���
DTCCM_API int _DTCALL_ ExCtrl(DWORD dwCtrl,DWORD dwParam,PVOID pIn,int *pInSize,PVOID pOut,int *pOutSize,int CurDev=-1);

#endif