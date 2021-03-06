#include "stm32f4_spi.h"

/* Private functions */
static void SPIx_Init(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack, SPI_Mode_t SPI_Mode, uint16_t SPI_BaudRatePrescaler, uint16_t SPI_MasterSlave, uint16_t SPI_FirstBit);
void SPI1_INT_InitPins(SPI_PinsPack_t pinspack);
void SPI2_INT_InitPins(SPI_PinsPack_t pinspack);
void SPI3_INT_InitPins(SPI_PinsPack_t pinspack);
void SPI4_INT_InitPins(SPI_PinsPack_t pinspack);
void SPI5_INT_InitPins(SPI_PinsPack_t pinspack);
void SPI6_INT_InitPins(SPI_PinsPack_t pinspack);

void SPI_Inits(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack) {
	/* Init with default settings */
#ifdef USE_SPI1
	if (SPIx == SPI1) {
		SPIx_Init(SPI1, pinspack, SPI1_MODE, SPI1_PRESCALER, SPI1_MASTERSLAVE, SPI1_FIRSTBIT);
	}
#endif
#ifdef USE_SPI2
	if (SPIx == SPI2) {
		SPIx_Init(SPI2, pinspack, SPI2_MODE, SPI2_PRESCALER, SPI2_MASTERSLAVE, SPI2_FIRSTBIT);
	}
#endif
#ifdef USE_SPI3
	if (SPIx == SPI3) {
		SPIx_Init(SPI3, pinspack, SPI3_MODE, SPI3_PRESCALER, SPI3_MASTERSLAVE, SPI3_FIRSTBIT);
	}
#endif
#ifdef USE_SPI4
	if (SPIx == SPI4) {
		SPIx_Init(SPI4, pinspack, SPI4_MODE, SPI4_PRESCALER, SPI4_MASTERSLAVE, SPI4_FIRSTBIT);
	}
#endif
#ifdef USE_SPI5
	if (SPIx == SPI5) {
		SPIx_Init(SPI5, pinspack, SPI5_MODE, SPI5_PRESCALER, SPI5_MASTERSLAVE, SPI5_FIRSTBIT);
	}
#endif
#ifdef USE_SPI6
	if (SPIx == SPI6) {
		SPIx_Init(SPI6, pinspack, SPI6_MODE, SPI6_PRESCALER, SPI6_MASTERSLAVE, SPI6_FIRSTBIT);
	}
#endif
}

void SPI_InitWithMode(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack, SPI_Mode_t SPI_Mode) {
	/* Init with custom mode, 0, 1, 2, 3 */
#ifdef USE_SPI1
	if (SPIx == SPI1) {
		SPIx_Init(SPI1, pinspack, SPI_Mode, SPI1_PRESCALER, SPI1_MASTERSLAVE, SPI1_FIRSTBIT);
	}
#endif
#ifdef USE_SPI2
	if (SPIx == SPI2) {
		SPIx_Init(SPI2, pinspack, SPI_Mode, SPI2_PRESCALER, SPI2_MASTERSLAVE, SPI2_FIRSTBIT);
	}
#endif
#ifdef USE_SPI3
	if (SPIx == SPI3) {
		SPIx_Init(SPI3, pinspack, SPI_Mode, SPI3_PRESCALER, SPI3_MASTERSLAVE, SPI3_FIRSTBIT);
	}
#endif
#ifdef USE_SPI4
	if (SPIx == SPI4) {
		SPIx_Init(SPI4, pinspack, SPI_Mode, SPI4_PRESCALER, SPI4_MASTERSLAVE, SPI4_FIRSTBIT);
	}
#endif
#ifdef USE_SPI5
	if (SPIx == SPI5) {
		SPIx_Init(SPI5, pinspack, SPI_Mode, SPI5_PRESCALER, SPI5_MASTERSLAVE, SPI5_FIRSTBIT);
	}
#endif
#ifdef USE_SPI6
	if (SPIx == SPI6) {
		SPIx_Init(SPI6, pinspack, SPI_Mode, SPI6_PRESCALER, SPI6_MASTERSLAVE, SPI6_FIRSTBIT);
	}
#endif
}

void SPI_InitFull(
	SPI_TypeDef* SPIx,              \
	SPI_PinsPack_t pinspack,     \
	uint16_t SPI_BaudRatePrescaler, \
	SPI_Mode_t Spi_Mode_t,       \
	uint16_t SPI_Mode,              \
	uint16_t SPI_FirstBit           \
) {
	/* Init FULL SPI settings by user */
#ifdef USE_SPI1
	if (SPIx == SPI1) {
		SPIx_Init(SPI1, pinspack, Spi_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
#ifdef USE_SPI2
	if (SPIx == SPI2) {
		SPIx_Init(SPI2, pinspack, Spi_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
#ifdef USE_SPI3
	if (SPIx == SPI3) {
		SPIx_Init(SPI3, pinspack, Spi_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
#ifdef USE_SPI4
	if (SPIx == SPI4) {
		SPIx_Init(SPI4, pinspack, Spi_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
#ifdef USE_SPI5
	if (SPIx == SPI5) {
		SPIx_Init(SPI5, pinspack, Spi_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
#ifdef USE_SPI6
	if (SPIx == SPI6) {
		SPIx_Init(SPI6, pinspack, Spi_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
}

uint16_t SPI_GetPrescalerFromMaxFrequency(SPI_TypeDef* SPIx, uint32_t MAX_SPI_Frequency) {
	RCC_ClocksTypeDef RCC_Clocks;
	uint32_t APB_Frequency;
	uint8_t i;
	
	/* Prevent false input */
	if (MAX_SPI_Frequency == 0) {
		return SPI_BaudRatePrescaler_256;
	}
	
	/* Get clock values from RCC */
	RCC_GetClocksFreq(&RCC_Clocks);
	
	/* Calculate max SPI clock */
	if (0
#ifdef USE_SPI1	
		|| SPIx == SPI1
#endif
#ifdef USE_SPI4
		|| SPIx == SPI4
#endif
#ifdef USE_SPI5
		|| SPIx == SPI5
#endif
#ifdef USE_SPI6
		|| SPIx == SPI6
#endif
	) {
		APB_Frequency = RCC_Clocks.PCLK2_Frequency;
	} else {
		APB_Frequency = RCC_Clocks.PCLK1_Frequency;
	}
	
	/* Calculate prescaler value */
	/* Bits 5:3 in CR1 SPI registers are prescalers */
	/* 000 = 2, 001 = 4, 002 = 8, ..., 111 = 256 */
	for (i = 0; i < 8; i++) {
		if (APB_Frequency / (1 << (i + 1)) <= MAX_SPI_Frequency) {
			/* Bits for BP are 5:3 in CR1 register */
			return (i << 3);
		}
	}
	
	/* Use max prescaler possible */
	return SPI_BaudRatePrescaler_256;
}

SPI_DataSize_t SPI_SetDataSize(SPI_TypeDef* SPIx, SPI_DataSize_t DataSize) {
	SPI_DataSize_t status = (SPIx->CR1 & SPI_CR1_DFF) ? SPI_DataSize_16bit : SPI_DataSize_8bit;
	
	/* Disable SPI first */
	SPIx->CR1 &= ~SPI_CR1_SPE;
	
	/* Set proper value */
	if (DataSize == SPI_DataSize_16bit) {
		/* Set bit for frame */
		SPIx->CR1 |= SPI_CR1_DFF;
	} else {
		/* Clear bit for frame */
		SPIx->CR1 &= ~SPI_CR1_DFF;
	}
	
	/* Enable SPI back */
	SPIx->CR1 |= SPI_CR1_SPE;
	
	/* Return status */
	return status;
}

void SPI_SendMulti(SPI_TypeDef* SPIx, uint8_t* dataOut, uint8_t* dataIn, uint32_t count) {
	uint32_t i;
	
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		/* Fill output buffer with data */
		SPIx->DR = dataOut[i];
		
		/* Wait for SPI to end everything */
		SPI_WAIT(SPIx);
		
		/* Read data register */
		dataIn[i] = SPIx->DR;
	}
}

void SPI_WriteMulti(SPI_TypeDef* SPIx, uint8_t* dataOut, uint32_t count) {
	uint32_t i;	
	
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		/* Fill output buffer with data */
		SPIx->DR = dataOut[i];
		
		/* Wait for SPI to end everything */
		SPI_WAIT(SPIx);
		
		/* Read data register */
		(void)SPIx->DR;
	}
}

void SPI_ReadMulti(SPI_TypeDef* SPIx, uint8_t* dataIn, uint8_t dummy, uint32_t count) {
	uint32_t i;
	
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		/* Fill output buffer with data */
		SPIx->DR = dummy;
		
		/* Wait for SPI to end everything */
		SPI_WAIT(SPIx);
		
		/* Save data to buffer */
		dataIn[i] = SPIx->DR;
	}
}

void SPI_SendMulti16(SPI_TypeDef* SPIx, uint16_t* dataOut, uint16_t* dataIn, uint32_t count) {
	uint32_t i;	
	
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		/* Fill output buffer with data */
		SPIx->DR = dataOut[i];
		
		/* Wait for SPI to end everything */
		SPI_WAIT(SPIx);
		
		/* Read data register */
		dataIn[i] = SPIx->DR;
	}
}

void SPI_WriteMulti16(SPI_TypeDef* SPIx, uint16_t* dataOut, uint32_t count) {
	uint32_t i;
	
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		/* Fill output buffer with data */
		SPIx->DR = dataOut[i];
		
		/* Wait for SPI to end everything */
		SPI_WAIT(SPIx);
		
		/* Read data register */
		(void)SPIx->DR;
	}
}

void SPI_ReadMulti16(SPI_TypeDef* SPIx, uint16_t* dataIn, uint16_t dummy, uint32_t count) {
	uint32_t i;
	
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPIx);
	
	for (i = 0; i < count; i++) {
		/* Fill output buffer with data */
		SPIx->DR = dummy;
		
		/* Wait for SPI to end everything */
		SPI_WAIT(SPIx);
		
		/* Save data to buffer */
		dataIn[i] = SPIx->DR;
	}
}

__weak void SPI_InitCustomPinsCallback(SPI_TypeDef* SPIx, uint16_t AlternateFunction) {
	/* Custom user function. */
	/* In case user needs functionality for custom pins, this function should be declared outside this library */
}

/* Private functions */
static void SPIx_Init(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack, SPI_Mode_t SPI_Mode, uint16_t SPI_BaudRatePrescaler, uint16_t SPI_MasterSlave, uint16_t SPI_FirstBit) {
	SPI_InitTypeDef SPI_InitStruct;

	/* Set default settings */
	SPI_StructInit(&SPI_InitStruct);
#ifdef USE_SPI1	
	if (SPIx == SPI1) {
		/* Enable SPI clock */
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
		
		/* Init pins */
		SPI1_INT_InitPins(pinspack);
		
		/* Set options */
		SPI_InitStruct.SPI_DataSize = SPI1_DATASIZE;
	}
#endif
#ifdef USE_SPI2
	if (SPIx == SPI2) {
		/* Enable SPI clock */
		RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
		
		/* Init pins */
		SPI2_INT_InitPins(pinspack);
		
		/* Set options */
		SPI_InitStruct.SPI_DataSize = SPI2_DATASIZE;
	}
#endif
#ifdef USE_SPI3
	if (SPIx == SPI3) {
		/* Enable SPI clock */
		RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
		
		/* Init pins */
		SPI3_INT_InitPins(pinspack);
		
		/* Set options */
		SPI_InitStruct.SPI_DataSize = SPI3_DATASIZE;
	
	}
#endif
#ifdef USE_SPI4
	if (SPIx == SPI4) {
		/* Enable SPI clock */
		RCC->APB2ENR |= RCC_APB2ENR_SPI4EN;
		
		/* Init pins */
		SPI4_INT_InitPins(pinspack);
		
		/* Set options */
		SPI_InitStruct.SPI_DataSize = SPI4_DATASIZE;
	}
#endif
#ifdef USE_SPI5
	if (SPIx == SPI5) {
		/* Enable SPI clock */
		RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
		
		/* Init pins */
		SPI5_INT_InitPins(pinspack);
		
		/* Set options */
		SPI_InitStruct.SPI_DataSize = SPI5_DATASIZE;
	}
#endif
#ifdef USE_SPI6
	if (SPIx == SPI6) {
		/* Enable SPI clock */
		RCC->APB2ENR |= RCC_APB2ENR_SPI6EN;
		
		/* Init pins */
		SPI6_INT_InitPins(pinspack);
		
		/* Set options */
		SPI_InitStruct.SPI_DataSize = SPI6_DATASIZE;
	}
#endif

	/* Fill SPI settings */
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit;
	SPI_InitStruct.SPI_Mode = SPI_MasterSlave;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	//SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;
	
	/* SPI mode */
	if (SPI_Mode == SPI_Mode_0) {
		SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	} else if (SPI_Mode == SPI_Mode_1) {
		SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	} else if (SPI_Mode == SPI_Mode_2) {
		SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
		SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	} else if (SPI_Mode == SPI_Mode_3) {
		SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
		SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	}
	
	/* Disable first */
	SPIx->CR1 &= ~SPI_CR1_SPE;
	
	/* Init SPI */
	SPI_Init(SPIx, &SPI_InitStruct);
	
	/* Enable SPI */
	SPIx->CR1 |= SPI_CR1_SPE;
}

/* Private functions */
#ifdef USE_SPI1
void SPI1_INT_InitPins(SPI_PinsPack_t pinspack) {
	/* Init SPI pins */
#if defined(GPIOA)
	if (pinspack == SPI_PinsPack_1) {
		GPIO_InitAlternate(GPIOA, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI1);
	}
#endif
#if defined(GPIOB)
	if (pinspack == SPI_PinsPack_2) {
		GPIO_InitAlternate(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI1);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI1, GPIO_AF_SPI1);
	}
}
#endif

#ifdef USE_SPI2
void SPI2_INT_InitPins(SPI_PinsPack_t pinspack) {
	/* Init SPI pins */
#if defined(GPIOB) && defined(GPIOC)
	if (pinspack == SPI_PinsPack_1) {
		GPIO_InitAlternate(GPIOB, GPIO_Pin_10, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI2);
		GPIO_InitAlternate(GPIOC, GPIO_Pin_2 | GPIO_Pin_3, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI2);
	}
#endif
#if defined(GPIOB)
	if (pinspack == SPI_PinsPack_2) {
		GPIO_InitAlternate(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI2);
	}
#endif
#if defined(GPIOI)
	if (pinspack == SPI_PinsPack_3) {
		GPIO_InitAlternate(GPIOI, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI2);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI2, GPIO_AF_SPI2);
	}
}
#endif

#ifdef USE_SPI3
void SPI3_INT_InitPins(SPI_PinsPack_t pinspack) {
	/* Enable SPI pins */
#if defined(GPIOB)
	if (pinspack == SPI_PinsPack_1) {
		GPIO_InitAlternate(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI3);
	}
#endif
#if defined(GPIOC)
	if (pinspack == SPI_PinsPack_2) {
		GPIO_InitAlternate(GPIOC, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI3);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI3, GPIO_AF_SPI3);
	}
}
#endif

#ifdef USE_SPI4
void SPI4_INT_InitPins(SPI_PinsPack_t pinspack) {
	/* Init SPI pins */
#if defined(GPIOE)
	if (pinspack == SPI_PinsPack_1) {
		GPIO_InitAlternate(GPIOE, GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI4);
	}
#endif
#if defined(GPIOE)
	if (pinspack == SPI_PinsPack_2) {
		GPIO_InitAlternate(GPIOE, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI4);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI4, GPIO_AF_SPI4);
	}
}
#endif

#ifdef USE_SPI5
void SPI5_INT_InitPins(SPI_PinsPack_t pinspack) {
	/* Init SPI pins */
#if defined(GPIOF)
	if (pinspack == SPI_PinsPack_1) {
		GPIO_InitAlternate(GPIOF, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI5);
	}
#endif
#if defined(GPIOF) && defined(GPIOH)
	if (pinspack == SPI_PinsPack_2) {
		GPIO_InitAlternate(GPIOF, GPIO_Pin_11, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI5);
		GPIO_InitAlternate(GPIOH, GPIO_Pin_6 | GPIO_Pin_7, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI5);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI5, GPIO_AF_SPI5);
	}
}
#endif

#ifdef USE_SPI6
void SPI6_INT_InitPins(SPI_PinsPack_t pinspack) {
#if defined(GPIOG)
	if (pinspack == SPI_PinsPack_1) {
		/* Init SPI pins */
		GPIO_InitAlternate(GPIOG, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_High_Speed, GPIO_AF_SPI6);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI6, GPIO_AF_SPI6);
	}
}
#endif

