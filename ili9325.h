/*
 * ili9325.h
 *
 *  Created on: 23 окт. 2016 г.
 *      Author: l-pro
 */

#ifndef ILI9325_H_
#define ILI9325_H_

#include "ili9325_registers.h"

namespace Stm32PlusPlus { namespace Display {

template<typename HardwareInterface>
class Ili9325 {
public:
	typedef HardwareInterface HW;

	enum class FrameRate : uint8_t{
		fr40 = 0,
		fr43,
		fr45,
		fr48,
		fr51,
		fr55,
		fr59,
		fr64,
		fr70,
		fr77,
		fr85,
		fr96, //(default)
		fr110,
		fr128
	};

	struct GammaCurve {
		uint16_t v[10];
	};

	static void write(uint16_t address, uint16_t data){
		HW::setAddress(address);
		HW::write(data);
	}

	static uint16_t read(uint16_t address, uint16_t data){
		HW::setAddress(address);
		return HW::read();
	}

	static void init(){
		HW::reset();

		write(Reg::DriverOutputControl::Address, Reg::DriverOutputControl::SS);
		write(Reg::LcdDrivingControl::Address, Reg::LcdDrivingControl::BC0 | Reg::LcdDrivingControl::EOR); /* set 1 line inversion */
		setOrientation(0);

		write(Reg::ResizeControl::Address, 0); //Disable resizing
		setBackAndFrontPorch(2, 2);
		write(Reg::DisplayControl3::Address, 0); //Set non-display area refresh cycle ISC[3:0]
		write(Reg::DisplayControl4::Address, 0); //FMARK function
		write(Reg::RgbDisplayInterfaceControl1::Address, 0); // RGB interface setting
		write(Reg::FrameMarkerPosition::Address, 0); //Frame marker Position
		write(Reg::RgbDisplayInterfaceControl2::Address, 0); // RGB interface polarity

		//Power On
		write(Reg::PowerControl1::Address, 0); // SAP, BT[3:0], AP, DSTB, SLP, STB
		write(Reg::PowerControl2::Address, REG_SET(Reg::PowerControl2, VC, 7));
		write(Reg::PowerControl3::Address, 0); // VREG1OUT voltage
		write(Reg::PowerControl4::Address, 0); // VDV[4:0] for VCOM amplitude
		write(Reg::DisplayControl1::Address, Reg::DisplayControl1::D0);
		HAL_Delay(200);

		// Dis-charge capacitor power voltage
		write(Reg::PowerControl1::Address, Reg::PowerControl1::AP0 | Reg::PowerControl1::APE | Reg::PowerControl1::SAP);

		write(Reg::PowerControl2::Address,
				REG_SET(Reg::PowerControl2, VC, 7) |
				REG_SET(Reg::PowerControl2, DC0, 2) |
				REG_SET(Reg::PowerControl2, DC1, 2));
		HAL_Delay(50);

		write(Reg::PowerControl3::Address, REG_SET(Reg::PowerControl3, VRH, 0xf) | Reg::PowerControl3::PON);
		HAL_Delay(50);

		write(Reg::PowerControl4::Address, REG_SET(Reg::PowerControl4, VDV, 0x15)); // VDV for VCOM amplitude

		write(Reg::PowerControl7::Address, REG_SET(Reg::PowerControl7, VCM, 0x27)); // VCM for VCOMH
		setFrameRate(FrameRate::fr128);
		HAL_Delay(50);

		//write(0x20, 0x0000); // GRAM horizontal Address
		//write(0x21, 0x0000); // GRAM Vertical Address

		//Set Gamma Curve
		GammaCurve curve = {
			0x0000,0x0707,0x0307,0x0200,0x0008,
			0x0004,0x0000,0x0707,0x0002,0x1D04
		};
		setGammaCurve(curve);

		//Set GRAM area
		write(Reg::HorizontalAddressStartPosition::Address, 0); // Horizontal GRAM Start Address
		write(Reg::HorizontalAddressEndPosition::Address, 239); // Horizontal GRAM End Address
		write(Reg::VerticalAddressStartPosition::Address, 0); // Vertical GRAM Start Address
		write(Reg::VerticalAddressEndPosition::Address, 319); // Vertical GRAM Start Address
		write(Reg::DriverOutputControl2::Address, REG_SET(Reg::DriverOutputControl2, NL, 0x27) | Reg::DriverOutputControl2::GS); // Gate Scan Line
		write(Reg::BaseImageDisplayControl::Address, Reg::BaseImageDisplayControl::REV);
		write(Reg::VerticalScrollControl::Address, 0); // set scrolling line

		//Partial Display Control
		write(Reg::PartialImage1DisplayPosition::Address, 0);
		write(Reg::PartialImage1StartLine::Address, 0);
		write(Reg::PartialImage1EndLine::Address, 0);
		write(Reg::PartialImage2DisplayPosition::Address, 0);
		write(Reg::PartialImage2StartLine::Address, 0);
		write(Reg::PartialImage2EndLine::Address, 0);

		//Panel Control
		write(Reg::PanelInterfaceControl1::Address, REG_SET(Reg::PanelInterfaceControl1, RTNI, 0x10));
		write(Reg::PanelInterfaceControl2::Address, REG_SET(Reg::PanelInterfaceControl2, NOWI, 0x06));
		write(Reg::DisplayControl1::Address,
				Reg::DisplayControl1::D0 | Reg::DisplayControl1::D1 |
				Reg::DisplayControl1::DTE | Reg::DisplayControl1::GON | Reg::DisplayControl1::BASEE); //display ON

		HAL_Delay(50);
	}

	static void setGammaCurve(GammaCurve curve){
		write(Reg::GammaControl1::Address, curve.v[0]);
		write(Reg::GammaControl2::Address, curve.v[1]);
		write(Reg::GammaControl3::Address, curve.v[2]);
		write(Reg::GammaControl4::Address, curve.v[3]);
		write(Reg::GammaControl5::Address, curve.v[4]);
		write(Reg::GammaControl6::Address, curve.v[5]);
		write(Reg::GammaControl7::Address, curve.v[6]);
		write(Reg::GammaControl8::Address, curve.v[7]);
		write(Reg::GammaControl9::Address, curve.v[8]);
		write(Reg::GammaControl10::Address, curve.v[9]);
	}

	static void setFrameRate(FrameRate frameRate){
		write(Reg::FrameRateAndColorControl::Address, REG_SET(Reg::FrameRateAndColorControl, FRS, (uint8_t)frameRate));
	}

	static bool setBackAndFrontPorch(uint8_t backPorch, uint8_t frontPorch){
		if((backPorch < 2) || (frontPorch < 2) || ((backPorch + frontPorch) > 16)){
			return false;
		}
		write(Reg::DisplayControl2::Address,
				REG_SET(Reg::DisplayControl2, BP, backPorch) |
				REG_SET(Reg::DisplayControl2, FP, frontPorch));
		return true;
	}

	static void setOrientation(uint8_t orientation){
		//TODO: remove BGR from here
		if (orientation == 0){
			write(Reg::EntryMode::Address, Reg::EntryMode::ID0 | Reg::EntryMode::ID1 | Reg::EntryMode::BGR);
		}else if (orientation == 90){
			write(Reg::EntryMode::Address, Reg::EntryMode::ID0 | Reg::EntryMode::AM | Reg::EntryMode::BGR);
		}else if (orientation == 180){
			write(Reg::EntryMode::Address, Reg::EntryMode::BGR);
		}else if (orientation == 270){
			write(Reg::EntryMode::Address, Reg::EntryMode::ID1 | Reg::EntryMode::BGR | Reg::EntryMode::AM);
		}
	}

	static void setCursor(uint16_t x, uint16_t y){
		write(Reg::HorizontalGRAMAddressSet::Address, x);
		write(Reg::VerticalGRAMAddressSet::Address, y);
	}

	static void beginWriteGram(){
		HW::setAddress(Reg::WriteDataToGRAM::Address);
	}

	static void write(uint16_t value){
		HW::write(value);
	}

	static void clear(uint16_t color){
		setCursor(0, 0);
		beginWriteGram();

		for(uint32_t index = 0; index < 320*240; index++ ){ //TODO: remove hardcode
			HW::write(color);
		}
	}
};

}}


#endif /* ILI9325_H_ */
