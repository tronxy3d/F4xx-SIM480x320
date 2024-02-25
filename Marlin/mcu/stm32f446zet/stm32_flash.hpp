#pragma once

#ifdef STM32F4xx
enum{ 
  FLASH_OK = 0,
  FLASH_BUSY = 1,
  FLASH_TIMEOUT = 2
};

//STM32F4的FLASH扇区大小不是固定的,从0x08000000开始,依次是4个16K,1个64K,7个128K,如果是2M的FLASH,则后面1M和前1M是一样的顺序
#define ADDR_FLASH_SECTOR_0     0x08000000//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     0x08004000//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     0x08008000//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     0x0800C000//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     0x08010000//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     0x08020000//扇区5起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     0x08040000//扇区6起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7     0x08060000//扇区7起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_8     0x08080000//扇区8起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_9     0x080A0000//扇区9起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_10    0x080C0000//扇区10起始地址,128 Kbytes  
#define ADDR_FLASH_SECTOR_11    0x080E0000//扇区11起始地址,128 Kbytes
#define ADDR_FLASH_SECTOR_12    0x08100000//扇区11起始地址,16 Kbytes

class IFlash
{
public:
	static inline uint32_t sectorNumOfAddr(uint32_t addr) //获取当前地址所在扇区号
	{
		if(addr < ADDR_FLASH_SECTOR_1)return 0;
		else if(addr < ADDR_FLASH_SECTOR_2)return 1;
		else if(addr < ADDR_FLASH_SECTOR_3)return 2;
		else if(addr < ADDR_FLASH_SECTOR_4)return 3;
		else if(addr < ADDR_FLASH_SECTOR_5)return 4;
		else if(addr < ADDR_FLASH_SECTOR_6)return 5;
		else if(addr < ADDR_FLASH_SECTOR_7)return 6;
		else if(addr < ADDR_FLASH_SECTOR_8)return 7;
		else if(addr < ADDR_FLASH_SECTOR_9)return 8;
		else if(addr < ADDR_FLASH_SECTOR_10)return 9;
		else if(addr < ADDR_FLASH_SECTOR_11)return 10;
		return 11;	
	}
	static inline uint32_t currentSectorAddr(uint32_t addr){ //目标地址所在扇区起始地址
		if(addr < ADDR_FLASH_SECTOR_1)return FLASH_BASE;
		else if(addr < ADDR_FLASH_SECTOR_2)return ADDR_FLASH_SECTOR_1;
		else if(addr < ADDR_FLASH_SECTOR_3)return ADDR_FLASH_SECTOR_2;
		else if(addr < ADDR_FLASH_SECTOR_4)return ADDR_FLASH_SECTOR_3;
		else if(addr < ADDR_FLASH_SECTOR_5)return ADDR_FLASH_SECTOR_4;
		else if(addr < ADDR_FLASH_SECTOR_6)return ADDR_FLASH_SECTOR_5;
		else if(addr < ADDR_FLASH_SECTOR_7)return ADDR_FLASH_SECTOR_6;
		else if(addr < ADDR_FLASH_SECTOR_8)return ADDR_FLASH_SECTOR_7;
		else if(addr < ADDR_FLASH_SECTOR_9)return ADDR_FLASH_SECTOR_8;
		else if(addr < ADDR_FLASH_SECTOR_10)return ADDR_FLASH_SECTOR_9;
		else if(addr < ADDR_FLASH_SECTOR_11)return ADDR_FLASH_SECTOR_10;
		return ADDR_FLASH_SECTOR_11;	
	}
	static inline uint32_t nextSectorAddr(uint32_t addr){ //目标地址下一扇区地址
		if(addr < ADDR_FLASH_SECTOR_1)return ADDR_FLASH_SECTOR_1;
		else if(addr < ADDR_FLASH_SECTOR_2)return ADDR_FLASH_SECTOR_2;
		else if(addr < ADDR_FLASH_SECTOR_3)return ADDR_FLASH_SECTOR_3;
		else if(addr < ADDR_FLASH_SECTOR_4)return ADDR_FLASH_SECTOR_4;
		else if(addr < ADDR_FLASH_SECTOR_5)return ADDR_FLASH_SECTOR_5;
		else if(addr < ADDR_FLASH_SECTOR_6)return ADDR_FLASH_SECTOR_6;
		else if(addr < ADDR_FLASH_SECTOR_7)return ADDR_FLASH_SECTOR_7;
		else if(addr < ADDR_FLASH_SECTOR_8)return ADDR_FLASH_SECTOR_8;
		else if(addr < ADDR_FLASH_SECTOR_9)return ADDR_FLASH_SECTOR_9;
		else if(addr < ADDR_FLASH_SECTOR_10)return ADDR_FLASH_SECTOR_10;
		else if(addr < ADDR_FLASH_SECTOR_11)return ADDR_FLASH_SECTOR_11;
		return ADDR_FLASH_SECTOR_12;
	}

	/*******************************************************************************
	* 函数名    :vwrite
	* 描述      :向FLASH中指定地址写入指定长度的数据,必须先擦除使该页为0xFF
	* 参数      :addr要写入的地址
				:data要写入的FLASH数据地址
				:byteSize写入的数据大小,字节为单位,必须小于addr所在页addr地址后面剩余空间
	* 返回      :-
	* 编写者    ：YSZ
	* 编写日期  ：2019-12-28
	*******************************************************************************/
	static uint8_t vwrite(uint32_t addr,const void* data,uint32_t byteSize);

	/*******************************************************************************
	* 函数名    :eraseSector
	* 描述      :检测该地址往后的本扇区剩余量是否需要擦除,需要的话,本扇区会全部擦除
	* 参数      :addr目标地址
	* 返回      :-
	* 编写者    ：YSZ
	* 编写日期  ：2021-03-02
	*******************************************************************************/
	static uint8_t eraseSector(uint32_t addr);

	/*******************************************************************************
	* 函数名    :read
	* 描述      :读取FLASH中指定地址指定长度的数据
	* 参数      :addr要读取的地址
				:data读取的数据存放的内存地址
				:size读取的大小
	* 返回      :-
	* 编写者    ：YSZ
	* 编写日期  ：2019-12-28
	*******************************************************************************/
	static void read(uint32_t addr,void* data,uint32_t byteSize);

	/*******************************************************************************
	* 函数名    :swrite
	* 描述      :向FLASH中指定地址写入指定长度的数据,会擦除掉关联扇区的数据
	* 参数      :addr写入地址
	            :nextEraseAddr需要擦除的地址
				:data要写入的FLASH数据地址
				:byteSize写入的数据大小,字节为单位
	* 返回      :-
	* 编写者    ：YSZ
	* 编写日期  ：2019-12-28
	*******************************************************************************/
	static uint8_t swrite(uint32_t& addr,uint32_t& nextEraseAddr,const void* data,uint32_t byteSize);
};
#endif
