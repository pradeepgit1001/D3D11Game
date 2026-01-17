#pragma once
#include <DX3D/Core/Common.h>
#include <iostream>
namespace dx3d
{
	class Base
	{
	public:
		explicit Base(const BaseDesc& desc); //explicit to avoid implicit conversion and the descriptor is const and passed by reference for read only
		virtual ~Base();
		virtual Logger& getLogger() noexcept final;
	protected:
		//we don't want to create a copy or move the base class
		Base(const Base&) = delete;
		Base(Base&&) = delete;
		Base& operator = (const Base&) = delete;
		Base& operator = (Base&&) = delete;

	protected:
		Logger& m_logger;
	};
}
