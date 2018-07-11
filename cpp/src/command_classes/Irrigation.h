/*
 * Irrigation.h
 *
 *  Created on: Jul 10, 2018
 *      Author: klah
 */

#ifndef _Irrigation_H_
#define _Irrigation_H_

#include "command_classes/CommandClass.h"

namespace OpenZWave {

	class ValueByte; // XXX: Do we need this???

	/** \brief Implements COMMAND_CLASS_IRRIGATION (0x6B), a Z-Wave device command class.
	 */
	class Irrigation: public CommandClass {
	public:
		static CommandClass* Create( uint32 const _homeId, uint8 const _nodeId ) { return new Irrigation(_homeId, _nodeId); }
		virtual ~Irrigation(){}

		static uint8 const StaticGetCommandClassId(){ return 0x6B; }
		static string const StaticGetCommandClassName(){ return "COMMAND_CLASS_IRRIGATION"; }

		// From CommandClass
		virtual bool RequestState( uint32 const _requestFlags, uint8 const _instance, Driver::MsgQueue const _queue );
		virtual bool RequestValue( uint32 const _requestFlags, uint8 const _index, uint8 const _instance, Driver::MsgQueue const _queue );
		virtual uint8 const GetCommandClassId()const{ return StaticGetCommandClassId(); }
		virtual string const GetCommandClassName()const{ return StaticGetCommandClassName(); }
		virtual bool HandleMsg( uint8 const* _data, uint32 const _length, uint32 const _instance = 1 );
		virtual bool SetValue( Value const& _value );

	protected:
		virtual void CreateVars( uint8 const _instance );

	private:
		Irrigation(uint32 const _homeId, uint8 const _nodeId): CommandClass( _homeId, _nodeId ) {}
	};

} /* namespace OpenZWave */

#endif /* _Irrigation_H_ */
