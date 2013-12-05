/**
 * Copyright (c) 2006-2013 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#ifndef LOVE_GRAPHICS_OPENGL_OPENGL_H
#define LOVE_GRAPHICS_OPENGL_OPENGL_H

// LOVE
#include "graphics/Color.h"
#include "graphics/Image.h"
#include "common/Matrix.h"

// GLAD
#include "libraries/glad/gladfuncs.hpp"

// C++
#include <vector>
#include <stack>

// The last argument to AttribPointer takes a buffer offset casted to a pointer.
#define BUFFER_OFFSET(i) ((char *) NULL + (i))

namespace love
{
namespace graphics
{
namespace opengl
{

// Awful, but the library uses the namespace in order to use the functions sanely
// with proper autocomplete in IDEs while having name mangling safety -
// no clashes with other GL libraries when linking, etc.
using namespace glad;

/**
 * Thin layer between OpenGL and the rest of the program.
 * Internally shadows some OpenGL context state for improved efficiency and
 * accuracy (compared to glGet etc.)
 * A class is more convenient and readable than plain namespaced functions, but
 * typically only one OpenGL object should be used (singleton.)
 **/
class OpenGL
{
public:

	// OpenGL GPU vendors.
	enum Vendor
	{
		VENDOR_ATI_AMD,
		VENDOR_NVIDIA,
		VENDOR_INTEL,
		VENDOR_MESA_SOFT, // Software renderer.
		VENDOR_APPLE,     // Software renderer.
		VENDOR_MICROSOFT, // Software renderer.
		VENDOR_UNKNOWN
	};

	// Vertex attributes. The values map to OpenGL generic vertex attribute
	// indices, when applicable (GLES2.)
	enum VertexAttrib
	{
		ATTRIB_POS      = 0,
		ATTRIB_TEXCOORD = 1,
		ATTRIB_COLOR    = 2,
		ATTRIB_MAX_ENUM
	};

	// A rectangle representing an OpenGL viewport or a scissor box.
	struct Viewport
	{
		int x, y;
		int w, h;

		Viewport()
			: x(0), y(0), w(0), h(0)
		{}

		Viewport(int _x, int _y, int _w, int _h)
			: x(_x), y(_y), w(_w), h(_h)
		{}
	};

	// Transformation matrix stacks.
	struct
	{
		std::stack<Matrix> transform;
		std::stack<Matrix> projection;
	} matrices;

	OpenGL();
	virtual ~OpenGL() {}

	/**
	 * Initializes some required context state based on current and default
	 * OpenGL state. Call this directly after creating an OpenGL context!
	 **/
	bool initContext();

	/**
	 * Marks current context state as invalid and deletes OpenGL objects owned
	 * by this class instance. Call this directly before potentially deleting
	 * an OpenGL context!
	 **/
	void deInitContext();

	/**
	 * Set up necessary state (matrices etc.) for drawing. This *must* be called
	 * directly before GL draws.
	 **/
	void prepareDraw();

	/**
	 * Sets the current constant color.
	 **/
	void setColor(const Color &c);

	/**
	 * Gets the current constant color.
	 **/
	Color getColor() const;

	/**
	 * Sets the current clear color for all framebuffer objects.
	 **/
	void setClearColor(const Color &c);

	/**
	 * Gets the current clear color.
	 **/
	Color getClearColor() const;

	/**
	 * Enables usage of an array for a vertex attribute when drawing.
	 * See http://www.opengl.org/sdk/docs/man/xhtml/glEnableVertexAttribArray.xml
	 **/
	void enableVertexAttribArray(VertexAttrib attrib);

	/**
	 * Disables usage of an array for a vertex attribute when drawing.
	 * See http://www.opengl.org/sdk/docs/man/xhtml/glDisableVertexAttribArray.xml
	 **/
	void disableVertexAttribArray(VertexAttrib attrib);

	/**
	 * Sets the parameters for an array of data for a vertex attribute.
	 * See http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	 **/
	void setVertexAttribArray(VertexAttrib attrib, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

	/**
	 * Sets the OpenGL rendering viewport to the specified rectangle.
	 * The y-coordinate starts at the top.
	 **/
	void setViewport(const Viewport &v);

	/**
	 * Gets the current OpenGL rendering viewport rectangle.
	 **/
	Viewport getViewport() const;

	/**
	 * Sets the scissor box to the specified rectangle.
	 * The y-coordinate starts at the top and is flipped internally.
	 **/
	void setScissor(const Viewport &v);

	/**
	 * Gets the current scissor box (regardless of whether scissoring is enabled.)
	 **/
	Viewport getScissor() const;

	/**
	 * Sets the global point size.
	 **/
	void setPointSize(float size);

	/**
	 * Gets the global point size.
	 **/
	float getPointSize() const;

	/**
	 * This will usually be 0 (system drawable), but some platforms require a
	 * non-zero FBO for rendering.
	 **/
	GLuint getDefaultFBO() const;

	/**
	 * Helper for setting the active texture unit.
	 *
	 * @param textureunit Index in the range of [0, maxtextureunits-1]
	 **/
	void setTextureUnit(int textureunit);

	/**
	 * Helper for binding an OpenGL texture.
	 * Makes sure we aren't redundantly binding textures.
	 **/
	void bindTexture(GLuint texture);

	/**
	 * Helper for binding a texture to a specific texture unit.
	 *
	 * @param textureunit Index in the range of [0, maxtextureunits-1]
	 * @param restoreprev Restore previously bound texture unit when done.
	 **/
	void bindTextureToUnit(GLuint texture, int textureunit, bool restoreprev);

	/**
	 * Helper for deleting an OpenGL texture.
	 * Cleans up if the texture is currently bound.
	 **/
	void deleteTexture(GLuint texture);

	/**
	 * Sets the image filter mode for the currently bound texture.
	 * Returns the actual amount of anisotropic filtering set.
	 **/
	float setTextureFilter(const graphics::Image::Filter &f);

	/**
	 * Returns the image filter mode for the currently bound texture.
	 **/
	graphics::Image::Filter getTextureFilter();

	/**
	 * Sets the image wrap mode for the currently bound texture.
	 **/
	void setTextureWrap(const graphics::Image::Wrap &w);

	/**
	 * Returns the image wrap mode for the currently bound texture.
	 **/
	graphics::Image::Wrap getTextureWrap();

	/**
	 * Returns the maximum supported width or height of a texture.
	 **/
	int getMaxTextureSize() const;

	/**
	 * Get the GPU vendor of this OpenGL context.
	 **/
	Vendor getVendor() const;

private:

	void initVendor();
	void initOpenGLFunctions();
	void initMaxValues();
	void initMatrices();
	void createDefaultTexture();

	GLint getGLAttrib(VertexAttrib attrib);

	bool contextInitialized;

	float maxAnisotropy;
	int maxTextureSize;

	Vendor vendor;

	// Tracked OpenGL state.
	struct
	{
		// Current constant color.
		Color color;

		Color clearColor;

		// Texture unit state (currently bound texture for each texture unit.)
		std::vector<GLuint> textureUnits;

		// Currently active texture unit.
		int curTextureUnit;

		Viewport viewport;
		Viewport scissor;

		float pointSize;

		GLuint defaultFBO;

	} state;

}; // OpenGL

// OpenGL class instance singleton.
extern OpenGL gl;

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_OPENGL_H
