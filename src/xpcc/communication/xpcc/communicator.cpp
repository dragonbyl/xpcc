// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2009, Roboterclub Aachen e.V.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
// ----------------------------------------------------------------------------

#include "communicator.hpp"

// ----------------------------------------------------------------------------
xpcc::Communicator::Communicator(
		const uint8_t ownIdentifier,
		Dispatcher &inDispatcher) :
	ownIdentifier(ownIdentifier), dispatcher(inDispatcher)
{
}

// ----------------------------------------------------------------------------
void
xpcc::Communicator::callAction(uint8_t receiver, uint8_t actionIdentifier)
{
	Header header(Header::Type::REQUEST, false,
			receiver,
			this->ownIdentifier,
			actionIdentifier);
	
	SmartPointer payload;
	this->dispatcher.addMessage(header, payload);
}

void
xpcc::Communicator::callAction(uint8_t receiver, uint8_t actionIdentifier, ResponseCallback& responseCallback)
{
	Header header(Header::Type::REQUEST, false,
			receiver,
			this->ownIdentifier,
			actionIdentifier);
	
	SmartPointer payload;
	this->dispatcher.addMessage(header, payload, responseCallback);
}

// ----------------------------------------------------------------------------
void
xpcc::Communicator::publishEvent(uint8_t eventIdentifier)
{
	Header header(Header::Type::REQUEST, false,
			0,
			this->ownIdentifier,
			eventIdentifier);
	
	SmartPointer payload;
	this->dispatcher.addMessage(header, payload);
}

// ----------------------------------------------------------------------------
void
xpcc::Communicator::sendResponse(const ResponseHandle& handle)
{
	Header header(Header::Type::RESPONSE, false,
			handle.destination,
			this->ownIdentifier,
			handle.packetIdentifier);
	
	SmartPointer payload;
	this->dispatcher.addResponse(header, payload);
}

void
xpcc::Communicator::sendNegativeResponse(const ResponseHandle& handle)
{
	Header header(Header::Type::NEGATIVE_RESPONSE, false,
			handle.destination,
			this->ownIdentifier,
			handle.packetIdentifier);
	
	SmartPointer payload;
	this->dispatcher.addResponse(header, payload);
}
