#include "Flash.h"
#include "string.h"

static uint32_t WRPR_Value = 0xFFFFFFFF, ProtectedPages = 0x00;
volatile FLASH_Status MemoryProgramStatus,FLASHStatus = 0;

const struct _Flash_DATA Flash_DATA =
{
    .information = 0,
    .version = 2,
    .baud = 4,
    .IP = 6,
    .GPIO = 8,
};

int Read_Flash(int Address)
{
#ifdef Exist_FLASH
    int temp;
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV2;
    __disable_irq();
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);

    temp = *(__IO uint16_t*) Address;

    FLASH_Lock();
    FLASHStatus = FLASH_GetStatus();
    while(FLASHStatus != FLASH_COMPLETE);       //����һ��״̬���
    RCC->CFGR0 &= ~(uint32_t)RCC_HPRE_DIV2;
    __enable_irq();
    return temp;
#endif
}

/*
 * ���256 byteֻ��ʹ�ÿ��ٵģ����ٵ��ǲ����з���ֵ��
 */
char Clear_Flash_Page(int Addr)
{
    char Status = 0;
#ifdef Exist_FLASH
    int Address;
    int Page = (Addr -0x08000000) / FLASH_PAGE_SIZE;
    Address = 0x08000000 + (Page * FLASH_PAGE_SIZE);        //��ҳ�׵�ַ(������)

//    printf("Address %x \r\n",Address);    //debug

    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV2;
    __disable_irq();
    FLASH_Unlock_Fast();
    FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);

    if (Address >= FLASH_DATA && Address < FLASH_END)   //��ֹ��ͷ
    {
        FLASH_ErasePage_Fast(Address);   //��256
    }

    FLASH_Lock_Fast();
    FLASHStatus = FLASH_GetStatus();
    while(FLASHStatus != FLASH_COMPLETE);       //����һ��״̬���
    RCC->CFGR0 &= ~(uint32_t)RCC_HPRE_DIV2;
    __enable_irq();

    Status = 1;
#endif
    FLASHStatus = 0;
    return Status;
}

char Clear_Flash_Area(int addr_start,int addr_end)
{
    char Status = 0;
#ifdef Exist_FLASH
    int Address;
    int addr[2];
    int Area = (addr_start -0x08000000) / FLASH_AREA_SIZE;
    addr[0] = 0x08000000 + (Area * FLASH_AREA_SIZE);        //��ҳ�׵�ַ(������)
    Area = (addr_end -0x08000000) / FLASH_AREA_SIZE;
    if((addr_end -0x08000000) % FLASH_AREA_SIZE > 0)
            Area++;
    addr[1] = 0x08000000 + (Area * FLASH_AREA_SIZE);        //��ҳβ��ַ(������)

//    printf("Area_end %d \r\n",Area);    //debug
//    if (Area > 16) {
//        printf("ch32 over !!\r\n");
//    }

    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV2;
    __disable_irq();
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);

    if (Area <= 16)
    {
        int temp = 0;
        do {
            Address = addr[0] + temp * FLASH_AREA_SIZE;
            if (Address >= FLASH_DATA && Address <= FLASH_END)  //��ֹ��ͷ
            {
                FLASHStatus |= FLASH_ErasePage(Address);        //��4K
            }
            temp++;
        } while (temp <= ((addr[1] - addr[0]) / FLASH_AREA_SIZE) && (FLASHStatus == FLASH_COMPLETE));
    }
    else
    {
        FLASHStatus |= FLASH_EraseAllPages();
    }

//    �����ڴ�����    //debug
    Address = addr[0];
    while((Address < addr[1]) && (FLASHStatus == FLASH_COMPLETE))
    {
        FLASHStatus |= FLASH_ProgramHalfWord(Address, 0xaaaa);
        Address += 2;
    }

    FLASH_Lock();
    FLASHStatus = FLASH_GetStatus();
    while(FLASHStatus != FLASH_COMPLETE);       //����һ��״̬���

    RCC->CFGR0 &= ~(uint32_t)RCC_HPRE_DIV2;
    __enable_irq();

    if(FLASHStatus != FLASH_COMPLETE)
    {
        printf("FLASH Erase Fail\r\n");
    }
    else
    {
        printf("FLASH Erase Suc\r\n");
        Status = 1;
    }

#endif
    FLASHStatus = 0;
    return Status;
}

/*
 * ���256 byteֻ��ʹ�ÿ��ٵģ����ٵ��ǲ����з���ֵ��
 * ����д�����з���ֵ
 */
char Save_Flash(int Addr,const uint16_t *Data,int Lenght)
{
    char Status = 0;
#ifdef Exist_FLASH
    int temp = 0;
    int Address;
    int Page = (Addr - 0x08000000) / FLASH_PAGE_SIZE;
    Address = 0x08000000 + (Page * FLASH_PAGE_SIZE);        //��ҳ�׵�ַ(������)

    printf("Address %x,now: %x \r\n",Address,Addr);    //debug

    uint16_t string[FLASH_PAGE_SIZE/2];
    memcpy(string,(uint16_t *)Address,FLASH_PAGE_SIZE); //����
    memcpy(string + (Addr-Address),Data,Lenght);        //����
    printf("string [%d] %x \n",0,string[0]);
    printf("string [%d]  %x \n",(Addr-Address),string[(Addr-Address)]);
    printf("string [%d]  %x \r\n",120,string[120]);
    int i = 10000;
    while(i--);

    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV2;
    __disable_irq();
    FLASH_Unlock_Fast();        //����ģʽ_ON
    FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);

    if (Address >= FLASH_DATA && Address < FLASH_END)   //��ֹ��ͷ
    {
        FLASH_ErasePage_Fast(Address);                  //��256
    }
    FLASH_Lock_Fast ();         //��ͨģʽ_OFF

    FLASHStatus = FLASH_GetStatus();
    while(FLASHStatus != FLASH_COMPLETE);   //����һ��״̬���
    FLASH_Unlock();

    int8_t pp = 0;
    temp = Address;
    while((temp < (0x0800a000+FLASH_PAGE_SIZE)) && (FLASHStatus == FLASH_COMPLETE))
    {
        FLASHStatus |= FLASH_ProgramHalfWord(temp, string[pp]);
        temp += 2;
        pp += 1;
    }
    temp = Address;
    pp = 0;
    MemoryProgramStatus = 1;
    while(temp < (0x0800a000+FLASH_PAGE_SIZE))  //У��
    {
        int16_t data = Fast_Flash(temp);
        if(data != string[pp])
        {
            MemoryProgramStatus = FAILED;
            break;
        }
        temp += 2;
        pp += 1;
    }
    FLASH_Lock();     //����ģʽ_OFF
    FLASHStatus = FLASH_GetStatus();
    while(FLASHStatus != FLASH_COMPLETE);       //����һ��״̬���
    RCC->CFGR0 &= ~(uint32_t)RCC_HPRE_DIV2;
    __enable_irq();

    if(FLASHStatus != FLASH_COMPLETE)
        printf("FLASH Erase Fail\r\n");
    else {
        printf("FLASH Erase Suc\r\n");
        Status = 1;
    }
    if(MemoryProgramStatus == FAILED)
    {
//        printf("FLASH Memory Fail\r\n");
        temp = Address + pp;
        printf("FLASH Memory Fail num:%d flash %x--str %x \n",pp,Fast_Flash(0x0800a000),string[pp]);
    }
    else {
        printf("FLASH Memory Suc\r\n");
        Status = 1;
    }

#endif
    FLASHStatus = 0;
    MemoryProgramStatus = 0;
    return Status;
}




