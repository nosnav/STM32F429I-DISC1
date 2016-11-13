#include "stm32f4_spi_dma.h"

/* Private structure */
typedef struct {
	uint32_t TX_Channel;
	DMA_Stream_TypeDef* TX_Stream;
	uint32_t RX_Channel;
	DMA_Stream_TypeDef* RX_Stream;
	uint32_t Dummy32;
	uint16_t Dummy16;
} SPI_DMA_INT_t;

/* Private variables */
#ifdef SPI1
static SPI_DMA_INT_t SPI1_DMA_INT = {SPI1_DMA_TX_CHANNEL, SPI1_DMA_TX_STREAM, SPI1_DMA_RX_CHANNEL, SPI1_DMA_RX_STREAM};
#endif
#ifdef SPI2
static SPI_DMA_INT_t SPI2_DMA_INT = {SPI2_DMA_TX_CHANNEL, SPI2_DMA_TX_STREAM, SPI2_DMA_RX_CHANNEL, SPI2_DMA_RX_STREAM};
#endif
#ifdef SPI3
static SPI_DMA_INT_t SPI3_DMA_INT = {SPI3_DMA_TX_CHANNEL, SPI3_DMA_TX_STREAM, SPI3_DMA_RX_CHANNEL, SPI3_DMA_RX_STREAM};
#endif
#ifdef SPI4
static SPI_DMA_INT_t SPI4_DMA_INT = {SPI4_DMA_TX_CHANNEL, SPI4_DMA_TX_STREAM, SPI4_DMA_RX_CHANNEL, SPI4_DMA_RX_STREAM};
#endif
#ifdef SPI5
static SPI_DMA_INT_t SPI5_DMA_INT = {SPI5_DMA_TX_CHANNEL, SPI5_DMA_TX_STREAM, SPI5_DMA_RX_CHANNEL, SPI5_DMA_RX_STREAM};
#endif
#ifdef SPI6
static SPI_DMA_INT_t SPI6_DMA_INT = {SPI6_DMA_TX_CHANNEL, SPI6_DMA_TX_STREAM, SPI6_DMA_RX_CHANNEL, SPI6_DMA_RX_STREAM};
#endif

/* Private DMA structure */
static DMA_InitTypeDef DMA_InitStruct;

/* Private functions */
static SPI_DMA_INT_t* SPI_DMA_INT_GetSettings(SPI_TypeDef* SPIx);
	
void SPI_DMA_Init(SPI_TypeDef* SPIx) {
	/* Init DMA TX mode */
	/* Assuming SPI is already initialized and clock is enabled */
	
	/* Get USART settings */
	SPI_DMA_INT_t* Settings = SPI_DMA_INT_GetSettings(SPIx);
	
	/* Enable DMA clock */
	if (Settings->TX_Stream >= DMA2_Stream0) {
		/* Enable DMA2 clock */	
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	} else {
		/* Enable DMA1 clock */
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	}
	
	/* Enable DMA clock */
	if (Settings->RX_Stream >= DMA2_Stream0) {
		/* Enable DMA2 clock */	
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	} else {
		/* Enable DMA1 clock */
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	}
	
	/* Set DMA options for TX stream */
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Low;
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
}

void SPI_DMA_InitWithStreamAndChannel(SPI_TypeDef* SPIx, DMA_Stream_TypeDef* TX_Stream, uint32_t TX_Channel, DMA_Stream_TypeDef* RX_Stream, uint32_t RX_Channel) {
	/* Get USART settings */
	SPI_DMA_INT_t* Settings = SPI_DMA_INT_GetSettings(SPIx);
	
	/* Set values */
	Settings->RX_Channel = RX_Channel;
	Settings->RX_Stream = RX_Stream;
	Settings->TX_Channel = TX_Channel;
	Settings->TX_Stream = TX_Stream;
	
	/* Init SPI */
	SPI_DMA_Init(SPIx);
}

void SPI_DMA_Deinit(SPI_TypeDef* SPIx) {
	/* Get USART settings */
	SPI_DMA_INT_t* Settings = SPI_DMA_INT_GetSettings(SPIx);
	
	/* Deinit DMA Streams */
	DMA_DeInit(Settings->TX_Stream);
	DMA_DeInit(Settings->RX_Stream);
}

uint8_t SPI_DMA_Transmit(SPI_TypeDef* SPIx, uint8_t* TX_Buffer, uint8_t* RX_Buffer, uint16_t count) {
	/* Get USART settings */
	SPI_DMA_INT_t* Settings = SPI_DMA_INT_GetSettings(SPIx);
	
	/* Check if DMA available */
	if (
		Settings->RX_Stream->NDTR || 
		Settings->TX_Stream->NDTR || 
		(TX_Buffer == NULL && RX_Buffer == NULL)
	) {
		return 0;
	}
	
	/* Set dummy memory to default */
	Settings->Dummy16 = 0x00;
	
	/* Set memory size */
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/* Set DMA peripheral address and count */
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) &SPIx->DR;
	DMA_InitStruct.DMA_BufferSize = count;
	
	/* Configure TX DMA */
	DMA_InitStruct.DMA_Channel = Settings->TX_Channel;
	DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	
	if (TX_Buffer != NULL) {
		DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t) TX_Buffer;
		DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	} else {
		DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t) &Settings->Dummy32;
		DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	}
	
	/* Deinit first TX stream */
	DMA_Clear_Flag(Settings->TX_Stream, DMA_FLAG_ALL);
	
	/* Init TX stream */
	DMA_Init(Settings->TX_Stream, &DMA_InitStruct);	
	
	/* Configure RX DMA */
	DMA_InitStruct.DMA_Channel = Settings->RX_Channel;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
	
	if (RX_Buffer != NULL) {
		DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t) RX_Buffer;
		DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	} else {
		DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t) &Settings->Dummy32;
		DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	}
	
	/* Deinit first RX stream */
	DMA_Clear_Flag(Settings->RX_Stream, DMA_FLAG_ALL);
	
	/* Init RX stream */
	DMA_Init(Settings->RX_Stream, &DMA_InitStruct);
	
	/* Enable RX stream */
	Settings->RX_Stream->CR |= DMA_SxCR_EN;
	
	/* Enable TX stream */
	Settings->TX_Stream->CR |= DMA_SxCR_EN;
	
	/* Enable SPI RX & TX DMA */
	SPIx->CR2 |= SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN;
	
	/* Return OK */
	return 1;
}

uint8_t SPI_DMA_SendByte(SPI_TypeDef* SPIx, uint8_t value, uint16_t count) {
	/* Get USART settings */
	SPI_DMA_INT_t* Settings = SPI_DMA_INT_GetSettings(SPIx);
	
	/* Check if DMA available */
	if (Settings->TX_Stream->NDTR) {
		return 0;
	}
	
	/* Set dummy memory to value we specify */
	Settings->Dummy32 = value;
	
	/* Set DMA peripheral address, number of bytes and disable memory increase pointer */
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) &SPIx->DR;
	DMA_InitStruct.DMA_BufferSize = count;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	
	/* Configure TX DMA */
	DMA_InitStruct.DMA_Channel = Settings->TX_Channel;
	DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	
	/* Set memory size */
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/* Deinit first TX stream */
	DMA_Clear_Flag(Settings->TX_Stream, DMA_FLAG_ALL);
	
	/* Init TX stream */
	DMA_Init(Settings->TX_Stream, &DMA_InitStruct);
	
	/* Enable TX stream */
	Settings->TX_Stream->CR |= DMA_SxCR_EN;
	
	/* Enable SPI TX DMA */
	SPIx->CR2 |= SPI_CR2_TXDMAEN;
	
	/* Return OK */
	return 1;
}

uint8_t SPI_DMA_SendHalfWord(SPI_TypeDef* SPIx, uint16_t value, uint16_t count) {
	/* Get USART settings */
	SPI_DMA_INT_t* Settings = SPI_DMA_INT_GetSettings(SPIx);
	
	/* Check if DMA available */
	if (Settings->TX_Stream->NDTR) {
		return 0;
	}
	
	/* Set dummy memory to value we specify */
	Settings->Dummy16 = value;
	
	/* Set DMA peripheral address, number of bytes and disable memory increase pointer */
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) &SPIx->DR;
	DMA_InitStruct.DMA_BufferSize = count;
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t) &Settings->Dummy16;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
	
	/* Configure TX DMA */
	DMA_InitStruct.DMA_Channel = Settings->TX_Channel;
	DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	
	/* Set memory size */
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	/* Deinit first TX stream */
	DMA_Clear_Flag(Settings->TX_Stream, DMA_FLAG_ALL);
	
	/* Init TX stream */
	DMA_Init(Settings->TX_Stream, &DMA_InitStruct);
	
	/* Enable TX stream */
	Settings->TX_Stream->CR |= DMA_SxCR_EN;
	
	/* Enable SPI TX DMA */
	SPIx->CR2 |= SPI_CR2_TXDMAEN;
	
	/* Return OK */
	return 1;
}

uint8_t SPI_DMA_Working(SPI_TypeDef* SPIx) {
	/* Get SPI settings */
	SPI_DMA_INT_t* Settings = SPI_DMA_INT_GetSettings(SPIx);
	
	/* Check if TX or RX DMA are working */
	return (
		Settings->RX_Stream->NDTR || /*!< RX is working */
		Settings->TX_Stream->NDTR || /*!< TX is working */
		SPI_IS_BUSY(SPIx)            /*!< SPI is busy */
	);
}

DMA_Stream_TypeDef* SPI_DMA_GetStreamTX(SPI_TypeDef* SPIx) {
	/* Return pointer to TX stream */
	return SPI_DMA_INT_GetSettings(SPIx)->TX_Stream;
}

DMA_Stream_TypeDef* SPI_DMA_GetStreamRX(SPI_TypeDef* SPIx) {
	/* Return pointer to TX stream */
	return SPI_DMA_INT_GetSettings(SPIx)->RX_Stream;
}

void SPI_DMA_EnableInterrupts(SPI_TypeDef* SPIx) {
	/* Get SPI settings */
	SPI_DMA_INT_t* Settings = SPI_DMA_INT_GetSettings(SPIx);
	
	/* Enable interrupts for TX and RX streams */
	DMA_EnableInterrupts(Settings->TX_Stream);
	DMA_EnableInterrupts(Settings->RX_Stream);
}

void SPI_DMA_DisableInterrupts(SPI_TypeDef* SPIx) {
	/* Get SPI settings */
	SPI_DMA_INT_t* Settings = SPI_DMA_INT_GetSettings(SPIx);
	
	/* Enable interrupts for TX and RX streams */
	DMA_DisableInterrupts(Settings->TX_Stream);
	DMA_DisableInterrupts(Settings->RX_Stream);
}

/* Private functions */
static SPI_DMA_INT_t* SPI_DMA_INT_GetSettings(SPI_TypeDef* SPIx) {
	SPI_DMA_INT_t* result;
#ifdef SPI1
	if (SPIx == SPI1) {
		result = &SPI1_DMA_INT;
	}
#endif
#ifdef SPI2
	if (SPIx == SPI2) {
		result = &SPI2_DMA_INT;
	}
#endif
#ifdef SPI3
	if (SPIx == SPI3) {
		result = &SPI3_DMA_INT;
	}
#endif
#ifdef SPI4
	if (SPIx == SPI4) {
		result = &SPI4_DMA_INT;
	}
#endif
#ifdef SPI5
	if (SPIx == SPI5) {
		result = &SPI5_DMA_INT;
	}
#endif
#ifdef SPI6
	if (SPIx == SPI6) {
		result = &SPI6_DMA_INT;
	}
#endif

	/* Return */
	return result;
}