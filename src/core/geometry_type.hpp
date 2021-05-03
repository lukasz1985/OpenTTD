/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file geometry_type.hpp All geometry types in OpenTTD. */

#ifndef GEOMETRY_TYPE_HPP
#define GEOMETRY_TYPE_HPP

#if defined(__APPLE__)
	/* Mac OS X already has both Rect and Point declared */
#	define Rect OTTD_Rect
#	define Point OTTD_Point
#endif /* __APPLE__ */


/** Coordinates of a point in 2D */
struct Point {
	int x;
	int y;
};

/** Dimensions (a width and height) of a rectangle in 2D */
struct Dimension {
	uint width;
	uint height;

	Dimension(uint w = 0, uint h = 0) : width(w), height(h) {};

	bool operator< (const Dimension &other) const
	{
		int x = (*this).width - other.width;
		if (x != 0) return x < 0;
		return (*this).height < other.height;
	}

	bool operator== (const Dimension &other) const
	{
		return (*this).width == other.width && (*this).height == other.height;
	}
};

/** Specification of a rectangle with absolute coordinates of all edges */
struct Rect {
	int left;
	int top;
	int right;
	int bottom;

	/**
	 * Get width of Rect.
	 * @return width of Rect.
	 */
	inline int Width() const { return this->right - this->left + 1; }

	/**
	 * Get height of Rect.
	 * @return height of Rect.
	 */
	inline int Height() const { return this->bottom - this->top + 1; }

	/**
	 * Copy and shrink Rect by s pixels.
	 * @param s number of pixels to remove from each side of Rect.
	 * @return the new smaller Rect.
	 */
	[[nodiscard]] inline Rect Shrink(int s) const
	{
		return {this->left + s, this->top + s, this->right - s, this->bottom - s};
	}

	/**
	 * Copy and shrink Rect by h horizontal and v vertical pixels.
	 * @param h number of pixels to remove from left and right sides.
	 * @param v number of pixels to remove from top and bottom sides.
	 * @return the new smaller Rect.
	 */
	[[nodiscard]] inline Rect Shrink(int h, int v) const
	{
		return {this->left + h, this->top + v, this->right - h, this->bottom - v};
	}

	/**
	 * Copy and shrink Rect by pixels.
	 * @param left number of pixels to remove from left side.
	 * @param top number of pixels to remove from top side.
	 * @param right number of pixels to remove from right side.
	 * @param bottom number of pixels to remove from bottom side.
	 * @return the new smaller Rect.
	 */
	[[nodiscard]] inline Rect Shrink(int left, int top, int right, int bottom) const
	{
		return {this->left + left, this->top + top, this->right - right, this->bottom - bottom};
	}

	/**
	 * Copy and expand Rect by s pixels.
	 * @param s number of pixels to add to each side of Rect.
	 * @return the new larger Rect.
	 */
	[[nodiscard]] inline Rect Expand(int s) const
	{
		return this->Shrink(-s);
	}

	/**
	 * Copy and translate Rect by x,y pixels.
	 * @param x number of pixels to move horizontally.
	 * @param y number of pixels to move vertically.
	 * @return the new translated Rect.
	 */
	[[nodiscard]] inline Rect Translate(int x, int y) const
	{
		return {this->left + x, this->top + y, this->right + x, this->bottom + y};
	}

	/**
	 * Copy Rect and set its width.
	 * @param width width in pixels for new Rect.
	 * @param end   if set, set width at end of Rect, i.e. on right.
	 * @return the new resized Rect.
	 */
	[[nodiscard]] inline Rect WithWidth(int width, bool end) const
	{
		return end
			? Rect {this->right - width + 1, this->top, this->right,            this->bottom}
			: Rect {this->left,              this->top, this->left + width - 1, this->bottom};
	}

	/**
	 * Copy Rect and indent it from its position.
	 * @param indent offset in pixels for new Rect.
	 * @param end   if set, set indent at end of Rect, i.e. on right.
	 * @return the new resized Rect.
	 */
	[[nodiscard]] inline Rect Indent(int indent, bool end) const
	{
		return end
			? Rect {this->left,          this->top, this->right - indent, this->bottom}
			: Rect {this->left + indent, this->top, this->right,          this->bottom};
	}

	/**
	 * Copy Rect and set its height.
	 * @param width height in pixels for new Rect.
	 * @param end   if set, set height at end of Rect, i.e. at bottom.
	 * @return the new resized Rect.
	 */
	[[nodiscard]] inline Rect WithHeight(int height, bool end = false) const
	{
		return end
			? Rect {this->left, this->bottom - height + 1, this->right, this->bottom}
			: Rect {this->left, this->top,                 this->right, this->top + height - 1};
	}
};

/**
 * Specification of a rectangle with an absolute top-left coordinate and a
 * (relative) width/height
 */
struct PointDimension {
	int x;
	int y;
	int width;
	int height;
};

#endif /* GEOMETRY_TYPE_HPP */
