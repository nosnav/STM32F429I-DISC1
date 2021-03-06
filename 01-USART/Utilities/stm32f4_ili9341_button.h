#ifndef __STM32F4_ILI9341_BUTTON_H
#define __STM32F4_ILI9341_BUTTON_H
#ifdef __cplusplus
 extern "C" {
#endif
     
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4_i2c.h"
#include "stm32f4_delay.h"
#include "stm32f4_ili9341.h"
#include "stm32f4_fonts.h"
#include "stm32f4_stmpe811.h"

// Maximum number of buttons available
#ifndef ILI9341_BUTTON_MAX_BUTTONS
#define ILI9341_BUTTON_MAX_BUTTONS	10
#endif

//Button flags
#define BUTTON_FLAG_ENABLED			0x0001	// Button is enabled - internal flag
#define BUTTON_FLAG_NOBORDER			0x0002	// No border used in
#define BUTTON_FLAG_IMAGE			0x0004	// Use image for background
#define BUTTON_FLAG_NOLABEL			0x0008	// Do not display button label
#define BUTTON_FLAG_USED				0x8000	// Button is used - internal flag

/**
 * Button options struct
 *
 * Parameters:
 *	- uint16_t x: X coordinate of top left button corner
 *	- uint16_t y: Y coordinate of top left button corner
 *	- uint16_t width: button width in pixels
 *	- uint16_t height: button height in pixels
 *	- uint16_t background: 16bit background color
 *	- uint16_t borderColor: 16bit border color
 *	- uint16_t flags: Button flags
 *	- char *label: pointer to first character of label
 *	- FontDef_t *font: pointer to font structure
 *	- uint16_t color: label color
 *	- uint16_t *image: pointer to location at first color for pixel
 */
typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	uint16_t background;
	uint16_t borderColor;
	uint16_t flags;
	char* label;
	FontDef_t* font;
	uint16_t color;
	uint16_t* image;
} ILI9341_Button_t;

extern ILI9341_Button_t ILI9341_Buttons[ILI9341_BUTTON_MAX_BUTTONS];

/**
 * Add new button to library
 *
 * Parameters:
 * 	- ILI9341_Button_t *button: pointer to ILI9341_Button_t structure
 *
 * Returns button id on success (starting from 0), or -1 on failure
 */
extern int8_t ILI9341_Button_Add(ILI9341_Button_t* button);

/**
 * Draw button on LCD
 *
 * Parameters:
 * 	uint8_t id: button id to draw
 *
 * Return SUCCESS on success, otherwise ERROR
 */
extern ErrorStatus ILI9341_Button_Draw(uint8_t id);

/**
 * Draw all buttons in library
 *
 *
 */
extern void ILI9341_Button_DrawAll(void);

/**
 * Enable button
 *
 * Parameters:
 * 	- uint8_t id: button id
 */
extern void ILI9341_Button_Enable(uint8_t id);

/**
 * Disable button
 *
 * Parameters:
 * 	- uint8_t id: button id
 */
extern void ILI9341_Button_Disable(uint8_t id);

/**
 * Delete all buttons in library
 *
 *
 */
extern void ILI9341_Button_DeleteAll(void);

/**
 * Delete button
 *
 * Parameters:
 * 	- uint8_t id: button id
 */
extern void ILI9341_Button_Delete(uint8_t id);

/**
 * Get pressed button
 *
 * Parameters:
 * 	- STMPE811_TouchData *TouchData: pointer to STMPE811_TouchData structure
 *
 * Returns button id on success, otherwise -1
 */
extern int8_t ILI9341_Button_Touch(STMPE811_TouchData* TouchData);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4_ILI9341_BUTTON_H */

