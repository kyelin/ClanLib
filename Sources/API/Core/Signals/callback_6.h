/*
**  ClanLib SDK
**  Copyright (c) 1997-2013 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/


#pragma once

#include "../System/exception.h"
#include <memory>

namespace clan
{
/// \addtogroup clanCore_Signals clanCore Signals
/// \{

/// (Internal ClanLib Class)
template <typename RetVal, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Callback_Impl_6
{
public:
	virtual ~Callback_Impl_6()
	{
	}

	virtual RetVal invoke(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const = 0;
};

/// (Internal ClanLib Class)
template <typename RetVal, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Callback_Impl_6_static : public Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6>
{
public:
	Callback_Impl_6_static(RetVal (*static_func)(P1, P2, P3, P4, P5, P6))
	: static_func(static_func)
	{
	}

	RetVal invoke(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const
	{
		return static_func(p1, p2, p3, p4, p5, p6);
	}

	RetVal (*static_func)(P1, P2, P3, P4, P5, P6);
};

/// (Internal ClanLib Class)
template <typename RetVal, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename UserData>
class Callback_Impl_6_static_user : public Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6>
{
public:
	Callback_Impl_6_static_user(
		RetVal (*static_func)(P1, P2, P3, P4, P5, P6, UserData), const UserData &user_data)
	: static_func(static_func), user_data(user_data)
	{
	}

	RetVal invoke(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const
	{
		return static_func(p1, p2, p3, p4, p5, p6, user_data);
	}

	RetVal (*static_func)(P1, P2, P3, P4, P5, P6, UserData);

	UserData user_data;
};

/// (Internal ClanLib Class)
template <typename RetVal, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename InstanceClass>
class Callback_Impl_6_member : public Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6>
{
public:
	Callback_Impl_6_member(InstanceClass *instance,
		RetVal (InstanceClass::*member_func)(P1, P2, P3, P4, P5, P6))
	: instance(instance), member_func(member_func)
	{
	}

	RetVal invoke(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const
	{
		return (instance->*member_func)(p1, p2, p3, p4, p5, p6);
	}

	InstanceClass *instance;

	RetVal (InstanceClass::*member_func)(P1, P2, P3, P4, P5, P6);
};

/// (Internal ClanLib Class)
template <typename RetVal, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename InstanceClass, typename UserData>
class Callback_Impl_6_member_user : public Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6>
{
public:
	Callback_Impl_6_member_user(InstanceClass *instance,
		RetVal (InstanceClass::*member_func)(P1, P2, P3, P4, P5, P6, UserData), const UserData &user_data)
	: instance(instance), member_func(member_func), user_data(user_data)
	{
	}

	RetVal invoke(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const
	{
		return (instance->*member_func)(p1, p2, p3, p4, p5, p6, user_data);
	}

	InstanceClass *instance;

	RetVal (InstanceClass::*member_func)(P1, P2, P3, P4, P5, P6, UserData);

	UserData user_data;
};

/// (Internal ClanLib Class)
template <typename RetVal, class P1, class P2, class P3, class P4, class P5, class P6, class Functor>
class Callback_Impl_6_functor : public Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6>
{
public:
	Callback_Impl_6_functor(Functor functor)
	: functor(functor)
	{
	}

	RetVal invoke(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const
	{
		return functor(p1, p2, p3, p4, p5, p6);
	}

	Functor functor;
};

/// \brief Callback_6
///
template <typename RetVal, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Callback_6
{
public:
	Callback_6()
	{
	}

	Callback_6(const Callback_6 &copy)
	: impl(copy.impl)
	{
	}

	Callback_6(Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6> *impl)
	: impl(impl)
	{
	}

	Callback_6(RetVal (*function)(P1, P2, P3, P4, P5, P6))
	: impl(new Callback_Impl_6_static<RetVal, P1, P2, P3, P4, P5, P6>(function))
	{
	}

	template<typename UserData>
	Callback_6(RetVal (*function)(P1, P2, P3, P4, P5, P6, UserData), const UserData &user_data)
	: impl(new Callback_Impl_6_static_user<RetVal, P1, P2, P3, P4, P5, P6, UserData>(function, user_data))
	{
	}

	template<class InstanceClass>
	Callback_6(InstanceClass *instance, RetVal (InstanceClass::*function)(P1, P2, P3, P4, P5, P6))
	: impl(new Callback_Impl_6_member<RetVal, P1, P2, P3, P4, P5, P6, InstanceClass>(instance, function))
	{
	}

	template<class InstanceClass, typename UserData>
	Callback_6(InstanceClass *instance, RetVal (InstanceClass::*function)(P1, P2, P3, P4, P5, P6, UserData), const UserData &user_data)
	: impl(new Callback_Impl_6_member_user<RetVal, P1, P2, P3, P4, P5, P6, InstanceClass, UserData>(instance, function, user_data))
	{
	}

	void set(RetVal (*function)(P1, P2, P3, P4, P5, P6))
	{
		impl = std::shared_ptr< Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6> >(new Callback_Impl_6_static<RetVal, P1, P2, P3, P4, P5, P6>(function));
	}

	template<typename UserData>
	void set(RetVal (*function)(P1, P2, P3, P4, P5, P6, UserData), const UserData &user_data)
	{
		impl = std::shared_ptr< Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6> >(new Callback_Impl_6_static_user<RetVal, P1, P2, P3, P4, P5, P6, UserData>(function, user_data));
	}

	template<class InstanceClass>
	void set(InstanceClass *instance, RetVal (InstanceClass::*function)(P1, P2, P3, P4, P5, P6))
	{
		impl = std::shared_ptr< Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6> >(new Callback_Impl_6_member<RetVal, P1, P2, P3, P4, P5, P6, InstanceClass>(instance, function));
	}

	template<class InstanceClass, typename UserData>
	void set(InstanceClass *instance, RetVal (InstanceClass::*function)(P1, P2, P3, P4, P5, P6, UserData), const UserData &user_data)
	{
		impl = std::shared_ptr< Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6> >(new Callback_Impl_6_member_user<RetVal, P1, P2, P3, P4, P5, P6, InstanceClass, UserData>(instance, function, user_data));
	}

	void clear()
	{
		impl = std::shared_ptr< Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6> >();
	}

	RetVal invoke(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) const
	{
		return impl->invoke(p1, p2, p3, p4, p5, p6);
	}

	bool is_null() const
	{
		return !impl;
	}

private:
	std::shared_ptr< Callback_Impl_6<RetVal, P1, P2, P3, P4, P5, P6> > impl;
};

/// \brief Callback_6_functor
///
template <typename RetVal, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Callback_6_functor : public Callback_6<RetVal, P1, P2, P3, P4, P5, P6>
{
public:
	Callback_6_functor()
	{
	}

	Callback_6_functor(const Callback_6_functor &copy)
	: Callback_6<RetVal, P1, P2, P3, P4, P5, P6>(copy)
	{
	}

	template<class Functor>
	Callback_6_functor(Functor functor)
	: Callback_6<RetVal, P1, P2, P3, P4, P5, P6>(new Callback_Impl_6_functor<RetVal, P1, P2, P3, P4, P5, P6, Functor>(functor))
	{
	}
};

}

/// \}
