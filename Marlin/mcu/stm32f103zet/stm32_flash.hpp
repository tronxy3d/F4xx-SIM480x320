#pragma once

#ifdef STM32F1xx
enum{ 
  FLASH_OK = 0,
  FLASH_BUSY = 1,
  FLASH_TIMEOUT = 2
};

#define	HIGH_CAPACITY_SIZE	0x800	//STM32F10x_xC(含)以上大容量每页是2K
#define	MID_CAPACITY_SIZE	0x400	//STM32F10x_xB(含)以下中容量每页是1K
#define SECTOR_SIZE HIGH_CAPACITY_SIZE
class IFlash
{
public:
	static inline uint32_t currentSectorAddr(uint32_t addr){return addr / SECTOR_SIZE * SECTOR_SIZE;}//目标地址所在扇区起始地址
	static inline uint32_t nextSectorAddr(uint32_t addr){return (addr / SECTOR_SIZE + 1) * SECTOR_SIZE;}//目标地址下一扇区地址

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
#endif // define STM32F1xx
