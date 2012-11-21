/*
**  ClanLib SDK
**  Copyright (c) 1997-2012 The ClanLib Team
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
**    Arkadiusz Kalinowski
*/

/// \addtogroup clanPhysics_Dynamics clanPhysics Dynamics
/// \{

#pragma once

#include "../api_physics.h"
#include <memory>
#include "../../Core/Math/vec2.h"

namespace clan
{

class PhysicWorld;
class BodyDescription;
class Body_Impl;
class FixtureDescription;

/// \brief Body class
///
/// \xmlonly !group=Physics/Dynamics! !header=body.h! \endxmlonly
class CL_API_PHYSICS Body
{
public:
	/// \brief Constructs a null instance.
	Body();

	/// \brief Constructs a World
	///
	/// \param description = Body Description
	Body(const BodyDescription &description);

	~Body();

/// \}
/// \name Attributes
/// \{
public:

	/// \brief Returns true if this object is invalid.
	bool is_null() const { return !impl; }

	/// \brief Throw an exception if this object is invalid.
	void throw_if_null() const;

	/// \brief Get the position of the body.
	Vec2f get_position() const;

	/// \brief Get the angle of the body
	Angle get_angle() const;

	/// \brief Return the linear velocity of the body.
	Vec2f get_linear_velocity() const;

	/// \brief Return the angular velocity of the body.
	Angle get_angular_velocity() const;


/// \}
/// \name Operations
/// \{
public:

	/// \brief add a fixture to the body.
	//Fixture create_fixture(const FixtureDescription &fixture);

	/// \brief set the position of the body.
	void set_position(const Vec2f &pos);

	/// \brief set the angle of the body
	void set_angle(const Angle &angle);

	/// \brief set the linear velocity of the body.
	void set_linear_velocity(const Vec2f &velocity);

	/// \brief set the angular velocity of the body.
	void set_angular_velocity(const Angle &velocity);

/// \}
/// \name Implementation
/// \{
private:

	std::shared_ptr<Body_Impl> impl;
/// \}
	friend class Fixture_Impl;
};

}
/// \}