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

#include "GUI/precomp.h"
#include "gui_css_display_visitor.h"
#include "../gui_element.h"

namespace clan
{

void GUICSSDisplayVisitor::node(GUIComponent_Impl *node)
{
	if (node->visible) // invisible components evaluates to display: none
	{
		const CSSComputedBox &properties = node->element.get_css_values().get_box();
		switch (properties.display.type)
		{
		case CSSValueDisplay::type_flex:
			flex_node(node);
			break;
		case CSSValueDisplay::type_clan_grid:
			clan_grid_node(node);
			break;
		case CSSValueDisplay::type_clan_stacked:
			clan_stacked_node(node);
			break;
		//default:
		//	throw Exception("Unsupported display type for GUI components");
		}
	}
}

void GUICSSDisplayVisitor::flex_node(GUIComponent_Impl *node)
{
	const CSSComputedFlex &properties = node->element.get_css_values().get_flex();
	if (properties.flex_direction.type == CSSValueFlexDirection::type_column || properties.flex_direction.type == CSSValueFlexDirection::type_column_reverse)
	{
		flex_vertical_node(node);
	}
	else if (properties.flex_direction.type == CSSValueFlexDirection::type_row || properties.flex_direction.type == CSSValueFlexDirection::type_row_reverse)
	{
		flex_horizontal_node(node);
	}
	else
	{
		throw Exception("Unexpected CSS flex-direction computed value");
	}
}

void GUICSSDisplayVisitor::clan_grid_node(GUIComponent_Impl *node)
{
	throw Exception("-clan-grid layout not implemented yet");
}

void GUICSSDisplayVisitor::clan_stacked_node(GUIComponent_Impl *node)
{
	throw Exception("-clan-stacked layout not implemented yet");
}

CSSUsedValue GUICSSDisplayVisitor::get_used_noncontent_width(const GUICSSUsedValues &values)
{
	return values.margin.left + values.border.left + values.padding.left + values.padding.right + values.border.right + values.margin.right;
}

CSSUsedValue GUICSSDisplayVisitor::get_used_noncontent_height(const GUICSSUsedValues &values)
{
	return values.margin.top + values.border.top + values.padding.top + values.padding.bottom + values.border.bottom + values.margin.bottom;
}

float GUICSSDisplayVisitor::get_css_relative_x(GUIComponent_Impl *node, float containing_width)
{
	const CSSComputedBox &properties = node->element.get_css_values().get_box();
	if (properties.position.type == CSSValuePosition::type_relative)
	{
		if (properties.left.type == CSSValueLeft::type_length)
			return properties.left.length.value;
		else if (properties.left.type == CSSValueLeft::type_percentage)
			return properties.left.percentage / 100.0f * containing_width;
		else
			return 0.0f;
	}
	else
	{
		return 0.0f;
	}
}

float GUICSSDisplayVisitor::get_css_relative_y(GUIComponent_Impl *node, float containing_height)
{
	const CSSComputedBox &properties = node->element.get_css_values().get_box();
	if (properties.position.type == CSSValuePosition::type_relative)
	{
		if (properties.top.type == CSSValueTop::type_length)
			return properties.top.length.value;
		else if (properties.top.type == CSSValueTop::type_percentage)
			return properties.top.percentage / 100.0f * containing_height;
		else
			return 0.0f;
	}
	else
	{
		return 0.0f;
	}
}

bool GUICSSDisplayVisitor::is_normal_flow(GUIComponent_Impl *node)
{
	return
		node->visible &&
		node->element.get_css_values().get_box().display.type != CSSValueDisplay::type_none &&
		node->element.get_css_values().get_box().position.type != CSSValuePosition::type_absolute &&
		node->element.get_css_values().get_box().position.type != CSSValuePosition::type_fixed &&
		node->use_auto_geometry;
}

}
