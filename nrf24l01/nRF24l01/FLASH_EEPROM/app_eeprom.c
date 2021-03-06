#include "app_eeprom.h"
#include "Comm_GLOBALS.h"
//uint16_t virt_add_var_tab[NUMB_OF_VAR] = {0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008,
//                                          0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f, 0x0010,
//                                          0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018,
//                                          0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f, 0x0020,
//                                          0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028,
//                                         };  /* 1个数据对应1个虚拟地址 */
uint16_t virt_add_var_tab[NUMB_OF_VAR] = {0x0000,0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 
//                                        0x0008,0x0009, 0x000a, 0x000b, 0x000c, 0x000d,
                                         };  /* 1个数据对应1个虚拟地址 */

void virt_add_tab_init(void)
{
    uint16_t  read_status;
    uint16_t  init_flag = 0;
//    read_status = EE_ReadVariable(EE_READ_STATUS_VIRT_ADDR, &init_flag);
    read_status = EE_ReadVariable(TX_ADDRESS_EE_ADDR, &init_flag);
    if(read_status == 0)			/* 找到了此地址，说明已经初始化过了 */
    {
        return;
    }

    /* 没有找到 EE_INIT_FLAG_EE_ADDR 这个地址,说明之前没有执行过初始化操作，执行第一次写入操作*/
    TX_ADDRESS[0] = 0XFF;//ID号
    TX_ADDRESS[1] = 0XFF;//ID号
    TX_ADDRESS[2] = 0XFF;//ID号
    TX_ADDRESS[3] = 0XFF;//ID号
    TX_ADDRESS[4] = 0XFF;//ID号
    BaudRate = 9600;
    Speed = SPEED_2M;
    Power = POWER_0DBM;
    CRCMode = MODE_16;
    FreqPoint = 0;
    STMFLASH_Write(TX_ADDRESS_EE_ADDR, (uint16_t *)&TX_ADDRESS[1], 2 );
    STMFLASH_Write(BaudRate_EE_ADDR, (uint16_t *)&BaudRate, 2 );
    STMFLASH_Write(Speed_EE_ADDR, &Speed, 1);
    STMFLASH_Write(Power_EE_ADDR, &Power, 1);
    STMFLASH_Write(CRCMode_EE_ADDR, &CRCMode, 1);
    STMFLASH_Write(FreqPoint_EE_ADDR, &FreqPoint, 1);
}
void EEP_Init(void)
{
		STMFLASH_Read(TX_ADDRESS_EE_ADDR, (uint16_t *)&TX_ADDRESS[1], 2 );
		STMFLASH_Read(BaudRate_EE_ADDR, (uint16_t *)&BaudRate, 2 );
		STMFLASH_Read(Speed_EE_ADDR, &Speed, 1);
		STMFLASH_Read(Power_EE_ADDR, &Power, 1);
		STMFLASH_Read(CRCMode_EE_ADDR, &CRCMode, 1);
		STMFLASH_Read(FreqPoint_EE_ADDR, &FreqPoint, 1);
}
void app_ee_init(void)
{
    HAL_FLASH_Unlock();             /* 对flash编程前，必须解锁flash */
    EE_Init();
    virt_add_tab_init();
    HAL_FLASH_Lock();               /* 编程结束后，必须锁定flash */
	  EEP_Init();
}


/********************** END OF FILE ******************************************/
