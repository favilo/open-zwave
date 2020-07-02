/*
 * Irrigation.cpp
 *
 *  Created on: Jul 10, 2018
 *      Author: klah
 */

#include "command_classes/CommandClasses.h"
#include "command_classes/Irrigation.h"
#include "Defs.h"
#include "Msg.h"
#include "Node.h"
#include "Driver.h"
#include "platform/Log.h"

#include "value_classes/ValueBool.h"

namespace OpenZWave
{
	namespace Internal
	{
		namespace CC
		{

			enum IrrigationCmd
			{
				IrrigationCmd_SystemInfoGet			= 0x01,
				IrrigationCmd_SystemInfoReport  	= 0x02,
				IrrigationCmd_SystemStatusGet		= 0x03,
				IrrigationCmd_SystemStatusReport	= 0x04,
				IrrigationCmd_SystemConfigSet		= 0x05,
				IrrigationCmd_SystemConfigGet  		= 0x06,
				IrrigationCmd_SystemConfigReport	= 0x07,

				IrrigationCmd_ValveInfoGet			= 0x08,
				IrrigationCmd_ValveInfoReport		= 0x09,

				IrrigationCmd_ValveConfigSet		= 0x0A,
				IrrigationCmd_ValveConfigGet		= 0x0B,
				IrrigationCmd_ValveConfigReport		= 0x0C,

				IrrigationCmd_ValveRun				= 0x0D,

				IrrigationCmd_ValveTableSet			= 0x0E,
				IrrigationCmd_ValveTableGet			= 0x0F,
				IrrigationCmd_ValveTableReport		= 0x10,
				IrrigationCmd_ValveTableRun			= 0x11,

				IrrigationCmd_Shutoff				= 0x12
			};

			enum {
				// System Info
				IrrigationIndex_MasterValvePresent = 1,
				IrrigationIndex_TotalValves,
				IrrigationIndex_TotalValveTables,
				IrrigationIndex_MaxValveTableSize,

				// System Status
				IrrigationIndex_SystemVoltage,

				// Sensor Status bits
				// 0 = Flow Sensor Detected
				// 1 = Pressure Sensor Detected
				// 2 = Rain Sensor Detected
				// 3 = Moisture Sensor Detected
				// 4–7 = Reserved
				IrrigationIndex_SensorStatusBitSet,


				IrrigationIndex_Flow,
				IrrigationIndex_Pressure,
				IrrigationIndex_ShutoffDuration,

				// System Error Status bits
				// 0 = device has not been programmed
				// 1 = device has experienced emergency shutdown
				// 2 = system pressure high threshold has been triggered
				// 3 = system pressure low threshold has been triggered
				// 4 = valve (master or zone) is reporting errors. Valves can be checked with IrrigationCmd_ValveInfoGet
				// 5-7 = Reserved
				IrrigationIndex_SystemErrorStatus,
				IrrigationIndex_MasterValveOn,
				IrrigationIndex_ValveIdOn,

				// System Config
				IrrigationIndex_MasterValveDelay,
				IrrigationIndex_HighPressureThreshold,
				IrrigationIndex_LowPressureThreshold,
				// Sensor Polarity Bits
				// 0 = Rain Sensor Polarity (0 LOW, 1 HIGH)
				// 1 = Moisture Sensor Polarity (0 LOW, 1 HIGH)
				// 2-6 = Reserved
				// 7 = Valid
				IrrigationIndex_SensorPolarity,

				IrrigationIndex_ValveInfoStart = 0x100,
				IrrigationIndex_ValveConfigStart = 0x200,

			};

			//-----------------------------------------------------------------------------
			// <Irrigation::RequestState>
			// Request current state from the device
			//-----------------------------------------------------------------------------
			bool Irrigation::RequestState
			(
					uint32 const _requestFlags,
					uint8 const _instance,
					Driver::MsgQueue const _queue
				)
			{
				// XXX: Fix this
				if( _requestFlags & RequestFlag_Dynamic )
				{
					return RequestValue( _requestFlags, 0, _instance, _queue );
				}

				return false;
			}

			bool Irrigation::RequestValue
			(
				uint32 const _requestFlags,
				uint8 const _dummy1,	// = 0 (not used)
				uint8 const _instance,
				Driver::MsgQueue const _queue
			)
			{

				// XXX: implement
				return false;
			}

			bool Irrigation::HandleMsg
			(
					const uint8* _data,
					const uint32 _length,
					const uint32 _instance
			)
			{
				// XXX: implement
				return false;
			}

			bool Irrigation::SetValue
			(
					const Value& _value
			)
			{
				// XXX: implement
				return false;
			}

			void Irrigation::CreateVars
			(
					const uint8 _instance
			)
			{
				if( Node* node = GetNodeUnsafe() )
				{
					node->CreateValueBool(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_MasterValvePresent, "Master Valve Present", "", true, false, false, 0);
					node->CreateValueByte(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_TotalValves, "Total Number of Valves", "", true, false, 0, 0);
					node->CreateValueByte(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_TotalValveTables, "Total Number of Valve Tables", "", true, false, 0, 0);
					node->CreateValueByte(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_MaxValveTableSize, "Valve Table Max Size", "", true, false, 0, 0);

					node->CreateValueByte(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_SystemVoltage, "System Voltage", "V", true, false, 0, 0);
					node->CreateValueBitSet(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_SensorStatusBitSet, "Sensor Status", "", true, false, 0, 0);
					node->CreateValueDecimal(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_Flow, "Flow Reading", "l/h", true, false, "0.0", 0);
					node->CreateValueDecimal(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_Pressure, "Pressure Reading", "kPa", true, false, "0.0", 0);
					node->CreateValueByte(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_ShutoffDuration, "Shutoff Duration", "h", true, false, 0, 0);
					node->CreateValueBitSet(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_SystemErrorStatus, "System Error Status", "", true, false, 0, 0);
					node->CreateValueBool(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_MasterValveOn, "Master Valve On", "", true, false, false, 0);
					node->CreateValueByte(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_ValveIdOn, "Valve ID On", "", true, false, false, 0);

					node->CreateValueByte(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_MasterValveDelay, "Master Valve Delay", "s", true, false, 0, 0);
					node->CreateValueDecimal(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_HighPressureThreshold, "High Pressure Threshold", "kPa", true, false, "0.0", 0);
					node->CreateValueDecimal(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_LowPressureThreshold, "Low Pressure Threshold", "kPa", true, false, "0.0", 0);
					node->CreateValueBitSet(ValueID::ValueGenre_User, GetCommandClassId(), _instance, IrrigationIndex_SensorPolarity, "Sensor Polarity", "", true, false, 0, 0);

					// Don't make values for the valve-info or tables. There can potentially be up to 256 of each.
					// We can do that when reading/writing to them on the device. Saving space in the indexes though
				}
			}

		}
	}
}
