#include <DX3D/Core/Base.h>
using namespace dx3d;

/**
 * @brief Construct the Base object.
 *
 * Stores a reference to the provided Logger. Base is a lightweight common
 * ancestor providing access to the logger for derived classes.
 *
 * @param desc Base descriptor containing Logger reference
 */
dx3d::Base::Base(const BaseDesc& desc): m_logger(desc.logger)
{
	std::clog << "BASE CONSTRUCTOR" << "\n";
}

/**
 * @brief Base destructor.
 *
 * Logs base destruction. Actual resource cleanup is performed by derived classes.
 */
dx3d::Base::~Base()
{
	std::clog << "base destructor" << "\n";
}

/**
 * @brief Access the logger associated with this Base instance.
 *
 * @return Logger& reference to the logger
 */
Logger& dx3d::Base::getLogger() noexcept
{
	return m_logger;
}
