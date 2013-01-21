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
**    Magnus Norddahl
*/

#pragma once

#include "API/CSSLayout/ComputedValues/css_computed_box.h"
#include "API/CSSLayout/ComputedValues/css_computed_values.h"
#include "API/CSSLayout/CSSDocument/css_select_result.h"
#include "API/CSSLayout/CSSDocument/css_style_properties.h"

namespace clan
{

class CSSComputedValues_Impl
{
public:
	CSSComputedValues_Impl(CSSResourceCache *resource_cache) : specified_values_changed(true), box_generation(0), resource_cache(resource_cache) { }

	void update_if_changed();

	CSSComputedValues parent;

	bool specified_values_changed;

	CSSComputedBox box;
	int box_generation;

	CSSSelectResult selected_values;
	CSSStyleProperties style_values;

	CSSResourceCache *resource_cache;
};

inline void CSSComputedValues_Impl::update_if_changed()
{
	if (specified_values_changed)
	{
		const CSSComputedBox *parent_computed_box_values = (!parent.is_null()) ? &parent.get_box() : nullptr;

		box = CSSComputedBox();
		const std::vector<CSSPropertyValue *> &selected_values_vector = selected_values.get_values();
		//const std::vector<std::unique_ptr<CSSPropertyValue> > &style_values_vector = style_values.get_values();
		for (size_t i = 0; i < selected_values_vector.size(); i++) { selected_values_vector[i]->apply_to_box(box); }
		//for (size_t i = 0; i < style_values_vector.size(); i++) { style_values_vector[i]->apply_to_box(box); }

		box.compute(parent_computed_box_values, resource_cache);

		box_generation++;
		specified_values_changed = false;
	}
}

}