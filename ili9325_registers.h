/*
 * ili9325_registers.h
 *
 *  Created on: 23 окт. 2016 г.
 *      Author: l-pro
 */

#ifndef ILI9325_REGISTERS_H_
#define ILI9325_REGISTERS_H_

namespace Stm32PlusPlus { namespace Display { namespace Reg {

#define COMBINE2(__a, __b) __a##__b
#define COMBINE(__a, __b) COMBINE2(__a, __b)

#define REG_SET(__register, __fieldName, __value)\
		(((__value) & __register::__fieldName##_bitmask) << (__register::__fieldName##_offset))

namespace DriverCodeRead {
	static constexpr uint16_t Address = 0x00;
	static constexpr uint16_t VAL_bitmask = 0xffff;
	static constexpr uint16_t VAL_offset = 0;
}

namespace DriverOutputControl {
	static constexpr uint16_t Address = 0x01;
	static constexpr uint16_t SS = 1 << 8; //Shift direction select
	static constexpr uint16_t SM = 1 << 10;
}

namespace LcdDrivingControl {
	static constexpr uint16_t Address = 0x02;
	static constexpr uint16_t EOR = 1 << 8; //EOR = 1 and B/C=1 to set the line inversion
	static constexpr uint16_t BC0 = 1 << 9; //0: Frame/Field inversion, 1: Line inversion
}

namespace EntryMode {
	static constexpr uint16_t Address = 0x03;
	//Control the GRAM update direction.
	//When AM = У0Ф, the address is updated in horizontal writing direction.
	//When AM = У1Ф, the address is updated in vertical writing direction.
	static constexpr uint16_t AM  = 1 << 3;
	//Control the address counter (AC) to automatically increase or decrease
	//by 1 when update one pixel display data. Refer to the following figure for the details
	static constexpr uint16_t ID0 = 1 << 4;
	static constexpr uint16_t ID1 = 1 << 5;
	static constexpr uint16_t ORG = 1 << 7;
	static constexpr uint16_t HWM = 1 << 9;
	//RGB swap. 0 == RGB, 1 == BGR
	static constexpr uint16_t BGR = 1 << 12;
	static constexpr uint16_t DFM = 1 << 14;
	static constexpr uint16_t TRI = 1 << 15;
}

namespace ResizeControl {
	static constexpr uint16_t Address = 0x04;
	static constexpr uint16_t RSZ0 = 1 << 0;
	static constexpr uint16_t RSZ1 = 1 << 1;
	static constexpr uint16_t RCH0 = 1 << 4;
	static constexpr uint16_t RCH1 = 1 << 5;
	static constexpr uint16_t RCV0 = 1 << 8;
	static constexpr uint16_t RCV1 = 1 << 9;
}

namespace DisplayControl1 {
	static constexpr uint16_t Address = 0x07;
	//Enable internal display operations
	static constexpr uint16_t D0 = 1 << 0;
	//Turn on display
	static constexpr uint16_t D1 = 1 << 1;
	static constexpr uint16_t CL = 1 << 3;
	//DTE + GON => Set the output level of gate driver G1 ~ G320
	static constexpr uint16_t DTE = 1 << 4;
	static constexpr uint16_t GON = 1 << 5;
	//Base image display enable
	static constexpr uint16_t BASEE = 1 << 8;
	//Partial image 2 and Partial image 1 enable bits
	static constexpr uint16_t PTDE0 = 1 << 12;
	static constexpr uint16_t PTDE1 = 1 << 13;
}

namespace DisplayControl2 {
	static constexpr uint16_t Address = 0x08;
	//BP + FP <= 16 lines

	//Back porch (>= 2)
	static constexpr uint16_t BP_bitmask = 0xf;
	static constexpr uint16_t BP_offset = 0;

	//Front porch (>= 2)
	static constexpr uint16_t FP_bitmask = 0xf;
	static constexpr uint16_t FP_offset = 8;
}

namespace DisplayControl3 {
	static constexpr uint16_t Address = 0x09;

	static constexpr uint16_t ISC_bitmask = 0xf;
	static constexpr uint16_t ISC_offset = 0;

	static constexpr uint16_t PTG_bitmask = 0x3;
	static constexpr uint16_t PTG_offset = 4;
	
	static constexpr uint16_t PTS0 = 1 << 8;
	static constexpr uint16_t PTS1 = 1 << 9;
	static constexpr uint16_t PTS2 = 1 << 10;
}

namespace DisplayControl4 {
	static constexpr uint16_t Address = 0x0A;
	static constexpr uint16_t FMI0 		= 1 << 0;
	static constexpr uint16_t FMI1 		= 1 << 1;
	static constexpr uint16_t FMI2 		= 1 << 2;
	static constexpr uint16_t FMARKOE 	= 1 << 3;
}

namespace RgbDisplayInterfaceControl1 {
	static constexpr uint16_t Address 	= 0x0C;
	//RGB Interface Mode 0 == 18 bit, 1 == 16 bit, 2 == 6 bit
	static constexpr uint16_t RIM0 		= 1 << 0;
	static constexpr uint16_t RIM1 		= 1 << 1;

	static constexpr uint16_t DM0 		= 1 << 4;
	static constexpr uint16_t DM1 		= 1 << 5;
	static constexpr uint16_t RM 		= 1 << 8;
	static constexpr uint16_t ENC0 		= 1 << 12;
	static constexpr uint16_t ENC1 		= 1 << 13;
	static constexpr uint16_t ENC2 		= 1 << 14;
}

namespace FrameMarkerPosition {
	static constexpr uint16_t Address = 0x0D;
	static constexpr uint16_t FMP0 	  = 1 << 0;
	static constexpr uint16_t FMP1 	  = 1 << 1;
	static constexpr uint16_t FMP2 	  = 1 << 2;
	static constexpr uint16_t FMP3 	  = 1 << 3;
	static constexpr uint16_t FMP4 	  = 1 << 4;
	static constexpr uint16_t FMP5 	  = 1 << 5;
	static constexpr uint16_t FMP6 	  = 1 << 6;
	static constexpr uint16_t FMP7 	  = 1 << 7;
	static constexpr uint16_t FMP8 	  = 1 << 8;
}

namespace RgbDisplayInterfaceControl2 {
	static constexpr uint16_t Address = 0x0F;
	static constexpr uint16_t EPL0 	  = 1 << 0;
	static constexpr uint16_t DPL 	  = 1 << 1;
	static constexpr uint16_t HSPL 	  = 1 << 3;
	static constexpr uint16_t VSPL 	  = 1 << 4;
}

namespace PowerControl1 {
	static constexpr uint16_t Address = 0x10;
	//Standby mode
	static constexpr uint16_t STB 	  = 1 << 0;
	//Sleep mode (1 == sleep)
	static constexpr uint16_t SLP 	  = 1 << 1;
	//Deep standby
	static constexpr uint16_t DSTB 	  = 1 << 2;
	//Amplifier value
	static constexpr uint16_t AP0 	  = 1 << 4;
	static constexpr uint16_t AP1 	  = 1 << 5;
	static constexpr uint16_t AP2 	  = 1 << 6;
	//Power supply enable bit.
	static constexpr uint16_t APE 	  = 1 << 7;
	static constexpr uint16_t BT0 	  = 1 << 8;
	static constexpr uint16_t BT1 	  = 1 << 9;
	static constexpr uint16_t BT2 	  = 1 << 10;
	//SAP=0, Source driver is disabled. SAP=1, Source driver is enabled.
	static constexpr uint16_t SAP 	  = 1 << 12;
}

namespace PowerControl2 {
	static constexpr uint16_t Address = 0x11;
	//VCi ratio factor
	static constexpr uint16_t VC_bitmask = 0x7;
	static constexpr uint16_t VC_offset = 0;
	//Frequency of the step-up circuit 1
	static constexpr uint16_t DC0_bitmask = 0x7;
	static constexpr uint16_t DC0_offset = 4;
	//Frequency of the step-up circuit 2
	static constexpr uint16_t DC1_bitmask = 0x7;
	static constexpr uint16_t DC1_offset = 8;
}

namespace PowerControl3 {
	static constexpr uint16_t Address = 0x12;
	// amplifying rate
	static constexpr uint16_t VRH_bitmask = 0xf;
	static constexpr uint16_t VRH_offset = 0;
	//Control ON/OFF of circuit3 output
	static constexpr uint16_t PON 	  = 1 << 4;
	//VCIRE=0 External reference voltage Vci (default) VCIRE = 1 Internal reference voltage 2.5V
	static constexpr uint16_t VCIRE   = 1 << 7;
}

namespace PowerControl4 {
	static constexpr uint16_t Address = 0x13;
	static constexpr uint16_t VDV_bitmask = 0x1f;
	static constexpr uint16_t VDV_offset = 8;
}

namespace HorizontalGRAMAddressSet {
	static constexpr uint16_t Address = 0x20;
	static constexpr uint16_t AD0 	  = 1 << 0;
	static constexpr uint16_t AD1 	  = 1 << 1;
	static constexpr uint16_t AD2 	  = 1 << 2;
	static constexpr uint16_t AD3 	  = 1 << 3;
	static constexpr uint16_t AD4 	  = 1 << 4;
	static constexpr uint16_t AD5 	  = 1 << 5;
	static constexpr uint16_t AD6 	  = 1 << 6;
	static constexpr uint16_t AD7 	  = 1 << 7;
}

namespace VerticalGRAMAddressSet {
	static constexpr uint16_t Address = 0x21;
	static constexpr uint16_t AD8 	  = 1 << 0;
	static constexpr uint16_t AD9 	  = 1 << 1;
	static constexpr uint16_t AD10 	  = 1 << 2;
	static constexpr uint16_t AD11 	  = 1 << 3;
	static constexpr uint16_t AD12 	  = 1 << 4;
	static constexpr uint16_t AD13 	  = 1 << 5;
	static constexpr uint16_t AD14 	  = 1 << 6;
	static constexpr uint16_t AD15 	  = 1 << 7;
	static constexpr uint16_t AD16 	  = 1 << 8;
}

namespace WriteDataToGRAM {
	//Set the internal VcomH voltage.
	static constexpr uint16_t Address = 0x22;
}

namespace PowerControl7 {
	static constexpr uint16_t Address = 0x29;

	static constexpr uint16_t VCM_bitmask = 0x3f;
	static constexpr uint16_t VCM_offset = 0;
}

namespace FrameRateAndColorControl {
	static constexpr uint16_t Address = 0x2B;
	//0000 40
	//0001 43
	//0010 45
	//0011 48
	//0100 51
	//0101 55
	//0110 59
	//0111 64
	//1000 70
	//1001 77
	//1010 85
	//1011 96 (default)
	//1100 110
	//1101 128
	static constexpr uint16_t FRS_bitmask = 0xf;
	static constexpr uint16_t FRS_offset = 0;
}

namespace GammaControl1 {
	static constexpr uint16_t Address = 0x30;
}
namespace GammaControl2 {
	static constexpr uint16_t Address = 0x31;
}
namespace GammaControl3 {
	static constexpr uint16_t Address = 0x32;
}
namespace GammaControl4 {
	static constexpr uint16_t Address = 0x35;
}
namespace GammaControl5 {
	static constexpr uint16_t Address = 0x36;
}
namespace GammaControl6 {
	static constexpr uint16_t Address = 0x37;
}
namespace GammaControl7 {
	static constexpr uint16_t Address = 0x38;
}
namespace GammaControl8 {
	static constexpr uint16_t Address = 0x39;
}
namespace GammaControl9 {
	static constexpr uint16_t Address = 0x3C;
}
namespace GammaControl10 {
	static constexpr uint16_t Address = 0x3D;
}

namespace HorizontalAddressStartPosition {
	static constexpr uint16_t Address = 0x50;
}

namespace HorizontalAddressEndPosition {
	static constexpr uint16_t Address = 0x51;
}

namespace VerticalAddressStartPosition {
	static constexpr uint16_t Address = 0x52;
}

namespace VerticalAddressEndPosition {
	static constexpr uint16_t Address = 0x53;
}

namespace DriverOutputControl2 {
	static constexpr uint16_t Address = 0x60;
	static constexpr uint16_t GS 	  = 1 << 15;
	static constexpr uint16_t SCN_bitmask = 0x3f;
	static constexpr uint16_t SCN_offset = 0;
	static constexpr uint16_t NL_bitmask = 0x3f;
	static constexpr uint16_t NL_offset = 8;
}

namespace BaseImageDisplayControl {
	static constexpr uint16_t Address = 0x61;
	static constexpr uint16_t REV 	  = 1 << 0;
	static constexpr uint16_t VLE 	  = 1 << 1;
	static constexpr uint16_t NDL 	  = 1 << 2;
}

namespace VerticalScrollControl {
	static constexpr uint16_t Address = 0x6A;
	static constexpr uint16_t VL_bitmask = 0x1ff;
	static constexpr uint16_t VL_offset = 0;
}


namespace PartialImage1DisplayPosition {
	static constexpr uint16_t Address = 0x80;
	static constexpr uint16_t PTDP_bitmask = 0x1ff;
	static constexpr uint16_t PTDP_offset = 0;
}

namespace PartialImage1StartLine {
	static constexpr uint16_t Address = 0x81;
	static constexpr uint16_t PTSA_bitmask = 0x1ff;
	static constexpr uint16_t PTSA_offset = 0;
}

namespace PartialImage1EndLine {
	static constexpr uint16_t Address = 0x82;
	static constexpr uint16_t PTEA_bitmask = 0x1ff;
	static constexpr uint16_t PTEA_offset = 0;
}


namespace PartialImage2DisplayPosition {
	static constexpr uint16_t Address = 0x83;
	static constexpr uint16_t PTDP_bitmask = 0x1ff;
	static constexpr uint16_t PTDP_offset = 0;
}

namespace PartialImage2StartLine {
	static constexpr uint16_t Address = 0x84;
	static constexpr uint16_t PTSA_bitmask = 0x1ff;
	static constexpr uint16_t PTSA_offset = 0;
}

namespace PartialImage2EndLine {
	static constexpr uint16_t Address = 0x85;
	static constexpr uint16_t PTEA_bitmask = 0x1ff;
	static constexpr uint16_t PTEA_offset = 0;
}


namespace PanelInterfaceControl1 {
	static constexpr uint16_t Address = 0x90;
	static constexpr uint16_t RTNI_bitmask = 0x1f;
	static constexpr uint16_t RTNI_offset = 0;
	static constexpr uint16_t DIVI_bitmask = 0x3;
	static constexpr uint16_t DIVI_offset = 8;
}

namespace PanelInterfaceControl2 {
	static constexpr uint16_t Address = 0x92;
	static constexpr uint16_t NOWI_bitmask = 0x7;
	static constexpr uint16_t NOWI_offset = 8;
}

namespace PanelInterfaceControl4 {
	static constexpr uint16_t Address = 0x95;
	static constexpr uint16_t RTNE_bitmask = 0x3f;
	static constexpr uint16_t RTNE_offset = 0;
	static constexpr uint16_t DIVE_bitmask = 0x3;
	static constexpr uint16_t DIVE_offset = 8;
}

namespace OTPVCMProgrammingControl {
	static constexpr uint16_t Address = 0xA1;
	static constexpr uint16_t VCM_OTP_bitmask = 0x3f;
	static constexpr uint16_t VCM_OTP_offset = 0;
	static constexpr uint16_t OTP_PGM_EN_bitmask = 0x1;
	static constexpr uint16_t OTP_PGM_EN_offset = 11;
}

namespace OTPVCMStatusAndEnable {
	static constexpr uint16_t Address = 0xA2;
	static constexpr uint16_t VCM_EN = 1 << 0;
	static constexpr uint16_t VCM_D_bitmask = 0x3f;
	static constexpr uint16_t VCM_D_offset = 8;
	static constexpr uint16_t PGM_CNT_bitmask = 0x3;
	static constexpr uint16_t PGM_CNT_offset = 14;
}

namespace OTPProgrammingIDKey {
	static constexpr uint16_t Address = 0xA5;
	static constexpr uint16_t KEY_bitmask = 0xffff;
	static constexpr uint16_t KEY_offset = 0;
}

}}}


#endif /* ILI9325_REGISTERS_H_ */
