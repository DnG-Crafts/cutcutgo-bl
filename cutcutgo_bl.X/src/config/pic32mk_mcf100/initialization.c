/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include "device.h"
#include "clock_config.h"
#include "buttons.h"
#include "led.h"



// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************

/*
 * Configuration bits for PIC32MK1024MCF100.
 * Oscillator-dependent settings come from clock_config.h.
 */

/*** DEVCFG0 ***/
#ifdef __DEBUG
    #pragma config DEBUG =      ON
#else
    #pragma config DEBUG =      OFF
#endif
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx1
#pragma config TRCEN =      OFF
#pragma config BOOTISA =    MIPS32
#pragma config FSLEEP =     OFF
#pragma config DBGPER =     PG_ALL
#pragma config SMCLR =      MCLR_NORM
#pragma config SOSCGAIN =   GAIN_2X
#pragma config SOSCBOOST =  ON
#pragma config POSCGAIN =   GAIN_LEVEL_3
#pragma config POSCBOOST =  ON
#pragma config EJTAGBEN =   NORMAL
#pragma config CP =         OFF

/*** DEVCFG1 ***/
#pragma config FNOSC =      SPLL
#pragma config DMTINTV =    WIN_127_128
#pragma config FSOSCEN =    OFF
#pragma config IESO =       ON
#if (BOARD_POSC_IS_CRYSTAL == 1)
    #pragma config POSCMOD =    HS
#else
    #pragma config POSCMOD =    EC
#endif
#pragma config OSCIOFNC =   OFF
#pragma config FCKSM =      CSECME
#pragma config WDTPS =      PS1048576
#pragma config WDTSPGM =    STOP
#pragma config FWDTEN =     OFF
#pragma config WINDIS =     NORMAL
#pragma config FWDTWINSZ =  WINSZ_25
#pragma config DMTCNT =     DMT31
#pragma config FDMTEN =     OFF

/*** DEVCFG2 ***/
/* SYSCLK = POSC / FPLLIDIV * FPLLMULT / FPLLODIV = 120 MHz (VCO = 480 MHz) */
#if (BOARD_POSC_MHZ == 12)
    #pragma config FPLLIDIV =   DIV_1
    #pragma config FPLLRNG =    RANGE_8_16_MHZ
    #pragma config FPLLMULT =   MUL_40
#elif (BOARD_POSC_MHZ == 24)
    #pragma config FPLLIDIV =   DIV_2
    #pragma config FPLLRNG =    RANGE_8_16_MHZ
    #pragma config FPLLMULT =   MUL_40
#elif (BOARD_POSC_MHZ == 8)
    #pragma config FPLLIDIV =   DIV_1
    #pragma config FPLLRNG =    RANGE_5_10_MHZ
    #pragma config FPLLMULT =   MUL_60
#endif
#pragma config FPLLICLK =   PLL_POSC
#pragma config FPLLODIV =   DIV_4
#pragma config VBATBOREN =  ON
#pragma config DSBOREN =    ON
#pragma config DSWDTPS =    DSPS32
#pragma config DSWDTOSC =   LPRC
#pragma config DSWDTEN =    OFF
#pragma config FDSEN =      OFF
#pragma config BORSEL =     HIGH
#pragma config UPLLEN =     ON

/*** DEVCFG3 ***/
#pragma config USERID =     0xffff
#pragma config PWMLOCK =    OFF
#pragma config FUSBIDIO2 =  ON
#pragma config FVBUSIO2 =   ON
#pragma config PGL1WAY =    ON
#pragma config PMDL1WAY =   ON
#pragma config IOL1WAY =    ON
#pragma config FUSBIDIO1 =  ON
#pragma config FVBUSIO1 =   ON

/*** BF1SEQ ***/
#pragma config TSEQ =       0x0
#pragma config CSEQ =       0xffff




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="DRV_MEMORY Instance 0 Initialization Data">

static uint8_t gDrvMemory0EraseBuffer[NVM_ERASE_BUFFER_SIZE] CACHE_ALIGN;

static DRV_MEMORY_CLIENT_OBJECT gDrvMemory0ClientObject[DRV_MEMORY_CLIENTS_NUMBER_IDX0];

static DRV_MEMORY_BUFFER_OBJECT gDrvMemory0BufferObject[DRV_MEMORY_BUFFER_QUEUE_SIZE_IDX0];

const DRV_MEMORY_DEVICE_INTERFACE drvMemory0DeviceAPI = {
    .Open               = DRV_NVM_Open,
    .Close              = DRV_NVM_Close,
    .Status             = DRV_NVM_Status,
    .SectorErase        = DRV_NVM_SectorErase,
    .Read               = DRV_NVM_Read,
    .PageWrite          = DRV_NVM_PageWrite,
    .EventHandlerSet    = (DRV_MEMORY_DEVICE_EVENT_HANDLER_SET)DRV_NVM_EventHandlerSet,
    .GeometryGet        = (DRV_MEMORY_DEVICE_GEOMETRY_GET)DRV_NVM_GeometryGet,
    .TransferStatusGet  = (DRV_MEMORY_DEVICE_TRANSFER_STATUS_GET)DRV_NVM_TransferStatusGet
};

const DRV_MEMORY_INIT drvMemory0InitData =
{
    .memDevIndex                = 0,
    .memoryDevice               = &drvMemory0DeviceAPI,
    .isMemDevInterruptEnabled   = true,
    .isFsEnabled                = false,
    .ewBuffer                   = &gDrvMemory0EraseBuffer[0],
    .clientObjPool              = (uintptr_t)&gDrvMemory0ClientObject[0],
    .bufferObj                  = (uintptr_t)&gDrvMemory0BufferObject[0],
    .queueSize                  = DRV_MEMORY_BUFFER_QUEUE_SIZE_IDX0,
    .nClientsMax                = DRV_MEMORY_CLIENTS_NUMBER_IDX0
};

// </editor-fold>


// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************
/******************************************************
 * USB Driver Initialization
 ******************************************************/
 
uint8_t __attribute__((aligned(512))) endPointTable1[DRV_USBFS_ENDPOINTS_NUMBER * 32];


const DRV_USBFS_INIT drvUSBFSInit =
{
	 /* Assign the endpoint table */
    .endpointTable= endPointTable1,


	/* Interrupt Source for USB module */
	.interruptSource = INT_SOURCE_USB_1,


    
    /* USB Controller to operate as USB Device */
    .operationMode = DRV_USBFS_OPMODE_DEVICE,
	
	.operationSpeed = USB_SPEED_FULL,
 
	/* Stop in idle */
    .stopInIdle = false,
	
	    /* Suspend in sleep */
    .suspendInSleep = false,
 
    /* Identifies peripheral (PLIB-level) ID */
    .usbID = USB_ID_1,
	

};








// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************



/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize_Min ( void* data )
{
    
    /* Start out with interrupts disabled before configuring any modules */
    __builtin_disable_interrupts();

    
    CLK_Initialize();


    /* Configure KSEG0 as cacheable memory. This is needed for Prefetch Buffer */
    __builtin_mtc0(16, 0,(__builtin_mfc0(16, 0) | 0x3));

    /* Configure Flash Wait States and Prefetch (120 MHz SYSCLK) */
    CHECONbits.PFMWS = 3;
    CHECONbits.PREFEN = 0;   /* same as Microchip's PIC32MK reference config */


    GPIO_Initialize();

    //BSP_Initialize();
    
    buttons_init();
    led_init();

	/* Enable global interrupts */
    __builtin_enable_interrupts();

}

void SYS_Initialize_Remaining ( void* data )
{
    
    /* Start out with interrupts disabled before configuring any modules */
    __builtin_disable_interrupts();

    
    NVM_Initialize();


    sysObj.drvMemory0 = DRV_MEMORY_Initialize((SYS_MODULE_INDEX)DRV_MEMORY_INDEX_0, (SYS_MODULE_INIT *)&drvMemory0InitData);



    /* Initialize USB Driver */ 
    sysObj.drvUSBFSObject = DRV_USBFS_Initialize(DRV_USBFS_INDEX_0, (SYS_MODULE_INIT *) &drvUSBFSInit);	


     /* Initialize the USB device layer */
    sysObj.usbDevObject0 = USB_DEVICE_Initialize (USB_DEVICE_INDEX_0 , ( SYS_MODULE_INIT* ) & usbDevInitData);



    APP_Initialize();


    EVIC_Initialize();
        
	/* Enable global interrupts */
    __builtin_enable_interrupts();

}


void __WEAK SYS_DeInitialize( void *data )
{
    /* Function can be overriden with custom implementation */
}


/*******************************************************************************
 End of File
*/
