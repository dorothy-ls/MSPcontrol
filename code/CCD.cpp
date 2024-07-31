#include "CCD.h"

uint32_t DMA_EN_cnt = 0;
void CCD::SI_send()//��ʱ��OC�жϵ��ã�����һ�����ݷ���һ��SI�ź�
{
    if(state == 0)
    {
        state ++;
    }
    else if(state == 1)
    {
        DL_GPIO_setPins(GPIO_CCD_PORT, GPIO_CCD_PIN_SI_PIN);
        state ++;
    }
    else
    {
        DL_GPIO_clearPins(GPIO_CCD_PORT, GPIO_CCD_PIN_SI_PIN);
        NVIC_DisableIRQ(TIM_CCD_INST_INT_IRQN);
        state = 0;

        //��ADC DMA
        //HAL_ADC_Start_DMA(&hadc3, (uint32_t *)data, 128);
        //DL_ADC12_enableDMA(ADC_CCD_INST);//����Ҫ�޸� �涨����Ĵ洢����ַ�����ݳ���
        DL_ADC12_enableConversions(ADC_CCD_INST);
        DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,(uint32_t) DL_ADC12_getMemResultAddress(ADC_CCD_INST,ADC_CCD_ADCMEM_0));
        DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) data);
        DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, 128);
        DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);

        //DL_ADC12_startConversion(ADC_CCD_INST);

        DMA_EN_cnt++;
        //DL_ADC12_startConversion(ADC_CCD_INST);
    }
}

void CCD::Handler()//ÿ10ms����һ��CCD����
{
    if(utick % integrate_time == 0)
    {
        NVIC_EnableIRQ(TIM_CCD_INST_INT_IRQN);//��CCD_TIM�жϣ�����һ��SI����
        sample_t = 0;
        sample_complete = false;
    }
    sample_t++;
}

void CCD::init() //��CCD_TIM����
{
    DL_Timer_startCounter(TIM_CCD_INST);
    last_dir = 64;
}





