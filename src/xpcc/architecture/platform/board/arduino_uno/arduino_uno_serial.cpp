/* Copyright (c) 2014-2016, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 * ------------------------------------------------------------------------ */
#include "arduino_uno.hpp"

// Create an IODeviceWrapper around the Uart Peripheral we want to use
Board::LoggerDevice loggerDevice;

// Set all four logger streams to use the UART
xpcc::IOStream serialStream(loggerDevice);
xpcc::log::Logger xpcc::log::debug(loggerDevice);
xpcc::log::Logger xpcc::log::info(loggerDevice);
xpcc::log::Logger xpcc::log::warning(loggerDevice);
xpcc::log::Logger xpcc::log::error(loggerDevice);
