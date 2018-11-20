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
 
//!  ������ͼ��ɼ���װ��װ��
/*! �������ý�����WIN7����ϵͳ�� 4G�����ڴ棬 INTEL I3���ϴ�����
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
	//!  �򿪹�װ�� ��ִ����������֮�����򿪹�װ
	/*! �����ڳ���һ��ʼ��ʱ��򿪹�װ���������ʱ�رչ�װ
	\param[in] usPID USB3.0�豸PID�� �˲�����ʱ��������̶���Ϊ0
	\param[in] usVID USB3.0�豸VID�� �˲�����ʱ��������̶���Ϊ0
	\param[in] pstrFriendlyName USB3.0�豸�������ƣ� �˲�����ʱ��������̶���Ϊ0
	\param[in] ucDeviceIndex USB3.0�豸��ţ� �˲�����ʱ��������̶���Ϊ0xFF
	\param[in] puiKey ��װΨһ���кţ� ��puiKey==NULL,���������ӵ����Ե���һ��װ�� 
	                         ��puiKey��ָ�� unsigned int[4]�����ָ��ʱ�������򿪺��������к�ƥ��Ĺ�װ��
							 �˲�����Ҫ����1���������Ӷ����װ�������
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3CloseDevice()�� _HisFX3Platform_ErrorCode
	*/
	int HisFX3OpenDevice(unsigned short usPID=0, unsigned short usVID=0, char* pstrFriendlyName=NULL, unsigned char ucDeviceIndex=0xFF, unsigned int* puiKey = NULL, unsigned int uiTransformDelay = 110);

	//!  ��ȡ��װ����
	/*! 
	\return ��װ����
	*/
	unsigned int HisFX3DeviceCount();

	//!  �رչ�װ
	/*! 
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3OpenDevice()�� _HisFX3Platform_ErrorCode
	*/
	int HisFX3CloseDevice();

	//! ͨ��1��ʼ��ͼ
	/*! �����˫�㹤װ���˺�����������ͨ��1
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa _HisFX3_PreviewStruct�� HisFX3StopPreview()�� _HisFX3Platform_ErrorCode
	*/
	int HisFX3StartPreview(struct _HisFX3_PreviewStruct* pstPrama);

	//! ͨ��1ֹͣ��ͼ
	/*! �����˫�㹤װ���˺�����������ͨ��1
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()�� _HisFX3Platform_ErrorCode
	*/
	int HisFX3StopPreview();

	//! ͨ��2��ʼ��ͼ
	/*! ֻ����˫�㹤װ�ϣ� �˺�������Ч
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa _HisFX3_PreviewStruct�� HisFX3StopPreview_S2()�� _HisFX3Platform_ErrorCode
	*/
	int HisFX3StartPreview_S2(struct _HisFX3_PreviewStruct* pstPrama);

	//! ͨ��2ֹͣ��ͼ
	/*! ֻ����˫�㹤װ�ϣ� �˺�������Ч
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview_S2()�� _HisFX3Platform_ErrorCode
	*/
	int HisFX3StopPreview_S2();

	int reStartPreview(struct _HisFX3_PreviewStruct* pstPrama);

	//! ͨ��1ץͼ
	/*! �����˫�㹤װ���˺�����������ͨ��1
	\param[out] ppucBuffer ����ͼ�����ݵ�bufferָ�룬������_aligned_malloc(size, _HisCacheLine_Aligned)�����ڴ�ռ䡣
										  �������NULL, ��ֻ�᷵��ui64FramIndex��
	\param[in] uiBufBytes ppucBuffer������ڴ��С���������һ֡ͼ��������ڴ��С
	\param[out] ui64FramIndex ��ǰ֡��������ʼ��ͼ֮��ĵ�һ֡Ϊ1���Դ�����
	\param[in] uiTimeOut ��ȡ�µ�һ֡��timeoutʱ��
	\param[in] uiConvertFlag 1:[raw10][raw12] ����[width*height*5/4][width*height*3/2] byte  0: [raw10][raw12] ����width*height byte
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()�� _HisFX3Platform_ErrorCode
	*/
	int HisFX3GrabFrame(unsigned char **ppucBuffer, unsigned int uiBufBytes, unsigned __int64& ui64FramIndex, unsigned int uiTimeOut = 3000, unsigned int uiConvertFlag=0);

	//! ͨ��2ץͼ
	/*! �����˫�㹤װ���˺�����������ͨ��2
	\param[out] ppucBuffer ����ͼ�����ݵ�bufferָ�룬������_aligned_malloc(size, _HisCacheLine_Aligned)�����ڴ�ռ䡣
										  �������NULL, ��ֻ�᷵��ui64FramIndex��
	\param[in] uiBufBytes ppucBuffer������ڴ��С���������һ֡ͼ��������ڴ��С
	\param[out] ui64FramIndex ��ǰ֡��������ʼ��ͼ֮��ĵ�һ֡Ϊ1���Դ�����
	\param[in] uiTimeOut ��ȡ�µ�һ֡��timeoutʱ��
	\param[in] uiConvertFlag 1:[raw10][raw12] ����[width*height*5/4][width*height*3/2] byte  0: [raw10][raw12] ����width*height byte
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3StartPreview()�� _HisFX3Platform_ErrorCode
	*/
	int HisFX3GrabFrame_S2(unsigned char **ppucBuffer, unsigned int uiBufBytes, unsigned __int64& ui64FramIndex, unsigned int uiTimeOut = 3000, unsigned int uiConvertFlag=0);

	//! ��װ�Ƿ��Ѵ�
	/*! 
	\return true: �Ѵ�  false: ��δ��
	\sa HisFX3isstart()�� HisFX3OpenDevice, HisFX3CloseDevice
	*/
	bool HisFX3isopen();

	//! ͨ��1�������Ƿ��ѿ���
	/*! 
	\return true: �ѿ���  false: δ����
	\sa HisFX3isopen()�� HisFX3StartPreview(), HisFX3StopPreview()
	*/ 
	bool HisFX3isstart();

	//! ͨ��2�������Ƿ��ѿ���
	/*!  ֻ����˫�㹤װ�ϣ� �˺�������Ч
	\return true: �ѿ���  false: δ����
	\sa HisFX3isopen()�� HisFX3StartPreview_S2(), HisFX3StopPreview_S2()
	*/
	bool HisFX3isstart_S2();

	//! ��ȡ��ǰopen��װ��Ψһ���к�
	/*!  ֻ���ڳɹ�����HisFX3OpenDevice֮����ܵ��ô˺���
	\param puiKey ָ��unsigned int[4], ��������ɹ��� �Ḵ���豸Ψһ���кŵ�������ռ�
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa getHardwareKeyList, HisFX3OpenDevice()�� HisFX3CloseDevice(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetHardwareKey(unsigned int* puiKey);

	//! ��ȡ���������й�װ��Ψһ���к�
	/*!  ֻ����HisFX3OpenDevice֮ǰ���ܵ��ô˺���
	\param[out] puiKey ָ��unsigned int, ��������ɹ��� �Ḵ���豸Ψһ���кŵ�������ռ�
	\param[out] uiKeyCount  �����ж��������кţ�һ�����к���4��unsigned int��ʾ
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3GetHardwareKey, HisFX3OpenDevice()�� HisFX3CloseDevice(), _HisFX3Platform_ErrorCode
	*/
	int getHardwareKeyList(unsigned int* puiKeyList, unsigned int& uiKeyCount);
	
	//! ����ͨ��1 RST�ź�
	/*!  
	\param bPullHigh true: ��Ϊ�ߵ�ƽ  false:��Ϊ�͵�ƽ
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3PullPWND(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullReset(bool bPullHigh);

	//! ����ͨ��2 RST�ź�
	/*!    ֻ����˫�㹤װ�ϣ� �˺�������Ч
	\param bPullHigh true: ��Ϊ�ߵ�ƽ  false:��Ϊ�͵�ƽ
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3PullPWND_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullReset_S2(bool bPullHigh);

	//! ����ͨ��1 PWDN�ź�
	/*!  
	\param bPullHigh true: ��Ϊ�ߵ�ƽ  false:��Ϊ�͵�ƽ
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3PullReset(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullPWND(bool bPullHigh);

	//! ����ͨ��2 PWDN�ź�
	/*!    ֻ����˫�㹤װ�ϣ� �˺�������Ч
	\param bPullHigh true: ��Ϊ�ߵ�ƽ  false:��Ϊ�͵�ƽ
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3PullReset_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PullPWND_S2(bool bPullHigh);

	//! ����дIIC
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] ui64Data Ҫд�������
	\param[in] usType �Ĵ��������ݸ�ʽ, eg:0x1608-��ʾ��ַλд��16bit, ����λд��8bit��
							 ֧�ֵĸ�ʽ:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] back  true: �ж�ACK  false:���ж�ACK(��ʱ���٣���������ȫ)
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3WriteIIC(unsigned char ucSlave, unsigned int uiReg, unsigned __int64 ui64Data, unsigned short usType, bool back=true);

	//! ����дͨ��2 IIC
	/*!    ֻ����˫�㹤װ�ϣ� �˺�������Ч
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] ui64Data Ҫд�������
	\param[in] usType �Ĵ��������ݸ�ʽ, eg:0x1608-��ʾ��ַλд��16bit, ����λд��8bit��
							 ֧�ֵĸ�ʽ:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] back  true: �ж�ACK  false:���ж�ACK(��ʱ���٣���������ȫ)
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3WriteIIC_S2(unsigned char ucSlave, unsigned int uiReg, unsigned __int64 ui64Data, unsigned short usType, bool back=true);

	//! ������IIC
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[out] pui64Data ������������
	\param[in] usType �Ĵ��������ݸ�ʽ, eg:0x1608-��ʾ��ַλд��16bit, ����λд��8bit��
							 ֧�ֵĸ�ʽ:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3ReadI2C(unsigned char ucSlave, unsigned int uiReg, unsigned __int64* pui64Data, unsigned short usType); 

	//! ������IIC(ͨ��2)
	/*!    ֻ����˫�㹤װ�ϣ� �˺�������Ч
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[out] pui64Data ������������
	\param[in] usType �Ĵ��������ݸ�ʽ, eg:0x1608-��ʾ��ַλд��16bit, ����λд��8bit��
							 ֧�ֵĸ�ʽ:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3ReadI2C_S2(unsigned char ucSlave, unsigned int uiReg, unsigned __int64* pui64Data, unsigned short usType); 

	//! ����д��IIC
	/*! 
	\param[in] uiCount  Ҫд���IIC������
	\param[in] pucSlave �豸��ַ����ָ��
	\param[in] puiReg �Ĵ�����ַ����ָ��
	\param[in] puiData ��������ָ��
	\param[in] pusType ��ʽ����ָ��, eg:0x1608-��ʾ��ַλд��16bit, ����λд��8bit��
							 ֧�ֵĸ�ʽ:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay ����֮��ļ��ʱ�䣬��λ: us
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC(), HisFX3ReadIIC(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchWriteIICNoLimit(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay=10);

	//! ����д��IIC(ͨ��2)
	/*! 
	\param[in] uiCount  Ҫд���IIC������
	\param[in] pucSlave �豸��ַ����ָ��
	\param[in] puiReg �Ĵ�����ַ����ָ��
	\param[in] puiData ��������ָ��
	\param[in] pusType ��ʽ����ָ��, eg:0x1608-��ʾ��ַλд��16bit, ����λд��8bit��
							 ֧�ֵĸ�ʽ:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay ����֮��ļ��ʱ�䣬��λ: us
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC_S2(), HisFX3ReadIIC_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchWriteIICNoLimit_S2(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay=10);
	
	//! ������ȡIIC
	/*! 
	\param[in] uiCount  Ҫд���IIC������
	\param[in] pucSlave �豸��ַ����ָ��
	\param[in] puiReg �Ĵ�����ַ����ָ��
	\param[out] puiData ��������ָ��
	\param[in] pusType ��ʽ����ָ��, eg:0x1608-��ʾ��ַλд��16bit, ����λд��8bit��
							 ֧�ֵĸ�ʽ:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay ����֮��ļ��ʱ�䣬��λ: us
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC(), HisFX3ReadIIC(), HisFX3BatchWriteIICNoLimit(), HisFX3PageWriteIIC(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchReadIICNoLimit(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay=10);
	
	//! ������ȡIIC(ͨ��2)
	/*! 
	\param[in] uiCount  Ҫд���IIC������
	\param[in] pucSlave �豸��ַ����ָ��
	\param[in] puiReg �Ĵ�����ַ����ָ��
	\param[out] puiData ��������ָ��
	\param[in] pusType ��ʽ����ָ��, eg:0x1608-��ʾ��ַλд��16bit, ����λд��8bit��
							 ֧�ֵĸ�ʽ:0x0808,0x0816,0x1608,0x1616,0x1632
	\param[in] usDelay ����֮��ļ��ʱ�䣬��λ: us
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3WriteIIC_S2(), HisFX3ReadIIC_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3BatchReadIICNoLimit_S2(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay=10);

	//! Pageд��IIC
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] uiRegSize �Ĵ�����ַ�ֽڳ��ȣ�1,2,4��ѡ
	\param[in] pucData ��������ָ��
	\param[in] uiDataSize Ҫд������ݳ��ȣ���λ:byte
	\param[in] usDelay ÿ��BYTE��ʱusDelay *0.5��ʼ������
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned short usDelay = 4);

	//! Pageģʽд��IIC(ͨ��2)
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] uiRegSize �Ĵ�����ַ�ֽڳ��ȣ�1,2,4��ѡ
	\param[in] pucData ��������ָ��
	\param[in] uiDataSize Ҫд������ݳ��ȣ���λ:byte
	\param[in] usDelay ÿ��BYTE��ʱusDelay *0.5��ʼ������
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C_S2(), HisFX3WriteI2C_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageReadIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIIC_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned short usDelay = 4);
	
	//! Pageģʽ��ȡIIC
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] uiRegSize �Ĵ�����ַ�ֽڳ��ȣ�1,2,4��ѡ
	\param[out] pucData ��������ָ��
	\param[in] uiDataSize Ҫ��ȡ�����ݳ��ȣ���λ:byte
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize);
	
	//! Pageģʽ��ȡIIC(ͨ��2)
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] uiRegSize �Ĵ�����ַ�ֽڳ��ȣ�1,2,4��ѡ
	\param[out] pucData ��������ָ��
	\param[in] uiDataSize Ҫ��ȡ�����ݳ��ȣ���λ:byte
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3ReadI2C_S2(), HisFX3WriteI2C_S2(), HisFX3BatchWriteIICNoLimit_S2(), HisFX3BatchReadIICNoLimit_S2(), HisFX3PageWriteIIC_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIIC_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize);

	//! Pageд��IIC, �޳�������(ͨ��1)
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] uiRegSize �Ĵ�����ַ�ֽڳ��ȣ�1,2,4��ѡ
	\param[in] pucData ��������ָ��
	\param[in] uiDataSize Ҫд������ݳ��ȣ���λ:byte
	\param[in] uiPageSize һ��Page�Ĵ�С����Ҫ����EEPROM�Ĺ���飬һ����128,256,512,1024...
	\param[in] usByteDelay ÿ��BYTE��ʱusDelay *0.5��ʼ������
	\param[in] uiPageDelay ÿ��Pageд��֮�����ʱ����λ:ms
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3PageWriteIIC(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIICNoLimit(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned short usByteDelay = 4, unsigned int uiPageDelay= 100);
	
	//! Pageд��IIC, �޳�������(ͨ��2)
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] uiRegSize �Ĵ�����ַ�ֽڳ��ȣ�1,2,4��ѡ
	\param[in] pucData ��������ָ��
	\param[in] uiDataSize Ҫд������ݳ��ȣ���λ:byte
	\param[in] uiPageSize һ��Page�Ĵ�С����Ҫ����EEPROM�Ĺ���飬һ����128,256,512,1024...
	\param[in] usByteDelay ÿ��BYTE��ʱusDelay *0.5��ʼ������
	\param[in] uiPageDelay ÿ��Pageд��֮�����ʱ����λ:ms
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3PageWriteIIC_S2(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageReadIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteIICNoLimit_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned short usByteDelay = 4, unsigned int uiPageDelay= 100);

	//! Pageģʽ��ȡIIC, �޳�������(ͨ��1)
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] uiRegSize �Ĵ�����ַ�ֽڳ��ȣ�1,2,4��ѡ
	\param[out] pucData ��������ָ��
	\param[in] uiDataSize Ҫ��ȡ�����ݳ��ȣ���λ:byte
	\param[in] uiPageSize һ��Page�Ĵ�С����Ҫ����EEPROM�Ĺ���飬һ����128,256,512,1024...
	\param[in] uiPageDelay ÿ��Page��ȡ֮�����ʱ����λ:ms
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3PageReadIIC(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIICNoLimit(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned int uiPageDelay = 0);

	//! Pageģʽ��ȡIIC, �޳�������(ͨ��2)
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] uiRegSize �Ĵ�����ַ�ֽڳ��ȣ�1,2,4��ѡ
	\param[out] pucData ��������ָ��
	\param[in] uiDataSize Ҫ��ȡ�����ݳ��ȣ���λ:byte
	\param[in] uiPageSize һ��Page�Ĵ�С����Ҫ����EEPROM�Ĺ���飬һ����128,256,512,1024...
	\param[in] uiPageDelay ÿ��Page��ȡ֮�����ʱ����λ:ms
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3PageReadIIC_S2(), HisFX3ReadI2C(), HisFX3WriteI2C(), HisFX3BatchWriteIICNoLimit(), HisFX3BatchReadIICNoLimit(), HisFX3PageWriteIIC(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadIICNoLimit_S2(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, unsigned int uiPageSize, unsigned int uiPageDelay = 0);

	//! Pageģʽд��SPI
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] uiRegSize �Ĵ�����ַ�ֽڳ��ȣ�1,2,4��ѡ
	\param[in] pucData ��������ָ��
	\param[in] uiDataSize Ҫд������ݳ��ȣ���λ:byte
	\param[in] bCSLow ���ò���SPIʱ��CS�źŵ�ƽ�� true:�͵�ƽ�� false:�ߵ�ƽ
	\param[in] bLowFirst true: ��λ��ǰ�� false:��λ��ǰ
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3PageReadSPI(), HisFX3WriteSPI(), HisFX3ReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageWriteSPI(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, bool bCSLow=true, bool bLowFirst=true);
	
	//! Pageģʽ��ȡSPI
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] uiRegSize �Ĵ�����ַ�ֽڳ��ȣ�1,2,4��ѡ
	\param[out] pucData ��������ָ��
	\param[in] uiDataSize Ҫд������ݳ��ȣ���λ:byte
	\param[in] bCSLow ���ò���SPIʱ��CS�źŵ�ƽ�� true:�͵�ƽ�� false:�ߵ�ƽ
	\param[in] bLowFirst true: ��λ��ǰ�� false:��λ��ǰ
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3PageWriteSPI(), HisFX3WriteSPI(), HisFX3ReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3PageReadSPI(unsigned char ucSlave, unsigned int uiReg, unsigned int uiRegSize, unsigned char* pucData, unsigned int uiDataSize, bool bCSLow=true, bool bLowFirst=true);

	//! ����дSPI
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[in] ui64Data Ҫд�������
	\param[in] usType �Ĵ��������ݸ�ʽ, eg:0x1608-��ʾ��ַλд��16bit, ����λд��8bit��
							 ֧�ֵĸ�ʽ:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] bCSLow ���ò���SPIʱ��CS�źŵ�ƽ�� true:�͵�ƽ�� false:�ߵ�ƽ
	\param[in] bLowFirst true: ��λ��ǰ�� false:��λ��ǰ
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3ReadSPI(), HisFX3PageWriteSPI(), HisFX3PageReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3WriteSPI(unsigned char ucSlave, unsigned int uiReg, unsigned __int64 ui64Data, unsigned short usType, bool bCSLow=true, bool bLowFirst=true);
	
	//! ������ȡSPI
	/*!    
	\param[in] ucSlave �ӻ��豸��ַ
	\param[in] uiReg �Ĵ�����ַ
	\param[out] pui64Data ��ȡ������
	\param[in] usType �Ĵ��������ݸ�ʽ, eg:0x1608-��ʾ��ַλд��16bit, ����λд��8bit��
							 ֧�ֵĸ�ʽ:0x0808,0x0816,0x1608,0x1616,0x1632,0x0008,0x0016,0x0032
	\param[in] bCSLow ���ò���SPIʱ��CS�źŵ�ƽ�� true:�͵�ƽ�� false:�ߵ�ƽ
	\param[in] bLowFirst true: ��λ��ǰ�� false:��λ��ǰ
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3WriteSPI(), HisFX3PageWriteSPI(), HisFX3PageReadSPI(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3ReadSPI(unsigned char ucSlave, unsigned int uiReg, unsigned __int64* pui64Data, unsigned short usType, bool bCSLow=true, bool bLowFirst=true);

	//! ���¼���API, ���鲻ʹ��
	int HisFX3BatchWriteIIC(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short usType, unsigned short usDelay=10);
	
	//! ���¼���API, ���鲻ʹ��
	int HisFX3BatchReadIIC(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short usType, unsigned short usDelay=10);
	
	//! ���¼���API, ���鲻ʹ��
	int HisFX3BatchWriteIIC_V2(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay);
	
	//! ���¼���API, ���鲻ʹ��
	int HisFX3BatchReadIIC_V2(unsigned int uiCount, unsigned char* pucSlave, unsigned int* puiReg, unsigned int* puiData, unsigned short* pusType, unsigned short usDelay);

	//! ����IICͨ���ٶ�
	/*!    
	\param[in] us1kMultiple 10KHz~1MHz��Χ�ɵ�
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3GetIICSpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetIICSpeed(unsigned short us1kMultiple);

	//! ����IICͨ���ٶ�(ͨ��2)
	/*!    
	\param[in] us1kMultiple 10KHz~1MHz��Χ�ɵ�
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3GetIICSpeed_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetIICSpeed_S2(unsigned short us1kMultiple);

	//! ��ȡ��ǰIICͨ���ٶ�
	/*!    
	\param[out] pus1kMultiple ��λ��KHz
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3SetIICSpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetIICSpeed(unsigned short* pus1kMultiple);

	//! ��ȡ��ǰIICͨ���ٶ�(ͨ��2)
	/*!    
	\param[out] pus1kMultiple ��λ��KHz
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3SetIICSpeed_S2(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetIICSpeed_S2(unsigned short* pus1kMultiple);

	//! ����SPIͨ���ٶ�
	/*!    
	\param[in] us1kMultiple 10KHz~25MHz��Χ�ɵ�, ��λ: KHz
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3GetSPISpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetSPISpeed(unsigned short us1kMultiple);

	//! ��ȡ��ǰSPIͨ���ٶ�
	/*!    
	\param[out] pus1kMultiple ��λ��KHz
	\return 0:�ɹ�  ��0:ʧ�ܵĴ������, ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3SetSPISpeed(), _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetSPISpeed(unsigned short* pus1kMultiple);

	//! ���ͨ��1�Ĵ��豸��ַ��Ӧ
	/*!    
	\param[in] ucSlave ���豸���豸��ַ
	\return 0:����Ӧ  ��0:δ��Ӧ, ��ο�_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3SlaveResponds(unsigned char ucSlave);

	//! ���ͨ��2�Ĵ��豸��ַ��Ӧ
	/*!    
	\param[in] ucSlave ���豸���豸��ַ
	\return 0:����Ӧ  ��0:δ��Ӧ, ��ο�_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3SlaveResponds_S2(unsigned char ucSlave);

	//! ����
	int HisFX3GetMIPIDataType(_HisFX3_ImageSenor_DataType* pDataType);

	//! ����5V12V��ѹ�����R5��
	/*!    
	\param[in] uiV5 0��5V�ر�  1��5V��  2��5V������
	\param[in] uiV12 0��12V�ر�  1��12V��  2��12V������
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3SetVolt, HisFX3SetVolt_S2, _HisFX3Platform_ErrorCode
	*/
	int HisFX3Set5V12V(unsigned int uiV5 = 2, unsigned int uiV12 = 2);

	//! ����ͨ��1��ѹ
	/*!    
	\param[in] flDOVDD 0.0V~3.5V��Χ�ɵ�, ʵ�������ѹ= flDOVDD *flMultiple
	\param[in] flAVDD 0.0V~3.5V��Χ�ɵ�, ʵ�������ѹ= flAVDD *flMultiple
	\param[in] flDVDD 0.0V~3.5V��Χ�ɵ�, ʵ�������ѹ= flDVDD *flMultiple
	\param[in] flAF 0.0V~3.5V��Χ�ɵ�, ʵ�������ѹ= flAF *flMultiple
	\param[in] flVFuse 0.0V~10.0V��Χ�ɵ�, ʵ�������ѹ= flVFuse *flMultiple
	\param[in] flPOW 0.0V~3.5V��Χ�ɵ���R5����R3X����R5X��, ʵ�������ѹ= flPOW *flMultiple
	\param[in] flIODD 0.0V~3.5V��Χ�ɵ����忨�ڲ�IO��ƽ����R5��, ʵ�������ѹ= flIODD *flMultiple
	\param[in] usSwitch ���õ�ѹ���أ� _HisFX3_Platform_VoltFlag��
									  eg,����AVDD��DVDD��ѹ�� _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] flMultiple ��ѹֵϵ��
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3Set5V12V, HisFX3SetVolt_S2, HisFX3GetVolt, _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetVolt(float flDOVDD=0.0f, float flAVDD=0.0f, float flDVDD=0.0f, float flAF = 0.0f, float flVFuse=0.0f, float flPOW=0.0f, float flIODD = 0.0f, unsigned short usSwitch=0xFF, float flMultiple = 0.1f);
	
	//! ����ͨ��2��ѹ
	/*!    
	\param[in] flDOVDD 0.0V~3.5V��Χ�ɵ�, ʵ�������ѹ= flDOVDD *flMultiple
	\param[in] flAVDD 0.0V~3.5V��Χ�ɵ�, ʵ�������ѹ= flAVDD *flMultiple
	\param[in] flDVDD 0.0V~3.5V��Χ�ɵ�, ʵ�������ѹ= flDVDD *flMultiple
	\param[in] flAF 0.0V~3.5V��Χ�ɵ�, ʵ�������ѹ= flAF *flMultiple
	\param[in] flVFuse 0.0V~10.0V��Χ�ɵ�, ʵ�������ѹ= flVFuse *flMultiple
	\param[in] flPOW 0.0V~3.5V��Χ�ɵ���R5��, ʵ�������ѹ= flPOW *flMultiple
	\param[in] flIODD 0.0V~3.5V��Χ�ɵ����忨�ڲ�IO��ƽ����R5��, ʵ�������ѹ= flIODD *flMultiple
	\param[in] usSwitch ���õ�ѹ���أ� _HisFX3_Platform_VoltFlag��
									  eg,����AVDD��DVDD��ѹ�� _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] flMultiple ��ѹֵϵ��
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3Set5V12V, HisFX3SetVolt, HisFX3GetVolt_S2, _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetVolt_S2(float flDOVDD=0, float flAVDD=0, float flDVDD=0, float flAF = 0, float flVFuse=0, float flPOW=0, float flIODD = 0, unsigned short usSwitch=0xFF, float flMultiple=0.1f);

	//! ��ȡͨ��1��ǰ���õ�ѹ
	/*!    
	\param[out] pflDOVDD ��ǰDOVDD���õ�ѹ
	\param[out] pflAVDD ��ǰAVDD���õ�ѹ
	\param[out] pflDVDD ��ǰDVDD���õ�ѹ
	\param[out] pflAF ��ǰAF���õ�ѹ
	\param[out] pflVFuse ��ǰVFuse���õ�ѹ
	\param[out] pflPOW ��ǰPOW���õ�ѹ
	\param[out] pflIODD ��ǰIODD���õ�ѹ
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3SetVolt,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetVolt(float* pflDOVDD=NULL, float* pflAVDD=NULL, float* pflDVDD=NULL, float* pflAF=NULL, float* pflVFuse=NULL, float* pflPOW=NULL, float* pflIODD=NULL);

	//! ��ȡͨ��2��ǰ���õ�ѹ
	/*!    
	\param[out] pflDOVDD ��ǰDOVDD���õ�ѹ
	\param[out] pflAVDD ��ǰAVDD���õ�ѹ
	\param[out] pflDVDD ��ǰDVDD���õ�ѹ
	\param[out] pflAF ��ǰAF���õ�ѹ
	\param[out] pflVFuse ��ǰVFuse���õ�ѹ
	\param[out] pflPOW ��ǰPOW���õ�ѹ
	\param[out] pflIODD ��ǰIODD���õ�ѹ
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3SetVolt_S2,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetVolt_S2(float* pflDOVDD=NULL, float* pflAVDD=NULL, float* pflDVDD=NULL, float* pflAF=NULL, float* pflVFuse=NULL, float* pflPOW=NULL, float* pflIODD=NULL);

	//! ����
	int HisFX3SetVFuseVolt(unsigned char ucVFUSE);

	//! ����
	int HisFX3GetVFuseVolt(float* pflVFUSE = NULL);

	//! ����ͨ��1 MCLKʱ��
	/*!    
	\param[in] flMCLK 0~136MHz�ɵ��� ��λ: MHz
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3GetMCLK,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetMCLK(float flMCLK);

	//! ����ͨ��2 MCLKʱ��
	/*!    
	\param[in] flMCLK 0~136MHz�ɵ��� ��λ: MHz
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3GetMCLK_S2,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetMCLK_S2(float flMCLK);

	//! ��ȡͨ��1��ǰMCLK����ʱ��
	/*!    
	\param[out] pflMCLK ��λ: MHz
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3SetMCLK,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetMCLK(float* pflMCLK);

	//! ��ȡͨ��2��ǰMCLK����ʱ��
	/*!    
	\param[out] pflMCLK ��λ: MHz
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3SetMCLK_S2,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetMCLK_S2(float* pflMCLK);

	//! ����ͨ��1 Sensor���ݸ�ʽ
	/*! 
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3GetMIPILane, _HisFX3_MIPILane_Stream
	*/
	int HisFX3SetMIPILane(unsigned char ucLane);

	//! ����ͨ��2 Sensor���ݸ�ʽ
	/*! 
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3GetMIPILane, _HisFX3_MIPILane_Stream
	*/
	int HisFX3SetMIPILane_S2(unsigned char ucLane);

	//! ��ȡ��ǰ���õ�ͨ��1 Sensor���ݸ�ʽ
	/*! 
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3SetMIPILane, _HisFX3_MIPILane_Stream
	*/
	int HisFX3GetMIPILane(unsigned char* pucLane);	

	//! ��ȡ��ǰ���õ�ͨ��2 Sensor���ݸ�ʽ
	/*! 
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3SetMIPILane_S2, _HisFX3_MIPILane_Stream
	*/
	int HisFX3GetMIPILane_S2(unsigned char* pucLane);

	//! ���ò���VS, HSͬ���ź�
	/*! һ��ֻ��Ҫ����VS�źţ� HS�źű���Ĭ��
	\param[in] bDVP_VS_ActiveHigh VS�źţ� true:�ߵ�ƽ������Ч�� false: �͵�ƽ������Ч
	\param[in] bDVP_HS_ActiveHigh HS�źţ� true:�ߵ�ƽ������Ч�� false: �͵�ƽ������Ч
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3GetDVPHSVS, _HisFX3Platform_ErrorCode
	*/
	int HisFX3SetDVPHSVS(bool bDVP_VS_ActiveHigh=false, bool bDVP_HS_ActiveHigh=true);

	//! ��ȡ��ǰ���õĲ���VS, HSͬ���ź�
	/*! 
	\param[out] pbDVP_VS_ActiveHigh VS�ź�
	\param[out] pbDVP_HS_ActiveHigh HS�ź�
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa HisFX3SetDVPHSVS, _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetDVPHSVS(bool* pbDVP_VS_ActiveHigh=NULL, bool* pbDVP_HS_ActiveHigh=NULL);

	//! ���ò��ڲɼ�ͬ���ź�����
	/*! 
	\param[in] sCountPs18  0:������;  1: 90��;  2: 180��;  3: 270��;
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa _HisFX3Platform_ErrorCode
	*/
	int HisFX3DVPPCLKPhaseShift(short sCountPs18);

	//! ��ȡFPGA����汾��
	/*!    
	\param[out] puiversion �汾��
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa   HisFX3OpenDevice,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetHardwareVersion(unsigned int* puiversion);

	//! ��ȡ����·����汾��
	/*!    
	\param[out] pusversion �汾��
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa   HisFX3OpenDevice,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetOSVersion(unsigned short* pusversion);

	//! ��ȡFX3����汾��
	/*!    
	\param[out] pusversion �汾��
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa   HisFX3OpenDevice,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetFX3Version(unsigned short* pusversion);

	//! ����
	int HisFX3GetHardGeneration(unsigned int* puiGernation);

	int HisFX3CurrentCalibration(unsigned int* puiKey, _HisFX3_Current_Calibration* pstCal);
	int HisFX3CurrentCalibration_S2(unsigned int* puiKey, _HisFX3_Current_Calibration* pstCal);

	int HisFX3SetCurrentCalData(_HisFX3_Current_Calibration* pstCal);
	int HisFX3SetCurrentCalData_S2(_HisFX3_Current_Calibration* pstCal);

	//! ����ͨ��1��������
	/*!    
	\param[out] flAVDD ���ص�AVDD����
	\param[out] flDVDD ���ص�DVDD����
	\param[out] flDOVDD ���ص�DOVDD����
	\param[out] flAF ���ص�AF����
	\param[out] flVFuse ���ص�VFuse����
	\param[out] flPOW ���ص�POW������R5����R3X����R5X��
	\param[in] uiFlag ����Ҫ����Щ·�ĵ���ֵ�� _HisFX3_Platform_VoltFlag��
									 eg,Ҫ��AVDD��DVDD������ _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] uiAverageTimes ȡuiAverageTimes�����ݣ�Ȼ����ƽ��
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa   HisFX3GetStandbyCurrent,  HisFX3GetWorkCurrent_S2, HisFX3GetStandbyCurrent_S2, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetWorkCurrent(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flVFuse, float& flPOW, unsigned int uiFlag=0xFF, unsigned int uiAverageTimes = 17);

	//! ����ͨ��2��������
	/*!    
	\param[out] flAVDD ���ص�AVDD����
	\param[out] flDVDD ���ص�DVDD����
	\param[out] flDOVDD ���ص�DOVDD����
	\param[out] flAF ���ص�AF����
	\param[out] flVFuse ���ص�VFuse����
	\param[out] flPOW ���ص�POW������R5����R3X����R5X��
	\param[in] uiFlag ����Ҫ����Щ·�ĵ���ֵ�� _HisFX3_Platform_VoltFlag��
									 eg,Ҫ��AVDD��DVDD������ _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] uiAverageTimes ȡuiAverageTimes�����ݣ�Ȼ����ƽ��
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa   HisFX3GetStandbyCurrent,  HisFX3GetWorkCurrent, HisFX3GetStandbyCurrent_S2, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetWorkCurrent_S2(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flVFuse, float& flPOW, unsigned int uiFlag=0xFF, unsigned int uiAverageTimes = 17);
	
	//! ����ͨ��1��̬����
	/*!    
	\param[out] flAVDD ���ص�AVDD����
	\param[out] flDVDD ���ص�DVDD����
	\param[out] flDOVDD ���ص�DOVDD����
	\param[out] flAF ���ص�AF����
	\param[out] flPOW ���ص�POW������R5����R3X����R5X��
	\param[in] uiFlag ����Ҫ����Щ·�ĵ���ֵ�� _HisFX3_Platform_VoltFlag��
									 eg,Ҫ��AVDD��DVDD������ _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] bPWND	true:��PWND�������ģʽ��  false:������PWND�ź�
	\param[in] bReset	true:��RST�������ģʽ��  false:������RST�ź�
	\param[in] bMCLK	true:MCLK��Ϊ0MHz�������ģʽ��  false:�����MCLKʼ����Ϊ0MHz
	\param[in] bDVDD	true:DVDD��Ϊ0V�������ģʽ��  false:�����DVDD����0V
	\param[in] uiDelay	�������ģʽ����ʱuiDelay ms֮���ٲ��������
	\param[in] uiAverageTimes ȡuiAverageTimes�����ݣ�Ȼ����ƽ��
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa   HisFX3GetWorkCurrent,  HisFX3GetWorkCurrent_S2, HisFX3GetStandbyCurrent_S2, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetStandbyCurrent(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flPOW, unsigned int uiFlag=0xFF, \
		bool bPWND=true, bool bReset=true,  bool bMCLK=true, bool bDVDD=false, unsigned int uiDelay=5000, unsigned int uiAverageTimes = 7);

	//! ����ͨ��2��̬����
	/*!    
	\param[out] flAVDD ���ص�AVDD����
	\param[out] flDVDD ���ص�DVDD����
	\param[out] flDOVDD ���ص�DOVDD����
	\param[out] flAF ���ص�AF����
	\param[out] flPOW ���ص�POW������R5����R3X����R5X��
	\param[in] uiFlag ����Ҫ����Щ·�ĵ���ֵ�� _HisFX3_Platform_VoltFlag��
									 eg,Ҫ��AVDD��DVDD������ _HisFX3_Platform_VlotOn_AVDD | _HisFX3_Platform_VlotOn_DVDD
	\param[in] bPWND	true:��PWND�������ģʽ��  false:������PWND�ź�
	\param[in] bReset	true:��RST�������ģʽ��  false:������RST�ź�
	\param[in] bMCLK	true:MCLK��Ϊ0MHz�������ģʽ��  false:�����MCLKʼ����Ϊ0MHz
	\param[in] bDVDD	true:DVDD��Ϊ0V�������ģʽ��  false:�����DVDD����0V
	\param[in] uiDelay	�������ģʽ����ʱuiDelay ms֮���ٲ��������
	\param[in] uiAverageTimes ȡuiAverageTimes�����ݣ�Ȼ����ƽ��
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa   HisFX3GetStandbyCurrent,  HisFX3GetWorkCurrent_S2, HisFX3GetWorkCurrent, _HisFX3_Platform_VoltFlag,  _HisFX3Platform_ErrorCode
	*/
	int HisFX3GetStandbyCurrent_S2(float& flAVDD, float& flDVDD, float& flDOVDD, float& flAF, float& flPOW, unsigned int uiFlag=0xFF, \
		bool bPWND=true, bool bReset=true,  bool bMCLK=true, bool bDVDD=false, unsigned int uiDelay=5000, unsigned int uiAverageTimes = 7);
	
	int HisFX3VlotageCalibration(unsigned int* puiKey, _HisFX3_Voltage_Calibration* pstCal);
	int HisFX3VlotageCalibration_S2(unsigned int* puiKey, _HisFX3_Voltage_Calibration* pstCal);
	int HisFX3SetVoltageCalData(_HisFX3_Voltage_Calibration* pstCal);
	int HisFX3SetVoltageCalData_S2(_HisFX3_Voltage_Calibration* pstCal);

	//! ����Եؿ�·����
	/*!
	\param[in] ucSwitch   0�����Ե�һ·MIPI  1�����Բ���	2�����Եڶ�·MIPI
	\param[inout]   vectorConfigconst  ����Ҫ���п�·���Ե�PIN��
	\param[in] cuiCurrentWaitTime �����ȶ�ʱ�䣺cuiCurrentWaitTime (ms)
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3OSNegtiveTest,  HisFX3OSShortTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSPositiveTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Positive_Item>& vectorConfigconst, const unsigned int cuiCurrentWaitTime=4);

	//! �����DOVDD��·����
	/*!
	\param[in] ucSwitch   0�����Ե�һ·MIPI  1�����Բ���	2�����Եڶ�·MIPI
	\param[inout]   vectorConfig  ����Ҫ���в��Ե�PIN��
	\param[in] cuiCurrentWaitTime �����ȶ�ʱ�䣺cuiCurrentWaitTime (ms)
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSShortTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSNegtiveTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Negtive_Item>& vectorConfig, const unsigned int cuiCurrentWaitTime=4);

	//! ��·����
	/*!
	\param[in] ucSwitch   0�����Ե�һ·MIPI  1�����Բ���	2�����Եڶ�·MIPI
	\param[inout]   vectorConfig  ����Ҫ���в��Ե�PIN��
	\param[in] cuiCurrentWaitTime �����ȶ�ʱ�䣺cuiCurrentWaitTime (ms)
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSNegtiveTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSShortTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Short_Item>& vectorConfig, const unsigned int cuiCurrentWaitTime=4);

	//! ��·����
	/*!
	\param[in] ucSwitch   0������MIPI  1�����Բ���
	\param[inout]   vectorConfig  ����Ҫ���в��Ե�PIN��
	\param[in] cuiCurrentWaitTime �����ȶ�ʱ�䣺cuiCurrentWaitTime (ms)
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSNegtiveTest, HisFX3OSShortTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSOpenTest(unsigned char ucSwitch, std::vector<_HisFX3OS_Open_Item>& vectorConfig, unsigned int cuiCurrentWaitTime);


	//! ��ֵ����
	/*!
	\param[in] ucSwitch   0�����Ե�һ·MIPI  1�����Բ���	2�����Եڶ�·MIPI
	\param[inout]   stConfig  ����Ҫ���в��Ե�PIN��
	\param[in] flCurrent ������ֵʱ���õĵ����� ��Ϊ0.0��Ϊ1.3mA, һ����Ա���Ĭ��ֵ
	\param[in] cuiCurrentWaitTime �����ȶ�ʱ�䣺cuiCurrentWaitTime (ms)
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  _HisFX3OS_Positive_Item,  HisFX3OSNegtiveTest, HisFX3OSOhmTest, _HisFX3Platform_ErrorCode
	*/
	int HisFX3OSOhmTest(unsigned char ucSwitch, _HisFX3OS_OHM_Item& stConfig, float flCurrent = 0.0f, const unsigned int cuiCurrentWaitTime=4);

	int measureExteralVoltage(unsigned int uiChannel, float& flVolt);

	//! ����ͨ��1�����IO�ĵ�ƽ
	/*!
	\param[in] uiStatus  Bit0: ����Out0��ƽ 1-�ߵ�ƽ��0-�͵�ƽ�� �Դ�����...
	\param[in] uiFlag  Bit0: �Ƿ�Ҫ����Out0��ƽ 1-Ҫ���ã�0-�����ã� �Դ�����...
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortRead, HisFX3IO_InPortRead
	*/
	int HisFX3IO_OutPortWrite(unsigned int uiStatus, unsigned int uiFlag = 0xFF);

	//! ����ͨ��2�����IO�ĵ�ƽ
	/*!
	\param[in] uiStatus  Bit0: ����Out0��ƽ 1-�ߵ�ƽ��0-�͵�ƽ�� �Դ�����...
	\param[in] uiFlag  Bit0: �Ƿ�Ҫ����Out0��ƽ 1-Ҫ���ã�0-�����ã� �Դ�����...
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortRead_S2, HisFX3IO_InPortRead_S2
	*/
	int HisFX3IO_OutPortWrite_S2(unsigned int uiStatus, unsigned int uiFlag = 0xFF);

	//! ��ȡͨ��1���IO�ڵĵ�ƽ״̬
	/*!
	\param[in] uiStatus  Bit0: Out0��ƽ 1-�ߵ�ƽ��0-�͵�ƽ�� �Դ�����...
	\param[in] uiFlag  Bit0: �Ƿ�Ҫ��ȡOut0��ƽ 1-Ҫ��ȡ��0-����ȡ�� �Դ�����...
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite, HisFX3IO_InPortRead
	*/
	int HisFX3IO_OutPortRead(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	//! ��ȡͨ��2���IO�ڵĵ�ƽ״̬
	/*!
	\param[in] uiStatus  Bit0: Out0��ƽ 1-�ߵ�ƽ��0-�͵�ƽ�� �Դ�����...
	\param[in] uiFlag  Bit0: �Ƿ�Ҫ��ȡOut0��ƽ 1-Ҫ��ȡ��0-����ȡ�� �Դ�����...
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite_S2, HisFX3IO_InPortRead_S2
	*/
	int HisFX3IO_OutPortRead_S2(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	//! ��ȡͨ��1����IO�ڵĵ�ƽ״̬
	/*!
	\param[in] uiStatus  Bit0: In0��ƽ 1-�ߵ�ƽ��0-�͵�ƽ�� �Դ�����...
	\param[in] uiFlag  Bit0: �Ƿ�Ҫ��ȡIn0��ƽ 1-Ҫ��ȡ��0-����ȡ�� �Դ�����...
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite, HisFX3IO_OutPortRead
	*/
	int HisFX3IO_InPortRead(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	//! ��ȡͨ��2����IO�ڵĵ�ƽ״̬
	/*!
	\param[in] uiStatus  Bit0: In0��ƽ 1-�ߵ�ƽ��0-�͵�ƽ�� �Դ�����...
	\param[in] uiFlag  Bit0: �Ƿ�Ҫ��ȡIn0��ƽ 1-Ҫ��ȡ��0-����ȡ�� �Դ�����...
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  HisFX3IO_OutPortWrite_S2, HisFX3IO_OutPortRead_S2
	*/
	int HisFX3IO_InPortRead_S2(unsigned int& uiStatus, unsigned int uiFlag = 0xFF);

	int HisFX3LedControl(bool bOn, unsigned int* puiKey = 0);

	int HisFX3BuzzerControl(bool bOn, unsigned int* puiKey = 0);

	int getOSPinNameList(unsigned char ucSwitch, std::vector<std::string>& vecOSPin);
	int getOSPositiveGNDPinName(unsigned char ucSwitch, std::vector<std::string>& vecOSPin);
	int getOSNegtiveDOVDDPinName(unsigned char ucSwitch, std::vector<std::string>& vecOSPin);
	
	//! ����
	int HisFX3R2OSSwitch(bool bOS);

	int HisFX3R2OSCalibration(unsigned int* puiKey, _HisFX3R2_OSCal_Item* pstCal, unsigned int uiItemCount);
	int HisFX3SetOSCalData(_HisFX3R2_OSCal_Item* pstCal, unsigned int uiItemCount);
	 
	//! ����
	int HisFX3GetLInfo(unsigned char* pucGeneration, unsigned char* pucApplication, \
		unsigned char* pucFactory, unsigned char* pucAuthorization, unsigned char* pucReserve1, unsigned char* pucReserve2);
	 
	//! ����
	int HisFX3WriteOSIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiData, unsigned short usType);

	//! ����
	int HisFX3ReadOSIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int* puiData, unsigned short usType);

	//! ����
	int HisFX3WriteCurrentIIC(unsigned char ucSlave, unsigned int uiReg, unsigned int uiData, unsigned short usType);

	//! ����
	int HisFX3ReadCurrentI2C(unsigned char ucSlave, unsigned int uiReg, unsigned int* puiData, unsigned short usType);

/*
	int HisFX3GetContinusFrames(bool bC1, bool bC2, unsigned int& uiFrameCount, unsigned int uiBufByte1=0, unsigned char** ppBuffer1=0, unsigned int uiBufByte2=0, unsigned char** ppBuffer2=0);
*/

	int HIsFX3ReadVoltageValue(float* pflDOVDD=0, float* pflAVDD=0, float* pflDVDD=0, float* pflAF=0, float* pflVFuse=0, float* pflPOW=0);
	int HIsFX3ReadVoltageValue_S2(float* pflDOVDD=0, float* pflAVDD=0, float* pflDVDD=0, float* pflAF=0, float* pflVFuse=0, float* pflPOW=0);

	//! ����
	bool isDataStreaming(unsigned int uiTimeOut = 25);

	//! ����
	bool isDataStreaming_S2(unsigned int uiTimeOut = 25);

	//! ����
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

	//! ����USB���Ĵ�С
	/*!
	\param[in] lsize   ��λ��Byte  ��Χ��256*1024~4*1024*1024  ע�������256*1024��������
	\sa  getCurrentBulkTransformSize
	*/
	void setBulkTransformSize(LONG lsize);

	//! ���õ�ǰUSB���Ĵ�С
	/*!
	\return ���Ĵ�С����λ��Byte
	\sa  setBulkTransformSize
	*/
	LONG getCurrentBulkTransformSize();

	//! ��ȡͨ��1����ͷSensor�����֡����
	/*!
	\return ֡����
	\sa  getSensorFrameIndex_S2, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getSensorFrameIndex();

	//! ��ȡͨ��2����ͷSensor�����֡����
	/*!
	\return ֡����
	\sa  getSensorFrameIndex, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getSensorFrameIndex_S2();

	//! ��ȡͨ��1����ͷSensor����֡����
	/*!
	\return ֡����
	\sa  getSensorFrameIndex_S2, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getErrorFrameIndex();

	//! ��ȡͨ��1����ͷSensor����֡����
	/*!
	\return ֡����
	\sa  getSensorFrameIndex_S2, getUploadFrameIndex, getUploadFrameIndex_S2
	*/
	unsigned __int64 getErrorFrameIndex_S2();

	//! ��ȡͨ��1�ϴ�֡����
	/*!
	\return ֡����
	\sa  getUploadFrameIndex_S2, getSensorFrameIndex, getSensorFrameIndex_S2
	*/
	unsigned __int64 getUploadFrameIndex();

	//! ��ȡͨ��2�ϴ�֡����
	/*!
	\return ֡����
	\sa  getUploadFrameIndex, getSensorFrameIndex, getSensorFrameIndex_S2
	*/
	unsigned __int64 getUploadFrameIndex_S2();


	void testComputerCompatibility(float* pflErrorRate, float* pflErrorRead);
	void setCurrentPlatformType(_HisFX3_Platform_Type platformType);

	//! ����USB��������
	/*!
	\param[in] uiDelay   ��Χ��10~240 ʱ�����ڣ� ԽС����Խ��
	\return 0:�ɹ�  ��0:ʧ�� ��ο�_HisFX3Platform_ErrorCode
	\sa  _HisFX3Platform_ErrorCode
	*/
	int setUSBSpeed(unsigned int uiDelay);

	int LedControl(bool bOn);
	int BuzzerControl(bool bOn);

	int HisFX3StartAudio();
	int HisFX3StopAudio();
	int HisFX3GrabAudioBuffer(_HisPlatformAudio_Buffer* pstBuf, unsigned int uiTimeOut = 1500);
	int UVCSetProperty(int aProperty, float aValue, int aAuto = 0);

	//! ��ȡ������Ϣ���ַ�������
	/*! ��� ����->C/C++ ->����->��WChar_t��Ϊ�������� ��Ϊ������ô˺�������Ϊ�ǣ������GetLastErrorMB
	\return ������Ϣ�ַ���ָ��
	\sa  GetLastErrorMB, ClearError
	*/
	const wchar_t* GetLastError(void);

	bool HisFX3IsOpenLight();

	//! ��ȡ������Ϣ���ַ�������
	/*! ��� ����->C/C++ ->����->��WChar_t��Ϊ�������� ��Ϊ�ǣ�����ô˺�������Ϊ�������GetLastError
		 eg. wchar_t* pstrError = (wchar_t*)GetLastErrorMB();
	\return ������Ϣ�ַ���ָ��
	\sa  GetLastError, ClearError
	*/
	unsigned short* GetLastErrorMB(void);

	//! ���������Ϣ
	/*! 
	\sa  GetLastError, GetLastErrorMB
	*/
	void ClearError(void);


	int DothinkeyINI2Rolongo(char* pstrRolongoIniPath, _HisFX3_PreviewStruct& stPreivewConfig);

	int decodeRolongoXML_A(char* pstrPath, _HisFX3_PreviewStruct& previewConfig, std::vector<_RolongoXMLOtherSectionItem>& vecPair);

	//! ����
	void test();

	//! ����
	bool checkSenseShieldEnabled(unsigned int uiLincenseID, unsigned char ucClient, unsigned char ucProduct);

	//! ����
	int getPlatformType(unsigned short usPID, unsigned short usVID, char* pstrFriendlyName, unsigned char ucDeviceIndex, unsigned int* puiKey);

	//�ڲ�ʹ�ã���Ҫ����***
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

//!  ����USB���Ĵ�С
/*! �������������ʱ�򣬻��Զ����ԭ���Ĵ�С
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
	/// @brief SENSOR���
	USHORT width;          ///<SENSOR���
	/// @brief SENSOR�߶�
	USHORT height;         ///<SENSOR�߶�
	/// @brief SENSOR��������
	BYTE type;             ///<SENSOR��������
	/// @brief SENSOR��RESET��PWDN��������
	BYTE pin;              ///<SENSOR��RESET��PWDN��������
	/// @brief SENSOR��������ַ
	BYTE SlaveID;          ///<SENSOR��������ַ
	/// @brief SENSOR��I2Cģʽ
	BYTE mode;						 ///<SENSOR��I2Cģʽ
	/// @brief SENSOR��־�Ĵ���1.
	USHORT FlagReg;				 ///<SENSOR��־�Ĵ���1.
	/// @brief SENSOR��־�Ĵ���1��ֵ
	USHORT FlagData;			 ///<SENSOR��־�Ĵ���1��ֵ
	/// @brief SENSOR��־�Ĵ���1������ֵ
	USHORT FlagMask;			 ///<SENSOR��־�Ĵ���1������ֵ
	/// @brief SENSOR��־�Ĵ���2.
	USHORT FlagReg1;			 ///<SENSOR��־�Ĵ���2.
	/// @brief SENSOR��־�Ĵ���2��ֵ
	USHORT FlagData1;			 ///<SENSOR��־�Ĵ���2��ֵ
	/// @brief SENSOR��־�Ĵ���2������ֵ
	USHORT FlagMask1;			 ///<SENSOR��־�Ĵ���2������ֵ
	/// @brief SENSOR������
	char name[64];				///<SENSOR������

	/// @brief ��ʼ��SENSOR���ݱ�
	USHORT* ParaList;			///<��ʼ��SENSOR���ݱ�
	/// @brief ��ʼ��SENSOR���ݱ��С����λ�ֽ�
	USHORT  ParaListSize; ///<��ʼ��SENSOR���ݱ��С����λ�ֽ�

	/// @brief SENSOR����PLATFORMSHARE::Sleepģʽ�Ĳ�����
	USHORT* SleepParaList;	///<SENSOR����PLATFORMSHARE::Sleepģʽ�Ĳ�����
	/// @brief SENSOR����PLATFORMSHARE::Sleepģʽ�Ĳ������С����λ�ֽ�
	USHORT  SleepParaListSize;///<SENSOR����PLATFORMSHARE::Sleepģʽ�Ĳ������С����λ�ֽ�

	/// @brief SENSOR������ݸ�ʽ��YUV//0:YCbYCr;	//1:YCrYCb;	//2:CbYCrY;	//3:CrYCbY.
	BYTE outformat;         ///<SENSOR������ݸ�ʽ��YUV//0:YCbYCr;	//1:YCrYCb;	//2:CbYCrY;	//3:CrYCbY.
	/// @brief SENSOR������ʱ��MCLK��0:12M; 1:24M; 2:48M.
	int mclk;               ///<SENSOR������ʱ��MCLK��0:12M; 1:24M; 2:48M.
	/// @brief SENSOR��AVDD��ѹֵ
	BYTE avdd;              ///<SENSOR��AVDD��ѹֵ
	/// @brief SENSOR��DOVDD��ѹֵ
	BYTE dovdd;             ///<SENSOR��DOVDD��ѹֵ
	/// @brief SENSOR��DVDD��ѹֵ		
	BYTE dvdd;							///<SENSOR��DVDD��ѹֵ

	/// @brief SENSOR�����ݽӿ�����
	BYTE port; 							///<SENSOR�����ݽӿ�����
	USHORT Ext0;
	USHORT Ext1;
	USHORT Ext2; 

	/// @brief AF��ʼ��������
	USHORT* AF_InitParaList;        ///<AF��ʼ��������
	/// @brief AF��ʼ���������С����λ�ֽ�
	USHORT  AF_InitParaListSize;		///<AF��ʼ���������С����λ�ֽ�

	/// @brief AF_AUTO������
	USHORT* AF_AutoParaList;				///<AF_AUTO������
	/// @brief AF_AUTO�������С����λ�ֽ�
	USHORT  AF_AutoParaListSize;		///<AF_AUTO�������С����λ�ֽ�

	/// @brief AF_FAR������
	USHORT* AF_FarParaList;					///<AF_FAR������
	/// @brief AF_FAR�������С����λ�ֽ�
	USHORT  AF_FarParaListSize;			///<AF_FAR�������С����λ�ֽ�

	/// @brief AF_NEAR������
	USHORT* AF_NearParaList;				///<AF_NEAR������
	/// @brief AF_NEAR�������С����λ�ֽ�
	USHORT  AF_NearParaListSize;		///<AF_NEAR�������С����λ�ֽ�

	/// @brief �ع������
	USHORT* Exposure_ParaList;      ///<�ع������
	/// @brief �ع�������С����λ�ֽ�
	USHORT  Exposure_ParaListSize;	///<�ع�������С����λ�ֽ�

	/// @brief ���������
	USHORT* Gain_ParaList;          ///<���������
	/// @brief ����������С����λ�ֽ�
	USHORT	Gain_ParaListSize;			///<����������С����λ�ֽ� 

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

		Exposure_ParaList=NULL;      //�ع�
		Exposure_ParaListSize=0;

		Gain_ParaList=NULL;          //����
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
		HISFX3PLATFORM_EXPORT int	_stdcall 	IOlevel_SetM(float fvolt, int index); //1.6 ~ 3.5 range �� table ����. (2006. 3/13)
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

