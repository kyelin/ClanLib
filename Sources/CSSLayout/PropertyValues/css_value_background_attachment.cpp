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

#include "CSSLayout/precomp.h"
#include "API/CSSLayout/PropertyValues/css_value_background_attachment.h"
#include "API/CSSLayout/ComputedValues/css_computed_values_updater.h"

namespace clan
{

CSSValueBackgroundAttachment::CSSValueBackgroundAttachment()
: type(type_attachments)
{
	attachments.push_back(attachment_scroll);
}

std::string CSSValueBackgroundAttachment::get_name() const
{
	return "background-attachment";
}
std::unique_ptr<CSSPropertyValue> CSSValueBackgroundAttachment::clone() const
{
	return std::unique_ptr<CSSPropertyValue>(new CSSValueBackgroundAttachment (*this));
}


void CSSValueBackgroundAttachment::apply(CSSComputedValuesUpdater *updater)
{
	updater->get_background().background_attachment = *this;
}

void CSSValueBackgroundAttachment::compute(const CSSValueBackgroundAttachment *parent, CSSResourceCache *layout, float em_size, float ex_size)
{
	if (type == type_inherit)
	{
		if (parent)
		{
			type = parent->type;
		}
		else
		{
			type = type_attachments;
			attachments.clear();
			attachments.push_back(attachment_scroll);
		}
	}
}

std::string CSSValueBackgroundAttachment::to_string() const
{
	if (type == type_inherit)
		return "inherit";
	std::string s;
	for (size_t i = 0; i < attachments.size(); i++)
	{
		if (i > 0)
			s += ", ";
		switch (attachments[i])
		{
		case attachment_scroll:
			s += "scroll";
			break;
		case attachment_fixed:
			s += "fixed";
			break;
		case attachment_local:
			s += "local";
			break;
		}
	}
	return s;
}

}
