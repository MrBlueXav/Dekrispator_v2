/**
 ******************************************************************************
 * @file    usbh_MIDI.h
 * @author  
 * @version 
 * @date    
 * @brief   This file contains all the prototypes for the usbh_MIDI.c
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Define to prevent recursive  ----------------------------------------------*/
#ifndef __USBH_MIDI_CORE_H
#define __USBH_MIDI_CORE_H

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "stm32f4_discovery.h"


/*-------------------------------------------------------------------------------*/
// buffer size (should be at least >= MIOS32_USB_MIDI_DESC_DATA_*_SIZE/4)
#define USB_MIDI_RX_BUFFER_SIZE   64 // packages
#define USB_MIDI_TX_BUFFER_SIZE   64 // packages

// size of IN/OUT pipe
#define USB_MIDI_DATA_IN_SIZE           64
#define USB_MIDI_DATA_OUT_SIZE          64

// endpoint assignments (don't change!)
#define USB_MIDI_DATA_OUT_EP 0x02
#define USB_MIDI_DATA_IN_EP  0x81
/** @defgroup USBH_MIDI_CORE_Exported_Defines
 * @{
 */
#define USB_AUDIO_CLASS                                 0x01
#define USB_MIDISTREAMING_SubCLASS                      0x03
#define USB_MIDI_DESC_SIZE                                 9


extern USBH_ClassTypeDef  MIDI_Class;
#define USBH_MIDI_CLASS    &MIDI_Class

/*-------------------------------------------------------------------------------*/
typedef enum {
	NoteOff       = 0x8,
	NoteOn        = 0x9,
	PolyPressure  = 0xa,
	CC            = 0xb,
	ProgramChange = 0xc,
	Aftertouch    = 0xd,
	PitchBend     = 0xe
} midi_event_t;


typedef enum {
	Chn1,
	Chn2,
	Chn3,
	Chn4,
	Chn5,
	Chn6,
	Chn7,
	Chn8,
	Chn9,
	Chn10,
	Chn11,
	Chn12,
	Chn13,
	Chn14,
	Chn15,
	Chn16
} midi_chn_t;


typedef union {
	struct {
		uint32_t ALL;
	};
	struct {
		uint8_t cin_cable;
		uint8_t evnt0;
		uint8_t evnt1;
		uint8_t evnt2;
	};
	struct {
		uint8_t type:4;
		uint8_t cable:4;
		uint8_t chn:4; // mios32_midi_chn_t
		uint8_t event:4; // mios32_midi_event_t
		uint8_t value1;
		uint8_t value2;
	};

	// C++ doesn't allow to redefine names in anonymous unions
	// as a simple workaround, we rename these redundant names
	struct {
		uint8_t cin:4;
		uint8_t dummy1_cable:4;
		uint8_t dummy1_chn:4; // mios32_midi_chn_t
		uint8_t dummy1_event:4; // mios32_midi_event_t
		uint8_t note:8;
		uint8_t velocity:8;
	};
	struct {
		uint8_t dummy2_cin:4;
		uint8_t dummy2_cable:4;
		uint8_t dummy2_chn:4; // mios32_midi_chn_t
		uint8_t dummy2_event:4; // mios32_midi_event_t
		uint8_t cc_number:8;
		uint8_t value:8;
	};
	struct {
		uint8_t dummy3_cin:4;
		uint8_t dummy3_cable:4;
		uint8_t dummy3_chn:4; // mios32_midi_chn_t
		uint8_t dummy3_event:4; // mios32_midi_event_t
		uint8_t program_change:8;
		uint8_t dummy3:8;
	};
} midi_package_t;


/** @addtogroup USBH_LIB
 * @{
 */

/** @addtogroup USBH_CLASS
 * @{
 */

/** @addtogroup USBH_MIDI_CLASS
 * @{
 */

/** @defgroup USBH_MIDI_CORE
 * @brief This file is the Header file for USBH_MIDI_CORE.c
 * @{
 */


/**
 * @}
 */

/** @defgroup USBH_MIDI_CORE_Exported_Types
 * @{
 */

/* States for MIDI State Machine */
//typedef enum {
//	USBH_MIDI_IDLE,
//	USBH_MIDI_RX,
//	USBH_MIDI_TX,
//} USBH_MIDI_transfer_state_t;


/* States for MIDI State Machine */
typedef enum
{
	MIDI_IDLE= 0,
	MIDI_SEND_DATA,
	MIDI_SEND_DATA_WAIT,
	MIDI_RECEIVE_DATA,
	MIDI_RECEIVE_DATA_WAIT,
}
MIDI_DataStateTypeDef;

typedef enum
{
	MIDI_IDLE_STATE= 0,
	MIDI_TRANSFER_DATA,
	MIDI_ERROR_STATE,
}
MIDI_StateTypeDef;


/**
 * @}
 */
/* Structure for MIDI process */
//typedef struct MIDI_Process
//{
//	USBH_MIDI_transfer_state_t	state;
//	//uint8_t			buff[64];
//	uint8_t         InPipe; //	hc_num_in;
//	uint8_t         OutPipe; //	hc_num_out;
//	uint8_t			OutEp;
//	uint8_t			InEp;
//	uint16_t		InEpSize;
//	uint16_t		OutEpSize;
//	uint8_t 		tx_count;
//}
//MIDI_HandleTypeDef;

//typedef struct
//{
//  uint8_t              InPipe;
//  uint8_t              OutPipe;
//  uint8_t              OutEp;
//  uint8_t              InEp;
//  uint8_t              buff[8];
//  uint16_t             OutEpSize;
//  uint16_t             InEpSize;
//}
//MIDI_DataItfTypedef ;


/* Structure for MIDI process */
typedef struct _MIDI_Process
{
	MIDI_StateTypeDef			state;
	uint8_t			InPipe;
	uint8_t			OutPipe;
	uint8_t			OutEp;
	uint8_t			InEp;
	uint16_t		OutEpSize;
	uint16_t		InEpSize;

	uint8_t			*pTxData;
	uint8_t			*pRxData;
	uint16_t		TxDataLength;
	uint16_t		RxDataLength;
	MIDI_DataStateTypeDef		data_tx_state;
	MIDI_DataStateTypeDef		data_rx_state;
	uint8_t						Rx_Poll;
	//uint8_t			buff[8];
	//MIDI_DataItfTypedef                DataItf;
	//CDC_InterfaceDesc_Typedef         CDC_Desc;
}
MIDI_HandleTypeDef;


/**
 * @}
 */

/** @defgroup USBH_MIDI_CORE_Exported_FunctionsPrototype
 * @{
 */
USBH_StatusTypeDef  USBH_MIDI_Transmit(USBH_HandleTypeDef *phost,
                                      uint8_t *pbuff,
                                      uint16_t length);

USBH_StatusTypeDef  USBH_MIDI_Receive(USBH_HandleTypeDef *phost,
                                     uint8_t *pbuff,
                                     uint16_t length);


uint16_t            USBH_MIDI_GetLastReceivedDataSize(USBH_HandleTypeDef *phost);

USBH_StatusTypeDef  USBH_MIDI_Stop(USBH_HandleTypeDef *phost);

void USBH_MIDI_TransmitCallback(USBH_HandleTypeDef *phost);

void USBH_MIDI_ReceiveCallback(USBH_HandleTypeDef *phost);

//USBH_StatusTypeDef USBH_MIDI_IOProcess (USBH_HandleTypeDef *phost);
//USBH_StatusTypeDef USBH_MIDI_Init (USBH_HandleTypeDef *phost);
/**
 * @}
 */


#endif /* __USBH_MIDI_CORE_H */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

