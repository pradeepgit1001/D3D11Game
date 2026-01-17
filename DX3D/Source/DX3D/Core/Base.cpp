#include <DX3D/Core/Base.h>
using namespace dx3d;

dx3d::Base::Base(const BaseDesc& desc): m_logger(desc.logger)
{
	std::clog << "BASE CONSTRUCTOR" << "\n";
}

dx3d::Base::~Base()
{
	std::clog << "base destructor" << "\n";
}

Logger& dx3d::Base::getLogger() noexcept
{
	return m_logger;
}
