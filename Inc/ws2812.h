#ifndef MYLIB_WS28XX
#define MYLIB_WS28XX

#include "tim.h"			
/****************************************
*Config
****************************************/
#define BIT_1               61            //1��Ƚ�ֵΪ61-->850us
#define BIT_0               28            //0��Ƚ�ֵΪ28-->400us

#define PIXEL_SIZE			    8             //�Ƶ�����
#define WS28xx_PWM_hTIMER	  htim3         //��ʱ��3
#define WS28xx_PWM_Chaneel  TIM_CHANNEL_1	//ͨ��1	

//����WS28xx_DataTypeStruct�ṹ�彫����PWM��ʽ����
typedef struct
{						
	unsigned char ColorStartData[3];           //3��0�ȴ�PWM�ȶ�			
	unsigned char ColorRealData[24*PIXEL_SIZE];//ʵ��GRB����(�Ѿ�ת��ΪPWM��Ӧ��ֵ)
	unsigned char ColorEndData;             	 //����λΪ0
}WS28xx_DataTypeStruct;

/****************************************
*���󻯱��
****************************************/
typedef struct 
{
	//ʵ�ʷ��͵�����
	WS28xx_DataTypeStruct WS28xx_Data;
	//������
	unsigned short int Pixel_size;
	
    //��������index��RGB��ɫ
    void (*SetPixelColor_RGB)(unsigned short int index,unsigned char r,unsigned char g,unsigned char b);
    //��RGB���ݶ���������index��RGB��ɫ
    void (*SetPixelColor_From_RGB_Buffer)( unsigned short int pixelIndex,unsigned char pRGB_Buffer[][3],unsigned short int DataCount);
    //��������ΪRGB��ɫ
    void (*SetALLColor_RGB)(unsigned char r,unsigned char g,unsigned char b);
    //��ȡĳ��λ�õ�RGB
    void (*GetPixelColor_RGB)(unsigned short int index,unsigned char *r,unsigned char *g,unsigned char *b);
    //��ʾ���������ݣ�
    void (*show)(void);
}WS28xx_TypeStruct;

extern WS28xx_TypeStruct WS28xx;

void   WS28xx_TypeStructInit(void);

#endif
