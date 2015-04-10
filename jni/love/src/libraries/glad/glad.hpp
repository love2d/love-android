
/**
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013 David Herberth, modified by Alex Szpakowski
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **/
 

#ifndef __glad_hpp_

#if defined(__gl_h_) || defined(__glext_h_) || defined(__glcorearb_h_) \
    || defined(__gl3_h) || defined(__gl3_ext_h)
#error OpenGL header already included, remove this include, glad already provides it
#endif

#define __glad_hpp_
#define __gl_h_

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>

#ifdef near
#undef near
#endif

#ifdef far
#undef far
#endif

#endif

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif

namespace glad {

bool gladLoadGL(void);

typedef void* (* LOADER)(const char *name);
bool gladLoadGLLoader(LOADER);


#include <stddef.h>
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLclampx;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void *GLeglImageOES;
typedef char GLchar;
typedef char GLcharARB;
#ifdef __APPLE__
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
typedef unsigned short GLhalfARB;
typedef unsigned short GLhalf;
typedef GLint GLfixed;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef ptrdiff_t GLintptrARB;
typedef ptrdiff_t GLsizeiptrARB;
typedef int64_t GLint64EXT;
typedef uint64_t GLuint64EXT;
typedef struct __GLsync *GLsync;
struct _cl_context;
struct _cl_event;
typedef void (APIENTRY *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (APIENTRY *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (APIENTRY *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (APIENTRY *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
typedef unsigned short GLhalfNV;
typedef GLintptr GLvdpauSurfaceNV;

 /* GL_VERSION_1_0 */
extern GLboolean GLAD_VERSION_1_0;
typedef void (APIENTRYP pfn_glCullFace) (GLenum);
extern pfn_glCullFace fp_glCullFace;
typedef void (APIENTRYP pfn_glFrontFace) (GLenum);
extern pfn_glFrontFace fp_glFrontFace;
typedef void (APIENTRYP pfn_glHint) (GLenum, GLenum);
extern pfn_glHint fp_glHint;
typedef void (APIENTRYP pfn_glLineWidth) (GLfloat);
extern pfn_glLineWidth fp_glLineWidth;
typedef void (APIENTRYP pfn_glPointSize) (GLfloat);
extern pfn_glPointSize fp_glPointSize;
typedef void (APIENTRYP pfn_glPolygonMode) (GLenum, GLenum);
extern pfn_glPolygonMode fp_glPolygonMode;
typedef void (APIENTRYP pfn_glScissor) (GLint, GLint, GLsizei, GLsizei);
extern pfn_glScissor fp_glScissor;
typedef void (APIENTRYP pfn_glTexParameterf) (GLenum, GLenum, GLfloat);
extern pfn_glTexParameterf fp_glTexParameterf;
typedef void (APIENTRYP pfn_glTexParameterfv) (GLenum, GLenum, const GLfloat*);
extern pfn_glTexParameterfv fp_glTexParameterfv;
typedef void (APIENTRYP pfn_glTexParameteri) (GLenum, GLenum, GLint);
extern pfn_glTexParameteri fp_glTexParameteri;
typedef void (APIENTRYP pfn_glTexParameteriv) (GLenum, GLenum, const GLint*);
extern pfn_glTexParameteriv fp_glTexParameteriv;
typedef void (APIENTRYP pfn_glTexImage1D) (GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void*);
extern pfn_glTexImage1D fp_glTexImage1D;
typedef void (APIENTRYP pfn_glTexImage2D) (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
extern pfn_glTexImage2D fp_glTexImage2D;
typedef void (APIENTRYP pfn_glDrawBuffer) (GLenum);
extern pfn_glDrawBuffer fp_glDrawBuffer;
typedef void (APIENTRYP pfn_glClear) (GLbitfield);
extern pfn_glClear fp_glClear;
typedef void (APIENTRYP pfn_glClearColor) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glClearColor fp_glClearColor;
typedef void (APIENTRYP pfn_glClearStencil) (GLint);
extern pfn_glClearStencil fp_glClearStencil;
typedef void (APIENTRYP pfn_glClearDepth) (GLdouble);
extern pfn_glClearDepth fp_glClearDepth;
typedef void (APIENTRYP pfn_glStencilMask) (GLuint);
extern pfn_glStencilMask fp_glStencilMask;
typedef void (APIENTRYP pfn_glColorMask) (GLboolean, GLboolean, GLboolean, GLboolean);
extern pfn_glColorMask fp_glColorMask;
typedef void (APIENTRYP pfn_glDepthMask) (GLboolean);
extern pfn_glDepthMask fp_glDepthMask;
typedef void (APIENTRYP pfn_glDisable) (GLenum);
extern pfn_glDisable fp_glDisable;
typedef void (APIENTRYP pfn_glEnable) (GLenum);
extern pfn_glEnable fp_glEnable;
typedef void (APIENTRYP pfn_glFinish) ();
extern pfn_glFinish fp_glFinish;
typedef void (APIENTRYP pfn_glFlush) ();
extern pfn_glFlush fp_glFlush;
typedef void (APIENTRYP pfn_glBlendFunc) (GLenum, GLenum);
extern pfn_glBlendFunc fp_glBlendFunc;
typedef void (APIENTRYP pfn_glLogicOp) (GLenum);
extern pfn_glLogicOp fp_glLogicOp;
typedef void (APIENTRYP pfn_glStencilFunc) (GLenum, GLint, GLuint);
extern pfn_glStencilFunc fp_glStencilFunc;
typedef void (APIENTRYP pfn_glStencilOp) (GLenum, GLenum, GLenum);
extern pfn_glStencilOp fp_glStencilOp;
typedef void (APIENTRYP pfn_glDepthFunc) (GLenum);
extern pfn_glDepthFunc fp_glDepthFunc;
typedef void (APIENTRYP pfn_glPixelStoref) (GLenum, GLfloat);
extern pfn_glPixelStoref fp_glPixelStoref;
typedef void (APIENTRYP pfn_glPixelStorei) (GLenum, GLint);
extern pfn_glPixelStorei fp_glPixelStorei;
typedef void (APIENTRYP pfn_glReadBuffer) (GLenum);
extern pfn_glReadBuffer fp_glReadBuffer;
typedef void (APIENTRYP pfn_glReadPixels) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void*);
extern pfn_glReadPixels fp_glReadPixels;
typedef void (APIENTRYP pfn_glGetBooleanv) (GLenum, GLboolean*);
extern pfn_glGetBooleanv fp_glGetBooleanv;
typedef void (APIENTRYP pfn_glGetDoublev) (GLenum, GLdouble*);
extern pfn_glGetDoublev fp_glGetDoublev;
typedef GLenum (APIENTRYP pfn_glGetError) ();
extern pfn_glGetError fp_glGetError;
typedef void (APIENTRYP pfn_glGetFloatv) (GLenum, GLfloat*);
extern pfn_glGetFloatv fp_glGetFloatv;
typedef void (APIENTRYP pfn_glGetIntegerv) (GLenum, GLint*);
extern pfn_glGetIntegerv fp_glGetIntegerv;
typedef const GLubyte* (APIENTRYP pfn_glGetString) (GLenum);
extern pfn_glGetString fp_glGetString;
typedef void (APIENTRYP pfn_glGetTexImage) (GLenum, GLint, GLenum, GLenum, void*);
extern pfn_glGetTexImage fp_glGetTexImage;
typedef void (APIENTRYP pfn_glGetTexParameterfv) (GLenum, GLenum, GLfloat*);
extern pfn_glGetTexParameterfv fp_glGetTexParameterfv;
typedef void (APIENTRYP pfn_glGetTexParameteriv) (GLenum, GLenum, GLint*);
extern pfn_glGetTexParameteriv fp_glGetTexParameteriv;
typedef void (APIENTRYP pfn_glGetTexLevelParameterfv) (GLenum, GLint, GLenum, GLfloat*);
extern pfn_glGetTexLevelParameterfv fp_glGetTexLevelParameterfv;
typedef void (APIENTRYP pfn_glGetTexLevelParameteriv) (GLenum, GLint, GLenum, GLint*);
extern pfn_glGetTexLevelParameteriv fp_glGetTexLevelParameteriv;
typedef GLboolean (APIENTRYP pfn_glIsEnabled) (GLenum);
extern pfn_glIsEnabled fp_glIsEnabled;
typedef void (APIENTRYP pfn_glDepthRange) (GLdouble, GLdouble);
extern pfn_glDepthRange fp_glDepthRange;
typedef void (APIENTRYP pfn_glViewport) (GLint, GLint, GLsizei, GLsizei);
extern pfn_glViewport fp_glViewport;
typedef void (APIENTRYP pfn_glNewList) (GLuint, GLenum);
extern pfn_glNewList fp_glNewList;
typedef void (APIENTRYP pfn_glEndList) ();
extern pfn_glEndList fp_glEndList;
typedef void (APIENTRYP pfn_glCallList) (GLuint);
extern pfn_glCallList fp_glCallList;
typedef void (APIENTRYP pfn_glCallLists) (GLsizei, GLenum, const void*);
extern pfn_glCallLists fp_glCallLists;
typedef void (APIENTRYP pfn_glDeleteLists) (GLuint, GLsizei);
extern pfn_glDeleteLists fp_glDeleteLists;
typedef GLuint (APIENTRYP pfn_glGenLists) (GLsizei);
extern pfn_glGenLists fp_glGenLists;
typedef void (APIENTRYP pfn_glListBase) (GLuint);
extern pfn_glListBase fp_glListBase;
typedef void (APIENTRYP pfn_glBegin) (GLenum);
extern pfn_glBegin fp_glBegin;
typedef void (APIENTRYP pfn_glBitmap) (GLsizei, GLsizei, GLfloat, GLfloat, GLfloat, GLfloat, const GLubyte*);
extern pfn_glBitmap fp_glBitmap;
typedef void (APIENTRYP pfn_glColor3b) (GLbyte, GLbyte, GLbyte);
extern pfn_glColor3b fp_glColor3b;
typedef void (APIENTRYP pfn_glColor3bv) (const GLbyte*);
extern pfn_glColor3bv fp_glColor3bv;
typedef void (APIENTRYP pfn_glColor3d) (GLdouble, GLdouble, GLdouble);
extern pfn_glColor3d fp_glColor3d;
typedef void (APIENTRYP pfn_glColor3dv) (const GLdouble*);
extern pfn_glColor3dv fp_glColor3dv;
typedef void (APIENTRYP pfn_glColor3f) (GLfloat, GLfloat, GLfloat);
extern pfn_glColor3f fp_glColor3f;
typedef void (APIENTRYP pfn_glColor3fv) (const GLfloat*);
extern pfn_glColor3fv fp_glColor3fv;
typedef void (APIENTRYP pfn_glColor3i) (GLint, GLint, GLint);
extern pfn_glColor3i fp_glColor3i;
typedef void (APIENTRYP pfn_glColor3iv) (const GLint*);
extern pfn_glColor3iv fp_glColor3iv;
typedef void (APIENTRYP pfn_glColor3s) (GLshort, GLshort, GLshort);
extern pfn_glColor3s fp_glColor3s;
typedef void (APIENTRYP pfn_glColor3sv) (const GLshort*);
extern pfn_glColor3sv fp_glColor3sv;
typedef void (APIENTRYP pfn_glColor3ub) (GLubyte, GLubyte, GLubyte);
extern pfn_glColor3ub fp_glColor3ub;
typedef void (APIENTRYP pfn_glColor3ubv) (const GLubyte*);
extern pfn_glColor3ubv fp_glColor3ubv;
typedef void (APIENTRYP pfn_glColor3ui) (GLuint, GLuint, GLuint);
extern pfn_glColor3ui fp_glColor3ui;
typedef void (APIENTRYP pfn_glColor3uiv) (const GLuint*);
extern pfn_glColor3uiv fp_glColor3uiv;
typedef void (APIENTRYP pfn_glColor3us) (GLushort, GLushort, GLushort);
extern pfn_glColor3us fp_glColor3us;
typedef void (APIENTRYP pfn_glColor3usv) (const GLushort*);
extern pfn_glColor3usv fp_glColor3usv;
typedef void (APIENTRYP pfn_glColor4b) (GLbyte, GLbyte, GLbyte, GLbyte);
extern pfn_glColor4b fp_glColor4b;
typedef void (APIENTRYP pfn_glColor4bv) (const GLbyte*);
extern pfn_glColor4bv fp_glColor4bv;
typedef void (APIENTRYP pfn_glColor4d) (GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glColor4d fp_glColor4d;
typedef void (APIENTRYP pfn_glColor4dv) (const GLdouble*);
extern pfn_glColor4dv fp_glColor4dv;
typedef void (APIENTRYP pfn_glColor4f) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glColor4f fp_glColor4f;
typedef void (APIENTRYP pfn_glColor4fv) (const GLfloat*);
extern pfn_glColor4fv fp_glColor4fv;
typedef void (APIENTRYP pfn_glColor4i) (GLint, GLint, GLint, GLint);
extern pfn_glColor4i fp_glColor4i;
typedef void (APIENTRYP pfn_glColor4iv) (const GLint*);
extern pfn_glColor4iv fp_glColor4iv;
typedef void (APIENTRYP pfn_glColor4s) (GLshort, GLshort, GLshort, GLshort);
extern pfn_glColor4s fp_glColor4s;
typedef void (APIENTRYP pfn_glColor4sv) (const GLshort*);
extern pfn_glColor4sv fp_glColor4sv;
typedef void (APIENTRYP pfn_glColor4ub) (GLubyte, GLubyte, GLubyte, GLubyte);
extern pfn_glColor4ub fp_glColor4ub;
typedef void (APIENTRYP pfn_glColor4ubv) (const GLubyte*);
extern pfn_glColor4ubv fp_glColor4ubv;
typedef void (APIENTRYP pfn_glColor4ui) (GLuint, GLuint, GLuint, GLuint);
extern pfn_glColor4ui fp_glColor4ui;
typedef void (APIENTRYP pfn_glColor4uiv) (const GLuint*);
extern pfn_glColor4uiv fp_glColor4uiv;
typedef void (APIENTRYP pfn_glColor4us) (GLushort, GLushort, GLushort, GLushort);
extern pfn_glColor4us fp_glColor4us;
typedef void (APIENTRYP pfn_glColor4usv) (const GLushort*);
extern pfn_glColor4usv fp_glColor4usv;
typedef void (APIENTRYP pfn_glEdgeFlag) (GLboolean);
extern pfn_glEdgeFlag fp_glEdgeFlag;
typedef void (APIENTRYP pfn_glEdgeFlagv) (const GLboolean*);
extern pfn_glEdgeFlagv fp_glEdgeFlagv;
typedef void (APIENTRYP pfn_glEnd) ();
extern pfn_glEnd fp_glEnd;
typedef void (APIENTRYP pfn_glIndexd) (GLdouble);
extern pfn_glIndexd fp_glIndexd;
typedef void (APIENTRYP pfn_glIndexdv) (const GLdouble*);
extern pfn_glIndexdv fp_glIndexdv;
typedef void (APIENTRYP pfn_glIndexf) (GLfloat);
extern pfn_glIndexf fp_glIndexf;
typedef void (APIENTRYP pfn_glIndexfv) (const GLfloat*);
extern pfn_glIndexfv fp_glIndexfv;
typedef void (APIENTRYP pfn_glIndexi) (GLint);
extern pfn_glIndexi fp_glIndexi;
typedef void (APIENTRYP pfn_glIndexiv) (const GLint*);
extern pfn_glIndexiv fp_glIndexiv;
typedef void (APIENTRYP pfn_glIndexs) (GLshort);
extern pfn_glIndexs fp_glIndexs;
typedef void (APIENTRYP pfn_glIndexsv) (const GLshort*);
extern pfn_glIndexsv fp_glIndexsv;
typedef void (APIENTRYP pfn_glNormal3b) (GLbyte, GLbyte, GLbyte);
extern pfn_glNormal3b fp_glNormal3b;
typedef void (APIENTRYP pfn_glNormal3bv) (const GLbyte*);
extern pfn_glNormal3bv fp_glNormal3bv;
typedef void (APIENTRYP pfn_glNormal3d) (GLdouble, GLdouble, GLdouble);
extern pfn_glNormal3d fp_glNormal3d;
typedef void (APIENTRYP pfn_glNormal3dv) (const GLdouble*);
extern pfn_glNormal3dv fp_glNormal3dv;
typedef void (APIENTRYP pfn_glNormal3f) (GLfloat, GLfloat, GLfloat);
extern pfn_glNormal3f fp_glNormal3f;
typedef void (APIENTRYP pfn_glNormal3fv) (const GLfloat*);
extern pfn_glNormal3fv fp_glNormal3fv;
typedef void (APIENTRYP pfn_glNormal3i) (GLint, GLint, GLint);
extern pfn_glNormal3i fp_glNormal3i;
typedef void (APIENTRYP pfn_glNormal3iv) (const GLint*);
extern pfn_glNormal3iv fp_glNormal3iv;
typedef void (APIENTRYP pfn_glNormal3s) (GLshort, GLshort, GLshort);
extern pfn_glNormal3s fp_glNormal3s;
typedef void (APIENTRYP pfn_glNormal3sv) (const GLshort*);
extern pfn_glNormal3sv fp_glNormal3sv;
typedef void (APIENTRYP pfn_glRasterPos2d) (GLdouble, GLdouble);
extern pfn_glRasterPos2d fp_glRasterPos2d;
typedef void (APIENTRYP pfn_glRasterPos2dv) (const GLdouble*);
extern pfn_glRasterPos2dv fp_glRasterPos2dv;
typedef void (APIENTRYP pfn_glRasterPos2f) (GLfloat, GLfloat);
extern pfn_glRasterPos2f fp_glRasterPos2f;
typedef void (APIENTRYP pfn_glRasterPos2fv) (const GLfloat*);
extern pfn_glRasterPos2fv fp_glRasterPos2fv;
typedef void (APIENTRYP pfn_glRasterPos2i) (GLint, GLint);
extern pfn_glRasterPos2i fp_glRasterPos2i;
typedef void (APIENTRYP pfn_glRasterPos2iv) (const GLint*);
extern pfn_glRasterPos2iv fp_glRasterPos2iv;
typedef void (APIENTRYP pfn_glRasterPos2s) (GLshort, GLshort);
extern pfn_glRasterPos2s fp_glRasterPos2s;
typedef void (APIENTRYP pfn_glRasterPos2sv) (const GLshort*);
extern pfn_glRasterPos2sv fp_glRasterPos2sv;
typedef void (APIENTRYP pfn_glRasterPos3d) (GLdouble, GLdouble, GLdouble);
extern pfn_glRasterPos3d fp_glRasterPos3d;
typedef void (APIENTRYP pfn_glRasterPos3dv) (const GLdouble*);
extern pfn_glRasterPos3dv fp_glRasterPos3dv;
typedef void (APIENTRYP pfn_glRasterPos3f) (GLfloat, GLfloat, GLfloat);
extern pfn_glRasterPos3f fp_glRasterPos3f;
typedef void (APIENTRYP pfn_glRasterPos3fv) (const GLfloat*);
extern pfn_glRasterPos3fv fp_glRasterPos3fv;
typedef void (APIENTRYP pfn_glRasterPos3i) (GLint, GLint, GLint);
extern pfn_glRasterPos3i fp_glRasterPos3i;
typedef void (APIENTRYP pfn_glRasterPos3iv) (const GLint*);
extern pfn_glRasterPos3iv fp_glRasterPos3iv;
typedef void (APIENTRYP pfn_glRasterPos3s) (GLshort, GLshort, GLshort);
extern pfn_glRasterPos3s fp_glRasterPos3s;
typedef void (APIENTRYP pfn_glRasterPos3sv) (const GLshort*);
extern pfn_glRasterPos3sv fp_glRasterPos3sv;
typedef void (APIENTRYP pfn_glRasterPos4d) (GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glRasterPos4d fp_glRasterPos4d;
typedef void (APIENTRYP pfn_glRasterPos4dv) (const GLdouble*);
extern pfn_glRasterPos4dv fp_glRasterPos4dv;
typedef void (APIENTRYP pfn_glRasterPos4f) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glRasterPos4f fp_glRasterPos4f;
typedef void (APIENTRYP pfn_glRasterPos4fv) (const GLfloat*);
extern pfn_glRasterPos4fv fp_glRasterPos4fv;
typedef void (APIENTRYP pfn_glRasterPos4i) (GLint, GLint, GLint, GLint);
extern pfn_glRasterPos4i fp_glRasterPos4i;
typedef void (APIENTRYP pfn_glRasterPos4iv) (const GLint*);
extern pfn_glRasterPos4iv fp_glRasterPos4iv;
typedef void (APIENTRYP pfn_glRasterPos4s) (GLshort, GLshort, GLshort, GLshort);
extern pfn_glRasterPos4s fp_glRasterPos4s;
typedef void (APIENTRYP pfn_glRasterPos4sv) (const GLshort*);
extern pfn_glRasterPos4sv fp_glRasterPos4sv;
typedef void (APIENTRYP pfn_glRectd) (GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glRectd fp_glRectd;
typedef void (APIENTRYP pfn_glRectdv) (const GLdouble*, const GLdouble*);
extern pfn_glRectdv fp_glRectdv;
typedef void (APIENTRYP pfn_glRectf) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glRectf fp_glRectf;
typedef void (APIENTRYP pfn_glRectfv) (const GLfloat*, const GLfloat*);
extern pfn_glRectfv fp_glRectfv;
typedef void (APIENTRYP pfn_glRecti) (GLint, GLint, GLint, GLint);
extern pfn_glRecti fp_glRecti;
typedef void (APIENTRYP pfn_glRectiv) (const GLint*, const GLint*);
extern pfn_glRectiv fp_glRectiv;
typedef void (APIENTRYP pfn_glRects) (GLshort, GLshort, GLshort, GLshort);
extern pfn_glRects fp_glRects;
typedef void (APIENTRYP pfn_glRectsv) (const GLshort*, const GLshort*);
extern pfn_glRectsv fp_glRectsv;
typedef void (APIENTRYP pfn_glTexCoord1d) (GLdouble);
extern pfn_glTexCoord1d fp_glTexCoord1d;
typedef void (APIENTRYP pfn_glTexCoord1dv) (const GLdouble*);
extern pfn_glTexCoord1dv fp_glTexCoord1dv;
typedef void (APIENTRYP pfn_glTexCoord1f) (GLfloat);
extern pfn_glTexCoord1f fp_glTexCoord1f;
typedef void (APIENTRYP pfn_glTexCoord1fv) (const GLfloat*);
extern pfn_glTexCoord1fv fp_glTexCoord1fv;
typedef void (APIENTRYP pfn_glTexCoord1i) (GLint);
extern pfn_glTexCoord1i fp_glTexCoord1i;
typedef void (APIENTRYP pfn_glTexCoord1iv) (const GLint*);
extern pfn_glTexCoord1iv fp_glTexCoord1iv;
typedef void (APIENTRYP pfn_glTexCoord1s) (GLshort);
extern pfn_glTexCoord1s fp_glTexCoord1s;
typedef void (APIENTRYP pfn_glTexCoord1sv) (const GLshort*);
extern pfn_glTexCoord1sv fp_glTexCoord1sv;
typedef void (APIENTRYP pfn_glTexCoord2d) (GLdouble, GLdouble);
extern pfn_glTexCoord2d fp_glTexCoord2d;
typedef void (APIENTRYP pfn_glTexCoord2dv) (const GLdouble*);
extern pfn_glTexCoord2dv fp_glTexCoord2dv;
typedef void (APIENTRYP pfn_glTexCoord2f) (GLfloat, GLfloat);
extern pfn_glTexCoord2f fp_glTexCoord2f;
typedef void (APIENTRYP pfn_glTexCoord2fv) (const GLfloat*);
extern pfn_glTexCoord2fv fp_glTexCoord2fv;
typedef void (APIENTRYP pfn_glTexCoord2i) (GLint, GLint);
extern pfn_glTexCoord2i fp_glTexCoord2i;
typedef void (APIENTRYP pfn_glTexCoord2iv) (const GLint*);
extern pfn_glTexCoord2iv fp_glTexCoord2iv;
typedef void (APIENTRYP pfn_glTexCoord2s) (GLshort, GLshort);
extern pfn_glTexCoord2s fp_glTexCoord2s;
typedef void (APIENTRYP pfn_glTexCoord2sv) (const GLshort*);
extern pfn_glTexCoord2sv fp_glTexCoord2sv;
typedef void (APIENTRYP pfn_glTexCoord3d) (GLdouble, GLdouble, GLdouble);
extern pfn_glTexCoord3d fp_glTexCoord3d;
typedef void (APIENTRYP pfn_glTexCoord3dv) (const GLdouble*);
extern pfn_glTexCoord3dv fp_glTexCoord3dv;
typedef void (APIENTRYP pfn_glTexCoord3f) (GLfloat, GLfloat, GLfloat);
extern pfn_glTexCoord3f fp_glTexCoord3f;
typedef void (APIENTRYP pfn_glTexCoord3fv) (const GLfloat*);
extern pfn_glTexCoord3fv fp_glTexCoord3fv;
typedef void (APIENTRYP pfn_glTexCoord3i) (GLint, GLint, GLint);
extern pfn_glTexCoord3i fp_glTexCoord3i;
typedef void (APIENTRYP pfn_glTexCoord3iv) (const GLint*);
extern pfn_glTexCoord3iv fp_glTexCoord3iv;
typedef void (APIENTRYP pfn_glTexCoord3s) (GLshort, GLshort, GLshort);
extern pfn_glTexCoord3s fp_glTexCoord3s;
typedef void (APIENTRYP pfn_glTexCoord3sv) (const GLshort*);
extern pfn_glTexCoord3sv fp_glTexCoord3sv;
typedef void (APIENTRYP pfn_glTexCoord4d) (GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glTexCoord4d fp_glTexCoord4d;
typedef void (APIENTRYP pfn_glTexCoord4dv) (const GLdouble*);
extern pfn_glTexCoord4dv fp_glTexCoord4dv;
typedef void (APIENTRYP pfn_glTexCoord4f) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glTexCoord4f fp_glTexCoord4f;
typedef void (APIENTRYP pfn_glTexCoord4fv) (const GLfloat*);
extern pfn_glTexCoord4fv fp_glTexCoord4fv;
typedef void (APIENTRYP pfn_glTexCoord4i) (GLint, GLint, GLint, GLint);
extern pfn_glTexCoord4i fp_glTexCoord4i;
typedef void (APIENTRYP pfn_glTexCoord4iv) (const GLint*);
extern pfn_glTexCoord4iv fp_glTexCoord4iv;
typedef void (APIENTRYP pfn_glTexCoord4s) (GLshort, GLshort, GLshort, GLshort);
extern pfn_glTexCoord4s fp_glTexCoord4s;
typedef void (APIENTRYP pfn_glTexCoord4sv) (const GLshort*);
extern pfn_glTexCoord4sv fp_glTexCoord4sv;
typedef void (APIENTRYP pfn_glVertex2d) (GLdouble, GLdouble);
extern pfn_glVertex2d fp_glVertex2d;
typedef void (APIENTRYP pfn_glVertex2dv) (const GLdouble*);
extern pfn_glVertex2dv fp_glVertex2dv;
typedef void (APIENTRYP pfn_glVertex2f) (GLfloat, GLfloat);
extern pfn_glVertex2f fp_glVertex2f;
typedef void (APIENTRYP pfn_glVertex2fv) (const GLfloat*);
extern pfn_glVertex2fv fp_glVertex2fv;
typedef void (APIENTRYP pfn_glVertex2i) (GLint, GLint);
extern pfn_glVertex2i fp_glVertex2i;
typedef void (APIENTRYP pfn_glVertex2iv) (const GLint*);
extern pfn_glVertex2iv fp_glVertex2iv;
typedef void (APIENTRYP pfn_glVertex2s) (GLshort, GLshort);
extern pfn_glVertex2s fp_glVertex2s;
typedef void (APIENTRYP pfn_glVertex2sv) (const GLshort*);
extern pfn_glVertex2sv fp_glVertex2sv;
typedef void (APIENTRYP pfn_glVertex3d) (GLdouble, GLdouble, GLdouble);
extern pfn_glVertex3d fp_glVertex3d;
typedef void (APIENTRYP pfn_glVertex3dv) (const GLdouble*);
extern pfn_glVertex3dv fp_glVertex3dv;
typedef void (APIENTRYP pfn_glVertex3f) (GLfloat, GLfloat, GLfloat);
extern pfn_glVertex3f fp_glVertex3f;
typedef void (APIENTRYP pfn_glVertex3fv) (const GLfloat*);
extern pfn_glVertex3fv fp_glVertex3fv;
typedef void (APIENTRYP pfn_glVertex3i) (GLint, GLint, GLint);
extern pfn_glVertex3i fp_glVertex3i;
typedef void (APIENTRYP pfn_glVertex3iv) (const GLint*);
extern pfn_glVertex3iv fp_glVertex3iv;
typedef void (APIENTRYP pfn_glVertex3s) (GLshort, GLshort, GLshort);
extern pfn_glVertex3s fp_glVertex3s;
typedef void (APIENTRYP pfn_glVertex3sv) (const GLshort*);
extern pfn_glVertex3sv fp_glVertex3sv;
typedef void (APIENTRYP pfn_glVertex4d) (GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glVertex4d fp_glVertex4d;
typedef void (APIENTRYP pfn_glVertex4dv) (const GLdouble*);
extern pfn_glVertex4dv fp_glVertex4dv;
typedef void (APIENTRYP pfn_glVertex4f) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glVertex4f fp_glVertex4f;
typedef void (APIENTRYP pfn_glVertex4fv) (const GLfloat*);
extern pfn_glVertex4fv fp_glVertex4fv;
typedef void (APIENTRYP pfn_glVertex4i) (GLint, GLint, GLint, GLint);
extern pfn_glVertex4i fp_glVertex4i;
typedef void (APIENTRYP pfn_glVertex4iv) (const GLint*);
extern pfn_glVertex4iv fp_glVertex4iv;
typedef void (APIENTRYP pfn_glVertex4s) (GLshort, GLshort, GLshort, GLshort);
extern pfn_glVertex4s fp_glVertex4s;
typedef void (APIENTRYP pfn_glVertex4sv) (const GLshort*);
extern pfn_glVertex4sv fp_glVertex4sv;
typedef void (APIENTRYP pfn_glClipPlane) (GLenum, const GLdouble*);
extern pfn_glClipPlane fp_glClipPlane;
typedef void (APIENTRYP pfn_glColorMaterial) (GLenum, GLenum);
extern pfn_glColorMaterial fp_glColorMaterial;
typedef void (APIENTRYP pfn_glFogf) (GLenum, GLfloat);
extern pfn_glFogf fp_glFogf;
typedef void (APIENTRYP pfn_glFogfv) (GLenum, const GLfloat*);
extern pfn_glFogfv fp_glFogfv;
typedef void (APIENTRYP pfn_glFogi) (GLenum, GLint);
extern pfn_glFogi fp_glFogi;
typedef void (APIENTRYP pfn_glFogiv) (GLenum, const GLint*);
extern pfn_glFogiv fp_glFogiv;
typedef void (APIENTRYP pfn_glLightf) (GLenum, GLenum, GLfloat);
extern pfn_glLightf fp_glLightf;
typedef void (APIENTRYP pfn_glLightfv) (GLenum, GLenum, const GLfloat*);
extern pfn_glLightfv fp_glLightfv;
typedef void (APIENTRYP pfn_glLighti) (GLenum, GLenum, GLint);
extern pfn_glLighti fp_glLighti;
typedef void (APIENTRYP pfn_glLightiv) (GLenum, GLenum, const GLint*);
extern pfn_glLightiv fp_glLightiv;
typedef void (APIENTRYP pfn_glLightModelf) (GLenum, GLfloat);
extern pfn_glLightModelf fp_glLightModelf;
typedef void (APIENTRYP pfn_glLightModelfv) (GLenum, const GLfloat*);
extern pfn_glLightModelfv fp_glLightModelfv;
typedef void (APIENTRYP pfn_glLightModeli) (GLenum, GLint);
extern pfn_glLightModeli fp_glLightModeli;
typedef void (APIENTRYP pfn_glLightModeliv) (GLenum, const GLint*);
extern pfn_glLightModeliv fp_glLightModeliv;
typedef void (APIENTRYP pfn_glLineStipple) (GLint, GLushort);
extern pfn_glLineStipple fp_glLineStipple;
typedef void (APIENTRYP pfn_glMaterialf) (GLenum, GLenum, GLfloat);
extern pfn_glMaterialf fp_glMaterialf;
typedef void (APIENTRYP pfn_glMaterialfv) (GLenum, GLenum, const GLfloat*);
extern pfn_glMaterialfv fp_glMaterialfv;
typedef void (APIENTRYP pfn_glMateriali) (GLenum, GLenum, GLint);
extern pfn_glMateriali fp_glMateriali;
typedef void (APIENTRYP pfn_glMaterialiv) (GLenum, GLenum, const GLint*);
extern pfn_glMaterialiv fp_glMaterialiv;
typedef void (APIENTRYP pfn_glPolygonStipple) (const GLubyte*);
extern pfn_glPolygonStipple fp_glPolygonStipple;
typedef void (APIENTRYP pfn_glShadeModel) (GLenum);
extern pfn_glShadeModel fp_glShadeModel;
typedef void (APIENTRYP pfn_glTexEnvf) (GLenum, GLenum, GLfloat);
extern pfn_glTexEnvf fp_glTexEnvf;
typedef void (APIENTRYP pfn_glTexEnvfv) (GLenum, GLenum, const GLfloat*);
extern pfn_glTexEnvfv fp_glTexEnvfv;
typedef void (APIENTRYP pfn_glTexEnvi) (GLenum, GLenum, GLint);
extern pfn_glTexEnvi fp_glTexEnvi;
typedef void (APIENTRYP pfn_glTexEnviv) (GLenum, GLenum, const GLint*);
extern pfn_glTexEnviv fp_glTexEnviv;
typedef void (APIENTRYP pfn_glTexGend) (GLenum, GLenum, GLdouble);
extern pfn_glTexGend fp_glTexGend;
typedef void (APIENTRYP pfn_glTexGendv) (GLenum, GLenum, const GLdouble*);
extern pfn_glTexGendv fp_glTexGendv;
typedef void (APIENTRYP pfn_glTexGenf) (GLenum, GLenum, GLfloat);
extern pfn_glTexGenf fp_glTexGenf;
typedef void (APIENTRYP pfn_glTexGenfv) (GLenum, GLenum, const GLfloat*);
extern pfn_glTexGenfv fp_glTexGenfv;
typedef void (APIENTRYP pfn_glTexGeni) (GLenum, GLenum, GLint);
extern pfn_glTexGeni fp_glTexGeni;
typedef void (APIENTRYP pfn_glTexGeniv) (GLenum, GLenum, const GLint*);
extern pfn_glTexGeniv fp_glTexGeniv;
typedef void (APIENTRYP pfn_glFeedbackBuffer) (GLsizei, GLenum, GLfloat*);
extern pfn_glFeedbackBuffer fp_glFeedbackBuffer;
typedef void (APIENTRYP pfn_glSelectBuffer) (GLsizei, GLuint*);
extern pfn_glSelectBuffer fp_glSelectBuffer;
typedef GLint (APIENTRYP pfn_glRenderMode) (GLenum);
extern pfn_glRenderMode fp_glRenderMode;
typedef void (APIENTRYP pfn_glInitNames) ();
extern pfn_glInitNames fp_glInitNames;
typedef void (APIENTRYP pfn_glLoadName) (GLuint);
extern pfn_glLoadName fp_glLoadName;
typedef void (APIENTRYP pfn_glPassThrough) (GLfloat);
extern pfn_glPassThrough fp_glPassThrough;
typedef void (APIENTRYP pfn_glPopName) ();
extern pfn_glPopName fp_glPopName;
typedef void (APIENTRYP pfn_glPushName) (GLuint);
extern pfn_glPushName fp_glPushName;
typedef void (APIENTRYP pfn_glClearAccum) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glClearAccum fp_glClearAccum;
typedef void (APIENTRYP pfn_glClearIndex) (GLfloat);
extern pfn_glClearIndex fp_glClearIndex;
typedef void (APIENTRYP pfn_glIndexMask) (GLuint);
extern pfn_glIndexMask fp_glIndexMask;
typedef void (APIENTRYP pfn_glAccum) (GLenum, GLfloat);
extern pfn_glAccum fp_glAccum;
typedef void (APIENTRYP pfn_glPopAttrib) ();
extern pfn_glPopAttrib fp_glPopAttrib;
typedef void (APIENTRYP pfn_glPushAttrib) (GLbitfield);
extern pfn_glPushAttrib fp_glPushAttrib;
typedef void (APIENTRYP pfn_glMap1d) (GLenum, GLdouble, GLdouble, GLint, GLint, const GLdouble*);
extern pfn_glMap1d fp_glMap1d;
typedef void (APIENTRYP pfn_glMap1f) (GLenum, GLfloat, GLfloat, GLint, GLint, const GLfloat*);
extern pfn_glMap1f fp_glMap1f;
typedef void (APIENTRYP pfn_glMap2d) (GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint, const GLdouble*);
extern pfn_glMap2d fp_glMap2d;
typedef void (APIENTRYP pfn_glMap2f) (GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint, const GLfloat*);
extern pfn_glMap2f fp_glMap2f;
typedef void (APIENTRYP pfn_glMapGrid1d) (GLint, GLdouble, GLdouble);
extern pfn_glMapGrid1d fp_glMapGrid1d;
typedef void (APIENTRYP pfn_glMapGrid1f) (GLint, GLfloat, GLfloat);
extern pfn_glMapGrid1f fp_glMapGrid1f;
typedef void (APIENTRYP pfn_glMapGrid2d) (GLint, GLdouble, GLdouble, GLint, GLdouble, GLdouble);
extern pfn_glMapGrid2d fp_glMapGrid2d;
typedef void (APIENTRYP pfn_glMapGrid2f) (GLint, GLfloat, GLfloat, GLint, GLfloat, GLfloat);
extern pfn_glMapGrid2f fp_glMapGrid2f;
typedef void (APIENTRYP pfn_glEvalCoord1d) (GLdouble);
extern pfn_glEvalCoord1d fp_glEvalCoord1d;
typedef void (APIENTRYP pfn_glEvalCoord1dv) (const GLdouble*);
extern pfn_glEvalCoord1dv fp_glEvalCoord1dv;
typedef void (APIENTRYP pfn_glEvalCoord1f) (GLfloat);
extern pfn_glEvalCoord1f fp_glEvalCoord1f;
typedef void (APIENTRYP pfn_glEvalCoord1fv) (const GLfloat*);
extern pfn_glEvalCoord1fv fp_glEvalCoord1fv;
typedef void (APIENTRYP pfn_glEvalCoord2d) (GLdouble, GLdouble);
extern pfn_glEvalCoord2d fp_glEvalCoord2d;
typedef void (APIENTRYP pfn_glEvalCoord2dv) (const GLdouble*);
extern pfn_glEvalCoord2dv fp_glEvalCoord2dv;
typedef void (APIENTRYP pfn_glEvalCoord2f) (GLfloat, GLfloat);
extern pfn_glEvalCoord2f fp_glEvalCoord2f;
typedef void (APIENTRYP pfn_glEvalCoord2fv) (const GLfloat*);
extern pfn_glEvalCoord2fv fp_glEvalCoord2fv;
typedef void (APIENTRYP pfn_glEvalMesh1) (GLenum, GLint, GLint);
extern pfn_glEvalMesh1 fp_glEvalMesh1;
typedef void (APIENTRYP pfn_glEvalPoint1) (GLint);
extern pfn_glEvalPoint1 fp_glEvalPoint1;
typedef void (APIENTRYP pfn_glEvalMesh2) (GLenum, GLint, GLint, GLint, GLint);
extern pfn_glEvalMesh2 fp_glEvalMesh2;
typedef void (APIENTRYP pfn_glEvalPoint2) (GLint, GLint);
extern pfn_glEvalPoint2 fp_glEvalPoint2;
typedef void (APIENTRYP pfn_glAlphaFunc) (GLenum, GLfloat);
extern pfn_glAlphaFunc fp_glAlphaFunc;
typedef void (APIENTRYP pfn_glPixelZoom) (GLfloat, GLfloat);
extern pfn_glPixelZoom fp_glPixelZoom;
typedef void (APIENTRYP pfn_glPixelTransferf) (GLenum, GLfloat);
extern pfn_glPixelTransferf fp_glPixelTransferf;
typedef void (APIENTRYP pfn_glPixelTransferi) (GLenum, GLint);
extern pfn_glPixelTransferi fp_glPixelTransferi;
typedef void (APIENTRYP pfn_glPixelMapfv) (GLenum, GLsizei, const GLfloat*);
extern pfn_glPixelMapfv fp_glPixelMapfv;
typedef void (APIENTRYP pfn_glPixelMapuiv) (GLenum, GLsizei, const GLuint*);
extern pfn_glPixelMapuiv fp_glPixelMapuiv;
typedef void (APIENTRYP pfn_glPixelMapusv) (GLenum, GLsizei, const GLushort*);
extern pfn_glPixelMapusv fp_glPixelMapusv;
typedef void (APIENTRYP pfn_glCopyPixels) (GLint, GLint, GLsizei, GLsizei, GLenum);
extern pfn_glCopyPixels fp_glCopyPixels;
typedef void (APIENTRYP pfn_glDrawPixels) (GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glDrawPixels fp_glDrawPixels;
typedef void (APIENTRYP pfn_glGetClipPlane) (GLenum, GLdouble*);
extern pfn_glGetClipPlane fp_glGetClipPlane;
typedef void (APIENTRYP pfn_glGetLightfv) (GLenum, GLenum, GLfloat*);
extern pfn_glGetLightfv fp_glGetLightfv;
typedef void (APIENTRYP pfn_glGetLightiv) (GLenum, GLenum, GLint*);
extern pfn_glGetLightiv fp_glGetLightiv;
typedef void (APIENTRYP pfn_glGetMapdv) (GLenum, GLenum, GLdouble*);
extern pfn_glGetMapdv fp_glGetMapdv;
typedef void (APIENTRYP pfn_glGetMapfv) (GLenum, GLenum, GLfloat*);
extern pfn_glGetMapfv fp_glGetMapfv;
typedef void (APIENTRYP pfn_glGetMapiv) (GLenum, GLenum, GLint*);
extern pfn_glGetMapiv fp_glGetMapiv;
typedef void (APIENTRYP pfn_glGetMaterialfv) (GLenum, GLenum, GLfloat*);
extern pfn_glGetMaterialfv fp_glGetMaterialfv;
typedef void (APIENTRYP pfn_glGetMaterialiv) (GLenum, GLenum, GLint*);
extern pfn_glGetMaterialiv fp_glGetMaterialiv;
typedef void (APIENTRYP pfn_glGetPixelMapfv) (GLenum, GLfloat*);
extern pfn_glGetPixelMapfv fp_glGetPixelMapfv;
typedef void (APIENTRYP pfn_glGetPixelMapuiv) (GLenum, GLuint*);
extern pfn_glGetPixelMapuiv fp_glGetPixelMapuiv;
typedef void (APIENTRYP pfn_glGetPixelMapusv) (GLenum, GLushort*);
extern pfn_glGetPixelMapusv fp_glGetPixelMapusv;
typedef void (APIENTRYP pfn_glGetPolygonStipple) (GLubyte*);
extern pfn_glGetPolygonStipple fp_glGetPolygonStipple;
typedef void (APIENTRYP pfn_glGetTexEnvfv) (GLenum, GLenum, GLfloat*);
extern pfn_glGetTexEnvfv fp_glGetTexEnvfv;
typedef void (APIENTRYP pfn_glGetTexEnviv) (GLenum, GLenum, GLint*);
extern pfn_glGetTexEnviv fp_glGetTexEnviv;
typedef void (APIENTRYP pfn_glGetTexGendv) (GLenum, GLenum, GLdouble*);
extern pfn_glGetTexGendv fp_glGetTexGendv;
typedef void (APIENTRYP pfn_glGetTexGenfv) (GLenum, GLenum, GLfloat*);
extern pfn_glGetTexGenfv fp_glGetTexGenfv;
typedef void (APIENTRYP pfn_glGetTexGeniv) (GLenum, GLenum, GLint*);
extern pfn_glGetTexGeniv fp_glGetTexGeniv;
typedef GLboolean (APIENTRYP pfn_glIsList) (GLuint);
extern pfn_glIsList fp_glIsList;
typedef void (APIENTRYP pfn_glFrustum) (GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glFrustum fp_glFrustum;
typedef void (APIENTRYP pfn_glLoadIdentity) ();
extern pfn_glLoadIdentity fp_glLoadIdentity;
typedef void (APIENTRYP pfn_glLoadMatrixf) (const GLfloat*);
extern pfn_glLoadMatrixf fp_glLoadMatrixf;
typedef void (APIENTRYP pfn_glLoadMatrixd) (const GLdouble*);
extern pfn_glLoadMatrixd fp_glLoadMatrixd;
typedef void (APIENTRYP pfn_glMatrixMode) (GLenum);
extern pfn_glMatrixMode fp_glMatrixMode;
typedef void (APIENTRYP pfn_glMultMatrixf) (const GLfloat*);
extern pfn_glMultMatrixf fp_glMultMatrixf;
typedef void (APIENTRYP pfn_glMultMatrixd) (const GLdouble*);
extern pfn_glMultMatrixd fp_glMultMatrixd;
typedef void (APIENTRYP pfn_glOrtho) (GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glOrtho fp_glOrtho;
typedef void (APIENTRYP pfn_glPopMatrix) ();
extern pfn_glPopMatrix fp_glPopMatrix;
typedef void (APIENTRYP pfn_glPushMatrix) ();
extern pfn_glPushMatrix fp_glPushMatrix;
typedef void (APIENTRYP pfn_glRotated) (GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glRotated fp_glRotated;
typedef void (APIENTRYP pfn_glRotatef) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glRotatef fp_glRotatef;
typedef void (APIENTRYP pfn_glScaled) (GLdouble, GLdouble, GLdouble);
extern pfn_glScaled fp_glScaled;
typedef void (APIENTRYP pfn_glScalef) (GLfloat, GLfloat, GLfloat);
extern pfn_glScalef fp_glScalef;
typedef void (APIENTRYP pfn_glTranslated) (GLdouble, GLdouble, GLdouble);
extern pfn_glTranslated fp_glTranslated;
typedef void (APIENTRYP pfn_glTranslatef) (GLfloat, GLfloat, GLfloat);
extern pfn_glTranslatef fp_glTranslatef;

 /* GL_VERSION_1_1 */
extern GLboolean GLAD_VERSION_1_1;
#define GL_DEPTH_BUFFER_BIT                    0x00000100
#define GL_STENCIL_BUFFER_BIT                  0x00000400
#define GL_COLOR_BUFFER_BIT                    0x00004000
#define GL_FALSE                               0
#define GL_TRUE                                1
#define GL_POINTS                              0x0000
#define GL_LINES                               0x0001
#define GL_LINE_LOOP                           0x0002
#define GL_LINE_STRIP                          0x0003
#define GL_TRIANGLES                           0x0004
#define GL_TRIANGLE_STRIP                      0x0005
#define GL_TRIANGLE_FAN                        0x0006
#define GL_QUADS                               0x0007
#define GL_NEVER                               0x0200
#define GL_LESS                                0x0201
#define GL_EQUAL                               0x0202
#define GL_LEQUAL                              0x0203
#define GL_GREATER                             0x0204
#define GL_NOTEQUAL                            0x0205
#define GL_GEQUAL                              0x0206
#define GL_ALWAYS                              0x0207
#define GL_ZERO                                0
#define GL_ONE                                 1
#define GL_SRC_COLOR                           0x0300
#define GL_ONE_MINUS_SRC_COLOR                 0x0301
#define GL_SRC_ALPHA                           0x0302
#define GL_ONE_MINUS_SRC_ALPHA                 0x0303
#define GL_DST_ALPHA                           0x0304
#define GL_ONE_MINUS_DST_ALPHA                 0x0305
#define GL_DST_COLOR                           0x0306
#define GL_ONE_MINUS_DST_COLOR                 0x0307
#define GL_SRC_ALPHA_SATURATE                  0x0308
#define GL_NONE                                0
#define GL_FRONT_LEFT                          0x0400
#define GL_FRONT_RIGHT                         0x0401
#define GL_BACK_LEFT                           0x0402
#define GL_BACK_RIGHT                          0x0403
#define GL_FRONT                               0x0404
#define GL_BACK                                0x0405
#define GL_LEFT                                0x0406
#define GL_RIGHT                               0x0407
#define GL_FRONT_AND_BACK                      0x0408
#define GL_NO_ERROR                            0
#define GL_INVALID_ENUM                        0x0500
#define GL_INVALID_VALUE                       0x0501
#define GL_INVALID_OPERATION                   0x0502
#define GL_OUT_OF_MEMORY                       0x0505
#define GL_CW                                  0x0900
#define GL_CCW                                 0x0901
#define GL_POINT_SIZE                          0x0B11
#define GL_POINT_SIZE_RANGE                    0x0B12
#define GL_POINT_SIZE_GRANULARITY              0x0B13
#define GL_LINE_SMOOTH                         0x0B20
#define GL_LINE_WIDTH                          0x0B21
#define GL_LINE_WIDTH_RANGE                    0x0B22
#define GL_LINE_WIDTH_GRANULARITY              0x0B23
#define GL_POLYGON_MODE                        0x0B40
#define GL_POLYGON_SMOOTH                      0x0B41
#define GL_CULL_FACE                           0x0B44
#define GL_CULL_FACE_MODE                      0x0B45
#define GL_FRONT_FACE                          0x0B46
#define GL_DEPTH_RANGE                         0x0B70
#define GL_DEPTH_TEST                          0x0B71
#define GL_DEPTH_WRITEMASK                     0x0B72
#define GL_DEPTH_CLEAR_VALUE                   0x0B73
#define GL_DEPTH_FUNC                          0x0B74
#define GL_STENCIL_TEST                        0x0B90
#define GL_STENCIL_CLEAR_VALUE                 0x0B91
#define GL_STENCIL_FUNC                        0x0B92
#define GL_STENCIL_VALUE_MASK                  0x0B93
#define GL_STENCIL_FAIL                        0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL             0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS             0x0B96
#define GL_STENCIL_REF                         0x0B97
#define GL_STENCIL_WRITEMASK                   0x0B98
#define GL_VIEWPORT                            0x0BA2
#define GL_DITHER                              0x0BD0
#define GL_BLEND_DST                           0x0BE0
#define GL_BLEND_SRC                           0x0BE1
#define GL_BLEND                               0x0BE2
#define GL_LOGIC_OP_MODE                       0x0BF0
#define GL_COLOR_LOGIC_OP                      0x0BF2
#define GL_DRAW_BUFFER                         0x0C01
#define GL_READ_BUFFER                         0x0C02
#define GL_SCISSOR_BOX                         0x0C10
#define GL_SCISSOR_TEST                        0x0C11
#define GL_COLOR_CLEAR_VALUE                   0x0C22
#define GL_COLOR_WRITEMASK                     0x0C23
#define GL_DOUBLEBUFFER                        0x0C32
#define GL_STEREO                              0x0C33
#define GL_LINE_SMOOTH_HINT                    0x0C52
#define GL_POLYGON_SMOOTH_HINT                 0x0C53
#define GL_UNPACK_SWAP_BYTES                   0x0CF0
#define GL_UNPACK_LSB_FIRST                    0x0CF1
#define GL_UNPACK_ROW_LENGTH                   0x0CF2
#define GL_UNPACK_SKIP_ROWS                    0x0CF3
#define GL_UNPACK_SKIP_PIXELS                  0x0CF4
#define GL_UNPACK_ALIGNMENT                    0x0CF5
#define GL_PACK_SWAP_BYTES                     0x0D00
#define GL_PACK_LSB_FIRST                      0x0D01
#define GL_PACK_ROW_LENGTH                     0x0D02
#define GL_PACK_SKIP_ROWS                      0x0D03
#define GL_PACK_SKIP_PIXELS                    0x0D04
#define GL_PACK_ALIGNMENT                      0x0D05
#define GL_MAX_TEXTURE_SIZE                    0x0D33
#define GL_MAX_VIEWPORT_DIMS                   0x0D3A
#define GL_SUBPIXEL_BITS                       0x0D50
#define GL_TEXTURE_1D                          0x0DE0
#define GL_TEXTURE_2D                          0x0DE1
#define GL_POLYGON_OFFSET_UNITS                0x2A00
#define GL_POLYGON_OFFSET_POINT                0x2A01
#define GL_POLYGON_OFFSET_LINE                 0x2A02
#define GL_POLYGON_OFFSET_FILL                 0x8037
#define GL_POLYGON_OFFSET_FACTOR               0x8038
#define GL_TEXTURE_BINDING_1D                  0x8068
#define GL_TEXTURE_BINDING_2D                  0x8069
#define GL_TEXTURE_WIDTH                       0x1000
#define GL_TEXTURE_HEIGHT                      0x1001
#define GL_TEXTURE_INTERNAL_FORMAT             0x1003
#define GL_TEXTURE_BORDER_COLOR                0x1004
#define GL_TEXTURE_RED_SIZE                    0x805C
#define GL_TEXTURE_GREEN_SIZE                  0x805D
#define GL_TEXTURE_BLUE_SIZE                   0x805E
#define GL_TEXTURE_ALPHA_SIZE                  0x805F
#define GL_DONT_CARE                           0x1100
#define GL_FASTEST                             0x1101
#define GL_NICEST                              0x1102
#define GL_BYTE                                0x1400
#define GL_UNSIGNED_BYTE                       0x1401
#define GL_SHORT                               0x1402
#define GL_UNSIGNED_SHORT                      0x1403
#define GL_INT                                 0x1404
#define GL_UNSIGNED_INT                        0x1405
#define GL_FLOAT                               0x1406
#define GL_DOUBLE                              0x140A
#define GL_STACK_OVERFLOW                      0x0503
#define GL_STACK_UNDERFLOW                     0x0504
#define GL_CLEAR                               0x1500
#define GL_AND                                 0x1501
#define GL_AND_REVERSE                         0x1502
#define GL_COPY                                0x1503
#define GL_AND_INVERTED                        0x1504
#define GL_NOOP                                0x1505
#define GL_XOR                                 0x1506
#define GL_OR                                  0x1507
#define GL_NOR                                 0x1508
#define GL_EQUIV                               0x1509
#define GL_INVERT                              0x150A
#define GL_OR_REVERSE                          0x150B
#define GL_COPY_INVERTED                       0x150C
#define GL_OR_INVERTED                         0x150D
#define GL_NAND                                0x150E
#define GL_SET                                 0x150F
#define GL_TEXTURE                             0x1702
#define GL_COLOR                               0x1800
#define GL_DEPTH                               0x1801
#define GL_STENCIL                             0x1802
#define GL_STENCIL_INDEX                       0x1901
#define GL_DEPTH_COMPONENT                     0x1902
#define GL_RED                                 0x1903
#define GL_GREEN                               0x1904
#define GL_BLUE                                0x1905
#define GL_ALPHA                               0x1906
#define GL_RGB                                 0x1907
#define GL_RGBA                                0x1908
#define GL_POINT                               0x1B00
#define GL_LINE                                0x1B01
#define GL_FILL                                0x1B02
#define GL_KEEP                                0x1E00
#define GL_REPLACE                             0x1E01
#define GL_INCR                                0x1E02
#define GL_DECR                                0x1E03
#define GL_VENDOR                              0x1F00
#define GL_RENDERER                            0x1F01
#define GL_VERSION                             0x1F02
#define GL_EXTENSIONS                          0x1F03
#define GL_NEAREST                             0x2600
#define GL_LINEAR                              0x2601
#define GL_NEAREST_MIPMAP_NEAREST              0x2700
#define GL_LINEAR_MIPMAP_NEAREST               0x2701
#define GL_NEAREST_MIPMAP_LINEAR               0x2702
#define GL_LINEAR_MIPMAP_LINEAR                0x2703
#define GL_TEXTURE_MAG_FILTER                  0x2800
#define GL_TEXTURE_MIN_FILTER                  0x2801
#define GL_TEXTURE_WRAP_S                      0x2802
#define GL_TEXTURE_WRAP_T                      0x2803
#define GL_PROXY_TEXTURE_1D                    0x8063
#define GL_PROXY_TEXTURE_2D                    0x8064
#define GL_REPEAT                              0x2901
#define GL_R3_G3_B2                            0x2A10
#define GL_RGB4                                0x804F
#define GL_RGB5                                0x8050
#define GL_RGB8                                0x8051
#define GL_RGB10                               0x8052
#define GL_RGB12                               0x8053
#define GL_RGB16                               0x8054
#define GL_RGBA2                               0x8055
#define GL_RGBA4                               0x8056
#define GL_RGB5_A1                             0x8057
#define GL_RGBA8                               0x8058
#define GL_RGB10_A2                            0x8059
#define GL_RGBA12                              0x805A
#define GL_RGBA16                              0x805B
#define GL_CURRENT_BIT                         0x00000001
#define GL_POINT_BIT                           0x00000002
#define GL_LINE_BIT                            0x00000004
#define GL_POLYGON_BIT                         0x00000008
#define GL_POLYGON_STIPPLE_BIT                 0x00000010
#define GL_PIXEL_MODE_BIT                      0x00000020
#define GL_LIGHTING_BIT                        0x00000040
#define GL_FOG_BIT                             0x00000080
#define GL_ACCUM_BUFFER_BIT                    0x00000200
#define GL_VIEWPORT_BIT                        0x00000800
#define GL_TRANSFORM_BIT                       0x00001000
#define GL_ENABLE_BIT                          0x00002000
#define GL_HINT_BIT                            0x00008000
#define GL_EVAL_BIT                            0x00010000
#define GL_LIST_BIT                            0x00020000
#define GL_TEXTURE_BIT                         0x00040000
#define GL_SCISSOR_BIT                         0x00080000
#define GL_ALL_ATTRIB_BITS                     0xFFFFFFFF
#define GL_CLIENT_PIXEL_STORE_BIT              0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT             0x00000002
#define GL_CLIENT_ALL_ATTRIB_BITS              0xFFFFFFFF
#define GL_QUAD_STRIP                          0x0008
#define GL_POLYGON                             0x0009
#define GL_ACCUM                               0x0100
#define GL_LOAD                                0x0101
#define GL_RETURN                              0x0102
#define GL_MULT                                0x0103
#define GL_ADD                                 0x0104
#define GL_AUX0                                0x0409
#define GL_AUX1                                0x040A
#define GL_AUX2                                0x040B
#define GL_AUX3                                0x040C
#define GL_2D                                  0x0600
#define GL_3D                                  0x0601
#define GL_3D_COLOR                            0x0602
#define GL_3D_COLOR_TEXTURE                    0x0603
#define GL_4D_COLOR_TEXTURE                    0x0604
#define GL_PASS_THROUGH_TOKEN                  0x0700
#define GL_POINT_TOKEN                         0x0701
#define GL_LINE_TOKEN                          0x0702
#define GL_POLYGON_TOKEN                       0x0703
#define GL_BITMAP_TOKEN                        0x0704
#define GL_DRAW_PIXEL_TOKEN                    0x0705
#define GL_COPY_PIXEL_TOKEN                    0x0706
#define GL_LINE_RESET_TOKEN                    0x0707
#define GL_EXP                                 0x0800
#define GL_EXP2                                0x0801
#define GL_COEFF                               0x0A00
#define GL_ORDER                               0x0A01
#define GL_DOMAIN                              0x0A02
#define GL_PIXEL_MAP_I_TO_I                    0x0C70
#define GL_PIXEL_MAP_S_TO_S                    0x0C71
#define GL_PIXEL_MAP_I_TO_R                    0x0C72
#define GL_PIXEL_MAP_I_TO_G                    0x0C73
#define GL_PIXEL_MAP_I_TO_B                    0x0C74
#define GL_PIXEL_MAP_I_TO_A                    0x0C75
#define GL_PIXEL_MAP_R_TO_R                    0x0C76
#define GL_PIXEL_MAP_G_TO_G                    0x0C77
#define GL_PIXEL_MAP_B_TO_B                    0x0C78
#define GL_PIXEL_MAP_A_TO_A                    0x0C79
#define GL_VERTEX_ARRAY_POINTER                0x808E
#define GL_NORMAL_ARRAY_POINTER                0x808F
#define GL_COLOR_ARRAY_POINTER                 0x8090
#define GL_INDEX_ARRAY_POINTER                 0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER         0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER             0x8093
#define GL_FEEDBACK_BUFFER_POINTER             0x0DF0
#define GL_SELECTION_BUFFER_POINTER            0x0DF3
#define GL_CURRENT_COLOR                       0x0B00
#define GL_CURRENT_INDEX                       0x0B01
#define GL_CURRENT_NORMAL                      0x0B02
#define GL_CURRENT_TEXTURE_COORDS              0x0B03
#define GL_CURRENT_RASTER_COLOR                0x0B04
#define GL_CURRENT_RASTER_INDEX                0x0B05
#define GL_CURRENT_RASTER_TEXTURE_COORDS       0x0B06
#define GL_CURRENT_RASTER_POSITION             0x0B07
#define GL_CURRENT_RASTER_POSITION_VALID       0x0B08
#define GL_CURRENT_RASTER_DISTANCE             0x0B09
#define GL_POINT_SMOOTH                        0x0B10
#define GL_LINE_STIPPLE                        0x0B24
#define GL_LINE_STIPPLE_PATTERN                0x0B25
#define GL_LINE_STIPPLE_REPEAT                 0x0B26
#define GL_LIST_MODE                           0x0B30
#define GL_MAX_LIST_NESTING                    0x0B31
#define GL_LIST_BASE                           0x0B32
#define GL_LIST_INDEX                          0x0B33
#define GL_POLYGON_STIPPLE                     0x0B42
#define GL_EDGE_FLAG                           0x0B43
#define GL_LIGHTING                            0x0B50
#define GL_LIGHT_MODEL_LOCAL_VIEWER            0x0B51
#define GL_LIGHT_MODEL_TWO_SIDE                0x0B52
#define GL_LIGHT_MODEL_AMBIENT                 0x0B53
#define GL_SHADE_MODEL                         0x0B54
#define GL_COLOR_MATERIAL_FACE                 0x0B55
#define GL_COLOR_MATERIAL_PARAMETER            0x0B56
#define GL_COLOR_MATERIAL                      0x0B57
#define GL_FOG                                 0x0B60
#define GL_FOG_INDEX                           0x0B61
#define GL_FOG_DENSITY                         0x0B62
#define GL_FOG_START                           0x0B63
#define GL_FOG_END                             0x0B64
#define GL_FOG_MODE                            0x0B65
#define GL_FOG_COLOR                           0x0B66
#define GL_ACCUM_CLEAR_VALUE                   0x0B80
#define GL_MATRIX_MODE                         0x0BA0
#define GL_NORMALIZE                           0x0BA1
#define GL_MODELVIEW_STACK_DEPTH               0x0BA3
#define GL_PROJECTION_STACK_DEPTH              0x0BA4
#define GL_TEXTURE_STACK_DEPTH                 0x0BA5
#define GL_MODELVIEW_MATRIX                    0x0BA6
#define GL_PROJECTION_MATRIX                   0x0BA7
#define GL_TEXTURE_MATRIX                      0x0BA8
#define GL_ATTRIB_STACK_DEPTH                  0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH           0x0BB1
#define GL_ALPHA_TEST                          0x0BC0
#define GL_ALPHA_TEST_FUNC                     0x0BC1
#define GL_ALPHA_TEST_REF                      0x0BC2
#define GL_INDEX_LOGIC_OP                      0x0BF1
#define GL_LOGIC_OP                            0x0BF1
#define GL_AUX_BUFFERS                         0x0C00
#define GL_INDEX_CLEAR_VALUE                   0x0C20
#define GL_INDEX_WRITEMASK                     0x0C21
#define GL_INDEX_MODE                          0x0C30
#define GL_RGBA_MODE                           0x0C31
#define GL_RENDER_MODE                         0x0C40
#define GL_PERSPECTIVE_CORRECTION_HINT         0x0C50
#define GL_POINT_SMOOTH_HINT                   0x0C51
#define GL_FOG_HINT                            0x0C54
#define GL_TEXTURE_GEN_S                       0x0C60
#define GL_TEXTURE_GEN_T                       0x0C61
#define GL_TEXTURE_GEN_R                       0x0C62
#define GL_TEXTURE_GEN_Q                       0x0C63
#define GL_PIXEL_MAP_I_TO_I_SIZE               0x0CB0
#define GL_PIXEL_MAP_S_TO_S_SIZE               0x0CB1
#define GL_PIXEL_MAP_I_TO_R_SIZE               0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE               0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE               0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE               0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE               0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE               0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE               0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE               0x0CB9
#define GL_MAP_COLOR                           0x0D10
#define GL_MAP_STENCIL                         0x0D11
#define GL_INDEX_SHIFT                         0x0D12
#define GL_INDEX_OFFSET                        0x0D13
#define GL_RED_SCALE                           0x0D14
#define GL_RED_BIAS                            0x0D15
#define GL_ZOOM_X                              0x0D16
#define GL_ZOOM_Y                              0x0D17
#define GL_GREEN_SCALE                         0x0D18
#define GL_GREEN_BIAS                          0x0D19
#define GL_BLUE_SCALE                          0x0D1A
#define GL_BLUE_BIAS                           0x0D1B
#define GL_ALPHA_SCALE                         0x0D1C
#define GL_ALPHA_BIAS                          0x0D1D
#define GL_DEPTH_SCALE                         0x0D1E
#define GL_DEPTH_BIAS                          0x0D1F
#define GL_MAX_EVAL_ORDER                      0x0D30
#define GL_MAX_LIGHTS                          0x0D31
#define GL_MAX_CLIP_PLANES                     0x0D32
#define GL_MAX_PIXEL_MAP_TABLE                 0x0D34
#define GL_MAX_ATTRIB_STACK_DEPTH              0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH           0x0D36
#define GL_MAX_NAME_STACK_DEPTH                0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH          0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH             0x0D39
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH       0x0D3B
#define GL_INDEX_BITS                          0x0D51
#define GL_RED_BITS                            0x0D52
#define GL_GREEN_BITS                          0x0D53
#define GL_BLUE_BITS                           0x0D54
#define GL_ALPHA_BITS                          0x0D55
#define GL_DEPTH_BITS                          0x0D56
#define GL_STENCIL_BITS                        0x0D57
#define GL_ACCUM_RED_BITS                      0x0D58
#define GL_ACCUM_GREEN_BITS                    0x0D59
#define GL_ACCUM_BLUE_BITS                     0x0D5A
#define GL_ACCUM_ALPHA_BITS                    0x0D5B
#define GL_NAME_STACK_DEPTH                    0x0D70
#define GL_AUTO_NORMAL                         0x0D80
#define GL_MAP1_COLOR_4                        0x0D90
#define GL_MAP1_INDEX                          0x0D91
#define GL_MAP1_NORMAL                         0x0D92
#define GL_MAP1_TEXTURE_COORD_1                0x0D93
#define GL_MAP1_TEXTURE_COORD_2                0x0D94
#define GL_MAP1_TEXTURE_COORD_3                0x0D95
#define GL_MAP1_TEXTURE_COORD_4                0x0D96
#define GL_MAP1_VERTEX_3                       0x0D97
#define GL_MAP1_VERTEX_4                       0x0D98
#define GL_MAP2_COLOR_4                        0x0DB0
#define GL_MAP2_INDEX                          0x0DB1
#define GL_MAP2_NORMAL                         0x0DB2
#define GL_MAP2_TEXTURE_COORD_1                0x0DB3
#define GL_MAP2_TEXTURE_COORD_2                0x0DB4
#define GL_MAP2_TEXTURE_COORD_3                0x0DB5
#define GL_MAP2_TEXTURE_COORD_4                0x0DB6
#define GL_MAP2_VERTEX_3                       0x0DB7
#define GL_MAP2_VERTEX_4                       0x0DB8
#define GL_MAP1_GRID_DOMAIN                    0x0DD0
#define GL_MAP1_GRID_SEGMENTS                  0x0DD1
#define GL_MAP2_GRID_DOMAIN                    0x0DD2
#define GL_MAP2_GRID_SEGMENTS                  0x0DD3
#define GL_FEEDBACK_BUFFER_SIZE                0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE                0x0DF2
#define GL_SELECTION_BUFFER_SIZE               0x0DF4
#define GL_VERTEX_ARRAY                        0x8074
#define GL_NORMAL_ARRAY                        0x8075
#define GL_COLOR_ARRAY                         0x8076
#define GL_INDEX_ARRAY                         0x8077
#define GL_TEXTURE_COORD_ARRAY                 0x8078
#define GL_EDGE_FLAG_ARRAY                     0x8079
#define GL_VERTEX_ARRAY_SIZE                   0x807A
#define GL_VERTEX_ARRAY_TYPE                   0x807B
#define GL_VERTEX_ARRAY_STRIDE                 0x807C
#define GL_NORMAL_ARRAY_TYPE                   0x807E
#define GL_NORMAL_ARRAY_STRIDE                 0x807F
#define GL_COLOR_ARRAY_SIZE                    0x8081
#define GL_COLOR_ARRAY_TYPE                    0x8082
#define GL_COLOR_ARRAY_STRIDE                  0x8083
#define GL_INDEX_ARRAY_TYPE                    0x8085
#define GL_INDEX_ARRAY_STRIDE                  0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE            0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE            0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE          0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE              0x808C
#define GL_TEXTURE_COMPONENTS                  0x1003
#define GL_TEXTURE_BORDER                      0x1005
#define GL_TEXTURE_LUMINANCE_SIZE              0x8060
#define GL_TEXTURE_INTENSITY_SIZE              0x8061
#define GL_TEXTURE_PRIORITY                    0x8066
#define GL_TEXTURE_RESIDENT                    0x8067
#define GL_AMBIENT                             0x1200
#define GL_DIFFUSE                             0x1201
#define GL_SPECULAR                            0x1202
#define GL_POSITION                            0x1203
#define GL_SPOT_DIRECTION                      0x1204
#define GL_SPOT_EXPONENT                       0x1205
#define GL_SPOT_CUTOFF                         0x1206
#define GL_CONSTANT_ATTENUATION                0x1207
#define GL_LINEAR_ATTENUATION                  0x1208
#define GL_QUADRATIC_ATTENUATION               0x1209
#define GL_COMPILE                             0x1300
#define GL_COMPILE_AND_EXECUTE                 0x1301
#define GL_2_BYTES                             0x1407
#define GL_3_BYTES                             0x1408
#define GL_4_BYTES                             0x1409
#define GL_EMISSION                            0x1600
#define GL_SHININESS                           0x1601
#define GL_AMBIENT_AND_DIFFUSE                 0x1602
#define GL_COLOR_INDEXES                       0x1603
#define GL_MODELVIEW                           0x1700
#define GL_PROJECTION                          0x1701
#define GL_COLOR_INDEX                         0x1900
#define GL_LUMINANCE                           0x1909
#define GL_LUMINANCE_ALPHA                     0x190A
#define GL_BITMAP                              0x1A00
#define GL_RENDER                              0x1C00
#define GL_FEEDBACK                            0x1C01
#define GL_SELECT                              0x1C02
#define GL_FLAT                                0x1D00
#define GL_SMOOTH                              0x1D01
#define GL_S                                   0x2000
#define GL_T                                   0x2001
#define GL_R                                   0x2002
#define GL_Q                                   0x2003
#define GL_MODULATE                            0x2100
#define GL_DECAL                               0x2101
#define GL_TEXTURE_ENV_MODE                    0x2200
#define GL_TEXTURE_ENV_COLOR                   0x2201
#define GL_TEXTURE_ENV                         0x2300
#define GL_EYE_LINEAR                          0x2400
#define GL_OBJECT_LINEAR                       0x2401
#define GL_SPHERE_MAP                          0x2402
#define GL_TEXTURE_GEN_MODE                    0x2500
#define GL_OBJECT_PLANE                        0x2501
#define GL_EYE_PLANE                           0x2502
#define GL_CLAMP                               0x2900
#define GL_ALPHA4                              0x803B
#define GL_ALPHA8                              0x803C
#define GL_ALPHA12                             0x803D
#define GL_ALPHA16                             0x803E
#define GL_LUMINANCE4                          0x803F
#define GL_LUMINANCE8                          0x8040
#define GL_LUMINANCE12                         0x8041
#define GL_LUMINANCE16                         0x8042
#define GL_LUMINANCE4_ALPHA4                   0x8043
#define GL_LUMINANCE6_ALPHA2                   0x8044
#define GL_LUMINANCE8_ALPHA8                   0x8045
#define GL_LUMINANCE12_ALPHA4                  0x8046
#define GL_LUMINANCE12_ALPHA12                 0x8047
#define GL_LUMINANCE16_ALPHA16                 0x8048
#define GL_INTENSITY                           0x8049
#define GL_INTENSITY4                          0x804A
#define GL_INTENSITY8                          0x804B
#define GL_INTENSITY12                         0x804C
#define GL_INTENSITY16                         0x804D
#define GL_V2F                                 0x2A20
#define GL_V3F                                 0x2A21
#define GL_C4UB_V2F                            0x2A22
#define GL_C4UB_V3F                            0x2A23
#define GL_C3F_V3F                             0x2A24
#define GL_N3F_V3F                             0x2A25
#define GL_C4F_N3F_V3F                         0x2A26
#define GL_T2F_V3F                             0x2A27
#define GL_T4F_V4F                             0x2A28
#define GL_T2F_C4UB_V3F                        0x2A29
#define GL_T2F_C3F_V3F                         0x2A2A
#define GL_T2F_N3F_V3F                         0x2A2B
#define GL_T2F_C4F_N3F_V3F                     0x2A2C
#define GL_T4F_C4F_N3F_V4F                     0x2A2D
#define GL_CLIP_PLANE0                         0x3000
#define GL_CLIP_PLANE1                         0x3001
#define GL_CLIP_PLANE2                         0x3002
#define GL_CLIP_PLANE3                         0x3003
#define GL_CLIP_PLANE4                         0x3004
#define GL_CLIP_PLANE5                         0x3005
#define GL_LIGHT0                              0x4000
#define GL_LIGHT1                              0x4001
#define GL_LIGHT2                              0x4002
#define GL_LIGHT3                              0x4003
#define GL_LIGHT4                              0x4004
#define GL_LIGHT5                              0x4005
#define GL_LIGHT6                              0x4006
#define GL_LIGHT7                              0x4007
typedef void (APIENTRYP pfn_glDrawArrays) (GLenum, GLint, GLsizei);
extern pfn_glDrawArrays fp_glDrawArrays;
typedef void (APIENTRYP pfn_glDrawElements) (GLenum, GLsizei, GLenum, const void*);
extern pfn_glDrawElements fp_glDrawElements;
typedef void (APIENTRYP pfn_glGetPointerv) (GLenum, void**);
extern pfn_glGetPointerv fp_glGetPointerv;
typedef void (APIENTRYP pfn_glPolygonOffset) (GLfloat, GLfloat);
extern pfn_glPolygonOffset fp_glPolygonOffset;
typedef void (APIENTRYP pfn_glCopyTexImage1D) (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
extern pfn_glCopyTexImage1D fp_glCopyTexImage1D;
typedef void (APIENTRYP pfn_glCopyTexImage2D) (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
extern pfn_glCopyTexImage2D fp_glCopyTexImage2D;
typedef void (APIENTRYP pfn_glCopyTexSubImage1D) (GLenum, GLint, GLint, GLint, GLint, GLsizei);
extern pfn_glCopyTexSubImage1D fp_glCopyTexSubImage1D;
typedef void (APIENTRYP pfn_glCopyTexSubImage2D) (GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
extern pfn_glCopyTexSubImage2D fp_glCopyTexSubImage2D;
typedef void (APIENTRYP pfn_glTexSubImage1D) (GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void*);
extern pfn_glTexSubImage1D fp_glTexSubImage1D;
typedef void (APIENTRYP pfn_glTexSubImage2D) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glTexSubImage2D fp_glTexSubImage2D;
typedef void (APIENTRYP pfn_glBindTexture) (GLenum, GLuint);
extern pfn_glBindTexture fp_glBindTexture;
typedef void (APIENTRYP pfn_glDeleteTextures) (GLsizei, const GLuint*);
extern pfn_glDeleteTextures fp_glDeleteTextures;
typedef void (APIENTRYP pfn_glGenTextures) (GLsizei, GLuint*);
extern pfn_glGenTextures fp_glGenTextures;
typedef GLboolean (APIENTRYP pfn_glIsTexture) (GLuint);
extern pfn_glIsTexture fp_glIsTexture;
typedef void (APIENTRYP pfn_glArrayElement) (GLint);
extern pfn_glArrayElement fp_glArrayElement;
typedef void (APIENTRYP pfn_glColorPointer) (GLint, GLenum, GLsizei, const void*);
extern pfn_glColorPointer fp_glColorPointer;
typedef void (APIENTRYP pfn_glDisableClientState) (GLenum);
extern pfn_glDisableClientState fp_glDisableClientState;
typedef void (APIENTRYP pfn_glEdgeFlagPointer) (GLsizei, const void*);
extern pfn_glEdgeFlagPointer fp_glEdgeFlagPointer;
typedef void (APIENTRYP pfn_glEnableClientState) (GLenum);
extern pfn_glEnableClientState fp_glEnableClientState;
typedef void (APIENTRYP pfn_glIndexPointer) (GLenum, GLsizei, const void*);
extern pfn_glIndexPointer fp_glIndexPointer;
typedef void (APIENTRYP pfn_glInterleavedArrays) (GLenum, GLsizei, const void*);
extern pfn_glInterleavedArrays fp_glInterleavedArrays;
typedef void (APIENTRYP pfn_glNormalPointer) (GLenum, GLsizei, const void*);
extern pfn_glNormalPointer fp_glNormalPointer;
typedef void (APIENTRYP pfn_glTexCoordPointer) (GLint, GLenum, GLsizei, const void*);
extern pfn_glTexCoordPointer fp_glTexCoordPointer;
typedef void (APIENTRYP pfn_glVertexPointer) (GLint, GLenum, GLsizei, const void*);
extern pfn_glVertexPointer fp_glVertexPointer;
typedef GLboolean (APIENTRYP pfn_glAreTexturesResident) (GLsizei, const GLuint*, GLboolean*);
extern pfn_glAreTexturesResident fp_glAreTexturesResident;
typedef void (APIENTRYP pfn_glPrioritizeTextures) (GLsizei, const GLuint*, const GLfloat*);
extern pfn_glPrioritizeTextures fp_glPrioritizeTextures;
typedef void (APIENTRYP pfn_glIndexub) (GLubyte);
extern pfn_glIndexub fp_glIndexub;
typedef void (APIENTRYP pfn_glIndexubv) (const GLubyte*);
extern pfn_glIndexubv fp_glIndexubv;
typedef void (APIENTRYP pfn_glPopClientAttrib) ();
extern pfn_glPopClientAttrib fp_glPopClientAttrib;
typedef void (APIENTRYP pfn_glPushClientAttrib) (GLbitfield);
extern pfn_glPushClientAttrib fp_glPushClientAttrib;

 /* GL_VERSION_1_2 */
extern GLboolean GLAD_VERSION_1_2;
#define GL_UNSIGNED_BYTE_3_3_2                 0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4              0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1              0x8034
#define GL_UNSIGNED_INT_8_8_8_8                0x8035
#define GL_UNSIGNED_INT_10_10_10_2             0x8036
#define GL_TEXTURE_BINDING_3D                  0x806A
#define GL_PACK_SKIP_IMAGES                    0x806B
#define GL_PACK_IMAGE_HEIGHT                   0x806C
#define GL_UNPACK_SKIP_IMAGES                  0x806D
#define GL_UNPACK_IMAGE_HEIGHT                 0x806E
#define GL_TEXTURE_3D                          0x806F
#define GL_PROXY_TEXTURE_3D                    0x8070
#define GL_TEXTURE_DEPTH                       0x8071
#define GL_TEXTURE_WRAP_R                      0x8072
#define GL_MAX_3D_TEXTURE_SIZE                 0x8073
#define GL_UNSIGNED_BYTE_2_3_3_REV             0x8362
#define GL_UNSIGNED_SHORT_5_6_5                0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV            0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV          0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV          0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV            0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV         0x8368
#define GL_BGR                                 0x80E0
#define GL_BGRA                                0x80E1
#define GL_MAX_ELEMENTS_VERTICES               0x80E8
#define GL_MAX_ELEMENTS_INDICES                0x80E9
#define GL_CLAMP_TO_EDGE                       0x812F
#define GL_TEXTURE_MIN_LOD                     0x813A
#define GL_TEXTURE_MAX_LOD                     0x813B
#define GL_TEXTURE_BASE_LEVEL                  0x813C
#define GL_TEXTURE_MAX_LEVEL                   0x813D
#define GL_SMOOTH_POINT_SIZE_RANGE             0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY       0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE             0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY       0x0B23
#define GL_ALIASED_LINE_WIDTH_RANGE            0x846E
#define GL_RESCALE_NORMAL                      0x803A
#define GL_LIGHT_MODEL_COLOR_CONTROL           0x81F8
#define GL_SINGLE_COLOR                        0x81F9
#define GL_SEPARATE_SPECULAR_COLOR             0x81FA
#define GL_ALIASED_POINT_SIZE_RANGE            0x846D
typedef void (APIENTRYP pfn_glDrawRangeElements) (GLenum, GLuint, GLuint, GLsizei, GLenum, const void*);
extern pfn_glDrawRangeElements fp_glDrawRangeElements;
typedef void (APIENTRYP pfn_glTexImage3D) (GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
extern pfn_glTexImage3D fp_glTexImage3D;
typedef void (APIENTRYP pfn_glTexSubImage3D) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glTexSubImage3D fp_glTexSubImage3D;
typedef void (APIENTRYP pfn_glCopyTexSubImage3D) (GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
extern pfn_glCopyTexSubImage3D fp_glCopyTexSubImage3D;

 /* GL_VERSION_1_3 */
extern GLboolean GLAD_VERSION_1_3;
#define GL_TEXTURE0                            0x84C0
#define GL_TEXTURE1                            0x84C1
#define GL_TEXTURE2                            0x84C2
#define GL_TEXTURE3                            0x84C3
#define GL_TEXTURE4                            0x84C4
#define GL_TEXTURE5                            0x84C5
#define GL_TEXTURE6                            0x84C6
#define GL_TEXTURE7                            0x84C7
#define GL_TEXTURE8                            0x84C8
#define GL_TEXTURE9                            0x84C9
#define GL_TEXTURE10                           0x84CA
#define GL_TEXTURE11                           0x84CB
#define GL_TEXTURE12                           0x84CC
#define GL_TEXTURE13                           0x84CD
#define GL_TEXTURE14                           0x84CE
#define GL_TEXTURE15                           0x84CF
#define GL_TEXTURE16                           0x84D0
#define GL_TEXTURE17                           0x84D1
#define GL_TEXTURE18                           0x84D2
#define GL_TEXTURE19                           0x84D3
#define GL_TEXTURE20                           0x84D4
#define GL_TEXTURE21                           0x84D5
#define GL_TEXTURE22                           0x84D6
#define GL_TEXTURE23                           0x84D7
#define GL_TEXTURE24                           0x84D8
#define GL_TEXTURE25                           0x84D9
#define GL_TEXTURE26                           0x84DA
#define GL_TEXTURE27                           0x84DB
#define GL_TEXTURE28                           0x84DC
#define GL_TEXTURE29                           0x84DD
#define GL_TEXTURE30                           0x84DE
#define GL_TEXTURE31                           0x84DF
#define GL_ACTIVE_TEXTURE                      0x84E0
#define GL_MULTISAMPLE                         0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE            0x809E
#define GL_SAMPLE_ALPHA_TO_ONE                 0x809F
#define GL_SAMPLE_COVERAGE                     0x80A0
#define GL_SAMPLE_BUFFERS                      0x80A8
#define GL_SAMPLES                             0x80A9
#define GL_SAMPLE_COVERAGE_VALUE               0x80AA
#define GL_SAMPLE_COVERAGE_INVERT              0x80AB
#define GL_TEXTURE_CUBE_MAP                    0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP            0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X         0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X         0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y         0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y         0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z         0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z         0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP              0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE           0x851C
#define GL_COMPRESSED_RGB                      0x84ED
#define GL_COMPRESSED_RGBA                     0x84EE
#define GL_TEXTURE_COMPRESSION_HINT            0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE       0x86A0
#define GL_TEXTURE_COMPRESSED                  0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS      0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS          0x86A3
#define GL_CLAMP_TO_BORDER                     0x812D
#define GL_CLIENT_ACTIVE_TEXTURE               0x84E1
#define GL_MAX_TEXTURE_UNITS                   0x84E2
#define GL_TRANSPOSE_MODELVIEW_MATRIX          0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX         0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX            0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX              0x84E6
#define GL_MULTISAMPLE_BIT                     0x20000000
#define GL_NORMAL_MAP                          0x8511
#define GL_REFLECTION_MAP                      0x8512
#define GL_COMPRESSED_ALPHA                    0x84E9
#define GL_COMPRESSED_LUMINANCE                0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA          0x84EB
#define GL_COMPRESSED_INTENSITY                0x84EC
#define GL_COMBINE                             0x8570
#define GL_COMBINE_RGB                         0x8571
#define GL_COMBINE_ALPHA                       0x8572
#define GL_SOURCE0_RGB                         0x8580
#define GL_SOURCE1_RGB                         0x8581
#define GL_SOURCE2_RGB                         0x8582
#define GL_SOURCE0_ALPHA                       0x8588
#define GL_SOURCE1_ALPHA                       0x8589
#define GL_SOURCE2_ALPHA                       0x858A
#define GL_OPERAND0_RGB                        0x8590
#define GL_OPERAND1_RGB                        0x8591
#define GL_OPERAND2_RGB                        0x8592
#define GL_OPERAND0_ALPHA                      0x8598
#define GL_OPERAND1_ALPHA                      0x8599
#define GL_OPERAND2_ALPHA                      0x859A
#define GL_RGB_SCALE                           0x8573
#define GL_ADD_SIGNED                          0x8574
#define GL_INTERPOLATE                         0x8575
#define GL_SUBTRACT                            0x84E7
#define GL_CONSTANT                            0x8576
#define GL_PRIMARY_COLOR                       0x8577
#define GL_PREVIOUS                            0x8578
#define GL_DOT3_RGB                            0x86AE
#define GL_DOT3_RGBA                           0x86AF
typedef void (APIENTRYP pfn_glActiveTexture) (GLenum);
extern pfn_glActiveTexture fp_glActiveTexture;
typedef void (APIENTRYP pfn_glSampleCoverage) (GLfloat, GLboolean);
extern pfn_glSampleCoverage fp_glSampleCoverage;
typedef void (APIENTRYP pfn_glCompressedTexImage3D) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedTexImage3D fp_glCompressedTexImage3D;
typedef void (APIENTRYP pfn_glCompressedTexImage2D) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedTexImage2D fp_glCompressedTexImage2D;
typedef void (APIENTRYP pfn_glCompressedTexImage1D) (GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedTexImage1D fp_glCompressedTexImage1D;
typedef void (APIENTRYP pfn_glCompressedTexSubImage3D) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedTexSubImage3D fp_glCompressedTexSubImage3D;
typedef void (APIENTRYP pfn_glCompressedTexSubImage2D) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedTexSubImage2D fp_glCompressedTexSubImage2D;
typedef void (APIENTRYP pfn_glCompressedTexSubImage1D) (GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedTexSubImage1D fp_glCompressedTexSubImage1D;
typedef void (APIENTRYP pfn_glGetCompressedTexImage) (GLenum, GLint, void*);
extern pfn_glGetCompressedTexImage fp_glGetCompressedTexImage;
typedef void (APIENTRYP pfn_glClientActiveTexture) (GLenum);
extern pfn_glClientActiveTexture fp_glClientActiveTexture;
typedef void (APIENTRYP pfn_glMultiTexCoord1d) (GLenum, GLdouble);
extern pfn_glMultiTexCoord1d fp_glMultiTexCoord1d;
typedef void (APIENTRYP pfn_glMultiTexCoord1dv) (GLenum, const GLdouble*);
extern pfn_glMultiTexCoord1dv fp_glMultiTexCoord1dv;
typedef void (APIENTRYP pfn_glMultiTexCoord1f) (GLenum, GLfloat);
extern pfn_glMultiTexCoord1f fp_glMultiTexCoord1f;
typedef void (APIENTRYP pfn_glMultiTexCoord1fv) (GLenum, const GLfloat*);
extern pfn_glMultiTexCoord1fv fp_glMultiTexCoord1fv;
typedef void (APIENTRYP pfn_glMultiTexCoord1i) (GLenum, GLint);
extern pfn_glMultiTexCoord1i fp_glMultiTexCoord1i;
typedef void (APIENTRYP pfn_glMultiTexCoord1iv) (GLenum, const GLint*);
extern pfn_glMultiTexCoord1iv fp_glMultiTexCoord1iv;
typedef void (APIENTRYP pfn_glMultiTexCoord1s) (GLenum, GLshort);
extern pfn_glMultiTexCoord1s fp_glMultiTexCoord1s;
typedef void (APIENTRYP pfn_glMultiTexCoord1sv) (GLenum, const GLshort*);
extern pfn_glMultiTexCoord1sv fp_glMultiTexCoord1sv;
typedef void (APIENTRYP pfn_glMultiTexCoord2d) (GLenum, GLdouble, GLdouble);
extern pfn_glMultiTexCoord2d fp_glMultiTexCoord2d;
typedef void (APIENTRYP pfn_glMultiTexCoord2dv) (GLenum, const GLdouble*);
extern pfn_glMultiTexCoord2dv fp_glMultiTexCoord2dv;
typedef void (APIENTRYP pfn_glMultiTexCoord2f) (GLenum, GLfloat, GLfloat);
extern pfn_glMultiTexCoord2f fp_glMultiTexCoord2f;
typedef void (APIENTRYP pfn_glMultiTexCoord2fv) (GLenum, const GLfloat*);
extern pfn_glMultiTexCoord2fv fp_glMultiTexCoord2fv;
typedef void (APIENTRYP pfn_glMultiTexCoord2i) (GLenum, GLint, GLint);
extern pfn_glMultiTexCoord2i fp_glMultiTexCoord2i;
typedef void (APIENTRYP pfn_glMultiTexCoord2iv) (GLenum, const GLint*);
extern pfn_glMultiTexCoord2iv fp_glMultiTexCoord2iv;
typedef void (APIENTRYP pfn_glMultiTexCoord2s) (GLenum, GLshort, GLshort);
extern pfn_glMultiTexCoord2s fp_glMultiTexCoord2s;
typedef void (APIENTRYP pfn_glMultiTexCoord2sv) (GLenum, const GLshort*);
extern pfn_glMultiTexCoord2sv fp_glMultiTexCoord2sv;
typedef void (APIENTRYP pfn_glMultiTexCoord3d) (GLenum, GLdouble, GLdouble, GLdouble);
extern pfn_glMultiTexCoord3d fp_glMultiTexCoord3d;
typedef void (APIENTRYP pfn_glMultiTexCoord3dv) (GLenum, const GLdouble*);
extern pfn_glMultiTexCoord3dv fp_glMultiTexCoord3dv;
typedef void (APIENTRYP pfn_glMultiTexCoord3f) (GLenum, GLfloat, GLfloat, GLfloat);
extern pfn_glMultiTexCoord3f fp_glMultiTexCoord3f;
typedef void (APIENTRYP pfn_glMultiTexCoord3fv) (GLenum, const GLfloat*);
extern pfn_glMultiTexCoord3fv fp_glMultiTexCoord3fv;
typedef void (APIENTRYP pfn_glMultiTexCoord3i) (GLenum, GLint, GLint, GLint);
extern pfn_glMultiTexCoord3i fp_glMultiTexCoord3i;
typedef void (APIENTRYP pfn_glMultiTexCoord3iv) (GLenum, const GLint*);
extern pfn_glMultiTexCoord3iv fp_glMultiTexCoord3iv;
typedef void (APIENTRYP pfn_glMultiTexCoord3s) (GLenum, GLshort, GLshort, GLshort);
extern pfn_glMultiTexCoord3s fp_glMultiTexCoord3s;
typedef void (APIENTRYP pfn_glMultiTexCoord3sv) (GLenum, const GLshort*);
extern pfn_glMultiTexCoord3sv fp_glMultiTexCoord3sv;
typedef void (APIENTRYP pfn_glMultiTexCoord4d) (GLenum, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glMultiTexCoord4d fp_glMultiTexCoord4d;
typedef void (APIENTRYP pfn_glMultiTexCoord4dv) (GLenum, const GLdouble*);
extern pfn_glMultiTexCoord4dv fp_glMultiTexCoord4dv;
typedef void (APIENTRYP pfn_glMultiTexCoord4f) (GLenum, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glMultiTexCoord4f fp_glMultiTexCoord4f;
typedef void (APIENTRYP pfn_glMultiTexCoord4fv) (GLenum, const GLfloat*);
extern pfn_glMultiTexCoord4fv fp_glMultiTexCoord4fv;
typedef void (APIENTRYP pfn_glMultiTexCoord4i) (GLenum, GLint, GLint, GLint, GLint);
extern pfn_glMultiTexCoord4i fp_glMultiTexCoord4i;
typedef void (APIENTRYP pfn_glMultiTexCoord4iv) (GLenum, const GLint*);
extern pfn_glMultiTexCoord4iv fp_glMultiTexCoord4iv;
typedef void (APIENTRYP pfn_glMultiTexCoord4s) (GLenum, GLshort, GLshort, GLshort, GLshort);
extern pfn_glMultiTexCoord4s fp_glMultiTexCoord4s;
typedef void (APIENTRYP pfn_glMultiTexCoord4sv) (GLenum, const GLshort*);
extern pfn_glMultiTexCoord4sv fp_glMultiTexCoord4sv;
typedef void (APIENTRYP pfn_glLoadTransposeMatrixf) (const GLfloat*);
extern pfn_glLoadTransposeMatrixf fp_glLoadTransposeMatrixf;
typedef void (APIENTRYP pfn_glLoadTransposeMatrixd) (const GLdouble*);
extern pfn_glLoadTransposeMatrixd fp_glLoadTransposeMatrixd;
typedef void (APIENTRYP pfn_glMultTransposeMatrixf) (const GLfloat*);
extern pfn_glMultTransposeMatrixf fp_glMultTransposeMatrixf;
typedef void (APIENTRYP pfn_glMultTransposeMatrixd) (const GLdouble*);
extern pfn_glMultTransposeMatrixd fp_glMultTransposeMatrixd;

 /* GL_VERSION_1_4 */
extern GLboolean GLAD_VERSION_1_4;
#define GL_BLEND_DST_RGB                       0x80C8
#define GL_BLEND_SRC_RGB                       0x80C9
#define GL_BLEND_DST_ALPHA                     0x80CA
#define GL_BLEND_SRC_ALPHA                     0x80CB
#define GL_POINT_FADE_THRESHOLD_SIZE           0x8128
#define GL_DEPTH_COMPONENT16                   0x81A5
#define GL_DEPTH_COMPONENT24                   0x81A6
#define GL_DEPTH_COMPONENT32                   0x81A7
#define GL_MIRRORED_REPEAT                     0x8370
#define GL_MAX_TEXTURE_LOD_BIAS                0x84FD
#define GL_TEXTURE_LOD_BIAS                    0x8501
#define GL_INCR_WRAP                           0x8507
#define GL_DECR_WRAP                           0x8508
#define GL_TEXTURE_DEPTH_SIZE                  0x884A
#define GL_TEXTURE_COMPARE_MODE                0x884C
#define GL_TEXTURE_COMPARE_FUNC                0x884D
#define GL_POINT_SIZE_MIN                      0x8126
#define GL_POINT_SIZE_MAX                      0x8127
#define GL_POINT_DISTANCE_ATTENUATION          0x8129
#define GL_GENERATE_MIPMAP                     0x8191
#define GL_GENERATE_MIPMAP_HINT                0x8192
#define GL_FOG_COORDINATE_SOURCE               0x8450
#define GL_FOG_COORDINATE                      0x8451
#define GL_FRAGMENT_DEPTH                      0x8452
#define GL_CURRENT_FOG_COORDINATE              0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE           0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE         0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER        0x8456
#define GL_FOG_COORDINATE_ARRAY                0x8457
#define GL_COLOR_SUM                           0x8458
#define GL_CURRENT_SECONDARY_COLOR             0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE          0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE          0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE        0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER       0x845D
#define GL_SECONDARY_COLOR_ARRAY               0x845E
#define GL_TEXTURE_FILTER_CONTROL              0x8500
#define GL_DEPTH_TEXTURE_MODE                  0x884B
#define GL_COMPARE_R_TO_TEXTURE                0x884E
#define GL_FUNC_ADD                            0x8006
#define GL_FUNC_SUBTRACT                       0x800A
#define GL_FUNC_REVERSE_SUBTRACT               0x800B
#define GL_MIN                                 0x8007
#define GL_MAX                                 0x8008
#define GL_CONSTANT_COLOR                      0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR            0x8002
#define GL_CONSTANT_ALPHA                      0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA            0x8004
typedef void (APIENTRYP pfn_glBlendFuncSeparate) (GLenum, GLenum, GLenum, GLenum);
extern pfn_glBlendFuncSeparate fp_glBlendFuncSeparate;
typedef void (APIENTRYP pfn_glMultiDrawArrays) (GLenum, const GLint*, const GLsizei*, GLsizei);
extern pfn_glMultiDrawArrays fp_glMultiDrawArrays;
typedef void (APIENTRYP pfn_glMultiDrawElements) (GLenum, const GLsizei*, GLenum, const void**, GLsizei);
extern pfn_glMultiDrawElements fp_glMultiDrawElements;
typedef void (APIENTRYP pfn_glPointParameterf) (GLenum, GLfloat);
extern pfn_glPointParameterf fp_glPointParameterf;
typedef void (APIENTRYP pfn_glPointParameterfv) (GLenum, const GLfloat*);
extern pfn_glPointParameterfv fp_glPointParameterfv;
typedef void (APIENTRYP pfn_glPointParameteri) (GLenum, GLint);
extern pfn_glPointParameteri fp_glPointParameteri;
typedef void (APIENTRYP pfn_glPointParameteriv) (GLenum, const GLint*);
extern pfn_glPointParameteriv fp_glPointParameteriv;
typedef void (APIENTRYP pfn_glFogCoordf) (GLfloat);
extern pfn_glFogCoordf fp_glFogCoordf;
typedef void (APIENTRYP pfn_glFogCoordfv) (const GLfloat*);
extern pfn_glFogCoordfv fp_glFogCoordfv;
typedef void (APIENTRYP pfn_glFogCoordd) (GLdouble);
extern pfn_glFogCoordd fp_glFogCoordd;
typedef void (APIENTRYP pfn_glFogCoorddv) (const GLdouble*);
extern pfn_glFogCoorddv fp_glFogCoorddv;
typedef void (APIENTRYP pfn_glFogCoordPointer) (GLenum, GLsizei, const void*);
extern pfn_glFogCoordPointer fp_glFogCoordPointer;
typedef void (APIENTRYP pfn_glSecondaryColor3b) (GLbyte, GLbyte, GLbyte);
extern pfn_glSecondaryColor3b fp_glSecondaryColor3b;
typedef void (APIENTRYP pfn_glSecondaryColor3bv) (const GLbyte*);
extern pfn_glSecondaryColor3bv fp_glSecondaryColor3bv;
typedef void (APIENTRYP pfn_glSecondaryColor3d) (GLdouble, GLdouble, GLdouble);
extern pfn_glSecondaryColor3d fp_glSecondaryColor3d;
typedef void (APIENTRYP pfn_glSecondaryColor3dv) (const GLdouble*);
extern pfn_glSecondaryColor3dv fp_glSecondaryColor3dv;
typedef void (APIENTRYP pfn_glSecondaryColor3f) (GLfloat, GLfloat, GLfloat);
extern pfn_glSecondaryColor3f fp_glSecondaryColor3f;
typedef void (APIENTRYP pfn_glSecondaryColor3fv) (const GLfloat*);
extern pfn_glSecondaryColor3fv fp_glSecondaryColor3fv;
typedef void (APIENTRYP pfn_glSecondaryColor3i) (GLint, GLint, GLint);
extern pfn_glSecondaryColor3i fp_glSecondaryColor3i;
typedef void (APIENTRYP pfn_glSecondaryColor3iv) (const GLint*);
extern pfn_glSecondaryColor3iv fp_glSecondaryColor3iv;
typedef void (APIENTRYP pfn_glSecondaryColor3s) (GLshort, GLshort, GLshort);
extern pfn_glSecondaryColor3s fp_glSecondaryColor3s;
typedef void (APIENTRYP pfn_glSecondaryColor3sv) (const GLshort*);
extern pfn_glSecondaryColor3sv fp_glSecondaryColor3sv;
typedef void (APIENTRYP pfn_glSecondaryColor3ub) (GLubyte, GLubyte, GLubyte);
extern pfn_glSecondaryColor3ub fp_glSecondaryColor3ub;
typedef void (APIENTRYP pfn_glSecondaryColor3ubv) (const GLubyte*);
extern pfn_glSecondaryColor3ubv fp_glSecondaryColor3ubv;
typedef void (APIENTRYP pfn_glSecondaryColor3ui) (GLuint, GLuint, GLuint);
extern pfn_glSecondaryColor3ui fp_glSecondaryColor3ui;
typedef void (APIENTRYP pfn_glSecondaryColor3uiv) (const GLuint*);
extern pfn_glSecondaryColor3uiv fp_glSecondaryColor3uiv;
typedef void (APIENTRYP pfn_glSecondaryColor3us) (GLushort, GLushort, GLushort);
extern pfn_glSecondaryColor3us fp_glSecondaryColor3us;
typedef void (APIENTRYP pfn_glSecondaryColor3usv) (const GLushort*);
extern pfn_glSecondaryColor3usv fp_glSecondaryColor3usv;
typedef void (APIENTRYP pfn_glSecondaryColorPointer) (GLint, GLenum, GLsizei, const void*);
extern pfn_glSecondaryColorPointer fp_glSecondaryColorPointer;
typedef void (APIENTRYP pfn_glWindowPos2d) (GLdouble, GLdouble);
extern pfn_glWindowPos2d fp_glWindowPos2d;
typedef void (APIENTRYP pfn_glWindowPos2dv) (const GLdouble*);
extern pfn_glWindowPos2dv fp_glWindowPos2dv;
typedef void (APIENTRYP pfn_glWindowPos2f) (GLfloat, GLfloat);
extern pfn_glWindowPos2f fp_glWindowPos2f;
typedef void (APIENTRYP pfn_glWindowPos2fv) (const GLfloat*);
extern pfn_glWindowPos2fv fp_glWindowPos2fv;
typedef void (APIENTRYP pfn_glWindowPos2i) (GLint, GLint);
extern pfn_glWindowPos2i fp_glWindowPos2i;
typedef void (APIENTRYP pfn_glWindowPos2iv) (const GLint*);
extern pfn_glWindowPos2iv fp_glWindowPos2iv;
typedef void (APIENTRYP pfn_glWindowPos2s) (GLshort, GLshort);
extern pfn_glWindowPos2s fp_glWindowPos2s;
typedef void (APIENTRYP pfn_glWindowPos2sv) (const GLshort*);
extern pfn_glWindowPos2sv fp_glWindowPos2sv;
typedef void (APIENTRYP pfn_glWindowPos3d) (GLdouble, GLdouble, GLdouble);
extern pfn_glWindowPos3d fp_glWindowPos3d;
typedef void (APIENTRYP pfn_glWindowPos3dv) (const GLdouble*);
extern pfn_glWindowPos3dv fp_glWindowPos3dv;
typedef void (APIENTRYP pfn_glWindowPos3f) (GLfloat, GLfloat, GLfloat);
extern pfn_glWindowPos3f fp_glWindowPos3f;
typedef void (APIENTRYP pfn_glWindowPos3fv) (const GLfloat*);
extern pfn_glWindowPos3fv fp_glWindowPos3fv;
typedef void (APIENTRYP pfn_glWindowPos3i) (GLint, GLint, GLint);
extern pfn_glWindowPos3i fp_glWindowPos3i;
typedef void (APIENTRYP pfn_glWindowPos3iv) (const GLint*);
extern pfn_glWindowPos3iv fp_glWindowPos3iv;
typedef void (APIENTRYP pfn_glWindowPos3s) (GLshort, GLshort, GLshort);
extern pfn_glWindowPos3s fp_glWindowPos3s;
typedef void (APIENTRYP pfn_glWindowPos3sv) (const GLshort*);
extern pfn_glWindowPos3sv fp_glWindowPos3sv;
typedef void (APIENTRYP pfn_glBlendColor) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glBlendColor fp_glBlendColor;
typedef void (APIENTRYP pfn_glBlendEquation) (GLenum);
extern pfn_glBlendEquation fp_glBlendEquation;

 /* GL_VERSION_1_5 */
extern GLboolean GLAD_VERSION_1_5;
#define GL_BUFFER_SIZE                         0x8764
#define GL_BUFFER_USAGE                        0x8765
#define GL_QUERY_COUNTER_BITS                  0x8864
#define GL_CURRENT_QUERY                       0x8865
#define GL_QUERY_RESULT                        0x8866
#define GL_QUERY_RESULT_AVAILABLE              0x8867
#define GL_ARRAY_BUFFER                        0x8892
#define GL_ELEMENT_ARRAY_BUFFER                0x8893
#define GL_ARRAY_BUFFER_BINDING                0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING        0x8895
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING  0x889F
#define GL_READ_ONLY                           0x88B8
#define GL_WRITE_ONLY                          0x88B9
#define GL_READ_WRITE                          0x88BA
#define GL_BUFFER_ACCESS                       0x88BB
#define GL_BUFFER_MAPPED                       0x88BC
#define GL_BUFFER_MAP_POINTER                  0x88BD
#define GL_STREAM_DRAW                         0x88E0
#define GL_STREAM_READ                         0x88E1
#define GL_STREAM_COPY                         0x88E2
#define GL_STATIC_DRAW                         0x88E4
#define GL_STATIC_READ                         0x88E5
#define GL_STATIC_COPY                         0x88E6
#define GL_DYNAMIC_DRAW                        0x88E8
#define GL_DYNAMIC_READ                        0x88E9
#define GL_DYNAMIC_COPY                        0x88EA
#define GL_SAMPLES_PASSED                      0x8914
#define GL_SRC1_ALPHA                          0x8589
#define GL_VERTEX_ARRAY_BUFFER_BINDING         0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING         0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING          0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING          0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING  0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING      0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING  0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING  0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING         0x889E
#define GL_FOG_COORD_SRC                       0x8450
#define GL_FOG_COORD                           0x8451
#define GL_CURRENT_FOG_COORD                   0x8453
#define GL_FOG_COORD_ARRAY_TYPE                0x8454
#define GL_FOG_COORD_ARRAY_STRIDE              0x8455
#define GL_FOG_COORD_ARRAY_POINTER             0x8456
#define GL_FOG_COORD_ARRAY                     0x8457
#define GL_FOG_COORD_ARRAY_BUFFER_BINDING      0x889D
#define GL_SRC0_RGB                            0x8580
#define GL_SRC1_RGB                            0x8581
#define GL_SRC2_RGB                            0x8582
#define GL_SRC0_ALPHA                          0x8588
#define GL_SRC2_ALPHA                          0x858A
typedef void (APIENTRYP pfn_glGenQueries) (GLsizei, GLuint*);
extern pfn_glGenQueries fp_glGenQueries;
typedef void (APIENTRYP pfn_glDeleteQueries) (GLsizei, const GLuint*);
extern pfn_glDeleteQueries fp_glDeleteQueries;
typedef GLboolean (APIENTRYP pfn_glIsQuery) (GLuint);
extern pfn_glIsQuery fp_glIsQuery;
typedef void (APIENTRYP pfn_glBeginQuery) (GLenum, GLuint);
extern pfn_glBeginQuery fp_glBeginQuery;
typedef void (APIENTRYP pfn_glEndQuery) (GLenum);
extern pfn_glEndQuery fp_glEndQuery;
typedef void (APIENTRYP pfn_glGetQueryiv) (GLenum, GLenum, GLint*);
extern pfn_glGetQueryiv fp_glGetQueryiv;
typedef void (APIENTRYP pfn_glGetQueryObjectiv) (GLuint, GLenum, GLint*);
extern pfn_glGetQueryObjectiv fp_glGetQueryObjectiv;
typedef void (APIENTRYP pfn_glGetQueryObjectuiv) (GLuint, GLenum, GLuint*);
extern pfn_glGetQueryObjectuiv fp_glGetQueryObjectuiv;
typedef void (APIENTRYP pfn_glBindBuffer) (GLenum, GLuint);
extern pfn_glBindBuffer fp_glBindBuffer;
typedef void (APIENTRYP pfn_glDeleteBuffers) (GLsizei, const GLuint*);
extern pfn_glDeleteBuffers fp_glDeleteBuffers;
typedef void (APIENTRYP pfn_glGenBuffers) (GLsizei, GLuint*);
extern pfn_glGenBuffers fp_glGenBuffers;
typedef GLboolean (APIENTRYP pfn_glIsBuffer) (GLuint);
extern pfn_glIsBuffer fp_glIsBuffer;
typedef void (APIENTRYP pfn_glBufferData) (GLenum, GLsizeiptr, const void*, GLenum);
extern pfn_glBufferData fp_glBufferData;
typedef void (APIENTRYP pfn_glBufferSubData) (GLenum, GLintptr, GLsizeiptr, const void*);
extern pfn_glBufferSubData fp_glBufferSubData;
typedef void (APIENTRYP pfn_glGetBufferSubData) (GLenum, GLintptr, GLsizeiptr, void*);
extern pfn_glGetBufferSubData fp_glGetBufferSubData;
typedef void* (APIENTRYP pfn_glMapBuffer) (GLenum, GLenum);
extern pfn_glMapBuffer fp_glMapBuffer;
typedef GLboolean (APIENTRYP pfn_glUnmapBuffer) (GLenum);
extern pfn_glUnmapBuffer fp_glUnmapBuffer;
typedef void (APIENTRYP pfn_glGetBufferParameteriv) (GLenum, GLenum, GLint*);
extern pfn_glGetBufferParameteriv fp_glGetBufferParameteriv;
typedef void (APIENTRYP pfn_glGetBufferPointerv) (GLenum, GLenum, void**);
extern pfn_glGetBufferPointerv fp_glGetBufferPointerv;

 /* GL_VERSION_2_0 */
extern GLboolean GLAD_VERSION_2_0;
#define GL_BLEND_EQUATION_RGB                  0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED         0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE            0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE          0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE            0x8625
#define GL_CURRENT_VERTEX_ATTRIB               0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE           0x8642
#define GL_VERTEX_ATTRIB_ARRAY_POINTER         0x8645
#define GL_STENCIL_BACK_FUNC                   0x8800
#define GL_STENCIL_BACK_FAIL                   0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL        0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS        0x8803
#define GL_MAX_DRAW_BUFFERS                    0x8824
#define GL_DRAW_BUFFER0                        0x8825
#define GL_DRAW_BUFFER1                        0x8826
#define GL_DRAW_BUFFER2                        0x8827
#define GL_DRAW_BUFFER3                        0x8828
#define GL_DRAW_BUFFER4                        0x8829
#define GL_DRAW_BUFFER5                        0x882A
#define GL_DRAW_BUFFER6                        0x882B
#define GL_DRAW_BUFFER7                        0x882C
#define GL_DRAW_BUFFER8                        0x882D
#define GL_DRAW_BUFFER9                        0x882E
#define GL_DRAW_BUFFER10                       0x882F
#define GL_DRAW_BUFFER11                       0x8830
#define GL_DRAW_BUFFER12                       0x8831
#define GL_DRAW_BUFFER13                       0x8832
#define GL_DRAW_BUFFER14                       0x8833
#define GL_DRAW_BUFFER15                       0x8834
#define GL_BLEND_EQUATION_ALPHA                0x883D
#define GL_MAX_VERTEX_ATTRIBS                  0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED      0x886A
#define GL_MAX_TEXTURE_IMAGE_UNITS             0x8872
#define GL_FRAGMENT_SHADER                     0x8B30
#define GL_VERTEX_SHADER                       0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS     0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS       0x8B4A
#define GL_MAX_VARYING_FLOATS                  0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS      0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS    0x8B4D
#define GL_SHADER_TYPE                         0x8B4F
#define GL_FLOAT_VEC2                          0x8B50
#define GL_FLOAT_VEC3                          0x8B51
#define GL_FLOAT_VEC4                          0x8B52
#define GL_INT_VEC2                            0x8B53
#define GL_INT_VEC3                            0x8B54
#define GL_INT_VEC4                            0x8B55
#define GL_BOOL                                0x8B56
#define GL_BOOL_VEC2                           0x8B57
#define GL_BOOL_VEC3                           0x8B58
#define GL_BOOL_VEC4                           0x8B59
#define GL_FLOAT_MAT2                          0x8B5A
#define GL_FLOAT_MAT3                          0x8B5B
#define GL_FLOAT_MAT4                          0x8B5C
#define GL_SAMPLER_1D                          0x8B5D
#define GL_SAMPLER_2D                          0x8B5E
#define GL_SAMPLER_3D                          0x8B5F
#define GL_SAMPLER_CUBE                        0x8B60
#define GL_SAMPLER_1D_SHADOW                   0x8B61
#define GL_SAMPLER_2D_SHADOW                   0x8B62
#define GL_DELETE_STATUS                       0x8B80
#define GL_COMPILE_STATUS                      0x8B81
#define GL_LINK_STATUS                         0x8B82
#define GL_VALIDATE_STATUS                     0x8B83
#define GL_INFO_LOG_LENGTH                     0x8B84
#define GL_ATTACHED_SHADERS                    0x8B85
#define GL_ACTIVE_UNIFORMS                     0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH           0x8B87
#define GL_SHADER_SOURCE_LENGTH                0x8B88
#define GL_ACTIVE_ATTRIBUTES                   0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH         0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT     0x8B8B
#define GL_SHADING_LANGUAGE_VERSION            0x8B8C
#define GL_CURRENT_PROGRAM                     0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN           0x8CA0
#define GL_LOWER_LEFT                          0x8CA1
#define GL_UPPER_LEFT                          0x8CA2
#define GL_STENCIL_BACK_REF                    0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK             0x8CA4
#define GL_STENCIL_BACK_WRITEMASK              0x8CA5
#define GL_VERTEX_PROGRAM_TWO_SIDE             0x8643
#define GL_POINT_SPRITE                        0x8861
#define GL_COORD_REPLACE                       0x8862
#define GL_MAX_TEXTURE_COORDS                  0x8871
typedef void (APIENTRYP pfn_glBlendEquationSeparate) (GLenum, GLenum);
extern pfn_glBlendEquationSeparate fp_glBlendEquationSeparate;
typedef void (APIENTRYP pfn_glDrawBuffers) (GLsizei, const GLenum*);
extern pfn_glDrawBuffers fp_glDrawBuffers;
typedef void (APIENTRYP pfn_glStencilOpSeparate) (GLenum, GLenum, GLenum, GLenum);
extern pfn_glStencilOpSeparate fp_glStencilOpSeparate;
typedef void (APIENTRYP pfn_glStencilFuncSeparate) (GLenum, GLenum, GLint, GLuint);
extern pfn_glStencilFuncSeparate fp_glStencilFuncSeparate;
typedef void (APIENTRYP pfn_glStencilMaskSeparate) (GLenum, GLuint);
extern pfn_glStencilMaskSeparate fp_glStencilMaskSeparate;
typedef void (APIENTRYP pfn_glAttachShader) (GLuint, GLuint);
extern pfn_glAttachShader fp_glAttachShader;
typedef void (APIENTRYP pfn_glBindAttribLocation) (GLuint, GLuint, const GLchar*);
extern pfn_glBindAttribLocation fp_glBindAttribLocation;
typedef void (APIENTRYP pfn_glCompileShader) (GLuint);
extern pfn_glCompileShader fp_glCompileShader;
typedef GLuint (APIENTRYP pfn_glCreateProgram) ();
extern pfn_glCreateProgram fp_glCreateProgram;
typedef GLuint (APIENTRYP pfn_glCreateShader) (GLenum);
extern pfn_glCreateShader fp_glCreateShader;
typedef void (APIENTRYP pfn_glDeleteProgram) (GLuint);
extern pfn_glDeleteProgram fp_glDeleteProgram;
typedef void (APIENTRYP pfn_glDeleteShader) (GLuint);
extern pfn_glDeleteShader fp_glDeleteShader;
typedef void (APIENTRYP pfn_glDetachShader) (GLuint, GLuint);
extern pfn_glDetachShader fp_glDetachShader;
typedef void (APIENTRYP pfn_glDisableVertexAttribArray) (GLuint);
extern pfn_glDisableVertexAttribArray fp_glDisableVertexAttribArray;
typedef void (APIENTRYP pfn_glEnableVertexAttribArray) (GLuint);
extern pfn_glEnableVertexAttribArray fp_glEnableVertexAttribArray;
typedef void (APIENTRYP pfn_glGetActiveAttrib) (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*);
extern pfn_glGetActiveAttrib fp_glGetActiveAttrib;
typedef void (APIENTRYP pfn_glGetActiveUniform) (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*);
extern pfn_glGetActiveUniform fp_glGetActiveUniform;
typedef void (APIENTRYP pfn_glGetAttachedShaders) (GLuint, GLsizei, GLsizei*, GLuint*);
extern pfn_glGetAttachedShaders fp_glGetAttachedShaders;
typedef GLint (APIENTRYP pfn_glGetAttribLocation) (GLuint, const GLchar*);
extern pfn_glGetAttribLocation fp_glGetAttribLocation;
typedef void (APIENTRYP pfn_glGetProgramiv) (GLuint, GLenum, GLint*);
extern pfn_glGetProgramiv fp_glGetProgramiv;
typedef void (APIENTRYP pfn_glGetProgramInfoLog) (GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetProgramInfoLog fp_glGetProgramInfoLog;
typedef void (APIENTRYP pfn_glGetShaderiv) (GLuint, GLenum, GLint*);
extern pfn_glGetShaderiv fp_glGetShaderiv;
typedef void (APIENTRYP pfn_glGetShaderInfoLog) (GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetShaderInfoLog fp_glGetShaderInfoLog;
typedef void (APIENTRYP pfn_glGetShaderSource) (GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetShaderSource fp_glGetShaderSource;
typedef GLint (APIENTRYP pfn_glGetUniformLocation) (GLuint, const GLchar*);
extern pfn_glGetUniformLocation fp_glGetUniformLocation;
typedef void (APIENTRYP pfn_glGetUniformfv) (GLuint, GLint, GLfloat*);
extern pfn_glGetUniformfv fp_glGetUniformfv;
typedef void (APIENTRYP pfn_glGetUniformiv) (GLuint, GLint, GLint*);
extern pfn_glGetUniformiv fp_glGetUniformiv;
typedef void (APIENTRYP pfn_glGetVertexAttribdv) (GLuint, GLenum, GLdouble*);
extern pfn_glGetVertexAttribdv fp_glGetVertexAttribdv;
typedef void (APIENTRYP pfn_glGetVertexAttribfv) (GLuint, GLenum, GLfloat*);
extern pfn_glGetVertexAttribfv fp_glGetVertexAttribfv;
typedef void (APIENTRYP pfn_glGetVertexAttribiv) (GLuint, GLenum, GLint*);
extern pfn_glGetVertexAttribiv fp_glGetVertexAttribiv;
typedef void (APIENTRYP pfn_glGetVertexAttribPointerv) (GLuint, GLenum, void**);
extern pfn_glGetVertexAttribPointerv fp_glGetVertexAttribPointerv;
typedef GLboolean (APIENTRYP pfn_glIsProgram) (GLuint);
extern pfn_glIsProgram fp_glIsProgram;
typedef GLboolean (APIENTRYP pfn_glIsShader) (GLuint);
extern pfn_glIsShader fp_glIsShader;
typedef void (APIENTRYP pfn_glLinkProgram) (GLuint);
extern pfn_glLinkProgram fp_glLinkProgram;
typedef void (APIENTRYP pfn_glShaderSource) (GLuint, GLsizei, const GLchar**, const GLint*);
extern pfn_glShaderSource fp_glShaderSource;
typedef void (APIENTRYP pfn_glUseProgram) (GLuint);
extern pfn_glUseProgram fp_glUseProgram;
typedef void (APIENTRYP pfn_glUniform1f) (GLint, GLfloat);
extern pfn_glUniform1f fp_glUniform1f;
typedef void (APIENTRYP pfn_glUniform2f) (GLint, GLfloat, GLfloat);
extern pfn_glUniform2f fp_glUniform2f;
typedef void (APIENTRYP pfn_glUniform3f) (GLint, GLfloat, GLfloat, GLfloat);
extern pfn_glUniform3f fp_glUniform3f;
typedef void (APIENTRYP pfn_glUniform4f) (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glUniform4f fp_glUniform4f;
typedef void (APIENTRYP pfn_glUniform1i) (GLint, GLint);
extern pfn_glUniform1i fp_glUniform1i;
typedef void (APIENTRYP pfn_glUniform2i) (GLint, GLint, GLint);
extern pfn_glUniform2i fp_glUniform2i;
typedef void (APIENTRYP pfn_glUniform3i) (GLint, GLint, GLint, GLint);
extern pfn_glUniform3i fp_glUniform3i;
typedef void (APIENTRYP pfn_glUniform4i) (GLint, GLint, GLint, GLint, GLint);
extern pfn_glUniform4i fp_glUniform4i;
typedef void (APIENTRYP pfn_glUniform1fv) (GLint, GLsizei, const GLfloat*);
extern pfn_glUniform1fv fp_glUniform1fv;
typedef void (APIENTRYP pfn_glUniform2fv) (GLint, GLsizei, const GLfloat*);
extern pfn_glUniform2fv fp_glUniform2fv;
typedef void (APIENTRYP pfn_glUniform3fv) (GLint, GLsizei, const GLfloat*);
extern pfn_glUniform3fv fp_glUniform3fv;
typedef void (APIENTRYP pfn_glUniform4fv) (GLint, GLsizei, const GLfloat*);
extern pfn_glUniform4fv fp_glUniform4fv;
typedef void (APIENTRYP pfn_glUniform1iv) (GLint, GLsizei, const GLint*);
extern pfn_glUniform1iv fp_glUniform1iv;
typedef void (APIENTRYP pfn_glUniform2iv) (GLint, GLsizei, const GLint*);
extern pfn_glUniform2iv fp_glUniform2iv;
typedef void (APIENTRYP pfn_glUniform3iv) (GLint, GLsizei, const GLint*);
extern pfn_glUniform3iv fp_glUniform3iv;
typedef void (APIENTRYP pfn_glUniform4iv) (GLint, GLsizei, const GLint*);
extern pfn_glUniform4iv fp_glUniform4iv;
typedef void (APIENTRYP pfn_glUniformMatrix2fv) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix2fv fp_glUniformMatrix2fv;
typedef void (APIENTRYP pfn_glUniformMatrix3fv) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix3fv fp_glUniformMatrix3fv;
typedef void (APIENTRYP pfn_glUniformMatrix4fv) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix4fv fp_glUniformMatrix4fv;
typedef void (APIENTRYP pfn_glValidateProgram) (GLuint);
extern pfn_glValidateProgram fp_glValidateProgram;
typedef void (APIENTRYP pfn_glVertexAttrib1d) (GLuint, GLdouble);
extern pfn_glVertexAttrib1d fp_glVertexAttrib1d;
typedef void (APIENTRYP pfn_glVertexAttrib1dv) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib1dv fp_glVertexAttrib1dv;
typedef void (APIENTRYP pfn_glVertexAttrib1f) (GLuint, GLfloat);
extern pfn_glVertexAttrib1f fp_glVertexAttrib1f;
typedef void (APIENTRYP pfn_glVertexAttrib1fv) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib1fv fp_glVertexAttrib1fv;
typedef void (APIENTRYP pfn_glVertexAttrib1s) (GLuint, GLshort);
extern pfn_glVertexAttrib1s fp_glVertexAttrib1s;
typedef void (APIENTRYP pfn_glVertexAttrib1sv) (GLuint, const GLshort*);
extern pfn_glVertexAttrib1sv fp_glVertexAttrib1sv;
typedef void (APIENTRYP pfn_glVertexAttrib2d) (GLuint, GLdouble, GLdouble);
extern pfn_glVertexAttrib2d fp_glVertexAttrib2d;
typedef void (APIENTRYP pfn_glVertexAttrib2dv) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib2dv fp_glVertexAttrib2dv;
typedef void (APIENTRYP pfn_glVertexAttrib2f) (GLuint, GLfloat, GLfloat);
extern pfn_glVertexAttrib2f fp_glVertexAttrib2f;
typedef void (APIENTRYP pfn_glVertexAttrib2fv) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib2fv fp_glVertexAttrib2fv;
typedef void (APIENTRYP pfn_glVertexAttrib2s) (GLuint, GLshort, GLshort);
extern pfn_glVertexAttrib2s fp_glVertexAttrib2s;
typedef void (APIENTRYP pfn_glVertexAttrib2sv) (GLuint, const GLshort*);
extern pfn_glVertexAttrib2sv fp_glVertexAttrib2sv;
typedef void (APIENTRYP pfn_glVertexAttrib3d) (GLuint, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexAttrib3d fp_glVertexAttrib3d;
typedef void (APIENTRYP pfn_glVertexAttrib3dv) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib3dv fp_glVertexAttrib3dv;
typedef void (APIENTRYP pfn_glVertexAttrib3f) (GLuint, GLfloat, GLfloat, GLfloat);
extern pfn_glVertexAttrib3f fp_glVertexAttrib3f;
typedef void (APIENTRYP pfn_glVertexAttrib3fv) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib3fv fp_glVertexAttrib3fv;
typedef void (APIENTRYP pfn_glVertexAttrib3s) (GLuint, GLshort, GLshort, GLshort);
extern pfn_glVertexAttrib3s fp_glVertexAttrib3s;
typedef void (APIENTRYP pfn_glVertexAttrib3sv) (GLuint, const GLshort*);
extern pfn_glVertexAttrib3sv fp_glVertexAttrib3sv;
typedef void (APIENTRYP pfn_glVertexAttrib4Nbv) (GLuint, const GLbyte*);
extern pfn_glVertexAttrib4Nbv fp_glVertexAttrib4Nbv;
typedef void (APIENTRYP pfn_glVertexAttrib4Niv) (GLuint, const GLint*);
extern pfn_glVertexAttrib4Niv fp_glVertexAttrib4Niv;
typedef void (APIENTRYP pfn_glVertexAttrib4Nsv) (GLuint, const GLshort*);
extern pfn_glVertexAttrib4Nsv fp_glVertexAttrib4Nsv;
typedef void (APIENTRYP pfn_glVertexAttrib4Nub) (GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
extern pfn_glVertexAttrib4Nub fp_glVertexAttrib4Nub;
typedef void (APIENTRYP pfn_glVertexAttrib4Nubv) (GLuint, const GLubyte*);
extern pfn_glVertexAttrib4Nubv fp_glVertexAttrib4Nubv;
typedef void (APIENTRYP pfn_glVertexAttrib4Nuiv) (GLuint, const GLuint*);
extern pfn_glVertexAttrib4Nuiv fp_glVertexAttrib4Nuiv;
typedef void (APIENTRYP pfn_glVertexAttrib4Nusv) (GLuint, const GLushort*);
extern pfn_glVertexAttrib4Nusv fp_glVertexAttrib4Nusv;
typedef void (APIENTRYP pfn_glVertexAttrib4bv) (GLuint, const GLbyte*);
extern pfn_glVertexAttrib4bv fp_glVertexAttrib4bv;
typedef void (APIENTRYP pfn_glVertexAttrib4d) (GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexAttrib4d fp_glVertexAttrib4d;
typedef void (APIENTRYP pfn_glVertexAttrib4dv) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib4dv fp_glVertexAttrib4dv;
typedef void (APIENTRYP pfn_glVertexAttrib4f) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glVertexAttrib4f fp_glVertexAttrib4f;
typedef void (APIENTRYP pfn_glVertexAttrib4fv) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib4fv fp_glVertexAttrib4fv;
typedef void (APIENTRYP pfn_glVertexAttrib4iv) (GLuint, const GLint*);
extern pfn_glVertexAttrib4iv fp_glVertexAttrib4iv;
typedef void (APIENTRYP pfn_glVertexAttrib4s) (GLuint, GLshort, GLshort, GLshort, GLshort);
extern pfn_glVertexAttrib4s fp_glVertexAttrib4s;
typedef void (APIENTRYP pfn_glVertexAttrib4sv) (GLuint, const GLshort*);
extern pfn_glVertexAttrib4sv fp_glVertexAttrib4sv;
typedef void (APIENTRYP pfn_glVertexAttrib4ubv) (GLuint, const GLubyte*);
extern pfn_glVertexAttrib4ubv fp_glVertexAttrib4ubv;
typedef void (APIENTRYP pfn_glVertexAttrib4uiv) (GLuint, const GLuint*);
extern pfn_glVertexAttrib4uiv fp_glVertexAttrib4uiv;
typedef void (APIENTRYP pfn_glVertexAttrib4usv) (GLuint, const GLushort*);
extern pfn_glVertexAttrib4usv fp_glVertexAttrib4usv;
typedef void (APIENTRYP pfn_glVertexAttribPointer) (GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
extern pfn_glVertexAttribPointer fp_glVertexAttribPointer;

 /* GL_VERSION_2_1 */
extern GLboolean GLAD_VERSION_2_1;
#define GL_PIXEL_PACK_BUFFER                   0x88EB
#define GL_PIXEL_UNPACK_BUFFER                 0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING           0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING         0x88EF
#define GL_FLOAT_MAT2x3                        0x8B65
#define GL_FLOAT_MAT2x4                        0x8B66
#define GL_FLOAT_MAT3x2                        0x8B67
#define GL_FLOAT_MAT3x4                        0x8B68
#define GL_FLOAT_MAT4x2                        0x8B69
#define GL_FLOAT_MAT4x3                        0x8B6A
#define GL_SRGB                                0x8C40
#define GL_SRGB8                               0x8C41
#define GL_SRGB_ALPHA                          0x8C42
#define GL_SRGB8_ALPHA8                        0x8C43
#define GL_COMPRESSED_SRGB                     0x8C48
#define GL_COMPRESSED_SRGB_ALPHA               0x8C49
#define GL_CURRENT_RASTER_SECONDARY_COLOR      0x845F
#define GL_SLUMINANCE_ALPHA                    0x8C44
#define GL_SLUMINANCE8_ALPHA8                  0x8C45
#define GL_SLUMINANCE                          0x8C46
#define GL_SLUMINANCE8                         0x8C47
#define GL_COMPRESSED_SLUMINANCE               0x8C4A
#define GL_COMPRESSED_SLUMINANCE_ALPHA         0x8C4B
typedef void (APIENTRYP pfn_glUniformMatrix2x3fv) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix2x3fv fp_glUniformMatrix2x3fv;
typedef void (APIENTRYP pfn_glUniformMatrix3x2fv) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix3x2fv fp_glUniformMatrix3x2fv;
typedef void (APIENTRYP pfn_glUniformMatrix2x4fv) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix2x4fv fp_glUniformMatrix2x4fv;
typedef void (APIENTRYP pfn_glUniformMatrix4x2fv) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix4x2fv fp_glUniformMatrix4x2fv;
typedef void (APIENTRYP pfn_glUniformMatrix3x4fv) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix3x4fv fp_glUniformMatrix3x4fv;
typedef void (APIENTRYP pfn_glUniformMatrix4x3fv) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix4x3fv fp_glUniformMatrix4x3fv;

 /* GL_VERSION_3_0 */
extern GLboolean GLAD_VERSION_3_0;
#define GL_COMPARE_REF_TO_TEXTURE              0x884E
#define GL_CLIP_DISTANCE0                      0x3000
#define GL_CLIP_DISTANCE1                      0x3001
#define GL_CLIP_DISTANCE2                      0x3002
#define GL_CLIP_DISTANCE3                      0x3003
#define GL_CLIP_DISTANCE4                      0x3004
#define GL_CLIP_DISTANCE5                      0x3005
#define GL_CLIP_DISTANCE6                      0x3006
#define GL_CLIP_DISTANCE7                      0x3007
#define GL_MAX_CLIP_DISTANCES                  0x0D32
#define GL_MAJOR_VERSION                       0x821B
#define GL_MINOR_VERSION                       0x821C
#define GL_NUM_EXTENSIONS                      0x821D
#define GL_CONTEXT_FLAGS                       0x821E
#define GL_COMPRESSED_RED                      0x8225
#define GL_COMPRESSED_RG                       0x8226
#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT  0x00000001
#define GL_RGBA32F                             0x8814
#define GL_RGB32F                              0x8815
#define GL_RGBA16F                             0x881A
#define GL_RGB16F                              0x881B
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER         0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS            0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET            0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET            0x8905
#define GL_CLAMP_READ_COLOR                    0x891C
#define GL_FIXED_ONLY                          0x891D
#define GL_MAX_VARYING_COMPONENTS              0x8B4B
#define GL_TEXTURE_1D_ARRAY                    0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY              0x8C19
#define GL_TEXTURE_2D_ARRAY                    0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY              0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY            0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY            0x8C1D
#define GL_R11F_G11F_B10F                      0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV        0x8C3B
#define GL_RGB9_E5                             0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV            0x8C3E
#define GL_TEXTURE_SHARED_SIZE                 0x8C3F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH  0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE      0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS  0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS         0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START     0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE      0x8C85
#define GL_PRIMITIVES_GENERATED                0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN  0x8C88
#define GL_RASTERIZER_DISCARD                  0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS  0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS  0x8C8B
#define GL_INTERLEAVED_ATTRIBS                 0x8C8C
#define GL_SEPARATE_ATTRIBS                    0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER           0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING   0x8C8F
#define GL_RGBA32UI                            0x8D70
#define GL_RGB32UI                             0x8D71
#define GL_RGBA16UI                            0x8D76
#define GL_RGB16UI                             0x8D77
#define GL_RGBA8UI                             0x8D7C
#define GL_RGB8UI                              0x8D7D
#define GL_RGBA32I                             0x8D82
#define GL_RGB32I                              0x8D83
#define GL_RGBA16I                             0x8D88
#define GL_RGB16I                              0x8D89
#define GL_RGBA8I                              0x8D8E
#define GL_RGB8I                               0x8D8F
#define GL_RED_INTEGER                         0x8D94
#define GL_GREEN_INTEGER                       0x8D95
#define GL_BLUE_INTEGER                        0x8D96
#define GL_RGB_INTEGER                         0x8D98
#define GL_RGBA_INTEGER                        0x8D99
#define GL_BGR_INTEGER                         0x8D9A
#define GL_BGRA_INTEGER                        0x8D9B
#define GL_SAMPLER_1D_ARRAY                    0x8DC0
#define GL_SAMPLER_2D_ARRAY                    0x8DC1
#define GL_SAMPLER_1D_ARRAY_SHADOW             0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW             0x8DC4
#define GL_SAMPLER_CUBE_SHADOW                 0x8DC5
#define GL_UNSIGNED_INT_VEC2                   0x8DC6
#define GL_UNSIGNED_INT_VEC3                   0x8DC7
#define GL_UNSIGNED_INT_VEC4                   0x8DC8
#define GL_INT_SAMPLER_1D                      0x8DC9
#define GL_INT_SAMPLER_2D                      0x8DCA
#define GL_INT_SAMPLER_3D                      0x8DCB
#define GL_INT_SAMPLER_CUBE                    0x8DCC
#define GL_INT_SAMPLER_1D_ARRAY                0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY                0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_1D             0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D             0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D             0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE           0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY       0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY       0x8DD7
#define GL_QUERY_WAIT                          0x8E13
#define GL_QUERY_NO_WAIT                       0x8E14
#define GL_QUERY_BY_REGION_WAIT                0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT             0x8E16
#define GL_BUFFER_ACCESS_FLAGS                 0x911F
#define GL_BUFFER_MAP_LENGTH                   0x9120
#define GL_BUFFER_MAP_OFFSET                   0x9121
#define GL_DEPTH_COMPONENT32F                  0x8CAC
#define GL_DEPTH32F_STENCIL8                   0x8CAD
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV      0x8DAD
#define GL_INVALID_FRAMEBUFFER_OPERATION       0x0506
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING  0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE  0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE     0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE   0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE    0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE   0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE   0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE  0x8217
#define GL_FRAMEBUFFER_DEFAULT                 0x8218
#define GL_FRAMEBUFFER_UNDEFINED               0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT            0x821A
#define GL_MAX_RENDERBUFFER_SIZE               0x84E8
#define GL_DEPTH_STENCIL                       0x84F9
#define GL_UNSIGNED_INT_24_8                   0x84FA
#define GL_DEPTH24_STENCIL8                    0x88F0
#define GL_TEXTURE_STENCIL_SIZE                0x88F1
#define GL_TEXTURE_RED_TYPE                    0x8C10
#define GL_TEXTURE_GREEN_TYPE                  0x8C11
#define GL_TEXTURE_BLUE_TYPE                   0x8C12
#define GL_TEXTURE_ALPHA_TYPE                  0x8C13
#define GL_TEXTURE_DEPTH_TYPE                  0x8C16
#define GL_UNSIGNED_NORMALIZED                 0x8C17
#define GL_FRAMEBUFFER_BINDING                 0x8CA6
#define GL_DRAW_FRAMEBUFFER_BINDING            0x8CA6
#define GL_RENDERBUFFER_BINDING                0x8CA7
#define GL_READ_FRAMEBUFFER                    0x8CA8
#define GL_DRAW_FRAMEBUFFER                    0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING            0x8CAA
#define GL_RENDERBUFFER_SAMPLES                0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE  0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME  0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL  0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE  0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER  0x8CD4
#define GL_FRAMEBUFFER_COMPLETE                0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT   0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT  0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER  0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER  0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED             0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS               0x8CDF
#define GL_COLOR_ATTACHMENT0                   0x8CE0
#define GL_COLOR_ATTACHMENT1                   0x8CE1
#define GL_COLOR_ATTACHMENT2                   0x8CE2
#define GL_COLOR_ATTACHMENT3                   0x8CE3
#define GL_COLOR_ATTACHMENT4                   0x8CE4
#define GL_COLOR_ATTACHMENT5                   0x8CE5
#define GL_COLOR_ATTACHMENT6                   0x8CE6
#define GL_COLOR_ATTACHMENT7                   0x8CE7
#define GL_COLOR_ATTACHMENT8                   0x8CE8
#define GL_COLOR_ATTACHMENT9                   0x8CE9
#define GL_COLOR_ATTACHMENT10                  0x8CEA
#define GL_COLOR_ATTACHMENT11                  0x8CEB
#define GL_COLOR_ATTACHMENT12                  0x8CEC
#define GL_COLOR_ATTACHMENT13                  0x8CED
#define GL_COLOR_ATTACHMENT14                  0x8CEE
#define GL_COLOR_ATTACHMENT15                  0x8CEF
#define GL_DEPTH_ATTACHMENT                    0x8D00
#define GL_STENCIL_ATTACHMENT                  0x8D20
#define GL_FRAMEBUFFER                         0x8D40
#define GL_RENDERBUFFER                        0x8D41
#define GL_RENDERBUFFER_WIDTH                  0x8D42
#define GL_RENDERBUFFER_HEIGHT                 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT        0x8D44
#define GL_STENCIL_INDEX1                      0x8D46
#define GL_STENCIL_INDEX4                      0x8D47
#define GL_STENCIL_INDEX8                      0x8D48
#define GL_STENCIL_INDEX16                     0x8D49
#define GL_RENDERBUFFER_RED_SIZE               0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE             0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE              0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE             0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE             0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE           0x8D55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE  0x8D56
#define GL_MAX_SAMPLES                         0x8D57
#define GL_INDEX                               0x8222
#define GL_TEXTURE_LUMINANCE_TYPE              0x8C14
#define GL_TEXTURE_INTENSITY_TYPE              0x8C15
#define GL_FRAMEBUFFER_SRGB                    0x8DB9
#define GL_HALF_FLOAT                          0x140B
#define GL_MAP_READ_BIT                        0x0001
#define GL_MAP_WRITE_BIT                       0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT            0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT           0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT              0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT              0x0020
#define GL_COMPRESSED_RED_RGTC1                0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1         0x8DBC
#define GL_COMPRESSED_RG_RGTC2                 0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2          0x8DBE
#define GL_RG                                  0x8227
#define GL_RG_INTEGER                          0x8228
#define GL_R8                                  0x8229
#define GL_R16                                 0x822A
#define GL_RG8                                 0x822B
#define GL_RG16                                0x822C
#define GL_R16F                                0x822D
#define GL_R32F                                0x822E
#define GL_RG16F                               0x822F
#define GL_RG32F                               0x8230
#define GL_R8I                                 0x8231
#define GL_R8UI                                0x8232
#define GL_R16I                                0x8233
#define GL_R16UI                               0x8234
#define GL_R32I                                0x8235
#define GL_R32UI                               0x8236
#define GL_RG8I                                0x8237
#define GL_RG8UI                               0x8238
#define GL_RG16I                               0x8239
#define GL_RG16UI                              0x823A
#define GL_RG32I                               0x823B
#define GL_RG32UI                              0x823C
#define GL_VERTEX_ARRAY_BINDING                0x85B5
#define GL_CLAMP_VERTEX_COLOR                  0x891A
#define GL_CLAMP_FRAGMENT_COLOR                0x891B
#define GL_ALPHA_INTEGER                       0x8D97
typedef void (APIENTRYP pfn_glColorMaski) (GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
extern pfn_glColorMaski fp_glColorMaski;
typedef void (APIENTRYP pfn_glGetBooleani_v) (GLenum, GLuint, GLboolean*);
extern pfn_glGetBooleani_v fp_glGetBooleani_v;
typedef void (APIENTRYP pfn_glGetIntegeri_v) (GLenum, GLuint, GLint*);
extern pfn_glGetIntegeri_v fp_glGetIntegeri_v;
typedef void (APIENTRYP pfn_glEnablei) (GLenum, GLuint);
extern pfn_glEnablei fp_glEnablei;
typedef void (APIENTRYP pfn_glDisablei) (GLenum, GLuint);
extern pfn_glDisablei fp_glDisablei;
typedef GLboolean (APIENTRYP pfn_glIsEnabledi) (GLenum, GLuint);
extern pfn_glIsEnabledi fp_glIsEnabledi;
typedef void (APIENTRYP pfn_glBeginTransformFeedback) (GLenum);
extern pfn_glBeginTransformFeedback fp_glBeginTransformFeedback;
typedef void (APIENTRYP pfn_glEndTransformFeedback) ();
extern pfn_glEndTransformFeedback fp_glEndTransformFeedback;
typedef void (APIENTRYP pfn_glBindBufferRange) (GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
extern pfn_glBindBufferRange fp_glBindBufferRange;
typedef void (APIENTRYP pfn_glBindBufferBase) (GLenum, GLuint, GLuint);
extern pfn_glBindBufferBase fp_glBindBufferBase;
typedef void (APIENTRYP pfn_glTransformFeedbackVaryings) (GLuint, GLsizei, const GLchar**, GLenum);
extern pfn_glTransformFeedbackVaryings fp_glTransformFeedbackVaryings;
typedef void (APIENTRYP pfn_glGetTransformFeedbackVarying) (GLuint, GLuint, GLsizei, GLsizei*, GLsizei*, GLenum*, GLchar*);
extern pfn_glGetTransformFeedbackVarying fp_glGetTransformFeedbackVarying;
typedef void (APIENTRYP pfn_glClampColor) (GLenum, GLenum);
extern pfn_glClampColor fp_glClampColor;
typedef void (APIENTRYP pfn_glBeginConditionalRender) (GLuint, GLenum);
extern pfn_glBeginConditionalRender fp_glBeginConditionalRender;
typedef void (APIENTRYP pfn_glEndConditionalRender) ();
extern pfn_glEndConditionalRender fp_glEndConditionalRender;
typedef void (APIENTRYP pfn_glVertexAttribIPointer) (GLuint, GLint, GLenum, GLsizei, const void*);
extern pfn_glVertexAttribIPointer fp_glVertexAttribIPointer;
typedef void (APIENTRYP pfn_glGetVertexAttribIiv) (GLuint, GLenum, GLint*);
extern pfn_glGetVertexAttribIiv fp_glGetVertexAttribIiv;
typedef void (APIENTRYP pfn_glGetVertexAttribIuiv) (GLuint, GLenum, GLuint*);
extern pfn_glGetVertexAttribIuiv fp_glGetVertexAttribIuiv;
typedef void (APIENTRYP pfn_glVertexAttribI1i) (GLuint, GLint);
extern pfn_glVertexAttribI1i fp_glVertexAttribI1i;
typedef void (APIENTRYP pfn_glVertexAttribI2i) (GLuint, GLint, GLint);
extern pfn_glVertexAttribI2i fp_glVertexAttribI2i;
typedef void (APIENTRYP pfn_glVertexAttribI3i) (GLuint, GLint, GLint, GLint);
extern pfn_glVertexAttribI3i fp_glVertexAttribI3i;
typedef void (APIENTRYP pfn_glVertexAttribI4i) (GLuint, GLint, GLint, GLint, GLint);
extern pfn_glVertexAttribI4i fp_glVertexAttribI4i;
typedef void (APIENTRYP pfn_glVertexAttribI1ui) (GLuint, GLuint);
extern pfn_glVertexAttribI1ui fp_glVertexAttribI1ui;
typedef void (APIENTRYP pfn_glVertexAttribI2ui) (GLuint, GLuint, GLuint);
extern pfn_glVertexAttribI2ui fp_glVertexAttribI2ui;
typedef void (APIENTRYP pfn_glVertexAttribI3ui) (GLuint, GLuint, GLuint, GLuint);
extern pfn_glVertexAttribI3ui fp_glVertexAttribI3ui;
typedef void (APIENTRYP pfn_glVertexAttribI4ui) (GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glVertexAttribI4ui fp_glVertexAttribI4ui;
typedef void (APIENTRYP pfn_glVertexAttribI1iv) (GLuint, const GLint*);
extern pfn_glVertexAttribI1iv fp_glVertexAttribI1iv;
typedef void (APIENTRYP pfn_glVertexAttribI2iv) (GLuint, const GLint*);
extern pfn_glVertexAttribI2iv fp_glVertexAttribI2iv;
typedef void (APIENTRYP pfn_glVertexAttribI3iv) (GLuint, const GLint*);
extern pfn_glVertexAttribI3iv fp_glVertexAttribI3iv;
typedef void (APIENTRYP pfn_glVertexAttribI4iv) (GLuint, const GLint*);
extern pfn_glVertexAttribI4iv fp_glVertexAttribI4iv;
typedef void (APIENTRYP pfn_glVertexAttribI1uiv) (GLuint, const GLuint*);
extern pfn_glVertexAttribI1uiv fp_glVertexAttribI1uiv;
typedef void (APIENTRYP pfn_glVertexAttribI2uiv) (GLuint, const GLuint*);
extern pfn_glVertexAttribI2uiv fp_glVertexAttribI2uiv;
typedef void (APIENTRYP pfn_glVertexAttribI3uiv) (GLuint, const GLuint*);
extern pfn_glVertexAttribI3uiv fp_glVertexAttribI3uiv;
typedef void (APIENTRYP pfn_glVertexAttribI4uiv) (GLuint, const GLuint*);
extern pfn_glVertexAttribI4uiv fp_glVertexAttribI4uiv;
typedef void (APIENTRYP pfn_glVertexAttribI4bv) (GLuint, const GLbyte*);
extern pfn_glVertexAttribI4bv fp_glVertexAttribI4bv;
typedef void (APIENTRYP pfn_glVertexAttribI4sv) (GLuint, const GLshort*);
extern pfn_glVertexAttribI4sv fp_glVertexAttribI4sv;
typedef void (APIENTRYP pfn_glVertexAttribI4ubv) (GLuint, const GLubyte*);
extern pfn_glVertexAttribI4ubv fp_glVertexAttribI4ubv;
typedef void (APIENTRYP pfn_glVertexAttribI4usv) (GLuint, const GLushort*);
extern pfn_glVertexAttribI4usv fp_glVertexAttribI4usv;
typedef void (APIENTRYP pfn_glGetUniformuiv) (GLuint, GLint, GLuint*);
extern pfn_glGetUniformuiv fp_glGetUniformuiv;
typedef void (APIENTRYP pfn_glBindFragDataLocation) (GLuint, GLuint, const GLchar*);
extern pfn_glBindFragDataLocation fp_glBindFragDataLocation;
typedef GLint (APIENTRYP pfn_glGetFragDataLocation) (GLuint, const GLchar*);
extern pfn_glGetFragDataLocation fp_glGetFragDataLocation;
typedef void (APIENTRYP pfn_glUniform1ui) (GLint, GLuint);
extern pfn_glUniform1ui fp_glUniform1ui;
typedef void (APIENTRYP pfn_glUniform2ui) (GLint, GLuint, GLuint);
extern pfn_glUniform2ui fp_glUniform2ui;
typedef void (APIENTRYP pfn_glUniform3ui) (GLint, GLuint, GLuint, GLuint);
extern pfn_glUniform3ui fp_glUniform3ui;
typedef void (APIENTRYP pfn_glUniform4ui) (GLint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glUniform4ui fp_glUniform4ui;
typedef void (APIENTRYP pfn_glUniform1uiv) (GLint, GLsizei, const GLuint*);
extern pfn_glUniform1uiv fp_glUniform1uiv;
typedef void (APIENTRYP pfn_glUniform2uiv) (GLint, GLsizei, const GLuint*);
extern pfn_glUniform2uiv fp_glUniform2uiv;
typedef void (APIENTRYP pfn_glUniform3uiv) (GLint, GLsizei, const GLuint*);
extern pfn_glUniform3uiv fp_glUniform3uiv;
typedef void (APIENTRYP pfn_glUniform4uiv) (GLint, GLsizei, const GLuint*);
extern pfn_glUniform4uiv fp_glUniform4uiv;
typedef void (APIENTRYP pfn_glTexParameterIiv) (GLenum, GLenum, const GLint*);
extern pfn_glTexParameterIiv fp_glTexParameterIiv;
typedef void (APIENTRYP pfn_glTexParameterIuiv) (GLenum, GLenum, const GLuint*);
extern pfn_glTexParameterIuiv fp_glTexParameterIuiv;
typedef void (APIENTRYP pfn_glGetTexParameterIiv) (GLenum, GLenum, GLint*);
extern pfn_glGetTexParameterIiv fp_glGetTexParameterIiv;
typedef void (APIENTRYP pfn_glGetTexParameterIuiv) (GLenum, GLenum, GLuint*);
extern pfn_glGetTexParameterIuiv fp_glGetTexParameterIuiv;
typedef void (APIENTRYP pfn_glClearBufferiv) (GLenum, GLint, const GLint*);
extern pfn_glClearBufferiv fp_glClearBufferiv;
typedef void (APIENTRYP pfn_glClearBufferuiv) (GLenum, GLint, const GLuint*);
extern pfn_glClearBufferuiv fp_glClearBufferuiv;
typedef void (APIENTRYP pfn_glClearBufferfv) (GLenum, GLint, const GLfloat*);
extern pfn_glClearBufferfv fp_glClearBufferfv;
typedef void (APIENTRYP pfn_glClearBufferfi) (GLenum, GLint, GLfloat, GLint);
extern pfn_glClearBufferfi fp_glClearBufferfi;
typedef const GLubyte* (APIENTRYP pfn_glGetStringi) (GLenum, GLuint);
extern pfn_glGetStringi fp_glGetStringi;
typedef GLboolean (APIENTRYP pfn_glIsRenderbuffer) (GLuint);
extern pfn_glIsRenderbuffer fp_glIsRenderbuffer;
typedef void (APIENTRYP pfn_glBindRenderbuffer) (GLenum, GLuint);
extern pfn_glBindRenderbuffer fp_glBindRenderbuffer;
typedef void (APIENTRYP pfn_glDeleteRenderbuffers) (GLsizei, const GLuint*);
extern pfn_glDeleteRenderbuffers fp_glDeleteRenderbuffers;
typedef void (APIENTRYP pfn_glGenRenderbuffers) (GLsizei, GLuint*);
extern pfn_glGenRenderbuffers fp_glGenRenderbuffers;
typedef void (APIENTRYP pfn_glRenderbufferStorage) (GLenum, GLenum, GLsizei, GLsizei);
extern pfn_glRenderbufferStorage fp_glRenderbufferStorage;
typedef void (APIENTRYP pfn_glGetRenderbufferParameteriv) (GLenum, GLenum, GLint*);
extern pfn_glGetRenderbufferParameteriv fp_glGetRenderbufferParameteriv;
typedef GLboolean (APIENTRYP pfn_glIsFramebuffer) (GLuint);
extern pfn_glIsFramebuffer fp_glIsFramebuffer;
typedef void (APIENTRYP pfn_glBindFramebuffer) (GLenum, GLuint);
extern pfn_glBindFramebuffer fp_glBindFramebuffer;
typedef void (APIENTRYP pfn_glDeleteFramebuffers) (GLsizei, const GLuint*);
extern pfn_glDeleteFramebuffers fp_glDeleteFramebuffers;
typedef void (APIENTRYP pfn_glGenFramebuffers) (GLsizei, GLuint*);
extern pfn_glGenFramebuffers fp_glGenFramebuffers;
typedef GLenum (APIENTRYP pfn_glCheckFramebufferStatus) (GLenum);
extern pfn_glCheckFramebufferStatus fp_glCheckFramebufferStatus;
typedef void (APIENTRYP pfn_glFramebufferTexture1D) (GLenum, GLenum, GLenum, GLuint, GLint);
extern pfn_glFramebufferTexture1D fp_glFramebufferTexture1D;
typedef void (APIENTRYP pfn_glFramebufferTexture2D) (GLenum, GLenum, GLenum, GLuint, GLint);
extern pfn_glFramebufferTexture2D fp_glFramebufferTexture2D;
typedef void (APIENTRYP pfn_glFramebufferTexture3D) (GLenum, GLenum, GLenum, GLuint, GLint, GLint);
extern pfn_glFramebufferTexture3D fp_glFramebufferTexture3D;
typedef void (APIENTRYP pfn_glFramebufferRenderbuffer) (GLenum, GLenum, GLenum, GLuint);
extern pfn_glFramebufferRenderbuffer fp_glFramebufferRenderbuffer;
typedef void (APIENTRYP pfn_glGetFramebufferAttachmentParameteriv) (GLenum, GLenum, GLenum, GLint*);
extern pfn_glGetFramebufferAttachmentParameteriv fp_glGetFramebufferAttachmentParameteriv;
typedef void (APIENTRYP pfn_glGenerateMipmap) (GLenum);
extern pfn_glGenerateMipmap fp_glGenerateMipmap;
typedef void (APIENTRYP pfn_glBlitFramebuffer) (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
extern pfn_glBlitFramebuffer fp_glBlitFramebuffer;
typedef void (APIENTRYP pfn_glRenderbufferStorageMultisample) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glRenderbufferStorageMultisample fp_glRenderbufferStorageMultisample;
typedef void (APIENTRYP pfn_glFramebufferTextureLayer) (GLenum, GLenum, GLuint, GLint, GLint);
extern pfn_glFramebufferTextureLayer fp_glFramebufferTextureLayer;
typedef void* (APIENTRYP pfn_glMapBufferRange) (GLenum, GLintptr, GLsizeiptr, GLbitfield);
extern pfn_glMapBufferRange fp_glMapBufferRange;
typedef void (APIENTRYP pfn_glFlushMappedBufferRange) (GLenum, GLintptr, GLsizeiptr);
extern pfn_glFlushMappedBufferRange fp_glFlushMappedBufferRange;
typedef void (APIENTRYP pfn_glBindVertexArray) (GLuint);
extern pfn_glBindVertexArray fp_glBindVertexArray;
typedef void (APIENTRYP pfn_glDeleteVertexArrays) (GLsizei, const GLuint*);
extern pfn_glDeleteVertexArrays fp_glDeleteVertexArrays;
typedef void (APIENTRYP pfn_glGenVertexArrays) (GLsizei, GLuint*);
extern pfn_glGenVertexArrays fp_glGenVertexArrays;
typedef GLboolean (APIENTRYP pfn_glIsVertexArray) (GLuint);
extern pfn_glIsVertexArray fp_glIsVertexArray;

 /* GL_VERSION_3_1 */
extern GLboolean GLAD_VERSION_3_1;
#define GL_SAMPLER_2D_RECT                     0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW              0x8B64
#define GL_SAMPLER_BUFFER                      0x8DC2
#define GL_INT_SAMPLER_2D_RECT                 0x8DCD
#define GL_INT_SAMPLER_BUFFER                  0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT        0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_BUFFER         0x8DD8
#define GL_TEXTURE_BUFFER                      0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE             0x8C2B
#define GL_TEXTURE_BINDING_BUFFER              0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING   0x8C2D
#define GL_TEXTURE_RECTANGLE                   0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE           0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE             0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE          0x84F8
#define GL_R8_SNORM                            0x8F94
#define GL_RG8_SNORM                           0x8F95
#define GL_RGB8_SNORM                          0x8F96
#define GL_RGBA8_SNORM                         0x8F97
#define GL_R16_SNORM                           0x8F98
#define GL_RG16_SNORM                          0x8F99
#define GL_RGB16_SNORM                         0x8F9A
#define GL_RGBA16_SNORM                        0x8F9B
#define GL_SIGNED_NORMALIZED                   0x8F9C
#define GL_PRIMITIVE_RESTART                   0x8F9D
#define GL_PRIMITIVE_RESTART_INDEX             0x8F9E
#define GL_COPY_READ_BUFFER                    0x8F36
#define GL_COPY_WRITE_BUFFER                   0x8F37
#define GL_UNIFORM_BUFFER                      0x8A11
#define GL_UNIFORM_BUFFER_BINDING              0x8A28
#define GL_UNIFORM_BUFFER_START                0x8A29
#define GL_UNIFORM_BUFFER_SIZE                 0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS           0x8A2B
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS         0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS         0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS         0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE              0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS  0x8A31
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS  0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT     0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH  0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS               0x8A36
#define GL_UNIFORM_TYPE                        0x8A37
#define GL_UNIFORM_SIZE                        0x8A38
#define GL_UNIFORM_NAME_LENGTH                 0x8A39
#define GL_UNIFORM_BLOCK_INDEX                 0x8A3A
#define GL_UNIFORM_OFFSET                      0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE                0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE               0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR                0x8A3E
#define GL_UNIFORM_BLOCK_BINDING               0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE             0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH           0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS       0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES  0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER  0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER  0x8A46
#define GL_INVALID_INDEX                       0xFFFFFFFF
typedef void (APIENTRYP pfn_glDrawArraysInstanced) (GLenum, GLint, GLsizei, GLsizei);
extern pfn_glDrawArraysInstanced fp_glDrawArraysInstanced;
typedef void (APIENTRYP pfn_glDrawElementsInstanced) (GLenum, GLsizei, GLenum, const void*, GLsizei);
extern pfn_glDrawElementsInstanced fp_glDrawElementsInstanced;
typedef void (APIENTRYP pfn_glTexBuffer) (GLenum, GLenum, GLuint);
extern pfn_glTexBuffer fp_glTexBuffer;
typedef void (APIENTRYP pfn_glPrimitiveRestartIndex) (GLuint);
extern pfn_glPrimitiveRestartIndex fp_glPrimitiveRestartIndex;
typedef void (APIENTRYP pfn_glCopyBufferSubData) (GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
extern pfn_glCopyBufferSubData fp_glCopyBufferSubData;
typedef void (APIENTRYP pfn_glGetUniformIndices) (GLuint, GLsizei, const GLchar**, GLuint*);
extern pfn_glGetUniformIndices fp_glGetUniformIndices;
typedef void (APIENTRYP pfn_glGetActiveUniformsiv) (GLuint, GLsizei, const GLuint*, GLenum, GLint*);
extern pfn_glGetActiveUniformsiv fp_glGetActiveUniformsiv;
typedef void (APIENTRYP pfn_glGetActiveUniformName) (GLuint, GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetActiveUniformName fp_glGetActiveUniformName;
typedef GLuint (APIENTRYP pfn_glGetUniformBlockIndex) (GLuint, const GLchar*);
extern pfn_glGetUniformBlockIndex fp_glGetUniformBlockIndex;
typedef void (APIENTRYP pfn_glGetActiveUniformBlockiv) (GLuint, GLuint, GLenum, GLint*);
extern pfn_glGetActiveUniformBlockiv fp_glGetActiveUniformBlockiv;
typedef void (APIENTRYP pfn_glGetActiveUniformBlockName) (GLuint, GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetActiveUniformBlockName fp_glGetActiveUniformBlockName;
typedef void (APIENTRYP pfn_glUniformBlockBinding) (GLuint, GLuint, GLuint);
extern pfn_glUniformBlockBinding fp_glUniformBlockBinding;

 /* GL_VERSION_3_2 */
extern GLboolean GLAD_VERSION_3_2;
#define GL_CONTEXT_CORE_PROFILE_BIT            0x00000001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT   0x00000002
#define GL_LINES_ADJACENCY                     0x000A
#define GL_LINE_STRIP_ADJACENCY                0x000B
#define GL_TRIANGLES_ADJACENCY                 0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY            0x000D
#define GL_PROGRAM_POINT_SIZE                  0x8642
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS    0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED      0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS  0x8DA8
#define GL_GEOMETRY_SHADER                     0x8DD9
#define GL_GEOMETRY_VERTICES_OUT               0x8916
#define GL_GEOMETRY_INPUT_TYPE                 0x8917
#define GL_GEOMETRY_OUTPUT_TYPE                0x8918
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS     0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES        0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS  0x8DE1
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS        0x9122
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS       0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS      0x9124
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS       0x9125
#define GL_CONTEXT_PROFILE_MASK                0x9126
#define GL_DEPTH_CLAMP                         0x864F
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION  0x8E4C
#define GL_FIRST_VERTEX_CONVENTION             0x8E4D
#define GL_LAST_VERTEX_CONVENTION              0x8E4E
#define GL_PROVOKING_VERTEX                    0x8E4F
#define GL_TEXTURE_CUBE_MAP_SEAMLESS           0x884F
#define GL_MAX_SERVER_WAIT_TIMEOUT             0x9111
#define GL_OBJECT_TYPE                         0x9112
#define GL_SYNC_CONDITION                      0x9113
#define GL_SYNC_STATUS                         0x9114
#define GL_SYNC_FLAGS                          0x9115
#define GL_SYNC_FENCE                          0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE          0x9117
#define GL_UNSIGNALED                          0x9118
#define GL_SIGNALED                            0x9119
#define GL_ALREADY_SIGNALED                    0x911A
#define GL_TIMEOUT_EXPIRED                     0x911B
#define GL_CONDITION_SATISFIED                 0x911C
#define GL_WAIT_FAILED                         0x911D
#define GL_TIMEOUT_IGNORED                     0xFFFFFFFFFFFFFFFF
#define GL_SYNC_FLUSH_COMMANDS_BIT             0x00000001
#define GL_SAMPLE_POSITION                     0x8E50
#define GL_SAMPLE_MASK                         0x8E51
#define GL_SAMPLE_MASK_VALUE                   0x8E52
#define GL_MAX_SAMPLE_MASK_WORDS               0x8E59
#define GL_TEXTURE_2D_MULTISAMPLE              0x9100
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE        0x9101
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY        0x9102
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY  0x9103
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE      0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY  0x9105
#define GL_TEXTURE_SAMPLES                     0x9106
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS      0x9107
#define GL_SAMPLER_2D_MULTISAMPLE              0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE          0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE  0x910A
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY        0x910B
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY    0x910C
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY  0x910D
#define GL_MAX_COLOR_TEXTURE_SAMPLES           0x910E
#define GL_MAX_DEPTH_TEXTURE_SAMPLES           0x910F
#define GL_MAX_INTEGER_SAMPLES                 0x9110
typedef void (APIENTRYP pfn_glDrawElementsBaseVertex) (GLenum, GLsizei, GLenum, const void*, GLint);
extern pfn_glDrawElementsBaseVertex fp_glDrawElementsBaseVertex;
typedef void (APIENTRYP pfn_glDrawRangeElementsBaseVertex) (GLenum, GLuint, GLuint, GLsizei, GLenum, const void*, GLint);
extern pfn_glDrawRangeElementsBaseVertex fp_glDrawRangeElementsBaseVertex;
typedef void (APIENTRYP pfn_glDrawElementsInstancedBaseVertex) (GLenum, GLsizei, GLenum, const void*, GLsizei, GLint);
extern pfn_glDrawElementsInstancedBaseVertex fp_glDrawElementsInstancedBaseVertex;
typedef void (APIENTRYP pfn_glMultiDrawElementsBaseVertex) (GLenum, const GLsizei*, GLenum, const void**, GLsizei, const GLint*);
extern pfn_glMultiDrawElementsBaseVertex fp_glMultiDrawElementsBaseVertex;
typedef void (APIENTRYP pfn_glProvokingVertex) (GLenum);
extern pfn_glProvokingVertex fp_glProvokingVertex;
typedef GLsync (APIENTRYP pfn_glFenceSync) (GLenum, GLbitfield);
extern pfn_glFenceSync fp_glFenceSync;
typedef GLboolean (APIENTRYP pfn_glIsSync) (GLsync);
extern pfn_glIsSync fp_glIsSync;
typedef void (APIENTRYP pfn_glDeleteSync) (GLsync);
extern pfn_glDeleteSync fp_glDeleteSync;
typedef GLenum (APIENTRYP pfn_glClientWaitSync) (GLsync, GLbitfield, GLuint64);
extern pfn_glClientWaitSync fp_glClientWaitSync;
typedef void (APIENTRYP pfn_glWaitSync) (GLsync, GLbitfield, GLuint64);
extern pfn_glWaitSync fp_glWaitSync;
typedef void (APIENTRYP pfn_glGetInteger64v) (GLenum, GLint64*);
extern pfn_glGetInteger64v fp_glGetInteger64v;
typedef void (APIENTRYP pfn_glGetSynciv) (GLsync, GLenum, GLsizei, GLsizei*, GLint*);
extern pfn_glGetSynciv fp_glGetSynciv;
typedef void (APIENTRYP pfn_glGetInteger64i_v) (GLenum, GLuint, GLint64*);
extern pfn_glGetInteger64i_v fp_glGetInteger64i_v;
typedef void (APIENTRYP pfn_glGetBufferParameteri64v) (GLenum, GLenum, GLint64*);
extern pfn_glGetBufferParameteri64v fp_glGetBufferParameteri64v;
typedef void (APIENTRYP pfn_glFramebufferTexture) (GLenum, GLenum, GLuint, GLint);
extern pfn_glFramebufferTexture fp_glFramebufferTexture;
typedef void (APIENTRYP pfn_glTexImage2DMultisample) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
extern pfn_glTexImage2DMultisample fp_glTexImage2DMultisample;
typedef void (APIENTRYP pfn_glTexImage3DMultisample) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
extern pfn_glTexImage3DMultisample fp_glTexImage3DMultisample;
typedef void (APIENTRYP pfn_glGetMultisamplefv) (GLenum, GLuint, GLfloat*);
extern pfn_glGetMultisamplefv fp_glGetMultisamplefv;
typedef void (APIENTRYP pfn_glSampleMaski) (GLuint, GLbitfield);
extern pfn_glSampleMaski fp_glSampleMaski;

 /* GL_VERSION_3_3 */
extern GLboolean GLAD_VERSION_3_3;
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR         0x88FE
#define GL_SRC1_COLOR                          0x88F9
#define GL_ONE_MINUS_SRC1_COLOR                0x88FA
#define GL_ONE_MINUS_SRC1_ALPHA                0x88FB
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS        0x88FC
#define GL_ANY_SAMPLES_PASSED                  0x8C2F
#define GL_SAMPLER_BINDING                     0x8919
#define GL_RGB10_A2UI                          0x906F
#define GL_TEXTURE_SWIZZLE_R                   0x8E42
#define GL_TEXTURE_SWIZZLE_G                   0x8E43
#define GL_TEXTURE_SWIZZLE_B                   0x8E44
#define GL_TEXTURE_SWIZZLE_A                   0x8E45
#define GL_TEXTURE_SWIZZLE_RGBA                0x8E46
#define GL_TIME_ELAPSED                        0x88BF
#define GL_TIMESTAMP                           0x8E28
#define GL_INT_2_10_10_10_REV                  0x8D9F
typedef void (APIENTRYP pfn_glBindFragDataLocationIndexed) (GLuint, GLuint, GLuint, const GLchar*);
extern pfn_glBindFragDataLocationIndexed fp_glBindFragDataLocationIndexed;
typedef GLint (APIENTRYP pfn_glGetFragDataIndex) (GLuint, const GLchar*);
extern pfn_glGetFragDataIndex fp_glGetFragDataIndex;
typedef void (APIENTRYP pfn_glGenSamplers) (GLsizei, GLuint*);
extern pfn_glGenSamplers fp_glGenSamplers;
typedef void (APIENTRYP pfn_glDeleteSamplers) (GLsizei, const GLuint*);
extern pfn_glDeleteSamplers fp_glDeleteSamplers;
typedef GLboolean (APIENTRYP pfn_glIsSampler) (GLuint);
extern pfn_glIsSampler fp_glIsSampler;
typedef void (APIENTRYP pfn_glBindSampler) (GLuint, GLuint);
extern pfn_glBindSampler fp_glBindSampler;
typedef void (APIENTRYP pfn_glSamplerParameteri) (GLuint, GLenum, GLint);
extern pfn_glSamplerParameteri fp_glSamplerParameteri;
typedef void (APIENTRYP pfn_glSamplerParameteriv) (GLuint, GLenum, const GLint*);
extern pfn_glSamplerParameteriv fp_glSamplerParameteriv;
typedef void (APIENTRYP pfn_glSamplerParameterf) (GLuint, GLenum, GLfloat);
extern pfn_glSamplerParameterf fp_glSamplerParameterf;
typedef void (APIENTRYP pfn_glSamplerParameterfv) (GLuint, GLenum, const GLfloat*);
extern pfn_glSamplerParameterfv fp_glSamplerParameterfv;
typedef void (APIENTRYP pfn_glSamplerParameterIiv) (GLuint, GLenum, const GLint*);
extern pfn_glSamplerParameterIiv fp_glSamplerParameterIiv;
typedef void (APIENTRYP pfn_glSamplerParameterIuiv) (GLuint, GLenum, const GLuint*);
extern pfn_glSamplerParameterIuiv fp_glSamplerParameterIuiv;
typedef void (APIENTRYP pfn_glGetSamplerParameteriv) (GLuint, GLenum, GLint*);
extern pfn_glGetSamplerParameteriv fp_glGetSamplerParameteriv;
typedef void (APIENTRYP pfn_glGetSamplerParameterIiv) (GLuint, GLenum, GLint*);
extern pfn_glGetSamplerParameterIiv fp_glGetSamplerParameterIiv;
typedef void (APIENTRYP pfn_glGetSamplerParameterfv) (GLuint, GLenum, GLfloat*);
extern pfn_glGetSamplerParameterfv fp_glGetSamplerParameterfv;
typedef void (APIENTRYP pfn_glGetSamplerParameterIuiv) (GLuint, GLenum, GLuint*);
extern pfn_glGetSamplerParameterIuiv fp_glGetSamplerParameterIuiv;
typedef void (APIENTRYP pfn_glQueryCounter) (GLuint, GLenum);
extern pfn_glQueryCounter fp_glQueryCounter;
typedef void (APIENTRYP pfn_glGetQueryObjecti64v) (GLuint, GLenum, GLint64*);
extern pfn_glGetQueryObjecti64v fp_glGetQueryObjecti64v;
typedef void (APIENTRYP pfn_glGetQueryObjectui64v) (GLuint, GLenum, GLuint64*);
extern pfn_glGetQueryObjectui64v fp_glGetQueryObjectui64v;
typedef void (APIENTRYP pfn_glVertexAttribDivisor) (GLuint, GLuint);
extern pfn_glVertexAttribDivisor fp_glVertexAttribDivisor;
typedef void (APIENTRYP pfn_glVertexAttribP1ui) (GLuint, GLenum, GLboolean, GLuint);
extern pfn_glVertexAttribP1ui fp_glVertexAttribP1ui;
typedef void (APIENTRYP pfn_glVertexAttribP1uiv) (GLuint, GLenum, GLboolean, const GLuint*);
extern pfn_glVertexAttribP1uiv fp_glVertexAttribP1uiv;
typedef void (APIENTRYP pfn_glVertexAttribP2ui) (GLuint, GLenum, GLboolean, GLuint);
extern pfn_glVertexAttribP2ui fp_glVertexAttribP2ui;
typedef void (APIENTRYP pfn_glVertexAttribP2uiv) (GLuint, GLenum, GLboolean, const GLuint*);
extern pfn_glVertexAttribP2uiv fp_glVertexAttribP2uiv;
typedef void (APIENTRYP pfn_glVertexAttribP3ui) (GLuint, GLenum, GLboolean, GLuint);
extern pfn_glVertexAttribP3ui fp_glVertexAttribP3ui;
typedef void (APIENTRYP pfn_glVertexAttribP3uiv) (GLuint, GLenum, GLboolean, const GLuint*);
extern pfn_glVertexAttribP3uiv fp_glVertexAttribP3uiv;
typedef void (APIENTRYP pfn_glVertexAttribP4ui) (GLuint, GLenum, GLboolean, GLuint);
extern pfn_glVertexAttribP4ui fp_glVertexAttribP4ui;
typedef void (APIENTRYP pfn_glVertexAttribP4uiv) (GLuint, GLenum, GLboolean, const GLuint*);
extern pfn_glVertexAttribP4uiv fp_glVertexAttribP4uiv;
typedef void (APIENTRYP pfn_glVertexP2ui) (GLenum, GLuint);
extern pfn_glVertexP2ui fp_glVertexP2ui;
typedef void (APIENTRYP pfn_glVertexP2uiv) (GLenum, const GLuint*);
extern pfn_glVertexP2uiv fp_glVertexP2uiv;
typedef void (APIENTRYP pfn_glVertexP3ui) (GLenum, GLuint);
extern pfn_glVertexP3ui fp_glVertexP3ui;
typedef void (APIENTRYP pfn_glVertexP3uiv) (GLenum, const GLuint*);
extern pfn_glVertexP3uiv fp_glVertexP3uiv;
typedef void (APIENTRYP pfn_glVertexP4ui) (GLenum, GLuint);
extern pfn_glVertexP4ui fp_glVertexP4ui;
typedef void (APIENTRYP pfn_glVertexP4uiv) (GLenum, const GLuint*);
extern pfn_glVertexP4uiv fp_glVertexP4uiv;
typedef void (APIENTRYP pfn_glTexCoordP1ui) (GLenum, GLuint);
extern pfn_glTexCoordP1ui fp_glTexCoordP1ui;
typedef void (APIENTRYP pfn_glTexCoordP1uiv) (GLenum, const GLuint*);
extern pfn_glTexCoordP1uiv fp_glTexCoordP1uiv;
typedef void (APIENTRYP pfn_glTexCoordP2ui) (GLenum, GLuint);
extern pfn_glTexCoordP2ui fp_glTexCoordP2ui;
typedef void (APIENTRYP pfn_glTexCoordP2uiv) (GLenum, const GLuint*);
extern pfn_glTexCoordP2uiv fp_glTexCoordP2uiv;
typedef void (APIENTRYP pfn_glTexCoordP3ui) (GLenum, GLuint);
extern pfn_glTexCoordP3ui fp_glTexCoordP3ui;
typedef void (APIENTRYP pfn_glTexCoordP3uiv) (GLenum, const GLuint*);
extern pfn_glTexCoordP3uiv fp_glTexCoordP3uiv;
typedef void (APIENTRYP pfn_glTexCoordP4ui) (GLenum, GLuint);
extern pfn_glTexCoordP4ui fp_glTexCoordP4ui;
typedef void (APIENTRYP pfn_glTexCoordP4uiv) (GLenum, const GLuint*);
extern pfn_glTexCoordP4uiv fp_glTexCoordP4uiv;
typedef void (APIENTRYP pfn_glMultiTexCoordP1ui) (GLenum, GLenum, GLuint);
extern pfn_glMultiTexCoordP1ui fp_glMultiTexCoordP1ui;
typedef void (APIENTRYP pfn_glMultiTexCoordP1uiv) (GLenum, GLenum, const GLuint*);
extern pfn_glMultiTexCoordP1uiv fp_glMultiTexCoordP1uiv;
typedef void (APIENTRYP pfn_glMultiTexCoordP2ui) (GLenum, GLenum, GLuint);
extern pfn_glMultiTexCoordP2ui fp_glMultiTexCoordP2ui;
typedef void (APIENTRYP pfn_glMultiTexCoordP2uiv) (GLenum, GLenum, const GLuint*);
extern pfn_glMultiTexCoordP2uiv fp_glMultiTexCoordP2uiv;
typedef void (APIENTRYP pfn_glMultiTexCoordP3ui) (GLenum, GLenum, GLuint);
extern pfn_glMultiTexCoordP3ui fp_glMultiTexCoordP3ui;
typedef void (APIENTRYP pfn_glMultiTexCoordP3uiv) (GLenum, GLenum, const GLuint*);
extern pfn_glMultiTexCoordP3uiv fp_glMultiTexCoordP3uiv;
typedef void (APIENTRYP pfn_glMultiTexCoordP4ui) (GLenum, GLenum, GLuint);
extern pfn_glMultiTexCoordP4ui fp_glMultiTexCoordP4ui;
typedef void (APIENTRYP pfn_glMultiTexCoordP4uiv) (GLenum, GLenum, const GLuint*);
extern pfn_glMultiTexCoordP4uiv fp_glMultiTexCoordP4uiv;
typedef void (APIENTRYP pfn_glNormalP3ui) (GLenum, GLuint);
extern pfn_glNormalP3ui fp_glNormalP3ui;
typedef void (APIENTRYP pfn_glNormalP3uiv) (GLenum, const GLuint*);
extern pfn_glNormalP3uiv fp_glNormalP3uiv;
typedef void (APIENTRYP pfn_glColorP3ui) (GLenum, GLuint);
extern pfn_glColorP3ui fp_glColorP3ui;
typedef void (APIENTRYP pfn_glColorP3uiv) (GLenum, const GLuint*);
extern pfn_glColorP3uiv fp_glColorP3uiv;
typedef void (APIENTRYP pfn_glColorP4ui) (GLenum, GLuint);
extern pfn_glColorP4ui fp_glColorP4ui;
typedef void (APIENTRYP pfn_glColorP4uiv) (GLenum, const GLuint*);
extern pfn_glColorP4uiv fp_glColorP4uiv;
typedef void (APIENTRYP pfn_glSecondaryColorP3ui) (GLenum, GLuint);
extern pfn_glSecondaryColorP3ui fp_glSecondaryColorP3ui;
typedef void (APIENTRYP pfn_glSecondaryColorP3uiv) (GLenum, const GLuint*);
extern pfn_glSecondaryColorP3uiv fp_glSecondaryColorP3uiv;

 /* GL_VERSION_4_0 */
extern GLboolean GLAD_VERSION_4_0;
#define GL_SAMPLE_SHADING                      0x8C36
#define GL_MIN_SAMPLE_SHADING_VALUE            0x8C37
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET   0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET   0x8E5F
#define GL_TEXTURE_CUBE_MAP_ARRAY              0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY      0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY        0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY              0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW       0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY          0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY  0x900F
#define GL_DRAW_INDIRECT_BUFFER                0x8F3F
#define GL_DRAW_INDIRECT_BUFFER_BINDING        0x8F43
#define GL_GEOMETRY_SHADER_INVOCATIONS         0x887F
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS     0x8E5A
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET   0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET   0x8E5C
#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS  0x8E5D
#define GL_MAX_VERTEX_STREAMS                  0x8E71
#define GL_DOUBLE_VEC2                         0x8FFC
#define GL_DOUBLE_VEC3                         0x8FFD
#define GL_DOUBLE_VEC4                         0x8FFE
#define GL_DOUBLE_MAT2                         0x8F46
#define GL_DOUBLE_MAT3                         0x8F47
#define GL_DOUBLE_MAT4                         0x8F48
#define GL_DOUBLE_MAT2x3                       0x8F49
#define GL_DOUBLE_MAT2x4                       0x8F4A
#define GL_DOUBLE_MAT3x2                       0x8F4B
#define GL_DOUBLE_MAT3x4                       0x8F4C
#define GL_DOUBLE_MAT4x2                       0x8F4D
#define GL_DOUBLE_MAT4x3                       0x8F4E
#define GL_ACTIVE_SUBROUTINES                  0x8DE5
#define GL_ACTIVE_SUBROUTINE_UNIFORMS          0x8DE6
#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS  0x8E47
#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH        0x8E48
#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH  0x8E49
#define GL_MAX_SUBROUTINES                     0x8DE7
#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS    0x8DE8
#define GL_NUM_COMPATIBLE_SUBROUTINES          0x8E4A
#define GL_COMPATIBLE_SUBROUTINES              0x8E4B
#define GL_PATCHES                             0x000E
#define GL_PATCH_VERTICES                      0x8E72
#define GL_PATCH_DEFAULT_INNER_LEVEL           0x8E73
#define GL_PATCH_DEFAULT_OUTER_LEVEL           0x8E74
#define GL_TESS_CONTROL_OUTPUT_VERTICES        0x8E75
#define GL_TESS_GEN_MODE                       0x8E76
#define GL_TESS_GEN_SPACING                    0x8E77
#define GL_TESS_GEN_VERTEX_ORDER               0x8E78
#define GL_TESS_GEN_POINT_MODE                 0x8E79
#define GL_ISOLINES                            0x8E7A
#define GL_FRACTIONAL_ODD                      0x8E7B
#define GL_FRACTIONAL_EVEN                     0x8E7C
#define GL_MAX_PATCH_VERTICES                  0x8E7D
#define GL_MAX_TESS_GEN_LEVEL                  0x8E7E
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS  0x8E7F
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS  0x8E80
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS  0x8E81
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS  0x8E82
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS  0x8E83
#define GL_MAX_TESS_PATCH_COMPONENTS           0x8E84
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS  0x8E85
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS  0x8E86
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS     0x8E89
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS  0x8E8A
#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS   0x886C
#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS  0x886D
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS  0x8E1E
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS  0x8E1F
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER  0x84F0
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER  0x84F1
#define GL_TESS_EVALUATION_SHADER              0x8E87
#define GL_TESS_CONTROL_SHADER                 0x8E88
#define GL_TRANSFORM_FEEDBACK                  0x8E22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED    0x8E23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE    0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING          0x8E25
#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS      0x8E70
typedef void (APIENTRYP pfn_glMinSampleShading) (GLfloat);
extern pfn_glMinSampleShading fp_glMinSampleShading;
typedef void (APIENTRYP pfn_glBlendEquationi) (GLuint, GLenum);
extern pfn_glBlendEquationi fp_glBlendEquationi;
typedef void (APIENTRYP pfn_glBlendEquationSeparatei) (GLuint, GLenum, GLenum);
extern pfn_glBlendEquationSeparatei fp_glBlendEquationSeparatei;
typedef void (APIENTRYP pfn_glBlendFunci) (GLuint, GLenum, GLenum);
extern pfn_glBlendFunci fp_glBlendFunci;
typedef void (APIENTRYP pfn_glBlendFuncSeparatei) (GLuint, GLenum, GLenum, GLenum, GLenum);
extern pfn_glBlendFuncSeparatei fp_glBlendFuncSeparatei;
typedef void (APIENTRYP pfn_glDrawArraysIndirect) (GLenum, const void*);
extern pfn_glDrawArraysIndirect fp_glDrawArraysIndirect;
typedef void (APIENTRYP pfn_glDrawElementsIndirect) (GLenum, GLenum, const void*);
extern pfn_glDrawElementsIndirect fp_glDrawElementsIndirect;
typedef void (APIENTRYP pfn_glUniform1d) (GLint, GLdouble);
extern pfn_glUniform1d fp_glUniform1d;
typedef void (APIENTRYP pfn_glUniform2d) (GLint, GLdouble, GLdouble);
extern pfn_glUniform2d fp_glUniform2d;
typedef void (APIENTRYP pfn_glUniform3d) (GLint, GLdouble, GLdouble, GLdouble);
extern pfn_glUniform3d fp_glUniform3d;
typedef void (APIENTRYP pfn_glUniform4d) (GLint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glUniform4d fp_glUniform4d;
typedef void (APIENTRYP pfn_glUniform1dv) (GLint, GLsizei, const GLdouble*);
extern pfn_glUniform1dv fp_glUniform1dv;
typedef void (APIENTRYP pfn_glUniform2dv) (GLint, GLsizei, const GLdouble*);
extern pfn_glUniform2dv fp_glUniform2dv;
typedef void (APIENTRYP pfn_glUniform3dv) (GLint, GLsizei, const GLdouble*);
extern pfn_glUniform3dv fp_glUniform3dv;
typedef void (APIENTRYP pfn_glUniform4dv) (GLint, GLsizei, const GLdouble*);
extern pfn_glUniform4dv fp_glUniform4dv;
typedef void (APIENTRYP pfn_glUniformMatrix2dv) (GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glUniformMatrix2dv fp_glUniformMatrix2dv;
typedef void (APIENTRYP pfn_glUniformMatrix3dv) (GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glUniformMatrix3dv fp_glUniformMatrix3dv;
typedef void (APIENTRYP pfn_glUniformMatrix4dv) (GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glUniformMatrix4dv fp_glUniformMatrix4dv;
typedef void (APIENTRYP pfn_glUniformMatrix2x3dv) (GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glUniformMatrix2x3dv fp_glUniformMatrix2x3dv;
typedef void (APIENTRYP pfn_glUniformMatrix2x4dv) (GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glUniformMatrix2x4dv fp_glUniformMatrix2x4dv;
typedef void (APIENTRYP pfn_glUniformMatrix3x2dv) (GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glUniformMatrix3x2dv fp_glUniformMatrix3x2dv;
typedef void (APIENTRYP pfn_glUniformMatrix3x4dv) (GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glUniformMatrix3x4dv fp_glUniformMatrix3x4dv;
typedef void (APIENTRYP pfn_glUniformMatrix4x2dv) (GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glUniformMatrix4x2dv fp_glUniformMatrix4x2dv;
typedef void (APIENTRYP pfn_glUniformMatrix4x3dv) (GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glUniformMatrix4x3dv fp_glUniformMatrix4x3dv;
typedef void (APIENTRYP pfn_glGetUniformdv) (GLuint, GLint, GLdouble*);
extern pfn_glGetUniformdv fp_glGetUniformdv;
typedef GLint (APIENTRYP pfn_glGetSubroutineUniformLocation) (GLuint, GLenum, const GLchar*);
extern pfn_glGetSubroutineUniformLocation fp_glGetSubroutineUniformLocation;
typedef GLuint (APIENTRYP pfn_glGetSubroutineIndex) (GLuint, GLenum, const GLchar*);
extern pfn_glGetSubroutineIndex fp_glGetSubroutineIndex;
typedef void (APIENTRYP pfn_glGetActiveSubroutineUniformiv) (GLuint, GLenum, GLuint, GLenum, GLint*);
extern pfn_glGetActiveSubroutineUniformiv fp_glGetActiveSubroutineUniformiv;
typedef void (APIENTRYP pfn_glGetActiveSubroutineUniformName) (GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetActiveSubroutineUniformName fp_glGetActiveSubroutineUniformName;
typedef void (APIENTRYP pfn_glGetActiveSubroutineName) (GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetActiveSubroutineName fp_glGetActiveSubroutineName;
typedef void (APIENTRYP pfn_glUniformSubroutinesuiv) (GLenum, GLsizei, const GLuint*);
extern pfn_glUniformSubroutinesuiv fp_glUniformSubroutinesuiv;
typedef void (APIENTRYP pfn_glGetUniformSubroutineuiv) (GLenum, GLint, GLuint*);
extern pfn_glGetUniformSubroutineuiv fp_glGetUniformSubroutineuiv;
typedef void (APIENTRYP pfn_glGetProgramStageiv) (GLuint, GLenum, GLenum, GLint*);
extern pfn_glGetProgramStageiv fp_glGetProgramStageiv;
typedef void (APIENTRYP pfn_glPatchParameteri) (GLenum, GLint);
extern pfn_glPatchParameteri fp_glPatchParameteri;
typedef void (APIENTRYP pfn_glPatchParameterfv) (GLenum, const GLfloat*);
extern pfn_glPatchParameterfv fp_glPatchParameterfv;
typedef void (APIENTRYP pfn_glBindTransformFeedback) (GLenum, GLuint);
extern pfn_glBindTransformFeedback fp_glBindTransformFeedback;
typedef void (APIENTRYP pfn_glDeleteTransformFeedbacks) (GLsizei, const GLuint*);
extern pfn_glDeleteTransformFeedbacks fp_glDeleteTransformFeedbacks;
typedef void (APIENTRYP pfn_glGenTransformFeedbacks) (GLsizei, GLuint*);
extern pfn_glGenTransformFeedbacks fp_glGenTransformFeedbacks;
typedef GLboolean (APIENTRYP pfn_glIsTransformFeedback) (GLuint);
extern pfn_glIsTransformFeedback fp_glIsTransformFeedback;
typedef void (APIENTRYP pfn_glPauseTransformFeedback) ();
extern pfn_glPauseTransformFeedback fp_glPauseTransformFeedback;
typedef void (APIENTRYP pfn_glResumeTransformFeedback) ();
extern pfn_glResumeTransformFeedback fp_glResumeTransformFeedback;
typedef void (APIENTRYP pfn_glDrawTransformFeedback) (GLenum, GLuint);
extern pfn_glDrawTransformFeedback fp_glDrawTransformFeedback;
typedef void (APIENTRYP pfn_glDrawTransformFeedbackStream) (GLenum, GLuint, GLuint);
extern pfn_glDrawTransformFeedbackStream fp_glDrawTransformFeedbackStream;
typedef void (APIENTRYP pfn_glBeginQueryIndexed) (GLenum, GLuint, GLuint);
extern pfn_glBeginQueryIndexed fp_glBeginQueryIndexed;
typedef void (APIENTRYP pfn_glEndQueryIndexed) (GLenum, GLuint);
extern pfn_glEndQueryIndexed fp_glEndQueryIndexed;
typedef void (APIENTRYP pfn_glGetQueryIndexediv) (GLenum, GLuint, GLenum, GLint*);
extern pfn_glGetQueryIndexediv fp_glGetQueryIndexediv;

 /* GL_VERSION_4_1 */
extern GLboolean GLAD_VERSION_4_1;
#define GL_FIXED                               0x140C
#define GL_IMPLEMENTATION_COLOR_READ_TYPE      0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT    0x8B9B
#define GL_LOW_FLOAT                           0x8DF0
#define GL_MEDIUM_FLOAT                        0x8DF1
#define GL_HIGH_FLOAT                          0x8DF2
#define GL_LOW_INT                             0x8DF3
#define GL_MEDIUM_INT                          0x8DF4
#define GL_HIGH_INT                            0x8DF5
#define GL_SHADER_COMPILER                     0x8DFA
#define GL_SHADER_BINARY_FORMATS               0x8DF8
#define GL_NUM_SHADER_BINARY_FORMATS           0x8DF9
#define GL_MAX_VERTEX_UNIFORM_VECTORS          0x8DFB
#define GL_MAX_VARYING_VECTORS                 0x8DFC
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS        0x8DFD
#define GL_RGB565                              0x8D62
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT     0x8257
#define GL_PROGRAM_BINARY_LENGTH               0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS          0x87FE
#define GL_PROGRAM_BINARY_FORMATS              0x87FF
#define GL_VERTEX_SHADER_BIT                   0x00000001
#define GL_FRAGMENT_SHADER_BIT                 0x00000002
#define GL_GEOMETRY_SHADER_BIT                 0x00000004
#define GL_TESS_CONTROL_SHADER_BIT             0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT          0x00000010
#define GL_ALL_SHADER_BITS                     0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE                   0x8258
#define GL_ACTIVE_PROGRAM                      0x8259
#define GL_PROGRAM_PIPELINE_BINDING            0x825A
#define GL_MAX_VIEWPORTS                       0x825B
#define GL_VIEWPORT_SUBPIXEL_BITS              0x825C
#define GL_VIEWPORT_BOUNDS_RANGE               0x825D
#define GL_LAYER_PROVOKING_VERTEX              0x825E
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX     0x825F
#define GL_UNDEFINED_VERTEX                    0x8260
typedef void (APIENTRYP pfn_glReleaseShaderCompiler) ();
extern pfn_glReleaseShaderCompiler fp_glReleaseShaderCompiler;
typedef void (APIENTRYP pfn_glShaderBinary) (GLsizei, const GLuint*, GLenum, const void*, GLsizei);
extern pfn_glShaderBinary fp_glShaderBinary;
typedef void (APIENTRYP pfn_glGetShaderPrecisionFormat) (GLenum, GLenum, GLint*, GLint*);
extern pfn_glGetShaderPrecisionFormat fp_glGetShaderPrecisionFormat;
typedef void (APIENTRYP pfn_glDepthRangef) (GLfloat, GLfloat);
extern pfn_glDepthRangef fp_glDepthRangef;
typedef void (APIENTRYP pfn_glClearDepthf) (GLfloat);
extern pfn_glClearDepthf fp_glClearDepthf;
typedef void (APIENTRYP pfn_glGetProgramBinary) (GLuint, GLsizei, GLsizei*, GLenum*, void*);
extern pfn_glGetProgramBinary fp_glGetProgramBinary;
typedef void (APIENTRYP pfn_glProgramBinary) (GLuint, GLenum, const void*, GLsizei);
extern pfn_glProgramBinary fp_glProgramBinary;
typedef void (APIENTRYP pfn_glProgramParameteri) (GLuint, GLenum, GLint);
extern pfn_glProgramParameteri fp_glProgramParameteri;
typedef void (APIENTRYP pfn_glUseProgramStages) (GLuint, GLbitfield, GLuint);
extern pfn_glUseProgramStages fp_glUseProgramStages;
typedef void (APIENTRYP pfn_glActiveShaderProgram) (GLuint, GLuint);
extern pfn_glActiveShaderProgram fp_glActiveShaderProgram;
typedef GLuint (APIENTRYP pfn_glCreateShaderProgramv) (GLenum, GLsizei, const GLchar**);
extern pfn_glCreateShaderProgramv fp_glCreateShaderProgramv;
typedef void (APIENTRYP pfn_glBindProgramPipeline) (GLuint);
extern pfn_glBindProgramPipeline fp_glBindProgramPipeline;
typedef void (APIENTRYP pfn_glDeleteProgramPipelines) (GLsizei, const GLuint*);
extern pfn_glDeleteProgramPipelines fp_glDeleteProgramPipelines;
typedef void (APIENTRYP pfn_glGenProgramPipelines) (GLsizei, GLuint*);
extern pfn_glGenProgramPipelines fp_glGenProgramPipelines;
typedef GLboolean (APIENTRYP pfn_glIsProgramPipeline) (GLuint);
extern pfn_glIsProgramPipeline fp_glIsProgramPipeline;
typedef void (APIENTRYP pfn_glGetProgramPipelineiv) (GLuint, GLenum, GLint*);
extern pfn_glGetProgramPipelineiv fp_glGetProgramPipelineiv;
typedef void (APIENTRYP pfn_glProgramUniform1i) (GLuint, GLint, GLint);
extern pfn_glProgramUniform1i fp_glProgramUniform1i;
typedef void (APIENTRYP pfn_glProgramUniform1iv) (GLuint, GLint, GLsizei, const GLint*);
extern pfn_glProgramUniform1iv fp_glProgramUniform1iv;
typedef void (APIENTRYP pfn_glProgramUniform1f) (GLuint, GLint, GLfloat);
extern pfn_glProgramUniform1f fp_glProgramUniform1f;
typedef void (APIENTRYP pfn_glProgramUniform1fv) (GLuint, GLint, GLsizei, const GLfloat*);
extern pfn_glProgramUniform1fv fp_glProgramUniform1fv;
typedef void (APIENTRYP pfn_glProgramUniform1d) (GLuint, GLint, GLdouble);
extern pfn_glProgramUniform1d fp_glProgramUniform1d;
typedef void (APIENTRYP pfn_glProgramUniform1dv) (GLuint, GLint, GLsizei, const GLdouble*);
extern pfn_glProgramUniform1dv fp_glProgramUniform1dv;
typedef void (APIENTRYP pfn_glProgramUniform1ui) (GLuint, GLint, GLuint);
extern pfn_glProgramUniform1ui fp_glProgramUniform1ui;
typedef void (APIENTRYP pfn_glProgramUniform1uiv) (GLuint, GLint, GLsizei, const GLuint*);
extern pfn_glProgramUniform1uiv fp_glProgramUniform1uiv;
typedef void (APIENTRYP pfn_glProgramUniform2i) (GLuint, GLint, GLint, GLint);
extern pfn_glProgramUniform2i fp_glProgramUniform2i;
typedef void (APIENTRYP pfn_glProgramUniform2iv) (GLuint, GLint, GLsizei, const GLint*);
extern pfn_glProgramUniform2iv fp_glProgramUniform2iv;
typedef void (APIENTRYP pfn_glProgramUniform2f) (GLuint, GLint, GLfloat, GLfloat);
extern pfn_glProgramUniform2f fp_glProgramUniform2f;
typedef void (APIENTRYP pfn_glProgramUniform2fv) (GLuint, GLint, GLsizei, const GLfloat*);
extern pfn_glProgramUniform2fv fp_glProgramUniform2fv;
typedef void (APIENTRYP pfn_glProgramUniform2d) (GLuint, GLint, GLdouble, GLdouble);
extern pfn_glProgramUniform2d fp_glProgramUniform2d;
typedef void (APIENTRYP pfn_glProgramUniform2dv) (GLuint, GLint, GLsizei, const GLdouble*);
extern pfn_glProgramUniform2dv fp_glProgramUniform2dv;
typedef void (APIENTRYP pfn_glProgramUniform2ui) (GLuint, GLint, GLuint, GLuint);
extern pfn_glProgramUniform2ui fp_glProgramUniform2ui;
typedef void (APIENTRYP pfn_glProgramUniform2uiv) (GLuint, GLint, GLsizei, const GLuint*);
extern pfn_glProgramUniform2uiv fp_glProgramUniform2uiv;
typedef void (APIENTRYP pfn_glProgramUniform3i) (GLuint, GLint, GLint, GLint, GLint);
extern pfn_glProgramUniform3i fp_glProgramUniform3i;
typedef void (APIENTRYP pfn_glProgramUniform3iv) (GLuint, GLint, GLsizei, const GLint*);
extern pfn_glProgramUniform3iv fp_glProgramUniform3iv;
typedef void (APIENTRYP pfn_glProgramUniform3f) (GLuint, GLint, GLfloat, GLfloat, GLfloat);
extern pfn_glProgramUniform3f fp_glProgramUniform3f;
typedef void (APIENTRYP pfn_glProgramUniform3fv) (GLuint, GLint, GLsizei, const GLfloat*);
extern pfn_glProgramUniform3fv fp_glProgramUniform3fv;
typedef void (APIENTRYP pfn_glProgramUniform3d) (GLuint, GLint, GLdouble, GLdouble, GLdouble);
extern pfn_glProgramUniform3d fp_glProgramUniform3d;
typedef void (APIENTRYP pfn_glProgramUniform3dv) (GLuint, GLint, GLsizei, const GLdouble*);
extern pfn_glProgramUniform3dv fp_glProgramUniform3dv;
typedef void (APIENTRYP pfn_glProgramUniform3ui) (GLuint, GLint, GLuint, GLuint, GLuint);
extern pfn_glProgramUniform3ui fp_glProgramUniform3ui;
typedef void (APIENTRYP pfn_glProgramUniform3uiv) (GLuint, GLint, GLsizei, const GLuint*);
extern pfn_glProgramUniform3uiv fp_glProgramUniform3uiv;
typedef void (APIENTRYP pfn_glProgramUniform4i) (GLuint, GLint, GLint, GLint, GLint, GLint);
extern pfn_glProgramUniform4i fp_glProgramUniform4i;
typedef void (APIENTRYP pfn_glProgramUniform4iv) (GLuint, GLint, GLsizei, const GLint*);
extern pfn_glProgramUniform4iv fp_glProgramUniform4iv;
typedef void (APIENTRYP pfn_glProgramUniform4f) (GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glProgramUniform4f fp_glProgramUniform4f;
typedef void (APIENTRYP pfn_glProgramUniform4fv) (GLuint, GLint, GLsizei, const GLfloat*);
extern pfn_glProgramUniform4fv fp_glProgramUniform4fv;
typedef void (APIENTRYP pfn_glProgramUniform4d) (GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glProgramUniform4d fp_glProgramUniform4d;
typedef void (APIENTRYP pfn_glProgramUniform4dv) (GLuint, GLint, GLsizei, const GLdouble*);
extern pfn_glProgramUniform4dv fp_glProgramUniform4dv;
typedef void (APIENTRYP pfn_glProgramUniform4ui) (GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glProgramUniform4ui fp_glProgramUniform4ui;
typedef void (APIENTRYP pfn_glProgramUniform4uiv) (GLuint, GLint, GLsizei, const GLuint*);
extern pfn_glProgramUniform4uiv fp_glProgramUniform4uiv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2fv) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix2fv fp_glProgramUniformMatrix2fv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3fv) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix3fv fp_glProgramUniformMatrix3fv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4fv) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix4fv fp_glProgramUniformMatrix4fv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2dv) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix2dv fp_glProgramUniformMatrix2dv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3dv) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix3dv fp_glProgramUniformMatrix3dv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4dv) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix4dv fp_glProgramUniformMatrix4dv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2x3fv) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix2x3fv fp_glProgramUniformMatrix2x3fv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3x2fv) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix3x2fv fp_glProgramUniformMatrix3x2fv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2x4fv) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix2x4fv fp_glProgramUniformMatrix2x4fv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4x2fv) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix4x2fv fp_glProgramUniformMatrix4x2fv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3x4fv) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix3x4fv fp_glProgramUniformMatrix3x4fv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4x3fv) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix4x3fv fp_glProgramUniformMatrix4x3fv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2x3dv) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix2x3dv fp_glProgramUniformMatrix2x3dv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3x2dv) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix3x2dv fp_glProgramUniformMatrix3x2dv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2x4dv) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix2x4dv fp_glProgramUniformMatrix2x4dv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4x2dv) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix4x2dv fp_glProgramUniformMatrix4x2dv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3x4dv) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix3x4dv fp_glProgramUniformMatrix3x4dv;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4x3dv) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix4x3dv fp_glProgramUniformMatrix4x3dv;
typedef void (APIENTRYP pfn_glValidateProgramPipeline) (GLuint);
extern pfn_glValidateProgramPipeline fp_glValidateProgramPipeline;
typedef void (APIENTRYP pfn_glGetProgramPipelineInfoLog) (GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetProgramPipelineInfoLog fp_glGetProgramPipelineInfoLog;
typedef void (APIENTRYP pfn_glVertexAttribL1d) (GLuint, GLdouble);
extern pfn_glVertexAttribL1d fp_glVertexAttribL1d;
typedef void (APIENTRYP pfn_glVertexAttribL2d) (GLuint, GLdouble, GLdouble);
extern pfn_glVertexAttribL2d fp_glVertexAttribL2d;
typedef void (APIENTRYP pfn_glVertexAttribL3d) (GLuint, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexAttribL3d fp_glVertexAttribL3d;
typedef void (APIENTRYP pfn_glVertexAttribL4d) (GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexAttribL4d fp_glVertexAttribL4d;
typedef void (APIENTRYP pfn_glVertexAttribL1dv) (GLuint, const GLdouble*);
extern pfn_glVertexAttribL1dv fp_glVertexAttribL1dv;
typedef void (APIENTRYP pfn_glVertexAttribL2dv) (GLuint, const GLdouble*);
extern pfn_glVertexAttribL2dv fp_glVertexAttribL2dv;
typedef void (APIENTRYP pfn_glVertexAttribL3dv) (GLuint, const GLdouble*);
extern pfn_glVertexAttribL3dv fp_glVertexAttribL3dv;
typedef void (APIENTRYP pfn_glVertexAttribL4dv) (GLuint, const GLdouble*);
extern pfn_glVertexAttribL4dv fp_glVertexAttribL4dv;
typedef void (APIENTRYP pfn_glVertexAttribLPointer) (GLuint, GLint, GLenum, GLsizei, const void*);
extern pfn_glVertexAttribLPointer fp_glVertexAttribLPointer;
typedef void (APIENTRYP pfn_glGetVertexAttribLdv) (GLuint, GLenum, GLdouble*);
extern pfn_glGetVertexAttribLdv fp_glGetVertexAttribLdv;
typedef void (APIENTRYP pfn_glViewportArrayv) (GLuint, GLsizei, const GLfloat*);
extern pfn_glViewportArrayv fp_glViewportArrayv;
typedef void (APIENTRYP pfn_glViewportIndexedf) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glViewportIndexedf fp_glViewportIndexedf;
typedef void (APIENTRYP pfn_glViewportIndexedfv) (GLuint, const GLfloat*);
extern pfn_glViewportIndexedfv fp_glViewportIndexedfv;
typedef void (APIENTRYP pfn_glScissorArrayv) (GLuint, GLsizei, const GLint*);
extern pfn_glScissorArrayv fp_glScissorArrayv;
typedef void (APIENTRYP pfn_glScissorIndexed) (GLuint, GLint, GLint, GLsizei, GLsizei);
extern pfn_glScissorIndexed fp_glScissorIndexed;
typedef void (APIENTRYP pfn_glScissorIndexedv) (GLuint, const GLint*);
extern pfn_glScissorIndexedv fp_glScissorIndexedv;
typedef void (APIENTRYP pfn_glDepthRangeArrayv) (GLuint, GLsizei, const GLdouble*);
extern pfn_glDepthRangeArrayv fp_glDepthRangeArrayv;
typedef void (APIENTRYP pfn_glDepthRangeIndexed) (GLuint, GLdouble, GLdouble);
extern pfn_glDepthRangeIndexed fp_glDepthRangeIndexed;
typedef void (APIENTRYP pfn_glGetFloati_v) (GLenum, GLuint, GLfloat*);
extern pfn_glGetFloati_v fp_glGetFloati_v;
typedef void (APIENTRYP pfn_glGetDoublei_v) (GLenum, GLuint, GLdouble*);
extern pfn_glGetDoublei_v fp_glGetDoublei_v;

 /* GL_VERSION_4_2 */
extern GLboolean GLAD_VERSION_4_2;
#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH       0x9127
#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT      0x9128
#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH       0x9129
#define GL_UNPACK_COMPRESSED_BLOCK_SIZE        0x912A
#define GL_PACK_COMPRESSED_BLOCK_WIDTH         0x912B
#define GL_PACK_COMPRESSED_BLOCK_HEIGHT        0x912C
#define GL_PACK_COMPRESSED_BLOCK_DEPTH         0x912D
#define GL_PACK_COMPRESSED_BLOCK_SIZE          0x912E
#define GL_NUM_SAMPLE_COUNTS                   0x9380
#define GL_MIN_MAP_BUFFER_ALIGNMENT            0x90BC
#define GL_ATOMIC_COUNTER_BUFFER               0x92C0
#define GL_ATOMIC_COUNTER_BUFFER_BINDING       0x92C1
#define GL_ATOMIC_COUNTER_BUFFER_START         0x92C2
#define GL_ATOMIC_COUNTER_BUFFER_SIZE          0x92C3
#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE     0x92C4
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS  0x92C5
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES  0x92C6
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER  0x92C7
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER  0x92C8
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER  0x92C9
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER  0x92CA
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER  0x92CB
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS   0x92CC
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS  0x92CD
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS  0x92CE
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS  0x92CF
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS  0x92D0
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS  0x92D1
#define GL_MAX_VERTEX_ATOMIC_COUNTERS          0x92D2
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS    0x92D3
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS  0x92D4
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS        0x92D5
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS        0x92D6
#define GL_MAX_COMBINED_ATOMIC_COUNTERS        0x92D7
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE      0x92D8
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS  0x92DC
#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS       0x92D9
#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX  0x92DA
#define GL_UNSIGNED_INT_ATOMIC_COUNTER         0x92DB
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT     0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT           0x00000002
#define GL_UNIFORM_BARRIER_BIT                 0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT           0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT     0x00000020
#define GL_COMMAND_BARRIER_BIT                 0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT            0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT          0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT           0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT             0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT      0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT          0x00001000
#define GL_ALL_BARRIER_BITS                    0xFFFFFFFF
#define GL_MAX_IMAGE_UNITS                     0x8F38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS  0x8F39
#define GL_IMAGE_BINDING_NAME                  0x8F3A
#define GL_IMAGE_BINDING_LEVEL                 0x8F3B
#define GL_IMAGE_BINDING_LAYERED               0x8F3C
#define GL_IMAGE_BINDING_LAYER                 0x8F3D
#define GL_IMAGE_BINDING_ACCESS                0x8F3E
#define GL_IMAGE_1D                            0x904C
#define GL_IMAGE_2D                            0x904D
#define GL_IMAGE_3D                            0x904E
#define GL_IMAGE_2D_RECT                       0x904F
#define GL_IMAGE_CUBE                          0x9050
#define GL_IMAGE_BUFFER                        0x9051
#define GL_IMAGE_1D_ARRAY                      0x9052
#define GL_IMAGE_2D_ARRAY                      0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY                0x9054
#define GL_IMAGE_2D_MULTISAMPLE                0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY          0x9056
#define GL_INT_IMAGE_1D                        0x9057
#define GL_INT_IMAGE_2D                        0x9058
#define GL_INT_IMAGE_3D                        0x9059
#define GL_INT_IMAGE_2D_RECT                   0x905A
#define GL_INT_IMAGE_CUBE                      0x905B
#define GL_INT_IMAGE_BUFFER                    0x905C
#define GL_INT_IMAGE_1D_ARRAY                  0x905D
#define GL_INT_IMAGE_2D_ARRAY                  0x905E
#define GL_INT_IMAGE_CUBE_MAP_ARRAY            0x905F
#define GL_INT_IMAGE_2D_MULTISAMPLE            0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY      0x9061
#define GL_UNSIGNED_INT_IMAGE_1D               0x9062
#define GL_UNSIGNED_INT_IMAGE_2D               0x9063
#define GL_UNSIGNED_INT_IMAGE_3D               0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT          0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE             0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER           0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY         0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY         0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY   0x906A
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE   0x906B
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY  0x906C
#define GL_MAX_IMAGE_SAMPLES                   0x906D
#define GL_IMAGE_BINDING_FORMAT                0x906E
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE     0x90C7
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE  0x90C8
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS  0x90C9
#define GL_MAX_VERTEX_IMAGE_UNIFORMS           0x90CA
#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS     0x90CB
#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS  0x90CC
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS         0x90CD
#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS         0x90CE
#define GL_MAX_COMBINED_IMAGE_UNIFORMS         0x90CF
#define GL_TEXTURE_IMMUTABLE_FORMAT            0x912F
typedef void (APIENTRYP pfn_glDrawArraysInstancedBaseInstance) (GLenum, GLint, GLsizei, GLsizei, GLuint);
extern pfn_glDrawArraysInstancedBaseInstance fp_glDrawArraysInstancedBaseInstance;
typedef void (APIENTRYP pfn_glDrawElementsInstancedBaseInstance) (GLenum, GLsizei, GLenum, const void*, GLsizei, GLuint);
extern pfn_glDrawElementsInstancedBaseInstance fp_glDrawElementsInstancedBaseInstance;
typedef void (APIENTRYP pfn_glDrawElementsInstancedBaseVertexBaseInstance) (GLenum, GLsizei, GLenum, const void*, GLsizei, GLint, GLuint);
extern pfn_glDrawElementsInstancedBaseVertexBaseInstance fp_glDrawElementsInstancedBaseVertexBaseInstance;
typedef void (APIENTRYP pfn_glGetInternalformativ) (GLenum, GLenum, GLenum, GLsizei, GLint*);
extern pfn_glGetInternalformativ fp_glGetInternalformativ;
typedef void (APIENTRYP pfn_glGetActiveAtomicCounterBufferiv) (GLuint, GLuint, GLenum, GLint*);
extern pfn_glGetActiveAtomicCounterBufferiv fp_glGetActiveAtomicCounterBufferiv;
typedef void (APIENTRYP pfn_glBindImageTexture) (GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
extern pfn_glBindImageTexture fp_glBindImageTexture;
typedef void (APIENTRYP pfn_glMemoryBarrier) (GLbitfield);
extern pfn_glMemoryBarrier fp_glMemoryBarrier;
typedef void (APIENTRYP pfn_glTexStorage1D) (GLenum, GLsizei, GLenum, GLsizei);
extern pfn_glTexStorage1D fp_glTexStorage1D;
typedef void (APIENTRYP pfn_glTexStorage2D) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glTexStorage2D fp_glTexStorage2D;
typedef void (APIENTRYP pfn_glTexStorage3D) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
extern pfn_glTexStorage3D fp_glTexStorage3D;
typedef void (APIENTRYP pfn_glDrawTransformFeedbackInstanced) (GLenum, GLuint, GLsizei);
extern pfn_glDrawTransformFeedbackInstanced fp_glDrawTransformFeedbackInstanced;
typedef void (APIENTRYP pfn_glDrawTransformFeedbackStreamInstanced) (GLenum, GLuint, GLuint, GLsizei);
extern pfn_glDrawTransformFeedbackStreamInstanced fp_glDrawTransformFeedbackStreamInstanced;

 /* GL_VERSION_4_3 */
extern GLboolean GLAD_VERSION_4_3;
#define GL_NUM_SHADING_LANGUAGE_VERSIONS       0x82E9
#define GL_VERTEX_ATTRIB_ARRAY_LONG            0x874E
#define GL_COMPRESSED_RGB8_ETC2                0x9274
#define GL_COMPRESSED_SRGB8_ETC2               0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2  0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2  0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC           0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC    0x9279
#define GL_COMPRESSED_R11_EAC                  0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC           0x9271
#define GL_COMPRESSED_RG11_EAC                 0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC          0x9273
#define GL_PRIMITIVE_RESTART_FIXED_INDEX       0x8D69
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE     0x8D6A
#define GL_MAX_ELEMENT_INDEX                   0x8D6B
#define GL_COMPUTE_SHADER                      0x91B9
#define GL_MAX_COMPUTE_UNIFORM_BLOCKS          0x91BB
#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS     0x91BC
#define GL_MAX_COMPUTE_IMAGE_UNIFORMS          0x91BD
#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE      0x8262
#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS      0x8263
#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS  0x8264
#define GL_MAX_COMPUTE_ATOMIC_COUNTERS         0x8265
#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS  0x8266
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS  0x90EB
#define GL_MAX_COMPUTE_WORK_GROUP_COUNT        0x91BE
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE         0x91BF
#define GL_COMPUTE_WORK_GROUP_SIZE             0x8267
#define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER  0x90EC
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER  0x90ED
#define GL_DISPATCH_INDIRECT_BUFFER            0x90EE
#define GL_DISPATCH_INDIRECT_BUFFER_BINDING    0x90EF
#define GL_DEBUG_OUTPUT_SYNCHRONOUS            0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH    0x8243
#define GL_DEBUG_CALLBACK_FUNCTION             0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM           0x8245
#define GL_DEBUG_SOURCE_API                    0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM          0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER        0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY            0x8249
#define GL_DEBUG_SOURCE_APPLICATION            0x824A
#define GL_DEBUG_SOURCE_OTHER                  0x824B
#define GL_DEBUG_TYPE_ERROR                    0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR      0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR       0x824E
#define GL_DEBUG_TYPE_PORTABILITY              0x824F
#define GL_DEBUG_TYPE_PERFORMANCE              0x8250
#define GL_DEBUG_TYPE_OTHER                    0x8251
#define GL_MAX_DEBUG_MESSAGE_LENGTH            0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES           0x9144
#define GL_DEBUG_LOGGED_MESSAGES               0x9145
#define GL_DEBUG_SEVERITY_HIGH                 0x9146
#define GL_DEBUG_SEVERITY_MEDIUM               0x9147
#define GL_DEBUG_SEVERITY_LOW                  0x9148
#define GL_DEBUG_TYPE_MARKER                   0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP               0x8269
#define GL_DEBUG_TYPE_POP_GROUP                0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION         0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH         0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH             0x826D
#define GL_BUFFER                              0x82E0
#define GL_SHADER                              0x82E1
#define GL_PROGRAM                             0x82E2
#define GL_QUERY                               0x82E3
#define GL_PROGRAM_PIPELINE                    0x82E4
#define GL_SAMPLER                             0x82E6
#define GL_MAX_LABEL_LENGTH                    0x82E8
#define GL_DEBUG_OUTPUT                        0x92E0
#define GL_CONTEXT_FLAG_DEBUG_BIT              0x00000002
#define GL_MAX_UNIFORM_LOCATIONS               0x826E
#define GL_FRAMEBUFFER_DEFAULT_WIDTH           0x9310
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT          0x9311
#define GL_FRAMEBUFFER_DEFAULT_LAYERS          0x9312
#define GL_FRAMEBUFFER_DEFAULT_SAMPLES         0x9313
#define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS  0x9314
#define GL_MAX_FRAMEBUFFER_WIDTH               0x9315
#define GL_MAX_FRAMEBUFFER_HEIGHT              0x9316
#define GL_MAX_FRAMEBUFFER_LAYERS              0x9317
#define GL_MAX_FRAMEBUFFER_SAMPLES             0x9318
#define GL_INTERNALFORMAT_SUPPORTED            0x826F
#define GL_INTERNALFORMAT_PREFERRED            0x8270
#define GL_INTERNALFORMAT_RED_SIZE             0x8271
#define GL_INTERNALFORMAT_GREEN_SIZE           0x8272
#define GL_INTERNALFORMAT_BLUE_SIZE            0x8273
#define GL_INTERNALFORMAT_ALPHA_SIZE           0x8274
#define GL_INTERNALFORMAT_DEPTH_SIZE           0x8275
#define GL_INTERNALFORMAT_STENCIL_SIZE         0x8276
#define GL_INTERNALFORMAT_SHARED_SIZE          0x8277
#define GL_INTERNALFORMAT_RED_TYPE             0x8278
#define GL_INTERNALFORMAT_GREEN_TYPE           0x8279
#define GL_INTERNALFORMAT_BLUE_TYPE            0x827A
#define GL_INTERNALFORMAT_ALPHA_TYPE           0x827B
#define GL_INTERNALFORMAT_DEPTH_TYPE           0x827C
#define GL_INTERNALFORMAT_STENCIL_TYPE         0x827D
#define GL_MAX_WIDTH                           0x827E
#define GL_MAX_HEIGHT                          0x827F
#define GL_MAX_DEPTH                           0x8280
#define GL_MAX_LAYERS                          0x8281
#define GL_MAX_COMBINED_DIMENSIONS             0x8282
#define GL_COLOR_COMPONENTS                    0x8283
#define GL_DEPTH_COMPONENTS                    0x8284
#define GL_STENCIL_COMPONENTS                  0x8285
#define GL_COLOR_RENDERABLE                    0x8286
#define GL_DEPTH_RENDERABLE                    0x8287
#define GL_STENCIL_RENDERABLE                  0x8288
#define GL_FRAMEBUFFER_RENDERABLE              0x8289
#define GL_FRAMEBUFFER_RENDERABLE_LAYERED      0x828A
#define GL_FRAMEBUFFER_BLEND                   0x828B
#define GL_READ_PIXELS                         0x828C
#define GL_READ_PIXELS_FORMAT                  0x828D
#define GL_READ_PIXELS_TYPE                    0x828E
#define GL_TEXTURE_IMAGE_FORMAT                0x828F
#define GL_TEXTURE_IMAGE_TYPE                  0x8290
#define GL_GET_TEXTURE_IMAGE_FORMAT            0x8291
#define GL_GET_TEXTURE_IMAGE_TYPE              0x8292
#define GL_MIPMAP                              0x8293
#define GL_MANUAL_GENERATE_MIPMAP              0x8294
#define GL_AUTO_GENERATE_MIPMAP                0x8295
#define GL_COLOR_ENCODING                      0x8296
#define GL_SRGB_READ                           0x8297
#define GL_SRGB_WRITE                          0x8298
#define GL_FILTER                              0x829A
#define GL_VERTEX_TEXTURE                      0x829B
#define GL_TESS_CONTROL_TEXTURE                0x829C
#define GL_TESS_EVALUATION_TEXTURE             0x829D
#define GL_GEOMETRY_TEXTURE                    0x829E
#define GL_FRAGMENT_TEXTURE                    0x829F
#define GL_COMPUTE_TEXTURE                     0x82A0
#define GL_TEXTURE_SHADOW                      0x82A1
#define GL_TEXTURE_GATHER                      0x82A2
#define GL_TEXTURE_GATHER_SHADOW               0x82A3
#define GL_SHADER_IMAGE_LOAD                   0x82A4
#define GL_SHADER_IMAGE_STORE                  0x82A5
#define GL_SHADER_IMAGE_ATOMIC                 0x82A6
#define GL_IMAGE_TEXEL_SIZE                    0x82A7
#define GL_IMAGE_COMPATIBILITY_CLASS           0x82A8
#define GL_IMAGE_PIXEL_FORMAT                  0x82A9
#define GL_IMAGE_PIXEL_TYPE                    0x82AA
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST  0x82AC
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST  0x82AD
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE  0x82AE
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE  0x82AF
#define GL_TEXTURE_COMPRESSED_BLOCK_WIDTH      0x82B1
#define GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT     0x82B2
#define GL_TEXTURE_COMPRESSED_BLOCK_SIZE       0x82B3
#define GL_CLEAR_BUFFER                        0x82B4
#define GL_TEXTURE_VIEW                        0x82B5
#define GL_VIEW_COMPATIBILITY_CLASS            0x82B6
#define GL_FULL_SUPPORT                        0x82B7
#define GL_CAVEAT_SUPPORT                      0x82B8
#define GL_IMAGE_CLASS_4_X_32                  0x82B9
#define GL_IMAGE_CLASS_2_X_32                  0x82BA
#define GL_IMAGE_CLASS_1_X_32                  0x82BB
#define GL_IMAGE_CLASS_4_X_16                  0x82BC
#define GL_IMAGE_CLASS_2_X_16                  0x82BD
#define GL_IMAGE_CLASS_1_X_16                  0x82BE
#define GL_IMAGE_CLASS_4_X_8                   0x82BF
#define GL_IMAGE_CLASS_2_X_8                   0x82C0
#define GL_IMAGE_CLASS_1_X_8                   0x82C1
#define GL_IMAGE_CLASS_11_11_10                0x82C2
#define GL_IMAGE_CLASS_10_10_10_2              0x82C3
#define GL_VIEW_CLASS_128_BITS                 0x82C4
#define GL_VIEW_CLASS_96_BITS                  0x82C5
#define GL_VIEW_CLASS_64_BITS                  0x82C6
#define GL_VIEW_CLASS_48_BITS                  0x82C7
#define GL_VIEW_CLASS_32_BITS                  0x82C8
#define GL_VIEW_CLASS_24_BITS                  0x82C9
#define GL_VIEW_CLASS_16_BITS                  0x82CA
#define GL_VIEW_CLASS_8_BITS                   0x82CB
#define GL_VIEW_CLASS_S3TC_DXT1_RGB            0x82CC
#define GL_VIEW_CLASS_S3TC_DXT1_RGBA           0x82CD
#define GL_VIEW_CLASS_S3TC_DXT3_RGBA           0x82CE
#define GL_VIEW_CLASS_S3TC_DXT5_RGBA           0x82CF
#define GL_VIEW_CLASS_RGTC1_RED                0x82D0
#define GL_VIEW_CLASS_RGTC2_RG                 0x82D1
#define GL_VIEW_CLASS_BPTC_UNORM               0x82D2
#define GL_VIEW_CLASS_BPTC_FLOAT               0x82D3
#define GL_UNIFORM                             0x92E1
#define GL_UNIFORM_BLOCK                       0x92E2
#define GL_PROGRAM_INPUT                       0x92E3
#define GL_PROGRAM_OUTPUT                      0x92E4
#define GL_BUFFER_VARIABLE                     0x92E5
#define GL_SHADER_STORAGE_BLOCK                0x92E6
#define GL_VERTEX_SUBROUTINE                   0x92E8
#define GL_TESS_CONTROL_SUBROUTINE             0x92E9
#define GL_TESS_EVALUATION_SUBROUTINE          0x92EA
#define GL_GEOMETRY_SUBROUTINE                 0x92EB
#define GL_FRAGMENT_SUBROUTINE                 0x92EC
#define GL_COMPUTE_SUBROUTINE                  0x92ED
#define GL_VERTEX_SUBROUTINE_UNIFORM           0x92EE
#define GL_TESS_CONTROL_SUBROUTINE_UNIFORM     0x92EF
#define GL_TESS_EVALUATION_SUBROUTINE_UNIFORM  0x92F0
#define GL_GEOMETRY_SUBROUTINE_UNIFORM         0x92F1
#define GL_FRAGMENT_SUBROUTINE_UNIFORM         0x92F2
#define GL_COMPUTE_SUBROUTINE_UNIFORM          0x92F3
#define GL_TRANSFORM_FEEDBACK_VARYING          0x92F4
#define GL_ACTIVE_RESOURCES                    0x92F5
#define GL_MAX_NAME_LENGTH                     0x92F6
#define GL_MAX_NUM_ACTIVE_VARIABLES            0x92F7
#define GL_MAX_NUM_COMPATIBLE_SUBROUTINES      0x92F8
#define GL_NAME_LENGTH                         0x92F9
#define GL_TYPE                                0x92FA
#define GL_ARRAY_SIZE                          0x92FB
#define GL_OFFSET                              0x92FC
#define GL_BLOCK_INDEX                         0x92FD
#define GL_ARRAY_STRIDE                        0x92FE
#define GL_MATRIX_STRIDE                       0x92FF
#define GL_IS_ROW_MAJOR                        0x9300
#define GL_ATOMIC_COUNTER_BUFFER_INDEX         0x9301
#define GL_BUFFER_BINDING                      0x9302
#define GL_BUFFER_DATA_SIZE                    0x9303
#define GL_NUM_ACTIVE_VARIABLES                0x9304
#define GL_ACTIVE_VARIABLES                    0x9305
#define GL_REFERENCED_BY_VERTEX_SHADER         0x9306
#define GL_REFERENCED_BY_TESS_CONTROL_SHADER   0x9307
#define GL_REFERENCED_BY_TESS_EVALUATION_SHADER  0x9308
#define GL_REFERENCED_BY_GEOMETRY_SHADER       0x9309
#define GL_REFERENCED_BY_FRAGMENT_SHADER       0x930A
#define GL_REFERENCED_BY_COMPUTE_SHADER        0x930B
#define GL_TOP_LEVEL_ARRAY_SIZE                0x930C
#define GL_TOP_LEVEL_ARRAY_STRIDE              0x930D
#define GL_LOCATION                            0x930E
#define GL_LOCATION_INDEX                      0x930F
#define GL_IS_PER_PATCH                        0x92E7
#define GL_SHADER_STORAGE_BUFFER               0x90D2
#define GL_SHADER_STORAGE_BUFFER_BINDING       0x90D3
#define GL_SHADER_STORAGE_BUFFER_START         0x90D4
#define GL_SHADER_STORAGE_BUFFER_SIZE          0x90D5
#define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS    0x90D6
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS  0x90D7
#define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS  0x90D8
#define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS  0x90D9
#define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS  0x90DA
#define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS   0x90DB
#define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS  0x90DC
#define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS  0x90DD
#define GL_MAX_SHADER_STORAGE_BLOCK_SIZE       0x90DE
#define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT  0x90DF
#define GL_SHADER_STORAGE_BARRIER_BIT          0x00002000
#define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES  0x8F39
#define GL_DEPTH_STENCIL_TEXTURE_MODE          0x90EA
#define GL_TEXTURE_BUFFER_OFFSET               0x919D
#define GL_TEXTURE_BUFFER_SIZE                 0x919E
#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT     0x919F
#define GL_TEXTURE_VIEW_MIN_LEVEL              0x82DB
#define GL_TEXTURE_VIEW_NUM_LEVELS             0x82DC
#define GL_TEXTURE_VIEW_MIN_LAYER              0x82DD
#define GL_TEXTURE_VIEW_NUM_LAYERS             0x82DE
#define GL_TEXTURE_IMMUTABLE_LEVELS            0x82DF
#define GL_VERTEX_ATTRIB_BINDING               0x82D4
#define GL_VERTEX_ATTRIB_RELATIVE_OFFSET       0x82D5
#define GL_VERTEX_BINDING_DIVISOR              0x82D6
#define GL_VERTEX_BINDING_OFFSET               0x82D7
#define GL_VERTEX_BINDING_STRIDE               0x82D8
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET   0x82D9
#define GL_MAX_VERTEX_ATTRIB_BINDINGS          0x82DA
#define GL_DISPLAY_LIST                        0x82E7
typedef void (APIENTRYP pfn_glClearBufferData) (GLenum, GLenum, GLenum, GLenum, const void*);
extern pfn_glClearBufferData fp_glClearBufferData;
typedef void (APIENTRYP pfn_glClearBufferSubData) (GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void*);
extern pfn_glClearBufferSubData fp_glClearBufferSubData;
typedef void (APIENTRYP pfn_glDispatchCompute) (GLuint, GLuint, GLuint);
extern pfn_glDispatchCompute fp_glDispatchCompute;
typedef void (APIENTRYP pfn_glDispatchComputeIndirect) (GLintptr);
extern pfn_glDispatchComputeIndirect fp_glDispatchComputeIndirect;
typedef void (APIENTRYP pfn_glCopyImageSubData) (GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
extern pfn_glCopyImageSubData fp_glCopyImageSubData;
typedef void (APIENTRYP pfn_glFramebufferParameteri) (GLenum, GLenum, GLint);
extern pfn_glFramebufferParameteri fp_glFramebufferParameteri;
typedef void (APIENTRYP pfn_glGetFramebufferParameteriv) (GLenum, GLenum, GLint*);
extern pfn_glGetFramebufferParameteriv fp_glGetFramebufferParameteriv;
typedef void (APIENTRYP pfn_glGetInternalformati64v) (GLenum, GLenum, GLenum, GLsizei, GLint64*);
extern pfn_glGetInternalformati64v fp_glGetInternalformati64v;
typedef void (APIENTRYP pfn_glInvalidateTexSubImage) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
extern pfn_glInvalidateTexSubImage fp_glInvalidateTexSubImage;
typedef void (APIENTRYP pfn_glInvalidateTexImage) (GLuint, GLint);
extern pfn_glInvalidateTexImage fp_glInvalidateTexImage;
typedef void (APIENTRYP pfn_glInvalidateBufferSubData) (GLuint, GLintptr, GLsizeiptr);
extern pfn_glInvalidateBufferSubData fp_glInvalidateBufferSubData;
typedef void (APIENTRYP pfn_glInvalidateBufferData) (GLuint);
extern pfn_glInvalidateBufferData fp_glInvalidateBufferData;
typedef void (APIENTRYP pfn_glInvalidateFramebuffer) (GLenum, GLsizei, const GLenum*);
extern pfn_glInvalidateFramebuffer fp_glInvalidateFramebuffer;
typedef void (APIENTRYP pfn_glInvalidateSubFramebuffer) (GLenum, GLsizei, const GLenum*, GLint, GLint, GLsizei, GLsizei);
extern pfn_glInvalidateSubFramebuffer fp_glInvalidateSubFramebuffer;
typedef void (APIENTRYP pfn_glMultiDrawArraysIndirect) (GLenum, const void*, GLsizei, GLsizei);
extern pfn_glMultiDrawArraysIndirect fp_glMultiDrawArraysIndirect;
typedef void (APIENTRYP pfn_glMultiDrawElementsIndirect) (GLenum, GLenum, const void*, GLsizei, GLsizei);
extern pfn_glMultiDrawElementsIndirect fp_glMultiDrawElementsIndirect;
typedef void (APIENTRYP pfn_glGetProgramInterfaceiv) (GLuint, GLenum, GLenum, GLint*);
extern pfn_glGetProgramInterfaceiv fp_glGetProgramInterfaceiv;
typedef GLuint (APIENTRYP pfn_glGetProgramResourceIndex) (GLuint, GLenum, const GLchar*);
extern pfn_glGetProgramResourceIndex fp_glGetProgramResourceIndex;
typedef void (APIENTRYP pfn_glGetProgramResourceName) (GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetProgramResourceName fp_glGetProgramResourceName;
typedef void (APIENTRYP pfn_glGetProgramResourceiv) (GLuint, GLenum, GLuint, GLsizei, const GLenum*, GLsizei, GLsizei*, GLint*);
extern pfn_glGetProgramResourceiv fp_glGetProgramResourceiv;
typedef GLint (APIENTRYP pfn_glGetProgramResourceLocation) (GLuint, GLenum, const GLchar*);
extern pfn_glGetProgramResourceLocation fp_glGetProgramResourceLocation;
typedef GLint (APIENTRYP pfn_glGetProgramResourceLocationIndex) (GLuint, GLenum, const GLchar*);
extern pfn_glGetProgramResourceLocationIndex fp_glGetProgramResourceLocationIndex;
typedef void (APIENTRYP pfn_glShaderStorageBlockBinding) (GLuint, GLuint, GLuint);
extern pfn_glShaderStorageBlockBinding fp_glShaderStorageBlockBinding;
typedef void (APIENTRYP pfn_glTexBufferRange) (GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
extern pfn_glTexBufferRange fp_glTexBufferRange;
typedef void (APIENTRYP pfn_glTexStorage2DMultisample) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
extern pfn_glTexStorage2DMultisample fp_glTexStorage2DMultisample;
typedef void (APIENTRYP pfn_glTexStorage3DMultisample) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
extern pfn_glTexStorage3DMultisample fp_glTexStorage3DMultisample;
typedef void (APIENTRYP pfn_glTextureView) (GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
extern pfn_glTextureView fp_glTextureView;
typedef void (APIENTRYP pfn_glBindVertexBuffer) (GLuint, GLuint, GLintptr, GLsizei);
extern pfn_glBindVertexBuffer fp_glBindVertexBuffer;
typedef void (APIENTRYP pfn_glVertexAttribFormat) (GLuint, GLint, GLenum, GLboolean, GLuint);
extern pfn_glVertexAttribFormat fp_glVertexAttribFormat;
typedef void (APIENTRYP pfn_glVertexAttribIFormat) (GLuint, GLint, GLenum, GLuint);
extern pfn_glVertexAttribIFormat fp_glVertexAttribIFormat;
typedef void (APIENTRYP pfn_glVertexAttribLFormat) (GLuint, GLint, GLenum, GLuint);
extern pfn_glVertexAttribLFormat fp_glVertexAttribLFormat;
typedef void (APIENTRYP pfn_glVertexAttribBinding) (GLuint, GLuint);
extern pfn_glVertexAttribBinding fp_glVertexAttribBinding;
typedef void (APIENTRYP pfn_glVertexBindingDivisor) (GLuint, GLuint);
extern pfn_glVertexBindingDivisor fp_glVertexBindingDivisor;
typedef void (APIENTRYP pfn_glDebugMessageControl) (GLenum, GLenum, GLenum, GLsizei, const GLuint*, GLboolean);
extern pfn_glDebugMessageControl fp_glDebugMessageControl;
typedef void (APIENTRYP pfn_glDebugMessageInsert) (GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*);
extern pfn_glDebugMessageInsert fp_glDebugMessageInsert;
typedef void (APIENTRYP pfn_glDebugMessageCallback) (GLDEBUGPROC, const void*);
extern pfn_glDebugMessageCallback fp_glDebugMessageCallback;
typedef GLuint (APIENTRYP pfn_glGetDebugMessageLog) (GLuint, GLsizei, GLenum*, GLenum*, GLuint*, GLenum*, GLsizei*, GLchar*);
extern pfn_glGetDebugMessageLog fp_glGetDebugMessageLog;
typedef void (APIENTRYP pfn_glPushDebugGroup) (GLenum, GLuint, GLsizei, const GLchar*);
extern pfn_glPushDebugGroup fp_glPushDebugGroup;
typedef void (APIENTRYP pfn_glPopDebugGroup) ();
extern pfn_glPopDebugGroup fp_glPopDebugGroup;
typedef void (APIENTRYP pfn_glObjectLabel) (GLenum, GLuint, GLsizei, const GLchar*);
extern pfn_glObjectLabel fp_glObjectLabel;
typedef void (APIENTRYP pfn_glGetObjectLabel) (GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetObjectLabel fp_glGetObjectLabel;
typedef void (APIENTRYP pfn_glObjectPtrLabel) (const void*, GLsizei, const GLchar*);
extern pfn_glObjectPtrLabel fp_glObjectPtrLabel;
typedef void (APIENTRYP pfn_glGetObjectPtrLabel) (const void*, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetObjectPtrLabel fp_glGetObjectPtrLabel;

 /* GL_VERSION_4_4 */
extern GLboolean GLAD_VERSION_4_4;
#define GL_MAX_VERTEX_ATTRIB_STRIDE            0x82E5
#define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED  0x8221
#define GL_TEXTURE_BUFFER_BINDING              0x8C2A
#define GL_MAP_PERSISTENT_BIT                  0x0040
#define GL_MAP_COHERENT_BIT                    0x0080
#define GL_DYNAMIC_STORAGE_BIT                 0x0100
#define GL_CLIENT_STORAGE_BIT                  0x0200
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT    0x00004000
#define GL_BUFFER_IMMUTABLE_STORAGE            0x821F
#define GL_BUFFER_STORAGE_FLAGS                0x8220
#define GL_CLEAR_TEXTURE                       0x9365
#define GL_LOCATION_COMPONENT                  0x934A
#define GL_TRANSFORM_FEEDBACK_BUFFER_INDEX     0x934B
#define GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE    0x934C
#define GL_QUERY_BUFFER                        0x9192
#define GL_QUERY_BUFFER_BARRIER_BIT            0x00008000
#define GL_QUERY_BUFFER_BINDING                0x9193
#define GL_QUERY_RESULT_NO_WAIT                0x9194
#define GL_MIRROR_CLAMP_TO_EDGE                0x8743
typedef void (APIENTRYP pfn_glBufferStorage) (GLenum, GLsizeiptr, const void*, GLbitfield);
extern pfn_glBufferStorage fp_glBufferStorage;
typedef void (APIENTRYP pfn_glClearTexImage) (GLuint, GLint, GLenum, GLenum, const void*);
extern pfn_glClearTexImage fp_glClearTexImage;
typedef void (APIENTRYP pfn_glClearTexSubImage) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glClearTexSubImage fp_glClearTexSubImage;
typedef void (APIENTRYP pfn_glBindBuffersBase) (GLenum, GLuint, GLsizei, const GLuint*);
extern pfn_glBindBuffersBase fp_glBindBuffersBase;
typedef void (APIENTRYP pfn_glBindBuffersRange) (GLenum, GLuint, GLsizei, const GLuint*, const GLintptr*, const GLsizeiptr*);
extern pfn_glBindBuffersRange fp_glBindBuffersRange;
typedef void (APIENTRYP pfn_glBindTextures) (GLuint, GLsizei, const GLuint*);
extern pfn_glBindTextures fp_glBindTextures;
typedef void (APIENTRYP pfn_glBindSamplers) (GLuint, GLsizei, const GLuint*);
extern pfn_glBindSamplers fp_glBindSamplers;
typedef void (APIENTRYP pfn_glBindImageTextures) (GLuint, GLsizei, const GLuint*);
extern pfn_glBindImageTextures fp_glBindImageTextures;
typedef void (APIENTRYP pfn_glBindVertexBuffers) (GLuint, GLsizei, const GLuint*, const GLintptr*, const GLsizei*);
extern pfn_glBindVertexBuffers fp_glBindVertexBuffers;

 /* GL_ES_VERSION_2_0 */
extern GLboolean GLAD_ES_VERSION_2_0;
#define GL_BLEND_EQUATION                      0x8009
#define GL_BLEND_COLOR                         0x8005
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS   0x8CD9

 /* GL_ES_VERSION_3_0 */
extern GLboolean GLAD_ES_VERSION_3_0;
#define GL_COPY_READ_BUFFER_BINDING            0x8F36
#define GL_COPY_WRITE_BUFFER_BINDING           0x8F37
#define GL_TRANSFORM_FEEDBACK_PAUSED           0x8E23
#define GL_TRANSFORM_FEEDBACK_ACTIVE           0x8E24

 /* GL_KHR_debug */
extern GLboolean GLAD_KHR_debug;
#define GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR        0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR  0x8243
#define GL_DEBUG_CALLBACK_FUNCTION_KHR         0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM_KHR       0x8245
#define GL_DEBUG_SOURCE_API_KHR                0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR      0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER_KHR    0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY_KHR        0x8249
#define GL_DEBUG_SOURCE_APPLICATION_KHR        0x824A
#define GL_DEBUG_SOURCE_OTHER_KHR              0x824B
#define GL_DEBUG_TYPE_ERROR_KHR                0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR  0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR   0x824E
#define GL_DEBUG_TYPE_PORTABILITY_KHR          0x824F
#define GL_DEBUG_TYPE_PERFORMANCE_KHR          0x8250
#define GL_DEBUG_TYPE_OTHER_KHR                0x8251
#define GL_DEBUG_TYPE_MARKER_KHR               0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP_KHR           0x8269
#define GL_DEBUG_TYPE_POP_GROUP_KHR            0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION_KHR     0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH_KHR     0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH_KHR         0x826D
#define GL_BUFFER_KHR                          0x82E0
#define GL_SHADER_KHR                          0x82E1
#define GL_PROGRAM_KHR                         0x82E2
#define GL_VERTEX_ARRAY_KHR                    0x8074
#define GL_QUERY_KHR                           0x82E3
#define GL_SAMPLER_KHR                         0x82E6
#define GL_MAX_LABEL_LENGTH_KHR                0x82E8
#define GL_MAX_DEBUG_MESSAGE_LENGTH_KHR        0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES_KHR       0x9144
#define GL_DEBUG_LOGGED_MESSAGES_KHR           0x9145
#define GL_DEBUG_SEVERITY_HIGH_KHR             0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_KHR           0x9147
#define GL_DEBUG_SEVERITY_LOW_KHR              0x9148
#define GL_DEBUG_OUTPUT_KHR                    0x92E0
#define GL_CONTEXT_FLAG_DEBUG_BIT_KHR          0x00000002
#define GL_STACK_OVERFLOW_KHR                  0x0503
#define GL_STACK_UNDERFLOW_KHR                 0x0504
typedef void (APIENTRYP pfn_glDebugMessageControlKHR) (GLenum, GLenum, GLenum, GLsizei, const GLuint*, GLboolean);
extern pfn_glDebugMessageControlKHR fp_glDebugMessageControlKHR;
typedef void (APIENTRYP pfn_glDebugMessageInsertKHR) (GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*);
extern pfn_glDebugMessageInsertKHR fp_glDebugMessageInsertKHR;
typedef void (APIENTRYP pfn_glDebugMessageCallbackKHR) (GLDEBUGPROCKHR, const void*);
extern pfn_glDebugMessageCallbackKHR fp_glDebugMessageCallbackKHR;
typedef GLuint (APIENTRYP pfn_glGetDebugMessageLogKHR) (GLuint, GLsizei, GLenum*, GLenum*, GLuint*, GLenum*, GLsizei*, GLchar*);
extern pfn_glGetDebugMessageLogKHR fp_glGetDebugMessageLogKHR;
typedef void (APIENTRYP pfn_glPushDebugGroupKHR) (GLenum, GLuint, GLsizei, const GLchar*);
extern pfn_glPushDebugGroupKHR fp_glPushDebugGroupKHR;
typedef void (APIENTRYP pfn_glPopDebugGroupKHR) ();
extern pfn_glPopDebugGroupKHR fp_glPopDebugGroupKHR;
typedef void (APIENTRYP pfn_glObjectLabelKHR) (GLenum, GLuint, GLsizei, const GLchar*);
extern pfn_glObjectLabelKHR fp_glObjectLabelKHR;
typedef void (APIENTRYP pfn_glGetObjectLabelKHR) (GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetObjectLabelKHR fp_glGetObjectLabelKHR;
typedef void (APIENTRYP pfn_glObjectPtrLabelKHR) (const void*, GLsizei, const GLchar*);
extern pfn_glObjectPtrLabelKHR fp_glObjectPtrLabelKHR;
typedef void (APIENTRYP pfn_glGetObjectPtrLabelKHR) (const void*, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetObjectPtrLabelKHR fp_glGetObjectPtrLabelKHR;
typedef void (APIENTRYP pfn_glGetPointervKHR) (GLenum, void**);
extern pfn_glGetPointervKHR fp_glGetPointervKHR;

 /* GL_KHR_texture_compression_astc_hdr */
extern GLboolean GLAD_KHR_texture_compression_astc_hdr;
#define GL_COMPRESSED_RGBA_ASTC_4x4_KHR        0x93B0
#define GL_COMPRESSED_RGBA_ASTC_5x4_KHR        0x93B1
#define GL_COMPRESSED_RGBA_ASTC_5x5_KHR        0x93B2
#define GL_COMPRESSED_RGBA_ASTC_6x5_KHR        0x93B3
#define GL_COMPRESSED_RGBA_ASTC_6x6_KHR        0x93B4
#define GL_COMPRESSED_RGBA_ASTC_8x5_KHR        0x93B5
#define GL_COMPRESSED_RGBA_ASTC_8x6_KHR        0x93B6
#define GL_COMPRESSED_RGBA_ASTC_8x8_KHR        0x93B7
#define GL_COMPRESSED_RGBA_ASTC_10x5_KHR       0x93B8
#define GL_COMPRESSED_RGBA_ASTC_10x6_KHR       0x93B9
#define GL_COMPRESSED_RGBA_ASTC_10x8_KHR       0x93BA
#define GL_COMPRESSED_RGBA_ASTC_10x10_KHR      0x93BB
#define GL_COMPRESSED_RGBA_ASTC_12x10_KHR      0x93BC
#define GL_COMPRESSED_RGBA_ASTC_12x12_KHR      0x93BD
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR  0x93D0
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR  0x93D1
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR  0x93D2
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR  0x93D3
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR  0x93D4
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR  0x93D5
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR  0x93D6
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR  0x93D7
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR  0x93D8
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR  0x93D9
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR  0x93DA
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR  0x93DB
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR  0x93DC
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR  0x93DD

 /* GL_KHR_texture_compression_astc_ldr */
extern GLboolean GLAD_KHR_texture_compression_astc_ldr;

 /* GL_ARB_arrays_of_arrays */
extern GLboolean GLAD_ARB_arrays_of_arrays;

 /* GL_ARB_base_instance */
extern GLboolean GLAD_ARB_base_instance;

 /* GL_ARB_bindless_texture */
extern GLboolean GLAD_ARB_bindless_texture;
#define GL_UNSIGNED_INT64_ARB                  0x140F
typedef GLuint64 (APIENTRYP pfn_glGetTextureHandleARB) (GLuint);
extern pfn_glGetTextureHandleARB fp_glGetTextureHandleARB;
typedef GLuint64 (APIENTRYP pfn_glGetTextureSamplerHandleARB) (GLuint, GLuint);
extern pfn_glGetTextureSamplerHandleARB fp_glGetTextureSamplerHandleARB;
typedef void (APIENTRYP pfn_glMakeTextureHandleResidentARB) (GLuint64);
extern pfn_glMakeTextureHandleResidentARB fp_glMakeTextureHandleResidentARB;
typedef void (APIENTRYP pfn_glMakeTextureHandleNonResidentARB) (GLuint64);
extern pfn_glMakeTextureHandleNonResidentARB fp_glMakeTextureHandleNonResidentARB;
typedef GLuint64 (APIENTRYP pfn_glGetImageHandleARB) (GLuint, GLint, GLboolean, GLint, GLenum);
extern pfn_glGetImageHandleARB fp_glGetImageHandleARB;
typedef void (APIENTRYP pfn_glMakeImageHandleResidentARB) (GLuint64, GLenum);
extern pfn_glMakeImageHandleResidentARB fp_glMakeImageHandleResidentARB;
typedef void (APIENTRYP pfn_glMakeImageHandleNonResidentARB) (GLuint64);
extern pfn_glMakeImageHandleNonResidentARB fp_glMakeImageHandleNonResidentARB;
typedef void (APIENTRYP pfn_glUniformHandleui64ARB) (GLint, GLuint64);
extern pfn_glUniformHandleui64ARB fp_glUniformHandleui64ARB;
typedef void (APIENTRYP pfn_glUniformHandleui64vARB) (GLint, GLsizei, const GLuint64*);
extern pfn_glUniformHandleui64vARB fp_glUniformHandleui64vARB;
typedef void (APIENTRYP pfn_glProgramUniformHandleui64ARB) (GLuint, GLint, GLuint64);
extern pfn_glProgramUniformHandleui64ARB fp_glProgramUniformHandleui64ARB;
typedef void (APIENTRYP pfn_glProgramUniformHandleui64vARB) (GLuint, GLint, GLsizei, const GLuint64*);
extern pfn_glProgramUniformHandleui64vARB fp_glProgramUniformHandleui64vARB;
typedef GLboolean (APIENTRYP pfn_glIsTextureHandleResidentARB) (GLuint64);
extern pfn_glIsTextureHandleResidentARB fp_glIsTextureHandleResidentARB;
typedef GLboolean (APIENTRYP pfn_glIsImageHandleResidentARB) (GLuint64);
extern pfn_glIsImageHandleResidentARB fp_glIsImageHandleResidentARB;
typedef void (APIENTRYP pfn_glVertexAttribL1ui64ARB) (GLuint, GLuint64EXT);
extern pfn_glVertexAttribL1ui64ARB fp_glVertexAttribL1ui64ARB;
typedef void (APIENTRYP pfn_glVertexAttribL1ui64vARB) (GLuint, const GLuint64EXT*);
extern pfn_glVertexAttribL1ui64vARB fp_glVertexAttribL1ui64vARB;
typedef void (APIENTRYP pfn_glGetVertexAttribLui64vARB) (GLuint, GLenum, GLuint64EXT*);
extern pfn_glGetVertexAttribLui64vARB fp_glGetVertexAttribLui64vARB;

 /* GL_ARB_blend_func_extended */
extern GLboolean GLAD_ARB_blend_func_extended;

 /* GL_ARB_buffer_storage */
extern GLboolean GLAD_ARB_buffer_storage;

 /* GL_ARB_cl_event */
extern GLboolean GLAD_ARB_cl_event;
#define GL_SYNC_CL_EVENT_ARB                   0x8240
#define GL_SYNC_CL_EVENT_COMPLETE_ARB          0x8241
typedef GLsync (APIENTRYP pfn_glCreateSyncFromCLeventARB) (struct _cl_context*, struct _cl_event*, GLbitfield);
extern pfn_glCreateSyncFromCLeventARB fp_glCreateSyncFromCLeventARB;

 /* GL_ARB_clear_buffer_object */
extern GLboolean GLAD_ARB_clear_buffer_object;

 /* GL_ARB_clear_texture */
extern GLboolean GLAD_ARB_clear_texture;

 /* GL_ARB_color_buffer_float */
extern GLboolean GLAD_ARB_color_buffer_float;
#define GL_RGBA_FLOAT_MODE_ARB                 0x8820
#define GL_CLAMP_VERTEX_COLOR_ARB              0x891A
#define GL_CLAMP_FRAGMENT_COLOR_ARB            0x891B
#define GL_CLAMP_READ_COLOR_ARB                0x891C
#define GL_FIXED_ONLY_ARB                      0x891D
typedef void (APIENTRYP pfn_glClampColorARB) (GLenum, GLenum);
extern pfn_glClampColorARB fp_glClampColorARB;

 /* GL_ARB_compatibility */
extern GLboolean GLAD_ARB_compatibility;

 /* GL_ARB_compressed_texture_pixel_storage */
extern GLboolean GLAD_ARB_compressed_texture_pixel_storage;

 /* GL_ARB_compute_shader */
extern GLboolean GLAD_ARB_compute_shader;
#define GL_COMPUTE_SHADER_BIT                  0x00000020

 /* GL_ARB_compute_variable_group_size */
extern GLboolean GLAD_ARB_compute_variable_group_size;
#define GL_MAX_COMPUTE_VARIABLE_GROUP_INVOCATIONS_ARB  0x9344
#define GL_MAX_COMPUTE_FIXED_GROUP_INVOCATIONS_ARB  0x90EB
#define GL_MAX_COMPUTE_VARIABLE_GROUP_SIZE_ARB  0x9345
#define GL_MAX_COMPUTE_FIXED_GROUP_SIZE_ARB    0x91BF
typedef void (APIENTRYP pfn_glDispatchComputeGroupSizeARB) (GLuint, GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glDispatchComputeGroupSizeARB fp_glDispatchComputeGroupSizeARB;

 /* GL_ARB_conservative_depth */
extern GLboolean GLAD_ARB_conservative_depth;

 /* GL_ARB_copy_buffer */
extern GLboolean GLAD_ARB_copy_buffer;

 /* GL_ARB_copy_image */
extern GLboolean GLAD_ARB_copy_image;

 /* GL_ARB_debug_output */
extern GLboolean GLAD_ARB_debug_output;
#define GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB        0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB  0x8243
#define GL_DEBUG_CALLBACK_FUNCTION_ARB         0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM_ARB       0x8245
#define GL_DEBUG_SOURCE_API_ARB                0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB      0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER_ARB    0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY_ARB        0x8249
#define GL_DEBUG_SOURCE_APPLICATION_ARB        0x824A
#define GL_DEBUG_SOURCE_OTHER_ARB              0x824B
#define GL_DEBUG_TYPE_ERROR_ARB                0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB  0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB   0x824E
#define GL_DEBUG_TYPE_PORTABILITY_ARB          0x824F
#define GL_DEBUG_TYPE_PERFORMANCE_ARB          0x8250
#define GL_DEBUG_TYPE_OTHER_ARB                0x8251
#define GL_MAX_DEBUG_MESSAGE_LENGTH_ARB        0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES_ARB       0x9144
#define GL_DEBUG_LOGGED_MESSAGES_ARB           0x9145
#define GL_DEBUG_SEVERITY_HIGH_ARB             0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_ARB           0x9147
#define GL_DEBUG_SEVERITY_LOW_ARB              0x9148
typedef void (APIENTRYP pfn_glDebugMessageControlARB) (GLenum, GLenum, GLenum, GLsizei, const GLuint*, GLboolean);
extern pfn_glDebugMessageControlARB fp_glDebugMessageControlARB;
typedef void (APIENTRYP pfn_glDebugMessageInsertARB) (GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*);
extern pfn_glDebugMessageInsertARB fp_glDebugMessageInsertARB;
typedef void (APIENTRYP pfn_glDebugMessageCallbackARB) (GLDEBUGPROCARB, const void*);
extern pfn_glDebugMessageCallbackARB fp_glDebugMessageCallbackARB;
typedef GLuint (APIENTRYP pfn_glGetDebugMessageLogARB) (GLuint, GLsizei, GLenum*, GLenum*, GLuint*, GLenum*, GLsizei*, GLchar*);
extern pfn_glGetDebugMessageLogARB fp_glGetDebugMessageLogARB;

 /* GL_ARB_depth_buffer_float */
extern GLboolean GLAD_ARB_depth_buffer_float;

 /* GL_ARB_depth_clamp */
extern GLboolean GLAD_ARB_depth_clamp;

 /* GL_ARB_depth_texture */
extern GLboolean GLAD_ARB_depth_texture;
#define GL_DEPTH_COMPONENT16_ARB               0x81A5
#define GL_DEPTH_COMPONENT24_ARB               0x81A6
#define GL_DEPTH_COMPONENT32_ARB               0x81A7
#define GL_TEXTURE_DEPTH_SIZE_ARB              0x884A
#define GL_DEPTH_TEXTURE_MODE_ARB              0x884B

 /* GL_ARB_draw_buffers */
extern GLboolean GLAD_ARB_draw_buffers;
#define GL_MAX_DRAW_BUFFERS_ARB                0x8824
#define GL_DRAW_BUFFER0_ARB                    0x8825
#define GL_DRAW_BUFFER1_ARB                    0x8826
#define GL_DRAW_BUFFER2_ARB                    0x8827
#define GL_DRAW_BUFFER3_ARB                    0x8828
#define GL_DRAW_BUFFER4_ARB                    0x8829
#define GL_DRAW_BUFFER5_ARB                    0x882A
#define GL_DRAW_BUFFER6_ARB                    0x882B
#define GL_DRAW_BUFFER7_ARB                    0x882C
#define GL_DRAW_BUFFER8_ARB                    0x882D
#define GL_DRAW_BUFFER9_ARB                    0x882E
#define GL_DRAW_BUFFER10_ARB                   0x882F
#define GL_DRAW_BUFFER11_ARB                   0x8830
#define GL_DRAW_BUFFER12_ARB                   0x8831
#define GL_DRAW_BUFFER13_ARB                   0x8832
#define GL_DRAW_BUFFER14_ARB                   0x8833
#define GL_DRAW_BUFFER15_ARB                   0x8834
typedef void (APIENTRYP pfn_glDrawBuffersARB) (GLsizei, const GLenum*);
extern pfn_glDrawBuffersARB fp_glDrawBuffersARB;

 /* GL_ARB_draw_buffers_blend */
extern GLboolean GLAD_ARB_draw_buffers_blend;
typedef void (APIENTRYP pfn_glBlendEquationiARB) (GLuint, GLenum);
extern pfn_glBlendEquationiARB fp_glBlendEquationiARB;
typedef void (APIENTRYP pfn_glBlendEquationSeparateiARB) (GLuint, GLenum, GLenum);
extern pfn_glBlendEquationSeparateiARB fp_glBlendEquationSeparateiARB;
typedef void (APIENTRYP pfn_glBlendFunciARB) (GLuint, GLenum, GLenum);
extern pfn_glBlendFunciARB fp_glBlendFunciARB;
typedef void (APIENTRYP pfn_glBlendFuncSeparateiARB) (GLuint, GLenum, GLenum, GLenum, GLenum);
extern pfn_glBlendFuncSeparateiARB fp_glBlendFuncSeparateiARB;

 /* GL_ARB_draw_elements_base_vertex */
extern GLboolean GLAD_ARB_draw_elements_base_vertex;

 /* GL_ARB_draw_indirect */
extern GLboolean GLAD_ARB_draw_indirect;

 /* GL_ARB_draw_instanced */
extern GLboolean GLAD_ARB_draw_instanced;
typedef void (APIENTRYP pfn_glDrawArraysInstancedARB) (GLenum, GLint, GLsizei, GLsizei);
extern pfn_glDrawArraysInstancedARB fp_glDrawArraysInstancedARB;
typedef void (APIENTRYP pfn_glDrawElementsInstancedARB) (GLenum, GLsizei, GLenum, const void*, GLsizei);
extern pfn_glDrawElementsInstancedARB fp_glDrawElementsInstancedARB;

 /* GL_ARB_enhanced_layouts */
extern GLboolean GLAD_ARB_enhanced_layouts;

 /* GL_ARB_ES2_compatibility */
extern GLboolean GLAD_ARB_ES2_compatibility;

 /* GL_ARB_ES3_compatibility */
extern GLboolean GLAD_ARB_ES3_compatibility;

 /* GL_ARB_explicit_attrib_location */
extern GLboolean GLAD_ARB_explicit_attrib_location;

 /* GL_ARB_explicit_uniform_location */
extern GLboolean GLAD_ARB_explicit_uniform_location;

 /* GL_ARB_fragment_coord_conventions */
extern GLboolean GLAD_ARB_fragment_coord_conventions;

 /* GL_ARB_fragment_layer_viewport */
extern GLboolean GLAD_ARB_fragment_layer_viewport;

 /* GL_ARB_fragment_program */
extern GLboolean GLAD_ARB_fragment_program;
#define GL_FRAGMENT_PROGRAM_ARB                0x8804
#define GL_PROGRAM_FORMAT_ASCII_ARB            0x8875
#define GL_PROGRAM_LENGTH_ARB                  0x8627
#define GL_PROGRAM_FORMAT_ARB                  0x8876
#define GL_PROGRAM_BINDING_ARB                 0x8677
#define GL_PROGRAM_INSTRUCTIONS_ARB            0x88A0
#define GL_MAX_PROGRAM_INSTRUCTIONS_ARB        0x88A1
#define GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB     0x88A2
#define GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB  0x88A3
#define GL_PROGRAM_TEMPORARIES_ARB             0x88A4
#define GL_MAX_PROGRAM_TEMPORARIES_ARB         0x88A5
#define GL_PROGRAM_NATIVE_TEMPORARIES_ARB      0x88A6
#define GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB  0x88A7
#define GL_PROGRAM_PARAMETERS_ARB              0x88A8
#define GL_MAX_PROGRAM_PARAMETERS_ARB          0x88A9
#define GL_PROGRAM_NATIVE_PARAMETERS_ARB       0x88AA
#define GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB   0x88AB
#define GL_PROGRAM_ATTRIBS_ARB                 0x88AC
#define GL_MAX_PROGRAM_ATTRIBS_ARB             0x88AD
#define GL_PROGRAM_NATIVE_ATTRIBS_ARB          0x88AE
#define GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB      0x88AF
#define GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB    0x88B4
#define GL_MAX_PROGRAM_ENV_PARAMETERS_ARB      0x88B5
#define GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB     0x88B6
#define GL_PROGRAM_ALU_INSTRUCTIONS_ARB        0x8805
#define GL_PROGRAM_TEX_INSTRUCTIONS_ARB        0x8806
#define GL_PROGRAM_TEX_INDIRECTIONS_ARB        0x8807
#define GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB  0x8808
#define GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB  0x8809
#define GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB  0x880A
#define GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB    0x880B
#define GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB    0x880C
#define GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB    0x880D
#define GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB  0x880E
#define GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB  0x880F
#define GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB  0x8810
#define GL_PROGRAM_STRING_ARB                  0x8628
#define GL_PROGRAM_ERROR_POSITION_ARB          0x864B
#define GL_CURRENT_MATRIX_ARB                  0x8641
#define GL_TRANSPOSE_CURRENT_MATRIX_ARB        0x88B7
#define GL_CURRENT_MATRIX_STACK_DEPTH_ARB      0x8640
#define GL_MAX_PROGRAM_MATRICES_ARB            0x862F
#define GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB  0x862E
#define GL_MAX_TEXTURE_COORDS_ARB              0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_ARB         0x8872
#define GL_PROGRAM_ERROR_STRING_ARB            0x8874
#define GL_MATRIX0_ARB                         0x88C0
#define GL_MATRIX1_ARB                         0x88C1
#define GL_MATRIX2_ARB                         0x88C2
#define GL_MATRIX3_ARB                         0x88C3
#define GL_MATRIX4_ARB                         0x88C4
#define GL_MATRIX5_ARB                         0x88C5
#define GL_MATRIX6_ARB                         0x88C6
#define GL_MATRIX7_ARB                         0x88C7
#define GL_MATRIX8_ARB                         0x88C8
#define GL_MATRIX9_ARB                         0x88C9
#define GL_MATRIX10_ARB                        0x88CA
#define GL_MATRIX11_ARB                        0x88CB
#define GL_MATRIX12_ARB                        0x88CC
#define GL_MATRIX13_ARB                        0x88CD
#define GL_MATRIX14_ARB                        0x88CE
#define GL_MATRIX15_ARB                        0x88CF
#define GL_MATRIX16_ARB                        0x88D0
#define GL_MATRIX17_ARB                        0x88D1
#define GL_MATRIX18_ARB                        0x88D2
#define GL_MATRIX19_ARB                        0x88D3
#define GL_MATRIX20_ARB                        0x88D4
#define GL_MATRIX21_ARB                        0x88D5
#define GL_MATRIX22_ARB                        0x88D6
#define GL_MATRIX23_ARB                        0x88D7
#define GL_MATRIX24_ARB                        0x88D8
#define GL_MATRIX25_ARB                        0x88D9
#define GL_MATRIX26_ARB                        0x88DA
#define GL_MATRIX27_ARB                        0x88DB
#define GL_MATRIX28_ARB                        0x88DC
#define GL_MATRIX29_ARB                        0x88DD
#define GL_MATRIX30_ARB                        0x88DE
#define GL_MATRIX31_ARB                        0x88DF
typedef void (APIENTRYP pfn_glProgramStringARB) (GLenum, GLenum, GLsizei, const void*);
extern pfn_glProgramStringARB fp_glProgramStringARB;
typedef void (APIENTRYP pfn_glBindProgramARB) (GLenum, GLuint);
extern pfn_glBindProgramARB fp_glBindProgramARB;
typedef void (APIENTRYP pfn_glDeleteProgramsARB) (GLsizei, const GLuint*);
extern pfn_glDeleteProgramsARB fp_glDeleteProgramsARB;
typedef void (APIENTRYP pfn_glGenProgramsARB) (GLsizei, GLuint*);
extern pfn_glGenProgramsARB fp_glGenProgramsARB;
typedef void (APIENTRYP pfn_glProgramEnvParameter4dARB) (GLenum, GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glProgramEnvParameter4dARB fp_glProgramEnvParameter4dARB;
typedef void (APIENTRYP pfn_glProgramEnvParameter4dvARB) (GLenum, GLuint, const GLdouble*);
extern pfn_glProgramEnvParameter4dvARB fp_glProgramEnvParameter4dvARB;
typedef void (APIENTRYP pfn_glProgramEnvParameter4fARB) (GLenum, GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glProgramEnvParameter4fARB fp_glProgramEnvParameter4fARB;
typedef void (APIENTRYP pfn_glProgramEnvParameter4fvARB) (GLenum, GLuint, const GLfloat*);
extern pfn_glProgramEnvParameter4fvARB fp_glProgramEnvParameter4fvARB;
typedef void (APIENTRYP pfn_glProgramLocalParameter4dARB) (GLenum, GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glProgramLocalParameter4dARB fp_glProgramLocalParameter4dARB;
typedef void (APIENTRYP pfn_glProgramLocalParameter4dvARB) (GLenum, GLuint, const GLdouble*);
extern pfn_glProgramLocalParameter4dvARB fp_glProgramLocalParameter4dvARB;
typedef void (APIENTRYP pfn_glProgramLocalParameter4fARB) (GLenum, GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glProgramLocalParameter4fARB fp_glProgramLocalParameter4fARB;
typedef void (APIENTRYP pfn_glProgramLocalParameter4fvARB) (GLenum, GLuint, const GLfloat*);
extern pfn_glProgramLocalParameter4fvARB fp_glProgramLocalParameter4fvARB;
typedef void (APIENTRYP pfn_glGetProgramEnvParameterdvARB) (GLenum, GLuint, GLdouble*);
extern pfn_glGetProgramEnvParameterdvARB fp_glGetProgramEnvParameterdvARB;
typedef void (APIENTRYP pfn_glGetProgramEnvParameterfvARB) (GLenum, GLuint, GLfloat*);
extern pfn_glGetProgramEnvParameterfvARB fp_glGetProgramEnvParameterfvARB;
typedef void (APIENTRYP pfn_glGetProgramLocalParameterdvARB) (GLenum, GLuint, GLdouble*);
extern pfn_glGetProgramLocalParameterdvARB fp_glGetProgramLocalParameterdvARB;
typedef void (APIENTRYP pfn_glGetProgramLocalParameterfvARB) (GLenum, GLuint, GLfloat*);
extern pfn_glGetProgramLocalParameterfvARB fp_glGetProgramLocalParameterfvARB;
typedef void (APIENTRYP pfn_glGetProgramivARB) (GLenum, GLenum, GLint*);
extern pfn_glGetProgramivARB fp_glGetProgramivARB;
typedef void (APIENTRYP pfn_glGetProgramStringARB) (GLenum, GLenum, void*);
extern pfn_glGetProgramStringARB fp_glGetProgramStringARB;
typedef GLboolean (APIENTRYP pfn_glIsProgramARB) (GLuint);
extern pfn_glIsProgramARB fp_glIsProgramARB;

 /* GL_ARB_fragment_program_shadow */
extern GLboolean GLAD_ARB_fragment_program_shadow;

 /* GL_ARB_fragment_shader */
extern GLboolean GLAD_ARB_fragment_shader;
#define GL_FRAGMENT_SHADER_ARB                 0x8B30
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB  0x8B49
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT_ARB  0x8B8B

 /* GL_ARB_framebuffer_no_attachments */
extern GLboolean GLAD_ARB_framebuffer_no_attachments;

 /* GL_ARB_framebuffer_object */
extern GLboolean GLAD_ARB_framebuffer_object;

 /* GL_ARB_framebuffer_sRGB */
extern GLboolean GLAD_ARB_framebuffer_sRGB;

 /* GL_ARB_geometry_shader4 */
extern GLboolean GLAD_ARB_geometry_shader4;
#define GL_LINES_ADJACENCY_ARB                 0x000A
#define GL_LINE_STRIP_ADJACENCY_ARB            0x000B
#define GL_TRIANGLES_ADJACENCY_ARB             0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY_ARB        0x000D
#define GL_PROGRAM_POINT_SIZE_ARB              0x8642
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_ARB  0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_ARB  0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_ARB  0x8DA8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB  0x8DA9
#define GL_GEOMETRY_SHADER_ARB                 0x8DD9
#define GL_GEOMETRY_VERTICES_OUT_ARB           0x8DDA
#define GL_GEOMETRY_INPUT_TYPE_ARB             0x8DDB
#define GL_GEOMETRY_OUTPUT_TYPE_ARB            0x8DDC
#define GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB  0x8DDD
#define GL_MAX_VERTEX_VARYING_COMPONENTS_ARB   0x8DDE
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_ARB  0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_ARB    0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_ARB  0x8DE1
typedef void (APIENTRYP pfn_glProgramParameteriARB) (GLuint, GLenum, GLint);
extern pfn_glProgramParameteriARB fp_glProgramParameteriARB;
typedef void (APIENTRYP pfn_glFramebufferTextureARB) (GLenum, GLenum, GLuint, GLint);
extern pfn_glFramebufferTextureARB fp_glFramebufferTextureARB;
typedef void (APIENTRYP pfn_glFramebufferTextureLayerARB) (GLenum, GLenum, GLuint, GLint, GLint);
extern pfn_glFramebufferTextureLayerARB fp_glFramebufferTextureLayerARB;
typedef void (APIENTRYP pfn_glFramebufferTextureFaceARB) (GLenum, GLenum, GLuint, GLint, GLenum);
extern pfn_glFramebufferTextureFaceARB fp_glFramebufferTextureFaceARB;

 /* GL_ARB_get_program_binary */
extern GLboolean GLAD_ARB_get_program_binary;

 /* GL_ARB_gpu_shader5 */
extern GLboolean GLAD_ARB_gpu_shader5;

 /* GL_ARB_gpu_shader_fp64 */
extern GLboolean GLAD_ARB_gpu_shader_fp64;

 /* GL_ARB_half_float_pixel */
extern GLboolean GLAD_ARB_half_float_pixel;
#define GL_HALF_FLOAT_ARB                      0x140B

 /* GL_ARB_half_float_vertex */
extern GLboolean GLAD_ARB_half_float_vertex;

 /* GL_ARB_indirect_parameters */
extern GLboolean GLAD_ARB_indirect_parameters;
#define GL_PARAMETER_BUFFER_ARB                0x80EE
#define GL_PARAMETER_BUFFER_BINDING_ARB        0x80EF
typedef void (APIENTRYP pfn_glMultiDrawArraysIndirectCountARB) (GLenum, GLintptr, GLintptr, GLsizei, GLsizei);
extern pfn_glMultiDrawArraysIndirectCountARB fp_glMultiDrawArraysIndirectCountARB;
typedef void (APIENTRYP pfn_glMultiDrawElementsIndirectCountARB) (GLenum, GLenum, GLintptr, GLintptr, GLsizei, GLsizei);
extern pfn_glMultiDrawElementsIndirectCountARB fp_glMultiDrawElementsIndirectCountARB;

 /* GL_ARB_instanced_arrays */
extern GLboolean GLAD_ARB_instanced_arrays;
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ARB     0x88FE
typedef void (APIENTRYP pfn_glVertexAttribDivisorARB) (GLuint, GLuint);
extern pfn_glVertexAttribDivisorARB fp_glVertexAttribDivisorARB;

 /* GL_ARB_internalformat_query */
extern GLboolean GLAD_ARB_internalformat_query;

 /* GL_ARB_internalformat_query2 */
extern GLboolean GLAD_ARB_internalformat_query2;
#define GL_SRGB_DECODE_ARB                     0x8299

 /* GL_ARB_invalidate_subdata */
extern GLboolean GLAD_ARB_invalidate_subdata;

 /* GL_ARB_map_buffer_alignment */
extern GLboolean GLAD_ARB_map_buffer_alignment;

 /* GL_ARB_map_buffer_range */
extern GLboolean GLAD_ARB_map_buffer_range;

 /* GL_ARB_matrix_palette */
extern GLboolean GLAD_ARB_matrix_palette;
#define GL_MATRIX_PALETTE_ARB                  0x8840
#define GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB  0x8841
#define GL_MAX_PALETTE_MATRICES_ARB            0x8842
#define GL_CURRENT_PALETTE_MATRIX_ARB          0x8843
#define GL_MATRIX_INDEX_ARRAY_ARB              0x8844
#define GL_CURRENT_MATRIX_INDEX_ARB            0x8845
#define GL_MATRIX_INDEX_ARRAY_SIZE_ARB         0x8846
#define GL_MATRIX_INDEX_ARRAY_TYPE_ARB         0x8847
#define GL_MATRIX_INDEX_ARRAY_STRIDE_ARB       0x8848
#define GL_MATRIX_INDEX_ARRAY_POINTER_ARB      0x8849
typedef void (APIENTRYP pfn_glCurrentPaletteMatrixARB) (GLint);
extern pfn_glCurrentPaletteMatrixARB fp_glCurrentPaletteMatrixARB;
typedef void (APIENTRYP pfn_glMatrixIndexubvARB) (GLint, const GLubyte*);
extern pfn_glMatrixIndexubvARB fp_glMatrixIndexubvARB;
typedef void (APIENTRYP pfn_glMatrixIndexusvARB) (GLint, const GLushort*);
extern pfn_glMatrixIndexusvARB fp_glMatrixIndexusvARB;
typedef void (APIENTRYP pfn_glMatrixIndexuivARB) (GLint, const GLuint*);
extern pfn_glMatrixIndexuivARB fp_glMatrixIndexuivARB;
typedef void (APIENTRYP pfn_glMatrixIndexPointerARB) (GLint, GLenum, GLsizei, const void*);
extern pfn_glMatrixIndexPointerARB fp_glMatrixIndexPointerARB;

 /* GL_ARB_multi_bind */
extern GLboolean GLAD_ARB_multi_bind;

 /* GL_ARB_multi_draw_indirect */
extern GLboolean GLAD_ARB_multi_draw_indirect;

 /* GL_ARB_multisample */
extern GLboolean GLAD_ARB_multisample;
#define GL_MULTISAMPLE_ARB                     0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE_ARB        0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_ARB             0x809F
#define GL_SAMPLE_COVERAGE_ARB                 0x80A0
#define GL_SAMPLE_BUFFERS_ARB                  0x80A8
#define GL_SAMPLES_ARB                         0x80A9
#define GL_SAMPLE_COVERAGE_VALUE_ARB           0x80AA
#define GL_SAMPLE_COVERAGE_INVERT_ARB          0x80AB
#define GL_MULTISAMPLE_BIT_ARB                 0x20000000
typedef void (APIENTRYP pfn_glSampleCoverageARB) (GLfloat, GLboolean);
extern pfn_glSampleCoverageARB fp_glSampleCoverageARB;

 /* GL_ARB_multitexture */
extern GLboolean GLAD_ARB_multitexture;
#define GL_TEXTURE0_ARB                        0x84C0
#define GL_TEXTURE1_ARB                        0x84C1
#define GL_TEXTURE2_ARB                        0x84C2
#define GL_TEXTURE3_ARB                        0x84C3
#define GL_TEXTURE4_ARB                        0x84C4
#define GL_TEXTURE5_ARB                        0x84C5
#define GL_TEXTURE6_ARB                        0x84C6
#define GL_TEXTURE7_ARB                        0x84C7
#define GL_TEXTURE8_ARB                        0x84C8
#define GL_TEXTURE9_ARB                        0x84C9
#define GL_TEXTURE10_ARB                       0x84CA
#define GL_TEXTURE11_ARB                       0x84CB
#define GL_TEXTURE12_ARB                       0x84CC
#define GL_TEXTURE13_ARB                       0x84CD
#define GL_TEXTURE14_ARB                       0x84CE
#define GL_TEXTURE15_ARB                       0x84CF
#define GL_TEXTURE16_ARB                       0x84D0
#define GL_TEXTURE17_ARB                       0x84D1
#define GL_TEXTURE18_ARB                       0x84D2
#define GL_TEXTURE19_ARB                       0x84D3
#define GL_TEXTURE20_ARB                       0x84D4
#define GL_TEXTURE21_ARB                       0x84D5
#define GL_TEXTURE22_ARB                       0x84D6
#define GL_TEXTURE23_ARB                       0x84D7
#define GL_TEXTURE24_ARB                       0x84D8
#define GL_TEXTURE25_ARB                       0x84D9
#define GL_TEXTURE26_ARB                       0x84DA
#define GL_TEXTURE27_ARB                       0x84DB
#define GL_TEXTURE28_ARB                       0x84DC
#define GL_TEXTURE29_ARB                       0x84DD
#define GL_TEXTURE30_ARB                       0x84DE
#define GL_TEXTURE31_ARB                       0x84DF
#define GL_ACTIVE_TEXTURE_ARB                  0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB           0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB               0x84E2
typedef void (APIENTRYP pfn_glActiveTextureARB) (GLenum);
extern pfn_glActiveTextureARB fp_glActiveTextureARB;
typedef void (APIENTRYP pfn_glClientActiveTextureARB) (GLenum);
extern pfn_glClientActiveTextureARB fp_glClientActiveTextureARB;
typedef void (APIENTRYP pfn_glMultiTexCoord1dARB) (GLenum, GLdouble);
extern pfn_glMultiTexCoord1dARB fp_glMultiTexCoord1dARB;
typedef void (APIENTRYP pfn_glMultiTexCoord1dvARB) (GLenum, const GLdouble*);
extern pfn_glMultiTexCoord1dvARB fp_glMultiTexCoord1dvARB;
typedef void (APIENTRYP pfn_glMultiTexCoord1fARB) (GLenum, GLfloat);
extern pfn_glMultiTexCoord1fARB fp_glMultiTexCoord1fARB;
typedef void (APIENTRYP pfn_glMultiTexCoord1fvARB) (GLenum, const GLfloat*);
extern pfn_glMultiTexCoord1fvARB fp_glMultiTexCoord1fvARB;
typedef void (APIENTRYP pfn_glMultiTexCoord1iARB) (GLenum, GLint);
extern pfn_glMultiTexCoord1iARB fp_glMultiTexCoord1iARB;
typedef void (APIENTRYP pfn_glMultiTexCoord1ivARB) (GLenum, const GLint*);
extern pfn_glMultiTexCoord1ivARB fp_glMultiTexCoord1ivARB;
typedef void (APIENTRYP pfn_glMultiTexCoord1sARB) (GLenum, GLshort);
extern pfn_glMultiTexCoord1sARB fp_glMultiTexCoord1sARB;
typedef void (APIENTRYP pfn_glMultiTexCoord1svARB) (GLenum, const GLshort*);
extern pfn_glMultiTexCoord1svARB fp_glMultiTexCoord1svARB;
typedef void (APIENTRYP pfn_glMultiTexCoord2dARB) (GLenum, GLdouble, GLdouble);
extern pfn_glMultiTexCoord2dARB fp_glMultiTexCoord2dARB;
typedef void (APIENTRYP pfn_glMultiTexCoord2dvARB) (GLenum, const GLdouble*);
extern pfn_glMultiTexCoord2dvARB fp_glMultiTexCoord2dvARB;
typedef void (APIENTRYP pfn_glMultiTexCoord2fARB) (GLenum, GLfloat, GLfloat);
extern pfn_glMultiTexCoord2fARB fp_glMultiTexCoord2fARB;
typedef void (APIENTRYP pfn_glMultiTexCoord2fvARB) (GLenum, const GLfloat*);
extern pfn_glMultiTexCoord2fvARB fp_glMultiTexCoord2fvARB;
typedef void (APIENTRYP pfn_glMultiTexCoord2iARB) (GLenum, GLint, GLint);
extern pfn_glMultiTexCoord2iARB fp_glMultiTexCoord2iARB;
typedef void (APIENTRYP pfn_glMultiTexCoord2ivARB) (GLenum, const GLint*);
extern pfn_glMultiTexCoord2ivARB fp_glMultiTexCoord2ivARB;
typedef void (APIENTRYP pfn_glMultiTexCoord2sARB) (GLenum, GLshort, GLshort);
extern pfn_glMultiTexCoord2sARB fp_glMultiTexCoord2sARB;
typedef void (APIENTRYP pfn_glMultiTexCoord2svARB) (GLenum, const GLshort*);
extern pfn_glMultiTexCoord2svARB fp_glMultiTexCoord2svARB;
typedef void (APIENTRYP pfn_glMultiTexCoord3dARB) (GLenum, GLdouble, GLdouble, GLdouble);
extern pfn_glMultiTexCoord3dARB fp_glMultiTexCoord3dARB;
typedef void (APIENTRYP pfn_glMultiTexCoord3dvARB) (GLenum, const GLdouble*);
extern pfn_glMultiTexCoord3dvARB fp_glMultiTexCoord3dvARB;
typedef void (APIENTRYP pfn_glMultiTexCoord3fARB) (GLenum, GLfloat, GLfloat, GLfloat);
extern pfn_glMultiTexCoord3fARB fp_glMultiTexCoord3fARB;
typedef void (APIENTRYP pfn_glMultiTexCoord3fvARB) (GLenum, const GLfloat*);
extern pfn_glMultiTexCoord3fvARB fp_glMultiTexCoord3fvARB;
typedef void (APIENTRYP pfn_glMultiTexCoord3iARB) (GLenum, GLint, GLint, GLint);
extern pfn_glMultiTexCoord3iARB fp_glMultiTexCoord3iARB;
typedef void (APIENTRYP pfn_glMultiTexCoord3ivARB) (GLenum, const GLint*);
extern pfn_glMultiTexCoord3ivARB fp_glMultiTexCoord3ivARB;
typedef void (APIENTRYP pfn_glMultiTexCoord3sARB) (GLenum, GLshort, GLshort, GLshort);
extern pfn_glMultiTexCoord3sARB fp_glMultiTexCoord3sARB;
typedef void (APIENTRYP pfn_glMultiTexCoord3svARB) (GLenum, const GLshort*);
extern pfn_glMultiTexCoord3svARB fp_glMultiTexCoord3svARB;
typedef void (APIENTRYP pfn_glMultiTexCoord4dARB) (GLenum, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glMultiTexCoord4dARB fp_glMultiTexCoord4dARB;
typedef void (APIENTRYP pfn_glMultiTexCoord4dvARB) (GLenum, const GLdouble*);
extern pfn_glMultiTexCoord4dvARB fp_glMultiTexCoord4dvARB;
typedef void (APIENTRYP pfn_glMultiTexCoord4fARB) (GLenum, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glMultiTexCoord4fARB fp_glMultiTexCoord4fARB;
typedef void (APIENTRYP pfn_glMultiTexCoord4fvARB) (GLenum, const GLfloat*);
extern pfn_glMultiTexCoord4fvARB fp_glMultiTexCoord4fvARB;
typedef void (APIENTRYP pfn_glMultiTexCoord4iARB) (GLenum, GLint, GLint, GLint, GLint);
extern pfn_glMultiTexCoord4iARB fp_glMultiTexCoord4iARB;
typedef void (APIENTRYP pfn_glMultiTexCoord4ivARB) (GLenum, const GLint*);
extern pfn_glMultiTexCoord4ivARB fp_glMultiTexCoord4ivARB;
typedef void (APIENTRYP pfn_glMultiTexCoord4sARB) (GLenum, GLshort, GLshort, GLshort, GLshort);
extern pfn_glMultiTexCoord4sARB fp_glMultiTexCoord4sARB;
typedef void (APIENTRYP pfn_glMultiTexCoord4svARB) (GLenum, const GLshort*);
extern pfn_glMultiTexCoord4svARB fp_glMultiTexCoord4svARB;

 /* GL_ARB_occlusion_query */
extern GLboolean GLAD_ARB_occlusion_query;
#define GL_QUERY_COUNTER_BITS_ARB              0x8864
#define GL_CURRENT_QUERY_ARB                   0x8865
#define GL_QUERY_RESULT_ARB                    0x8866
#define GL_QUERY_RESULT_AVAILABLE_ARB          0x8867
#define GL_SAMPLES_PASSED_ARB                  0x8914
typedef void (APIENTRYP pfn_glGenQueriesARB) (GLsizei, GLuint*);
extern pfn_glGenQueriesARB fp_glGenQueriesARB;
typedef void (APIENTRYP pfn_glDeleteQueriesARB) (GLsizei, const GLuint*);
extern pfn_glDeleteQueriesARB fp_glDeleteQueriesARB;
typedef GLboolean (APIENTRYP pfn_glIsQueryARB) (GLuint);
extern pfn_glIsQueryARB fp_glIsQueryARB;
typedef void (APIENTRYP pfn_glBeginQueryARB) (GLenum, GLuint);
extern pfn_glBeginQueryARB fp_glBeginQueryARB;
typedef void (APIENTRYP pfn_glEndQueryARB) (GLenum);
extern pfn_glEndQueryARB fp_glEndQueryARB;
typedef void (APIENTRYP pfn_glGetQueryivARB) (GLenum, GLenum, GLint*);
extern pfn_glGetQueryivARB fp_glGetQueryivARB;
typedef void (APIENTRYP pfn_glGetQueryObjectivARB) (GLuint, GLenum, GLint*);
extern pfn_glGetQueryObjectivARB fp_glGetQueryObjectivARB;
typedef void (APIENTRYP pfn_glGetQueryObjectuivARB) (GLuint, GLenum, GLuint*);
extern pfn_glGetQueryObjectuivARB fp_glGetQueryObjectuivARB;

 /* GL_ARB_occlusion_query2 */
extern GLboolean GLAD_ARB_occlusion_query2;

 /* GL_ARB_pixel_buffer_object */
extern GLboolean GLAD_ARB_pixel_buffer_object;
#define GL_PIXEL_PACK_BUFFER_ARB               0x88EB
#define GL_PIXEL_UNPACK_BUFFER_ARB             0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING_ARB       0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING_ARB     0x88EF

 /* GL_ARB_point_parameters */
extern GLboolean GLAD_ARB_point_parameters;
#define GL_POINT_SIZE_MIN_ARB                  0x8126
#define GL_POINT_SIZE_MAX_ARB                  0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_ARB       0x8128
#define GL_POINT_DISTANCE_ATTENUATION_ARB      0x8129
typedef void (APIENTRYP pfn_glPointParameterfARB) (GLenum, GLfloat);
extern pfn_glPointParameterfARB fp_glPointParameterfARB;
typedef void (APIENTRYP pfn_glPointParameterfvARB) (GLenum, const GLfloat*);
extern pfn_glPointParameterfvARB fp_glPointParameterfvARB;

 /* GL_ARB_point_sprite */
extern GLboolean GLAD_ARB_point_sprite;
#define GL_POINT_SPRITE_ARB                    0x8861
#define GL_COORD_REPLACE_ARB                   0x8862

 /* GL_ARB_program_interface_query */
extern GLboolean GLAD_ARB_program_interface_query;

 /* GL_ARB_provoking_vertex */
extern GLboolean GLAD_ARB_provoking_vertex;

 /* GL_ARB_query_buffer_object */
extern GLboolean GLAD_ARB_query_buffer_object;

 /* GL_ARB_robust_buffer_access_behavior */
extern GLboolean GLAD_ARB_robust_buffer_access_behavior;

 /* GL_ARB_robustness */
extern GLboolean GLAD_ARB_robustness;
#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB  0x00000004
#define GL_LOSE_CONTEXT_ON_RESET_ARB           0x8252
#define GL_GUILTY_CONTEXT_RESET_ARB            0x8253
#define GL_INNOCENT_CONTEXT_RESET_ARB          0x8254
#define GL_UNKNOWN_CONTEXT_RESET_ARB           0x8255
#define GL_RESET_NOTIFICATION_STRATEGY_ARB     0x8256
#define GL_NO_RESET_NOTIFICATION_ARB           0x8261
typedef GLenum (APIENTRYP pfn_glGetGraphicsResetStatusARB) ();
extern pfn_glGetGraphicsResetStatusARB fp_glGetGraphicsResetStatusARB;
typedef void (APIENTRYP pfn_glGetnTexImageARB) (GLenum, GLint, GLenum, GLenum, GLsizei, void*);
extern pfn_glGetnTexImageARB fp_glGetnTexImageARB;
typedef void (APIENTRYP pfn_glReadnPixelsARB) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void*);
extern pfn_glReadnPixelsARB fp_glReadnPixelsARB;
typedef void (APIENTRYP pfn_glGetnCompressedTexImageARB) (GLenum, GLint, GLsizei, void*);
extern pfn_glGetnCompressedTexImageARB fp_glGetnCompressedTexImageARB;
typedef void (APIENTRYP pfn_glGetnUniformfvARB) (GLuint, GLint, GLsizei, GLfloat*);
extern pfn_glGetnUniformfvARB fp_glGetnUniformfvARB;
typedef void (APIENTRYP pfn_glGetnUniformivARB) (GLuint, GLint, GLsizei, GLint*);
extern pfn_glGetnUniformivARB fp_glGetnUniformivARB;
typedef void (APIENTRYP pfn_glGetnUniformuivARB) (GLuint, GLint, GLsizei, GLuint*);
extern pfn_glGetnUniformuivARB fp_glGetnUniformuivARB;
typedef void (APIENTRYP pfn_glGetnUniformdvARB) (GLuint, GLint, GLsizei, GLdouble*);
extern pfn_glGetnUniformdvARB fp_glGetnUniformdvARB;
typedef void (APIENTRYP pfn_glGetnMapdvARB) (GLenum, GLenum, GLsizei, GLdouble*);
extern pfn_glGetnMapdvARB fp_glGetnMapdvARB;
typedef void (APIENTRYP pfn_glGetnMapfvARB) (GLenum, GLenum, GLsizei, GLfloat*);
extern pfn_glGetnMapfvARB fp_glGetnMapfvARB;
typedef void (APIENTRYP pfn_glGetnMapivARB) (GLenum, GLenum, GLsizei, GLint*);
extern pfn_glGetnMapivARB fp_glGetnMapivARB;
typedef void (APIENTRYP pfn_glGetnPixelMapfvARB) (GLenum, GLsizei, GLfloat*);
extern pfn_glGetnPixelMapfvARB fp_glGetnPixelMapfvARB;
typedef void (APIENTRYP pfn_glGetnPixelMapuivARB) (GLenum, GLsizei, GLuint*);
extern pfn_glGetnPixelMapuivARB fp_glGetnPixelMapuivARB;
typedef void (APIENTRYP pfn_glGetnPixelMapusvARB) (GLenum, GLsizei, GLushort*);
extern pfn_glGetnPixelMapusvARB fp_glGetnPixelMapusvARB;
typedef void (APIENTRYP pfn_glGetnPolygonStippleARB) (GLsizei, GLubyte*);
extern pfn_glGetnPolygonStippleARB fp_glGetnPolygonStippleARB;
typedef void (APIENTRYP pfn_glGetnColorTableARB) (GLenum, GLenum, GLenum, GLsizei, void*);
extern pfn_glGetnColorTableARB fp_glGetnColorTableARB;
typedef void (APIENTRYP pfn_glGetnConvolutionFilterARB) (GLenum, GLenum, GLenum, GLsizei, void*);
extern pfn_glGetnConvolutionFilterARB fp_glGetnConvolutionFilterARB;
typedef void (APIENTRYP pfn_glGetnSeparableFilterARB) (GLenum, GLenum, GLenum, GLsizei, void*, GLsizei, void*, void*);
extern pfn_glGetnSeparableFilterARB fp_glGetnSeparableFilterARB;
typedef void (APIENTRYP pfn_glGetnHistogramARB) (GLenum, GLboolean, GLenum, GLenum, GLsizei, void*);
extern pfn_glGetnHistogramARB fp_glGetnHistogramARB;
typedef void (APIENTRYP pfn_glGetnMinmaxARB) (GLenum, GLboolean, GLenum, GLenum, GLsizei, void*);
extern pfn_glGetnMinmaxARB fp_glGetnMinmaxARB;

 /* GL_ARB_robustness_isolation */
extern GLboolean GLAD_ARB_robustness_isolation;

 /* GL_ARB_sample_shading */
extern GLboolean GLAD_ARB_sample_shading;
#define GL_SAMPLE_SHADING_ARB                  0x8C36
#define GL_MIN_SAMPLE_SHADING_VALUE_ARB        0x8C37
typedef void (APIENTRYP pfn_glMinSampleShadingARB) (GLfloat);
extern pfn_glMinSampleShadingARB fp_glMinSampleShadingARB;

 /* GL_ARB_sampler_objects */
extern GLboolean GLAD_ARB_sampler_objects;

 /* GL_ARB_seamless_cube_map */
extern GLboolean GLAD_ARB_seamless_cube_map;

 /* GL_ARB_seamless_cubemap_per_texture */
extern GLboolean GLAD_ARB_seamless_cubemap_per_texture;

 /* GL_ARB_separate_shader_objects */
extern GLboolean GLAD_ARB_separate_shader_objects;

 /* GL_ARB_shader_atomic_counters */
extern GLboolean GLAD_ARB_shader_atomic_counters;

 /* GL_ARB_shader_bit_encoding */
extern GLboolean GLAD_ARB_shader_bit_encoding;

 /* GL_ARB_shader_draw_parameters */
extern GLboolean GLAD_ARB_shader_draw_parameters;

 /* GL_ARB_shader_group_vote */
extern GLboolean GLAD_ARB_shader_group_vote;

 /* GL_ARB_shader_image_load_store */
extern GLboolean GLAD_ARB_shader_image_load_store;

 /* GL_ARB_shader_image_size */
extern GLboolean GLAD_ARB_shader_image_size;

 /* GL_ARB_shader_objects */
extern GLboolean GLAD_ARB_shader_objects;
#define GL_PROGRAM_OBJECT_ARB                  0x8B40
#define GL_SHADER_OBJECT_ARB                   0x8B48
#define GL_OBJECT_TYPE_ARB                     0x8B4E
#define GL_OBJECT_SUBTYPE_ARB                  0x8B4F
#define GL_FLOAT_VEC2_ARB                      0x8B50
#define GL_FLOAT_VEC3_ARB                      0x8B51
#define GL_FLOAT_VEC4_ARB                      0x8B52
#define GL_INT_VEC2_ARB                        0x8B53
#define GL_INT_VEC3_ARB                        0x8B54
#define GL_INT_VEC4_ARB                        0x8B55
#define GL_BOOL_ARB                            0x8B56
#define GL_BOOL_VEC2_ARB                       0x8B57
#define GL_BOOL_VEC3_ARB                       0x8B58
#define GL_BOOL_VEC4_ARB                       0x8B59
#define GL_FLOAT_MAT2_ARB                      0x8B5A
#define GL_FLOAT_MAT3_ARB                      0x8B5B
#define GL_FLOAT_MAT4_ARB                      0x8B5C
#define GL_SAMPLER_1D_ARB                      0x8B5D
#define GL_SAMPLER_2D_ARB                      0x8B5E
#define GL_SAMPLER_3D_ARB                      0x8B5F
#define GL_SAMPLER_CUBE_ARB                    0x8B60
#define GL_SAMPLER_1D_SHADOW_ARB               0x8B61
#define GL_SAMPLER_2D_SHADOW_ARB               0x8B62
#define GL_SAMPLER_2D_RECT_ARB                 0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW_ARB          0x8B64
#define GL_OBJECT_DELETE_STATUS_ARB            0x8B80
#define GL_OBJECT_COMPILE_STATUS_ARB           0x8B81
#define GL_OBJECT_LINK_STATUS_ARB              0x8B82
#define GL_OBJECT_VALIDATE_STATUS_ARB          0x8B83
#define GL_OBJECT_INFO_LOG_LENGTH_ARB          0x8B84
#define GL_OBJECT_ATTACHED_OBJECTS_ARB         0x8B85
#define GL_OBJECT_ACTIVE_UNIFORMS_ARB          0x8B86
#define GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB  0x8B87
#define GL_OBJECT_SHADER_SOURCE_LENGTH_ARB     0x8B88
typedef void (APIENTRYP pfn_glDeleteObjectARB) (GLhandleARB);
extern pfn_glDeleteObjectARB fp_glDeleteObjectARB;
typedef GLhandleARB (APIENTRYP pfn_glGetHandleARB) (GLenum);
extern pfn_glGetHandleARB fp_glGetHandleARB;
typedef void (APIENTRYP pfn_glDetachObjectARB) (GLhandleARB, GLhandleARB);
extern pfn_glDetachObjectARB fp_glDetachObjectARB;
typedef GLhandleARB (APIENTRYP pfn_glCreateShaderObjectARB) (GLenum);
extern pfn_glCreateShaderObjectARB fp_glCreateShaderObjectARB;
typedef void (APIENTRYP pfn_glShaderSourceARB) (GLhandleARB, GLsizei, const GLcharARB**, const GLint*);
extern pfn_glShaderSourceARB fp_glShaderSourceARB;
typedef void (APIENTRYP pfn_glCompileShaderARB) (GLhandleARB);
extern pfn_glCompileShaderARB fp_glCompileShaderARB;
typedef GLhandleARB (APIENTRYP pfn_glCreateProgramObjectARB) ();
extern pfn_glCreateProgramObjectARB fp_glCreateProgramObjectARB;
typedef void (APIENTRYP pfn_glAttachObjectARB) (GLhandleARB, GLhandleARB);
extern pfn_glAttachObjectARB fp_glAttachObjectARB;
typedef void (APIENTRYP pfn_glLinkProgramARB) (GLhandleARB);
extern pfn_glLinkProgramARB fp_glLinkProgramARB;
typedef void (APIENTRYP pfn_glUseProgramObjectARB) (GLhandleARB);
extern pfn_glUseProgramObjectARB fp_glUseProgramObjectARB;
typedef void (APIENTRYP pfn_glValidateProgramARB) (GLhandleARB);
extern pfn_glValidateProgramARB fp_glValidateProgramARB;
typedef void (APIENTRYP pfn_glUniform1fARB) (GLint, GLfloat);
extern pfn_glUniform1fARB fp_glUniform1fARB;
typedef void (APIENTRYP pfn_glUniform2fARB) (GLint, GLfloat, GLfloat);
extern pfn_glUniform2fARB fp_glUniform2fARB;
typedef void (APIENTRYP pfn_glUniform3fARB) (GLint, GLfloat, GLfloat, GLfloat);
extern pfn_glUniform3fARB fp_glUniform3fARB;
typedef void (APIENTRYP pfn_glUniform4fARB) (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glUniform4fARB fp_glUniform4fARB;
typedef void (APIENTRYP pfn_glUniform1iARB) (GLint, GLint);
extern pfn_glUniform1iARB fp_glUniform1iARB;
typedef void (APIENTRYP pfn_glUniform2iARB) (GLint, GLint, GLint);
extern pfn_glUniform2iARB fp_glUniform2iARB;
typedef void (APIENTRYP pfn_glUniform3iARB) (GLint, GLint, GLint, GLint);
extern pfn_glUniform3iARB fp_glUniform3iARB;
typedef void (APIENTRYP pfn_glUniform4iARB) (GLint, GLint, GLint, GLint, GLint);
extern pfn_glUniform4iARB fp_glUniform4iARB;
typedef void (APIENTRYP pfn_glUniform1fvARB) (GLint, GLsizei, const GLfloat*);
extern pfn_glUniform1fvARB fp_glUniform1fvARB;
typedef void (APIENTRYP pfn_glUniform2fvARB) (GLint, GLsizei, const GLfloat*);
extern pfn_glUniform2fvARB fp_glUniform2fvARB;
typedef void (APIENTRYP pfn_glUniform3fvARB) (GLint, GLsizei, const GLfloat*);
extern pfn_glUniform3fvARB fp_glUniform3fvARB;
typedef void (APIENTRYP pfn_glUniform4fvARB) (GLint, GLsizei, const GLfloat*);
extern pfn_glUniform4fvARB fp_glUniform4fvARB;
typedef void (APIENTRYP pfn_glUniform1ivARB) (GLint, GLsizei, const GLint*);
extern pfn_glUniform1ivARB fp_glUniform1ivARB;
typedef void (APIENTRYP pfn_glUniform2ivARB) (GLint, GLsizei, const GLint*);
extern pfn_glUniform2ivARB fp_glUniform2ivARB;
typedef void (APIENTRYP pfn_glUniform3ivARB) (GLint, GLsizei, const GLint*);
extern pfn_glUniform3ivARB fp_glUniform3ivARB;
typedef void (APIENTRYP pfn_glUniform4ivARB) (GLint, GLsizei, const GLint*);
extern pfn_glUniform4ivARB fp_glUniform4ivARB;
typedef void (APIENTRYP pfn_glUniformMatrix2fvARB) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix2fvARB fp_glUniformMatrix2fvARB;
typedef void (APIENTRYP pfn_glUniformMatrix3fvARB) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix3fvARB fp_glUniformMatrix3fvARB;
typedef void (APIENTRYP pfn_glUniformMatrix4fvARB) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix4fvARB fp_glUniformMatrix4fvARB;
typedef void (APIENTRYP pfn_glGetObjectParameterfvARB) (GLhandleARB, GLenum, GLfloat*);
extern pfn_glGetObjectParameterfvARB fp_glGetObjectParameterfvARB;
typedef void (APIENTRYP pfn_glGetObjectParameterivARB) (GLhandleARB, GLenum, GLint*);
extern pfn_glGetObjectParameterivARB fp_glGetObjectParameterivARB;
typedef void (APIENTRYP pfn_glGetInfoLogARB) (GLhandleARB, GLsizei, GLsizei*, GLcharARB*);
extern pfn_glGetInfoLogARB fp_glGetInfoLogARB;
typedef void (APIENTRYP pfn_glGetAttachedObjectsARB) (GLhandleARB, GLsizei, GLsizei*, GLhandleARB*);
extern pfn_glGetAttachedObjectsARB fp_glGetAttachedObjectsARB;
typedef GLint (APIENTRYP pfn_glGetUniformLocationARB) (GLhandleARB, const GLcharARB*);
extern pfn_glGetUniformLocationARB fp_glGetUniformLocationARB;
typedef void (APIENTRYP pfn_glGetActiveUniformARB) (GLhandleARB, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLcharARB*);
extern pfn_glGetActiveUniformARB fp_glGetActiveUniformARB;
typedef void (APIENTRYP pfn_glGetUniformfvARB) (GLhandleARB, GLint, GLfloat*);
extern pfn_glGetUniformfvARB fp_glGetUniformfvARB;
typedef void (APIENTRYP pfn_glGetUniformivARB) (GLhandleARB, GLint, GLint*);
extern pfn_glGetUniformivARB fp_glGetUniformivARB;
typedef void (APIENTRYP pfn_glGetShaderSourceARB) (GLhandleARB, GLsizei, GLsizei*, GLcharARB*);
extern pfn_glGetShaderSourceARB fp_glGetShaderSourceARB;

 /* GL_ARB_shader_precision */
extern GLboolean GLAD_ARB_shader_precision;

 /* GL_ARB_shader_stencil_export */
extern GLboolean GLAD_ARB_shader_stencil_export;

 /* GL_ARB_shader_storage_buffer_object */
extern GLboolean GLAD_ARB_shader_storage_buffer_object;

 /* GL_ARB_shader_subroutine */
extern GLboolean GLAD_ARB_shader_subroutine;

 /* GL_ARB_shader_texture_lod */
extern GLboolean GLAD_ARB_shader_texture_lod;

 /* GL_ARB_shading_language_100 */
extern GLboolean GLAD_ARB_shading_language_100;
#define GL_SHADING_LANGUAGE_VERSION_ARB        0x8B8C

 /* GL_ARB_shading_language_420pack */
extern GLboolean GLAD_ARB_shading_language_420pack;

 /* GL_ARB_shading_language_include */
extern GLboolean GLAD_ARB_shading_language_include;
#define GL_SHADER_INCLUDE_ARB                  0x8DAE
#define GL_NAMED_STRING_LENGTH_ARB             0x8DE9
#define GL_NAMED_STRING_TYPE_ARB               0x8DEA
typedef void (APIENTRYP pfn_glNamedStringARB) (GLenum, GLint, const GLchar*, GLint, const GLchar*);
extern pfn_glNamedStringARB fp_glNamedStringARB;
typedef void (APIENTRYP pfn_glDeleteNamedStringARB) (GLint, const GLchar*);
extern pfn_glDeleteNamedStringARB fp_glDeleteNamedStringARB;
typedef void (APIENTRYP pfn_glCompileShaderIncludeARB) (GLuint, GLsizei, const GLchar**, const GLint*);
extern pfn_glCompileShaderIncludeARB fp_glCompileShaderIncludeARB;
typedef GLboolean (APIENTRYP pfn_glIsNamedStringARB) (GLint, const GLchar*);
extern pfn_glIsNamedStringARB fp_glIsNamedStringARB;
typedef void (APIENTRYP pfn_glGetNamedStringARB) (GLint, const GLchar*, GLsizei, GLint*, GLchar*);
extern pfn_glGetNamedStringARB fp_glGetNamedStringARB;
typedef void (APIENTRYP pfn_glGetNamedStringivARB) (GLint, const GLchar*, GLenum, GLint*);
extern pfn_glGetNamedStringivARB fp_glGetNamedStringivARB;

 /* GL_ARB_shading_language_packing */
extern GLboolean GLAD_ARB_shading_language_packing;

 /* GL_ARB_shadow */
extern GLboolean GLAD_ARB_shadow;
#define GL_TEXTURE_COMPARE_MODE_ARB            0x884C
#define GL_TEXTURE_COMPARE_FUNC_ARB            0x884D
#define GL_COMPARE_R_TO_TEXTURE_ARB            0x884E

 /* GL_ARB_shadow_ambient */
extern GLboolean GLAD_ARB_shadow_ambient;
#define GL_TEXTURE_COMPARE_FAIL_VALUE_ARB      0x80BF

 /* GL_ARB_sparse_texture */
extern GLboolean GLAD_ARB_sparse_texture;
#define GL_TEXTURE_SPARSE_ARB                  0x91A6
#define GL_VIRTUAL_PAGE_SIZE_INDEX_ARB         0x91A7
#define GL_MIN_SPARSE_LEVEL_ARB                0x919B
#define GL_NUM_VIRTUAL_PAGE_SIZES_ARB          0x91A8
#define GL_VIRTUAL_PAGE_SIZE_X_ARB             0x9195
#define GL_VIRTUAL_PAGE_SIZE_Y_ARB             0x9196
#define GL_VIRTUAL_PAGE_SIZE_Z_ARB             0x9197
#define GL_MAX_SPARSE_TEXTURE_SIZE_ARB         0x9198
#define GL_MAX_SPARSE_3D_TEXTURE_SIZE_ARB      0x9199
#define GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_ARB  0x919A
#define GL_SPARSE_TEXTURE_FULL_ARRAY_CUBE_MIPMAPS_ARB  0x91A9
typedef void (APIENTRYP pfn_glTexPageCommitmentARB) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLboolean);
extern pfn_glTexPageCommitmentARB fp_glTexPageCommitmentARB;

 /* GL_ARB_stencil_texturing */
extern GLboolean GLAD_ARB_stencil_texturing;

 /* GL_ARB_sync */
extern GLboolean GLAD_ARB_sync;

 /* GL_ARB_tessellation_shader */
extern GLboolean GLAD_ARB_tessellation_shader;

 /* GL_ARB_texture_border_clamp */
extern GLboolean GLAD_ARB_texture_border_clamp;
#define GL_CLAMP_TO_BORDER_ARB                 0x812D

 /* GL_ARB_texture_buffer_object */
extern GLboolean GLAD_ARB_texture_buffer_object;
#define GL_TEXTURE_BUFFER_ARB                  0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE_ARB         0x8C2B
#define GL_TEXTURE_BINDING_BUFFER_ARB          0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING_ARB  0x8C2D
#define GL_TEXTURE_BUFFER_FORMAT_ARB           0x8C2E
typedef void (APIENTRYP pfn_glTexBufferARB) (GLenum, GLenum, GLuint);
extern pfn_glTexBufferARB fp_glTexBufferARB;

 /* GL_ARB_texture_buffer_object_rgb32 */
extern GLboolean GLAD_ARB_texture_buffer_object_rgb32;

 /* GL_ARB_texture_buffer_range */
extern GLboolean GLAD_ARB_texture_buffer_range;

 /* GL_ARB_texture_compression */
extern GLboolean GLAD_ARB_texture_compression;
#define GL_COMPRESSED_ALPHA_ARB                0x84E9
#define GL_COMPRESSED_LUMINANCE_ARB            0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA_ARB      0x84EB
#define GL_COMPRESSED_INTENSITY_ARB            0x84EC
#define GL_COMPRESSED_RGB_ARB                  0x84ED
#define GL_COMPRESSED_RGBA_ARB                 0x84EE
#define GL_TEXTURE_COMPRESSION_HINT_ARB        0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB   0x86A0
#define GL_TEXTURE_COMPRESSED_ARB              0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB  0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS_ARB      0x86A3
typedef void (APIENTRYP pfn_glCompressedTexImage3DARB) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedTexImage3DARB fp_glCompressedTexImage3DARB;
typedef void (APIENTRYP pfn_glCompressedTexImage2DARB) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedTexImage2DARB fp_glCompressedTexImage2DARB;
typedef void (APIENTRYP pfn_glCompressedTexImage1DARB) (GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedTexImage1DARB fp_glCompressedTexImage1DARB;
typedef void (APIENTRYP pfn_glCompressedTexSubImage3DARB) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedTexSubImage3DARB fp_glCompressedTexSubImage3DARB;
typedef void (APIENTRYP pfn_glCompressedTexSubImage2DARB) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedTexSubImage2DARB fp_glCompressedTexSubImage2DARB;
typedef void (APIENTRYP pfn_glCompressedTexSubImage1DARB) (GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedTexSubImage1DARB fp_glCompressedTexSubImage1DARB;
typedef void (APIENTRYP pfn_glGetCompressedTexImageARB) (GLenum, GLint, void*);
extern pfn_glGetCompressedTexImageARB fp_glGetCompressedTexImageARB;

 /* GL_ARB_texture_compression_bptc */
extern GLboolean GLAD_ARB_texture_compression_bptc;
#define GL_COMPRESSED_RGBA_BPTC_UNORM_ARB      0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB  0x8E8D
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB  0x8E8E
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB  0x8E8F

 /* GL_ARB_texture_compression_rgtc */
extern GLboolean GLAD_ARB_texture_compression_rgtc;

 /* GL_ARB_texture_cube_map */
extern GLboolean GLAD_ARB_texture_cube_map;
#define GL_NORMAL_MAP_ARB                      0x8511
#define GL_REFLECTION_MAP_ARB                  0x8512
#define GL_TEXTURE_CUBE_MAP_ARB                0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_ARB        0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB     0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB     0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB     0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB     0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB     0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB     0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB          0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB       0x851C

 /* GL_ARB_texture_cube_map_array */
extern GLboolean GLAD_ARB_texture_cube_map_array;
#define GL_TEXTURE_CUBE_MAP_ARRAY_ARB          0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_ARB  0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY_ARB    0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY_ARB          0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_ARB   0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY_ARB      0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_ARB  0x900F

 /* GL_ARB_texture_env_add */
extern GLboolean GLAD_ARB_texture_env_add;

 /* GL_ARB_texture_env_combine */
extern GLboolean GLAD_ARB_texture_env_combine;
#define GL_COMBINE_ARB                         0x8570
#define GL_COMBINE_RGB_ARB                     0x8571
#define GL_COMBINE_ALPHA_ARB                   0x8572
#define GL_SOURCE0_RGB_ARB                     0x8580
#define GL_SOURCE1_RGB_ARB                     0x8581
#define GL_SOURCE2_RGB_ARB                     0x8582
#define GL_SOURCE0_ALPHA_ARB                   0x8588
#define GL_SOURCE1_ALPHA_ARB                   0x8589
#define GL_SOURCE2_ALPHA_ARB                   0x858A
#define GL_OPERAND0_RGB_ARB                    0x8590
#define GL_OPERAND1_RGB_ARB                    0x8591
#define GL_OPERAND2_RGB_ARB                    0x8592
#define GL_OPERAND0_ALPHA_ARB                  0x8598
#define GL_OPERAND1_ALPHA_ARB                  0x8599
#define GL_OPERAND2_ALPHA_ARB                  0x859A
#define GL_RGB_SCALE_ARB                       0x8573
#define GL_ADD_SIGNED_ARB                      0x8574
#define GL_INTERPOLATE_ARB                     0x8575
#define GL_SUBTRACT_ARB                        0x84E7
#define GL_CONSTANT_ARB                        0x8576
#define GL_PRIMARY_COLOR_ARB                   0x8577
#define GL_PREVIOUS_ARB                        0x8578

 /* GL_ARB_texture_env_crossbar */
extern GLboolean GLAD_ARB_texture_env_crossbar;

 /* GL_ARB_texture_env_dot3 */
extern GLboolean GLAD_ARB_texture_env_dot3;
#define GL_DOT3_RGB_ARB                        0x86AE
#define GL_DOT3_RGBA_ARB                       0x86AF

 /* GL_ARB_texture_float */
extern GLboolean GLAD_ARB_texture_float;
#define GL_TEXTURE_RED_TYPE_ARB                0x8C10
#define GL_TEXTURE_GREEN_TYPE_ARB              0x8C11
#define GL_TEXTURE_BLUE_TYPE_ARB               0x8C12
#define GL_TEXTURE_ALPHA_TYPE_ARB              0x8C13
#define GL_TEXTURE_LUMINANCE_TYPE_ARB          0x8C14
#define GL_TEXTURE_INTENSITY_TYPE_ARB          0x8C15
#define GL_TEXTURE_DEPTH_TYPE_ARB              0x8C16
#define GL_UNSIGNED_NORMALIZED_ARB             0x8C17
#define GL_RGBA32F_ARB                         0x8814
#define GL_RGB32F_ARB                          0x8815
#define GL_ALPHA32F_ARB                        0x8816
#define GL_INTENSITY32F_ARB                    0x8817
#define GL_LUMINANCE32F_ARB                    0x8818
#define GL_LUMINANCE_ALPHA32F_ARB              0x8819
#define GL_RGBA16F_ARB                         0x881A
#define GL_RGB16F_ARB                          0x881B
#define GL_ALPHA16F_ARB                        0x881C
#define GL_INTENSITY16F_ARB                    0x881D
#define GL_LUMINANCE16F_ARB                    0x881E
#define GL_LUMINANCE_ALPHA16F_ARB              0x881F

 /* GL_ARB_texture_gather */
extern GLboolean GLAD_ARB_texture_gather;
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_ARB  0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET_ARB  0x8E5F
#define GL_MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS_ARB  0x8F9F

 /* GL_ARB_texture_mirror_clamp_to_edge */
extern GLboolean GLAD_ARB_texture_mirror_clamp_to_edge;

 /* GL_ARB_texture_mirrored_repeat */
extern GLboolean GLAD_ARB_texture_mirrored_repeat;
#define GL_MIRRORED_REPEAT_ARB                 0x8370

 /* GL_ARB_texture_multisample */
extern GLboolean GLAD_ARB_texture_multisample;

 /* GL_ARB_texture_non_power_of_two */
extern GLboolean GLAD_ARB_texture_non_power_of_two;

 /* GL_ARB_texture_query_levels */
extern GLboolean GLAD_ARB_texture_query_levels;

 /* GL_ARB_texture_query_lod */
extern GLboolean GLAD_ARB_texture_query_lod;

 /* GL_ARB_texture_rectangle */
extern GLboolean GLAD_ARB_texture_rectangle;
#define GL_TEXTURE_RECTANGLE_ARB               0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_ARB       0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_ARB         0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB      0x84F8

 /* GL_ARB_texture_rg */
extern GLboolean GLAD_ARB_texture_rg;

 /* GL_ARB_texture_rgb10_a2ui */
extern GLboolean GLAD_ARB_texture_rgb10_a2ui;

 /* GL_ARB_texture_stencil8 */
extern GLboolean GLAD_ARB_texture_stencil8;

 /* GL_ARB_texture_storage */
extern GLboolean GLAD_ARB_texture_storage;

 /* GL_ARB_texture_storage_multisample */
extern GLboolean GLAD_ARB_texture_storage_multisample;

 /* GL_ARB_texture_swizzle */
extern GLboolean GLAD_ARB_texture_swizzle;

 /* GL_ARB_texture_view */
extern GLboolean GLAD_ARB_texture_view;

 /* GL_ARB_timer_query */
extern GLboolean GLAD_ARB_timer_query;

 /* GL_ARB_transform_feedback2 */
extern GLboolean GLAD_ARB_transform_feedback2;

 /* GL_ARB_transform_feedback3 */
extern GLboolean GLAD_ARB_transform_feedback3;

 /* GL_ARB_transform_feedback_instanced */
extern GLboolean GLAD_ARB_transform_feedback_instanced;

 /* GL_ARB_transpose_matrix */
extern GLboolean GLAD_ARB_transpose_matrix;
#define GL_TRANSPOSE_MODELVIEW_MATRIX_ARB      0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX_ARB     0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX_ARB        0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX_ARB          0x84E6
typedef void (APIENTRYP pfn_glLoadTransposeMatrixfARB) (const GLfloat*);
extern pfn_glLoadTransposeMatrixfARB fp_glLoadTransposeMatrixfARB;
typedef void (APIENTRYP pfn_glLoadTransposeMatrixdARB) (const GLdouble*);
extern pfn_glLoadTransposeMatrixdARB fp_glLoadTransposeMatrixdARB;
typedef void (APIENTRYP pfn_glMultTransposeMatrixfARB) (const GLfloat*);
extern pfn_glMultTransposeMatrixfARB fp_glMultTransposeMatrixfARB;
typedef void (APIENTRYP pfn_glMultTransposeMatrixdARB) (const GLdouble*);
extern pfn_glMultTransposeMatrixdARB fp_glMultTransposeMatrixdARB;

 /* GL_ARB_uniform_buffer_object */
extern GLboolean GLAD_ARB_uniform_buffer_object;
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS         0x8A2C
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS  0x8A32
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER  0x8A45

 /* GL_ARB_vertex_array_bgra */
extern GLboolean GLAD_ARB_vertex_array_bgra;

 /* GL_ARB_vertex_array_object */
extern GLboolean GLAD_ARB_vertex_array_object;

 /* GL_ARB_vertex_attrib_64bit */
extern GLboolean GLAD_ARB_vertex_attrib_64bit;

 /* GL_ARB_vertex_attrib_binding */
extern GLboolean GLAD_ARB_vertex_attrib_binding;

 /* GL_ARB_vertex_blend */
extern GLboolean GLAD_ARB_vertex_blend;
#define GL_MAX_VERTEX_UNITS_ARB                0x86A4
#define GL_ACTIVE_VERTEX_UNITS_ARB             0x86A5
#define GL_WEIGHT_SUM_UNITY_ARB                0x86A6
#define GL_VERTEX_BLEND_ARB                    0x86A7
#define GL_CURRENT_WEIGHT_ARB                  0x86A8
#define GL_WEIGHT_ARRAY_TYPE_ARB               0x86A9
#define GL_WEIGHT_ARRAY_STRIDE_ARB             0x86AA
#define GL_WEIGHT_ARRAY_SIZE_ARB               0x86AB
#define GL_WEIGHT_ARRAY_POINTER_ARB            0x86AC
#define GL_WEIGHT_ARRAY_ARB                    0x86AD
#define GL_MODELVIEW0_ARB                      0x1700
#define GL_MODELVIEW1_ARB                      0x850A
#define GL_MODELVIEW2_ARB                      0x8722
#define GL_MODELVIEW3_ARB                      0x8723
#define GL_MODELVIEW4_ARB                      0x8724
#define GL_MODELVIEW5_ARB                      0x8725
#define GL_MODELVIEW6_ARB                      0x8726
#define GL_MODELVIEW7_ARB                      0x8727
#define GL_MODELVIEW8_ARB                      0x8728
#define GL_MODELVIEW9_ARB                      0x8729
#define GL_MODELVIEW10_ARB                     0x872A
#define GL_MODELVIEW11_ARB                     0x872B
#define GL_MODELVIEW12_ARB                     0x872C
#define GL_MODELVIEW13_ARB                     0x872D
#define GL_MODELVIEW14_ARB                     0x872E
#define GL_MODELVIEW15_ARB                     0x872F
#define GL_MODELVIEW16_ARB                     0x8730
#define GL_MODELVIEW17_ARB                     0x8731
#define GL_MODELVIEW18_ARB                     0x8732
#define GL_MODELVIEW19_ARB                     0x8733
#define GL_MODELVIEW20_ARB                     0x8734
#define GL_MODELVIEW21_ARB                     0x8735
#define GL_MODELVIEW22_ARB                     0x8736
#define GL_MODELVIEW23_ARB                     0x8737
#define GL_MODELVIEW24_ARB                     0x8738
#define GL_MODELVIEW25_ARB                     0x8739
#define GL_MODELVIEW26_ARB                     0x873A
#define GL_MODELVIEW27_ARB                     0x873B
#define GL_MODELVIEW28_ARB                     0x873C
#define GL_MODELVIEW29_ARB                     0x873D
#define GL_MODELVIEW30_ARB                     0x873E
#define GL_MODELVIEW31_ARB                     0x873F
typedef void (APIENTRYP pfn_glWeightbvARB) (GLint, const GLbyte*);
extern pfn_glWeightbvARB fp_glWeightbvARB;
typedef void (APIENTRYP pfn_glWeightsvARB) (GLint, const GLshort*);
extern pfn_glWeightsvARB fp_glWeightsvARB;
typedef void (APIENTRYP pfn_glWeightivARB) (GLint, const GLint*);
extern pfn_glWeightivARB fp_glWeightivARB;
typedef void (APIENTRYP pfn_glWeightfvARB) (GLint, const GLfloat*);
extern pfn_glWeightfvARB fp_glWeightfvARB;
typedef void (APIENTRYP pfn_glWeightdvARB) (GLint, const GLdouble*);
extern pfn_glWeightdvARB fp_glWeightdvARB;
typedef void (APIENTRYP pfn_glWeightubvARB) (GLint, const GLubyte*);
extern pfn_glWeightubvARB fp_glWeightubvARB;
typedef void (APIENTRYP pfn_glWeightusvARB) (GLint, const GLushort*);
extern pfn_glWeightusvARB fp_glWeightusvARB;
typedef void (APIENTRYP pfn_glWeightuivARB) (GLint, const GLuint*);
extern pfn_glWeightuivARB fp_glWeightuivARB;
typedef void (APIENTRYP pfn_glWeightPointerARB) (GLint, GLenum, GLsizei, const void*);
extern pfn_glWeightPointerARB fp_glWeightPointerARB;
typedef void (APIENTRYP pfn_glVertexBlendARB) (GLint);
extern pfn_glVertexBlendARB fp_glVertexBlendARB;

 /* GL_ARB_vertex_buffer_object */
extern GLboolean GLAD_ARB_vertex_buffer_object;
#define GL_BUFFER_SIZE_ARB                     0x8764
#define GL_BUFFER_USAGE_ARB                    0x8765
#define GL_ARRAY_BUFFER_ARB                    0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB            0x8893
#define GL_ARRAY_BUFFER_BINDING_ARB            0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB    0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING_ARB     0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING_ARB     0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING_ARB      0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING_ARB      0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB  0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB  0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB  0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB  0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB     0x889E
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB  0x889F
#define GL_READ_ONLY_ARB                       0x88B8
#define GL_WRITE_ONLY_ARB                      0x88B9
#define GL_READ_WRITE_ARB                      0x88BA
#define GL_BUFFER_ACCESS_ARB                   0x88BB
#define GL_BUFFER_MAPPED_ARB                   0x88BC
#define GL_BUFFER_MAP_POINTER_ARB              0x88BD
#define GL_STREAM_DRAW_ARB                     0x88E0
#define GL_STREAM_READ_ARB                     0x88E1
#define GL_STREAM_COPY_ARB                     0x88E2
#define GL_STATIC_DRAW_ARB                     0x88E4
#define GL_STATIC_READ_ARB                     0x88E5
#define GL_STATIC_COPY_ARB                     0x88E6
#define GL_DYNAMIC_DRAW_ARB                    0x88E8
#define GL_DYNAMIC_READ_ARB                    0x88E9
#define GL_DYNAMIC_COPY_ARB                    0x88EA
typedef void (APIENTRYP pfn_glBindBufferARB) (GLenum, GLuint);
extern pfn_glBindBufferARB fp_glBindBufferARB;
typedef void (APIENTRYP pfn_glDeleteBuffersARB) (GLsizei, const GLuint*);
extern pfn_glDeleteBuffersARB fp_glDeleteBuffersARB;
typedef void (APIENTRYP pfn_glGenBuffersARB) (GLsizei, GLuint*);
extern pfn_glGenBuffersARB fp_glGenBuffersARB;
typedef GLboolean (APIENTRYP pfn_glIsBufferARB) (GLuint);
extern pfn_glIsBufferARB fp_glIsBufferARB;
typedef void (APIENTRYP pfn_glBufferDataARB) (GLenum, GLsizeiptrARB, const void*, GLenum);
extern pfn_glBufferDataARB fp_glBufferDataARB;
typedef void (APIENTRYP pfn_glBufferSubDataARB) (GLenum, GLintptrARB, GLsizeiptrARB, const void*);
extern pfn_glBufferSubDataARB fp_glBufferSubDataARB;
typedef void (APIENTRYP pfn_glGetBufferSubDataARB) (GLenum, GLintptrARB, GLsizeiptrARB, void*);
extern pfn_glGetBufferSubDataARB fp_glGetBufferSubDataARB;
typedef void* (APIENTRYP pfn_glMapBufferARB) (GLenum, GLenum);
extern pfn_glMapBufferARB fp_glMapBufferARB;
typedef GLboolean (APIENTRYP pfn_glUnmapBufferARB) (GLenum);
extern pfn_glUnmapBufferARB fp_glUnmapBufferARB;
typedef void (APIENTRYP pfn_glGetBufferParameterivARB) (GLenum, GLenum, GLint*);
extern pfn_glGetBufferParameterivARB fp_glGetBufferParameterivARB;
typedef void (APIENTRYP pfn_glGetBufferPointervARB) (GLenum, GLenum, void**);
extern pfn_glGetBufferPointervARB fp_glGetBufferPointervARB;

 /* GL_ARB_vertex_program */
extern GLboolean GLAD_ARB_vertex_program;
#define GL_COLOR_SUM_ARB                       0x8458
#define GL_VERTEX_PROGRAM_ARB                  0x8620
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB     0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB        0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB      0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB        0x8625
#define GL_CURRENT_VERTEX_ATTRIB_ARB           0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE_ARB       0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_ARB         0x8643
#define GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB     0x8645
#define GL_MAX_VERTEX_ATTRIBS_ARB              0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB  0x886A
#define GL_PROGRAM_ADDRESS_REGISTERS_ARB       0x88B0
#define GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB   0x88B1
#define GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB  0x88B2
#define GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB  0x88B3
typedef void (APIENTRYP pfn_glVertexAttrib1dARB) (GLuint, GLdouble);
extern pfn_glVertexAttrib1dARB fp_glVertexAttrib1dARB;
typedef void (APIENTRYP pfn_glVertexAttrib1dvARB) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib1dvARB fp_glVertexAttrib1dvARB;
typedef void (APIENTRYP pfn_glVertexAttrib1fARB) (GLuint, GLfloat);
extern pfn_glVertexAttrib1fARB fp_glVertexAttrib1fARB;
typedef void (APIENTRYP pfn_glVertexAttrib1fvARB) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib1fvARB fp_glVertexAttrib1fvARB;
typedef void (APIENTRYP pfn_glVertexAttrib1sARB) (GLuint, GLshort);
extern pfn_glVertexAttrib1sARB fp_glVertexAttrib1sARB;
typedef void (APIENTRYP pfn_glVertexAttrib1svARB) (GLuint, const GLshort*);
extern pfn_glVertexAttrib1svARB fp_glVertexAttrib1svARB;
typedef void (APIENTRYP pfn_glVertexAttrib2dARB) (GLuint, GLdouble, GLdouble);
extern pfn_glVertexAttrib2dARB fp_glVertexAttrib2dARB;
typedef void (APIENTRYP pfn_glVertexAttrib2dvARB) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib2dvARB fp_glVertexAttrib2dvARB;
typedef void (APIENTRYP pfn_glVertexAttrib2fARB) (GLuint, GLfloat, GLfloat);
extern pfn_glVertexAttrib2fARB fp_glVertexAttrib2fARB;
typedef void (APIENTRYP pfn_glVertexAttrib2fvARB) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib2fvARB fp_glVertexAttrib2fvARB;
typedef void (APIENTRYP pfn_glVertexAttrib2sARB) (GLuint, GLshort, GLshort);
extern pfn_glVertexAttrib2sARB fp_glVertexAttrib2sARB;
typedef void (APIENTRYP pfn_glVertexAttrib2svARB) (GLuint, const GLshort*);
extern pfn_glVertexAttrib2svARB fp_glVertexAttrib2svARB;
typedef void (APIENTRYP pfn_glVertexAttrib3dARB) (GLuint, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexAttrib3dARB fp_glVertexAttrib3dARB;
typedef void (APIENTRYP pfn_glVertexAttrib3dvARB) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib3dvARB fp_glVertexAttrib3dvARB;
typedef void (APIENTRYP pfn_glVertexAttrib3fARB) (GLuint, GLfloat, GLfloat, GLfloat);
extern pfn_glVertexAttrib3fARB fp_glVertexAttrib3fARB;
typedef void (APIENTRYP pfn_glVertexAttrib3fvARB) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib3fvARB fp_glVertexAttrib3fvARB;
typedef void (APIENTRYP pfn_glVertexAttrib3sARB) (GLuint, GLshort, GLshort, GLshort);
extern pfn_glVertexAttrib3sARB fp_glVertexAttrib3sARB;
typedef void (APIENTRYP pfn_glVertexAttrib3svARB) (GLuint, const GLshort*);
extern pfn_glVertexAttrib3svARB fp_glVertexAttrib3svARB;
typedef void (APIENTRYP pfn_glVertexAttrib4NbvARB) (GLuint, const GLbyte*);
extern pfn_glVertexAttrib4NbvARB fp_glVertexAttrib4NbvARB;
typedef void (APIENTRYP pfn_glVertexAttrib4NivARB) (GLuint, const GLint*);
extern pfn_glVertexAttrib4NivARB fp_glVertexAttrib4NivARB;
typedef void (APIENTRYP pfn_glVertexAttrib4NsvARB) (GLuint, const GLshort*);
extern pfn_glVertexAttrib4NsvARB fp_glVertexAttrib4NsvARB;
typedef void (APIENTRYP pfn_glVertexAttrib4NubARB) (GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
extern pfn_glVertexAttrib4NubARB fp_glVertexAttrib4NubARB;
typedef void (APIENTRYP pfn_glVertexAttrib4NubvARB) (GLuint, const GLubyte*);
extern pfn_glVertexAttrib4NubvARB fp_glVertexAttrib4NubvARB;
typedef void (APIENTRYP pfn_glVertexAttrib4NuivARB) (GLuint, const GLuint*);
extern pfn_glVertexAttrib4NuivARB fp_glVertexAttrib4NuivARB;
typedef void (APIENTRYP pfn_glVertexAttrib4NusvARB) (GLuint, const GLushort*);
extern pfn_glVertexAttrib4NusvARB fp_glVertexAttrib4NusvARB;
typedef void (APIENTRYP pfn_glVertexAttrib4bvARB) (GLuint, const GLbyte*);
extern pfn_glVertexAttrib4bvARB fp_glVertexAttrib4bvARB;
typedef void (APIENTRYP pfn_glVertexAttrib4dARB) (GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexAttrib4dARB fp_glVertexAttrib4dARB;
typedef void (APIENTRYP pfn_glVertexAttrib4dvARB) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib4dvARB fp_glVertexAttrib4dvARB;
typedef void (APIENTRYP pfn_glVertexAttrib4fARB) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glVertexAttrib4fARB fp_glVertexAttrib4fARB;
typedef void (APIENTRYP pfn_glVertexAttrib4fvARB) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib4fvARB fp_glVertexAttrib4fvARB;
typedef void (APIENTRYP pfn_glVertexAttrib4ivARB) (GLuint, const GLint*);
extern pfn_glVertexAttrib4ivARB fp_glVertexAttrib4ivARB;
typedef void (APIENTRYP pfn_glVertexAttrib4sARB) (GLuint, GLshort, GLshort, GLshort, GLshort);
extern pfn_glVertexAttrib4sARB fp_glVertexAttrib4sARB;
typedef void (APIENTRYP pfn_glVertexAttrib4svARB) (GLuint, const GLshort*);
extern pfn_glVertexAttrib4svARB fp_glVertexAttrib4svARB;
typedef void (APIENTRYP pfn_glVertexAttrib4ubvARB) (GLuint, const GLubyte*);
extern pfn_glVertexAttrib4ubvARB fp_glVertexAttrib4ubvARB;
typedef void (APIENTRYP pfn_glVertexAttrib4uivARB) (GLuint, const GLuint*);
extern pfn_glVertexAttrib4uivARB fp_glVertexAttrib4uivARB;
typedef void (APIENTRYP pfn_glVertexAttrib4usvARB) (GLuint, const GLushort*);
extern pfn_glVertexAttrib4usvARB fp_glVertexAttrib4usvARB;
typedef void (APIENTRYP pfn_glVertexAttribPointerARB) (GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
extern pfn_glVertexAttribPointerARB fp_glVertexAttribPointerARB;
typedef void (APIENTRYP pfn_glEnableVertexAttribArrayARB) (GLuint);
extern pfn_glEnableVertexAttribArrayARB fp_glEnableVertexAttribArrayARB;
typedef void (APIENTRYP pfn_glDisableVertexAttribArrayARB) (GLuint);
extern pfn_glDisableVertexAttribArrayARB fp_glDisableVertexAttribArrayARB;
typedef void (APIENTRYP pfn_glGetVertexAttribdvARB) (GLuint, GLenum, GLdouble*);
extern pfn_glGetVertexAttribdvARB fp_glGetVertexAttribdvARB;
typedef void (APIENTRYP pfn_glGetVertexAttribfvARB) (GLuint, GLenum, GLfloat*);
extern pfn_glGetVertexAttribfvARB fp_glGetVertexAttribfvARB;
typedef void (APIENTRYP pfn_glGetVertexAttribivARB) (GLuint, GLenum, GLint*);
extern pfn_glGetVertexAttribivARB fp_glGetVertexAttribivARB;
typedef void (APIENTRYP pfn_glGetVertexAttribPointervARB) (GLuint, GLenum, void**);
extern pfn_glGetVertexAttribPointervARB fp_glGetVertexAttribPointervARB;

 /* GL_ARB_vertex_shader */
extern GLboolean GLAD_ARB_vertex_shader;
#define GL_VERTEX_SHADER_ARB                   0x8B31
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB   0x8B4A
#define GL_MAX_VARYING_FLOATS_ARB              0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB  0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB  0x8B4D
#define GL_OBJECT_ACTIVE_ATTRIBUTES_ARB        0x8B89
#define GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB  0x8B8A
typedef void (APIENTRYP pfn_glBindAttribLocationARB) (GLhandleARB, GLuint, const GLcharARB*);
extern pfn_glBindAttribLocationARB fp_glBindAttribLocationARB;
typedef void (APIENTRYP pfn_glGetActiveAttribARB) (GLhandleARB, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLcharARB*);
extern pfn_glGetActiveAttribARB fp_glGetActiveAttribARB;
typedef GLint (APIENTRYP pfn_glGetAttribLocationARB) (GLhandleARB, const GLcharARB*);
extern pfn_glGetAttribLocationARB fp_glGetAttribLocationARB;

 /* GL_ARB_vertex_type_10f_11f_11f_rev */
extern GLboolean GLAD_ARB_vertex_type_10f_11f_11f_rev;

 /* GL_ARB_vertex_type_2_10_10_10_rev */
extern GLboolean GLAD_ARB_vertex_type_2_10_10_10_rev;

 /* GL_ARB_viewport_array */
extern GLboolean GLAD_ARB_viewport_array;

 /* GL_ARB_window_pos */
extern GLboolean GLAD_ARB_window_pos;
typedef void (APIENTRYP pfn_glWindowPos2dARB) (GLdouble, GLdouble);
extern pfn_glWindowPos2dARB fp_glWindowPos2dARB;
typedef void (APIENTRYP pfn_glWindowPos2dvARB) (const GLdouble*);
extern pfn_glWindowPos2dvARB fp_glWindowPos2dvARB;
typedef void (APIENTRYP pfn_glWindowPos2fARB) (GLfloat, GLfloat);
extern pfn_glWindowPos2fARB fp_glWindowPos2fARB;
typedef void (APIENTRYP pfn_glWindowPos2fvARB) (const GLfloat*);
extern pfn_glWindowPos2fvARB fp_glWindowPos2fvARB;
typedef void (APIENTRYP pfn_glWindowPos2iARB) (GLint, GLint);
extern pfn_glWindowPos2iARB fp_glWindowPos2iARB;
typedef void (APIENTRYP pfn_glWindowPos2ivARB) (const GLint*);
extern pfn_glWindowPos2ivARB fp_glWindowPos2ivARB;
typedef void (APIENTRYP pfn_glWindowPos2sARB) (GLshort, GLshort);
extern pfn_glWindowPos2sARB fp_glWindowPos2sARB;
typedef void (APIENTRYP pfn_glWindowPos2svARB) (const GLshort*);
extern pfn_glWindowPos2svARB fp_glWindowPos2svARB;
typedef void (APIENTRYP pfn_glWindowPos3dARB) (GLdouble, GLdouble, GLdouble);
extern pfn_glWindowPos3dARB fp_glWindowPos3dARB;
typedef void (APIENTRYP pfn_glWindowPos3dvARB) (const GLdouble*);
extern pfn_glWindowPos3dvARB fp_glWindowPos3dvARB;
typedef void (APIENTRYP pfn_glWindowPos3fARB) (GLfloat, GLfloat, GLfloat);
extern pfn_glWindowPos3fARB fp_glWindowPos3fARB;
typedef void (APIENTRYP pfn_glWindowPos3fvARB) (const GLfloat*);
extern pfn_glWindowPos3fvARB fp_glWindowPos3fvARB;
typedef void (APIENTRYP pfn_glWindowPos3iARB) (GLint, GLint, GLint);
extern pfn_glWindowPos3iARB fp_glWindowPos3iARB;
typedef void (APIENTRYP pfn_glWindowPos3ivARB) (const GLint*);
extern pfn_glWindowPos3ivARB fp_glWindowPos3ivARB;
typedef void (APIENTRYP pfn_glWindowPos3sARB) (GLshort, GLshort, GLshort);
extern pfn_glWindowPos3sARB fp_glWindowPos3sARB;
typedef void (APIENTRYP pfn_glWindowPos3svARB) (const GLshort*);
extern pfn_glWindowPos3svARB fp_glWindowPos3svARB;

 /* GL_EXT_422_pixels */
extern GLboolean GLAD_EXT_422_pixels;
#define GL_422_EXT                             0x80CC
#define GL_422_REV_EXT                         0x80CD
#define GL_422_AVERAGE_EXT                     0x80CE
#define GL_422_REV_AVERAGE_EXT                 0x80CF

 /* GL_EXT_abgr */
extern GLboolean GLAD_EXT_abgr;
#define GL_ABGR_EXT                            0x8000

 /* GL_EXT_bindable_uniform */
extern GLboolean GLAD_EXT_bindable_uniform;
#define GL_MAX_VERTEX_BINDABLE_UNIFORMS_EXT    0x8DE2
#define GL_MAX_FRAGMENT_BINDABLE_UNIFORMS_EXT  0x8DE3
#define GL_MAX_GEOMETRY_BINDABLE_UNIFORMS_EXT  0x8DE4
#define GL_MAX_BINDABLE_UNIFORM_SIZE_EXT       0x8DED
#define GL_UNIFORM_BUFFER_EXT                  0x8DEE
#define GL_UNIFORM_BUFFER_BINDING_EXT          0x8DEF
typedef void (APIENTRYP pfn_glUniformBufferEXT) (GLuint, GLint, GLuint);
extern pfn_glUniformBufferEXT fp_glUniformBufferEXT;
typedef GLint (APIENTRYP pfn_glGetUniformBufferSizeEXT) (GLuint, GLint);
extern pfn_glGetUniformBufferSizeEXT fp_glGetUniformBufferSizeEXT;
typedef GLintptr (APIENTRYP pfn_glGetUniformOffsetEXT) (GLuint, GLint);
extern pfn_glGetUniformOffsetEXT fp_glGetUniformOffsetEXT;

 /* GL_EXT_blend_color */
extern GLboolean GLAD_EXT_blend_color;
#define GL_CONSTANT_COLOR_EXT                  0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR_EXT        0x8002
#define GL_CONSTANT_ALPHA_EXT                  0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA_EXT        0x8004
#define GL_BLEND_COLOR_EXT                     0x8005
typedef void (APIENTRYP pfn_glBlendColorEXT) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glBlendColorEXT fp_glBlendColorEXT;

 /* GL_EXT_blend_equation_separate */
extern GLboolean GLAD_EXT_blend_equation_separate;
#define GL_BLEND_EQUATION_RGB_EXT              0x8009
#define GL_BLEND_EQUATION_ALPHA_EXT            0x883D
typedef void (APIENTRYP pfn_glBlendEquationSeparateEXT) (GLenum, GLenum);
extern pfn_glBlendEquationSeparateEXT fp_glBlendEquationSeparateEXT;

 /* GL_EXT_blend_func_separate */
extern GLboolean GLAD_EXT_blend_func_separate;
#define GL_BLEND_DST_RGB_EXT                   0x80C8
#define GL_BLEND_SRC_RGB_EXT                   0x80C9
#define GL_BLEND_DST_ALPHA_EXT                 0x80CA
#define GL_BLEND_SRC_ALPHA_EXT                 0x80CB
typedef void (APIENTRYP pfn_glBlendFuncSeparateEXT) (GLenum, GLenum, GLenum, GLenum);
extern pfn_glBlendFuncSeparateEXT fp_glBlendFuncSeparateEXT;

 /* GL_EXT_blend_minmax */
extern GLboolean GLAD_EXT_blend_minmax;
#define GL_MIN_EXT                             0x8007
#define GL_MAX_EXT                             0x8008
#define GL_FUNC_ADD_EXT                        0x8006
#define GL_BLEND_EQUATION_EXT                  0x8009
typedef void (APIENTRYP pfn_glBlendEquationEXT) (GLenum);
extern pfn_glBlendEquationEXT fp_glBlendEquationEXT;

 /* GL_EXT_blend_subtract */
extern GLboolean GLAD_EXT_blend_subtract;
#define GL_FUNC_SUBTRACT_EXT                   0x800A
#define GL_FUNC_REVERSE_SUBTRACT_EXT           0x800B

 /* GL_EXT_clip_volume_hint */
extern GLboolean GLAD_EXT_clip_volume_hint;
#define GL_CLIP_VOLUME_CLIPPING_HINT_EXT       0x80F0

 /* GL_EXT_cmyka */
extern GLboolean GLAD_EXT_cmyka;
#define GL_CMYK_EXT                            0x800C
#define GL_CMYKA_EXT                           0x800D
#define GL_PACK_CMYK_HINT_EXT                  0x800E
#define GL_UNPACK_CMYK_HINT_EXT                0x800F

 /* GL_EXT_color_buffer_half_float */
extern GLboolean GLAD_EXT_color_buffer_half_float;
#define GL_RGBA16F_EXT                         0x881A
#define GL_RGB16F_EXT                          0x881B
#define GL_RG16F_EXT                           0x822F
#define GL_R16F_EXT                            0x822D
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT  0x8211
#define GL_UNSIGNED_NORMALIZED_EXT             0x8C17

 /* GL_EXT_color_subtable */
extern GLboolean GLAD_EXT_color_subtable;
typedef void (APIENTRYP pfn_glColorSubTableEXT) (GLenum, GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glColorSubTableEXT fp_glColorSubTableEXT;
typedef void (APIENTRYP pfn_glCopyColorSubTableEXT) (GLenum, GLsizei, GLint, GLint, GLsizei);
extern pfn_glCopyColorSubTableEXT fp_glCopyColorSubTableEXT;

 /* GL_EXT_compiled_vertex_array */
extern GLboolean GLAD_EXT_compiled_vertex_array;
#define GL_ARRAY_ELEMENT_LOCK_FIRST_EXT        0x81A8
#define GL_ARRAY_ELEMENT_LOCK_COUNT_EXT        0x81A9
typedef void (APIENTRYP pfn_glLockArraysEXT) (GLint, GLsizei);
extern pfn_glLockArraysEXT fp_glLockArraysEXT;
typedef void (APIENTRYP pfn_glUnlockArraysEXT) ();
extern pfn_glUnlockArraysEXT fp_glUnlockArraysEXT;

 /* GL_EXT_convolution */
extern GLboolean GLAD_EXT_convolution;
#define GL_CONVOLUTION_1D_EXT                  0x8010
#define GL_CONVOLUTION_2D_EXT                  0x8011
#define GL_SEPARABLE_2D_EXT                    0x8012
#define GL_CONVOLUTION_BORDER_MODE_EXT         0x8013
#define GL_CONVOLUTION_FILTER_SCALE_EXT        0x8014
#define GL_CONVOLUTION_FILTER_BIAS_EXT         0x8015
#define GL_REDUCE_EXT                          0x8016
#define GL_CONVOLUTION_FORMAT_EXT              0x8017
#define GL_CONVOLUTION_WIDTH_EXT               0x8018
#define GL_CONVOLUTION_HEIGHT_EXT              0x8019
#define GL_MAX_CONVOLUTION_WIDTH_EXT           0x801A
#define GL_MAX_CONVOLUTION_HEIGHT_EXT          0x801B
#define GL_POST_CONVOLUTION_RED_SCALE_EXT      0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE_EXT    0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE_EXT     0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE_EXT    0x801F
#define GL_POST_CONVOLUTION_RED_BIAS_EXT       0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS_EXT     0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS_EXT      0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS_EXT     0x8023
typedef void (APIENTRYP pfn_glConvolutionFilter1DEXT) (GLenum, GLenum, GLsizei, GLenum, GLenum, const void*);
extern pfn_glConvolutionFilter1DEXT fp_glConvolutionFilter1DEXT;
typedef void (APIENTRYP pfn_glConvolutionFilter2DEXT) (GLenum, GLenum, GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glConvolutionFilter2DEXT fp_glConvolutionFilter2DEXT;
typedef void (APIENTRYP pfn_glConvolutionParameterfEXT) (GLenum, GLenum, GLfloat);
extern pfn_glConvolutionParameterfEXT fp_glConvolutionParameterfEXT;
typedef void (APIENTRYP pfn_glConvolutionParameterfvEXT) (GLenum, GLenum, const GLfloat*);
extern pfn_glConvolutionParameterfvEXT fp_glConvolutionParameterfvEXT;
typedef void (APIENTRYP pfn_glConvolutionParameteriEXT) (GLenum, GLenum, GLint);
extern pfn_glConvolutionParameteriEXT fp_glConvolutionParameteriEXT;
typedef void (APIENTRYP pfn_glConvolutionParameterivEXT) (GLenum, GLenum, const GLint*);
extern pfn_glConvolutionParameterivEXT fp_glConvolutionParameterivEXT;
typedef void (APIENTRYP pfn_glCopyConvolutionFilter1DEXT) (GLenum, GLenum, GLint, GLint, GLsizei);
extern pfn_glCopyConvolutionFilter1DEXT fp_glCopyConvolutionFilter1DEXT;
typedef void (APIENTRYP pfn_glCopyConvolutionFilter2DEXT) (GLenum, GLenum, GLint, GLint, GLsizei, GLsizei);
extern pfn_glCopyConvolutionFilter2DEXT fp_glCopyConvolutionFilter2DEXT;
typedef void (APIENTRYP pfn_glGetConvolutionFilterEXT) (GLenum, GLenum, GLenum, void*);
extern pfn_glGetConvolutionFilterEXT fp_glGetConvolutionFilterEXT;
typedef void (APIENTRYP pfn_glGetConvolutionParameterfvEXT) (GLenum, GLenum, GLfloat*);
extern pfn_glGetConvolutionParameterfvEXT fp_glGetConvolutionParameterfvEXT;
typedef void (APIENTRYP pfn_glGetConvolutionParameterivEXT) (GLenum, GLenum, GLint*);
extern pfn_glGetConvolutionParameterivEXT fp_glGetConvolutionParameterivEXT;
typedef void (APIENTRYP pfn_glGetSeparableFilterEXT) (GLenum, GLenum, GLenum, void*, void*, void*);
extern pfn_glGetSeparableFilterEXT fp_glGetSeparableFilterEXT;
typedef void (APIENTRYP pfn_glSeparableFilter2DEXT) (GLenum, GLenum, GLsizei, GLsizei, GLenum, GLenum, const void*, const void*);
extern pfn_glSeparableFilter2DEXT fp_glSeparableFilter2DEXT;

 /* GL_EXT_coordinate_frame */
extern GLboolean GLAD_EXT_coordinate_frame;
#define GL_TANGENT_ARRAY_EXT                   0x8439
#define GL_BINORMAL_ARRAY_EXT                  0x843A
#define GL_CURRENT_TANGENT_EXT                 0x843B
#define GL_CURRENT_BINORMAL_EXT                0x843C
#define GL_TANGENT_ARRAY_TYPE_EXT              0x843E
#define GL_TANGENT_ARRAY_STRIDE_EXT            0x843F
#define GL_BINORMAL_ARRAY_TYPE_EXT             0x8440
#define GL_BINORMAL_ARRAY_STRIDE_EXT           0x8441
#define GL_TANGENT_ARRAY_POINTER_EXT           0x8442
#define GL_BINORMAL_ARRAY_POINTER_EXT          0x8443
#define GL_MAP1_TANGENT_EXT                    0x8444
#define GL_MAP2_TANGENT_EXT                    0x8445
#define GL_MAP1_BINORMAL_EXT                   0x8446
#define GL_MAP2_BINORMAL_EXT                   0x8447
typedef void (APIENTRYP pfn_glTangent3bEXT) (GLbyte, GLbyte, GLbyte);
extern pfn_glTangent3bEXT fp_glTangent3bEXT;
typedef void (APIENTRYP pfn_glTangent3bvEXT) (const GLbyte*);
extern pfn_glTangent3bvEXT fp_glTangent3bvEXT;
typedef void (APIENTRYP pfn_glTangent3dEXT) (GLdouble, GLdouble, GLdouble);
extern pfn_glTangent3dEXT fp_glTangent3dEXT;
typedef void (APIENTRYP pfn_glTangent3dvEXT) (const GLdouble*);
extern pfn_glTangent3dvEXT fp_glTangent3dvEXT;
typedef void (APIENTRYP pfn_glTangent3fEXT) (GLfloat, GLfloat, GLfloat);
extern pfn_glTangent3fEXT fp_glTangent3fEXT;
typedef void (APIENTRYP pfn_glTangent3fvEXT) (const GLfloat*);
extern pfn_glTangent3fvEXT fp_glTangent3fvEXT;
typedef void (APIENTRYP pfn_glTangent3iEXT) (GLint, GLint, GLint);
extern pfn_glTangent3iEXT fp_glTangent3iEXT;
typedef void (APIENTRYP pfn_glTangent3ivEXT) (const GLint*);
extern pfn_glTangent3ivEXT fp_glTangent3ivEXT;
typedef void (APIENTRYP pfn_glTangent3sEXT) (GLshort, GLshort, GLshort);
extern pfn_glTangent3sEXT fp_glTangent3sEXT;
typedef void (APIENTRYP pfn_glTangent3svEXT) (const GLshort*);
extern pfn_glTangent3svEXT fp_glTangent3svEXT;
typedef void (APIENTRYP pfn_glBinormal3bEXT) (GLbyte, GLbyte, GLbyte);
extern pfn_glBinormal3bEXT fp_glBinormal3bEXT;
typedef void (APIENTRYP pfn_glBinormal3bvEXT) (const GLbyte*);
extern pfn_glBinormal3bvEXT fp_glBinormal3bvEXT;
typedef void (APIENTRYP pfn_glBinormal3dEXT) (GLdouble, GLdouble, GLdouble);
extern pfn_glBinormal3dEXT fp_glBinormal3dEXT;
typedef void (APIENTRYP pfn_glBinormal3dvEXT) (const GLdouble*);
extern pfn_glBinormal3dvEXT fp_glBinormal3dvEXT;
typedef void (APIENTRYP pfn_glBinormal3fEXT) (GLfloat, GLfloat, GLfloat);
extern pfn_glBinormal3fEXT fp_glBinormal3fEXT;
typedef void (APIENTRYP pfn_glBinormal3fvEXT) (const GLfloat*);
extern pfn_glBinormal3fvEXT fp_glBinormal3fvEXT;
typedef void (APIENTRYP pfn_glBinormal3iEXT) (GLint, GLint, GLint);
extern pfn_glBinormal3iEXT fp_glBinormal3iEXT;
typedef void (APIENTRYP pfn_glBinormal3ivEXT) (const GLint*);
extern pfn_glBinormal3ivEXT fp_glBinormal3ivEXT;
typedef void (APIENTRYP pfn_glBinormal3sEXT) (GLshort, GLshort, GLshort);
extern pfn_glBinormal3sEXT fp_glBinormal3sEXT;
typedef void (APIENTRYP pfn_glBinormal3svEXT) (const GLshort*);
extern pfn_glBinormal3svEXT fp_glBinormal3svEXT;
typedef void (APIENTRYP pfn_glTangentPointerEXT) (GLenum, GLsizei, const void*);
extern pfn_glTangentPointerEXT fp_glTangentPointerEXT;
typedef void (APIENTRYP pfn_glBinormalPointerEXT) (GLenum, GLsizei, const void*);
extern pfn_glBinormalPointerEXT fp_glBinormalPointerEXT;

 /* GL_EXT_cull_vertex */
extern GLboolean GLAD_EXT_cull_vertex;
#define GL_CULL_VERTEX_EXT                     0x81AA
#define GL_CULL_VERTEX_EYE_POSITION_EXT        0x81AB
#define GL_CULL_VERTEX_OBJECT_POSITION_EXT     0x81AC
typedef void (APIENTRYP pfn_glCullParameterdvEXT) (GLenum, GLdouble*);
extern pfn_glCullParameterdvEXT fp_glCullParameterdvEXT;
typedef void (APIENTRYP pfn_glCullParameterfvEXT) (GLenum, GLfloat*);
extern pfn_glCullParameterfvEXT fp_glCullParameterfvEXT;

 /* GL_EXT_debug_label */
extern GLboolean GLAD_EXT_debug_label;
#define GL_PROGRAM_PIPELINE_OBJECT_EXT         0x8A4F
#define GL_PROGRAM_OBJECT_EXT                  0x8B40
#define GL_SHADER_OBJECT_EXT                   0x8B48
#define GL_BUFFER_OBJECT_EXT                   0x9151
#define GL_QUERY_OBJECT_EXT                    0x9153
#define GL_VERTEX_ARRAY_OBJECT_EXT             0x9154
typedef void (APIENTRYP pfn_glLabelObjectEXT) (GLenum, GLuint, GLsizei, const GLchar*);
extern pfn_glLabelObjectEXT fp_glLabelObjectEXT;
typedef void (APIENTRYP pfn_glGetObjectLabelEXT) (GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetObjectLabelEXT fp_glGetObjectLabelEXT;

 /* GL_EXT_debug_marker */
extern GLboolean GLAD_EXT_debug_marker;
typedef void (APIENTRYP pfn_glInsertEventMarkerEXT) (GLsizei, const GLchar*);
extern pfn_glInsertEventMarkerEXT fp_glInsertEventMarkerEXT;
typedef void (APIENTRYP pfn_glPushGroupMarkerEXT) (GLsizei, const GLchar*);
extern pfn_glPushGroupMarkerEXT fp_glPushGroupMarkerEXT;
typedef void (APIENTRYP pfn_glPopGroupMarkerEXT) ();
extern pfn_glPopGroupMarkerEXT fp_glPopGroupMarkerEXT;

 /* GL_EXT_depth_bounds_test */
extern GLboolean GLAD_EXT_depth_bounds_test;
#define GL_DEPTH_BOUNDS_TEST_EXT               0x8890
#define GL_DEPTH_BOUNDS_EXT                    0x8891
typedef void (APIENTRYP pfn_glDepthBoundsEXT) (GLclampd, GLclampd);
extern pfn_glDepthBoundsEXT fp_glDepthBoundsEXT;

 /* GL_EXT_direct_state_access */
extern GLboolean GLAD_EXT_direct_state_access;
#define GL_PROGRAM_MATRIX_EXT                  0x8E2D
#define GL_TRANSPOSE_PROGRAM_MATRIX_EXT        0x8E2E
#define GL_PROGRAM_MATRIX_STACK_DEPTH_EXT      0x8E2F
typedef void (APIENTRYP pfn_glMatrixLoadfEXT) (GLenum, const GLfloat*);
extern pfn_glMatrixLoadfEXT fp_glMatrixLoadfEXT;
typedef void (APIENTRYP pfn_glMatrixLoaddEXT) (GLenum, const GLdouble*);
extern pfn_glMatrixLoaddEXT fp_glMatrixLoaddEXT;
typedef void (APIENTRYP pfn_glMatrixMultfEXT) (GLenum, const GLfloat*);
extern pfn_glMatrixMultfEXT fp_glMatrixMultfEXT;
typedef void (APIENTRYP pfn_glMatrixMultdEXT) (GLenum, const GLdouble*);
extern pfn_glMatrixMultdEXT fp_glMatrixMultdEXT;
typedef void (APIENTRYP pfn_glMatrixLoadIdentityEXT) (GLenum);
extern pfn_glMatrixLoadIdentityEXT fp_glMatrixLoadIdentityEXT;
typedef void (APIENTRYP pfn_glMatrixRotatefEXT) (GLenum, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glMatrixRotatefEXT fp_glMatrixRotatefEXT;
typedef void (APIENTRYP pfn_glMatrixRotatedEXT) (GLenum, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glMatrixRotatedEXT fp_glMatrixRotatedEXT;
typedef void (APIENTRYP pfn_glMatrixScalefEXT) (GLenum, GLfloat, GLfloat, GLfloat);
extern pfn_glMatrixScalefEXT fp_glMatrixScalefEXT;
typedef void (APIENTRYP pfn_glMatrixScaledEXT) (GLenum, GLdouble, GLdouble, GLdouble);
extern pfn_glMatrixScaledEXT fp_glMatrixScaledEXT;
typedef void (APIENTRYP pfn_glMatrixTranslatefEXT) (GLenum, GLfloat, GLfloat, GLfloat);
extern pfn_glMatrixTranslatefEXT fp_glMatrixTranslatefEXT;
typedef void (APIENTRYP pfn_glMatrixTranslatedEXT) (GLenum, GLdouble, GLdouble, GLdouble);
extern pfn_glMatrixTranslatedEXT fp_glMatrixTranslatedEXT;
typedef void (APIENTRYP pfn_glMatrixFrustumEXT) (GLenum, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glMatrixFrustumEXT fp_glMatrixFrustumEXT;
typedef void (APIENTRYP pfn_glMatrixOrthoEXT) (GLenum, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glMatrixOrthoEXT fp_glMatrixOrthoEXT;
typedef void (APIENTRYP pfn_glMatrixPopEXT) (GLenum);
extern pfn_glMatrixPopEXT fp_glMatrixPopEXT;
typedef void (APIENTRYP pfn_glMatrixPushEXT) (GLenum);
extern pfn_glMatrixPushEXT fp_glMatrixPushEXT;
typedef void (APIENTRYP pfn_glClientAttribDefaultEXT) (GLbitfield);
extern pfn_glClientAttribDefaultEXT fp_glClientAttribDefaultEXT;
typedef void (APIENTRYP pfn_glPushClientAttribDefaultEXT) (GLbitfield);
extern pfn_glPushClientAttribDefaultEXT fp_glPushClientAttribDefaultEXT;
typedef void (APIENTRYP pfn_glTextureParameterfEXT) (GLuint, GLenum, GLenum, GLfloat);
extern pfn_glTextureParameterfEXT fp_glTextureParameterfEXT;
typedef void (APIENTRYP pfn_glTextureParameterfvEXT) (GLuint, GLenum, GLenum, const GLfloat*);
extern pfn_glTextureParameterfvEXT fp_glTextureParameterfvEXT;
typedef void (APIENTRYP pfn_glTextureParameteriEXT) (GLuint, GLenum, GLenum, GLint);
extern pfn_glTextureParameteriEXT fp_glTextureParameteriEXT;
typedef void (APIENTRYP pfn_glTextureParameterivEXT) (GLuint, GLenum, GLenum, const GLint*);
extern pfn_glTextureParameterivEXT fp_glTextureParameterivEXT;
typedef void (APIENTRYP pfn_glTextureImage1DEXT) (GLuint, GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void*);
extern pfn_glTextureImage1DEXT fp_glTextureImage1DEXT;
typedef void (APIENTRYP pfn_glTextureImage2DEXT) (GLuint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
extern pfn_glTextureImage2DEXT fp_glTextureImage2DEXT;
typedef void (APIENTRYP pfn_glTextureSubImage1DEXT) (GLuint, GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void*);
extern pfn_glTextureSubImage1DEXT fp_glTextureSubImage1DEXT;
typedef void (APIENTRYP pfn_glTextureSubImage2DEXT) (GLuint, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glTextureSubImage2DEXT fp_glTextureSubImage2DEXT;
typedef void (APIENTRYP pfn_glCopyTextureImage1DEXT) (GLuint, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
extern pfn_glCopyTextureImage1DEXT fp_glCopyTextureImage1DEXT;
typedef void (APIENTRYP pfn_glCopyTextureImage2DEXT) (GLuint, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
extern pfn_glCopyTextureImage2DEXT fp_glCopyTextureImage2DEXT;
typedef void (APIENTRYP pfn_glCopyTextureSubImage1DEXT) (GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei);
extern pfn_glCopyTextureSubImage1DEXT fp_glCopyTextureSubImage1DEXT;
typedef void (APIENTRYP pfn_glCopyTextureSubImage2DEXT) (GLuint, GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
extern pfn_glCopyTextureSubImage2DEXT fp_glCopyTextureSubImage2DEXT;
typedef void (APIENTRYP pfn_glGetTextureImageEXT) (GLuint, GLenum, GLint, GLenum, GLenum, void*);
extern pfn_glGetTextureImageEXT fp_glGetTextureImageEXT;
typedef void (APIENTRYP pfn_glGetTextureParameterfvEXT) (GLuint, GLenum, GLenum, GLfloat*);
extern pfn_glGetTextureParameterfvEXT fp_glGetTextureParameterfvEXT;
typedef void (APIENTRYP pfn_glGetTextureParameterivEXT) (GLuint, GLenum, GLenum, GLint*);
extern pfn_glGetTextureParameterivEXT fp_glGetTextureParameterivEXT;
typedef void (APIENTRYP pfn_glGetTextureLevelParameterfvEXT) (GLuint, GLenum, GLint, GLenum, GLfloat*);
extern pfn_glGetTextureLevelParameterfvEXT fp_glGetTextureLevelParameterfvEXT;
typedef void (APIENTRYP pfn_glGetTextureLevelParameterivEXT) (GLuint, GLenum, GLint, GLenum, GLint*);
extern pfn_glGetTextureLevelParameterivEXT fp_glGetTextureLevelParameterivEXT;
typedef void (APIENTRYP pfn_glTextureImage3DEXT) (GLuint, GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
extern pfn_glTextureImage3DEXT fp_glTextureImage3DEXT;
typedef void (APIENTRYP pfn_glTextureSubImage3DEXT) (GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glTextureSubImage3DEXT fp_glTextureSubImage3DEXT;
typedef void (APIENTRYP pfn_glCopyTextureSubImage3DEXT) (GLuint, GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
extern pfn_glCopyTextureSubImage3DEXT fp_glCopyTextureSubImage3DEXT;
typedef void (APIENTRYP pfn_glBindMultiTextureEXT) (GLenum, GLenum, GLuint);
extern pfn_glBindMultiTextureEXT fp_glBindMultiTextureEXT;
typedef void (APIENTRYP pfn_glMultiTexCoordPointerEXT) (GLenum, GLint, GLenum, GLsizei, const void*);
extern pfn_glMultiTexCoordPointerEXT fp_glMultiTexCoordPointerEXT;
typedef void (APIENTRYP pfn_glMultiTexEnvfEXT) (GLenum, GLenum, GLenum, GLfloat);
extern pfn_glMultiTexEnvfEXT fp_glMultiTexEnvfEXT;
typedef void (APIENTRYP pfn_glMultiTexEnvfvEXT) (GLenum, GLenum, GLenum, const GLfloat*);
extern pfn_glMultiTexEnvfvEXT fp_glMultiTexEnvfvEXT;
typedef void (APIENTRYP pfn_glMultiTexEnviEXT) (GLenum, GLenum, GLenum, GLint);
extern pfn_glMultiTexEnviEXT fp_glMultiTexEnviEXT;
typedef void (APIENTRYP pfn_glMultiTexEnvivEXT) (GLenum, GLenum, GLenum, const GLint*);
extern pfn_glMultiTexEnvivEXT fp_glMultiTexEnvivEXT;
typedef void (APIENTRYP pfn_glMultiTexGendEXT) (GLenum, GLenum, GLenum, GLdouble);
extern pfn_glMultiTexGendEXT fp_glMultiTexGendEXT;
typedef void (APIENTRYP pfn_glMultiTexGendvEXT) (GLenum, GLenum, GLenum, const GLdouble*);
extern pfn_glMultiTexGendvEXT fp_glMultiTexGendvEXT;
typedef void (APIENTRYP pfn_glMultiTexGenfEXT) (GLenum, GLenum, GLenum, GLfloat);
extern pfn_glMultiTexGenfEXT fp_glMultiTexGenfEXT;
typedef void (APIENTRYP pfn_glMultiTexGenfvEXT) (GLenum, GLenum, GLenum, const GLfloat*);
extern pfn_glMultiTexGenfvEXT fp_glMultiTexGenfvEXT;
typedef void (APIENTRYP pfn_glMultiTexGeniEXT) (GLenum, GLenum, GLenum, GLint);
extern pfn_glMultiTexGeniEXT fp_glMultiTexGeniEXT;
typedef void (APIENTRYP pfn_glMultiTexGenivEXT) (GLenum, GLenum, GLenum, const GLint*);
extern pfn_glMultiTexGenivEXT fp_glMultiTexGenivEXT;
typedef void (APIENTRYP pfn_glGetMultiTexEnvfvEXT) (GLenum, GLenum, GLenum, GLfloat*);
extern pfn_glGetMultiTexEnvfvEXT fp_glGetMultiTexEnvfvEXT;
typedef void (APIENTRYP pfn_glGetMultiTexEnvivEXT) (GLenum, GLenum, GLenum, GLint*);
extern pfn_glGetMultiTexEnvivEXT fp_glGetMultiTexEnvivEXT;
typedef void (APIENTRYP pfn_glGetMultiTexGendvEXT) (GLenum, GLenum, GLenum, GLdouble*);
extern pfn_glGetMultiTexGendvEXT fp_glGetMultiTexGendvEXT;
typedef void (APIENTRYP pfn_glGetMultiTexGenfvEXT) (GLenum, GLenum, GLenum, GLfloat*);
extern pfn_glGetMultiTexGenfvEXT fp_glGetMultiTexGenfvEXT;
typedef void (APIENTRYP pfn_glGetMultiTexGenivEXT) (GLenum, GLenum, GLenum, GLint*);
extern pfn_glGetMultiTexGenivEXT fp_glGetMultiTexGenivEXT;
typedef void (APIENTRYP pfn_glMultiTexParameteriEXT) (GLenum, GLenum, GLenum, GLint);
extern pfn_glMultiTexParameteriEXT fp_glMultiTexParameteriEXT;
typedef void (APIENTRYP pfn_glMultiTexParameterivEXT) (GLenum, GLenum, GLenum, const GLint*);
extern pfn_glMultiTexParameterivEXT fp_glMultiTexParameterivEXT;
typedef void (APIENTRYP pfn_glMultiTexParameterfEXT) (GLenum, GLenum, GLenum, GLfloat);
extern pfn_glMultiTexParameterfEXT fp_glMultiTexParameterfEXT;
typedef void (APIENTRYP pfn_glMultiTexParameterfvEXT) (GLenum, GLenum, GLenum, const GLfloat*);
extern pfn_glMultiTexParameterfvEXT fp_glMultiTexParameterfvEXT;
typedef void (APIENTRYP pfn_glMultiTexImage1DEXT) (GLenum, GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void*);
extern pfn_glMultiTexImage1DEXT fp_glMultiTexImage1DEXT;
typedef void (APIENTRYP pfn_glMultiTexImage2DEXT) (GLenum, GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
extern pfn_glMultiTexImage2DEXT fp_glMultiTexImage2DEXT;
typedef void (APIENTRYP pfn_glMultiTexSubImage1DEXT) (GLenum, GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void*);
extern pfn_glMultiTexSubImage1DEXT fp_glMultiTexSubImage1DEXT;
typedef void (APIENTRYP pfn_glMultiTexSubImage2DEXT) (GLenum, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glMultiTexSubImage2DEXT fp_glMultiTexSubImage2DEXT;
typedef void (APIENTRYP pfn_glCopyMultiTexImage1DEXT) (GLenum, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
extern pfn_glCopyMultiTexImage1DEXT fp_glCopyMultiTexImage1DEXT;
typedef void (APIENTRYP pfn_glCopyMultiTexImage2DEXT) (GLenum, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
extern pfn_glCopyMultiTexImage2DEXT fp_glCopyMultiTexImage2DEXT;
typedef void (APIENTRYP pfn_glCopyMultiTexSubImage1DEXT) (GLenum, GLenum, GLint, GLint, GLint, GLint, GLsizei);
extern pfn_glCopyMultiTexSubImage1DEXT fp_glCopyMultiTexSubImage1DEXT;
typedef void (APIENTRYP pfn_glCopyMultiTexSubImage2DEXT) (GLenum, GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
extern pfn_glCopyMultiTexSubImage2DEXT fp_glCopyMultiTexSubImage2DEXT;
typedef void (APIENTRYP pfn_glGetMultiTexImageEXT) (GLenum, GLenum, GLint, GLenum, GLenum, void*);
extern pfn_glGetMultiTexImageEXT fp_glGetMultiTexImageEXT;
typedef void (APIENTRYP pfn_glGetMultiTexParameterfvEXT) (GLenum, GLenum, GLenum, GLfloat*);
extern pfn_glGetMultiTexParameterfvEXT fp_glGetMultiTexParameterfvEXT;
typedef void (APIENTRYP pfn_glGetMultiTexParameterivEXT) (GLenum, GLenum, GLenum, GLint*);
extern pfn_glGetMultiTexParameterivEXT fp_glGetMultiTexParameterivEXT;
typedef void (APIENTRYP pfn_glGetMultiTexLevelParameterfvEXT) (GLenum, GLenum, GLint, GLenum, GLfloat*);
extern pfn_glGetMultiTexLevelParameterfvEXT fp_glGetMultiTexLevelParameterfvEXT;
typedef void (APIENTRYP pfn_glGetMultiTexLevelParameterivEXT) (GLenum, GLenum, GLint, GLenum, GLint*);
extern pfn_glGetMultiTexLevelParameterivEXT fp_glGetMultiTexLevelParameterivEXT;
typedef void (APIENTRYP pfn_glMultiTexImage3DEXT) (GLenum, GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
extern pfn_glMultiTexImage3DEXT fp_glMultiTexImage3DEXT;
typedef void (APIENTRYP pfn_glMultiTexSubImage3DEXT) (GLenum, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glMultiTexSubImage3DEXT fp_glMultiTexSubImage3DEXT;
typedef void (APIENTRYP pfn_glCopyMultiTexSubImage3DEXT) (GLenum, GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
extern pfn_glCopyMultiTexSubImage3DEXT fp_glCopyMultiTexSubImage3DEXT;
typedef void (APIENTRYP pfn_glEnableClientStateIndexedEXT) (GLenum, GLuint);
extern pfn_glEnableClientStateIndexedEXT fp_glEnableClientStateIndexedEXT;
typedef void (APIENTRYP pfn_glDisableClientStateIndexedEXT) (GLenum, GLuint);
extern pfn_glDisableClientStateIndexedEXT fp_glDisableClientStateIndexedEXT;
typedef void (APIENTRYP pfn_glGetFloatIndexedvEXT) (GLenum, GLuint, GLfloat*);
extern pfn_glGetFloatIndexedvEXT fp_glGetFloatIndexedvEXT;
typedef void (APIENTRYP pfn_glGetDoubleIndexedvEXT) (GLenum, GLuint, GLdouble*);
extern pfn_glGetDoubleIndexedvEXT fp_glGetDoubleIndexedvEXT;
typedef void (APIENTRYP pfn_glGetPointerIndexedvEXT) (GLenum, GLuint, void**);
extern pfn_glGetPointerIndexedvEXT fp_glGetPointerIndexedvEXT;
typedef void (APIENTRYP pfn_glEnableIndexedEXT) (GLenum, GLuint);
extern pfn_glEnableIndexedEXT fp_glEnableIndexedEXT;
typedef void (APIENTRYP pfn_glDisableIndexedEXT) (GLenum, GLuint);
extern pfn_glDisableIndexedEXT fp_glDisableIndexedEXT;
typedef GLboolean (APIENTRYP pfn_glIsEnabledIndexedEXT) (GLenum, GLuint);
extern pfn_glIsEnabledIndexedEXT fp_glIsEnabledIndexedEXT;
typedef void (APIENTRYP pfn_glGetIntegerIndexedvEXT) (GLenum, GLuint, GLint*);
extern pfn_glGetIntegerIndexedvEXT fp_glGetIntegerIndexedvEXT;
typedef void (APIENTRYP pfn_glGetBooleanIndexedvEXT) (GLenum, GLuint, GLboolean*);
extern pfn_glGetBooleanIndexedvEXT fp_glGetBooleanIndexedvEXT;
typedef void (APIENTRYP pfn_glCompressedTextureImage3DEXT) (GLuint, GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedTextureImage3DEXT fp_glCompressedTextureImage3DEXT;
typedef void (APIENTRYP pfn_glCompressedTextureImage2DEXT) (GLuint, GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedTextureImage2DEXT fp_glCompressedTextureImage2DEXT;
typedef void (APIENTRYP pfn_glCompressedTextureImage1DEXT) (GLuint, GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedTextureImage1DEXT fp_glCompressedTextureImage1DEXT;
typedef void (APIENTRYP pfn_glCompressedTextureSubImage3DEXT) (GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedTextureSubImage3DEXT fp_glCompressedTextureSubImage3DEXT;
typedef void (APIENTRYP pfn_glCompressedTextureSubImage2DEXT) (GLuint, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedTextureSubImage2DEXT fp_glCompressedTextureSubImage2DEXT;
typedef void (APIENTRYP pfn_glCompressedTextureSubImage1DEXT) (GLuint, GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedTextureSubImage1DEXT fp_glCompressedTextureSubImage1DEXT;
typedef void (APIENTRYP pfn_glGetCompressedTextureImageEXT) (GLuint, GLenum, GLint, void*);
extern pfn_glGetCompressedTextureImageEXT fp_glGetCompressedTextureImageEXT;
typedef void (APIENTRYP pfn_glCompressedMultiTexImage3DEXT) (GLenum, GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedMultiTexImage3DEXT fp_glCompressedMultiTexImage3DEXT;
typedef void (APIENTRYP pfn_glCompressedMultiTexImage2DEXT) (GLenum, GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedMultiTexImage2DEXT fp_glCompressedMultiTexImage2DEXT;
typedef void (APIENTRYP pfn_glCompressedMultiTexImage1DEXT) (GLenum, GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedMultiTexImage1DEXT fp_glCompressedMultiTexImage1DEXT;
typedef void (APIENTRYP pfn_glCompressedMultiTexSubImage3DEXT) (GLenum, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedMultiTexSubImage3DEXT fp_glCompressedMultiTexSubImage3DEXT;
typedef void (APIENTRYP pfn_glCompressedMultiTexSubImage2DEXT) (GLenum, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedMultiTexSubImage2DEXT fp_glCompressedMultiTexSubImage2DEXT;
typedef void (APIENTRYP pfn_glCompressedMultiTexSubImage1DEXT) (GLenum, GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedMultiTexSubImage1DEXT fp_glCompressedMultiTexSubImage1DEXT;
typedef void (APIENTRYP pfn_glGetCompressedMultiTexImageEXT) (GLenum, GLenum, GLint, void*);
extern pfn_glGetCompressedMultiTexImageEXT fp_glGetCompressedMultiTexImageEXT;
typedef void (APIENTRYP pfn_glMatrixLoadTransposefEXT) (GLenum, const GLfloat*);
extern pfn_glMatrixLoadTransposefEXT fp_glMatrixLoadTransposefEXT;
typedef void (APIENTRYP pfn_glMatrixLoadTransposedEXT) (GLenum, const GLdouble*);
extern pfn_glMatrixLoadTransposedEXT fp_glMatrixLoadTransposedEXT;
typedef void (APIENTRYP pfn_glMatrixMultTransposefEXT) (GLenum, const GLfloat*);
extern pfn_glMatrixMultTransposefEXT fp_glMatrixMultTransposefEXT;
typedef void (APIENTRYP pfn_glMatrixMultTransposedEXT) (GLenum, const GLdouble*);
extern pfn_glMatrixMultTransposedEXT fp_glMatrixMultTransposedEXT;
typedef void (APIENTRYP pfn_glNamedBufferDataEXT) (GLuint, GLsizeiptr, const void*, GLenum);
extern pfn_glNamedBufferDataEXT fp_glNamedBufferDataEXT;
typedef void (APIENTRYP pfn_glNamedBufferSubDataEXT) (GLuint, GLintptr, GLsizeiptr, const void*);
extern pfn_glNamedBufferSubDataEXT fp_glNamedBufferSubDataEXT;
typedef void* (APIENTRYP pfn_glMapNamedBufferEXT) (GLuint, GLenum);
extern pfn_glMapNamedBufferEXT fp_glMapNamedBufferEXT;
typedef GLboolean (APIENTRYP pfn_glUnmapNamedBufferEXT) (GLuint);
extern pfn_glUnmapNamedBufferEXT fp_glUnmapNamedBufferEXT;
typedef void (APIENTRYP pfn_glGetNamedBufferParameterivEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetNamedBufferParameterivEXT fp_glGetNamedBufferParameterivEXT;
typedef void (APIENTRYP pfn_glGetNamedBufferPointervEXT) (GLuint, GLenum, void**);
extern pfn_glGetNamedBufferPointervEXT fp_glGetNamedBufferPointervEXT;
typedef void (APIENTRYP pfn_glGetNamedBufferSubDataEXT) (GLuint, GLintptr, GLsizeiptr, void*);
extern pfn_glGetNamedBufferSubDataEXT fp_glGetNamedBufferSubDataEXT;
typedef void (APIENTRYP pfn_glProgramUniform1fEXT) (GLuint, GLint, GLfloat);
extern pfn_glProgramUniform1fEXT fp_glProgramUniform1fEXT;
typedef void (APIENTRYP pfn_glProgramUniform2fEXT) (GLuint, GLint, GLfloat, GLfloat);
extern pfn_glProgramUniform2fEXT fp_glProgramUniform2fEXT;
typedef void (APIENTRYP pfn_glProgramUniform3fEXT) (GLuint, GLint, GLfloat, GLfloat, GLfloat);
extern pfn_glProgramUniform3fEXT fp_glProgramUniform3fEXT;
typedef void (APIENTRYP pfn_glProgramUniform4fEXT) (GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glProgramUniform4fEXT fp_glProgramUniform4fEXT;
typedef void (APIENTRYP pfn_glProgramUniform1iEXT) (GLuint, GLint, GLint);
extern pfn_glProgramUniform1iEXT fp_glProgramUniform1iEXT;
typedef void (APIENTRYP pfn_glProgramUniform2iEXT) (GLuint, GLint, GLint, GLint);
extern pfn_glProgramUniform2iEXT fp_glProgramUniform2iEXT;
typedef void (APIENTRYP pfn_glProgramUniform3iEXT) (GLuint, GLint, GLint, GLint, GLint);
extern pfn_glProgramUniform3iEXT fp_glProgramUniform3iEXT;
typedef void (APIENTRYP pfn_glProgramUniform4iEXT) (GLuint, GLint, GLint, GLint, GLint, GLint);
extern pfn_glProgramUniform4iEXT fp_glProgramUniform4iEXT;
typedef void (APIENTRYP pfn_glProgramUniform1fvEXT) (GLuint, GLint, GLsizei, const GLfloat*);
extern pfn_glProgramUniform1fvEXT fp_glProgramUniform1fvEXT;
typedef void (APIENTRYP pfn_glProgramUniform2fvEXT) (GLuint, GLint, GLsizei, const GLfloat*);
extern pfn_glProgramUniform2fvEXT fp_glProgramUniform2fvEXT;
typedef void (APIENTRYP pfn_glProgramUniform3fvEXT) (GLuint, GLint, GLsizei, const GLfloat*);
extern pfn_glProgramUniform3fvEXT fp_glProgramUniform3fvEXT;
typedef void (APIENTRYP pfn_glProgramUniform4fvEXT) (GLuint, GLint, GLsizei, const GLfloat*);
extern pfn_glProgramUniform4fvEXT fp_glProgramUniform4fvEXT;
typedef void (APIENTRYP pfn_glProgramUniform1ivEXT) (GLuint, GLint, GLsizei, const GLint*);
extern pfn_glProgramUniform1ivEXT fp_glProgramUniform1ivEXT;
typedef void (APIENTRYP pfn_glProgramUniform2ivEXT) (GLuint, GLint, GLsizei, const GLint*);
extern pfn_glProgramUniform2ivEXT fp_glProgramUniform2ivEXT;
typedef void (APIENTRYP pfn_glProgramUniform3ivEXT) (GLuint, GLint, GLsizei, const GLint*);
extern pfn_glProgramUniform3ivEXT fp_glProgramUniform3ivEXT;
typedef void (APIENTRYP pfn_glProgramUniform4ivEXT) (GLuint, GLint, GLsizei, const GLint*);
extern pfn_glProgramUniform4ivEXT fp_glProgramUniform4ivEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2fvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix2fvEXT fp_glProgramUniformMatrix2fvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3fvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix3fvEXT fp_glProgramUniformMatrix3fvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4fvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix4fvEXT fp_glProgramUniformMatrix4fvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2x3fvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix2x3fvEXT fp_glProgramUniformMatrix2x3fvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3x2fvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix3x2fvEXT fp_glProgramUniformMatrix3x2fvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2x4fvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix2x4fvEXT fp_glProgramUniformMatrix2x4fvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4x2fvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix4x2fvEXT fp_glProgramUniformMatrix4x2fvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3x4fvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix3x4fvEXT fp_glProgramUniformMatrix3x4fvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4x3fvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glProgramUniformMatrix4x3fvEXT fp_glProgramUniformMatrix4x3fvEXT;
typedef void (APIENTRYP pfn_glTextureBufferEXT) (GLuint, GLenum, GLenum, GLuint);
extern pfn_glTextureBufferEXT fp_glTextureBufferEXT;
typedef void (APIENTRYP pfn_glMultiTexBufferEXT) (GLenum, GLenum, GLenum, GLuint);
extern pfn_glMultiTexBufferEXT fp_glMultiTexBufferEXT;
typedef void (APIENTRYP pfn_glTextureParameterIivEXT) (GLuint, GLenum, GLenum, const GLint*);
extern pfn_glTextureParameterIivEXT fp_glTextureParameterIivEXT;
typedef void (APIENTRYP pfn_glTextureParameterIuivEXT) (GLuint, GLenum, GLenum, const GLuint*);
extern pfn_glTextureParameterIuivEXT fp_glTextureParameterIuivEXT;
typedef void (APIENTRYP pfn_glGetTextureParameterIivEXT) (GLuint, GLenum, GLenum, GLint*);
extern pfn_glGetTextureParameterIivEXT fp_glGetTextureParameterIivEXT;
typedef void (APIENTRYP pfn_glGetTextureParameterIuivEXT) (GLuint, GLenum, GLenum, GLuint*);
extern pfn_glGetTextureParameterIuivEXT fp_glGetTextureParameterIuivEXT;
typedef void (APIENTRYP pfn_glMultiTexParameterIivEXT) (GLenum, GLenum, GLenum, const GLint*);
extern pfn_glMultiTexParameterIivEXT fp_glMultiTexParameterIivEXT;
typedef void (APIENTRYP pfn_glMultiTexParameterIuivEXT) (GLenum, GLenum, GLenum, const GLuint*);
extern pfn_glMultiTexParameterIuivEXT fp_glMultiTexParameterIuivEXT;
typedef void (APIENTRYP pfn_glGetMultiTexParameterIivEXT) (GLenum, GLenum, GLenum, GLint*);
extern pfn_glGetMultiTexParameterIivEXT fp_glGetMultiTexParameterIivEXT;
typedef void (APIENTRYP pfn_glGetMultiTexParameterIuivEXT) (GLenum, GLenum, GLenum, GLuint*);
extern pfn_glGetMultiTexParameterIuivEXT fp_glGetMultiTexParameterIuivEXT;
typedef void (APIENTRYP pfn_glProgramUniform1uiEXT) (GLuint, GLint, GLuint);
extern pfn_glProgramUniform1uiEXT fp_glProgramUniform1uiEXT;
typedef void (APIENTRYP pfn_glProgramUniform2uiEXT) (GLuint, GLint, GLuint, GLuint);
extern pfn_glProgramUniform2uiEXT fp_glProgramUniform2uiEXT;
typedef void (APIENTRYP pfn_glProgramUniform3uiEXT) (GLuint, GLint, GLuint, GLuint, GLuint);
extern pfn_glProgramUniform3uiEXT fp_glProgramUniform3uiEXT;
typedef void (APIENTRYP pfn_glProgramUniform4uiEXT) (GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glProgramUniform4uiEXT fp_glProgramUniform4uiEXT;
typedef void (APIENTRYP pfn_glProgramUniform1uivEXT) (GLuint, GLint, GLsizei, const GLuint*);
extern pfn_glProgramUniform1uivEXT fp_glProgramUniform1uivEXT;
typedef void (APIENTRYP pfn_glProgramUniform2uivEXT) (GLuint, GLint, GLsizei, const GLuint*);
extern pfn_glProgramUniform2uivEXT fp_glProgramUniform2uivEXT;
typedef void (APIENTRYP pfn_glProgramUniform3uivEXT) (GLuint, GLint, GLsizei, const GLuint*);
extern pfn_glProgramUniform3uivEXT fp_glProgramUniform3uivEXT;
typedef void (APIENTRYP pfn_glProgramUniform4uivEXT) (GLuint, GLint, GLsizei, const GLuint*);
extern pfn_glProgramUniform4uivEXT fp_glProgramUniform4uivEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParameters4fvEXT) (GLuint, GLenum, GLuint, GLsizei, const GLfloat*);
extern pfn_glNamedProgramLocalParameters4fvEXT fp_glNamedProgramLocalParameters4fvEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParameterI4iEXT) (GLuint, GLenum, GLuint, GLint, GLint, GLint, GLint);
extern pfn_glNamedProgramLocalParameterI4iEXT fp_glNamedProgramLocalParameterI4iEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParameterI4ivEXT) (GLuint, GLenum, GLuint, const GLint*);
extern pfn_glNamedProgramLocalParameterI4ivEXT fp_glNamedProgramLocalParameterI4ivEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParametersI4ivEXT) (GLuint, GLenum, GLuint, GLsizei, const GLint*);
extern pfn_glNamedProgramLocalParametersI4ivEXT fp_glNamedProgramLocalParametersI4ivEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParameterI4uiEXT) (GLuint, GLenum, GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glNamedProgramLocalParameterI4uiEXT fp_glNamedProgramLocalParameterI4uiEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParameterI4uivEXT) (GLuint, GLenum, GLuint, const GLuint*);
extern pfn_glNamedProgramLocalParameterI4uivEXT fp_glNamedProgramLocalParameterI4uivEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParametersI4uivEXT) (GLuint, GLenum, GLuint, GLsizei, const GLuint*);
extern pfn_glNamedProgramLocalParametersI4uivEXT fp_glNamedProgramLocalParametersI4uivEXT;
typedef void (APIENTRYP pfn_glGetNamedProgramLocalParameterIivEXT) (GLuint, GLenum, GLuint, GLint*);
extern pfn_glGetNamedProgramLocalParameterIivEXT fp_glGetNamedProgramLocalParameterIivEXT;
typedef void (APIENTRYP pfn_glGetNamedProgramLocalParameterIuivEXT) (GLuint, GLenum, GLuint, GLuint*);
extern pfn_glGetNamedProgramLocalParameterIuivEXT fp_glGetNamedProgramLocalParameterIuivEXT;
typedef void (APIENTRYP pfn_glEnableClientStateiEXT) (GLenum, GLuint);
extern pfn_glEnableClientStateiEXT fp_glEnableClientStateiEXT;
typedef void (APIENTRYP pfn_glDisableClientStateiEXT) (GLenum, GLuint);
extern pfn_glDisableClientStateiEXT fp_glDisableClientStateiEXT;
typedef void (APIENTRYP pfn_glGetFloati_vEXT) (GLenum, GLuint, GLfloat*);
extern pfn_glGetFloati_vEXT fp_glGetFloati_vEXT;
typedef void (APIENTRYP pfn_glGetDoublei_vEXT) (GLenum, GLuint, GLdouble*);
extern pfn_glGetDoublei_vEXT fp_glGetDoublei_vEXT;
typedef void (APIENTRYP pfn_glGetPointeri_vEXT) (GLenum, GLuint, void**);
extern pfn_glGetPointeri_vEXT fp_glGetPointeri_vEXT;
typedef void (APIENTRYP pfn_glNamedProgramStringEXT) (GLuint, GLenum, GLenum, GLsizei, const void*);
extern pfn_glNamedProgramStringEXT fp_glNamedProgramStringEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParameter4dEXT) (GLuint, GLenum, GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glNamedProgramLocalParameter4dEXT fp_glNamedProgramLocalParameter4dEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParameter4dvEXT) (GLuint, GLenum, GLuint, const GLdouble*);
extern pfn_glNamedProgramLocalParameter4dvEXT fp_glNamedProgramLocalParameter4dvEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParameter4fEXT) (GLuint, GLenum, GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glNamedProgramLocalParameter4fEXT fp_glNamedProgramLocalParameter4fEXT;
typedef void (APIENTRYP pfn_glNamedProgramLocalParameter4fvEXT) (GLuint, GLenum, GLuint, const GLfloat*);
extern pfn_glNamedProgramLocalParameter4fvEXT fp_glNamedProgramLocalParameter4fvEXT;
typedef void (APIENTRYP pfn_glGetNamedProgramLocalParameterdvEXT) (GLuint, GLenum, GLuint, GLdouble*);
extern pfn_glGetNamedProgramLocalParameterdvEXT fp_glGetNamedProgramLocalParameterdvEXT;
typedef void (APIENTRYP pfn_glGetNamedProgramLocalParameterfvEXT) (GLuint, GLenum, GLuint, GLfloat*);
extern pfn_glGetNamedProgramLocalParameterfvEXT fp_glGetNamedProgramLocalParameterfvEXT;
typedef void (APIENTRYP pfn_glGetNamedProgramivEXT) (GLuint, GLenum, GLenum, GLint*);
extern pfn_glGetNamedProgramivEXT fp_glGetNamedProgramivEXT;
typedef void (APIENTRYP pfn_glGetNamedProgramStringEXT) (GLuint, GLenum, GLenum, void*);
extern pfn_glGetNamedProgramStringEXT fp_glGetNamedProgramStringEXT;
typedef void (APIENTRYP pfn_glNamedRenderbufferStorageEXT) (GLuint, GLenum, GLsizei, GLsizei);
extern pfn_glNamedRenderbufferStorageEXT fp_glNamedRenderbufferStorageEXT;
typedef void (APIENTRYP pfn_glGetNamedRenderbufferParameterivEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetNamedRenderbufferParameterivEXT fp_glGetNamedRenderbufferParameterivEXT;
typedef void (APIENTRYP pfn_glNamedRenderbufferStorageMultisampleEXT) (GLuint, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glNamedRenderbufferStorageMultisampleEXT fp_glNamedRenderbufferStorageMultisampleEXT;
typedef void (APIENTRYP pfn_glNamedRenderbufferStorageMultisampleCoverageEXT) (GLuint, GLsizei, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glNamedRenderbufferStorageMultisampleCoverageEXT fp_glNamedRenderbufferStorageMultisampleCoverageEXT;
typedef GLenum (APIENTRYP pfn_glCheckNamedFramebufferStatusEXT) (GLuint, GLenum);
extern pfn_glCheckNamedFramebufferStatusEXT fp_glCheckNamedFramebufferStatusEXT;
typedef void (APIENTRYP pfn_glNamedFramebufferTexture1DEXT) (GLuint, GLenum, GLenum, GLuint, GLint);
extern pfn_glNamedFramebufferTexture1DEXT fp_glNamedFramebufferTexture1DEXT;
typedef void (APIENTRYP pfn_glNamedFramebufferTexture2DEXT) (GLuint, GLenum, GLenum, GLuint, GLint);
extern pfn_glNamedFramebufferTexture2DEXT fp_glNamedFramebufferTexture2DEXT;
typedef void (APIENTRYP pfn_glNamedFramebufferTexture3DEXT) (GLuint, GLenum, GLenum, GLuint, GLint, GLint);
extern pfn_glNamedFramebufferTexture3DEXT fp_glNamedFramebufferTexture3DEXT;
typedef void (APIENTRYP pfn_glNamedFramebufferRenderbufferEXT) (GLuint, GLenum, GLenum, GLuint);
extern pfn_glNamedFramebufferRenderbufferEXT fp_glNamedFramebufferRenderbufferEXT;
typedef void (APIENTRYP pfn_glGetNamedFramebufferAttachmentParameterivEXT) (GLuint, GLenum, GLenum, GLint*);
extern pfn_glGetNamedFramebufferAttachmentParameterivEXT fp_glGetNamedFramebufferAttachmentParameterivEXT;
typedef void (APIENTRYP pfn_glGenerateTextureMipmapEXT) (GLuint, GLenum);
extern pfn_glGenerateTextureMipmapEXT fp_glGenerateTextureMipmapEXT;
typedef void (APIENTRYP pfn_glGenerateMultiTexMipmapEXT) (GLenum, GLenum);
extern pfn_glGenerateMultiTexMipmapEXT fp_glGenerateMultiTexMipmapEXT;
typedef void (APIENTRYP pfn_glFramebufferDrawBufferEXT) (GLuint, GLenum);
extern pfn_glFramebufferDrawBufferEXT fp_glFramebufferDrawBufferEXT;
typedef void (APIENTRYP pfn_glFramebufferDrawBuffersEXT) (GLuint, GLsizei, const GLenum*);
extern pfn_glFramebufferDrawBuffersEXT fp_glFramebufferDrawBuffersEXT;
typedef void (APIENTRYP pfn_glFramebufferReadBufferEXT) (GLuint, GLenum);
extern pfn_glFramebufferReadBufferEXT fp_glFramebufferReadBufferEXT;
typedef void (APIENTRYP pfn_glGetFramebufferParameterivEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetFramebufferParameterivEXT fp_glGetFramebufferParameterivEXT;
typedef void (APIENTRYP pfn_glNamedCopyBufferSubDataEXT) (GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr);
extern pfn_glNamedCopyBufferSubDataEXT fp_glNamedCopyBufferSubDataEXT;
typedef void (APIENTRYP pfn_glNamedFramebufferTextureEXT) (GLuint, GLenum, GLuint, GLint);
extern pfn_glNamedFramebufferTextureEXT fp_glNamedFramebufferTextureEXT;
typedef void (APIENTRYP pfn_glNamedFramebufferTextureLayerEXT) (GLuint, GLenum, GLuint, GLint, GLint);
extern pfn_glNamedFramebufferTextureLayerEXT fp_glNamedFramebufferTextureLayerEXT;
typedef void (APIENTRYP pfn_glNamedFramebufferTextureFaceEXT) (GLuint, GLenum, GLuint, GLint, GLenum);
extern pfn_glNamedFramebufferTextureFaceEXT fp_glNamedFramebufferTextureFaceEXT;
typedef void (APIENTRYP pfn_glTextureRenderbufferEXT) (GLuint, GLenum, GLuint);
extern pfn_glTextureRenderbufferEXT fp_glTextureRenderbufferEXT;
typedef void (APIENTRYP pfn_glMultiTexRenderbufferEXT) (GLenum, GLenum, GLuint);
extern pfn_glMultiTexRenderbufferEXT fp_glMultiTexRenderbufferEXT;
typedef void (APIENTRYP pfn_glVertexArrayVertexOffsetEXT) (GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr);
extern pfn_glVertexArrayVertexOffsetEXT fp_glVertexArrayVertexOffsetEXT;
typedef void (APIENTRYP pfn_glVertexArrayColorOffsetEXT) (GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr);
extern pfn_glVertexArrayColorOffsetEXT fp_glVertexArrayColorOffsetEXT;
typedef void (APIENTRYP pfn_glVertexArrayEdgeFlagOffsetEXT) (GLuint, GLuint, GLsizei, GLintptr);
extern pfn_glVertexArrayEdgeFlagOffsetEXT fp_glVertexArrayEdgeFlagOffsetEXT;
typedef void (APIENTRYP pfn_glVertexArrayIndexOffsetEXT) (GLuint, GLuint, GLenum, GLsizei, GLintptr);
extern pfn_glVertexArrayIndexOffsetEXT fp_glVertexArrayIndexOffsetEXT;
typedef void (APIENTRYP pfn_glVertexArrayNormalOffsetEXT) (GLuint, GLuint, GLenum, GLsizei, GLintptr);
extern pfn_glVertexArrayNormalOffsetEXT fp_glVertexArrayNormalOffsetEXT;
typedef void (APIENTRYP pfn_glVertexArrayTexCoordOffsetEXT) (GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr);
extern pfn_glVertexArrayTexCoordOffsetEXT fp_glVertexArrayTexCoordOffsetEXT;
typedef void (APIENTRYP pfn_glVertexArrayMultiTexCoordOffsetEXT) (GLuint, GLuint, GLenum, GLint, GLenum, GLsizei, GLintptr);
extern pfn_glVertexArrayMultiTexCoordOffsetEXT fp_glVertexArrayMultiTexCoordOffsetEXT;
typedef void (APIENTRYP pfn_glVertexArrayFogCoordOffsetEXT) (GLuint, GLuint, GLenum, GLsizei, GLintptr);
extern pfn_glVertexArrayFogCoordOffsetEXT fp_glVertexArrayFogCoordOffsetEXT;
typedef void (APIENTRYP pfn_glVertexArraySecondaryColorOffsetEXT) (GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr);
extern pfn_glVertexArraySecondaryColorOffsetEXT fp_glVertexArraySecondaryColorOffsetEXT;
typedef void (APIENTRYP pfn_glVertexArrayVertexAttribOffsetEXT) (GLuint, GLuint, GLuint, GLint, GLenum, GLboolean, GLsizei, GLintptr);
extern pfn_glVertexArrayVertexAttribOffsetEXT fp_glVertexArrayVertexAttribOffsetEXT;
typedef void (APIENTRYP pfn_glVertexArrayVertexAttribIOffsetEXT) (GLuint, GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr);
extern pfn_glVertexArrayVertexAttribIOffsetEXT fp_glVertexArrayVertexAttribIOffsetEXT;
typedef void (APIENTRYP pfn_glEnableVertexArrayEXT) (GLuint, GLenum);
extern pfn_glEnableVertexArrayEXT fp_glEnableVertexArrayEXT;
typedef void (APIENTRYP pfn_glDisableVertexArrayEXT) (GLuint, GLenum);
extern pfn_glDisableVertexArrayEXT fp_glDisableVertexArrayEXT;
typedef void (APIENTRYP pfn_glEnableVertexArrayAttribEXT) (GLuint, GLuint);
extern pfn_glEnableVertexArrayAttribEXT fp_glEnableVertexArrayAttribEXT;
typedef void (APIENTRYP pfn_glDisableVertexArrayAttribEXT) (GLuint, GLuint);
extern pfn_glDisableVertexArrayAttribEXT fp_glDisableVertexArrayAttribEXT;
typedef void (APIENTRYP pfn_glGetVertexArrayIntegervEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetVertexArrayIntegervEXT fp_glGetVertexArrayIntegervEXT;
typedef void (APIENTRYP pfn_glGetVertexArrayPointervEXT) (GLuint, GLenum, void**);
extern pfn_glGetVertexArrayPointervEXT fp_glGetVertexArrayPointervEXT;
typedef void (APIENTRYP pfn_glGetVertexArrayIntegeri_vEXT) (GLuint, GLuint, GLenum, GLint*);
extern pfn_glGetVertexArrayIntegeri_vEXT fp_glGetVertexArrayIntegeri_vEXT;
typedef void (APIENTRYP pfn_glGetVertexArrayPointeri_vEXT) (GLuint, GLuint, GLenum, void**);
extern pfn_glGetVertexArrayPointeri_vEXT fp_glGetVertexArrayPointeri_vEXT;
typedef void* (APIENTRYP pfn_glMapNamedBufferRangeEXT) (GLuint, GLintptr, GLsizeiptr, GLbitfield);
extern pfn_glMapNamedBufferRangeEXT fp_glMapNamedBufferRangeEXT;
typedef void (APIENTRYP pfn_glFlushMappedNamedBufferRangeEXT) (GLuint, GLintptr, GLsizeiptr);
extern pfn_glFlushMappedNamedBufferRangeEXT fp_glFlushMappedNamedBufferRangeEXT;
typedef void (APIENTRYP pfn_glNamedBufferStorageEXT) (GLuint, GLsizeiptr, const void*, GLbitfield);
extern pfn_glNamedBufferStorageEXT fp_glNamedBufferStorageEXT;
typedef void (APIENTRYP pfn_glClearNamedBufferDataEXT) (GLuint, GLenum, GLenum, GLenum, const void*);
extern pfn_glClearNamedBufferDataEXT fp_glClearNamedBufferDataEXT;
typedef void (APIENTRYP pfn_glClearNamedBufferSubDataEXT) (GLuint, GLenum, GLenum, GLenum, GLsizeiptr, GLsizeiptr, const void*);
extern pfn_glClearNamedBufferSubDataEXT fp_glClearNamedBufferSubDataEXT;
typedef void (APIENTRYP pfn_glNamedFramebufferParameteriEXT) (GLuint, GLenum, GLint);
extern pfn_glNamedFramebufferParameteriEXT fp_glNamedFramebufferParameteriEXT;
typedef void (APIENTRYP pfn_glGetNamedFramebufferParameterivEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetNamedFramebufferParameterivEXT fp_glGetNamedFramebufferParameterivEXT;
typedef void (APIENTRYP pfn_glProgramUniform1dEXT) (GLuint, GLint, GLdouble);
extern pfn_glProgramUniform1dEXT fp_glProgramUniform1dEXT;
typedef void (APIENTRYP pfn_glProgramUniform2dEXT) (GLuint, GLint, GLdouble, GLdouble);
extern pfn_glProgramUniform2dEXT fp_glProgramUniform2dEXT;
typedef void (APIENTRYP pfn_glProgramUniform3dEXT) (GLuint, GLint, GLdouble, GLdouble, GLdouble);
extern pfn_glProgramUniform3dEXT fp_glProgramUniform3dEXT;
typedef void (APIENTRYP pfn_glProgramUniform4dEXT) (GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glProgramUniform4dEXT fp_glProgramUniform4dEXT;
typedef void (APIENTRYP pfn_glProgramUniform1dvEXT) (GLuint, GLint, GLsizei, const GLdouble*);
extern pfn_glProgramUniform1dvEXT fp_glProgramUniform1dvEXT;
typedef void (APIENTRYP pfn_glProgramUniform2dvEXT) (GLuint, GLint, GLsizei, const GLdouble*);
extern pfn_glProgramUniform2dvEXT fp_glProgramUniform2dvEXT;
typedef void (APIENTRYP pfn_glProgramUniform3dvEXT) (GLuint, GLint, GLsizei, const GLdouble*);
extern pfn_glProgramUniform3dvEXT fp_glProgramUniform3dvEXT;
typedef void (APIENTRYP pfn_glProgramUniform4dvEXT) (GLuint, GLint, GLsizei, const GLdouble*);
extern pfn_glProgramUniform4dvEXT fp_glProgramUniform4dvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2dvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix2dvEXT fp_glProgramUniformMatrix2dvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3dvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix3dvEXT fp_glProgramUniformMatrix3dvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4dvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix4dvEXT fp_glProgramUniformMatrix4dvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2x3dvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix2x3dvEXT fp_glProgramUniformMatrix2x3dvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix2x4dvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix2x4dvEXT fp_glProgramUniformMatrix2x4dvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3x2dvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix3x2dvEXT fp_glProgramUniformMatrix3x2dvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix3x4dvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix3x4dvEXT fp_glProgramUniformMatrix3x4dvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4x2dvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix4x2dvEXT fp_glProgramUniformMatrix4x2dvEXT;
typedef void (APIENTRYP pfn_glProgramUniformMatrix4x3dvEXT) (GLuint, GLint, GLsizei, GLboolean, const GLdouble*);
extern pfn_glProgramUniformMatrix4x3dvEXT fp_glProgramUniformMatrix4x3dvEXT;
typedef void (APIENTRYP pfn_glTextureBufferRangeEXT) (GLuint, GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
extern pfn_glTextureBufferRangeEXT fp_glTextureBufferRangeEXT;
typedef void (APIENTRYP pfn_glTextureStorage1DEXT) (GLuint, GLenum, GLsizei, GLenum, GLsizei);
extern pfn_glTextureStorage1DEXT fp_glTextureStorage1DEXT;
typedef void (APIENTRYP pfn_glTextureStorage2DEXT) (GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glTextureStorage2DEXT fp_glTextureStorage2DEXT;
typedef void (APIENTRYP pfn_glTextureStorage3DEXT) (GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
extern pfn_glTextureStorage3DEXT fp_glTextureStorage3DEXT;
typedef void (APIENTRYP pfn_glTextureStorage2DMultisampleEXT) (GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
extern pfn_glTextureStorage2DMultisampleEXT fp_glTextureStorage2DMultisampleEXT;
typedef void (APIENTRYP pfn_glTextureStorage3DMultisampleEXT) (GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
extern pfn_glTextureStorage3DMultisampleEXT fp_glTextureStorage3DMultisampleEXT;
typedef void (APIENTRYP pfn_glVertexArrayBindVertexBufferEXT) (GLuint, GLuint, GLuint, GLintptr, GLsizei);
extern pfn_glVertexArrayBindVertexBufferEXT fp_glVertexArrayBindVertexBufferEXT;
typedef void (APIENTRYP pfn_glVertexArrayVertexAttribFormatEXT) (GLuint, GLuint, GLint, GLenum, GLboolean, GLuint);
extern pfn_glVertexArrayVertexAttribFormatEXT fp_glVertexArrayVertexAttribFormatEXT;
typedef void (APIENTRYP pfn_glVertexArrayVertexAttribIFormatEXT) (GLuint, GLuint, GLint, GLenum, GLuint);
extern pfn_glVertexArrayVertexAttribIFormatEXT fp_glVertexArrayVertexAttribIFormatEXT;
typedef void (APIENTRYP pfn_glVertexArrayVertexAttribLFormatEXT) (GLuint, GLuint, GLint, GLenum, GLuint);
extern pfn_glVertexArrayVertexAttribLFormatEXT fp_glVertexArrayVertexAttribLFormatEXT;
typedef void (APIENTRYP pfn_glVertexArrayVertexAttribBindingEXT) (GLuint, GLuint, GLuint);
extern pfn_glVertexArrayVertexAttribBindingEXT fp_glVertexArrayVertexAttribBindingEXT;
typedef void (APIENTRYP pfn_glVertexArrayVertexBindingDivisorEXT) (GLuint, GLuint, GLuint);
extern pfn_glVertexArrayVertexBindingDivisorEXT fp_glVertexArrayVertexBindingDivisorEXT;
typedef void (APIENTRYP pfn_glVertexArrayVertexAttribLOffsetEXT) (GLuint, GLuint, GLuint, GLint, GLenum, GLsizei, GLintptr);
extern pfn_glVertexArrayVertexAttribLOffsetEXT fp_glVertexArrayVertexAttribLOffsetEXT;
typedef void (APIENTRYP pfn_glTexturePageCommitmentEXT) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLboolean);
extern pfn_glTexturePageCommitmentEXT fp_glTexturePageCommitmentEXT;
typedef void (APIENTRYP pfn_glVertexArrayVertexAttribDivisorEXT) (GLuint, GLuint, GLuint);
extern pfn_glVertexArrayVertexAttribDivisorEXT fp_glVertexArrayVertexAttribDivisorEXT;

 /* GL_EXT_discard_framebuffer */
extern GLboolean GLAD_EXT_discard_framebuffer;
#define GL_COLOR_EXT                           0x1800
#define GL_DEPTH_EXT                           0x1801
#define GL_STENCIL_EXT                         0x1802
typedef void (APIENTRYP pfn_glDiscardFramebufferEXT) (GLenum, GLsizei, const GLenum*);
extern pfn_glDiscardFramebufferEXT fp_glDiscardFramebufferEXT;

 /* GL_EXT_disjoint_timer_query */
extern GLboolean GLAD_EXT_disjoint_timer_query;
#define GL_QUERY_COUNTER_BITS_EXT              0x8864
#define GL_CURRENT_QUERY_EXT                   0x8865
#define GL_QUERY_RESULT_EXT                    0x8866
#define GL_QUERY_RESULT_AVAILABLE_EXT          0x8867
#define GL_TIME_ELAPSED_EXT                    0x88BF
#define GL_TIMESTAMP_EXT                       0x8E28
#define GL_GPU_DISJOINT_EXT                    0x8FBB
typedef void (APIENTRYP pfn_glGenQueriesEXT) (GLsizei, GLuint*);
extern pfn_glGenQueriesEXT fp_glGenQueriesEXT;
typedef void (APIENTRYP pfn_glDeleteQueriesEXT) (GLsizei, const GLuint*);
extern pfn_glDeleteQueriesEXT fp_glDeleteQueriesEXT;
typedef GLboolean (APIENTRYP pfn_glIsQueryEXT) (GLuint);
extern pfn_glIsQueryEXT fp_glIsQueryEXT;
typedef void (APIENTRYP pfn_glBeginQueryEXT) (GLenum, GLuint);
extern pfn_glBeginQueryEXT fp_glBeginQueryEXT;
typedef void (APIENTRYP pfn_glEndQueryEXT) (GLenum);
extern pfn_glEndQueryEXT fp_glEndQueryEXT;
typedef void (APIENTRYP pfn_glQueryCounterEXT) (GLuint, GLenum);
extern pfn_glQueryCounterEXT fp_glQueryCounterEXT;
typedef void (APIENTRYP pfn_glGetQueryivEXT) (GLenum, GLenum, GLint*);
extern pfn_glGetQueryivEXT fp_glGetQueryivEXT;
typedef void (APIENTRYP pfn_glGetQueryObjectivEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetQueryObjectivEXT fp_glGetQueryObjectivEXT;
typedef void (APIENTRYP pfn_glGetQueryObjectuivEXT) (GLuint, GLenum, GLuint*);
extern pfn_glGetQueryObjectuivEXT fp_glGetQueryObjectuivEXT;
typedef void (APIENTRYP pfn_glGetQueryObjecti64vEXT) (GLuint, GLenum, GLint64*);
extern pfn_glGetQueryObjecti64vEXT fp_glGetQueryObjecti64vEXT;
typedef void (APIENTRYP pfn_glGetQueryObjectui64vEXT) (GLuint, GLenum, GLuint64*);
extern pfn_glGetQueryObjectui64vEXT fp_glGetQueryObjectui64vEXT;

 /* GL_EXT_draw_buffers */
extern GLboolean GLAD_EXT_draw_buffers;
#define GL_MAX_COLOR_ATTACHMENTS_EXT           0x8CDF
#define GL_MAX_DRAW_BUFFERS_EXT                0x8824
#define GL_DRAW_BUFFER0_EXT                    0x8825
#define GL_DRAW_BUFFER1_EXT                    0x8826
#define GL_DRAW_BUFFER2_EXT                    0x8827
#define GL_DRAW_BUFFER3_EXT                    0x8828
#define GL_DRAW_BUFFER4_EXT                    0x8829
#define GL_DRAW_BUFFER5_EXT                    0x882A
#define GL_DRAW_BUFFER6_EXT                    0x882B
#define GL_DRAW_BUFFER7_EXT                    0x882C
#define GL_DRAW_BUFFER8_EXT                    0x882D
#define GL_DRAW_BUFFER9_EXT                    0x882E
#define GL_DRAW_BUFFER10_EXT                   0x882F
#define GL_DRAW_BUFFER11_EXT                   0x8830
#define GL_DRAW_BUFFER12_EXT                   0x8831
#define GL_DRAW_BUFFER13_EXT                   0x8832
#define GL_DRAW_BUFFER14_EXT                   0x8833
#define GL_DRAW_BUFFER15_EXT                   0x8834
#define GL_COLOR_ATTACHMENT0_EXT               0x8CE0
#define GL_COLOR_ATTACHMENT1_EXT               0x8CE1
#define GL_COLOR_ATTACHMENT2_EXT               0x8CE2
#define GL_COLOR_ATTACHMENT3_EXT               0x8CE3
#define GL_COLOR_ATTACHMENT4_EXT               0x8CE4
#define GL_COLOR_ATTACHMENT5_EXT               0x8CE5
#define GL_COLOR_ATTACHMENT6_EXT               0x8CE6
#define GL_COLOR_ATTACHMENT7_EXT               0x8CE7
#define GL_COLOR_ATTACHMENT8_EXT               0x8CE8
#define GL_COLOR_ATTACHMENT9_EXT               0x8CE9
#define GL_COLOR_ATTACHMENT10_EXT              0x8CEA
#define GL_COLOR_ATTACHMENT11_EXT              0x8CEB
#define GL_COLOR_ATTACHMENT12_EXT              0x8CEC
#define GL_COLOR_ATTACHMENT13_EXT              0x8CED
#define GL_COLOR_ATTACHMENT14_EXT              0x8CEE
#define GL_COLOR_ATTACHMENT15_EXT              0x8CEF
typedef void (APIENTRYP pfn_glDrawBuffersEXT) (GLsizei, const GLenum*);
extern pfn_glDrawBuffersEXT fp_glDrawBuffersEXT;

 /* GL_EXT_draw_buffers2 */
extern GLboolean GLAD_EXT_draw_buffers2;
typedef void (APIENTRYP pfn_glColorMaskIndexedEXT) (GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
extern pfn_glColorMaskIndexedEXT fp_glColorMaskIndexedEXT;

 /* GL_EXT_draw_instanced */
extern GLboolean GLAD_EXT_draw_instanced;
typedef void (APIENTRYP pfn_glDrawArraysInstancedEXT) (GLenum, GLint, GLsizei, GLsizei);
extern pfn_glDrawArraysInstancedEXT fp_glDrawArraysInstancedEXT;
typedef void (APIENTRYP pfn_glDrawElementsInstancedEXT) (GLenum, GLsizei, GLenum, const void*, GLsizei);
extern pfn_glDrawElementsInstancedEXT fp_glDrawElementsInstancedEXT;

 /* GL_EXT_fog_coord */
extern GLboolean GLAD_EXT_fog_coord;
#define GL_FOG_COORDINATE_SOURCE_EXT           0x8450
#define GL_FOG_COORDINATE_EXT                  0x8451
#define GL_FRAGMENT_DEPTH_EXT                  0x8452
#define GL_CURRENT_FOG_COORDINATE_EXT          0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE_EXT       0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE_EXT     0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER_EXT    0x8456
#define GL_FOG_COORDINATE_ARRAY_EXT            0x8457
typedef void (APIENTRYP pfn_glFogCoordfEXT) (GLfloat);
extern pfn_glFogCoordfEXT fp_glFogCoordfEXT;
typedef void (APIENTRYP pfn_glFogCoordfvEXT) (const GLfloat*);
extern pfn_glFogCoordfvEXT fp_glFogCoordfvEXT;
typedef void (APIENTRYP pfn_glFogCoorddEXT) (GLdouble);
extern pfn_glFogCoorddEXT fp_glFogCoorddEXT;
typedef void (APIENTRYP pfn_glFogCoorddvEXT) (const GLdouble*);
extern pfn_glFogCoorddvEXT fp_glFogCoorddvEXT;
typedef void (APIENTRYP pfn_glFogCoordPointerEXT) (GLenum, GLsizei, const void*);
extern pfn_glFogCoordPointerEXT fp_glFogCoordPointerEXT;

 /* GL_EXT_framebuffer_blit */
extern GLboolean GLAD_EXT_framebuffer_blit;
#define GL_READ_FRAMEBUFFER_EXT                0x8CA8
#define GL_DRAW_FRAMEBUFFER_EXT                0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_EXT        0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_EXT        0x8CAA
typedef void (APIENTRYP pfn_glBlitFramebufferEXT) (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
extern pfn_glBlitFramebufferEXT fp_glBlitFramebufferEXT;

 /* GL_EXT_framebuffer_multisample */
extern GLboolean GLAD_EXT_framebuffer_multisample;
#define GL_RENDERBUFFER_SAMPLES_EXT            0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT  0x8D56
#define GL_MAX_SAMPLES_EXT                     0x8D57
typedef void (APIENTRYP pfn_glRenderbufferStorageMultisampleEXT) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glRenderbufferStorageMultisampleEXT fp_glRenderbufferStorageMultisampleEXT;

 /* GL_EXT_framebuffer_multisample_blit_scaled */
extern GLboolean GLAD_EXT_framebuffer_multisample_blit_scaled;
#define GL_SCALED_RESOLVE_FASTEST_EXT          0x90BA
#define GL_SCALED_RESOLVE_NICEST_EXT           0x90BB

 /* GL_EXT_framebuffer_object */
extern GLboolean GLAD_EXT_framebuffer_object;
#define GL_INVALID_FRAMEBUFFER_OPERATION_EXT   0x0506
#define GL_MAX_RENDERBUFFER_SIZE_EXT           0x84E8
#define GL_FRAMEBUFFER_BINDING_EXT             0x8CA6
#define GL_RENDERBUFFER_BINDING_EXT            0x8CA7
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT  0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT  0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT  0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT  0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT  0x8CD4
#define GL_FRAMEBUFFER_COMPLETE_EXT            0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT  0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT  0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT  0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT  0x8CDA
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT  0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT  0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT         0x8CDD
#define GL_DEPTH_ATTACHMENT_EXT                0x8D00
#define GL_STENCIL_ATTACHMENT_EXT              0x8D20
#define GL_FRAMEBUFFER_EXT                     0x8D40
#define GL_RENDERBUFFER_EXT                    0x8D41
#define GL_RENDERBUFFER_WIDTH_EXT              0x8D42
#define GL_RENDERBUFFER_HEIGHT_EXT             0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT    0x8D44
#define GL_STENCIL_INDEX1_EXT                  0x8D46
#define GL_STENCIL_INDEX4_EXT                  0x8D47
#define GL_STENCIL_INDEX8_EXT                  0x8D48
#define GL_STENCIL_INDEX16_EXT                 0x8D49
#define GL_RENDERBUFFER_RED_SIZE_EXT           0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE_EXT         0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE_EXT          0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE_EXT         0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE_EXT         0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE_EXT       0x8D55
typedef GLboolean (APIENTRYP pfn_glIsRenderbufferEXT) (GLuint);
extern pfn_glIsRenderbufferEXT fp_glIsRenderbufferEXT;
typedef void (APIENTRYP pfn_glBindRenderbufferEXT) (GLenum, GLuint);
extern pfn_glBindRenderbufferEXT fp_glBindRenderbufferEXT;
typedef void (APIENTRYP pfn_glDeleteRenderbuffersEXT) (GLsizei, const GLuint*);
extern pfn_glDeleteRenderbuffersEXT fp_glDeleteRenderbuffersEXT;
typedef void (APIENTRYP pfn_glGenRenderbuffersEXT) (GLsizei, GLuint*);
extern pfn_glGenRenderbuffersEXT fp_glGenRenderbuffersEXT;
typedef void (APIENTRYP pfn_glRenderbufferStorageEXT) (GLenum, GLenum, GLsizei, GLsizei);
extern pfn_glRenderbufferStorageEXT fp_glRenderbufferStorageEXT;
typedef void (APIENTRYP pfn_glGetRenderbufferParameterivEXT) (GLenum, GLenum, GLint*);
extern pfn_glGetRenderbufferParameterivEXT fp_glGetRenderbufferParameterivEXT;
typedef GLboolean (APIENTRYP pfn_glIsFramebufferEXT) (GLuint);
extern pfn_glIsFramebufferEXT fp_glIsFramebufferEXT;
typedef void (APIENTRYP pfn_glBindFramebufferEXT) (GLenum, GLuint);
extern pfn_glBindFramebufferEXT fp_glBindFramebufferEXT;
typedef void (APIENTRYP pfn_glDeleteFramebuffersEXT) (GLsizei, const GLuint*);
extern pfn_glDeleteFramebuffersEXT fp_glDeleteFramebuffersEXT;
typedef void (APIENTRYP pfn_glGenFramebuffersEXT) (GLsizei, GLuint*);
extern pfn_glGenFramebuffersEXT fp_glGenFramebuffersEXT;
typedef GLenum (APIENTRYP pfn_glCheckFramebufferStatusEXT) (GLenum);
extern pfn_glCheckFramebufferStatusEXT fp_glCheckFramebufferStatusEXT;
typedef void (APIENTRYP pfn_glFramebufferTexture1DEXT) (GLenum, GLenum, GLenum, GLuint, GLint);
extern pfn_glFramebufferTexture1DEXT fp_glFramebufferTexture1DEXT;
typedef void (APIENTRYP pfn_glFramebufferTexture2DEXT) (GLenum, GLenum, GLenum, GLuint, GLint);
extern pfn_glFramebufferTexture2DEXT fp_glFramebufferTexture2DEXT;
typedef void (APIENTRYP pfn_glFramebufferTexture3DEXT) (GLenum, GLenum, GLenum, GLuint, GLint, GLint);
extern pfn_glFramebufferTexture3DEXT fp_glFramebufferTexture3DEXT;
typedef void (APIENTRYP pfn_glFramebufferRenderbufferEXT) (GLenum, GLenum, GLenum, GLuint);
extern pfn_glFramebufferRenderbufferEXT fp_glFramebufferRenderbufferEXT;
typedef void (APIENTRYP pfn_glGetFramebufferAttachmentParameterivEXT) (GLenum, GLenum, GLenum, GLint*);
extern pfn_glGetFramebufferAttachmentParameterivEXT fp_glGetFramebufferAttachmentParameterivEXT;
typedef void (APIENTRYP pfn_glGenerateMipmapEXT) (GLenum);
extern pfn_glGenerateMipmapEXT fp_glGenerateMipmapEXT;

 /* GL_EXT_framebuffer_sRGB */
extern GLboolean GLAD_EXT_framebuffer_sRGB;
#define GL_FRAMEBUFFER_SRGB_EXT                0x8DB9
#define GL_FRAMEBUFFER_SRGB_CAPABLE_EXT        0x8DBA

 /* GL_EXT_geometry_shader4 */
extern GLboolean GLAD_EXT_geometry_shader4;
#define GL_GEOMETRY_SHADER_EXT                 0x8DD9
#define GL_GEOMETRY_VERTICES_OUT_EXT           0x8DDA
#define GL_GEOMETRY_INPUT_TYPE_EXT             0x8DDB
#define GL_GEOMETRY_OUTPUT_TYPE_EXT            0x8DDC
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT  0x8C29
#define GL_MAX_GEOMETRY_VARYING_COMPONENTS_EXT  0x8DDD
#define GL_MAX_VERTEX_VARYING_COMPONENTS_EXT   0x8DDE
#define GL_MAX_VARYING_COMPONENTS_EXT          0x8B4B
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT  0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT    0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT  0x8DE1
#define GL_LINES_ADJACENCY_EXT                 0x000A
#define GL_LINE_STRIP_ADJACENCY_EXT            0x000B
#define GL_TRIANGLES_ADJACENCY_EXT             0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY_EXT        0x000D
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT  0x8DA8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_EXT  0x8DA9
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT  0x8DA7
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT  0x8CD4
#define GL_PROGRAM_POINT_SIZE_EXT              0x8642
typedef void (APIENTRYP pfn_glProgramParameteriEXT) (GLuint, GLenum, GLint);
extern pfn_glProgramParameteriEXT fp_glProgramParameteriEXT;

 /* GL_EXT_gpu_program_parameters */
extern GLboolean GLAD_EXT_gpu_program_parameters;
typedef void (APIENTRYP pfn_glProgramEnvParameters4fvEXT) (GLenum, GLuint, GLsizei, const GLfloat*);
extern pfn_glProgramEnvParameters4fvEXT fp_glProgramEnvParameters4fvEXT;
typedef void (APIENTRYP pfn_glProgramLocalParameters4fvEXT) (GLenum, GLuint, GLsizei, const GLfloat*);
extern pfn_glProgramLocalParameters4fvEXT fp_glProgramLocalParameters4fvEXT;

 /* GL_EXT_gpu_shader4 */
extern GLboolean GLAD_EXT_gpu_shader4;
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER_EXT     0x88FD
#define GL_SAMPLER_1D_ARRAY_EXT                0x8DC0
#define GL_SAMPLER_2D_ARRAY_EXT                0x8DC1
#define GL_SAMPLER_BUFFER_EXT                  0x8DC2
#define GL_SAMPLER_1D_ARRAY_SHADOW_EXT         0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW_EXT         0x8DC4
#define GL_SAMPLER_CUBE_SHADOW_EXT             0x8DC5
#define GL_UNSIGNED_INT_VEC2_EXT               0x8DC6
#define GL_UNSIGNED_INT_VEC3_EXT               0x8DC7
#define GL_UNSIGNED_INT_VEC4_EXT               0x8DC8
#define GL_INT_SAMPLER_1D_EXT                  0x8DC9
#define GL_INT_SAMPLER_2D_EXT                  0x8DCA
#define GL_INT_SAMPLER_3D_EXT                  0x8DCB
#define GL_INT_SAMPLER_CUBE_EXT                0x8DCC
#define GL_INT_SAMPLER_2D_RECT_EXT             0x8DCD
#define GL_INT_SAMPLER_1D_ARRAY_EXT            0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY_EXT            0x8DCF
#define GL_INT_SAMPLER_BUFFER_EXT              0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_1D_EXT         0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D_EXT         0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D_EXT         0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE_EXT       0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT_EXT    0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY_EXT   0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY_EXT   0x8DD7
#define GL_UNSIGNED_INT_SAMPLER_BUFFER_EXT     0x8DD8
#define GL_MIN_PROGRAM_TEXEL_OFFSET_EXT        0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET_EXT        0x8905
typedef void (APIENTRYP pfn_glGetUniformuivEXT) (GLuint, GLint, GLuint*);
extern pfn_glGetUniformuivEXT fp_glGetUniformuivEXT;
typedef void (APIENTRYP pfn_glBindFragDataLocationEXT) (GLuint, GLuint, const GLchar*);
extern pfn_glBindFragDataLocationEXT fp_glBindFragDataLocationEXT;
typedef GLint (APIENTRYP pfn_glGetFragDataLocationEXT) (GLuint, const GLchar*);
extern pfn_glGetFragDataLocationEXT fp_glGetFragDataLocationEXT;
typedef void (APIENTRYP pfn_glUniform1uiEXT) (GLint, GLuint);
extern pfn_glUniform1uiEXT fp_glUniform1uiEXT;
typedef void (APIENTRYP pfn_glUniform2uiEXT) (GLint, GLuint, GLuint);
extern pfn_glUniform2uiEXT fp_glUniform2uiEXT;
typedef void (APIENTRYP pfn_glUniform3uiEXT) (GLint, GLuint, GLuint, GLuint);
extern pfn_glUniform3uiEXT fp_glUniform3uiEXT;
typedef void (APIENTRYP pfn_glUniform4uiEXT) (GLint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glUniform4uiEXT fp_glUniform4uiEXT;
typedef void (APIENTRYP pfn_glUniform1uivEXT) (GLint, GLsizei, const GLuint*);
extern pfn_glUniform1uivEXT fp_glUniform1uivEXT;
typedef void (APIENTRYP pfn_glUniform2uivEXT) (GLint, GLsizei, const GLuint*);
extern pfn_glUniform2uivEXT fp_glUniform2uivEXT;
typedef void (APIENTRYP pfn_glUniform3uivEXT) (GLint, GLsizei, const GLuint*);
extern pfn_glUniform3uivEXT fp_glUniform3uivEXT;
typedef void (APIENTRYP pfn_glUniform4uivEXT) (GLint, GLsizei, const GLuint*);
extern pfn_glUniform4uivEXT fp_glUniform4uivEXT;

 /* GL_EXT_histogram */
extern GLboolean GLAD_EXT_histogram;
#define GL_HISTOGRAM_EXT                       0x8024
#define GL_PROXY_HISTOGRAM_EXT                 0x8025
#define GL_HISTOGRAM_WIDTH_EXT                 0x8026
#define GL_HISTOGRAM_FORMAT_EXT                0x8027
#define GL_HISTOGRAM_RED_SIZE_EXT              0x8028
#define GL_HISTOGRAM_GREEN_SIZE_EXT            0x8029
#define GL_HISTOGRAM_BLUE_SIZE_EXT             0x802A
#define GL_HISTOGRAM_ALPHA_SIZE_EXT            0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE_EXT        0x802C
#define GL_HISTOGRAM_SINK_EXT                  0x802D
#define GL_MINMAX_EXT                          0x802E
#define GL_MINMAX_FORMAT_EXT                   0x802F
#define GL_MINMAX_SINK_EXT                     0x8030
#define GL_TABLE_TOO_LARGE_EXT                 0x8031
typedef void (APIENTRYP pfn_glGetHistogramEXT) (GLenum, GLboolean, GLenum, GLenum, void*);
extern pfn_glGetHistogramEXT fp_glGetHistogramEXT;
typedef void (APIENTRYP pfn_glGetHistogramParameterfvEXT) (GLenum, GLenum, GLfloat*);
extern pfn_glGetHistogramParameterfvEXT fp_glGetHistogramParameterfvEXT;
typedef void (APIENTRYP pfn_glGetHistogramParameterivEXT) (GLenum, GLenum, GLint*);
extern pfn_glGetHistogramParameterivEXT fp_glGetHistogramParameterivEXT;
typedef void (APIENTRYP pfn_glGetMinmaxEXT) (GLenum, GLboolean, GLenum, GLenum, void*);
extern pfn_glGetMinmaxEXT fp_glGetMinmaxEXT;
typedef void (APIENTRYP pfn_glGetMinmaxParameterfvEXT) (GLenum, GLenum, GLfloat*);
extern pfn_glGetMinmaxParameterfvEXT fp_glGetMinmaxParameterfvEXT;
typedef void (APIENTRYP pfn_glGetMinmaxParameterivEXT) (GLenum, GLenum, GLint*);
extern pfn_glGetMinmaxParameterivEXT fp_glGetMinmaxParameterivEXT;
typedef void (APIENTRYP pfn_glHistogramEXT) (GLenum, GLsizei, GLenum, GLboolean);
extern pfn_glHistogramEXT fp_glHistogramEXT;
typedef void (APIENTRYP pfn_glMinmaxEXT) (GLenum, GLenum, GLboolean);
extern pfn_glMinmaxEXT fp_glMinmaxEXT;
typedef void (APIENTRYP pfn_glResetHistogramEXT) (GLenum);
extern pfn_glResetHistogramEXT fp_glResetHistogramEXT;
typedef void (APIENTRYP pfn_glResetMinmaxEXT) (GLenum);
extern pfn_glResetMinmaxEXT fp_glResetMinmaxEXT;

 /* GL_EXT_index_array_formats */
extern GLboolean GLAD_EXT_index_array_formats;
#define GL_IUI_V2F_EXT                         0x81AD
#define GL_IUI_V3F_EXT                         0x81AE
#define GL_IUI_N3F_V2F_EXT                     0x81AF
#define GL_IUI_N3F_V3F_EXT                     0x81B0
#define GL_T2F_IUI_V2F_EXT                     0x81B1
#define GL_T2F_IUI_V3F_EXT                     0x81B2
#define GL_T2F_IUI_N3F_V2F_EXT                 0x81B3
#define GL_T2F_IUI_N3F_V3F_EXT                 0x81B4

 /* GL_EXT_index_func */
extern GLboolean GLAD_EXT_index_func;
#define GL_INDEX_TEST_EXT                      0x81B5
#define GL_INDEX_TEST_FUNC_EXT                 0x81B6
#define GL_INDEX_TEST_REF_EXT                  0x81B7
typedef void (APIENTRYP pfn_glIndexFuncEXT) (GLenum, GLclampf);
extern pfn_glIndexFuncEXT fp_glIndexFuncEXT;

 /* GL_EXT_index_material */
extern GLboolean GLAD_EXT_index_material;
#define GL_INDEX_MATERIAL_EXT                  0x81B8
#define GL_INDEX_MATERIAL_PARAMETER_EXT        0x81B9
#define GL_INDEX_MATERIAL_FACE_EXT             0x81BA
typedef void (APIENTRYP pfn_glIndexMaterialEXT) (GLenum, GLenum);
extern pfn_glIndexMaterialEXT fp_glIndexMaterialEXT;

 /* GL_EXT_index_texture */
extern GLboolean GLAD_EXT_index_texture;

 /* GL_EXT_instanced_arrays */
extern GLboolean GLAD_EXT_instanced_arrays;
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_EXT     0x88FE
typedef void (APIENTRYP pfn_glVertexAttribDivisorEXT) (GLuint, GLuint);
extern pfn_glVertexAttribDivisorEXT fp_glVertexAttribDivisorEXT;

 /* GL_EXT_light_texture */
extern GLboolean GLAD_EXT_light_texture;
#define GL_FRAGMENT_MATERIAL_EXT               0x8349
#define GL_FRAGMENT_NORMAL_EXT                 0x834A
#define GL_FRAGMENT_COLOR_EXT                  0x834C
#define GL_ATTENUATION_EXT                     0x834D
#define GL_SHADOW_ATTENUATION_EXT              0x834E
#define GL_TEXTURE_APPLICATION_MODE_EXT        0x834F
#define GL_TEXTURE_LIGHT_EXT                   0x8350
#define GL_TEXTURE_MATERIAL_FACE_EXT           0x8351
#define GL_TEXTURE_MATERIAL_PARAMETER_EXT      0x8352
typedef void (APIENTRYP pfn_glApplyTextureEXT) (GLenum);
extern pfn_glApplyTextureEXT fp_glApplyTextureEXT;
typedef void (APIENTRYP pfn_glTextureLightEXT) (GLenum);
extern pfn_glTextureLightEXT fp_glTextureLightEXT;
typedef void (APIENTRYP pfn_glTextureMaterialEXT) (GLenum, GLenum);
extern pfn_glTextureMaterialEXT fp_glTextureMaterialEXT;

 /* GL_EXT_map_buffer_range */
extern GLboolean GLAD_EXT_map_buffer_range;
#define GL_MAP_READ_BIT_EXT                    0x0001
#define GL_MAP_WRITE_BIT_EXT                   0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT_EXT        0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT_EXT       0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT_EXT          0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT_EXT          0x0020
typedef void* (APIENTRYP pfn_glMapBufferRangeEXT) (GLenum, GLintptr, GLsizeiptr, GLbitfield);
extern pfn_glMapBufferRangeEXT fp_glMapBufferRangeEXT;
typedef void (APIENTRYP pfn_glFlushMappedBufferRangeEXT) (GLenum, GLintptr, GLsizeiptr);
extern pfn_glFlushMappedBufferRangeEXT fp_glFlushMappedBufferRangeEXT;

 /* GL_EXT_misc_attribute */
extern GLboolean GLAD_EXT_misc_attribute;

 /* GL_EXT_multi_draw_arrays */
extern GLboolean GLAD_EXT_multi_draw_arrays;
typedef void (APIENTRYP pfn_glMultiDrawArraysEXT) (GLenum, const GLint*, const GLsizei*, GLsizei);
extern pfn_glMultiDrawArraysEXT fp_glMultiDrawArraysEXT;
typedef void (APIENTRYP pfn_glMultiDrawElementsEXT) (GLenum, const GLsizei*, GLenum, const void**, GLsizei);
extern pfn_glMultiDrawElementsEXT fp_glMultiDrawElementsEXT;

 /* GL_EXT_multisample */
extern GLboolean GLAD_EXT_multisample;
#define GL_MULTISAMPLE_EXT                     0x809D
#define GL_SAMPLE_ALPHA_TO_MASK_EXT            0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_EXT             0x809F
#define GL_SAMPLE_MASK_EXT                     0x80A0
#define GL_1PASS_EXT                           0x80A1
#define GL_2PASS_0_EXT                         0x80A2
#define GL_2PASS_1_EXT                         0x80A3
#define GL_4PASS_0_EXT                         0x80A4
#define GL_4PASS_1_EXT                         0x80A5
#define GL_4PASS_2_EXT                         0x80A6
#define GL_4PASS_3_EXT                         0x80A7
#define GL_SAMPLE_BUFFERS_EXT                  0x80A8
#define GL_SAMPLES_EXT                         0x80A9
#define GL_SAMPLE_MASK_VALUE_EXT               0x80AA
#define GL_SAMPLE_MASK_INVERT_EXT              0x80AB
#define GL_SAMPLE_PATTERN_EXT                  0x80AC
#define GL_MULTISAMPLE_BIT_EXT                 0x20000000
typedef void (APIENTRYP pfn_glSampleMaskEXT) (GLclampf, GLboolean);
extern pfn_glSampleMaskEXT fp_glSampleMaskEXT;
typedef void (APIENTRYP pfn_glSamplePatternEXT) (GLenum);
extern pfn_glSamplePatternEXT fp_glSamplePatternEXT;

 /* GL_EXT_multisampled_render_to_texture */
extern GLboolean GLAD_EXT_multisampled_render_to_texture;
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT  0x8D6C
typedef void (APIENTRYP pfn_glFramebufferTexture2DMultisampleEXT) (GLenum, GLenum, GLenum, GLuint, GLint, GLsizei);
extern pfn_glFramebufferTexture2DMultisampleEXT fp_glFramebufferTexture2DMultisampleEXT;

 /* GL_EXT_multiview_draw_buffers */
extern GLboolean GLAD_EXT_multiview_draw_buffers;
#define GL_COLOR_ATTACHMENT_EXT                0x90F0
#define GL_MULTIVIEW_EXT                       0x90F1
#define GL_DRAW_BUFFER_EXT                     0x0C01
#define GL_READ_BUFFER_EXT                     0x0C02
#define GL_MAX_MULTIVIEW_BUFFERS_EXT           0x90F2
typedef void (APIENTRYP pfn_glReadBufferIndexedEXT) (GLenum, GLint);
extern pfn_glReadBufferIndexedEXT fp_glReadBufferIndexedEXT;
typedef void (APIENTRYP pfn_glDrawBuffersIndexedEXT) (GLint, const GLenum*, const GLint*);
extern pfn_glDrawBuffersIndexedEXT fp_glDrawBuffersIndexedEXT;
typedef void (APIENTRYP pfn_glGetIntegeri_vEXT) (GLenum, GLuint, GLint*);
extern pfn_glGetIntegeri_vEXT fp_glGetIntegeri_vEXT;

 /* GL_EXT_occlusion_query_boolean */
extern GLboolean GLAD_EXT_occlusion_query_boolean;
#define GL_ANY_SAMPLES_PASSED_EXT              0x8C2F
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT  0x8D6A

 /* GL_EXT_packed_depth_stencil */
extern GLboolean GLAD_EXT_packed_depth_stencil;
#define GL_DEPTH_STENCIL_EXT                   0x84F9
#define GL_UNSIGNED_INT_24_8_EXT               0x84FA
#define GL_DEPTH24_STENCIL8_EXT                0x88F0
#define GL_TEXTURE_STENCIL_SIZE_EXT            0x88F1

 /* GL_EXT_packed_float */
extern GLboolean GLAD_EXT_packed_float;
#define GL_R11F_G11F_B10F_EXT                  0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV_EXT    0x8C3B
#define GL_RGBA_SIGNED_COMPONENTS_EXT          0x8C3C

 /* GL_EXT_paletted_texture */
extern GLboolean GLAD_EXT_paletted_texture;
#define GL_COLOR_INDEX1_EXT                    0x80E2
#define GL_COLOR_INDEX2_EXT                    0x80E3
#define GL_COLOR_INDEX4_EXT                    0x80E4
#define GL_COLOR_INDEX8_EXT                    0x80E5
#define GL_COLOR_INDEX12_EXT                   0x80E6
#define GL_COLOR_INDEX16_EXT                   0x80E7
#define GL_TEXTURE_INDEX_SIZE_EXT              0x80ED
typedef void (APIENTRYP pfn_glColorTableEXT) (GLenum, GLenum, GLsizei, GLenum, GLenum, const void*);
extern pfn_glColorTableEXT fp_glColorTableEXT;
typedef void (APIENTRYP pfn_glGetColorTableEXT) (GLenum, GLenum, GLenum, void*);
extern pfn_glGetColorTableEXT fp_glGetColorTableEXT;
typedef void (APIENTRYP pfn_glGetColorTableParameterivEXT) (GLenum, GLenum, GLint*);
extern pfn_glGetColorTableParameterivEXT fp_glGetColorTableParameterivEXT;
typedef void (APIENTRYP pfn_glGetColorTableParameterfvEXT) (GLenum, GLenum, GLfloat*);
extern pfn_glGetColorTableParameterfvEXT fp_glGetColorTableParameterfvEXT;

 /* GL_EXT_pixel_buffer_object */
extern GLboolean GLAD_EXT_pixel_buffer_object;
#define GL_PIXEL_PACK_BUFFER_EXT               0x88EB
#define GL_PIXEL_UNPACK_BUFFER_EXT             0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING_EXT       0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING_EXT     0x88EF

 /* GL_EXT_pixel_transform */
extern GLboolean GLAD_EXT_pixel_transform;
#define GL_PIXEL_TRANSFORM_2D_EXT              0x8330
#define GL_PIXEL_MAG_FILTER_EXT                0x8331
#define GL_PIXEL_MIN_FILTER_EXT                0x8332
#define GL_PIXEL_CUBIC_WEIGHT_EXT              0x8333
#define GL_CUBIC_EXT                           0x8334
#define GL_AVERAGE_EXT                         0x8335
#define GL_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT  0x8336
#define GL_MAX_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT  0x8337
#define GL_PIXEL_TRANSFORM_2D_MATRIX_EXT       0x8338
typedef void (APIENTRYP pfn_glPixelTransformParameteriEXT) (GLenum, GLenum, GLint);
extern pfn_glPixelTransformParameteriEXT fp_glPixelTransformParameteriEXT;
typedef void (APIENTRYP pfn_glPixelTransformParameterfEXT) (GLenum, GLenum, GLfloat);
extern pfn_glPixelTransformParameterfEXT fp_glPixelTransformParameterfEXT;
typedef void (APIENTRYP pfn_glPixelTransformParameterivEXT) (GLenum, GLenum, const GLint*);
extern pfn_glPixelTransformParameterivEXT fp_glPixelTransformParameterivEXT;
typedef void (APIENTRYP pfn_glPixelTransformParameterfvEXT) (GLenum, GLenum, const GLfloat*);
extern pfn_glPixelTransformParameterfvEXT fp_glPixelTransformParameterfvEXT;
typedef void (APIENTRYP pfn_glGetPixelTransformParameterivEXT) (GLenum, GLenum, GLint*);
extern pfn_glGetPixelTransformParameterivEXT fp_glGetPixelTransformParameterivEXT;
typedef void (APIENTRYP pfn_glGetPixelTransformParameterfvEXT) (GLenum, GLenum, GLfloat*);
extern pfn_glGetPixelTransformParameterfvEXT fp_glGetPixelTransformParameterfvEXT;

 /* GL_EXT_pixel_transform_color_table */
extern GLboolean GLAD_EXT_pixel_transform_color_table;

 /* GL_EXT_point_parameters */
extern GLboolean GLAD_EXT_point_parameters;
#define GL_POINT_SIZE_MIN_EXT                  0x8126
#define GL_POINT_SIZE_MAX_EXT                  0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT       0x8128
#define GL_DISTANCE_ATTENUATION_EXT            0x8129
typedef void (APIENTRYP pfn_glPointParameterfEXT) (GLenum, GLfloat);
extern pfn_glPointParameterfEXT fp_glPointParameterfEXT;
typedef void (APIENTRYP pfn_glPointParameterfvEXT) (GLenum, const GLfloat*);
extern pfn_glPointParameterfvEXT fp_glPointParameterfvEXT;

 /* GL_EXT_provoking_vertex */
extern GLboolean GLAD_EXT_provoking_vertex;
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION_EXT  0x8E4C
#define GL_FIRST_VERTEX_CONVENTION_EXT         0x8E4D
#define GL_LAST_VERTEX_CONVENTION_EXT          0x8E4E
#define GL_PROVOKING_VERTEX_EXT                0x8E4F
typedef void (APIENTRYP pfn_glProvokingVertexEXT) (GLenum);
extern pfn_glProvokingVertexEXT fp_glProvokingVertexEXT;

 /* GL_EXT_pvrtc_sRGB */
extern GLboolean GLAD_EXT_pvrtc_sRGB;
#define GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT    0x8A54
#define GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT    0x8A55
#define GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT  0x8A56
#define GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT  0x8A57

 /* GL_EXT_read_format_bgra */
extern GLboolean GLAD_EXT_read_format_bgra;
#define GL_BGRA_EXT                            0x80E1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT      0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT      0x8366

 /* GL_EXT_robustness */
extern GLboolean GLAD_EXT_robustness;
#define GL_GUILTY_CONTEXT_RESET_EXT            0x8253
#define GL_INNOCENT_CONTEXT_RESET_EXT          0x8254
#define GL_UNKNOWN_CONTEXT_RESET_EXT           0x8255
#define GL_CONTEXT_ROBUST_ACCESS_EXT           0x90F3
#define GL_RESET_NOTIFICATION_STRATEGY_EXT     0x8256
#define GL_LOSE_CONTEXT_ON_RESET_EXT           0x8252
#define GL_NO_RESET_NOTIFICATION_EXT           0x8261
typedef GLenum (APIENTRYP pfn_glGetGraphicsResetStatusEXT) ();
extern pfn_glGetGraphicsResetStatusEXT fp_glGetGraphicsResetStatusEXT;
typedef void (APIENTRYP pfn_glReadnPixelsEXT) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void*);
extern pfn_glReadnPixelsEXT fp_glReadnPixelsEXT;
typedef void (APIENTRYP pfn_glGetnUniformfvEXT) (GLuint, GLint, GLsizei, GLfloat*);
extern pfn_glGetnUniformfvEXT fp_glGetnUniformfvEXT;
typedef void (APIENTRYP pfn_glGetnUniformivEXT) (GLuint, GLint, GLsizei, GLint*);
extern pfn_glGetnUniformivEXT fp_glGetnUniformivEXT;

 /* GL_EXT_secondary_color */
extern GLboolean GLAD_EXT_secondary_color;
#define GL_COLOR_SUM_EXT                       0x8458
#define GL_CURRENT_SECONDARY_COLOR_EXT         0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE_EXT      0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE_EXT      0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT    0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER_EXT   0x845D
#define GL_SECONDARY_COLOR_ARRAY_EXT           0x845E
typedef void (APIENTRYP pfn_glSecondaryColor3bEXT) (GLbyte, GLbyte, GLbyte);
extern pfn_glSecondaryColor3bEXT fp_glSecondaryColor3bEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3bvEXT) (const GLbyte*);
extern pfn_glSecondaryColor3bvEXT fp_glSecondaryColor3bvEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3dEXT) (GLdouble, GLdouble, GLdouble);
extern pfn_glSecondaryColor3dEXT fp_glSecondaryColor3dEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3dvEXT) (const GLdouble*);
extern pfn_glSecondaryColor3dvEXT fp_glSecondaryColor3dvEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3fEXT) (GLfloat, GLfloat, GLfloat);
extern pfn_glSecondaryColor3fEXT fp_glSecondaryColor3fEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3fvEXT) (const GLfloat*);
extern pfn_glSecondaryColor3fvEXT fp_glSecondaryColor3fvEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3iEXT) (GLint, GLint, GLint);
extern pfn_glSecondaryColor3iEXT fp_glSecondaryColor3iEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3ivEXT) (const GLint*);
extern pfn_glSecondaryColor3ivEXT fp_glSecondaryColor3ivEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3sEXT) (GLshort, GLshort, GLshort);
extern pfn_glSecondaryColor3sEXT fp_glSecondaryColor3sEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3svEXT) (const GLshort*);
extern pfn_glSecondaryColor3svEXT fp_glSecondaryColor3svEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3ubEXT) (GLubyte, GLubyte, GLubyte);
extern pfn_glSecondaryColor3ubEXT fp_glSecondaryColor3ubEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3ubvEXT) (const GLubyte*);
extern pfn_glSecondaryColor3ubvEXT fp_glSecondaryColor3ubvEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3uiEXT) (GLuint, GLuint, GLuint);
extern pfn_glSecondaryColor3uiEXT fp_glSecondaryColor3uiEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3uivEXT) (const GLuint*);
extern pfn_glSecondaryColor3uivEXT fp_glSecondaryColor3uivEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3usEXT) (GLushort, GLushort, GLushort);
extern pfn_glSecondaryColor3usEXT fp_glSecondaryColor3usEXT;
typedef void (APIENTRYP pfn_glSecondaryColor3usvEXT) (const GLushort*);
extern pfn_glSecondaryColor3usvEXT fp_glSecondaryColor3usvEXT;
typedef void (APIENTRYP pfn_glSecondaryColorPointerEXT) (GLint, GLenum, GLsizei, const void*);
extern pfn_glSecondaryColorPointerEXT fp_glSecondaryColorPointerEXT;

 /* GL_EXT_separate_shader_objects */
extern GLboolean GLAD_EXT_separate_shader_objects;
#define GL_ACTIVE_PROGRAM_EXT                  0x8B8D
#define GL_VERTEX_SHADER_BIT_EXT               0x00000001
#define GL_FRAGMENT_SHADER_BIT_EXT             0x00000002
#define GL_ALL_SHADER_BITS_EXT                 0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE_EXT               0x8258
#define GL_PROGRAM_PIPELINE_BINDING_EXT        0x825A
typedef void (APIENTRYP pfn_glUseShaderProgramEXT) (GLenum, GLuint);
extern pfn_glUseShaderProgramEXT fp_glUseShaderProgramEXT;
typedef void (APIENTRYP pfn_glActiveProgramEXT) (GLuint);
extern pfn_glActiveProgramEXT fp_glActiveProgramEXT;
typedef GLuint (APIENTRYP pfn_glCreateShaderProgramEXT) (GLenum, const GLchar*);
extern pfn_glCreateShaderProgramEXT fp_glCreateShaderProgramEXT;
typedef void (APIENTRYP pfn_glActiveShaderProgramEXT) (GLuint, GLuint);
extern pfn_glActiveShaderProgramEXT fp_glActiveShaderProgramEXT;
typedef void (APIENTRYP pfn_glBindProgramPipelineEXT) (GLuint);
extern pfn_glBindProgramPipelineEXT fp_glBindProgramPipelineEXT;
typedef GLuint (APIENTRYP pfn_glCreateShaderProgramvEXT) (GLenum, GLsizei, const GLchar**);
extern pfn_glCreateShaderProgramvEXT fp_glCreateShaderProgramvEXT;
typedef void (APIENTRYP pfn_glDeleteProgramPipelinesEXT) (GLsizei, const GLuint*);
extern pfn_glDeleteProgramPipelinesEXT fp_glDeleteProgramPipelinesEXT;
typedef void (APIENTRYP pfn_glGenProgramPipelinesEXT) (GLsizei, GLuint*);
extern pfn_glGenProgramPipelinesEXT fp_glGenProgramPipelinesEXT;
typedef void (APIENTRYP pfn_glGetProgramPipelineInfoLogEXT) (GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetProgramPipelineInfoLogEXT fp_glGetProgramPipelineInfoLogEXT;
typedef void (APIENTRYP pfn_glGetProgramPipelineivEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetProgramPipelineivEXT fp_glGetProgramPipelineivEXT;
typedef GLboolean (APIENTRYP pfn_glIsProgramPipelineEXT) (GLuint);
extern pfn_glIsProgramPipelineEXT fp_glIsProgramPipelineEXT;
typedef void (APIENTRYP pfn_glUseProgramStagesEXT) (GLuint, GLbitfield, GLuint);
extern pfn_glUseProgramStagesEXT fp_glUseProgramStagesEXT;
typedef void (APIENTRYP pfn_glValidateProgramPipelineEXT) (GLuint);
extern pfn_glValidateProgramPipelineEXT fp_glValidateProgramPipelineEXT;

 /* GL_EXT_shader_framebuffer_fetch */
extern GLboolean GLAD_EXT_shader_framebuffer_fetch;
#define GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT  0x8A52

 /* GL_EXT_shader_image_load_store */
extern GLboolean GLAD_EXT_shader_image_load_store;
#define GL_MAX_IMAGE_UNITS_EXT                 0x8F38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS_EXT  0x8F39
#define GL_IMAGE_BINDING_NAME_EXT              0x8F3A
#define GL_IMAGE_BINDING_LEVEL_EXT             0x8F3B
#define GL_IMAGE_BINDING_LAYERED_EXT           0x8F3C
#define GL_IMAGE_BINDING_LAYER_EXT             0x8F3D
#define GL_IMAGE_BINDING_ACCESS_EXT            0x8F3E
#define GL_IMAGE_1D_EXT                        0x904C
#define GL_IMAGE_2D_EXT                        0x904D
#define GL_IMAGE_3D_EXT                        0x904E
#define GL_IMAGE_2D_RECT_EXT                   0x904F
#define GL_IMAGE_CUBE_EXT                      0x9050
#define GL_IMAGE_BUFFER_EXT                    0x9051
#define GL_IMAGE_1D_ARRAY_EXT                  0x9052
#define GL_IMAGE_2D_ARRAY_EXT                  0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY_EXT            0x9054
#define GL_IMAGE_2D_MULTISAMPLE_EXT            0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY_EXT      0x9056
#define GL_INT_IMAGE_1D_EXT                    0x9057
#define GL_INT_IMAGE_2D_EXT                    0x9058
#define GL_INT_IMAGE_3D_EXT                    0x9059
#define GL_INT_IMAGE_2D_RECT_EXT               0x905A
#define GL_INT_IMAGE_CUBE_EXT                  0x905B
#define GL_INT_IMAGE_BUFFER_EXT                0x905C
#define GL_INT_IMAGE_1D_ARRAY_EXT              0x905D
#define GL_INT_IMAGE_2D_ARRAY_EXT              0x905E
#define GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT        0x905F
#define GL_INT_IMAGE_2D_MULTISAMPLE_EXT        0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY_EXT  0x9061
#define GL_UNSIGNED_INT_IMAGE_1D_EXT           0x9062
#define GL_UNSIGNED_INT_IMAGE_2D_EXT           0x9063
#define GL_UNSIGNED_INT_IMAGE_3D_EXT           0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT_EXT      0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE_EXT         0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER_EXT       0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY_EXT     0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY_EXT     0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT  0x906A
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_EXT  0x906B
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY_EXT  0x906C
#define GL_MAX_IMAGE_SAMPLES_EXT               0x906D
#define GL_IMAGE_BINDING_FORMAT_EXT            0x906E
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT_EXT  0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT_EXT       0x00000002
#define GL_UNIFORM_BARRIER_BIT_EXT             0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT_EXT       0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT_EXT  0x00000020
#define GL_COMMAND_BARRIER_BIT_EXT             0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT_EXT        0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT_EXT      0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT_EXT       0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT_EXT         0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT_EXT  0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT_EXT      0x00001000
#define GL_ALL_BARRIER_BITS_EXT                0xFFFFFFFF
typedef void (APIENTRYP pfn_glBindImageTextureEXT) (GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLint);
extern pfn_glBindImageTextureEXT fp_glBindImageTextureEXT;
typedef void (APIENTRYP pfn_glMemoryBarrierEXT) (GLbitfield);
extern pfn_glMemoryBarrierEXT fp_glMemoryBarrierEXT;

 /* GL_EXT_shader_integer_mix */
extern GLboolean GLAD_EXT_shader_integer_mix;

 /* GL_EXT_shader_texture_lod */
extern GLboolean GLAD_EXT_shader_texture_lod;

 /* GL_EXT_shadow_funcs */
extern GLboolean GLAD_EXT_shadow_funcs;

 /* GL_EXT_shadow_samplers */
extern GLboolean GLAD_EXT_shadow_samplers;
#define GL_TEXTURE_COMPARE_MODE_EXT            0x884C
#define GL_TEXTURE_COMPARE_FUNC_EXT            0x884D
#define GL_COMPARE_REF_TO_TEXTURE_EXT          0x884E
#define GL_SAMPLER_2D_SHADOW_EXT               0x8B62

 /* GL_EXT_shared_texture_palette */
extern GLboolean GLAD_EXT_shared_texture_palette;
#define GL_SHARED_TEXTURE_PALETTE_EXT          0x81FB

 /* GL_EXT_sRGB */
extern GLboolean GLAD_EXT_sRGB;
#define GL_SRGB_EXT                            0x8C40
#define GL_SRGB_ALPHA_EXT                      0x8C42
#define GL_SRGB8_ALPHA8_EXT                    0x8C43
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT  0x8210

 /* GL_EXT_sRGB_write_control */
extern GLboolean GLAD_EXT_sRGB_write_control;

 /* GL_EXT_stencil_clear_tag */
extern GLboolean GLAD_EXT_stencil_clear_tag;
#define GL_STENCIL_TAG_BITS_EXT                0x88F2
#define GL_STENCIL_CLEAR_TAG_VALUE_EXT         0x88F3
typedef void (APIENTRYP pfn_glStencilClearTagEXT) (GLsizei, GLuint);
extern pfn_glStencilClearTagEXT fp_glStencilClearTagEXT;

 /* GL_EXT_stencil_two_side */
extern GLboolean GLAD_EXT_stencil_two_side;
#define GL_STENCIL_TEST_TWO_SIDE_EXT           0x8910
#define GL_ACTIVE_STENCIL_FACE_EXT             0x8911
typedef void (APIENTRYP pfn_glActiveStencilFaceEXT) (GLenum);
extern pfn_glActiveStencilFaceEXT fp_glActiveStencilFaceEXT;

 /* GL_EXT_stencil_wrap */
extern GLboolean GLAD_EXT_stencil_wrap;
#define GL_INCR_WRAP_EXT                       0x8507
#define GL_DECR_WRAP_EXT                       0x8508

 /* GL_EXT_texture_array */
extern GLboolean GLAD_EXT_texture_array;
#define GL_TEXTURE_1D_ARRAY_EXT                0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY_EXT          0x8C19
#define GL_TEXTURE_2D_ARRAY_EXT                0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY_EXT          0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY_EXT        0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY_EXT        0x8C1D
#define GL_MAX_ARRAY_TEXTURE_LAYERS_EXT        0x88FF
#define GL_COMPARE_REF_DEPTH_TO_TEXTURE_EXT    0x884E

 /* GL_EXT_texture_buffer_object */
extern GLboolean GLAD_EXT_texture_buffer_object;
#define GL_TEXTURE_BUFFER_EXT                  0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE_EXT         0x8C2B
#define GL_TEXTURE_BINDING_BUFFER_EXT          0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING_EXT  0x8C2D
#define GL_TEXTURE_BUFFER_FORMAT_EXT           0x8C2E
typedef void (APIENTRYP pfn_glTexBufferEXT) (GLenum, GLenum, GLuint);
extern pfn_glTexBufferEXT fp_glTexBufferEXT;

 /* GL_EXT_texture_compression_dxt1 */
extern GLboolean GLAD_EXT_texture_compression_dxt1;
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT        0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT       0x83F1

 /* GL_EXT_texture_compression_latc */
extern GLboolean GLAD_EXT_texture_compression_latc;
#define GL_COMPRESSED_LUMINANCE_LATC1_EXT      0x8C70
#define GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT  0x8C71
#define GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT  0x8C72
#define GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT  0x8C73

 /* GL_EXT_texture_compression_rgtc */
extern GLboolean GLAD_EXT_texture_compression_rgtc;
#define GL_COMPRESSED_RED_RGTC1_EXT            0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1_EXT     0x8DBC
#define GL_COMPRESSED_RED_GREEN_RGTC2_EXT      0x8DBD
#define GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT  0x8DBE

 /* GL_EXT_texture_compression_s3tc */
extern GLboolean GLAD_EXT_texture_compression_s3tc;
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT       0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT       0x83F3

 /* GL_EXT_texture_cube_map */
extern GLboolean GLAD_EXT_texture_cube_map;
#define GL_NORMAL_MAP_EXT                      0x8511
#define GL_REFLECTION_MAP_EXT                  0x8512
#define GL_TEXTURE_CUBE_MAP_EXT                0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_EXT        0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT     0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT     0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT     0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT     0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT     0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT     0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_EXT          0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT       0x851C

 /* GL_EXT_texture_env_add */
extern GLboolean GLAD_EXT_texture_env_add;

 /* GL_EXT_texture_env_combine */
extern GLboolean GLAD_EXT_texture_env_combine;
#define GL_COMBINE_EXT                         0x8570
#define GL_COMBINE_RGB_EXT                     0x8571
#define GL_COMBINE_ALPHA_EXT                   0x8572
#define GL_RGB_SCALE_EXT                       0x8573
#define GL_ADD_SIGNED_EXT                      0x8574
#define GL_INTERPOLATE_EXT                     0x8575
#define GL_CONSTANT_EXT                        0x8576
#define GL_PRIMARY_COLOR_EXT                   0x8577
#define GL_PREVIOUS_EXT                        0x8578
#define GL_SOURCE0_RGB_EXT                     0x8580
#define GL_SOURCE1_RGB_EXT                     0x8581
#define GL_SOURCE2_RGB_EXT                     0x8582
#define GL_SOURCE0_ALPHA_EXT                   0x8588
#define GL_SOURCE1_ALPHA_EXT                   0x8589
#define GL_SOURCE2_ALPHA_EXT                   0x858A
#define GL_OPERAND0_RGB_EXT                    0x8590
#define GL_OPERAND1_RGB_EXT                    0x8591
#define GL_OPERAND2_RGB_EXT                    0x8592
#define GL_OPERAND0_ALPHA_EXT                  0x8598
#define GL_OPERAND1_ALPHA_EXT                  0x8599
#define GL_OPERAND2_ALPHA_EXT                  0x859A

 /* GL_EXT_texture_env_dot3 */
extern GLboolean GLAD_EXT_texture_env_dot3;
#define GL_DOT3_RGB_EXT                        0x8740
#define GL_DOT3_RGBA_EXT                       0x8741

 /* GL_EXT_texture_filter_anisotropic */
extern GLboolean GLAD_EXT_texture_filter_anisotropic;
#define GL_TEXTURE_MAX_ANISOTROPY_EXT          0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT      0x84FF

 /* GL_EXT_texture_format_BGRA8888 */
extern GLboolean GLAD_EXT_texture_format_BGRA8888;

 /* GL_EXT_texture_integer */
extern GLboolean GLAD_EXT_texture_integer;
#define GL_RGBA32UI_EXT                        0x8D70
#define GL_RGB32UI_EXT                         0x8D71
#define GL_ALPHA32UI_EXT                       0x8D72
#define GL_INTENSITY32UI_EXT                   0x8D73
#define GL_LUMINANCE32UI_EXT                   0x8D74
#define GL_LUMINANCE_ALPHA32UI_EXT             0x8D75
#define GL_RGBA16UI_EXT                        0x8D76
#define GL_RGB16UI_EXT                         0x8D77
#define GL_ALPHA16UI_EXT                       0x8D78
#define GL_INTENSITY16UI_EXT                   0x8D79
#define GL_LUMINANCE16UI_EXT                   0x8D7A
#define GL_LUMINANCE_ALPHA16UI_EXT             0x8D7B
#define GL_RGBA8UI_EXT                         0x8D7C
#define GL_RGB8UI_EXT                          0x8D7D
#define GL_ALPHA8UI_EXT                        0x8D7E
#define GL_INTENSITY8UI_EXT                    0x8D7F
#define GL_LUMINANCE8UI_EXT                    0x8D80
#define GL_LUMINANCE_ALPHA8UI_EXT              0x8D81
#define GL_RGBA32I_EXT                         0x8D82
#define GL_RGB32I_EXT                          0x8D83
#define GL_ALPHA32I_EXT                        0x8D84
#define GL_INTENSITY32I_EXT                    0x8D85
#define GL_LUMINANCE32I_EXT                    0x8D86
#define GL_LUMINANCE_ALPHA32I_EXT              0x8D87
#define GL_RGBA16I_EXT                         0x8D88
#define GL_RGB16I_EXT                          0x8D89
#define GL_ALPHA16I_EXT                        0x8D8A
#define GL_INTENSITY16I_EXT                    0x8D8B
#define GL_LUMINANCE16I_EXT                    0x8D8C
#define GL_LUMINANCE_ALPHA16I_EXT              0x8D8D
#define GL_RGBA8I_EXT                          0x8D8E
#define GL_RGB8I_EXT                           0x8D8F
#define GL_ALPHA8I_EXT                         0x8D90
#define GL_INTENSITY8I_EXT                     0x8D91
#define GL_LUMINANCE8I_EXT                     0x8D92
#define GL_LUMINANCE_ALPHA8I_EXT               0x8D93
#define GL_RED_INTEGER_EXT                     0x8D94
#define GL_GREEN_INTEGER_EXT                   0x8D95
#define GL_BLUE_INTEGER_EXT                    0x8D96
#define GL_ALPHA_INTEGER_EXT                   0x8D97
#define GL_RGB_INTEGER_EXT                     0x8D98
#define GL_RGBA_INTEGER_EXT                    0x8D99
#define GL_BGR_INTEGER_EXT                     0x8D9A
#define GL_BGRA_INTEGER_EXT                    0x8D9B
#define GL_LUMINANCE_INTEGER_EXT               0x8D9C
#define GL_LUMINANCE_ALPHA_INTEGER_EXT         0x8D9D
#define GL_RGBA_INTEGER_MODE_EXT               0x8D9E
typedef void (APIENTRYP pfn_glTexParameterIivEXT) (GLenum, GLenum, const GLint*);
extern pfn_glTexParameterIivEXT fp_glTexParameterIivEXT;
typedef void (APIENTRYP pfn_glTexParameterIuivEXT) (GLenum, GLenum, const GLuint*);
extern pfn_glTexParameterIuivEXT fp_glTexParameterIuivEXT;
typedef void (APIENTRYP pfn_glGetTexParameterIivEXT) (GLenum, GLenum, GLint*);
extern pfn_glGetTexParameterIivEXT fp_glGetTexParameterIivEXT;
typedef void (APIENTRYP pfn_glGetTexParameterIuivEXT) (GLenum, GLenum, GLuint*);
extern pfn_glGetTexParameterIuivEXT fp_glGetTexParameterIuivEXT;
typedef void (APIENTRYP pfn_glClearColorIiEXT) (GLint, GLint, GLint, GLint);
extern pfn_glClearColorIiEXT fp_glClearColorIiEXT;
typedef void (APIENTRYP pfn_glClearColorIuiEXT) (GLuint, GLuint, GLuint, GLuint);
extern pfn_glClearColorIuiEXT fp_glClearColorIuiEXT;

 /* GL_EXT_texture_lod_bias */
extern GLboolean GLAD_EXT_texture_lod_bias;
#define GL_MAX_TEXTURE_LOD_BIAS_EXT            0x84FD
#define GL_TEXTURE_FILTER_CONTROL_EXT          0x8500
#define GL_TEXTURE_LOD_BIAS_EXT                0x8501

 /* GL_EXT_texture_mirror_clamp */
extern GLboolean GLAD_EXT_texture_mirror_clamp;
#define GL_MIRROR_CLAMP_EXT                    0x8742
#define GL_MIRROR_CLAMP_TO_EDGE_EXT            0x8743
#define GL_MIRROR_CLAMP_TO_BORDER_EXT          0x8912

 /* GL_EXT_texture_perturb_normal */
extern GLboolean GLAD_EXT_texture_perturb_normal;
#define GL_PERTURB_EXT                         0x85AE
#define GL_TEXTURE_NORMAL_EXT                  0x85AF
typedef void (APIENTRYP pfn_glTextureNormalEXT) (GLenum);
extern pfn_glTextureNormalEXT fp_glTextureNormalEXT;

 /* GL_EXT_texture_rg */
extern GLboolean GLAD_EXT_texture_rg;
#define GL_RED_EXT                             0x1903
#define GL_RG_EXT                              0x8227
#define GL_R8_EXT                              0x8229
#define GL_RG8_EXT                             0x822B

 /* GL_EXT_texture_shared_exponent */
extern GLboolean GLAD_EXT_texture_shared_exponent;
#define GL_RGB9_E5_EXT                         0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV_EXT        0x8C3E
#define GL_TEXTURE_SHARED_SIZE_EXT             0x8C3F

 /* GL_EXT_texture_snorm */
extern GLboolean GLAD_EXT_texture_snorm;
#define GL_ALPHA_SNORM                         0x9010
#define GL_LUMINANCE_SNORM                     0x9011
#define GL_LUMINANCE_ALPHA_SNORM               0x9012
#define GL_INTENSITY_SNORM                     0x9013
#define GL_ALPHA8_SNORM                        0x9014
#define GL_LUMINANCE8_SNORM                    0x9015
#define GL_LUMINANCE8_ALPHA8_SNORM             0x9016
#define GL_INTENSITY8_SNORM                    0x9017
#define GL_ALPHA16_SNORM                       0x9018
#define GL_LUMINANCE16_SNORM                   0x9019
#define GL_LUMINANCE16_ALPHA16_SNORM           0x901A
#define GL_INTENSITY16_SNORM                   0x901B
#define GL_RED_SNORM                           0x8F90
#define GL_RG_SNORM                            0x8F91
#define GL_RGB_SNORM                           0x8F92
#define GL_RGBA_SNORM                          0x8F93

 /* GL_EXT_texture_sRGB */
extern GLboolean GLAD_EXT_texture_sRGB;
#define GL_SRGB8_EXT                           0x8C41
#define GL_SLUMINANCE_ALPHA_EXT                0x8C44
#define GL_SLUMINANCE8_ALPHA8_EXT              0x8C45
#define GL_SLUMINANCE_EXT                      0x8C46
#define GL_SLUMINANCE8_EXT                     0x8C47
#define GL_COMPRESSED_SRGB_EXT                 0x8C48
#define GL_COMPRESSED_SRGB_ALPHA_EXT           0x8C49
#define GL_COMPRESSED_SLUMINANCE_EXT           0x8C4A
#define GL_COMPRESSED_SLUMINANCE_ALPHA_EXT     0x8C4B
#define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT       0x8C4C
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT  0x8C4D
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT  0x8C4E
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT  0x8C4F

 /* GL_EXT_texture_sRGB_decode */
extern GLboolean GLAD_EXT_texture_sRGB_decode;
#define GL_TEXTURE_SRGB_DECODE_EXT             0x8A48
#define GL_DECODE_EXT                          0x8A49
#define GL_SKIP_DECODE_EXT                     0x8A4A

 /* GL_EXT_texture_storage */
extern GLboolean GLAD_EXT_texture_storage;
#define GL_TEXTURE_IMMUTABLE_FORMAT_EXT        0x912F
#define GL_ALPHA8_EXT                          0x803C
#define GL_LUMINANCE8_EXT                      0x8040
#define GL_LUMINANCE8_ALPHA8_EXT               0x8045
#define GL_RGBA32F_EXT                         0x8814
#define GL_RGB32F_EXT                          0x8815
#define GL_ALPHA32F_EXT                        0x8816
#define GL_LUMINANCE32F_EXT                    0x8818
#define GL_LUMINANCE_ALPHA32F_EXT              0x8819
#define GL_ALPHA16F_EXT                        0x881C
#define GL_LUMINANCE16F_EXT                    0x881E
#define GL_LUMINANCE_ALPHA16F_EXT              0x881F
#define GL_RGB10_A2_EXT                        0x8059
#define GL_RGB10_EXT                           0x8052
#define GL_BGRA8_EXT                           0x93A1
#define GL_R32F_EXT                            0x822E
#define GL_RG32F_EXT                           0x8230
typedef void (APIENTRYP pfn_glTexStorage1DEXT) (GLenum, GLsizei, GLenum, GLsizei);
extern pfn_glTexStorage1DEXT fp_glTexStorage1DEXT;
typedef void (APIENTRYP pfn_glTexStorage2DEXT) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glTexStorage2DEXT fp_glTexStorage2DEXT;
typedef void (APIENTRYP pfn_glTexStorage3DEXT) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
extern pfn_glTexStorage3DEXT fp_glTexStorage3DEXT;

 /* GL_EXT_texture_swizzle */
extern GLboolean GLAD_EXT_texture_swizzle;
#define GL_TEXTURE_SWIZZLE_R_EXT               0x8E42
#define GL_TEXTURE_SWIZZLE_G_EXT               0x8E43
#define GL_TEXTURE_SWIZZLE_B_EXT               0x8E44
#define GL_TEXTURE_SWIZZLE_A_EXT               0x8E45
#define GL_TEXTURE_SWIZZLE_RGBA_EXT            0x8E46

 /* GL_EXT_texture_type_2_10_10_10_REV */
extern GLboolean GLAD_EXT_texture_type_2_10_10_10_REV;
#define GL_UNSIGNED_INT_2_10_10_10_REV_EXT     0x8368

 /* GL_EXT_timer_query */
extern GLboolean GLAD_EXT_timer_query;

 /* GL_EXT_transform_feedback */
extern GLboolean GLAD_EXT_transform_feedback;
#define GL_TRANSFORM_FEEDBACK_BUFFER_EXT       0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_START_EXT  0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE_EXT  0x8C85
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING_EXT  0x8C8F
#define GL_INTERLEAVED_ATTRIBS_EXT             0x8C8C
#define GL_SEPARATE_ATTRIBS_EXT                0x8C8D
#define GL_PRIMITIVES_GENERATED_EXT            0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_EXT  0x8C88
#define GL_RASTERIZER_DISCARD_EXT              0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_EXT  0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_EXT  0x8C8B
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_EXT  0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS_EXT     0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE_EXT  0x8C7F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH_EXT  0x8C76
typedef void (APIENTRYP pfn_glBeginTransformFeedbackEXT) (GLenum);
extern pfn_glBeginTransformFeedbackEXT fp_glBeginTransformFeedbackEXT;
typedef void (APIENTRYP pfn_glEndTransformFeedbackEXT) ();
extern pfn_glEndTransformFeedbackEXT fp_glEndTransformFeedbackEXT;
typedef void (APIENTRYP pfn_glBindBufferRangeEXT) (GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
extern pfn_glBindBufferRangeEXT fp_glBindBufferRangeEXT;
typedef void (APIENTRYP pfn_glBindBufferOffsetEXT) (GLenum, GLuint, GLuint, GLintptr);
extern pfn_glBindBufferOffsetEXT fp_glBindBufferOffsetEXT;
typedef void (APIENTRYP pfn_glBindBufferBaseEXT) (GLenum, GLuint, GLuint);
extern pfn_glBindBufferBaseEXT fp_glBindBufferBaseEXT;
typedef void (APIENTRYP pfn_glTransformFeedbackVaryingsEXT) (GLuint, GLsizei, const GLchar**, GLenum);
extern pfn_glTransformFeedbackVaryingsEXT fp_glTransformFeedbackVaryingsEXT;
typedef void (APIENTRYP pfn_glGetTransformFeedbackVaryingEXT) (GLuint, GLuint, GLsizei, GLsizei*, GLsizei*, GLenum*, GLchar*);
extern pfn_glGetTransformFeedbackVaryingEXT fp_glGetTransformFeedbackVaryingEXT;

 /* GL_EXT_unpack_subimage */
extern GLboolean GLAD_EXT_unpack_subimage;
#define GL_UNPACK_ROW_LENGTH_EXT               0x0CF2
#define GL_UNPACK_SKIP_ROWS_EXT                0x0CF3
#define GL_UNPACK_SKIP_PIXELS_EXT              0x0CF4

 /* GL_EXT_vertex_array_bgra */
extern GLboolean GLAD_EXT_vertex_array_bgra;

 /* GL_EXT_vertex_attrib_64bit */
extern GLboolean GLAD_EXT_vertex_attrib_64bit;
#define GL_DOUBLE_VEC2_EXT                     0x8FFC
#define GL_DOUBLE_VEC3_EXT                     0x8FFD
#define GL_DOUBLE_VEC4_EXT                     0x8FFE
#define GL_DOUBLE_MAT2_EXT                     0x8F46
#define GL_DOUBLE_MAT3_EXT                     0x8F47
#define GL_DOUBLE_MAT4_EXT                     0x8F48
#define GL_DOUBLE_MAT2x3_EXT                   0x8F49
#define GL_DOUBLE_MAT2x4_EXT                   0x8F4A
#define GL_DOUBLE_MAT3x2_EXT                   0x8F4B
#define GL_DOUBLE_MAT3x4_EXT                   0x8F4C
#define GL_DOUBLE_MAT4x2_EXT                   0x8F4D
#define GL_DOUBLE_MAT4x3_EXT                   0x8F4E
typedef void (APIENTRYP pfn_glVertexAttribL1dEXT) (GLuint, GLdouble);
extern pfn_glVertexAttribL1dEXT fp_glVertexAttribL1dEXT;
typedef void (APIENTRYP pfn_glVertexAttribL2dEXT) (GLuint, GLdouble, GLdouble);
extern pfn_glVertexAttribL2dEXT fp_glVertexAttribL2dEXT;
typedef void (APIENTRYP pfn_glVertexAttribL3dEXT) (GLuint, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexAttribL3dEXT fp_glVertexAttribL3dEXT;
typedef void (APIENTRYP pfn_glVertexAttribL4dEXT) (GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexAttribL4dEXT fp_glVertexAttribL4dEXT;
typedef void (APIENTRYP pfn_glVertexAttribL1dvEXT) (GLuint, const GLdouble*);
extern pfn_glVertexAttribL1dvEXT fp_glVertexAttribL1dvEXT;
typedef void (APIENTRYP pfn_glVertexAttribL2dvEXT) (GLuint, const GLdouble*);
extern pfn_glVertexAttribL2dvEXT fp_glVertexAttribL2dvEXT;
typedef void (APIENTRYP pfn_glVertexAttribL3dvEXT) (GLuint, const GLdouble*);
extern pfn_glVertexAttribL3dvEXT fp_glVertexAttribL3dvEXT;
typedef void (APIENTRYP pfn_glVertexAttribL4dvEXT) (GLuint, const GLdouble*);
extern pfn_glVertexAttribL4dvEXT fp_glVertexAttribL4dvEXT;
typedef void (APIENTRYP pfn_glVertexAttribLPointerEXT) (GLuint, GLint, GLenum, GLsizei, const void*);
extern pfn_glVertexAttribLPointerEXT fp_glVertexAttribLPointerEXT;
typedef void (APIENTRYP pfn_glGetVertexAttribLdvEXT) (GLuint, GLenum, GLdouble*);
extern pfn_glGetVertexAttribLdvEXT fp_glGetVertexAttribLdvEXT;

 /* GL_EXT_vertex_shader */
extern GLboolean GLAD_EXT_vertex_shader;
#define GL_VERTEX_SHADER_EXT                   0x8780
#define GL_VERTEX_SHADER_BINDING_EXT           0x8781
#define GL_OP_INDEX_EXT                        0x8782
#define GL_OP_NEGATE_EXT                       0x8783
#define GL_OP_DOT3_EXT                         0x8784
#define GL_OP_DOT4_EXT                         0x8785
#define GL_OP_MUL_EXT                          0x8786
#define GL_OP_ADD_EXT                          0x8787
#define GL_OP_MADD_EXT                         0x8788
#define GL_OP_FRAC_EXT                         0x8789
#define GL_OP_MAX_EXT                          0x878A
#define GL_OP_MIN_EXT                          0x878B
#define GL_OP_SET_GE_EXT                       0x878C
#define GL_OP_SET_LT_EXT                       0x878D
#define GL_OP_CLAMP_EXT                        0x878E
#define GL_OP_FLOOR_EXT                        0x878F
#define GL_OP_ROUND_EXT                        0x8790
#define GL_OP_EXP_BASE_2_EXT                   0x8791
#define GL_OP_LOG_BASE_2_EXT                   0x8792
#define GL_OP_POWER_EXT                        0x8793
#define GL_OP_RECIP_EXT                        0x8794
#define GL_OP_RECIP_SQRT_EXT                   0x8795
#define GL_OP_SUB_EXT                          0x8796
#define GL_OP_CROSS_PRODUCT_EXT                0x8797
#define GL_OP_MULTIPLY_MATRIX_EXT              0x8798
#define GL_OP_MOV_EXT                          0x8799
#define GL_OUTPUT_VERTEX_EXT                   0x879A
#define GL_OUTPUT_COLOR0_EXT                   0x879B
#define GL_OUTPUT_COLOR1_EXT                   0x879C
#define GL_OUTPUT_TEXTURE_COORD0_EXT           0x879D
#define GL_OUTPUT_TEXTURE_COORD1_EXT           0x879E
#define GL_OUTPUT_TEXTURE_COORD2_EXT           0x879F
#define GL_OUTPUT_TEXTURE_COORD3_EXT           0x87A0
#define GL_OUTPUT_TEXTURE_COORD4_EXT           0x87A1
#define GL_OUTPUT_TEXTURE_COORD5_EXT           0x87A2
#define GL_OUTPUT_TEXTURE_COORD6_EXT           0x87A3
#define GL_OUTPUT_TEXTURE_COORD7_EXT           0x87A4
#define GL_OUTPUT_TEXTURE_COORD8_EXT           0x87A5
#define GL_OUTPUT_TEXTURE_COORD9_EXT           0x87A6
#define GL_OUTPUT_TEXTURE_COORD10_EXT          0x87A7
#define GL_OUTPUT_TEXTURE_COORD11_EXT          0x87A8
#define GL_OUTPUT_TEXTURE_COORD12_EXT          0x87A9
#define GL_OUTPUT_TEXTURE_COORD13_EXT          0x87AA
#define GL_OUTPUT_TEXTURE_COORD14_EXT          0x87AB
#define GL_OUTPUT_TEXTURE_COORD15_EXT          0x87AC
#define GL_OUTPUT_TEXTURE_COORD16_EXT          0x87AD
#define GL_OUTPUT_TEXTURE_COORD17_EXT          0x87AE
#define GL_OUTPUT_TEXTURE_COORD18_EXT          0x87AF
#define GL_OUTPUT_TEXTURE_COORD19_EXT          0x87B0
#define GL_OUTPUT_TEXTURE_COORD20_EXT          0x87B1
#define GL_OUTPUT_TEXTURE_COORD21_EXT          0x87B2
#define GL_OUTPUT_TEXTURE_COORD22_EXT          0x87B3
#define GL_OUTPUT_TEXTURE_COORD23_EXT          0x87B4
#define GL_OUTPUT_TEXTURE_COORD24_EXT          0x87B5
#define GL_OUTPUT_TEXTURE_COORD25_EXT          0x87B6
#define GL_OUTPUT_TEXTURE_COORD26_EXT          0x87B7
#define GL_OUTPUT_TEXTURE_COORD27_EXT          0x87B8
#define GL_OUTPUT_TEXTURE_COORD28_EXT          0x87B9
#define GL_OUTPUT_TEXTURE_COORD29_EXT          0x87BA
#define GL_OUTPUT_TEXTURE_COORD30_EXT          0x87BB
#define GL_OUTPUT_TEXTURE_COORD31_EXT          0x87BC
#define GL_OUTPUT_FOG_EXT                      0x87BD
#define GL_SCALAR_EXT                          0x87BE
#define GL_VECTOR_EXT                          0x87BF
#define GL_MATRIX_EXT                          0x87C0
#define GL_VARIANT_EXT                         0x87C1
#define GL_INVARIANT_EXT                       0x87C2
#define GL_LOCAL_CONSTANT_EXT                  0x87C3
#define GL_LOCAL_EXT                           0x87C4
#define GL_MAX_VERTEX_SHADER_INSTRUCTIONS_EXT  0x87C5
#define GL_MAX_VERTEX_SHADER_VARIANTS_EXT      0x87C6
#define GL_MAX_VERTEX_SHADER_INVARIANTS_EXT    0x87C7
#define GL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT  0x87C8
#define GL_MAX_VERTEX_SHADER_LOCALS_EXT        0x87C9
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT  0x87CA
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT  0x87CB
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT  0x87CC
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT  0x87CD
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT  0x87CE
#define GL_VERTEX_SHADER_INSTRUCTIONS_EXT      0x87CF
#define GL_VERTEX_SHADER_VARIANTS_EXT          0x87D0
#define GL_VERTEX_SHADER_INVARIANTS_EXT        0x87D1
#define GL_VERTEX_SHADER_LOCAL_CONSTANTS_EXT   0x87D2
#define GL_VERTEX_SHADER_LOCALS_EXT            0x87D3
#define GL_VERTEX_SHADER_OPTIMIZED_EXT         0x87D4
#define GL_X_EXT                               0x87D5
#define GL_Y_EXT                               0x87D6
#define GL_Z_EXT                               0x87D7
#define GL_W_EXT                               0x87D8
#define GL_NEGATIVE_X_EXT                      0x87D9
#define GL_NEGATIVE_Y_EXT                      0x87DA
#define GL_NEGATIVE_Z_EXT                      0x87DB
#define GL_NEGATIVE_W_EXT                      0x87DC
#define GL_ZERO_EXT                            0x87DD
#define GL_ONE_EXT                             0x87DE
#define GL_NEGATIVE_ONE_EXT                    0x87DF
#define GL_NORMALIZED_RANGE_EXT                0x87E0
#define GL_FULL_RANGE_EXT                      0x87E1
#define GL_CURRENT_VERTEX_EXT                  0x87E2
#define GL_MVP_MATRIX_EXT                      0x87E3
#define GL_VARIANT_VALUE_EXT                   0x87E4
#define GL_VARIANT_DATATYPE_EXT                0x87E5
#define GL_VARIANT_ARRAY_STRIDE_EXT            0x87E6
#define GL_VARIANT_ARRAY_TYPE_EXT              0x87E7
#define GL_VARIANT_ARRAY_EXT                   0x87E8
#define GL_VARIANT_ARRAY_POINTER_EXT           0x87E9
#define GL_INVARIANT_VALUE_EXT                 0x87EA
#define GL_INVARIANT_DATATYPE_EXT              0x87EB
#define GL_LOCAL_CONSTANT_VALUE_EXT            0x87EC
#define GL_LOCAL_CONSTANT_DATATYPE_EXT         0x87ED
typedef void (APIENTRYP pfn_glBeginVertexShaderEXT) ();
extern pfn_glBeginVertexShaderEXT fp_glBeginVertexShaderEXT;
typedef void (APIENTRYP pfn_glEndVertexShaderEXT) ();
extern pfn_glEndVertexShaderEXT fp_glEndVertexShaderEXT;
typedef void (APIENTRYP pfn_glBindVertexShaderEXT) (GLuint);
extern pfn_glBindVertexShaderEXT fp_glBindVertexShaderEXT;
typedef GLuint (APIENTRYP pfn_glGenVertexShadersEXT) (GLuint);
extern pfn_glGenVertexShadersEXT fp_glGenVertexShadersEXT;
typedef void (APIENTRYP pfn_glDeleteVertexShaderEXT) (GLuint);
extern pfn_glDeleteVertexShaderEXT fp_glDeleteVertexShaderEXT;
typedef void (APIENTRYP pfn_glShaderOp1EXT) (GLenum, GLuint, GLuint);
extern pfn_glShaderOp1EXT fp_glShaderOp1EXT;
typedef void (APIENTRYP pfn_glShaderOp2EXT) (GLenum, GLuint, GLuint, GLuint);
extern pfn_glShaderOp2EXT fp_glShaderOp2EXT;
typedef void (APIENTRYP pfn_glShaderOp3EXT) (GLenum, GLuint, GLuint, GLuint, GLuint);
extern pfn_glShaderOp3EXT fp_glShaderOp3EXT;
typedef void (APIENTRYP pfn_glSwizzleEXT) (GLuint, GLuint, GLenum, GLenum, GLenum, GLenum);
extern pfn_glSwizzleEXT fp_glSwizzleEXT;
typedef void (APIENTRYP pfn_glWriteMaskEXT) (GLuint, GLuint, GLenum, GLenum, GLenum, GLenum);
extern pfn_glWriteMaskEXT fp_glWriteMaskEXT;
typedef void (APIENTRYP pfn_glInsertComponentEXT) (GLuint, GLuint, GLuint);
extern pfn_glInsertComponentEXT fp_glInsertComponentEXT;
typedef void (APIENTRYP pfn_glExtractComponentEXT) (GLuint, GLuint, GLuint);
extern pfn_glExtractComponentEXT fp_glExtractComponentEXT;
typedef GLuint (APIENTRYP pfn_glGenSymbolsEXT) (GLenum, GLenum, GLenum, GLuint);
extern pfn_glGenSymbolsEXT fp_glGenSymbolsEXT;
typedef void (APIENTRYP pfn_glSetInvariantEXT) (GLuint, GLenum, const void*);
extern pfn_glSetInvariantEXT fp_glSetInvariantEXT;
typedef void (APIENTRYP pfn_glSetLocalConstantEXT) (GLuint, GLenum, const void*);
extern pfn_glSetLocalConstantEXT fp_glSetLocalConstantEXT;
typedef void (APIENTRYP pfn_glVariantbvEXT) (GLuint, const GLbyte*);
extern pfn_glVariantbvEXT fp_glVariantbvEXT;
typedef void (APIENTRYP pfn_glVariantsvEXT) (GLuint, const GLshort*);
extern pfn_glVariantsvEXT fp_glVariantsvEXT;
typedef void (APIENTRYP pfn_glVariantivEXT) (GLuint, const GLint*);
extern pfn_glVariantivEXT fp_glVariantivEXT;
typedef void (APIENTRYP pfn_glVariantfvEXT) (GLuint, const GLfloat*);
extern pfn_glVariantfvEXT fp_glVariantfvEXT;
typedef void (APIENTRYP pfn_glVariantdvEXT) (GLuint, const GLdouble*);
extern pfn_glVariantdvEXT fp_glVariantdvEXT;
typedef void (APIENTRYP pfn_glVariantubvEXT) (GLuint, const GLubyte*);
extern pfn_glVariantubvEXT fp_glVariantubvEXT;
typedef void (APIENTRYP pfn_glVariantusvEXT) (GLuint, const GLushort*);
extern pfn_glVariantusvEXT fp_glVariantusvEXT;
typedef void (APIENTRYP pfn_glVariantuivEXT) (GLuint, const GLuint*);
extern pfn_glVariantuivEXT fp_glVariantuivEXT;
typedef void (APIENTRYP pfn_glVariantPointerEXT) (GLuint, GLenum, GLuint, const void*);
extern pfn_glVariantPointerEXT fp_glVariantPointerEXT;
typedef void (APIENTRYP pfn_glEnableVariantClientStateEXT) (GLuint);
extern pfn_glEnableVariantClientStateEXT fp_glEnableVariantClientStateEXT;
typedef void (APIENTRYP pfn_glDisableVariantClientStateEXT) (GLuint);
extern pfn_glDisableVariantClientStateEXT fp_glDisableVariantClientStateEXT;
typedef GLuint (APIENTRYP pfn_glBindLightParameterEXT) (GLenum, GLenum);
extern pfn_glBindLightParameterEXT fp_glBindLightParameterEXT;
typedef GLuint (APIENTRYP pfn_glBindMaterialParameterEXT) (GLenum, GLenum);
extern pfn_glBindMaterialParameterEXT fp_glBindMaterialParameterEXT;
typedef GLuint (APIENTRYP pfn_glBindTexGenParameterEXT) (GLenum, GLenum, GLenum);
extern pfn_glBindTexGenParameterEXT fp_glBindTexGenParameterEXT;
typedef GLuint (APIENTRYP pfn_glBindTextureUnitParameterEXT) (GLenum, GLenum);
extern pfn_glBindTextureUnitParameterEXT fp_glBindTextureUnitParameterEXT;
typedef GLuint (APIENTRYP pfn_glBindParameterEXT) (GLenum);
extern pfn_glBindParameterEXT fp_glBindParameterEXT;
typedef GLboolean (APIENTRYP pfn_glIsVariantEnabledEXT) (GLuint, GLenum);
extern pfn_glIsVariantEnabledEXT fp_glIsVariantEnabledEXT;
typedef void (APIENTRYP pfn_glGetVariantBooleanvEXT) (GLuint, GLenum, GLboolean*);
extern pfn_glGetVariantBooleanvEXT fp_glGetVariantBooleanvEXT;
typedef void (APIENTRYP pfn_glGetVariantIntegervEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetVariantIntegervEXT fp_glGetVariantIntegervEXT;
typedef void (APIENTRYP pfn_glGetVariantFloatvEXT) (GLuint, GLenum, GLfloat*);
extern pfn_glGetVariantFloatvEXT fp_glGetVariantFloatvEXT;
typedef void (APIENTRYP pfn_glGetVariantPointervEXT) (GLuint, GLenum, void**);
extern pfn_glGetVariantPointervEXT fp_glGetVariantPointervEXT;
typedef void (APIENTRYP pfn_glGetInvariantBooleanvEXT) (GLuint, GLenum, GLboolean*);
extern pfn_glGetInvariantBooleanvEXT fp_glGetInvariantBooleanvEXT;
typedef void (APIENTRYP pfn_glGetInvariantIntegervEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetInvariantIntegervEXT fp_glGetInvariantIntegervEXT;
typedef void (APIENTRYP pfn_glGetInvariantFloatvEXT) (GLuint, GLenum, GLfloat*);
extern pfn_glGetInvariantFloatvEXT fp_glGetInvariantFloatvEXT;
typedef void (APIENTRYP pfn_glGetLocalConstantBooleanvEXT) (GLuint, GLenum, GLboolean*);
extern pfn_glGetLocalConstantBooleanvEXT fp_glGetLocalConstantBooleanvEXT;
typedef void (APIENTRYP pfn_glGetLocalConstantIntegervEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetLocalConstantIntegervEXT fp_glGetLocalConstantIntegervEXT;
typedef void (APIENTRYP pfn_glGetLocalConstantFloatvEXT) (GLuint, GLenum, GLfloat*);
extern pfn_glGetLocalConstantFloatvEXT fp_glGetLocalConstantFloatvEXT;

 /* GL_EXT_vertex_weighting */
extern GLboolean GLAD_EXT_vertex_weighting;
#define GL_MODELVIEW0_STACK_DEPTH_EXT          0x0BA3
#define GL_MODELVIEW1_STACK_DEPTH_EXT          0x8502
#define GL_MODELVIEW0_MATRIX_EXT               0x0BA6
#define GL_MODELVIEW1_MATRIX_EXT               0x8506
#define GL_VERTEX_WEIGHTING_EXT                0x8509
#define GL_MODELVIEW0_EXT                      0x1700
#define GL_MODELVIEW1_EXT                      0x850A
#define GL_CURRENT_VERTEX_WEIGHT_EXT           0x850B
#define GL_VERTEX_WEIGHT_ARRAY_EXT             0x850C
#define GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT        0x850D
#define GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT        0x850E
#define GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT      0x850F
#define GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT     0x8510
typedef void (APIENTRYP pfn_glVertexWeightfEXT) (GLfloat);
extern pfn_glVertexWeightfEXT fp_glVertexWeightfEXT;
typedef void (APIENTRYP pfn_glVertexWeightfvEXT) (const GLfloat*);
extern pfn_glVertexWeightfvEXT fp_glVertexWeightfvEXT;
typedef void (APIENTRYP pfn_glVertexWeightPointerEXT) (GLint, GLenum, GLsizei, const void*);
extern pfn_glVertexWeightPointerEXT fp_glVertexWeightPointerEXT;

 /* GL_EXT_x11_sync_object */
extern GLboolean GLAD_EXT_x11_sync_object;
#define GL_SYNC_X11_FENCE_EXT                  0x90E1
typedef GLsync (APIENTRYP pfn_glImportSyncEXT) (GLenum, GLintptr, GLbitfield);
extern pfn_glImportSyncEXT fp_glImportSyncEXT;

 /* GL_OES_byte_coordinates */
extern GLboolean GLAD_OES_byte_coordinates;
typedef void (APIENTRYP pfn_glMultiTexCoord1bOES) (GLenum, GLbyte);
extern pfn_glMultiTexCoord1bOES fp_glMultiTexCoord1bOES;
typedef void (APIENTRYP pfn_glMultiTexCoord1bvOES) (GLenum, const GLbyte*);
extern pfn_glMultiTexCoord1bvOES fp_glMultiTexCoord1bvOES;
typedef void (APIENTRYP pfn_glMultiTexCoord2bOES) (GLenum, GLbyte, GLbyte);
extern pfn_glMultiTexCoord2bOES fp_glMultiTexCoord2bOES;
typedef void (APIENTRYP pfn_glMultiTexCoord2bvOES) (GLenum, const GLbyte*);
extern pfn_glMultiTexCoord2bvOES fp_glMultiTexCoord2bvOES;
typedef void (APIENTRYP pfn_glMultiTexCoord3bOES) (GLenum, GLbyte, GLbyte, GLbyte);
extern pfn_glMultiTexCoord3bOES fp_glMultiTexCoord3bOES;
typedef void (APIENTRYP pfn_glMultiTexCoord3bvOES) (GLenum, const GLbyte*);
extern pfn_glMultiTexCoord3bvOES fp_glMultiTexCoord3bvOES;
typedef void (APIENTRYP pfn_glMultiTexCoord4bOES) (GLenum, GLbyte, GLbyte, GLbyte, GLbyte);
extern pfn_glMultiTexCoord4bOES fp_glMultiTexCoord4bOES;
typedef void (APIENTRYP pfn_glMultiTexCoord4bvOES) (GLenum, const GLbyte*);
extern pfn_glMultiTexCoord4bvOES fp_glMultiTexCoord4bvOES;
typedef void (APIENTRYP pfn_glTexCoord1bOES) (GLbyte);
extern pfn_glTexCoord1bOES fp_glTexCoord1bOES;
typedef void (APIENTRYP pfn_glTexCoord1bvOES) (const GLbyte*);
extern pfn_glTexCoord1bvOES fp_glTexCoord1bvOES;
typedef void (APIENTRYP pfn_glTexCoord2bOES) (GLbyte, GLbyte);
extern pfn_glTexCoord2bOES fp_glTexCoord2bOES;
typedef void (APIENTRYP pfn_glTexCoord2bvOES) (const GLbyte*);
extern pfn_glTexCoord2bvOES fp_glTexCoord2bvOES;
typedef void (APIENTRYP pfn_glTexCoord3bOES) (GLbyte, GLbyte, GLbyte);
extern pfn_glTexCoord3bOES fp_glTexCoord3bOES;
typedef void (APIENTRYP pfn_glTexCoord3bvOES) (const GLbyte*);
extern pfn_glTexCoord3bvOES fp_glTexCoord3bvOES;
typedef void (APIENTRYP pfn_glTexCoord4bOES) (GLbyte, GLbyte, GLbyte, GLbyte);
extern pfn_glTexCoord4bOES fp_glTexCoord4bOES;
typedef void (APIENTRYP pfn_glTexCoord4bvOES) (const GLbyte*);
extern pfn_glTexCoord4bvOES fp_glTexCoord4bvOES;
typedef void (APIENTRYP pfn_glVertex2bOES) (GLbyte);
extern pfn_glVertex2bOES fp_glVertex2bOES;
typedef void (APIENTRYP pfn_glVertex2bvOES) (const GLbyte*);
extern pfn_glVertex2bvOES fp_glVertex2bvOES;
typedef void (APIENTRYP pfn_glVertex3bOES) (GLbyte, GLbyte);
extern pfn_glVertex3bOES fp_glVertex3bOES;
typedef void (APIENTRYP pfn_glVertex3bvOES) (const GLbyte*);
extern pfn_glVertex3bvOES fp_glVertex3bvOES;
typedef void (APIENTRYP pfn_glVertex4bOES) (GLbyte, GLbyte, GLbyte);
extern pfn_glVertex4bOES fp_glVertex4bOES;
typedef void (APIENTRYP pfn_glVertex4bvOES) (const GLbyte*);
extern pfn_glVertex4bvOES fp_glVertex4bvOES;

 /* GL_OES_compressed_ETC1_RGB8_texture */
extern GLboolean GLAD_OES_compressed_ETC1_RGB8_texture;
#define GL_ETC1_RGB8_OES                       0x8D64

 /* GL_OES_compressed_paletted_texture */
extern GLboolean GLAD_OES_compressed_paletted_texture;
#define GL_PALETTE4_RGB8_OES                   0x8B90
#define GL_PALETTE4_RGBA8_OES                  0x8B91
#define GL_PALETTE4_R5_G6_B5_OES               0x8B92
#define GL_PALETTE4_RGBA4_OES                  0x8B93
#define GL_PALETTE4_RGB5_A1_OES                0x8B94
#define GL_PALETTE8_RGB8_OES                   0x8B95
#define GL_PALETTE8_RGBA8_OES                  0x8B96
#define GL_PALETTE8_R5_G6_B5_OES               0x8B97
#define GL_PALETTE8_RGBA4_OES                  0x8B98
#define GL_PALETTE8_RGB5_A1_OES                0x8B99

 /* GL_OES_depth24 */
extern GLboolean GLAD_OES_depth24;
#define GL_DEPTH_COMPONENT24_OES               0x81A6

 /* GL_OES_depth32 */
extern GLboolean GLAD_OES_depth32;
#define GL_DEPTH_COMPONENT32_OES               0x81A7

 /* GL_OES_depth_texture */
extern GLboolean GLAD_OES_depth_texture;

 /* GL_OES_EGL_image */
extern GLboolean GLAD_OES_EGL_image;
typedef void (APIENTRYP pfn_glEGLImageTargetTexture2DOES) (GLenum, GLeglImageOES);
extern pfn_glEGLImageTargetTexture2DOES fp_glEGLImageTargetTexture2DOES;
typedef void (APIENTRYP pfn_glEGLImageTargetRenderbufferStorageOES) (GLenum, GLeglImageOES);
extern pfn_glEGLImageTargetRenderbufferStorageOES fp_glEGLImageTargetRenderbufferStorageOES;

 /* GL_OES_EGL_image_external */
extern GLboolean GLAD_OES_EGL_image_external;
#define GL_TEXTURE_EXTERNAL_OES                0x8D65
#define GL_TEXTURE_BINDING_EXTERNAL_OES        0x8D67
#define GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES    0x8D68
#define GL_SAMPLER_EXTERNAL_OES                0x8D66

 /* GL_OES_element_index_uint */
extern GLboolean GLAD_OES_element_index_uint;

 /* GL_OES_fbo_render_mipmap */
extern GLboolean GLAD_OES_fbo_render_mipmap;

 /* GL_OES_fixed_point */
extern GLboolean GLAD_OES_fixed_point;
#define GL_FIXED_OES                           0x140C
typedef void (APIENTRYP pfn_glAlphaFuncxOES) (GLenum, GLfixed);
extern pfn_glAlphaFuncxOES fp_glAlphaFuncxOES;
typedef void (APIENTRYP pfn_glClearColorxOES) (GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glClearColorxOES fp_glClearColorxOES;
typedef void (APIENTRYP pfn_glClearDepthxOES) (GLfixed);
extern pfn_glClearDepthxOES fp_glClearDepthxOES;
typedef void (APIENTRYP pfn_glClipPlanexOES) (GLenum, const GLfixed*);
extern pfn_glClipPlanexOES fp_glClipPlanexOES;
typedef void (APIENTRYP pfn_glColor4xOES) (GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glColor4xOES fp_glColor4xOES;
typedef void (APIENTRYP pfn_glDepthRangexOES) (GLfixed, GLfixed);
extern pfn_glDepthRangexOES fp_glDepthRangexOES;
typedef void (APIENTRYP pfn_glFogxOES) (GLenum, GLfixed);
extern pfn_glFogxOES fp_glFogxOES;
typedef void (APIENTRYP pfn_glFogxvOES) (GLenum, const GLfixed*);
extern pfn_glFogxvOES fp_glFogxvOES;
typedef void (APIENTRYP pfn_glFrustumxOES) (GLfixed, GLfixed, GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glFrustumxOES fp_glFrustumxOES;
typedef void (APIENTRYP pfn_glGetClipPlanexOES) (GLenum, GLfixed*);
extern pfn_glGetClipPlanexOES fp_glGetClipPlanexOES;
typedef void (APIENTRYP pfn_glGetFixedvOES) (GLenum, GLfixed*);
extern pfn_glGetFixedvOES fp_glGetFixedvOES;
typedef void (APIENTRYP pfn_glGetTexEnvxvOES) (GLenum, GLenum, GLfixed*);
extern pfn_glGetTexEnvxvOES fp_glGetTexEnvxvOES;
typedef void (APIENTRYP pfn_glGetTexParameterxvOES) (GLenum, GLenum, GLfixed*);
extern pfn_glGetTexParameterxvOES fp_glGetTexParameterxvOES;
typedef void (APIENTRYP pfn_glLightModelxOES) (GLenum, GLfixed);
extern pfn_glLightModelxOES fp_glLightModelxOES;
typedef void (APIENTRYP pfn_glLightModelxvOES) (GLenum, const GLfixed*);
extern pfn_glLightModelxvOES fp_glLightModelxvOES;
typedef void (APIENTRYP pfn_glLightxOES) (GLenum, GLenum, GLfixed);
extern pfn_glLightxOES fp_glLightxOES;
typedef void (APIENTRYP pfn_glLightxvOES) (GLenum, GLenum, const GLfixed*);
extern pfn_glLightxvOES fp_glLightxvOES;
typedef void (APIENTRYP pfn_glLineWidthxOES) (GLfixed);
extern pfn_glLineWidthxOES fp_glLineWidthxOES;
typedef void (APIENTRYP pfn_glLoadMatrixxOES) (const GLfixed*);
extern pfn_glLoadMatrixxOES fp_glLoadMatrixxOES;
typedef void (APIENTRYP pfn_glMaterialxOES) (GLenum, GLenum, GLfixed);
extern pfn_glMaterialxOES fp_glMaterialxOES;
typedef void (APIENTRYP pfn_glMaterialxvOES) (GLenum, GLenum, const GLfixed*);
extern pfn_glMaterialxvOES fp_glMaterialxvOES;
typedef void (APIENTRYP pfn_glMultMatrixxOES) (const GLfixed*);
extern pfn_glMultMatrixxOES fp_glMultMatrixxOES;
typedef void (APIENTRYP pfn_glMultiTexCoord4xOES) (GLenum, GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glMultiTexCoord4xOES fp_glMultiTexCoord4xOES;
typedef void (APIENTRYP pfn_glNormal3xOES) (GLfixed, GLfixed, GLfixed);
extern pfn_glNormal3xOES fp_glNormal3xOES;
typedef void (APIENTRYP pfn_glOrthoxOES) (GLfixed, GLfixed, GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glOrthoxOES fp_glOrthoxOES;
typedef void (APIENTRYP pfn_glPointParameterxvOES) (GLenum, const GLfixed*);
extern pfn_glPointParameterxvOES fp_glPointParameterxvOES;
typedef void (APIENTRYP pfn_glPointSizexOES) (GLfixed);
extern pfn_glPointSizexOES fp_glPointSizexOES;
typedef void (APIENTRYP pfn_glPolygonOffsetxOES) (GLfixed, GLfixed);
extern pfn_glPolygonOffsetxOES fp_glPolygonOffsetxOES;
typedef void (APIENTRYP pfn_glRotatexOES) (GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glRotatexOES fp_glRotatexOES;
typedef void (APIENTRYP pfn_glSampleCoverageOES) (GLfixed, GLboolean);
extern pfn_glSampleCoverageOES fp_glSampleCoverageOES;
typedef void (APIENTRYP pfn_glScalexOES) (GLfixed, GLfixed, GLfixed);
extern pfn_glScalexOES fp_glScalexOES;
typedef void (APIENTRYP pfn_glTexEnvxOES) (GLenum, GLenum, GLfixed);
extern pfn_glTexEnvxOES fp_glTexEnvxOES;
typedef void (APIENTRYP pfn_glTexEnvxvOES) (GLenum, GLenum, const GLfixed*);
extern pfn_glTexEnvxvOES fp_glTexEnvxvOES;
typedef void (APIENTRYP pfn_glTexParameterxOES) (GLenum, GLenum, GLfixed);
extern pfn_glTexParameterxOES fp_glTexParameterxOES;
typedef void (APIENTRYP pfn_glTexParameterxvOES) (GLenum, GLenum, const GLfixed*);
extern pfn_glTexParameterxvOES fp_glTexParameterxvOES;
typedef void (APIENTRYP pfn_glTranslatexOES) (GLfixed, GLfixed, GLfixed);
extern pfn_glTranslatexOES fp_glTranslatexOES;
typedef void (APIENTRYP pfn_glGetLightxvOES) (GLenum, GLenum, GLfixed*);
extern pfn_glGetLightxvOES fp_glGetLightxvOES;
typedef void (APIENTRYP pfn_glGetMaterialxvOES) (GLenum, GLenum, GLfixed*);
extern pfn_glGetMaterialxvOES fp_glGetMaterialxvOES;
typedef void (APIENTRYP pfn_glPointParameterxOES) (GLenum, GLfixed);
extern pfn_glPointParameterxOES fp_glPointParameterxOES;
typedef void (APIENTRYP pfn_glSampleCoveragexOES) (GLclampx, GLboolean);
extern pfn_glSampleCoveragexOES fp_glSampleCoveragexOES;
typedef void (APIENTRYP pfn_glAccumxOES) (GLenum, GLfixed);
extern pfn_glAccumxOES fp_glAccumxOES;
typedef void (APIENTRYP pfn_glBitmapxOES) (GLsizei, GLsizei, GLfixed, GLfixed, GLfixed, GLfixed, const GLubyte*);
extern pfn_glBitmapxOES fp_glBitmapxOES;
typedef void (APIENTRYP pfn_glBlendColorxOES) (GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glBlendColorxOES fp_glBlendColorxOES;
typedef void (APIENTRYP pfn_glClearAccumxOES) (GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glClearAccumxOES fp_glClearAccumxOES;
typedef void (APIENTRYP pfn_glColor3xOES) (GLfixed, GLfixed, GLfixed);
extern pfn_glColor3xOES fp_glColor3xOES;
typedef void (APIENTRYP pfn_glColor3xvOES) (const GLfixed*);
extern pfn_glColor3xvOES fp_glColor3xvOES;
typedef void (APIENTRYP pfn_glColor4xvOES) (const GLfixed*);
extern pfn_glColor4xvOES fp_glColor4xvOES;
typedef void (APIENTRYP pfn_glConvolutionParameterxOES) (GLenum, GLenum, GLfixed);
extern pfn_glConvolutionParameterxOES fp_glConvolutionParameterxOES;
typedef void (APIENTRYP pfn_glConvolutionParameterxvOES) (GLenum, GLenum, const GLfixed*);
extern pfn_glConvolutionParameterxvOES fp_glConvolutionParameterxvOES;
typedef void (APIENTRYP pfn_glEvalCoord1xOES) (GLfixed);
extern pfn_glEvalCoord1xOES fp_glEvalCoord1xOES;
typedef void (APIENTRYP pfn_glEvalCoord1xvOES) (const GLfixed*);
extern pfn_glEvalCoord1xvOES fp_glEvalCoord1xvOES;
typedef void (APIENTRYP pfn_glEvalCoord2xOES) (GLfixed, GLfixed);
extern pfn_glEvalCoord2xOES fp_glEvalCoord2xOES;
typedef void (APIENTRYP pfn_glEvalCoord2xvOES) (const GLfixed*);
extern pfn_glEvalCoord2xvOES fp_glEvalCoord2xvOES;
typedef void (APIENTRYP pfn_glFeedbackBufferxOES) (GLsizei, GLenum, const GLfixed*);
extern pfn_glFeedbackBufferxOES fp_glFeedbackBufferxOES;
typedef void (APIENTRYP pfn_glGetConvolutionParameterxvOES) (GLenum, GLenum, GLfixed*);
extern pfn_glGetConvolutionParameterxvOES fp_glGetConvolutionParameterxvOES;
typedef void (APIENTRYP pfn_glGetHistogramParameterxvOES) (GLenum, GLenum, GLfixed*);
extern pfn_glGetHistogramParameterxvOES fp_glGetHistogramParameterxvOES;
typedef void (APIENTRYP pfn_glGetLightxOES) (GLenum, GLenum, GLfixed*);
extern pfn_glGetLightxOES fp_glGetLightxOES;
typedef void (APIENTRYP pfn_glGetMapxvOES) (GLenum, GLenum, GLfixed*);
extern pfn_glGetMapxvOES fp_glGetMapxvOES;
typedef void (APIENTRYP pfn_glGetMaterialxOES) (GLenum, GLenum, GLfixed);
extern pfn_glGetMaterialxOES fp_glGetMaterialxOES;
typedef void (APIENTRYP pfn_glGetPixelMapxv) (GLenum, GLint, GLfixed*);
extern pfn_glGetPixelMapxv fp_glGetPixelMapxv;
typedef void (APIENTRYP pfn_glGetTexGenxvOES) (GLenum, GLenum, GLfixed*);
extern pfn_glGetTexGenxvOES fp_glGetTexGenxvOES;
typedef void (APIENTRYP pfn_glGetTexLevelParameterxvOES) (GLenum, GLint, GLenum, GLfixed*);
extern pfn_glGetTexLevelParameterxvOES fp_glGetTexLevelParameterxvOES;
typedef void (APIENTRYP pfn_glIndexxOES) (GLfixed);
extern pfn_glIndexxOES fp_glIndexxOES;
typedef void (APIENTRYP pfn_glIndexxvOES) (const GLfixed*);
extern pfn_glIndexxvOES fp_glIndexxvOES;
typedef void (APIENTRYP pfn_glLoadTransposeMatrixxOES) (const GLfixed*);
extern pfn_glLoadTransposeMatrixxOES fp_glLoadTransposeMatrixxOES;
typedef void (APIENTRYP pfn_glMap1xOES) (GLenum, GLfixed, GLfixed, GLint, GLint, GLfixed);
extern pfn_glMap1xOES fp_glMap1xOES;
typedef void (APIENTRYP pfn_glMap2xOES) (GLenum, GLfixed, GLfixed, GLint, GLint, GLfixed, GLfixed, GLint, GLint, GLfixed);
extern pfn_glMap2xOES fp_glMap2xOES;
typedef void (APIENTRYP pfn_glMapGrid1xOES) (GLint, GLfixed, GLfixed);
extern pfn_glMapGrid1xOES fp_glMapGrid1xOES;
typedef void (APIENTRYP pfn_glMapGrid2xOES) (GLint, GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glMapGrid2xOES fp_glMapGrid2xOES;
typedef void (APIENTRYP pfn_glMultTransposeMatrixxOES) (const GLfixed*);
extern pfn_glMultTransposeMatrixxOES fp_glMultTransposeMatrixxOES;
typedef void (APIENTRYP pfn_glMultiTexCoord1xOES) (GLenum, GLfixed);
extern pfn_glMultiTexCoord1xOES fp_glMultiTexCoord1xOES;
typedef void (APIENTRYP pfn_glMultiTexCoord1xvOES) (GLenum, const GLfixed*);
extern pfn_glMultiTexCoord1xvOES fp_glMultiTexCoord1xvOES;
typedef void (APIENTRYP pfn_glMultiTexCoord2xOES) (GLenum, GLfixed, GLfixed);
extern pfn_glMultiTexCoord2xOES fp_glMultiTexCoord2xOES;
typedef void (APIENTRYP pfn_glMultiTexCoord2xvOES) (GLenum, const GLfixed*);
extern pfn_glMultiTexCoord2xvOES fp_glMultiTexCoord2xvOES;
typedef void (APIENTRYP pfn_glMultiTexCoord3xOES) (GLenum, GLfixed, GLfixed, GLfixed);
extern pfn_glMultiTexCoord3xOES fp_glMultiTexCoord3xOES;
typedef void (APIENTRYP pfn_glMultiTexCoord3xvOES) (GLenum, const GLfixed*);
extern pfn_glMultiTexCoord3xvOES fp_glMultiTexCoord3xvOES;
typedef void (APIENTRYP pfn_glMultiTexCoord4xvOES) (GLenum, const GLfixed*);
extern pfn_glMultiTexCoord4xvOES fp_glMultiTexCoord4xvOES;
typedef void (APIENTRYP pfn_glNormal3xvOES) (const GLfixed*);
extern pfn_glNormal3xvOES fp_glNormal3xvOES;
typedef void (APIENTRYP pfn_glPassThroughxOES) (GLfixed);
extern pfn_glPassThroughxOES fp_glPassThroughxOES;
typedef void (APIENTRYP pfn_glPixelMapx) (GLenum, GLint, const GLfixed*);
extern pfn_glPixelMapx fp_glPixelMapx;
typedef void (APIENTRYP pfn_glPixelStorex) (GLenum, GLfixed);
extern pfn_glPixelStorex fp_glPixelStorex;
typedef void (APIENTRYP pfn_glPixelTransferxOES) (GLenum, GLfixed);
extern pfn_glPixelTransferxOES fp_glPixelTransferxOES;
typedef void (APIENTRYP pfn_glPixelZoomxOES) (GLfixed, GLfixed);
extern pfn_glPixelZoomxOES fp_glPixelZoomxOES;
typedef void (APIENTRYP pfn_glPrioritizeTexturesxOES) (GLsizei, const GLuint*, const GLfixed*);
extern pfn_glPrioritizeTexturesxOES fp_glPrioritizeTexturesxOES;
typedef void (APIENTRYP pfn_glRasterPos2xOES) (GLfixed, GLfixed);
extern pfn_glRasterPos2xOES fp_glRasterPos2xOES;
typedef void (APIENTRYP pfn_glRasterPos2xvOES) (const GLfixed*);
extern pfn_glRasterPos2xvOES fp_glRasterPos2xvOES;
typedef void (APIENTRYP pfn_glRasterPos3xOES) (GLfixed, GLfixed, GLfixed);
extern pfn_glRasterPos3xOES fp_glRasterPos3xOES;
typedef void (APIENTRYP pfn_glRasterPos3xvOES) (const GLfixed*);
extern pfn_glRasterPos3xvOES fp_glRasterPos3xvOES;
typedef void (APIENTRYP pfn_glRasterPos4xOES) (GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glRasterPos4xOES fp_glRasterPos4xOES;
typedef void (APIENTRYP pfn_glRasterPos4xvOES) (const GLfixed*);
extern pfn_glRasterPos4xvOES fp_glRasterPos4xvOES;
typedef void (APIENTRYP pfn_glRectxOES) (GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glRectxOES fp_glRectxOES;
typedef void (APIENTRYP pfn_glRectxvOES) (const GLfixed*, const GLfixed*);
extern pfn_glRectxvOES fp_glRectxvOES;
typedef void (APIENTRYP pfn_glTexCoord1xOES) (GLfixed);
extern pfn_glTexCoord1xOES fp_glTexCoord1xOES;
typedef void (APIENTRYP pfn_glTexCoord1xvOES) (const GLfixed*);
extern pfn_glTexCoord1xvOES fp_glTexCoord1xvOES;
typedef void (APIENTRYP pfn_glTexCoord2xOES) (GLfixed, GLfixed);
extern pfn_glTexCoord2xOES fp_glTexCoord2xOES;
typedef void (APIENTRYP pfn_glTexCoord2xvOES) (const GLfixed*);
extern pfn_glTexCoord2xvOES fp_glTexCoord2xvOES;
typedef void (APIENTRYP pfn_glTexCoord3xOES) (GLfixed, GLfixed, GLfixed);
extern pfn_glTexCoord3xOES fp_glTexCoord3xOES;
typedef void (APIENTRYP pfn_glTexCoord3xvOES) (const GLfixed*);
extern pfn_glTexCoord3xvOES fp_glTexCoord3xvOES;
typedef void (APIENTRYP pfn_glTexCoord4xOES) (GLfixed, GLfixed, GLfixed, GLfixed);
extern pfn_glTexCoord4xOES fp_glTexCoord4xOES;
typedef void (APIENTRYP pfn_glTexCoord4xvOES) (const GLfixed*);
extern pfn_glTexCoord4xvOES fp_glTexCoord4xvOES;
typedef void (APIENTRYP pfn_glTexGenxOES) (GLenum, GLenum, GLfixed);
extern pfn_glTexGenxOES fp_glTexGenxOES;
typedef void (APIENTRYP pfn_glTexGenxvOES) (GLenum, GLenum, const GLfixed*);
extern pfn_glTexGenxvOES fp_glTexGenxvOES;
typedef void (APIENTRYP pfn_glVertex2xOES) (GLfixed);
extern pfn_glVertex2xOES fp_glVertex2xOES;
typedef void (APIENTRYP pfn_glVertex2xvOES) (const GLfixed*);
extern pfn_glVertex2xvOES fp_glVertex2xvOES;
typedef void (APIENTRYP pfn_glVertex3xOES) (GLfixed, GLfixed);
extern pfn_glVertex3xOES fp_glVertex3xOES;
typedef void (APIENTRYP pfn_glVertex3xvOES) (const GLfixed*);
extern pfn_glVertex3xvOES fp_glVertex3xvOES;
typedef void (APIENTRYP pfn_glVertex4xOES) (GLfixed, GLfixed, GLfixed);
extern pfn_glVertex4xOES fp_glVertex4xOES;
typedef void (APIENTRYP pfn_glVertex4xvOES) (const GLfixed*);
extern pfn_glVertex4xvOES fp_glVertex4xvOES;

 /* GL_OES_fragment_precision_high */
extern GLboolean GLAD_OES_fragment_precision_high;

 /* GL_OES_get_program_binary */
extern GLboolean GLAD_OES_get_program_binary;
#define GL_PROGRAM_BINARY_LENGTH_OES           0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS_OES      0x87FE
#define GL_PROGRAM_BINARY_FORMATS_OES          0x87FF
typedef void (APIENTRYP pfn_glGetProgramBinaryOES) (GLuint, GLsizei, GLsizei*, GLenum*, void*);
extern pfn_glGetProgramBinaryOES fp_glGetProgramBinaryOES;
typedef void (APIENTRYP pfn_glProgramBinaryOES) (GLuint, GLenum, const void*, GLint);
extern pfn_glProgramBinaryOES fp_glProgramBinaryOES;

 /* GL_OES_mapbuffer */
extern GLboolean GLAD_OES_mapbuffer;
#define GL_WRITE_ONLY_OES                      0x88B9
#define GL_BUFFER_ACCESS_OES                   0x88BB
#define GL_BUFFER_MAPPED_OES                   0x88BC
#define GL_BUFFER_MAP_POINTER_OES              0x88BD
typedef void* (APIENTRYP pfn_glMapBufferOES) (GLenum, GLenum);
extern pfn_glMapBufferOES fp_glMapBufferOES;
typedef GLboolean (APIENTRYP pfn_glUnmapBufferOES) (GLenum);
extern pfn_glUnmapBufferOES fp_glUnmapBufferOES;
typedef void (APIENTRYP pfn_glGetBufferPointervOES) (GLenum, GLenum, void**);
extern pfn_glGetBufferPointervOES fp_glGetBufferPointervOES;

 /* GL_OES_packed_depth_stencil */
extern GLboolean GLAD_OES_packed_depth_stencil;
#define GL_DEPTH_STENCIL_OES                   0x84F9
#define GL_UNSIGNED_INT_24_8_OES               0x84FA
#define GL_DEPTH24_STENCIL8_OES                0x88F0

 /* GL_OES_query_matrix */
extern GLboolean GLAD_OES_query_matrix;
typedef GLbitfield (APIENTRYP pfn_glQueryMatrixxOES) (GLfixed*, GLint*);
extern pfn_glQueryMatrixxOES fp_glQueryMatrixxOES;

 /* GL_OES_read_format */
extern GLboolean GLAD_OES_read_format;
#define GL_IMPLEMENTATION_COLOR_READ_TYPE_OES  0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES  0x8B9B

 /* GL_OES_required_internalformat */
extern GLboolean GLAD_OES_required_internalformat;
#define GL_ALPHA8_OES                          0x803C
#define GL_DEPTH_COMPONENT16_OES               0x81A5
#define GL_LUMINANCE4_ALPHA4_OES               0x8043
#define GL_LUMINANCE8_ALPHA8_OES               0x8045
#define GL_LUMINANCE8_OES                      0x8040
#define GL_RGBA4_OES                           0x8056
#define GL_RGB5_A1_OES                         0x8057
#define GL_RGB565_OES                          0x8D62
#define GL_RGB8_OES                            0x8051
#define GL_RGBA8_OES                           0x8058

 /* GL_OES_rgb8_rgba8 */
extern GLboolean GLAD_OES_rgb8_rgba8;

 /* GL_OES_single_precision */
extern GLboolean GLAD_OES_single_precision;
typedef void (APIENTRYP pfn_glClearDepthfOES) (GLclampf);
extern pfn_glClearDepthfOES fp_glClearDepthfOES;
typedef void (APIENTRYP pfn_glClipPlanefOES) (GLenum, const GLfloat*);
extern pfn_glClipPlanefOES fp_glClipPlanefOES;
typedef void (APIENTRYP pfn_glDepthRangefOES) (GLclampf, GLclampf);
extern pfn_glDepthRangefOES fp_glDepthRangefOES;
typedef void (APIENTRYP pfn_glFrustumfOES) (GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glFrustumfOES fp_glFrustumfOES;
typedef void (APIENTRYP pfn_glGetClipPlanefOES) (GLenum, GLfloat*);
extern pfn_glGetClipPlanefOES fp_glGetClipPlanefOES;
typedef void (APIENTRYP pfn_glOrthofOES) (GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glOrthofOES fp_glOrthofOES;

 /* GL_OES_standard_derivatives */
extern GLboolean GLAD_OES_standard_derivatives;
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES  0x8B8B

 /* GL_OES_stencil1 */
extern GLboolean GLAD_OES_stencil1;
#define GL_STENCIL_INDEX1_OES                  0x8D46

 /* GL_OES_stencil4 */
extern GLboolean GLAD_OES_stencil4;
#define GL_STENCIL_INDEX4_OES                  0x8D47

 /* GL_OES_surfaceless_context */
extern GLboolean GLAD_OES_surfaceless_context;
#define GL_FRAMEBUFFER_UNDEFINED_OES           0x8219

 /* GL_OES_texture_3D */
extern GLboolean GLAD_OES_texture_3D;
#define GL_TEXTURE_WRAP_R_OES                  0x8072
#define GL_TEXTURE_3D_OES                      0x806F
#define GL_TEXTURE_BINDING_3D_OES              0x806A
#define GL_MAX_3D_TEXTURE_SIZE_OES             0x8073
#define GL_SAMPLER_3D_OES                      0x8B5F
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES  0x8CD4
typedef void (APIENTRYP pfn_glTexImage3DOES) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
extern pfn_glTexImage3DOES fp_glTexImage3DOES;
typedef void (APIENTRYP pfn_glTexSubImage3DOES) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void*);
extern pfn_glTexSubImage3DOES fp_glTexSubImage3DOES;
typedef void (APIENTRYP pfn_glCopyTexSubImage3DOES) (GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
extern pfn_glCopyTexSubImage3DOES fp_glCopyTexSubImage3DOES;
typedef void (APIENTRYP pfn_glCompressedTexImage3DOES) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void*);
extern pfn_glCompressedTexImage3DOES fp_glCompressedTexImage3DOES;
typedef void (APIENTRYP pfn_glCompressedTexSubImage3DOES) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void*);
extern pfn_glCompressedTexSubImage3DOES fp_glCompressedTexSubImage3DOES;
typedef void (APIENTRYP pfn_glFramebufferTexture3DOES) (GLenum, GLenum, GLenum, GLuint, GLint, GLint);
extern pfn_glFramebufferTexture3DOES fp_glFramebufferTexture3DOES;

 /* GL_OES_texture_compression_astc */
extern GLboolean GLAD_OES_texture_compression_astc;

 /* GL_OES_texture_float */
extern GLboolean GLAD_OES_texture_float;

 /* GL_OES_texture_float_linear */
extern GLboolean GLAD_OES_texture_float_linear;

 /* GL_OES_texture_half_float */
extern GLboolean GLAD_OES_texture_half_float;
#define GL_HALF_FLOAT_OES                      0x8D61

 /* GL_OES_texture_half_float_linear */
extern GLboolean GLAD_OES_texture_half_float_linear;

 /* GL_OES_texture_npot */
extern GLboolean GLAD_OES_texture_npot;

 /* GL_OES_vertex_array_object */
extern GLboolean GLAD_OES_vertex_array_object;
#define GL_VERTEX_ARRAY_BINDING_OES            0x85B5
typedef void (APIENTRYP pfn_glBindVertexArrayOES) (GLuint);
extern pfn_glBindVertexArrayOES fp_glBindVertexArrayOES;
typedef void (APIENTRYP pfn_glDeleteVertexArraysOES) (GLsizei, const GLuint*);
extern pfn_glDeleteVertexArraysOES fp_glDeleteVertexArraysOES;
typedef void (APIENTRYP pfn_glGenVertexArraysOES) (GLsizei, GLuint*);
extern pfn_glGenVertexArraysOES fp_glGenVertexArraysOES;
typedef GLboolean (APIENTRYP pfn_glIsVertexArrayOES) (GLuint);
extern pfn_glIsVertexArrayOES fp_glIsVertexArrayOES;

 /* GL_OES_vertex_half_float */
extern GLboolean GLAD_OES_vertex_half_float;

 /* GL_OES_vertex_type_10_10_10_2 */
extern GLboolean GLAD_OES_vertex_type_10_10_10_2;
#define GL_UNSIGNED_INT_10_10_10_2_OES         0x8DF6
#define GL_INT_10_10_10_2_OES                  0x8DF7

 /* GL_AMD_blend_minmax_factor */
extern GLboolean GLAD_AMD_blend_minmax_factor;
#define GL_FACTOR_MIN_AMD                      0x901C
#define GL_FACTOR_MAX_AMD                      0x901D

 /* GL_AMD_compressed_3DC_texture */
extern GLboolean GLAD_AMD_compressed_3DC_texture;
#define GL_3DC_X_AMD                           0x87F9
#define GL_3DC_XY_AMD                          0x87FA

 /* GL_AMD_compressed_ATC_texture */
extern GLboolean GLAD_AMD_compressed_ATC_texture;
#define GL_ATC_RGB_AMD                         0x8C92
#define GL_ATC_RGBA_EXPLICIT_ALPHA_AMD         0x8C93
#define GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD     0x87EE

 /* GL_AMD_conservative_depth */
extern GLboolean GLAD_AMD_conservative_depth;

 /* GL_AMD_debug_output */
extern GLboolean GLAD_AMD_debug_output;
#define GL_MAX_DEBUG_MESSAGE_LENGTH_AMD        0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES_AMD       0x9144
#define GL_DEBUG_LOGGED_MESSAGES_AMD           0x9145
#define GL_DEBUG_SEVERITY_HIGH_AMD             0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_AMD           0x9147
#define GL_DEBUG_SEVERITY_LOW_AMD              0x9148
#define GL_DEBUG_CATEGORY_API_ERROR_AMD        0x9149
#define GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD    0x914A
#define GL_DEBUG_CATEGORY_DEPRECATION_AMD      0x914B
#define GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD  0x914C
#define GL_DEBUG_CATEGORY_PERFORMANCE_AMD      0x914D
#define GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD  0x914E
#define GL_DEBUG_CATEGORY_APPLICATION_AMD      0x914F
#define GL_DEBUG_CATEGORY_OTHER_AMD            0x9150
typedef void (APIENTRYP pfn_glDebugMessageEnableAMD) (GLenum, GLenum, GLsizei, const GLuint*, GLboolean);
extern pfn_glDebugMessageEnableAMD fp_glDebugMessageEnableAMD;
typedef void (APIENTRYP pfn_glDebugMessageInsertAMD) (GLenum, GLenum, GLuint, GLsizei, const GLchar*);
extern pfn_glDebugMessageInsertAMD fp_glDebugMessageInsertAMD;
typedef void (APIENTRYP pfn_glDebugMessageCallbackAMD) (GLDEBUGPROCAMD, void*);
extern pfn_glDebugMessageCallbackAMD fp_glDebugMessageCallbackAMD;
typedef GLuint (APIENTRYP pfn_glGetDebugMessageLogAMD) (GLuint, GLsizei, GLenum*, GLuint*, GLuint*, GLsizei*, GLchar*);
extern pfn_glGetDebugMessageLogAMD fp_glGetDebugMessageLogAMD;

 /* GL_AMD_depth_clamp_separate */
extern GLboolean GLAD_AMD_depth_clamp_separate;
#define GL_DEPTH_CLAMP_NEAR_AMD                0x901E
#define GL_DEPTH_CLAMP_FAR_AMD                 0x901F

 /* GL_AMD_draw_buffers_blend */
extern GLboolean GLAD_AMD_draw_buffers_blend;
typedef void (APIENTRYP pfn_glBlendFuncIndexedAMD) (GLuint, GLenum, GLenum);
extern pfn_glBlendFuncIndexedAMD fp_glBlendFuncIndexedAMD;
typedef void (APIENTRYP pfn_glBlendFuncSeparateIndexedAMD) (GLuint, GLenum, GLenum, GLenum, GLenum);
extern pfn_glBlendFuncSeparateIndexedAMD fp_glBlendFuncSeparateIndexedAMD;
typedef void (APIENTRYP pfn_glBlendEquationIndexedAMD) (GLuint, GLenum);
extern pfn_glBlendEquationIndexedAMD fp_glBlendEquationIndexedAMD;
typedef void (APIENTRYP pfn_glBlendEquationSeparateIndexedAMD) (GLuint, GLenum, GLenum);
extern pfn_glBlendEquationSeparateIndexedAMD fp_glBlendEquationSeparateIndexedAMD;

 /* GL_AMD_interleaved_elements */
extern GLboolean GLAD_AMD_interleaved_elements;
#define GL_VERTEX_ELEMENT_SWIZZLE_AMD          0x91A4
#define GL_VERTEX_ID_SWIZZLE_AMD               0x91A5
typedef void (APIENTRYP pfn_glVertexAttribParameteriAMD) (GLuint, GLenum, GLint);
extern pfn_glVertexAttribParameteriAMD fp_glVertexAttribParameteriAMD;

 /* GL_AMD_multi_draw_indirect */
extern GLboolean GLAD_AMD_multi_draw_indirect;
typedef void (APIENTRYP pfn_glMultiDrawArraysIndirectAMD) (GLenum, const void*, GLsizei, GLsizei);
extern pfn_glMultiDrawArraysIndirectAMD fp_glMultiDrawArraysIndirectAMD;
typedef void (APIENTRYP pfn_glMultiDrawElementsIndirectAMD) (GLenum, GLenum, const void*, GLsizei, GLsizei);
extern pfn_glMultiDrawElementsIndirectAMD fp_glMultiDrawElementsIndirectAMD;

 /* GL_AMD_name_gen_delete */
extern GLboolean GLAD_AMD_name_gen_delete;
#define GL_DATA_BUFFER_AMD                     0x9151
#define GL_PERFORMANCE_MONITOR_AMD             0x9152
#define GL_QUERY_OBJECT_AMD                    0x9153
#define GL_VERTEX_ARRAY_OBJECT_AMD             0x9154
#define GL_SAMPLER_OBJECT_AMD                  0x9155
typedef void (APIENTRYP pfn_glGenNamesAMD) (GLenum, GLuint, GLuint*);
extern pfn_glGenNamesAMD fp_glGenNamesAMD;
typedef void (APIENTRYP pfn_glDeleteNamesAMD) (GLenum, GLuint, const GLuint*);
extern pfn_glDeleteNamesAMD fp_glDeleteNamesAMD;
typedef GLboolean (APIENTRYP pfn_glIsNameAMD) (GLenum, GLuint);
extern pfn_glIsNameAMD fp_glIsNameAMD;

 /* GL_AMD_performance_monitor */
extern GLboolean GLAD_AMD_performance_monitor;
#define GL_COUNTER_TYPE_AMD                    0x8BC0
#define GL_COUNTER_RANGE_AMD                   0x8BC1
#define GL_UNSIGNED_INT64_AMD                  0x8BC2
#define GL_PERCENTAGE_AMD                      0x8BC3
#define GL_PERFMON_RESULT_AVAILABLE_AMD        0x8BC4
#define GL_PERFMON_RESULT_SIZE_AMD             0x8BC5
#define GL_PERFMON_RESULT_AMD                  0x8BC6
typedef void (APIENTRYP pfn_glGetPerfMonitorGroupsAMD) (GLint*, GLsizei, GLuint*);
extern pfn_glGetPerfMonitorGroupsAMD fp_glGetPerfMonitorGroupsAMD;
typedef void (APIENTRYP pfn_glGetPerfMonitorCountersAMD) (GLuint, GLint*, GLint*, GLsizei, GLuint*);
extern pfn_glGetPerfMonitorCountersAMD fp_glGetPerfMonitorCountersAMD;
typedef void (APIENTRYP pfn_glGetPerfMonitorGroupStringAMD) (GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetPerfMonitorGroupStringAMD fp_glGetPerfMonitorGroupStringAMD;
typedef void (APIENTRYP pfn_glGetPerfMonitorCounterStringAMD) (GLuint, GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetPerfMonitorCounterStringAMD fp_glGetPerfMonitorCounterStringAMD;
typedef void (APIENTRYP pfn_glGetPerfMonitorCounterInfoAMD) (GLuint, GLuint, GLenum, void*);
extern pfn_glGetPerfMonitorCounterInfoAMD fp_glGetPerfMonitorCounterInfoAMD;
typedef void (APIENTRYP pfn_glGenPerfMonitorsAMD) (GLsizei, GLuint*);
extern pfn_glGenPerfMonitorsAMD fp_glGenPerfMonitorsAMD;
typedef void (APIENTRYP pfn_glDeletePerfMonitorsAMD) (GLsizei, GLuint*);
extern pfn_glDeletePerfMonitorsAMD fp_glDeletePerfMonitorsAMD;
typedef void (APIENTRYP pfn_glSelectPerfMonitorCountersAMD) (GLuint, GLboolean, GLuint, GLint, GLuint*);
extern pfn_glSelectPerfMonitorCountersAMD fp_glSelectPerfMonitorCountersAMD;
typedef void (APIENTRYP pfn_glBeginPerfMonitorAMD) (GLuint);
extern pfn_glBeginPerfMonitorAMD fp_glBeginPerfMonitorAMD;
typedef void (APIENTRYP pfn_glEndPerfMonitorAMD) (GLuint);
extern pfn_glEndPerfMonitorAMD fp_glEndPerfMonitorAMD;
typedef void (APIENTRYP pfn_glGetPerfMonitorCounterDataAMD) (GLuint, GLenum, GLsizei, GLuint*, GLint*);
extern pfn_glGetPerfMonitorCounterDataAMD fp_glGetPerfMonitorCounterDataAMD;

 /* GL_AMD_pinned_memory */
extern GLboolean GLAD_AMD_pinned_memory;
#define GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD  0x9160

 /* GL_AMD_program_binary_Z400 */
extern GLboolean GLAD_AMD_program_binary_Z400;
#define GL_Z400_BINARY_AMD                     0x8740

 /* GL_AMD_query_buffer_object */
extern GLboolean GLAD_AMD_query_buffer_object;
#define GL_QUERY_BUFFER_AMD                    0x9192
#define GL_QUERY_BUFFER_BINDING_AMD            0x9193
#define GL_QUERY_RESULT_NO_WAIT_AMD            0x9194

 /* GL_AMD_sample_positions */
extern GLboolean GLAD_AMD_sample_positions;
#define GL_SUBSAMPLE_DISTANCE_AMD              0x883F
typedef void (APIENTRYP pfn_glSetMultisamplefvAMD) (GLenum, GLuint, const GLfloat*);
extern pfn_glSetMultisamplefvAMD fp_glSetMultisamplefvAMD;

 /* GL_AMD_seamless_cubemap_per_texture */
extern GLboolean GLAD_AMD_seamless_cubemap_per_texture;

 /* GL_AMD_shader_atomic_counter_ops */
extern GLboolean GLAD_AMD_shader_atomic_counter_ops;

 /* GL_AMD_shader_stencil_export */
extern GLboolean GLAD_AMD_shader_stencil_export;

 /* GL_AMD_shader_trinary_minmax */
extern GLboolean GLAD_AMD_shader_trinary_minmax;

 /* GL_AMD_sparse_texture */
extern GLboolean GLAD_AMD_sparse_texture;
#define GL_VIRTUAL_PAGE_SIZE_X_AMD             0x9195
#define GL_VIRTUAL_PAGE_SIZE_Y_AMD             0x9196
#define GL_VIRTUAL_PAGE_SIZE_Z_AMD             0x9197
#define GL_MAX_SPARSE_TEXTURE_SIZE_AMD         0x9198
#define GL_MAX_SPARSE_3D_TEXTURE_SIZE_AMD      0x9199
#define GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS     0x919A
#define GL_MIN_SPARSE_LEVEL_AMD                0x919B
#define GL_MIN_LOD_WARNING_AMD                 0x919C
#define GL_TEXTURE_STORAGE_SPARSE_BIT_AMD      0x00000001
typedef void (APIENTRYP pfn_glTexStorageSparseAMD) (GLenum, GLenum, GLsizei, GLsizei, GLsizei, GLsizei, GLbitfield);
extern pfn_glTexStorageSparseAMD fp_glTexStorageSparseAMD;
typedef void (APIENTRYP pfn_glTextureStorageSparseAMD) (GLuint, GLenum, GLenum, GLsizei, GLsizei, GLsizei, GLsizei, GLbitfield);
extern pfn_glTextureStorageSparseAMD fp_glTextureStorageSparseAMD;

 /* GL_AMD_stencil_operation_extended */
extern GLboolean GLAD_AMD_stencil_operation_extended;
#define GL_SET_AMD                             0x874A
#define GL_REPLACE_VALUE_AMD                   0x874B
#define GL_STENCIL_OP_VALUE_AMD                0x874C
#define GL_STENCIL_BACK_OP_VALUE_AMD           0x874D
typedef void (APIENTRYP pfn_glStencilOpValueAMD) (GLenum, GLuint);
extern pfn_glStencilOpValueAMD fp_glStencilOpValueAMD;

 /* GL_AMD_texture_texture4 */
extern GLboolean GLAD_AMD_texture_texture4;

 /* GL_AMD_transform_feedback3_lines_triangles */
extern GLboolean GLAD_AMD_transform_feedback3_lines_triangles;

 /* GL_AMD_vertex_shader_layer */
extern GLboolean GLAD_AMD_vertex_shader_layer;

 /* GL_AMD_vertex_shader_tessellator */
extern GLboolean GLAD_AMD_vertex_shader_tessellator;
#define GL_SAMPLER_BUFFER_AMD                  0x9001
#define GL_INT_SAMPLER_BUFFER_AMD              0x9002
#define GL_UNSIGNED_INT_SAMPLER_BUFFER_AMD     0x9003
#define GL_TESSELLATION_MODE_AMD               0x9004
#define GL_TESSELLATION_FACTOR_AMD             0x9005
#define GL_DISCRETE_AMD                        0x9006
#define GL_CONTINUOUS_AMD                      0x9007
typedef void (APIENTRYP pfn_glTessellationFactorAMD) (GLfloat);
extern pfn_glTessellationFactorAMD fp_glTessellationFactorAMD;
typedef void (APIENTRYP pfn_glTessellationModeAMD) (GLenum);
extern pfn_glTessellationModeAMD fp_glTessellationModeAMD;

 /* GL_AMD_vertex_shader_viewport_index */
extern GLboolean GLAD_AMD_vertex_shader_viewport_index;

 /* GL_ANGLE_depth_texture */
extern GLboolean GLAD_ANGLE_depth_texture;

 /* GL_ANGLE_framebuffer_blit */
extern GLboolean GLAD_ANGLE_framebuffer_blit;
#define GL_READ_FRAMEBUFFER_ANGLE              0x8CA8
#define GL_DRAW_FRAMEBUFFER_ANGLE              0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_ANGLE      0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_ANGLE      0x8CAA
typedef void (APIENTRYP pfn_glBlitFramebufferANGLE) (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
extern pfn_glBlitFramebufferANGLE fp_glBlitFramebufferANGLE;

 /* GL_ANGLE_framebuffer_multisample */
extern GLboolean GLAD_ANGLE_framebuffer_multisample;
#define GL_RENDERBUFFER_SAMPLES_ANGLE          0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE  0x8D56
#define GL_MAX_SAMPLES_ANGLE                   0x8D57
typedef void (APIENTRYP pfn_glRenderbufferStorageMultisampleANGLE) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glRenderbufferStorageMultisampleANGLE fp_glRenderbufferStorageMultisampleANGLE;

 /* GL_ANGLE_instanced_arrays */
extern GLboolean GLAD_ANGLE_instanced_arrays;
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ANGLE   0x88FE
typedef void (APIENTRYP pfn_glDrawArraysInstancedANGLE) (GLenum, GLint, GLsizei, GLsizei);
extern pfn_glDrawArraysInstancedANGLE fp_glDrawArraysInstancedANGLE;
typedef void (APIENTRYP pfn_glDrawElementsInstancedANGLE) (GLenum, GLsizei, GLenum, const void*, GLsizei);
extern pfn_glDrawElementsInstancedANGLE fp_glDrawElementsInstancedANGLE;
typedef void (APIENTRYP pfn_glVertexAttribDivisorANGLE) (GLuint, GLuint);
extern pfn_glVertexAttribDivisorANGLE fp_glVertexAttribDivisorANGLE;

 /* GL_ANGLE_pack_reverse_row_order */
extern GLboolean GLAD_ANGLE_pack_reverse_row_order;
#define GL_PACK_REVERSE_ROW_ORDER_ANGLE        0x93A4

 /* GL_ANGLE_program_binary */
extern GLboolean GLAD_ANGLE_program_binary;
#define GL_PROGRAM_BINARY_ANGLE                0x93A6

 /* GL_ANGLE_texture_compression_dxt3 */
extern GLboolean GLAD_ANGLE_texture_compression_dxt3;
#define GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE     0x83F2

 /* GL_ANGLE_texture_compression_dxt5 */
extern GLboolean GLAD_ANGLE_texture_compression_dxt5;
#define GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE     0x83F3

 /* GL_ANGLE_texture_usage */
extern GLboolean GLAD_ANGLE_texture_usage;
#define GL_TEXTURE_USAGE_ANGLE                 0x93A2
#define GL_FRAMEBUFFER_ATTACHMENT_ANGLE        0x93A3

 /* GL_ANGLE_translated_shader_source */
extern GLboolean GLAD_ANGLE_translated_shader_source;
#define GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE  0x93A0
typedef void (APIENTRYP pfn_glGetTranslatedShaderSourceANGLE) (GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetTranslatedShaderSourceANGLE fp_glGetTranslatedShaderSourceANGLE;

 /* GL_APPLE_aux_depth_stencil */
extern GLboolean GLAD_APPLE_aux_depth_stencil;
#define GL_AUX_DEPTH_STENCIL_APPLE             0x8A14

 /* GL_APPLE_client_storage */
extern GLboolean GLAD_APPLE_client_storage;
#define GL_UNPACK_CLIENT_STORAGE_APPLE         0x85B2

 /* GL_APPLE_copy_texture_levels */
extern GLboolean GLAD_APPLE_copy_texture_levels;
typedef void (APIENTRYP pfn_glCopyTextureLevelsAPPLE) (GLuint, GLuint, GLint, GLsizei);
extern pfn_glCopyTextureLevelsAPPLE fp_glCopyTextureLevelsAPPLE;

 /* GL_APPLE_element_array */
extern GLboolean GLAD_APPLE_element_array;
#define GL_ELEMENT_ARRAY_APPLE                 0x8A0C
#define GL_ELEMENT_ARRAY_TYPE_APPLE            0x8A0D
#define GL_ELEMENT_ARRAY_POINTER_APPLE         0x8A0E
typedef void (APIENTRYP pfn_glElementPointerAPPLE) (GLenum, const void*);
extern pfn_glElementPointerAPPLE fp_glElementPointerAPPLE;
typedef void (APIENTRYP pfn_glDrawElementArrayAPPLE) (GLenum, GLint, GLsizei);
extern pfn_glDrawElementArrayAPPLE fp_glDrawElementArrayAPPLE;
typedef void (APIENTRYP pfn_glDrawRangeElementArrayAPPLE) (GLenum, GLuint, GLuint, GLint, GLsizei);
extern pfn_glDrawRangeElementArrayAPPLE fp_glDrawRangeElementArrayAPPLE;
typedef void (APIENTRYP pfn_glMultiDrawElementArrayAPPLE) (GLenum, const GLint*, const GLsizei*, GLsizei);
extern pfn_glMultiDrawElementArrayAPPLE fp_glMultiDrawElementArrayAPPLE;
typedef void (APIENTRYP pfn_glMultiDrawRangeElementArrayAPPLE) (GLenum, GLuint, GLuint, const GLint*, const GLsizei*, GLsizei);
extern pfn_glMultiDrawRangeElementArrayAPPLE fp_glMultiDrawRangeElementArrayAPPLE;

 /* GL_APPLE_fence */
extern GLboolean GLAD_APPLE_fence;
#define GL_DRAW_PIXELS_APPLE                   0x8A0A
#define GL_FENCE_APPLE                         0x8A0B
typedef void (APIENTRYP pfn_glGenFencesAPPLE) (GLsizei, GLuint*);
extern pfn_glGenFencesAPPLE fp_glGenFencesAPPLE;
typedef void (APIENTRYP pfn_glDeleteFencesAPPLE) (GLsizei, const GLuint*);
extern pfn_glDeleteFencesAPPLE fp_glDeleteFencesAPPLE;
typedef void (APIENTRYP pfn_glSetFenceAPPLE) (GLuint);
extern pfn_glSetFenceAPPLE fp_glSetFenceAPPLE;
typedef GLboolean (APIENTRYP pfn_glIsFenceAPPLE) (GLuint);
extern pfn_glIsFenceAPPLE fp_glIsFenceAPPLE;
typedef GLboolean (APIENTRYP pfn_glTestFenceAPPLE) (GLuint);
extern pfn_glTestFenceAPPLE fp_glTestFenceAPPLE;
typedef void (APIENTRYP pfn_glFinishFenceAPPLE) (GLuint);
extern pfn_glFinishFenceAPPLE fp_glFinishFenceAPPLE;
typedef GLboolean (APIENTRYP pfn_glTestObjectAPPLE) (GLenum, GLuint);
extern pfn_glTestObjectAPPLE fp_glTestObjectAPPLE;
typedef void (APIENTRYP pfn_glFinishObjectAPPLE) (GLenum, GLint);
extern pfn_glFinishObjectAPPLE fp_glFinishObjectAPPLE;

 /* GL_APPLE_float_pixels */
extern GLboolean GLAD_APPLE_float_pixels;
#define GL_HALF_APPLE                          0x140B
#define GL_RGBA_FLOAT32_APPLE                  0x8814
#define GL_RGB_FLOAT32_APPLE                   0x8815
#define GL_ALPHA_FLOAT32_APPLE                 0x8816
#define GL_INTENSITY_FLOAT32_APPLE             0x8817
#define GL_LUMINANCE_FLOAT32_APPLE             0x8818
#define GL_LUMINANCE_ALPHA_FLOAT32_APPLE       0x8819
#define GL_RGBA_FLOAT16_APPLE                  0x881A
#define GL_RGB_FLOAT16_APPLE                   0x881B
#define GL_ALPHA_FLOAT16_APPLE                 0x881C
#define GL_INTENSITY_FLOAT16_APPLE             0x881D
#define GL_LUMINANCE_FLOAT16_APPLE             0x881E
#define GL_LUMINANCE_ALPHA_FLOAT16_APPLE       0x881F
#define GL_COLOR_FLOAT_APPLE                   0x8A0F

 /* GL_APPLE_flush_buffer_range */
extern GLboolean GLAD_APPLE_flush_buffer_range;
#define GL_BUFFER_SERIALIZED_MODIFY_APPLE      0x8A12
#define GL_BUFFER_FLUSHING_UNMAP_APPLE         0x8A13
typedef void (APIENTRYP pfn_glBufferParameteriAPPLE) (GLenum, GLenum, GLint);
extern pfn_glBufferParameteriAPPLE fp_glBufferParameteriAPPLE;
typedef void (APIENTRYP pfn_glFlushMappedBufferRangeAPPLE) (GLenum, GLintptr, GLsizeiptr);
extern pfn_glFlushMappedBufferRangeAPPLE fp_glFlushMappedBufferRangeAPPLE;

 /* GL_APPLE_framebuffer_multisample */
extern GLboolean GLAD_APPLE_framebuffer_multisample;
#define GL_RENDERBUFFER_SAMPLES_APPLE          0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE  0x8D56
#define GL_MAX_SAMPLES_APPLE                   0x8D57
#define GL_READ_FRAMEBUFFER_APPLE              0x8CA8
#define GL_DRAW_FRAMEBUFFER_APPLE              0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_APPLE      0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_APPLE      0x8CAA
typedef void (APIENTRYP pfn_glRenderbufferStorageMultisampleAPPLE) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glRenderbufferStorageMultisampleAPPLE fp_glRenderbufferStorageMultisampleAPPLE;
typedef void (APIENTRYP pfn_glResolveMultisampleFramebufferAPPLE) ();
extern pfn_glResolveMultisampleFramebufferAPPLE fp_glResolveMultisampleFramebufferAPPLE;

 /* GL_APPLE_object_purgeable */
extern GLboolean GLAD_APPLE_object_purgeable;
#define GL_BUFFER_OBJECT_APPLE                 0x85B3
#define GL_RELEASED_APPLE                      0x8A19
#define GL_VOLATILE_APPLE                      0x8A1A
#define GL_RETAINED_APPLE                      0x8A1B
#define GL_UNDEFINED_APPLE                     0x8A1C
#define GL_PURGEABLE_APPLE                     0x8A1D
typedef GLenum (APIENTRYP pfn_glObjectPurgeableAPPLE) (GLenum, GLuint, GLenum);
extern pfn_glObjectPurgeableAPPLE fp_glObjectPurgeableAPPLE;
typedef GLenum (APIENTRYP pfn_glObjectUnpurgeableAPPLE) (GLenum, GLuint, GLenum);
extern pfn_glObjectUnpurgeableAPPLE fp_glObjectUnpurgeableAPPLE;
typedef void (APIENTRYP pfn_glGetObjectParameterivAPPLE) (GLenum, GLuint, GLenum, GLint*);
extern pfn_glGetObjectParameterivAPPLE fp_glGetObjectParameterivAPPLE;

 /* GL_APPLE_rgb_422 */
extern GLboolean GLAD_APPLE_rgb_422;
#define GL_RGB_422_APPLE                       0x8A1F
#define GL_UNSIGNED_SHORT_8_8_APPLE            0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_APPLE        0x85BB
#define GL_RGB_RAW_422_APPLE                   0x8A51

 /* GL_APPLE_row_bytes */
extern GLboolean GLAD_APPLE_row_bytes;
#define GL_PACK_ROW_BYTES_APPLE                0x8A15
#define GL_UNPACK_ROW_BYTES_APPLE              0x8A16

 /* GL_APPLE_specular_vector */
extern GLboolean GLAD_APPLE_specular_vector;
#define GL_LIGHT_MODEL_SPECULAR_VECTOR_APPLE   0x85B0

 /* GL_APPLE_sync */
extern GLboolean GLAD_APPLE_sync;
#define GL_SYNC_OBJECT_APPLE                   0x8A53
#define GL_MAX_SERVER_WAIT_TIMEOUT_APPLE       0x9111
#define GL_OBJECT_TYPE_APPLE                   0x9112
#define GL_SYNC_CONDITION_APPLE                0x9113
#define GL_SYNC_STATUS_APPLE                   0x9114
#define GL_SYNC_FLAGS_APPLE                    0x9115
#define GL_SYNC_FENCE_APPLE                    0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE    0x9117
#define GL_UNSIGNALED_APPLE                    0x9118
#define GL_SIGNALED_APPLE                      0x9119
#define GL_ALREADY_SIGNALED_APPLE              0x911A
#define GL_TIMEOUT_EXPIRED_APPLE               0x911B
#define GL_CONDITION_SATISFIED_APPLE           0x911C
#define GL_WAIT_FAILED_APPLE                   0x911D
#define GL_SYNC_FLUSH_COMMANDS_BIT_APPLE       0x00000001
#define GL_TIMEOUT_IGNORED_APPLE               0xFFFFFFFFFFFFFFFF
typedef GLsync (APIENTRYP pfn_glFenceSyncAPPLE) (GLenum, GLbitfield);
extern pfn_glFenceSyncAPPLE fp_glFenceSyncAPPLE;
typedef GLboolean (APIENTRYP pfn_glIsSyncAPPLE) (GLsync);
extern pfn_glIsSyncAPPLE fp_glIsSyncAPPLE;
typedef void (APIENTRYP pfn_glDeleteSyncAPPLE) (GLsync);
extern pfn_glDeleteSyncAPPLE fp_glDeleteSyncAPPLE;
typedef GLenum (APIENTRYP pfn_glClientWaitSyncAPPLE) (GLsync, GLbitfield, GLuint64);
extern pfn_glClientWaitSyncAPPLE fp_glClientWaitSyncAPPLE;
typedef void (APIENTRYP pfn_glWaitSyncAPPLE) (GLsync, GLbitfield, GLuint64);
extern pfn_glWaitSyncAPPLE fp_glWaitSyncAPPLE;
typedef void (APIENTRYP pfn_glGetInteger64vAPPLE) (GLenum, GLint64*);
extern pfn_glGetInteger64vAPPLE fp_glGetInteger64vAPPLE;
typedef void (APIENTRYP pfn_glGetSyncivAPPLE) (GLsync, GLenum, GLsizei, GLsizei*, GLint*);
extern pfn_glGetSyncivAPPLE fp_glGetSyncivAPPLE;

 /* GL_APPLE_texture_format_BGRA8888 */
extern GLboolean GLAD_APPLE_texture_format_BGRA8888;

 /* GL_APPLE_texture_max_level */
extern GLboolean GLAD_APPLE_texture_max_level;
#define GL_TEXTURE_MAX_LEVEL_APPLE             0x813D

 /* GL_APPLE_texture_range */
extern GLboolean GLAD_APPLE_texture_range;
#define GL_TEXTURE_RANGE_LENGTH_APPLE          0x85B7
#define GL_TEXTURE_RANGE_POINTER_APPLE         0x85B8
#define GL_TEXTURE_STORAGE_HINT_APPLE          0x85BC
#define GL_STORAGE_PRIVATE_APPLE               0x85BD
#define GL_STORAGE_CACHED_APPLE                0x85BE
#define GL_STORAGE_SHARED_APPLE                0x85BF
typedef void (APIENTRYP pfn_glTextureRangeAPPLE) (GLenum, GLsizei, const void*);
extern pfn_glTextureRangeAPPLE fp_glTextureRangeAPPLE;
typedef void (APIENTRYP pfn_glGetTexParameterPointervAPPLE) (GLenum, GLenum, void**);
extern pfn_glGetTexParameterPointervAPPLE fp_glGetTexParameterPointervAPPLE;

 /* GL_APPLE_transform_hint */
extern GLboolean GLAD_APPLE_transform_hint;
#define GL_TRANSFORM_HINT_APPLE                0x85B1

 /* GL_APPLE_vertex_array_object */
extern GLboolean GLAD_APPLE_vertex_array_object;
#define GL_VERTEX_ARRAY_BINDING_APPLE          0x85B5
typedef void (APIENTRYP pfn_glBindVertexArrayAPPLE) (GLuint);
extern pfn_glBindVertexArrayAPPLE fp_glBindVertexArrayAPPLE;
typedef void (APIENTRYP pfn_glDeleteVertexArraysAPPLE) (GLsizei, const GLuint*);
extern pfn_glDeleteVertexArraysAPPLE fp_glDeleteVertexArraysAPPLE;
typedef void (APIENTRYP pfn_glGenVertexArraysAPPLE) (GLsizei, GLuint*);
extern pfn_glGenVertexArraysAPPLE fp_glGenVertexArraysAPPLE;
typedef GLboolean (APIENTRYP pfn_glIsVertexArrayAPPLE) (GLuint);
extern pfn_glIsVertexArrayAPPLE fp_glIsVertexArrayAPPLE;

 /* GL_APPLE_vertex_array_range */
extern GLboolean GLAD_APPLE_vertex_array_range;
#define GL_VERTEX_ARRAY_RANGE_APPLE            0x851D
#define GL_VERTEX_ARRAY_RANGE_LENGTH_APPLE     0x851E
#define GL_VERTEX_ARRAY_STORAGE_HINT_APPLE     0x851F
#define GL_VERTEX_ARRAY_RANGE_POINTER_APPLE    0x8521
#define GL_STORAGE_CLIENT_APPLE                0x85B4
typedef void (APIENTRYP pfn_glVertexArrayRangeAPPLE) (GLsizei, void*);
extern pfn_glVertexArrayRangeAPPLE fp_glVertexArrayRangeAPPLE;
typedef void (APIENTRYP pfn_glFlushVertexArrayRangeAPPLE) (GLsizei, void*);
extern pfn_glFlushVertexArrayRangeAPPLE fp_glFlushVertexArrayRangeAPPLE;
typedef void (APIENTRYP pfn_glVertexArrayParameteriAPPLE) (GLenum, GLint);
extern pfn_glVertexArrayParameteriAPPLE fp_glVertexArrayParameteriAPPLE;

 /* GL_APPLE_vertex_program_evaluators */
extern GLboolean GLAD_APPLE_vertex_program_evaluators;
#define GL_VERTEX_ATTRIB_MAP1_APPLE            0x8A00
#define GL_VERTEX_ATTRIB_MAP2_APPLE            0x8A01
#define GL_VERTEX_ATTRIB_MAP1_SIZE_APPLE       0x8A02
#define GL_VERTEX_ATTRIB_MAP1_COEFF_APPLE      0x8A03
#define GL_VERTEX_ATTRIB_MAP1_ORDER_APPLE      0x8A04
#define GL_VERTEX_ATTRIB_MAP1_DOMAIN_APPLE     0x8A05
#define GL_VERTEX_ATTRIB_MAP2_SIZE_APPLE       0x8A06
#define GL_VERTEX_ATTRIB_MAP2_COEFF_APPLE      0x8A07
#define GL_VERTEX_ATTRIB_MAP2_ORDER_APPLE      0x8A08
#define GL_VERTEX_ATTRIB_MAP2_DOMAIN_APPLE     0x8A09
typedef void (APIENTRYP pfn_glEnableVertexAttribAPPLE) (GLuint, GLenum);
extern pfn_glEnableVertexAttribAPPLE fp_glEnableVertexAttribAPPLE;
typedef void (APIENTRYP pfn_glDisableVertexAttribAPPLE) (GLuint, GLenum);
extern pfn_glDisableVertexAttribAPPLE fp_glDisableVertexAttribAPPLE;
typedef GLboolean (APIENTRYP pfn_glIsVertexAttribEnabledAPPLE) (GLuint, GLenum);
extern pfn_glIsVertexAttribEnabledAPPLE fp_glIsVertexAttribEnabledAPPLE;
typedef void (APIENTRYP pfn_glMapVertexAttrib1dAPPLE) (GLuint, GLuint, GLdouble, GLdouble, GLint, GLint, const GLdouble*);
extern pfn_glMapVertexAttrib1dAPPLE fp_glMapVertexAttrib1dAPPLE;
typedef void (APIENTRYP pfn_glMapVertexAttrib1fAPPLE) (GLuint, GLuint, GLfloat, GLfloat, GLint, GLint, const GLfloat*);
extern pfn_glMapVertexAttrib1fAPPLE fp_glMapVertexAttrib1fAPPLE;
typedef void (APIENTRYP pfn_glMapVertexAttrib2dAPPLE) (GLuint, GLuint, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint, const GLdouble*);
extern pfn_glMapVertexAttrib2dAPPLE fp_glMapVertexAttrib2dAPPLE;
typedef void (APIENTRYP pfn_glMapVertexAttrib2fAPPLE) (GLuint, GLuint, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint, const GLfloat*);
extern pfn_glMapVertexAttrib2fAPPLE fp_glMapVertexAttrib2fAPPLE;

 /* GL_APPLE_ycbcr_422 */
extern GLboolean GLAD_APPLE_ycbcr_422;
#define GL_YCBCR_422_APPLE                     0x85B9

 /* GL_ARM_mali_program_binary */
extern GLboolean GLAD_ARM_mali_program_binary;
#define GL_MALI_PROGRAM_BINARY_ARM             0x8F61

 /* GL_ARM_mali_shader_binary */
extern GLboolean GLAD_ARM_mali_shader_binary;
#define GL_MALI_SHADER_BINARY_ARM              0x8F60

 /* GL_ARM_rgba8 */
extern GLboolean GLAD_ARM_rgba8;

 /* GL_ATI_draw_buffers */
extern GLboolean GLAD_ATI_draw_buffers;
#define GL_MAX_DRAW_BUFFERS_ATI                0x8824
#define GL_DRAW_BUFFER0_ATI                    0x8825
#define GL_DRAW_BUFFER1_ATI                    0x8826
#define GL_DRAW_BUFFER2_ATI                    0x8827
#define GL_DRAW_BUFFER3_ATI                    0x8828
#define GL_DRAW_BUFFER4_ATI                    0x8829
#define GL_DRAW_BUFFER5_ATI                    0x882A
#define GL_DRAW_BUFFER6_ATI                    0x882B
#define GL_DRAW_BUFFER7_ATI                    0x882C
#define GL_DRAW_BUFFER8_ATI                    0x882D
#define GL_DRAW_BUFFER9_ATI                    0x882E
#define GL_DRAW_BUFFER10_ATI                   0x882F
#define GL_DRAW_BUFFER11_ATI                   0x8830
#define GL_DRAW_BUFFER12_ATI                   0x8831
#define GL_DRAW_BUFFER13_ATI                   0x8832
#define GL_DRAW_BUFFER14_ATI                   0x8833
#define GL_DRAW_BUFFER15_ATI                   0x8834
typedef void (APIENTRYP pfn_glDrawBuffersATI) (GLsizei, const GLenum*);
extern pfn_glDrawBuffersATI fp_glDrawBuffersATI;

 /* GL_ATI_element_array */
extern GLboolean GLAD_ATI_element_array;
#define GL_ELEMENT_ARRAY_ATI                   0x8768
#define GL_ELEMENT_ARRAY_TYPE_ATI              0x8769
#define GL_ELEMENT_ARRAY_POINTER_ATI           0x876A
typedef void (APIENTRYP pfn_glElementPointerATI) (GLenum, const void*);
extern pfn_glElementPointerATI fp_glElementPointerATI;
typedef void (APIENTRYP pfn_glDrawElementArrayATI) (GLenum, GLsizei);
extern pfn_glDrawElementArrayATI fp_glDrawElementArrayATI;
typedef void (APIENTRYP pfn_glDrawRangeElementArrayATI) (GLenum, GLuint, GLuint, GLsizei);
extern pfn_glDrawRangeElementArrayATI fp_glDrawRangeElementArrayATI;

 /* GL_ATI_envmap_bumpmap */
extern GLboolean GLAD_ATI_envmap_bumpmap;
#define GL_BUMP_ROT_MATRIX_ATI                 0x8775
#define GL_BUMP_ROT_MATRIX_SIZE_ATI            0x8776
#define GL_BUMP_NUM_TEX_UNITS_ATI              0x8777
#define GL_BUMP_TEX_UNITS_ATI                  0x8778
#define GL_DUDV_ATI                            0x8779
#define GL_DU8DV8_ATI                          0x877A
#define GL_BUMP_ENVMAP_ATI                     0x877B
#define GL_BUMP_TARGET_ATI                     0x877C
typedef void (APIENTRYP pfn_glTexBumpParameterivATI) (GLenum, const GLint*);
extern pfn_glTexBumpParameterivATI fp_glTexBumpParameterivATI;
typedef void (APIENTRYP pfn_glTexBumpParameterfvATI) (GLenum, const GLfloat*);
extern pfn_glTexBumpParameterfvATI fp_glTexBumpParameterfvATI;
typedef void (APIENTRYP pfn_glGetTexBumpParameterivATI) (GLenum, GLint*);
extern pfn_glGetTexBumpParameterivATI fp_glGetTexBumpParameterivATI;
typedef void (APIENTRYP pfn_glGetTexBumpParameterfvATI) (GLenum, GLfloat*);
extern pfn_glGetTexBumpParameterfvATI fp_glGetTexBumpParameterfvATI;

 /* GL_ATI_fragment_shader */
extern GLboolean GLAD_ATI_fragment_shader;
#define GL_FRAGMENT_SHADER_ATI                 0x8920
#define GL_REG_0_ATI                           0x8921
#define GL_REG_1_ATI                           0x8922
#define GL_REG_2_ATI                           0x8923
#define GL_REG_3_ATI                           0x8924
#define GL_REG_4_ATI                           0x8925
#define GL_REG_5_ATI                           0x8926
#define GL_REG_6_ATI                           0x8927
#define GL_REG_7_ATI                           0x8928
#define GL_REG_8_ATI                           0x8929
#define GL_REG_9_ATI                           0x892A
#define GL_REG_10_ATI                          0x892B
#define GL_REG_11_ATI                          0x892C
#define GL_REG_12_ATI                          0x892D
#define GL_REG_13_ATI                          0x892E
#define GL_REG_14_ATI                          0x892F
#define GL_REG_15_ATI                          0x8930
#define GL_REG_16_ATI                          0x8931
#define GL_REG_17_ATI                          0x8932
#define GL_REG_18_ATI                          0x8933
#define GL_REG_19_ATI                          0x8934
#define GL_REG_20_ATI                          0x8935
#define GL_REG_21_ATI                          0x8936
#define GL_REG_22_ATI                          0x8937
#define GL_REG_23_ATI                          0x8938
#define GL_REG_24_ATI                          0x8939
#define GL_REG_25_ATI                          0x893A
#define GL_REG_26_ATI                          0x893B
#define GL_REG_27_ATI                          0x893C
#define GL_REG_28_ATI                          0x893D
#define GL_REG_29_ATI                          0x893E
#define GL_REG_30_ATI                          0x893F
#define GL_REG_31_ATI                          0x8940
#define GL_CON_0_ATI                           0x8941
#define GL_CON_1_ATI                           0x8942
#define GL_CON_2_ATI                           0x8943
#define GL_CON_3_ATI                           0x8944
#define GL_CON_4_ATI                           0x8945
#define GL_CON_5_ATI                           0x8946
#define GL_CON_6_ATI                           0x8947
#define GL_CON_7_ATI                           0x8948
#define GL_CON_8_ATI                           0x8949
#define GL_CON_9_ATI                           0x894A
#define GL_CON_10_ATI                          0x894B
#define GL_CON_11_ATI                          0x894C
#define GL_CON_12_ATI                          0x894D
#define GL_CON_13_ATI                          0x894E
#define GL_CON_14_ATI                          0x894F
#define GL_CON_15_ATI                          0x8950
#define GL_CON_16_ATI                          0x8951
#define GL_CON_17_ATI                          0x8952
#define GL_CON_18_ATI                          0x8953
#define GL_CON_19_ATI                          0x8954
#define GL_CON_20_ATI                          0x8955
#define GL_CON_21_ATI                          0x8956
#define GL_CON_22_ATI                          0x8957
#define GL_CON_23_ATI                          0x8958
#define GL_CON_24_ATI                          0x8959
#define GL_CON_25_ATI                          0x895A
#define GL_CON_26_ATI                          0x895B
#define GL_CON_27_ATI                          0x895C
#define GL_CON_28_ATI                          0x895D
#define GL_CON_29_ATI                          0x895E
#define GL_CON_30_ATI                          0x895F
#define GL_CON_31_ATI                          0x8960
#define GL_MOV_ATI                             0x8961
#define GL_ADD_ATI                             0x8963
#define GL_MUL_ATI                             0x8964
#define GL_SUB_ATI                             0x8965
#define GL_DOT3_ATI                            0x8966
#define GL_DOT4_ATI                            0x8967
#define GL_MAD_ATI                             0x8968
#define GL_LERP_ATI                            0x8969
#define GL_CND_ATI                             0x896A
#define GL_CND0_ATI                            0x896B
#define GL_DOT2_ADD_ATI                        0x896C
#define GL_SECONDARY_INTERPOLATOR_ATI          0x896D
#define GL_NUM_FRAGMENT_REGISTERS_ATI          0x896E
#define GL_NUM_FRAGMENT_CONSTANTS_ATI          0x896F
#define GL_NUM_PASSES_ATI                      0x8970
#define GL_NUM_INSTRUCTIONS_PER_PASS_ATI       0x8971
#define GL_NUM_INSTRUCTIONS_TOTAL_ATI          0x8972
#define GL_NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI  0x8973
#define GL_NUM_LOOPBACK_COMPONENTS_ATI         0x8974
#define GL_COLOR_ALPHA_PAIRING_ATI             0x8975
#define GL_SWIZZLE_STR_ATI                     0x8976
#define GL_SWIZZLE_STQ_ATI                     0x8977
#define GL_SWIZZLE_STR_DR_ATI                  0x8978
#define GL_SWIZZLE_STQ_DQ_ATI                  0x8979
#define GL_SWIZZLE_STRQ_ATI                    0x897A
#define GL_SWIZZLE_STRQ_DQ_ATI                 0x897B
#define GL_RED_BIT_ATI                         0x00000001
#define GL_GREEN_BIT_ATI                       0x00000002
#define GL_BLUE_BIT_ATI                        0x00000004
#define GL_2X_BIT_ATI                          0x00000001
#define GL_4X_BIT_ATI                          0x00000002
#define GL_8X_BIT_ATI                          0x00000004
#define GL_HALF_BIT_ATI                        0x00000008
#define GL_QUARTER_BIT_ATI                     0x00000010
#define GL_EIGHTH_BIT_ATI                      0x00000020
#define GL_SATURATE_BIT_ATI                    0x00000040
#define GL_COMP_BIT_ATI                        0x00000002
#define GL_NEGATE_BIT_ATI                      0x00000004
#define GL_BIAS_BIT_ATI                        0x00000008
typedef GLuint (APIENTRYP pfn_glGenFragmentShadersATI) (GLuint);
extern pfn_glGenFragmentShadersATI fp_glGenFragmentShadersATI;
typedef void (APIENTRYP pfn_glBindFragmentShaderATI) (GLuint);
extern pfn_glBindFragmentShaderATI fp_glBindFragmentShaderATI;
typedef void (APIENTRYP pfn_glDeleteFragmentShaderATI) (GLuint);
extern pfn_glDeleteFragmentShaderATI fp_glDeleteFragmentShaderATI;
typedef void (APIENTRYP pfn_glBeginFragmentShaderATI) ();
extern pfn_glBeginFragmentShaderATI fp_glBeginFragmentShaderATI;
typedef void (APIENTRYP pfn_glEndFragmentShaderATI) ();
extern pfn_glEndFragmentShaderATI fp_glEndFragmentShaderATI;
typedef void (APIENTRYP pfn_glPassTexCoordATI) (GLuint, GLuint, GLenum);
extern pfn_glPassTexCoordATI fp_glPassTexCoordATI;
typedef void (APIENTRYP pfn_glSampleMapATI) (GLuint, GLuint, GLenum);
extern pfn_glSampleMapATI fp_glSampleMapATI;
typedef void (APIENTRYP pfn_glColorFragmentOp1ATI) (GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glColorFragmentOp1ATI fp_glColorFragmentOp1ATI;
typedef void (APIENTRYP pfn_glColorFragmentOp2ATI) (GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glColorFragmentOp2ATI fp_glColorFragmentOp2ATI;
typedef void (APIENTRYP pfn_glColorFragmentOp3ATI) (GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glColorFragmentOp3ATI fp_glColorFragmentOp3ATI;
typedef void (APIENTRYP pfn_glAlphaFragmentOp1ATI) (GLenum, GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glAlphaFragmentOp1ATI fp_glAlphaFragmentOp1ATI;
typedef void (APIENTRYP pfn_glAlphaFragmentOp2ATI) (GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glAlphaFragmentOp2ATI fp_glAlphaFragmentOp2ATI;
typedef void (APIENTRYP pfn_glAlphaFragmentOp3ATI) (GLenum, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glAlphaFragmentOp3ATI fp_glAlphaFragmentOp3ATI;
typedef void (APIENTRYP pfn_glSetFragmentShaderConstantATI) (GLuint, const GLfloat*);
extern pfn_glSetFragmentShaderConstantATI fp_glSetFragmentShaderConstantATI;

 /* GL_ATI_map_object_buffer */
extern GLboolean GLAD_ATI_map_object_buffer;
typedef void* (APIENTRYP pfn_glMapObjectBufferATI) (GLuint);
extern pfn_glMapObjectBufferATI fp_glMapObjectBufferATI;
typedef void (APIENTRYP pfn_glUnmapObjectBufferATI) (GLuint);
extern pfn_glUnmapObjectBufferATI fp_glUnmapObjectBufferATI;

 /* GL_ATI_meminfo */
extern GLboolean GLAD_ATI_meminfo;
#define GL_VBO_FREE_MEMORY_ATI                 0x87FB
#define GL_TEXTURE_FREE_MEMORY_ATI             0x87FC
#define GL_RENDERBUFFER_FREE_MEMORY_ATI        0x87FD

 /* GL_ATI_pixel_format_float */
extern GLboolean GLAD_ATI_pixel_format_float;
#define GL_RGBA_FLOAT_MODE_ATI                 0x8820
#define GL_COLOR_CLEAR_UNCLAMPED_VALUE_ATI     0x8835

 /* GL_ATI_pn_triangles */
extern GLboolean GLAD_ATI_pn_triangles;
#define GL_PN_TRIANGLES_ATI                    0x87F0
#define GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI  0x87F1
#define GL_PN_TRIANGLES_POINT_MODE_ATI         0x87F2
#define GL_PN_TRIANGLES_NORMAL_MODE_ATI        0x87F3
#define GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI  0x87F4
#define GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI  0x87F5
#define GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI   0x87F6
#define GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI  0x87F7
#define GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI  0x87F8
typedef void (APIENTRYP pfn_glPNTrianglesiATI) (GLenum, GLint);
extern pfn_glPNTrianglesiATI fp_glPNTrianglesiATI;
typedef void (APIENTRYP pfn_glPNTrianglesfATI) (GLenum, GLfloat);
extern pfn_glPNTrianglesfATI fp_glPNTrianglesfATI;

 /* GL_ATI_separate_stencil */
extern GLboolean GLAD_ATI_separate_stencil;
#define GL_STENCIL_BACK_FUNC_ATI               0x8800
#define GL_STENCIL_BACK_FAIL_ATI               0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL_ATI    0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS_ATI    0x8803
typedef void (APIENTRYP pfn_glStencilOpSeparateATI) (GLenum, GLenum, GLenum, GLenum);
extern pfn_glStencilOpSeparateATI fp_glStencilOpSeparateATI;
typedef void (APIENTRYP pfn_glStencilFuncSeparateATI) (GLenum, GLenum, GLint, GLuint);
extern pfn_glStencilFuncSeparateATI fp_glStencilFuncSeparateATI;

 /* GL_ATI_text_fragment_shader */
extern GLboolean GLAD_ATI_text_fragment_shader;
#define GL_TEXT_FRAGMENT_SHADER_ATI            0x8200

 /* GL_ATI_texture_env_combine3 */
extern GLboolean GLAD_ATI_texture_env_combine3;
#define GL_MODULATE_ADD_ATI                    0x8744
#define GL_MODULATE_SIGNED_ADD_ATI             0x8745
#define GL_MODULATE_SUBTRACT_ATI               0x8746

 /* GL_ATI_texture_float */
extern GLboolean GLAD_ATI_texture_float;
#define GL_RGBA_FLOAT32_ATI                    0x8814
#define GL_RGB_FLOAT32_ATI                     0x8815
#define GL_ALPHA_FLOAT32_ATI                   0x8816
#define GL_INTENSITY_FLOAT32_ATI               0x8817
#define GL_LUMINANCE_FLOAT32_ATI               0x8818
#define GL_LUMINANCE_ALPHA_FLOAT32_ATI         0x8819
#define GL_RGBA_FLOAT16_ATI                    0x881A
#define GL_RGB_FLOAT16_ATI                     0x881B
#define GL_ALPHA_FLOAT16_ATI                   0x881C
#define GL_INTENSITY_FLOAT16_ATI               0x881D
#define GL_LUMINANCE_FLOAT16_ATI               0x881E
#define GL_LUMINANCE_ALPHA_FLOAT16_ATI         0x881F

 /* GL_ATI_texture_mirror_once */
extern GLboolean GLAD_ATI_texture_mirror_once;
#define GL_MIRROR_CLAMP_ATI                    0x8742
#define GL_MIRROR_CLAMP_TO_EDGE_ATI            0x8743

 /* GL_ATI_vertex_array_object */
extern GLboolean GLAD_ATI_vertex_array_object;
#define GL_STATIC_ATI                          0x8760
#define GL_DYNAMIC_ATI                         0x8761
#define GL_PRESERVE_ATI                        0x8762
#define GL_DISCARD_ATI                         0x8763
#define GL_OBJECT_BUFFER_SIZE_ATI              0x8764
#define GL_OBJECT_BUFFER_USAGE_ATI             0x8765
#define GL_ARRAY_OBJECT_BUFFER_ATI             0x8766
#define GL_ARRAY_OBJECT_OFFSET_ATI             0x8767
typedef GLuint (APIENTRYP pfn_glNewObjectBufferATI) (GLsizei, const void*, GLenum);
extern pfn_glNewObjectBufferATI fp_glNewObjectBufferATI;
typedef GLboolean (APIENTRYP pfn_glIsObjectBufferATI) (GLuint);
extern pfn_glIsObjectBufferATI fp_glIsObjectBufferATI;
typedef void (APIENTRYP pfn_glUpdateObjectBufferATI) (GLuint, GLuint, GLsizei, const void*, GLenum);
extern pfn_glUpdateObjectBufferATI fp_glUpdateObjectBufferATI;
typedef void (APIENTRYP pfn_glGetObjectBufferfvATI) (GLuint, GLenum, GLfloat*);
extern pfn_glGetObjectBufferfvATI fp_glGetObjectBufferfvATI;
typedef void (APIENTRYP pfn_glGetObjectBufferivATI) (GLuint, GLenum, GLint*);
extern pfn_glGetObjectBufferivATI fp_glGetObjectBufferivATI;
typedef void (APIENTRYP pfn_glFreeObjectBufferATI) (GLuint);
extern pfn_glFreeObjectBufferATI fp_glFreeObjectBufferATI;
typedef void (APIENTRYP pfn_glArrayObjectATI) (GLenum, GLint, GLenum, GLsizei, GLuint, GLuint);
extern pfn_glArrayObjectATI fp_glArrayObjectATI;
typedef void (APIENTRYP pfn_glGetArrayObjectfvATI) (GLenum, GLenum, GLfloat*);
extern pfn_glGetArrayObjectfvATI fp_glGetArrayObjectfvATI;
typedef void (APIENTRYP pfn_glGetArrayObjectivATI) (GLenum, GLenum, GLint*);
extern pfn_glGetArrayObjectivATI fp_glGetArrayObjectivATI;
typedef void (APIENTRYP pfn_glVariantArrayObjectATI) (GLuint, GLenum, GLsizei, GLuint, GLuint);
extern pfn_glVariantArrayObjectATI fp_glVariantArrayObjectATI;
typedef void (APIENTRYP pfn_glGetVariantArrayObjectfvATI) (GLuint, GLenum, GLfloat*);
extern pfn_glGetVariantArrayObjectfvATI fp_glGetVariantArrayObjectfvATI;
typedef void (APIENTRYP pfn_glGetVariantArrayObjectivATI) (GLuint, GLenum, GLint*);
extern pfn_glGetVariantArrayObjectivATI fp_glGetVariantArrayObjectivATI;

 /* GL_ATI_vertex_attrib_array_object */
extern GLboolean GLAD_ATI_vertex_attrib_array_object;
typedef void (APIENTRYP pfn_glVertexAttribArrayObjectATI) (GLuint, GLint, GLenum, GLboolean, GLsizei, GLuint, GLuint);
extern pfn_glVertexAttribArrayObjectATI fp_glVertexAttribArrayObjectATI;
typedef void (APIENTRYP pfn_glGetVertexAttribArrayObjectfvATI) (GLuint, GLenum, GLfloat*);
extern pfn_glGetVertexAttribArrayObjectfvATI fp_glGetVertexAttribArrayObjectfvATI;
typedef void (APIENTRYP pfn_glGetVertexAttribArrayObjectivATI) (GLuint, GLenum, GLint*);
extern pfn_glGetVertexAttribArrayObjectivATI fp_glGetVertexAttribArrayObjectivATI;

 /* GL_ATI_vertex_streams */
extern GLboolean GLAD_ATI_vertex_streams;
#define GL_MAX_VERTEX_STREAMS_ATI              0x876B
#define GL_VERTEX_STREAM0_ATI                  0x876C
#define GL_VERTEX_STREAM1_ATI                  0x876D
#define GL_VERTEX_STREAM2_ATI                  0x876E
#define GL_VERTEX_STREAM3_ATI                  0x876F
#define GL_VERTEX_STREAM4_ATI                  0x8770
#define GL_VERTEX_STREAM5_ATI                  0x8771
#define GL_VERTEX_STREAM6_ATI                  0x8772
#define GL_VERTEX_STREAM7_ATI                  0x8773
#define GL_VERTEX_SOURCE_ATI                   0x8774
typedef void (APIENTRYP pfn_glVertexStream1sATI) (GLenum, GLshort);
extern pfn_glVertexStream1sATI fp_glVertexStream1sATI;
typedef void (APIENTRYP pfn_glVertexStream1svATI) (GLenum, const GLshort*);
extern pfn_glVertexStream1svATI fp_glVertexStream1svATI;
typedef void (APIENTRYP pfn_glVertexStream1iATI) (GLenum, GLint);
extern pfn_glVertexStream1iATI fp_glVertexStream1iATI;
typedef void (APIENTRYP pfn_glVertexStream1ivATI) (GLenum, const GLint*);
extern pfn_glVertexStream1ivATI fp_glVertexStream1ivATI;
typedef void (APIENTRYP pfn_glVertexStream1fATI) (GLenum, GLfloat);
extern pfn_glVertexStream1fATI fp_glVertexStream1fATI;
typedef void (APIENTRYP pfn_glVertexStream1fvATI) (GLenum, const GLfloat*);
extern pfn_glVertexStream1fvATI fp_glVertexStream1fvATI;
typedef void (APIENTRYP pfn_glVertexStream1dATI) (GLenum, GLdouble);
extern pfn_glVertexStream1dATI fp_glVertexStream1dATI;
typedef void (APIENTRYP pfn_glVertexStream1dvATI) (GLenum, const GLdouble*);
extern pfn_glVertexStream1dvATI fp_glVertexStream1dvATI;
typedef void (APIENTRYP pfn_glVertexStream2sATI) (GLenum, GLshort, GLshort);
extern pfn_glVertexStream2sATI fp_glVertexStream2sATI;
typedef void (APIENTRYP pfn_glVertexStream2svATI) (GLenum, const GLshort*);
extern pfn_glVertexStream2svATI fp_glVertexStream2svATI;
typedef void (APIENTRYP pfn_glVertexStream2iATI) (GLenum, GLint, GLint);
extern pfn_glVertexStream2iATI fp_glVertexStream2iATI;
typedef void (APIENTRYP pfn_glVertexStream2ivATI) (GLenum, const GLint*);
extern pfn_glVertexStream2ivATI fp_glVertexStream2ivATI;
typedef void (APIENTRYP pfn_glVertexStream2fATI) (GLenum, GLfloat, GLfloat);
extern pfn_glVertexStream2fATI fp_glVertexStream2fATI;
typedef void (APIENTRYP pfn_glVertexStream2fvATI) (GLenum, const GLfloat*);
extern pfn_glVertexStream2fvATI fp_glVertexStream2fvATI;
typedef void (APIENTRYP pfn_glVertexStream2dATI) (GLenum, GLdouble, GLdouble);
extern pfn_glVertexStream2dATI fp_glVertexStream2dATI;
typedef void (APIENTRYP pfn_glVertexStream2dvATI) (GLenum, const GLdouble*);
extern pfn_glVertexStream2dvATI fp_glVertexStream2dvATI;
typedef void (APIENTRYP pfn_glVertexStream3sATI) (GLenum, GLshort, GLshort, GLshort);
extern pfn_glVertexStream3sATI fp_glVertexStream3sATI;
typedef void (APIENTRYP pfn_glVertexStream3svATI) (GLenum, const GLshort*);
extern pfn_glVertexStream3svATI fp_glVertexStream3svATI;
typedef void (APIENTRYP pfn_glVertexStream3iATI) (GLenum, GLint, GLint, GLint);
extern pfn_glVertexStream3iATI fp_glVertexStream3iATI;
typedef void (APIENTRYP pfn_glVertexStream3ivATI) (GLenum, const GLint*);
extern pfn_glVertexStream3ivATI fp_glVertexStream3ivATI;
typedef void (APIENTRYP pfn_glVertexStream3fATI) (GLenum, GLfloat, GLfloat, GLfloat);
extern pfn_glVertexStream3fATI fp_glVertexStream3fATI;
typedef void (APIENTRYP pfn_glVertexStream3fvATI) (GLenum, const GLfloat*);
extern pfn_glVertexStream3fvATI fp_glVertexStream3fvATI;
typedef void (APIENTRYP pfn_glVertexStream3dATI) (GLenum, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexStream3dATI fp_glVertexStream3dATI;
typedef void (APIENTRYP pfn_glVertexStream3dvATI) (GLenum, const GLdouble*);
extern pfn_glVertexStream3dvATI fp_glVertexStream3dvATI;
typedef void (APIENTRYP pfn_glVertexStream4sATI) (GLenum, GLshort, GLshort, GLshort, GLshort);
extern pfn_glVertexStream4sATI fp_glVertexStream4sATI;
typedef void (APIENTRYP pfn_glVertexStream4svATI) (GLenum, const GLshort*);
extern pfn_glVertexStream4svATI fp_glVertexStream4svATI;
typedef void (APIENTRYP pfn_glVertexStream4iATI) (GLenum, GLint, GLint, GLint, GLint);
extern pfn_glVertexStream4iATI fp_glVertexStream4iATI;
typedef void (APIENTRYP pfn_glVertexStream4ivATI) (GLenum, const GLint*);
extern pfn_glVertexStream4ivATI fp_glVertexStream4ivATI;
typedef void (APIENTRYP pfn_glVertexStream4fATI) (GLenum, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glVertexStream4fATI fp_glVertexStream4fATI;
typedef void (APIENTRYP pfn_glVertexStream4fvATI) (GLenum, const GLfloat*);
extern pfn_glVertexStream4fvATI fp_glVertexStream4fvATI;
typedef void (APIENTRYP pfn_glVertexStream4dATI) (GLenum, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexStream4dATI fp_glVertexStream4dATI;
typedef void (APIENTRYP pfn_glVertexStream4dvATI) (GLenum, const GLdouble*);
extern pfn_glVertexStream4dvATI fp_glVertexStream4dvATI;
typedef void (APIENTRYP pfn_glNormalStream3bATI) (GLenum, GLbyte, GLbyte, GLbyte);
extern pfn_glNormalStream3bATI fp_glNormalStream3bATI;
typedef void (APIENTRYP pfn_glNormalStream3bvATI) (GLenum, const GLbyte*);
extern pfn_glNormalStream3bvATI fp_glNormalStream3bvATI;
typedef void (APIENTRYP pfn_glNormalStream3sATI) (GLenum, GLshort, GLshort, GLshort);
extern pfn_glNormalStream3sATI fp_glNormalStream3sATI;
typedef void (APIENTRYP pfn_glNormalStream3svATI) (GLenum, const GLshort*);
extern pfn_glNormalStream3svATI fp_glNormalStream3svATI;
typedef void (APIENTRYP pfn_glNormalStream3iATI) (GLenum, GLint, GLint, GLint);
extern pfn_glNormalStream3iATI fp_glNormalStream3iATI;
typedef void (APIENTRYP pfn_glNormalStream3ivATI) (GLenum, const GLint*);
extern pfn_glNormalStream3ivATI fp_glNormalStream3ivATI;
typedef void (APIENTRYP pfn_glNormalStream3fATI) (GLenum, GLfloat, GLfloat, GLfloat);
extern pfn_glNormalStream3fATI fp_glNormalStream3fATI;
typedef void (APIENTRYP pfn_glNormalStream3fvATI) (GLenum, const GLfloat*);
extern pfn_glNormalStream3fvATI fp_glNormalStream3fvATI;
typedef void (APIENTRYP pfn_glNormalStream3dATI) (GLenum, GLdouble, GLdouble, GLdouble);
extern pfn_glNormalStream3dATI fp_glNormalStream3dATI;
typedef void (APIENTRYP pfn_glNormalStream3dvATI) (GLenum, const GLdouble*);
extern pfn_glNormalStream3dvATI fp_glNormalStream3dvATI;
typedef void (APIENTRYP pfn_glClientActiveVertexStreamATI) (GLenum);
extern pfn_glClientActiveVertexStreamATI fp_glClientActiveVertexStreamATI;
typedef void (APIENTRYP pfn_glVertexBlendEnviATI) (GLenum, GLint);
extern pfn_glVertexBlendEnviATI fp_glVertexBlendEnviATI;
typedef void (APIENTRYP pfn_glVertexBlendEnvfATI) (GLenum, GLfloat);
extern pfn_glVertexBlendEnvfATI fp_glVertexBlendEnvfATI;

 /* GL_DMP_shader_binary */
extern GLboolean GLAD_DMP_shader_binary;
#define GL_SHADER_BINARY_DMP                   0x9250

 /* GL_FJ_shader_binary_GCCSO */
extern GLboolean GLAD_FJ_shader_binary_GCCSO;
#define GL_GCCSO_SHADER_BINARY_FJ              0x9260

 /* GL_GREMEDY_frame_terminator */
extern GLboolean GLAD_GREMEDY_frame_terminator;
typedef void (APIENTRYP pfn_glFrameTerminatorGREMEDY) ();
extern pfn_glFrameTerminatorGREMEDY fp_glFrameTerminatorGREMEDY;

 /* GL_GREMEDY_string_marker */
extern GLboolean GLAD_GREMEDY_string_marker;
typedef void (APIENTRYP pfn_glStringMarkerGREMEDY) (GLsizei, const void*);
extern pfn_glStringMarkerGREMEDY fp_glStringMarkerGREMEDY;

 /* GL_IBM_rasterpos_clip */
extern GLboolean GLAD_IBM_rasterpos_clip;
#define GL_RASTER_POSITION_UNCLIPPED_IBM       0x19262

 /* GL_IMG_multisampled_render_to_texture */
extern GLboolean GLAD_IMG_multisampled_render_to_texture;
#define GL_RENDERBUFFER_SAMPLES_IMG            0x9133
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG  0x9134
#define GL_MAX_SAMPLES_IMG                     0x9135
#define GL_TEXTURE_SAMPLES_IMG                 0x9136
typedef void (APIENTRYP pfn_glRenderbufferStorageMultisampleIMG) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glRenderbufferStorageMultisampleIMG fp_glRenderbufferStorageMultisampleIMG;
typedef void (APIENTRYP pfn_glFramebufferTexture2DMultisampleIMG) (GLenum, GLenum, GLenum, GLuint, GLint, GLsizei);
extern pfn_glFramebufferTexture2DMultisampleIMG fp_glFramebufferTexture2DMultisampleIMG;

 /* GL_IMG_program_binary */
extern GLboolean GLAD_IMG_program_binary;
#define GL_SGX_PROGRAM_BINARY_IMG              0x9130

 /* GL_IMG_read_format */
extern GLboolean GLAD_IMG_read_format;
#define GL_BGRA_IMG                            0x80E1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG      0x8365

 /* GL_IMG_shader_binary */
extern GLboolean GLAD_IMG_shader_binary;
#define GL_SGX_BINARY_IMG                      0x8C0A

 /* GL_IMG_texture_compression_pvrtc */
extern GLboolean GLAD_IMG_texture_compression_pvrtc;
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG     0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG     0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG    0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG    0x8C03

 /* GL_IMG_texture_compression_pvrtc2 */
extern GLboolean GLAD_IMG_texture_compression_pvrtc2;
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG    0x9137
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG    0x9138

 /* GL_INGR_blend_func_separate */
extern GLboolean GLAD_INGR_blend_func_separate;
typedef void (APIENTRYP pfn_glBlendFuncSeparateINGR) (GLenum, GLenum, GLenum, GLenum);
extern pfn_glBlendFuncSeparateINGR fp_glBlendFuncSeparateINGR;

 /* GL_INTEL_fragment_shader_ordering */
extern GLboolean GLAD_INTEL_fragment_shader_ordering;

 /* GL_INTEL_map_texture */
extern GLboolean GLAD_INTEL_map_texture;
#define GL_TEXTURE_MEMORY_LAYOUT_INTEL         0x83FF
#define GL_LAYOUT_DEFAULT_INTEL                0
#define GL_LAYOUT_LINEAR_INTEL                 1
#define GL_LAYOUT_LINEAR_CPU_CACHED_INTEL      2
typedef void (APIENTRYP pfn_glSyncTextureINTEL) (GLuint);
extern pfn_glSyncTextureINTEL fp_glSyncTextureINTEL;
typedef void (APIENTRYP pfn_glUnmapTexture2DINTEL) (GLuint, GLint);
extern pfn_glUnmapTexture2DINTEL fp_glUnmapTexture2DINTEL;
typedef void* (APIENTRYP pfn_glMapTexture2DINTEL) (GLuint, GLint, GLbitfield, GLint*, GLenum*);
extern pfn_glMapTexture2DINTEL fp_glMapTexture2DINTEL;

 /* GL_INTEL_parallel_arrays */
extern GLboolean GLAD_INTEL_parallel_arrays;
#define GL_PARALLEL_ARRAYS_INTEL               0x83F4
#define GL_VERTEX_ARRAY_PARALLEL_POINTERS_INTEL  0x83F5
#define GL_NORMAL_ARRAY_PARALLEL_POINTERS_INTEL  0x83F6
#define GL_COLOR_ARRAY_PARALLEL_POINTERS_INTEL  0x83F7
#define GL_TEXTURE_COORD_ARRAY_PARALLEL_POINTERS_INTEL  0x83F8
typedef void (APIENTRYP pfn_glVertexPointervINTEL) (GLint, GLenum, const void**);
extern pfn_glVertexPointervINTEL fp_glVertexPointervINTEL;
typedef void (APIENTRYP pfn_glNormalPointervINTEL) (GLenum, const void**);
extern pfn_glNormalPointervINTEL fp_glNormalPointervINTEL;
typedef void (APIENTRYP pfn_glColorPointervINTEL) (GLint, GLenum, const void**);
extern pfn_glColorPointervINTEL fp_glColorPointervINTEL;
typedef void (APIENTRYP pfn_glTexCoordPointervINTEL) (GLint, GLenum, const void**);
extern pfn_glTexCoordPointervINTEL fp_glTexCoordPointervINTEL;

 /* GL_MESA_pack_invert */
extern GLboolean GLAD_MESA_pack_invert;
#define GL_PACK_INVERT_MESA                    0x8758

 /* GL_MESA_resize_buffers */
extern GLboolean GLAD_MESA_resize_buffers;
typedef void (APIENTRYP pfn_glResizeBuffersMESA) ();
extern pfn_glResizeBuffersMESA fp_glResizeBuffersMESA;

 /* GL_MESA_window_pos */
extern GLboolean GLAD_MESA_window_pos;
typedef void (APIENTRYP pfn_glWindowPos2dMESA) (GLdouble, GLdouble);
extern pfn_glWindowPos2dMESA fp_glWindowPos2dMESA;
typedef void (APIENTRYP pfn_glWindowPos2dvMESA) (const GLdouble*);
extern pfn_glWindowPos2dvMESA fp_glWindowPos2dvMESA;
typedef void (APIENTRYP pfn_glWindowPos2fMESA) (GLfloat, GLfloat);
extern pfn_glWindowPos2fMESA fp_glWindowPos2fMESA;
typedef void (APIENTRYP pfn_glWindowPos2fvMESA) (const GLfloat*);
extern pfn_glWindowPos2fvMESA fp_glWindowPos2fvMESA;
typedef void (APIENTRYP pfn_glWindowPos2iMESA) (GLint, GLint);
extern pfn_glWindowPos2iMESA fp_glWindowPos2iMESA;
typedef void (APIENTRYP pfn_glWindowPos2ivMESA) (const GLint*);
extern pfn_glWindowPos2ivMESA fp_glWindowPos2ivMESA;
typedef void (APIENTRYP pfn_glWindowPos2sMESA) (GLshort, GLshort);
extern pfn_glWindowPos2sMESA fp_glWindowPos2sMESA;
typedef void (APIENTRYP pfn_glWindowPos2svMESA) (const GLshort*);
extern pfn_glWindowPos2svMESA fp_glWindowPos2svMESA;
typedef void (APIENTRYP pfn_glWindowPos3dMESA) (GLdouble, GLdouble, GLdouble);
extern pfn_glWindowPos3dMESA fp_glWindowPos3dMESA;
typedef void (APIENTRYP pfn_glWindowPos3dvMESA) (const GLdouble*);
extern pfn_glWindowPos3dvMESA fp_glWindowPos3dvMESA;
typedef void (APIENTRYP pfn_glWindowPos3fMESA) (GLfloat, GLfloat, GLfloat);
extern pfn_glWindowPos3fMESA fp_glWindowPos3fMESA;
typedef void (APIENTRYP pfn_glWindowPos3fvMESA) (const GLfloat*);
extern pfn_glWindowPos3fvMESA fp_glWindowPos3fvMESA;
typedef void (APIENTRYP pfn_glWindowPos3iMESA) (GLint, GLint, GLint);
extern pfn_glWindowPos3iMESA fp_glWindowPos3iMESA;
typedef void (APIENTRYP pfn_glWindowPos3ivMESA) (const GLint*);
extern pfn_glWindowPos3ivMESA fp_glWindowPos3ivMESA;
typedef void (APIENTRYP pfn_glWindowPos3sMESA) (GLshort, GLshort, GLshort);
extern pfn_glWindowPos3sMESA fp_glWindowPos3sMESA;
typedef void (APIENTRYP pfn_glWindowPos3svMESA) (const GLshort*);
extern pfn_glWindowPos3svMESA fp_glWindowPos3svMESA;
typedef void (APIENTRYP pfn_glWindowPos4dMESA) (GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glWindowPos4dMESA fp_glWindowPos4dMESA;
typedef void (APIENTRYP pfn_glWindowPos4dvMESA) (const GLdouble*);
extern pfn_glWindowPos4dvMESA fp_glWindowPos4dvMESA;
typedef void (APIENTRYP pfn_glWindowPos4fMESA) (GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glWindowPos4fMESA fp_glWindowPos4fMESA;
typedef void (APIENTRYP pfn_glWindowPos4fvMESA) (const GLfloat*);
extern pfn_glWindowPos4fvMESA fp_glWindowPos4fvMESA;
typedef void (APIENTRYP pfn_glWindowPos4iMESA) (GLint, GLint, GLint, GLint);
extern pfn_glWindowPos4iMESA fp_glWindowPos4iMESA;
typedef void (APIENTRYP pfn_glWindowPos4ivMESA) (const GLint*);
extern pfn_glWindowPos4ivMESA fp_glWindowPos4ivMESA;
typedef void (APIENTRYP pfn_glWindowPos4sMESA) (GLshort, GLshort, GLshort, GLshort);
extern pfn_glWindowPos4sMESA fp_glWindowPos4sMESA;
typedef void (APIENTRYP pfn_glWindowPos4svMESA) (const GLshort*);
extern pfn_glWindowPos4svMESA fp_glWindowPos4svMESA;

 /* GL_MESA_ycbcr_texture */
extern GLboolean GLAD_MESA_ycbcr_texture;
#define GL_UNSIGNED_SHORT_8_8_MESA             0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_MESA         0x85BB
#define GL_YCBCR_MESA                          0x8757

 /* GL_MESAX_texture_stack */
extern GLboolean GLAD_MESAX_texture_stack;
#define GL_TEXTURE_1D_STACK_MESAX              0x8759
#define GL_TEXTURE_2D_STACK_MESAX              0x875A
#define GL_PROXY_TEXTURE_1D_STACK_MESAX        0x875B
#define GL_PROXY_TEXTURE_2D_STACK_MESAX        0x875C
#define GL_TEXTURE_1D_STACK_BINDING_MESAX      0x875D
#define GL_TEXTURE_2D_STACK_BINDING_MESAX      0x875E

 /* GL_NV_bindless_multi_draw_indirect */
extern GLboolean GLAD_NV_bindless_multi_draw_indirect;
typedef void (APIENTRYP pfn_glMultiDrawArraysIndirectBindlessNV) (GLenum, const void*, GLsizei, GLsizei, GLint);
extern pfn_glMultiDrawArraysIndirectBindlessNV fp_glMultiDrawArraysIndirectBindlessNV;
typedef void (APIENTRYP pfn_glMultiDrawElementsIndirectBindlessNV) (GLenum, GLenum, const void*, GLsizei, GLsizei, GLint);
extern pfn_glMultiDrawElementsIndirectBindlessNV fp_glMultiDrawElementsIndirectBindlessNV;

 /* GL_NV_bindless_texture */
extern GLboolean GLAD_NV_bindless_texture;
typedef GLuint64 (APIENTRYP pfn_glGetTextureHandleNV) (GLuint);
extern pfn_glGetTextureHandleNV fp_glGetTextureHandleNV;
typedef GLuint64 (APIENTRYP pfn_glGetTextureSamplerHandleNV) (GLuint, GLuint);
extern pfn_glGetTextureSamplerHandleNV fp_glGetTextureSamplerHandleNV;
typedef void (APIENTRYP pfn_glMakeTextureHandleResidentNV) (GLuint64);
extern pfn_glMakeTextureHandleResidentNV fp_glMakeTextureHandleResidentNV;
typedef void (APIENTRYP pfn_glMakeTextureHandleNonResidentNV) (GLuint64);
extern pfn_glMakeTextureHandleNonResidentNV fp_glMakeTextureHandleNonResidentNV;
typedef GLuint64 (APIENTRYP pfn_glGetImageHandleNV) (GLuint, GLint, GLboolean, GLint, GLenum);
extern pfn_glGetImageHandleNV fp_glGetImageHandleNV;
typedef void (APIENTRYP pfn_glMakeImageHandleResidentNV) (GLuint64, GLenum);
extern pfn_glMakeImageHandleResidentNV fp_glMakeImageHandleResidentNV;
typedef void (APIENTRYP pfn_glMakeImageHandleNonResidentNV) (GLuint64);
extern pfn_glMakeImageHandleNonResidentNV fp_glMakeImageHandleNonResidentNV;
typedef void (APIENTRYP pfn_glUniformHandleui64NV) (GLint, GLuint64);
extern pfn_glUniformHandleui64NV fp_glUniformHandleui64NV;
typedef void (APIENTRYP pfn_glUniformHandleui64vNV) (GLint, GLsizei, const GLuint64*);
extern pfn_glUniformHandleui64vNV fp_glUniformHandleui64vNV;
typedef void (APIENTRYP pfn_glProgramUniformHandleui64NV) (GLuint, GLint, GLuint64);
extern pfn_glProgramUniformHandleui64NV fp_glProgramUniformHandleui64NV;
typedef void (APIENTRYP pfn_glProgramUniformHandleui64vNV) (GLuint, GLint, GLsizei, const GLuint64*);
extern pfn_glProgramUniformHandleui64vNV fp_glProgramUniformHandleui64vNV;
typedef GLboolean (APIENTRYP pfn_glIsTextureHandleResidentNV) (GLuint64);
extern pfn_glIsTextureHandleResidentNV fp_glIsTextureHandleResidentNV;
typedef GLboolean (APIENTRYP pfn_glIsImageHandleResidentNV) (GLuint64);
extern pfn_glIsImageHandleResidentNV fp_glIsImageHandleResidentNV;

 /* GL_NV_blend_equation_advanced */
extern GLboolean GLAD_NV_blend_equation_advanced;
#define GL_BLUE_NV                             0x1905
#define GL_GREEN_NV                            0x1904
#define GL_RED_NV                              0x1903
#define GL_XOR_NV                              0x1506
#define GL_BLEND_OVERLAP_NV                    0x9281
#define GL_BLEND_PREMULTIPLIED_SRC_NV          0x9280
#define GL_COLORBURN_NV                        0x929A
#define GL_COLORDODGE_NV                       0x9299
#define GL_CONJOINT_NV                         0x9284
#define GL_CONTRAST_NV                         0x92A1
#define GL_DARKEN_NV                           0x9297
#define GL_DIFFERENCE_NV                       0x929E
#define GL_DISJOINT_NV                         0x9283
#define GL_DST_ATOP_NV                         0x928F
#define GL_DST_IN_NV                           0x928B
#define GL_DST_NV                              0x9287
#define GL_DST_OUT_NV                          0x928D
#define GL_DST_OVER_NV                         0x9289
#define GL_EXCLUSION_NV                        0x92A0
#define GL_HARDLIGHT_NV                        0x929B
#define GL_HARDMIX_NV                          0x92A9
#define GL_HSL_COLOR_NV                        0x92AF
#define GL_HSL_HUE_NV                          0x92AD
#define GL_HSL_LUMINOSITY_NV                   0x92B0
#define GL_HSL_SATURATION_NV                   0x92AE
#define GL_INVERT_OVG_NV                       0x92B4
#define GL_INVERT_RGB_NV                       0x92A3
#define GL_LIGHTEN_NV                          0x9298
#define GL_LINEARBURN_NV                       0x92A5
#define GL_LINEARDODGE_NV                      0x92A4
#define GL_LINEARLIGHT_NV                      0x92A7
#define GL_MINUS_CLAMPED_NV                    0x92B3
#define GL_MINUS_NV                            0x929F
#define GL_MULTIPLY_NV                         0x9294
#define GL_OVERLAY_NV                          0x9296
#define GL_PINLIGHT_NV                         0x92A8
#define GL_PLUS_CLAMPED_ALPHA_NV               0x92B2
#define GL_PLUS_CLAMPED_NV                     0x92B1
#define GL_PLUS_DARKER_NV                      0x9292
#define GL_PLUS_NV                             0x9291
#define GL_SCREEN_NV                           0x9295
#define GL_SOFTLIGHT_NV                        0x929C
#define GL_SRC_ATOP_NV                         0x928E
#define GL_SRC_IN_NV                           0x928A
#define GL_SRC_NV                              0x9286
#define GL_SRC_OUT_NV                          0x928C
#define GL_SRC_OVER_NV                         0x9288
#define GL_UNCORRELATED_NV                     0x9282
#define GL_VIVIDLIGHT_NV                       0x92A6
typedef void (APIENTRYP pfn_glBlendParameteriNV) (GLenum, GLint);
extern pfn_glBlendParameteriNV fp_glBlendParameteriNV;
typedef void (APIENTRYP pfn_glBlendBarrierNV) ();
extern pfn_glBlendBarrierNV fp_glBlendBarrierNV;

 /* GL_NV_blend_equation_advanced_coherent */
extern GLboolean GLAD_NV_blend_equation_advanced_coherent;
#define GL_BLEND_ADVANCED_COHERENT_NV          0x9285

 /* GL_NV_blend_square */
extern GLboolean GLAD_NV_blend_square;

 /* GL_NV_compute_program5 */
extern GLboolean GLAD_NV_compute_program5;
#define GL_COMPUTE_PROGRAM_NV                  0x90FB
#define GL_COMPUTE_PROGRAM_PARAMETER_BUFFER_NV  0x90FC

 /* GL_NV_conditional_render */
extern GLboolean GLAD_NV_conditional_render;
#define GL_QUERY_WAIT_NV                       0x8E13
#define GL_QUERY_NO_WAIT_NV                    0x8E14
#define GL_QUERY_BY_REGION_WAIT_NV             0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT_NV          0x8E16
typedef void (APIENTRYP pfn_glBeginConditionalRenderNV) (GLuint, GLenum);
extern pfn_glBeginConditionalRenderNV fp_glBeginConditionalRenderNV;
typedef void (APIENTRYP pfn_glEndConditionalRenderNV) ();
extern pfn_glEndConditionalRenderNV fp_glEndConditionalRenderNV;

 /* GL_NV_copy_buffer */
extern GLboolean GLAD_NV_copy_buffer;
#define GL_COPY_READ_BUFFER_NV                 0x8F36
#define GL_COPY_WRITE_BUFFER_NV                0x8F37
typedef void (APIENTRYP pfn_glCopyBufferSubDataNV) (GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
extern pfn_glCopyBufferSubDataNV fp_glCopyBufferSubDataNV;

 /* GL_NV_copy_depth_to_color */
extern GLboolean GLAD_NV_copy_depth_to_color;
#define GL_DEPTH_STENCIL_TO_RGBA_NV            0x886E
#define GL_DEPTH_STENCIL_TO_BGRA_NV            0x886F

 /* GL_NV_copy_image */
extern GLboolean GLAD_NV_copy_image;
typedef void (APIENTRYP pfn_glCopyImageSubDataNV) (GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
extern pfn_glCopyImageSubDataNV fp_glCopyImageSubDataNV;

 /* GL_NV_coverage_sample */
extern GLboolean GLAD_NV_coverage_sample;
#define GL_COVERAGE_COMPONENT_NV               0x8ED0
#define GL_COVERAGE_COMPONENT4_NV              0x8ED1
#define GL_COVERAGE_ATTACHMENT_NV              0x8ED2
#define GL_COVERAGE_BUFFERS_NV                 0x8ED3
#define GL_COVERAGE_SAMPLES_NV                 0x8ED4
#define GL_COVERAGE_ALL_FRAGMENTS_NV           0x8ED5
#define GL_COVERAGE_EDGE_FRAGMENTS_NV          0x8ED6
#define GL_COVERAGE_AUTOMATIC_NV               0x8ED7
#define GL_COVERAGE_BUFFER_BIT_NV              0x00008000
typedef void (APIENTRYP pfn_glCoverageMaskNV) (GLboolean);
extern pfn_glCoverageMaskNV fp_glCoverageMaskNV;
typedef void (APIENTRYP pfn_glCoverageOperationNV) (GLenum);
extern pfn_glCoverageOperationNV fp_glCoverageOperationNV;

 /* GL_NV_deep_texture3D */
extern GLboolean GLAD_NV_deep_texture3D;
#define GL_MAX_DEEP_3D_TEXTURE_WIDTH_HEIGHT_NV  0x90D0
#define GL_MAX_DEEP_3D_TEXTURE_DEPTH_NV        0x90D1

 /* GL_NV_depth_buffer_float */
extern GLboolean GLAD_NV_depth_buffer_float;
#define GL_DEPTH_COMPONENT32F_NV               0x8DAB
#define GL_DEPTH32F_STENCIL8_NV                0x8DAC
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV_NV   0x8DAD
#define GL_DEPTH_BUFFER_FLOAT_MODE_NV          0x8DAF
typedef void (APIENTRYP pfn_glDepthRangedNV) (GLdouble, GLdouble);
extern pfn_glDepthRangedNV fp_glDepthRangedNV;
typedef void (APIENTRYP pfn_glClearDepthdNV) (GLdouble);
extern pfn_glClearDepthdNV fp_glClearDepthdNV;
typedef void (APIENTRYP pfn_glDepthBoundsdNV) (GLdouble, GLdouble);
extern pfn_glDepthBoundsdNV fp_glDepthBoundsdNV;

 /* GL_NV_depth_clamp */
extern GLboolean GLAD_NV_depth_clamp;
#define GL_DEPTH_CLAMP_NV                      0x864F

 /* GL_NV_depth_nonlinear */
extern GLboolean GLAD_NV_depth_nonlinear;
#define GL_DEPTH_COMPONENT16_NONLINEAR_NV      0x8E2C

 /* GL_NV_draw_buffers */
extern GLboolean GLAD_NV_draw_buffers;
#define GL_MAX_DRAW_BUFFERS_NV                 0x8824
#define GL_DRAW_BUFFER0_NV                     0x8825
#define GL_DRAW_BUFFER1_NV                     0x8826
#define GL_DRAW_BUFFER2_NV                     0x8827
#define GL_DRAW_BUFFER3_NV                     0x8828
#define GL_DRAW_BUFFER4_NV                     0x8829
#define GL_DRAW_BUFFER5_NV                     0x882A
#define GL_DRAW_BUFFER6_NV                     0x882B
#define GL_DRAW_BUFFER7_NV                     0x882C
#define GL_DRAW_BUFFER8_NV                     0x882D
#define GL_DRAW_BUFFER9_NV                     0x882E
#define GL_DRAW_BUFFER10_NV                    0x882F
#define GL_DRAW_BUFFER11_NV                    0x8830
#define GL_DRAW_BUFFER12_NV                    0x8831
#define GL_DRAW_BUFFER13_NV                    0x8832
#define GL_DRAW_BUFFER14_NV                    0x8833
#define GL_DRAW_BUFFER15_NV                    0x8834
#define GL_COLOR_ATTACHMENT0_NV                0x8CE0
#define GL_COLOR_ATTACHMENT1_NV                0x8CE1
#define GL_COLOR_ATTACHMENT2_NV                0x8CE2
#define GL_COLOR_ATTACHMENT3_NV                0x8CE3
#define GL_COLOR_ATTACHMENT4_NV                0x8CE4
#define GL_COLOR_ATTACHMENT5_NV                0x8CE5
#define GL_COLOR_ATTACHMENT6_NV                0x8CE6
#define GL_COLOR_ATTACHMENT7_NV                0x8CE7
#define GL_COLOR_ATTACHMENT8_NV                0x8CE8
#define GL_COLOR_ATTACHMENT9_NV                0x8CE9
#define GL_COLOR_ATTACHMENT10_NV               0x8CEA
#define GL_COLOR_ATTACHMENT11_NV               0x8CEB
#define GL_COLOR_ATTACHMENT12_NV               0x8CEC
#define GL_COLOR_ATTACHMENT13_NV               0x8CED
#define GL_COLOR_ATTACHMENT14_NV               0x8CEE
#define GL_COLOR_ATTACHMENT15_NV               0x8CEF
typedef void (APIENTRYP pfn_glDrawBuffersNV) (GLsizei, const GLenum*);
extern pfn_glDrawBuffersNV fp_glDrawBuffersNV;

 /* GL_NV_draw_instanced */
extern GLboolean GLAD_NV_draw_instanced;
typedef void (APIENTRYP pfn_glDrawArraysInstancedNV) (GLenum, GLint, GLsizei, GLsizei);
extern pfn_glDrawArraysInstancedNV fp_glDrawArraysInstancedNV;
typedef void (APIENTRYP pfn_glDrawElementsInstancedNV) (GLenum, GLsizei, GLenum, const void*, GLsizei);
extern pfn_glDrawElementsInstancedNV fp_glDrawElementsInstancedNV;

 /* GL_NV_draw_texture */
extern GLboolean GLAD_NV_draw_texture;
typedef void (APIENTRYP pfn_glDrawTextureNV) (GLuint, GLuint, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glDrawTextureNV fp_glDrawTextureNV;

 /* GL_NV_evaluators */
extern GLboolean GLAD_NV_evaluators;
#define GL_EVAL_2D_NV                          0x86C0
#define GL_EVAL_TRIANGULAR_2D_NV               0x86C1
#define GL_MAP_TESSELLATION_NV                 0x86C2
#define GL_MAP_ATTRIB_U_ORDER_NV               0x86C3
#define GL_MAP_ATTRIB_V_ORDER_NV               0x86C4
#define GL_EVAL_FRACTIONAL_TESSELLATION_NV     0x86C5
#define GL_EVAL_VERTEX_ATTRIB0_NV              0x86C6
#define GL_EVAL_VERTEX_ATTRIB1_NV              0x86C7
#define GL_EVAL_VERTEX_ATTRIB2_NV              0x86C8
#define GL_EVAL_VERTEX_ATTRIB3_NV              0x86C9
#define GL_EVAL_VERTEX_ATTRIB4_NV              0x86CA
#define GL_EVAL_VERTEX_ATTRIB5_NV              0x86CB
#define GL_EVAL_VERTEX_ATTRIB6_NV              0x86CC
#define GL_EVAL_VERTEX_ATTRIB7_NV              0x86CD
#define GL_EVAL_VERTEX_ATTRIB8_NV              0x86CE
#define GL_EVAL_VERTEX_ATTRIB9_NV              0x86CF
#define GL_EVAL_VERTEX_ATTRIB10_NV             0x86D0
#define GL_EVAL_VERTEX_ATTRIB11_NV             0x86D1
#define GL_EVAL_VERTEX_ATTRIB12_NV             0x86D2
#define GL_EVAL_VERTEX_ATTRIB13_NV             0x86D3
#define GL_EVAL_VERTEX_ATTRIB14_NV             0x86D4
#define GL_EVAL_VERTEX_ATTRIB15_NV             0x86D5
#define GL_MAX_MAP_TESSELLATION_NV             0x86D6
#define GL_MAX_RATIONAL_EVAL_ORDER_NV          0x86D7
typedef void (APIENTRYP pfn_glMapControlPointsNV) (GLenum, GLuint, GLenum, GLsizei, GLsizei, GLint, GLint, GLboolean, const void*);
extern pfn_glMapControlPointsNV fp_glMapControlPointsNV;
typedef void (APIENTRYP pfn_glMapParameterivNV) (GLenum, GLenum, const GLint*);
extern pfn_glMapParameterivNV fp_glMapParameterivNV;
typedef void (APIENTRYP pfn_glMapParameterfvNV) (GLenum, GLenum, const GLfloat*);
extern pfn_glMapParameterfvNV fp_glMapParameterfvNV;
typedef void (APIENTRYP pfn_glGetMapControlPointsNV) (GLenum, GLuint, GLenum, GLsizei, GLsizei, GLboolean, void*);
extern pfn_glGetMapControlPointsNV fp_glGetMapControlPointsNV;
typedef void (APIENTRYP pfn_glGetMapParameterivNV) (GLenum, GLenum, GLint*);
extern pfn_glGetMapParameterivNV fp_glGetMapParameterivNV;
typedef void (APIENTRYP pfn_glGetMapParameterfvNV) (GLenum, GLenum, GLfloat*);
extern pfn_glGetMapParameterfvNV fp_glGetMapParameterfvNV;
typedef void (APIENTRYP pfn_glGetMapAttribParameterivNV) (GLenum, GLuint, GLenum, GLint*);
extern pfn_glGetMapAttribParameterivNV fp_glGetMapAttribParameterivNV;
typedef void (APIENTRYP pfn_glGetMapAttribParameterfvNV) (GLenum, GLuint, GLenum, GLfloat*);
extern pfn_glGetMapAttribParameterfvNV fp_glGetMapAttribParameterfvNV;
typedef void (APIENTRYP pfn_glEvalMapsNV) (GLenum, GLenum);
extern pfn_glEvalMapsNV fp_glEvalMapsNV;

 /* GL_NV_explicit_attrib_location */
extern GLboolean GLAD_NV_explicit_attrib_location;

 /* GL_NV_explicit_multisample */
extern GLboolean GLAD_NV_explicit_multisample;
#define GL_SAMPLE_POSITION_NV                  0x8E50
#define GL_SAMPLE_MASK_NV                      0x8E51
#define GL_SAMPLE_MASK_VALUE_NV                0x8E52
#define GL_TEXTURE_BINDING_RENDERBUFFER_NV     0x8E53
#define GL_TEXTURE_RENDERBUFFER_DATA_STORE_BINDING_NV  0x8E54
#define GL_TEXTURE_RENDERBUFFER_NV             0x8E55
#define GL_SAMPLER_RENDERBUFFER_NV             0x8E56
#define GL_INT_SAMPLER_RENDERBUFFER_NV         0x8E57
#define GL_UNSIGNED_INT_SAMPLER_RENDERBUFFER_NV  0x8E58
#define GL_MAX_SAMPLE_MASK_WORDS_NV            0x8E59
typedef void (APIENTRYP pfn_glGetMultisamplefvNV) (GLenum, GLuint, GLfloat*);
extern pfn_glGetMultisamplefvNV fp_glGetMultisamplefvNV;
typedef void (APIENTRYP pfn_glSampleMaskIndexedNV) (GLuint, GLbitfield);
extern pfn_glSampleMaskIndexedNV fp_glSampleMaskIndexedNV;
typedef void (APIENTRYP pfn_glTexRenderbufferNV) (GLenum, GLuint);
extern pfn_glTexRenderbufferNV fp_glTexRenderbufferNV;

 /* GL_NV_fbo_color_attachments */
extern GLboolean GLAD_NV_fbo_color_attachments;
#define GL_MAX_COLOR_ATTACHMENTS_NV            0x8CDF

 /* GL_NV_fence */
extern GLboolean GLAD_NV_fence;
#define GL_ALL_COMPLETED_NV                    0x84F2
#define GL_FENCE_STATUS_NV                     0x84F3
#define GL_FENCE_CONDITION_NV                  0x84F4
typedef void (APIENTRYP pfn_glDeleteFencesNV) (GLsizei, const GLuint*);
extern pfn_glDeleteFencesNV fp_glDeleteFencesNV;
typedef void (APIENTRYP pfn_glGenFencesNV) (GLsizei, GLuint*);
extern pfn_glGenFencesNV fp_glGenFencesNV;
typedef GLboolean (APIENTRYP pfn_glIsFenceNV) (GLuint);
extern pfn_glIsFenceNV fp_glIsFenceNV;
typedef GLboolean (APIENTRYP pfn_glTestFenceNV) (GLuint);
extern pfn_glTestFenceNV fp_glTestFenceNV;
typedef void (APIENTRYP pfn_glGetFenceivNV) (GLuint, GLenum, GLint*);
extern pfn_glGetFenceivNV fp_glGetFenceivNV;
typedef void (APIENTRYP pfn_glFinishFenceNV) (GLuint);
extern pfn_glFinishFenceNV fp_glFinishFenceNV;
typedef void (APIENTRYP pfn_glSetFenceNV) (GLuint, GLenum);
extern pfn_glSetFenceNV fp_glSetFenceNV;

 /* GL_NV_float_buffer */
extern GLboolean GLAD_NV_float_buffer;
#define GL_FLOAT_R_NV                          0x8880
#define GL_FLOAT_RG_NV                         0x8881
#define GL_FLOAT_RGB_NV                        0x8882
#define GL_FLOAT_RGBA_NV                       0x8883
#define GL_FLOAT_R16_NV                        0x8884
#define GL_FLOAT_R32_NV                        0x8885
#define GL_FLOAT_RG16_NV                       0x8886
#define GL_FLOAT_RG32_NV                       0x8887
#define GL_FLOAT_RGB16_NV                      0x8888
#define GL_FLOAT_RGB32_NV                      0x8889
#define GL_FLOAT_RGBA16_NV                     0x888A
#define GL_FLOAT_RGBA32_NV                     0x888B
#define GL_TEXTURE_FLOAT_COMPONENTS_NV         0x888C
#define GL_FLOAT_CLEAR_COLOR_VALUE_NV          0x888D
#define GL_FLOAT_RGBA_MODE_NV                  0x888E

 /* GL_NV_fog_distance */
extern GLboolean GLAD_NV_fog_distance;
#define GL_FOG_DISTANCE_MODE_NV                0x855A
#define GL_EYE_RADIAL_NV                       0x855B
#define GL_EYE_PLANE_ABSOLUTE_NV               0x855C

 /* GL_NV_fragment_program */
extern GLboolean GLAD_NV_fragment_program;
#define GL_MAX_FRAGMENT_PROGRAM_LOCAL_PARAMETERS_NV  0x8868
#define GL_FRAGMENT_PROGRAM_NV                 0x8870
#define GL_MAX_TEXTURE_COORDS_NV               0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_NV          0x8872
#define GL_FRAGMENT_PROGRAM_BINDING_NV         0x8873
#define GL_PROGRAM_ERROR_STRING_NV             0x8874
typedef void (APIENTRYP pfn_glProgramNamedParameter4fNV) (GLuint, GLsizei, const GLubyte*, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glProgramNamedParameter4fNV fp_glProgramNamedParameter4fNV;
typedef void (APIENTRYP pfn_glProgramNamedParameter4fvNV) (GLuint, GLsizei, const GLubyte*, const GLfloat*);
extern pfn_glProgramNamedParameter4fvNV fp_glProgramNamedParameter4fvNV;
typedef void (APIENTRYP pfn_glProgramNamedParameter4dNV) (GLuint, GLsizei, const GLubyte*, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glProgramNamedParameter4dNV fp_glProgramNamedParameter4dNV;
typedef void (APIENTRYP pfn_glProgramNamedParameter4dvNV) (GLuint, GLsizei, const GLubyte*, const GLdouble*);
extern pfn_glProgramNamedParameter4dvNV fp_glProgramNamedParameter4dvNV;
typedef void (APIENTRYP pfn_glGetProgramNamedParameterfvNV) (GLuint, GLsizei, const GLubyte*, GLfloat*);
extern pfn_glGetProgramNamedParameterfvNV fp_glGetProgramNamedParameterfvNV;
typedef void (APIENTRYP pfn_glGetProgramNamedParameterdvNV) (GLuint, GLsizei, const GLubyte*, GLdouble*);
extern pfn_glGetProgramNamedParameterdvNV fp_glGetProgramNamedParameterdvNV;

 /* GL_NV_fragment_program2 */
extern GLboolean GLAD_NV_fragment_program2;
#define GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV    0x88F4
#define GL_MAX_PROGRAM_CALL_DEPTH_NV           0x88F5
#define GL_MAX_PROGRAM_IF_DEPTH_NV             0x88F6
#define GL_MAX_PROGRAM_LOOP_DEPTH_NV           0x88F7
#define GL_MAX_PROGRAM_LOOP_COUNT_NV           0x88F8

 /* GL_NV_fragment_program4 */
extern GLboolean GLAD_NV_fragment_program4;

 /* GL_NV_fragment_program_option */
extern GLboolean GLAD_NV_fragment_program_option;

 /* GL_NV_framebuffer_blit */
extern GLboolean GLAD_NV_framebuffer_blit;
#define GL_READ_FRAMEBUFFER_NV                 0x8CA8
#define GL_DRAW_FRAMEBUFFER_NV                 0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_NV         0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_NV         0x8CAA
typedef void (APIENTRYP pfn_glBlitFramebufferNV) (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
extern pfn_glBlitFramebufferNV fp_glBlitFramebufferNV;

 /* GL_NV_framebuffer_multisample */
extern GLboolean GLAD_NV_framebuffer_multisample;
#define GL_RENDERBUFFER_SAMPLES_NV             0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV  0x8D56
#define GL_MAX_SAMPLES_NV                      0x8D57
typedef void (APIENTRYP pfn_glRenderbufferStorageMultisampleNV) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glRenderbufferStorageMultisampleNV fp_glRenderbufferStorageMultisampleNV;

 /* GL_NV_framebuffer_multisample_coverage */
extern GLboolean GLAD_NV_framebuffer_multisample_coverage;
#define GL_RENDERBUFFER_COVERAGE_SAMPLES_NV    0x8CAB
#define GL_RENDERBUFFER_COLOR_SAMPLES_NV       0x8E10
#define GL_MAX_MULTISAMPLE_COVERAGE_MODES_NV   0x8E11
#define GL_MULTISAMPLE_COVERAGE_MODES_NV       0x8E12
typedef void (APIENTRYP pfn_glRenderbufferStorageMultisampleCoverageNV) (GLenum, GLsizei, GLsizei, GLenum, GLsizei, GLsizei);
extern pfn_glRenderbufferStorageMultisampleCoverageNV fp_glRenderbufferStorageMultisampleCoverageNV;

 /* GL_NV_generate_mipmap_sRGB */
extern GLboolean GLAD_NV_generate_mipmap_sRGB;

 /* GL_NV_geometry_program4 */
extern GLboolean GLAD_NV_geometry_program4;
#define GL_GEOMETRY_PROGRAM_NV                 0x8C26
#define GL_MAX_PROGRAM_OUTPUT_VERTICES_NV      0x8C27
#define GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV  0x8C28
typedef void (APIENTRYP pfn_glProgramVertexLimitNV) (GLenum, GLint);
extern pfn_glProgramVertexLimitNV fp_glProgramVertexLimitNV;
typedef void (APIENTRYP pfn_glFramebufferTextureEXT) (GLenum, GLenum, GLuint, GLint);
extern pfn_glFramebufferTextureEXT fp_glFramebufferTextureEXT;
typedef void (APIENTRYP pfn_glFramebufferTextureLayerEXT) (GLenum, GLenum, GLuint, GLint, GLint);
extern pfn_glFramebufferTextureLayerEXT fp_glFramebufferTextureLayerEXT;
typedef void (APIENTRYP pfn_glFramebufferTextureFaceEXT) (GLenum, GLenum, GLuint, GLint, GLenum);
extern pfn_glFramebufferTextureFaceEXT fp_glFramebufferTextureFaceEXT;

 /* GL_NV_geometry_shader4 */
extern GLboolean GLAD_NV_geometry_shader4;

 /* GL_NV_gpu_program4 */
extern GLboolean GLAD_NV_gpu_program4;
#define GL_MIN_PROGRAM_TEXEL_OFFSET_NV         0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET_NV         0x8905
#define GL_PROGRAM_ATTRIB_COMPONENTS_NV        0x8906
#define GL_PROGRAM_RESULT_COMPONENTS_NV        0x8907
#define GL_MAX_PROGRAM_ATTRIB_COMPONENTS_NV    0x8908
#define GL_MAX_PROGRAM_RESULT_COMPONENTS_NV    0x8909
#define GL_MAX_PROGRAM_GENERIC_ATTRIBS_NV      0x8DA5
#define GL_MAX_PROGRAM_GENERIC_RESULTS_NV      0x8DA6
typedef void (APIENTRYP pfn_glProgramLocalParameterI4iNV) (GLenum, GLuint, GLint, GLint, GLint, GLint);
extern pfn_glProgramLocalParameterI4iNV fp_glProgramLocalParameterI4iNV;
typedef void (APIENTRYP pfn_glProgramLocalParameterI4ivNV) (GLenum, GLuint, const GLint*);
extern pfn_glProgramLocalParameterI4ivNV fp_glProgramLocalParameterI4ivNV;
typedef void (APIENTRYP pfn_glProgramLocalParametersI4ivNV) (GLenum, GLuint, GLsizei, const GLint*);
extern pfn_glProgramLocalParametersI4ivNV fp_glProgramLocalParametersI4ivNV;
typedef void (APIENTRYP pfn_glProgramLocalParameterI4uiNV) (GLenum, GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glProgramLocalParameterI4uiNV fp_glProgramLocalParameterI4uiNV;
typedef void (APIENTRYP pfn_glProgramLocalParameterI4uivNV) (GLenum, GLuint, const GLuint*);
extern pfn_glProgramLocalParameterI4uivNV fp_glProgramLocalParameterI4uivNV;
typedef void (APIENTRYP pfn_glProgramLocalParametersI4uivNV) (GLenum, GLuint, GLsizei, const GLuint*);
extern pfn_glProgramLocalParametersI4uivNV fp_glProgramLocalParametersI4uivNV;
typedef void (APIENTRYP pfn_glProgramEnvParameterI4iNV) (GLenum, GLuint, GLint, GLint, GLint, GLint);
extern pfn_glProgramEnvParameterI4iNV fp_glProgramEnvParameterI4iNV;
typedef void (APIENTRYP pfn_glProgramEnvParameterI4ivNV) (GLenum, GLuint, const GLint*);
extern pfn_glProgramEnvParameterI4ivNV fp_glProgramEnvParameterI4ivNV;
typedef void (APIENTRYP pfn_glProgramEnvParametersI4ivNV) (GLenum, GLuint, GLsizei, const GLint*);
extern pfn_glProgramEnvParametersI4ivNV fp_glProgramEnvParametersI4ivNV;
typedef void (APIENTRYP pfn_glProgramEnvParameterI4uiNV) (GLenum, GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glProgramEnvParameterI4uiNV fp_glProgramEnvParameterI4uiNV;
typedef void (APIENTRYP pfn_glProgramEnvParameterI4uivNV) (GLenum, GLuint, const GLuint*);
extern pfn_glProgramEnvParameterI4uivNV fp_glProgramEnvParameterI4uivNV;
typedef void (APIENTRYP pfn_glProgramEnvParametersI4uivNV) (GLenum, GLuint, GLsizei, const GLuint*);
extern pfn_glProgramEnvParametersI4uivNV fp_glProgramEnvParametersI4uivNV;
typedef void (APIENTRYP pfn_glGetProgramLocalParameterIivNV) (GLenum, GLuint, GLint*);
extern pfn_glGetProgramLocalParameterIivNV fp_glGetProgramLocalParameterIivNV;
typedef void (APIENTRYP pfn_glGetProgramLocalParameterIuivNV) (GLenum, GLuint, GLuint*);
extern pfn_glGetProgramLocalParameterIuivNV fp_glGetProgramLocalParameterIuivNV;
typedef void (APIENTRYP pfn_glGetProgramEnvParameterIivNV) (GLenum, GLuint, GLint*);
extern pfn_glGetProgramEnvParameterIivNV fp_glGetProgramEnvParameterIivNV;
typedef void (APIENTRYP pfn_glGetProgramEnvParameterIuivNV) (GLenum, GLuint, GLuint*);
extern pfn_glGetProgramEnvParameterIuivNV fp_glGetProgramEnvParameterIuivNV;

 /* GL_NV_gpu_program5 */
extern GLboolean GLAD_NV_gpu_program5;
#define GL_MAX_GEOMETRY_PROGRAM_INVOCATIONS_NV  0x8E5A
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET_NV  0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET_NV  0x8E5C
#define GL_FRAGMENT_PROGRAM_INTERPOLATION_OFFSET_BITS_NV  0x8E5D
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_NV  0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET_NV  0x8E5F
#define GL_MAX_PROGRAM_SUBROUTINE_PARAMETERS_NV  0x8F44
#define GL_MAX_PROGRAM_SUBROUTINE_NUM_NV       0x8F45
typedef void (APIENTRYP pfn_glProgramSubroutineParametersuivNV) (GLenum, GLsizei, const GLuint*);
extern pfn_glProgramSubroutineParametersuivNV fp_glProgramSubroutineParametersuivNV;
typedef void (APIENTRYP pfn_glGetProgramSubroutineParameteruivNV) (GLenum, GLuint, GLuint*);
extern pfn_glGetProgramSubroutineParameteruivNV fp_glGetProgramSubroutineParameteruivNV;

 /* GL_NV_gpu_program5_mem_extended */
extern GLboolean GLAD_NV_gpu_program5_mem_extended;

 /* GL_NV_gpu_shader5 */
extern GLboolean GLAD_NV_gpu_shader5;
#define GL_INT64_NV                            0x140E
#define GL_UNSIGNED_INT64_NV                   0x140F
#define GL_INT8_NV                             0x8FE0
#define GL_INT8_VEC2_NV                        0x8FE1
#define GL_INT8_VEC3_NV                        0x8FE2
#define GL_INT8_VEC4_NV                        0x8FE3
#define GL_INT16_NV                            0x8FE4
#define GL_INT16_VEC2_NV                       0x8FE5
#define GL_INT16_VEC3_NV                       0x8FE6
#define GL_INT16_VEC4_NV                       0x8FE7
#define GL_INT64_VEC2_NV                       0x8FE9
#define GL_INT64_VEC3_NV                       0x8FEA
#define GL_INT64_VEC4_NV                       0x8FEB
#define GL_UNSIGNED_INT8_NV                    0x8FEC
#define GL_UNSIGNED_INT8_VEC2_NV               0x8FED
#define GL_UNSIGNED_INT8_VEC3_NV               0x8FEE
#define GL_UNSIGNED_INT8_VEC4_NV               0x8FEF
#define GL_UNSIGNED_INT16_NV                   0x8FF0
#define GL_UNSIGNED_INT16_VEC2_NV              0x8FF1
#define GL_UNSIGNED_INT16_VEC3_NV              0x8FF2
#define GL_UNSIGNED_INT16_VEC4_NV              0x8FF3
#define GL_UNSIGNED_INT64_VEC2_NV              0x8FF5
#define GL_UNSIGNED_INT64_VEC3_NV              0x8FF6
#define GL_UNSIGNED_INT64_VEC4_NV              0x8FF7
#define GL_FLOAT16_NV                          0x8FF8
#define GL_FLOAT16_VEC2_NV                     0x8FF9
#define GL_FLOAT16_VEC3_NV                     0x8FFA
#define GL_FLOAT16_VEC4_NV                     0x8FFB
typedef void (APIENTRYP pfn_glUniform1i64NV) (GLint, GLint64EXT);
extern pfn_glUniform1i64NV fp_glUniform1i64NV;
typedef void (APIENTRYP pfn_glUniform2i64NV) (GLint, GLint64EXT, GLint64EXT);
extern pfn_glUniform2i64NV fp_glUniform2i64NV;
typedef void (APIENTRYP pfn_glUniform3i64NV) (GLint, GLint64EXT, GLint64EXT, GLint64EXT);
extern pfn_glUniform3i64NV fp_glUniform3i64NV;
typedef void (APIENTRYP pfn_glUniform4i64NV) (GLint, GLint64EXT, GLint64EXT, GLint64EXT, GLint64EXT);
extern pfn_glUniform4i64NV fp_glUniform4i64NV;
typedef void (APIENTRYP pfn_glUniform1i64vNV) (GLint, GLsizei, const GLint64EXT*);
extern pfn_glUniform1i64vNV fp_glUniform1i64vNV;
typedef void (APIENTRYP pfn_glUniform2i64vNV) (GLint, GLsizei, const GLint64EXT*);
extern pfn_glUniform2i64vNV fp_glUniform2i64vNV;
typedef void (APIENTRYP pfn_glUniform3i64vNV) (GLint, GLsizei, const GLint64EXT*);
extern pfn_glUniform3i64vNV fp_glUniform3i64vNV;
typedef void (APIENTRYP pfn_glUniform4i64vNV) (GLint, GLsizei, const GLint64EXT*);
extern pfn_glUniform4i64vNV fp_glUniform4i64vNV;
typedef void (APIENTRYP pfn_glUniform1ui64NV) (GLint, GLuint64EXT);
extern pfn_glUniform1ui64NV fp_glUniform1ui64NV;
typedef void (APIENTRYP pfn_glUniform2ui64NV) (GLint, GLuint64EXT, GLuint64EXT);
extern pfn_glUniform2ui64NV fp_glUniform2ui64NV;
typedef void (APIENTRYP pfn_glUniform3ui64NV) (GLint, GLuint64EXT, GLuint64EXT, GLuint64EXT);
extern pfn_glUniform3ui64NV fp_glUniform3ui64NV;
typedef void (APIENTRYP pfn_glUniform4ui64NV) (GLint, GLuint64EXT, GLuint64EXT, GLuint64EXT, GLuint64EXT);
extern pfn_glUniform4ui64NV fp_glUniform4ui64NV;
typedef void (APIENTRYP pfn_glUniform1ui64vNV) (GLint, GLsizei, const GLuint64EXT*);
extern pfn_glUniform1ui64vNV fp_glUniform1ui64vNV;
typedef void (APIENTRYP pfn_glUniform2ui64vNV) (GLint, GLsizei, const GLuint64EXT*);
extern pfn_glUniform2ui64vNV fp_glUniform2ui64vNV;
typedef void (APIENTRYP pfn_glUniform3ui64vNV) (GLint, GLsizei, const GLuint64EXT*);
extern pfn_glUniform3ui64vNV fp_glUniform3ui64vNV;
typedef void (APIENTRYP pfn_glUniform4ui64vNV) (GLint, GLsizei, const GLuint64EXT*);
extern pfn_glUniform4ui64vNV fp_glUniform4ui64vNV;
typedef void (APIENTRYP pfn_glGetUniformi64vNV) (GLuint, GLint, GLint64EXT*);
extern pfn_glGetUniformi64vNV fp_glGetUniformi64vNV;
typedef void (APIENTRYP pfn_glProgramUniform1i64NV) (GLuint, GLint, GLint64EXT);
extern pfn_glProgramUniform1i64NV fp_glProgramUniform1i64NV;
typedef void (APIENTRYP pfn_glProgramUniform2i64NV) (GLuint, GLint, GLint64EXT, GLint64EXT);
extern pfn_glProgramUniform2i64NV fp_glProgramUniform2i64NV;
typedef void (APIENTRYP pfn_glProgramUniform3i64NV) (GLuint, GLint, GLint64EXT, GLint64EXT, GLint64EXT);
extern pfn_glProgramUniform3i64NV fp_glProgramUniform3i64NV;
typedef void (APIENTRYP pfn_glProgramUniform4i64NV) (GLuint, GLint, GLint64EXT, GLint64EXT, GLint64EXT, GLint64EXT);
extern pfn_glProgramUniform4i64NV fp_glProgramUniform4i64NV;
typedef void (APIENTRYP pfn_glProgramUniform1i64vNV) (GLuint, GLint, GLsizei, const GLint64EXT*);
extern pfn_glProgramUniform1i64vNV fp_glProgramUniform1i64vNV;
typedef void (APIENTRYP pfn_glProgramUniform2i64vNV) (GLuint, GLint, GLsizei, const GLint64EXT*);
extern pfn_glProgramUniform2i64vNV fp_glProgramUniform2i64vNV;
typedef void (APIENTRYP pfn_glProgramUniform3i64vNV) (GLuint, GLint, GLsizei, const GLint64EXT*);
extern pfn_glProgramUniform3i64vNV fp_glProgramUniform3i64vNV;
typedef void (APIENTRYP pfn_glProgramUniform4i64vNV) (GLuint, GLint, GLsizei, const GLint64EXT*);
extern pfn_glProgramUniform4i64vNV fp_glProgramUniform4i64vNV;
typedef void (APIENTRYP pfn_glProgramUniform1ui64NV) (GLuint, GLint, GLuint64EXT);
extern pfn_glProgramUniform1ui64NV fp_glProgramUniform1ui64NV;
typedef void (APIENTRYP pfn_glProgramUniform2ui64NV) (GLuint, GLint, GLuint64EXT, GLuint64EXT);
extern pfn_glProgramUniform2ui64NV fp_glProgramUniform2ui64NV;
typedef void (APIENTRYP pfn_glProgramUniform3ui64NV) (GLuint, GLint, GLuint64EXT, GLuint64EXT, GLuint64EXT);
extern pfn_glProgramUniform3ui64NV fp_glProgramUniform3ui64NV;
typedef void (APIENTRYP pfn_glProgramUniform4ui64NV) (GLuint, GLint, GLuint64EXT, GLuint64EXT, GLuint64EXT, GLuint64EXT);
extern pfn_glProgramUniform4ui64NV fp_glProgramUniform4ui64NV;
typedef void (APIENTRYP pfn_glProgramUniform1ui64vNV) (GLuint, GLint, GLsizei, const GLuint64EXT*);
extern pfn_glProgramUniform1ui64vNV fp_glProgramUniform1ui64vNV;
typedef void (APIENTRYP pfn_glProgramUniform2ui64vNV) (GLuint, GLint, GLsizei, const GLuint64EXT*);
extern pfn_glProgramUniform2ui64vNV fp_glProgramUniform2ui64vNV;
typedef void (APIENTRYP pfn_glProgramUniform3ui64vNV) (GLuint, GLint, GLsizei, const GLuint64EXT*);
extern pfn_glProgramUniform3ui64vNV fp_glProgramUniform3ui64vNV;
typedef void (APIENTRYP pfn_glProgramUniform4ui64vNV) (GLuint, GLint, GLsizei, const GLuint64EXT*);
extern pfn_glProgramUniform4ui64vNV fp_glProgramUniform4ui64vNV;

 /* GL_NV_half_float */
extern GLboolean GLAD_NV_half_float;
#define GL_HALF_FLOAT_NV                       0x140B
typedef void (APIENTRYP pfn_glVertex2hNV) (GLhalfNV, GLhalfNV);
extern pfn_glVertex2hNV fp_glVertex2hNV;
typedef void (APIENTRYP pfn_glVertex2hvNV) (const GLhalfNV*);
extern pfn_glVertex2hvNV fp_glVertex2hvNV;
typedef void (APIENTRYP pfn_glVertex3hNV) (GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glVertex3hNV fp_glVertex3hNV;
typedef void (APIENTRYP pfn_glVertex3hvNV) (const GLhalfNV*);
extern pfn_glVertex3hvNV fp_glVertex3hvNV;
typedef void (APIENTRYP pfn_glVertex4hNV) (GLhalfNV, GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glVertex4hNV fp_glVertex4hNV;
typedef void (APIENTRYP pfn_glVertex4hvNV) (const GLhalfNV*);
extern pfn_glVertex4hvNV fp_glVertex4hvNV;
typedef void (APIENTRYP pfn_glNormal3hNV) (GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glNormal3hNV fp_glNormal3hNV;
typedef void (APIENTRYP pfn_glNormal3hvNV) (const GLhalfNV*);
extern pfn_glNormal3hvNV fp_glNormal3hvNV;
typedef void (APIENTRYP pfn_glColor3hNV) (GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glColor3hNV fp_glColor3hNV;
typedef void (APIENTRYP pfn_glColor3hvNV) (const GLhalfNV*);
extern pfn_glColor3hvNV fp_glColor3hvNV;
typedef void (APIENTRYP pfn_glColor4hNV) (GLhalfNV, GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glColor4hNV fp_glColor4hNV;
typedef void (APIENTRYP pfn_glColor4hvNV) (const GLhalfNV*);
extern pfn_glColor4hvNV fp_glColor4hvNV;
typedef void (APIENTRYP pfn_glTexCoord1hNV) (GLhalfNV);
extern pfn_glTexCoord1hNV fp_glTexCoord1hNV;
typedef void (APIENTRYP pfn_glTexCoord1hvNV) (const GLhalfNV*);
extern pfn_glTexCoord1hvNV fp_glTexCoord1hvNV;
typedef void (APIENTRYP pfn_glTexCoord2hNV) (GLhalfNV, GLhalfNV);
extern pfn_glTexCoord2hNV fp_glTexCoord2hNV;
typedef void (APIENTRYP pfn_glTexCoord2hvNV) (const GLhalfNV*);
extern pfn_glTexCoord2hvNV fp_glTexCoord2hvNV;
typedef void (APIENTRYP pfn_glTexCoord3hNV) (GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glTexCoord3hNV fp_glTexCoord3hNV;
typedef void (APIENTRYP pfn_glTexCoord3hvNV) (const GLhalfNV*);
extern pfn_glTexCoord3hvNV fp_glTexCoord3hvNV;
typedef void (APIENTRYP pfn_glTexCoord4hNV) (GLhalfNV, GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glTexCoord4hNV fp_glTexCoord4hNV;
typedef void (APIENTRYP pfn_glTexCoord4hvNV) (const GLhalfNV*);
extern pfn_glTexCoord4hvNV fp_glTexCoord4hvNV;
typedef void (APIENTRYP pfn_glMultiTexCoord1hNV) (GLenum, GLhalfNV);
extern pfn_glMultiTexCoord1hNV fp_glMultiTexCoord1hNV;
typedef void (APIENTRYP pfn_glMultiTexCoord1hvNV) (GLenum, const GLhalfNV*);
extern pfn_glMultiTexCoord1hvNV fp_glMultiTexCoord1hvNV;
typedef void (APIENTRYP pfn_glMultiTexCoord2hNV) (GLenum, GLhalfNV, GLhalfNV);
extern pfn_glMultiTexCoord2hNV fp_glMultiTexCoord2hNV;
typedef void (APIENTRYP pfn_glMultiTexCoord2hvNV) (GLenum, const GLhalfNV*);
extern pfn_glMultiTexCoord2hvNV fp_glMultiTexCoord2hvNV;
typedef void (APIENTRYP pfn_glMultiTexCoord3hNV) (GLenum, GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glMultiTexCoord3hNV fp_glMultiTexCoord3hNV;
typedef void (APIENTRYP pfn_glMultiTexCoord3hvNV) (GLenum, const GLhalfNV*);
extern pfn_glMultiTexCoord3hvNV fp_glMultiTexCoord3hvNV;
typedef void (APIENTRYP pfn_glMultiTexCoord4hNV) (GLenum, GLhalfNV, GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glMultiTexCoord4hNV fp_glMultiTexCoord4hNV;
typedef void (APIENTRYP pfn_glMultiTexCoord4hvNV) (GLenum, const GLhalfNV*);
extern pfn_glMultiTexCoord4hvNV fp_glMultiTexCoord4hvNV;
typedef void (APIENTRYP pfn_glFogCoordhNV) (GLhalfNV);
extern pfn_glFogCoordhNV fp_glFogCoordhNV;
typedef void (APIENTRYP pfn_glFogCoordhvNV) (const GLhalfNV*);
extern pfn_glFogCoordhvNV fp_glFogCoordhvNV;
typedef void (APIENTRYP pfn_glSecondaryColor3hNV) (GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glSecondaryColor3hNV fp_glSecondaryColor3hNV;
typedef void (APIENTRYP pfn_glSecondaryColor3hvNV) (const GLhalfNV*);
extern pfn_glSecondaryColor3hvNV fp_glSecondaryColor3hvNV;
typedef void (APIENTRYP pfn_glVertexWeighthNV) (GLhalfNV);
extern pfn_glVertexWeighthNV fp_glVertexWeighthNV;
typedef void (APIENTRYP pfn_glVertexWeighthvNV) (const GLhalfNV*);
extern pfn_glVertexWeighthvNV fp_glVertexWeighthvNV;
typedef void (APIENTRYP pfn_glVertexAttrib1hNV) (GLuint, GLhalfNV);
extern pfn_glVertexAttrib1hNV fp_glVertexAttrib1hNV;
typedef void (APIENTRYP pfn_glVertexAttrib1hvNV) (GLuint, const GLhalfNV*);
extern pfn_glVertexAttrib1hvNV fp_glVertexAttrib1hvNV;
typedef void (APIENTRYP pfn_glVertexAttrib2hNV) (GLuint, GLhalfNV, GLhalfNV);
extern pfn_glVertexAttrib2hNV fp_glVertexAttrib2hNV;
typedef void (APIENTRYP pfn_glVertexAttrib2hvNV) (GLuint, const GLhalfNV*);
extern pfn_glVertexAttrib2hvNV fp_glVertexAttrib2hvNV;
typedef void (APIENTRYP pfn_glVertexAttrib3hNV) (GLuint, GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glVertexAttrib3hNV fp_glVertexAttrib3hNV;
typedef void (APIENTRYP pfn_glVertexAttrib3hvNV) (GLuint, const GLhalfNV*);
extern pfn_glVertexAttrib3hvNV fp_glVertexAttrib3hvNV;
typedef void (APIENTRYP pfn_glVertexAttrib4hNV) (GLuint, GLhalfNV, GLhalfNV, GLhalfNV, GLhalfNV);
extern pfn_glVertexAttrib4hNV fp_glVertexAttrib4hNV;
typedef void (APIENTRYP pfn_glVertexAttrib4hvNV) (GLuint, const GLhalfNV*);
extern pfn_glVertexAttrib4hvNV fp_glVertexAttrib4hvNV;
typedef void (APIENTRYP pfn_glVertexAttribs1hvNV) (GLuint, GLsizei, const GLhalfNV*);
extern pfn_glVertexAttribs1hvNV fp_glVertexAttribs1hvNV;
typedef void (APIENTRYP pfn_glVertexAttribs2hvNV) (GLuint, GLsizei, const GLhalfNV*);
extern pfn_glVertexAttribs2hvNV fp_glVertexAttribs2hvNV;
typedef void (APIENTRYP pfn_glVertexAttribs3hvNV) (GLuint, GLsizei, const GLhalfNV*);
extern pfn_glVertexAttribs3hvNV fp_glVertexAttribs3hvNV;
typedef void (APIENTRYP pfn_glVertexAttribs4hvNV) (GLuint, GLsizei, const GLhalfNV*);
extern pfn_glVertexAttribs4hvNV fp_glVertexAttribs4hvNV;

 /* GL_NV_instanced_arrays */
extern GLboolean GLAD_NV_instanced_arrays;
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_NV      0x88FE
typedef void (APIENTRYP pfn_glVertexAttribDivisorNV) (GLuint, GLuint);
extern pfn_glVertexAttribDivisorNV fp_glVertexAttribDivisorNV;

 /* GL_NV_light_max_exponent */
extern GLboolean GLAD_NV_light_max_exponent;
#define GL_MAX_SHININESS_NV                    0x8504
#define GL_MAX_SPOT_EXPONENT_NV                0x8505

 /* GL_NV_multisample_coverage */
extern GLboolean GLAD_NV_multisample_coverage;
#define GL_COLOR_SAMPLES_NV                    0x8E20

 /* GL_NV_multisample_filter_hint */
extern GLboolean GLAD_NV_multisample_filter_hint;
#define GL_MULTISAMPLE_FILTER_HINT_NV          0x8534

 /* GL_NV_non_square_matrices */
extern GLboolean GLAD_NV_non_square_matrices;
#define GL_FLOAT_MAT2x3_NV                     0x8B65
#define GL_FLOAT_MAT2x4_NV                     0x8B66
#define GL_FLOAT_MAT3x2_NV                     0x8B67
#define GL_FLOAT_MAT3x4_NV                     0x8B68
#define GL_FLOAT_MAT4x2_NV                     0x8B69
#define GL_FLOAT_MAT4x3_NV                     0x8B6A
typedef void (APIENTRYP pfn_glUniformMatrix2x3fvNV) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix2x3fvNV fp_glUniformMatrix2x3fvNV;
typedef void (APIENTRYP pfn_glUniformMatrix3x2fvNV) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix3x2fvNV fp_glUniformMatrix3x2fvNV;
typedef void (APIENTRYP pfn_glUniformMatrix2x4fvNV) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix2x4fvNV fp_glUniformMatrix2x4fvNV;
typedef void (APIENTRYP pfn_glUniformMatrix4x2fvNV) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix4x2fvNV fp_glUniformMatrix4x2fvNV;
typedef void (APIENTRYP pfn_glUniformMatrix3x4fvNV) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix3x4fvNV fp_glUniformMatrix3x4fvNV;
typedef void (APIENTRYP pfn_glUniformMatrix4x3fvNV) (GLint, GLsizei, GLboolean, const GLfloat*);
extern pfn_glUniformMatrix4x3fvNV fp_glUniformMatrix4x3fvNV;

 /* GL_NV_occlusion_query */
extern GLboolean GLAD_NV_occlusion_query;
#define GL_PIXEL_COUNTER_BITS_NV               0x8864
#define GL_CURRENT_OCCLUSION_QUERY_ID_NV       0x8865
#define GL_PIXEL_COUNT_NV                      0x8866
#define GL_PIXEL_COUNT_AVAILABLE_NV            0x8867
typedef void (APIENTRYP pfn_glGenOcclusionQueriesNV) (GLsizei, GLuint*);
extern pfn_glGenOcclusionQueriesNV fp_glGenOcclusionQueriesNV;
typedef void (APIENTRYP pfn_glDeleteOcclusionQueriesNV) (GLsizei, const GLuint*);
extern pfn_glDeleteOcclusionQueriesNV fp_glDeleteOcclusionQueriesNV;
typedef GLboolean (APIENTRYP pfn_glIsOcclusionQueryNV) (GLuint);
extern pfn_glIsOcclusionQueryNV fp_glIsOcclusionQueryNV;
typedef void (APIENTRYP pfn_glBeginOcclusionQueryNV) (GLuint);
extern pfn_glBeginOcclusionQueryNV fp_glBeginOcclusionQueryNV;
typedef void (APIENTRYP pfn_glEndOcclusionQueryNV) ();
extern pfn_glEndOcclusionQueryNV fp_glEndOcclusionQueryNV;
typedef void (APIENTRYP pfn_glGetOcclusionQueryivNV) (GLuint, GLenum, GLint*);
extern pfn_glGetOcclusionQueryivNV fp_glGetOcclusionQueryivNV;
typedef void (APIENTRYP pfn_glGetOcclusionQueryuivNV) (GLuint, GLenum, GLuint*);
extern pfn_glGetOcclusionQueryuivNV fp_glGetOcclusionQueryuivNV;

 /* GL_NV_packed_depth_stencil */
extern GLboolean GLAD_NV_packed_depth_stencil;
#define GL_DEPTH_STENCIL_NV                    0x84F9
#define GL_UNSIGNED_INT_24_8_NV                0x84FA

 /* GL_NV_parameter_buffer_object */
extern GLboolean GLAD_NV_parameter_buffer_object;
#define GL_MAX_PROGRAM_PARAMETER_BUFFER_BINDINGS_NV  0x8DA0
#define GL_MAX_PROGRAM_PARAMETER_BUFFER_SIZE_NV  0x8DA1
#define GL_VERTEX_PROGRAM_PARAMETER_BUFFER_NV  0x8DA2
#define GL_GEOMETRY_PROGRAM_PARAMETER_BUFFER_NV  0x8DA3
#define GL_FRAGMENT_PROGRAM_PARAMETER_BUFFER_NV  0x8DA4
typedef void (APIENTRYP pfn_glProgramBufferParametersfvNV) (GLenum, GLuint, GLuint, GLsizei, const GLfloat*);
extern pfn_glProgramBufferParametersfvNV fp_glProgramBufferParametersfvNV;
typedef void (APIENTRYP pfn_glProgramBufferParametersIivNV) (GLenum, GLuint, GLuint, GLsizei, const GLint*);
extern pfn_glProgramBufferParametersIivNV fp_glProgramBufferParametersIivNV;
typedef void (APIENTRYP pfn_glProgramBufferParametersIuivNV) (GLenum, GLuint, GLuint, GLsizei, const GLuint*);
extern pfn_glProgramBufferParametersIuivNV fp_glProgramBufferParametersIuivNV;

 /* GL_NV_parameter_buffer_object2 */
extern GLboolean GLAD_NV_parameter_buffer_object2;

 /* GL_NV_path_rendering */
extern GLboolean GLAD_NV_path_rendering;
#define GL_PATH_FORMAT_SVG_NV                  0x9070
#define GL_PATH_FORMAT_PS_NV                   0x9071
#define GL_STANDARD_FONT_NAME_NV               0x9072
#define GL_SYSTEM_FONT_NAME_NV                 0x9073
#define GL_FILE_NAME_NV                        0x9074
#define GL_PATH_STROKE_WIDTH_NV                0x9075
#define GL_PATH_END_CAPS_NV                    0x9076
#define GL_PATH_INITIAL_END_CAP_NV             0x9077
#define GL_PATH_TERMINAL_END_CAP_NV            0x9078
#define GL_PATH_JOIN_STYLE_NV                  0x9079
#define GL_PATH_MITER_LIMIT_NV                 0x907A
#define GL_PATH_DASH_CAPS_NV                   0x907B
#define GL_PATH_INITIAL_DASH_CAP_NV            0x907C
#define GL_PATH_TERMINAL_DASH_CAP_NV           0x907D
#define GL_PATH_DASH_OFFSET_NV                 0x907E
#define GL_PATH_CLIENT_LENGTH_NV               0x907F
#define GL_PATH_FILL_MODE_NV                   0x9080
#define GL_PATH_FILL_MASK_NV                   0x9081
#define GL_PATH_FILL_COVER_MODE_NV             0x9082
#define GL_PATH_STROKE_COVER_MODE_NV           0x9083
#define GL_PATH_STROKE_MASK_NV                 0x9084
#define GL_COUNT_UP_NV                         0x9088
#define GL_COUNT_DOWN_NV                       0x9089
#define GL_PATH_OBJECT_BOUNDING_BOX_NV         0x908A
#define GL_CONVEX_HULL_NV                      0x908B
#define GL_BOUNDING_BOX_NV                     0x908D
#define GL_TRANSLATE_X_NV                      0x908E
#define GL_TRANSLATE_Y_NV                      0x908F
#define GL_TRANSLATE_2D_NV                     0x9090
#define GL_TRANSLATE_3D_NV                     0x9091
#define GL_AFFINE_2D_NV                        0x9092
#define GL_AFFINE_3D_NV                        0x9094
#define GL_TRANSPOSE_AFFINE_2D_NV              0x9096
#define GL_TRANSPOSE_AFFINE_3D_NV              0x9098
#define GL_UTF8_NV                             0x909A
#define GL_UTF16_NV                            0x909B
#define GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV   0x909C
#define GL_PATH_COMMAND_COUNT_NV               0x909D
#define GL_PATH_COORD_COUNT_NV                 0x909E
#define GL_PATH_DASH_ARRAY_COUNT_NV            0x909F
#define GL_PATH_COMPUTED_LENGTH_NV             0x90A0
#define GL_PATH_FILL_BOUNDING_BOX_NV           0x90A1
#define GL_PATH_STROKE_BOUNDING_BOX_NV         0x90A2
#define GL_SQUARE_NV                           0x90A3
#define GL_ROUND_NV                            0x90A4
#define GL_TRIANGULAR_NV                       0x90A5
#define GL_BEVEL_NV                            0x90A6
#define GL_MITER_REVERT_NV                     0x90A7
#define GL_MITER_TRUNCATE_NV                   0x90A8
#define GL_SKIP_MISSING_GLYPH_NV               0x90A9
#define GL_USE_MISSING_GLYPH_NV                0x90AA
#define GL_PATH_ERROR_POSITION_NV              0x90AB
#define GL_PATH_FOG_GEN_MODE_NV                0x90AC
#define GL_ACCUM_ADJACENT_PAIRS_NV             0x90AD
#define GL_ADJACENT_PAIRS_NV                   0x90AE
#define GL_FIRST_TO_REST_NV                    0x90AF
#define GL_PATH_GEN_MODE_NV                    0x90B0
#define GL_PATH_GEN_COEFF_NV                   0x90B1
#define GL_PATH_GEN_COLOR_FORMAT_NV            0x90B2
#define GL_PATH_GEN_COMPONENTS_NV              0x90B3
#define GL_PATH_STENCIL_FUNC_NV                0x90B7
#define GL_PATH_STENCIL_REF_NV                 0x90B8
#define GL_PATH_STENCIL_VALUE_MASK_NV          0x90B9
#define GL_PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV  0x90BD
#define GL_PATH_STENCIL_DEPTH_OFFSET_UNITS_NV  0x90BE
#define GL_PATH_COVER_DEPTH_FUNC_NV            0x90BF
#define GL_PATH_DASH_OFFSET_RESET_NV           0x90B4
#define GL_MOVE_TO_RESETS_NV                   0x90B5
#define GL_MOVE_TO_CONTINUES_NV                0x90B6
#define GL_CLOSE_PATH_NV                       0x00
#define GL_MOVE_TO_NV                          0x02
#define GL_RELATIVE_MOVE_TO_NV                 0x03
#define GL_LINE_TO_NV                          0x04
#define GL_RELATIVE_LINE_TO_NV                 0x05
#define GL_HORIZONTAL_LINE_TO_NV               0x06
#define GL_RELATIVE_HORIZONTAL_LINE_TO_NV      0x07
#define GL_VERTICAL_LINE_TO_NV                 0x08
#define GL_RELATIVE_VERTICAL_LINE_TO_NV        0x09
#define GL_QUADRATIC_CURVE_TO_NV               0x0A
#define GL_RELATIVE_QUADRATIC_CURVE_TO_NV      0x0B
#define GL_CUBIC_CURVE_TO_NV                   0x0C
#define GL_RELATIVE_CUBIC_CURVE_TO_NV          0x0D
#define GL_SMOOTH_QUADRATIC_CURVE_TO_NV        0x0E
#define GL_RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV  0x0F
#define GL_SMOOTH_CUBIC_CURVE_TO_NV            0x10
#define GL_RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV   0x11
#define GL_SMALL_CCW_ARC_TO_NV                 0x12
#define GL_RELATIVE_SMALL_CCW_ARC_TO_NV        0x13
#define GL_SMALL_CW_ARC_TO_NV                  0x14
#define GL_RELATIVE_SMALL_CW_ARC_TO_NV         0x15
#define GL_LARGE_CCW_ARC_TO_NV                 0x16
#define GL_RELATIVE_LARGE_CCW_ARC_TO_NV        0x17
#define GL_LARGE_CW_ARC_TO_NV                  0x18
#define GL_RELATIVE_LARGE_CW_ARC_TO_NV         0x19
#define GL_RESTART_PATH_NV                     0xF0
#define GL_DUP_FIRST_CUBIC_CURVE_TO_NV         0xF2
#define GL_DUP_LAST_CUBIC_CURVE_TO_NV          0xF4
#define GL_RECT_NV                             0xF6
#define GL_CIRCULAR_CCW_ARC_TO_NV              0xF8
#define GL_CIRCULAR_CW_ARC_TO_NV               0xFA
#define GL_CIRCULAR_TANGENT_ARC_TO_NV          0xFC
#define GL_ARC_TO_NV                           0xFE
#define GL_RELATIVE_ARC_TO_NV                  0xFF
#define GL_BOLD_BIT_NV                         0x01
#define GL_ITALIC_BIT_NV                       0x02
#define GL_GLYPH_WIDTH_BIT_NV                  0x01
#define GL_GLYPH_HEIGHT_BIT_NV                 0x02
#define GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV   0x04
#define GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV   0x08
#define GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV  0x10
#define GL_GLYPH_VERTICAL_BEARING_X_BIT_NV     0x20
#define GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV     0x40
#define GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV  0x80
#define GL_GLYPH_HAS_KERNING_BIT_NV            0x100
#define GL_FONT_X_MIN_BOUNDS_BIT_NV            0x00010000
#define GL_FONT_Y_MIN_BOUNDS_BIT_NV            0x00020000
#define GL_FONT_X_MAX_BOUNDS_BIT_NV            0x00040000
#define GL_FONT_Y_MAX_BOUNDS_BIT_NV            0x00080000
#define GL_FONT_UNITS_PER_EM_BIT_NV            0x00100000
#define GL_FONT_ASCENDER_BIT_NV                0x00200000
#define GL_FONT_DESCENDER_BIT_NV               0x00400000
#define GL_FONT_HEIGHT_BIT_NV                  0x00800000
#define GL_FONT_MAX_ADVANCE_WIDTH_BIT_NV       0x01000000
#define GL_FONT_MAX_ADVANCE_HEIGHT_BIT_NV      0x02000000
#define GL_FONT_UNDERLINE_POSITION_BIT_NV      0x04000000
#define GL_FONT_UNDERLINE_THICKNESS_BIT_NV     0x08000000
#define GL_FONT_HAS_KERNING_BIT_NV             0x10000000
#define GL_PRIMARY_COLOR_NV                    0x852C
#define GL_SECONDARY_COLOR_NV                  0x852D
typedef GLuint (APIENTRYP pfn_glGenPathsNV) (GLsizei);
extern pfn_glGenPathsNV fp_glGenPathsNV;
typedef void (APIENTRYP pfn_glDeletePathsNV) (GLuint, GLsizei);
extern pfn_glDeletePathsNV fp_glDeletePathsNV;
typedef GLboolean (APIENTRYP pfn_glIsPathNV) (GLuint);
extern pfn_glIsPathNV fp_glIsPathNV;
typedef void (APIENTRYP pfn_glPathCommandsNV) (GLuint, GLsizei, const GLubyte*, GLsizei, GLenum, const void*);
extern pfn_glPathCommandsNV fp_glPathCommandsNV;
typedef void (APIENTRYP pfn_glPathCoordsNV) (GLuint, GLsizei, GLenum, const void*);
extern pfn_glPathCoordsNV fp_glPathCoordsNV;
typedef void (APIENTRYP pfn_glPathSubCommandsNV) (GLuint, GLsizei, GLsizei, GLsizei, const GLubyte*, GLsizei, GLenum, const void*);
extern pfn_glPathSubCommandsNV fp_glPathSubCommandsNV;
typedef void (APIENTRYP pfn_glPathSubCoordsNV) (GLuint, GLsizei, GLsizei, GLenum, const void*);
extern pfn_glPathSubCoordsNV fp_glPathSubCoordsNV;
typedef void (APIENTRYP pfn_glPathStringNV) (GLuint, GLenum, GLsizei, const void*);
extern pfn_glPathStringNV fp_glPathStringNV;
typedef void (APIENTRYP pfn_glPathGlyphsNV) (GLuint, GLenum, const void*, GLbitfield, GLsizei, GLenum, const void*, GLenum, GLuint, GLfloat);
extern pfn_glPathGlyphsNV fp_glPathGlyphsNV;
typedef void (APIENTRYP pfn_glPathGlyphRangeNV) (GLuint, GLenum, const void*, GLbitfield, GLuint, GLsizei, GLenum, GLuint, GLfloat);
extern pfn_glPathGlyphRangeNV fp_glPathGlyphRangeNV;
typedef void (APIENTRYP pfn_glWeightPathsNV) (GLuint, GLsizei, const GLuint*, const GLfloat*);
extern pfn_glWeightPathsNV fp_glWeightPathsNV;
typedef void (APIENTRYP pfn_glCopyPathNV) (GLuint, GLuint);
extern pfn_glCopyPathNV fp_glCopyPathNV;
typedef void (APIENTRYP pfn_glInterpolatePathsNV) (GLuint, GLuint, GLuint, GLfloat);
extern pfn_glInterpolatePathsNV fp_glInterpolatePathsNV;
typedef void (APIENTRYP pfn_glTransformPathNV) (GLuint, GLuint, GLenum, const GLfloat*);
extern pfn_glTransformPathNV fp_glTransformPathNV;
typedef void (APIENTRYP pfn_glPathParameterivNV) (GLuint, GLenum, const GLint*);
extern pfn_glPathParameterivNV fp_glPathParameterivNV;
typedef void (APIENTRYP pfn_glPathParameteriNV) (GLuint, GLenum, GLint);
extern pfn_glPathParameteriNV fp_glPathParameteriNV;
typedef void (APIENTRYP pfn_glPathParameterfvNV) (GLuint, GLenum, const GLfloat*);
extern pfn_glPathParameterfvNV fp_glPathParameterfvNV;
typedef void (APIENTRYP pfn_glPathParameterfNV) (GLuint, GLenum, GLfloat);
extern pfn_glPathParameterfNV fp_glPathParameterfNV;
typedef void (APIENTRYP pfn_glPathDashArrayNV) (GLuint, GLsizei, const GLfloat*);
extern pfn_glPathDashArrayNV fp_glPathDashArrayNV;
typedef void (APIENTRYP pfn_glPathStencilFuncNV) (GLenum, GLint, GLuint);
extern pfn_glPathStencilFuncNV fp_glPathStencilFuncNV;
typedef void (APIENTRYP pfn_glPathStencilDepthOffsetNV) (GLfloat, GLfloat);
extern pfn_glPathStencilDepthOffsetNV fp_glPathStencilDepthOffsetNV;
typedef void (APIENTRYP pfn_glStencilFillPathNV) (GLuint, GLenum, GLuint);
extern pfn_glStencilFillPathNV fp_glStencilFillPathNV;
typedef void (APIENTRYP pfn_glStencilStrokePathNV) (GLuint, GLint, GLuint);
extern pfn_glStencilStrokePathNV fp_glStencilStrokePathNV;
typedef void (APIENTRYP pfn_glStencilFillPathInstancedNV) (GLsizei, GLenum, const void*, GLuint, GLenum, GLuint, GLenum, const GLfloat*);
extern pfn_glStencilFillPathInstancedNV fp_glStencilFillPathInstancedNV;
typedef void (APIENTRYP pfn_glStencilStrokePathInstancedNV) (GLsizei, GLenum, const void*, GLuint, GLint, GLuint, GLenum, const GLfloat*);
extern pfn_glStencilStrokePathInstancedNV fp_glStencilStrokePathInstancedNV;
typedef void (APIENTRYP pfn_glPathCoverDepthFuncNV) (GLenum);
extern pfn_glPathCoverDepthFuncNV fp_glPathCoverDepthFuncNV;
typedef void (APIENTRYP pfn_glPathColorGenNV) (GLenum, GLenum, GLenum, const GLfloat*);
extern pfn_glPathColorGenNV fp_glPathColorGenNV;
typedef void (APIENTRYP pfn_glPathTexGenNV) (GLenum, GLenum, GLint, const GLfloat*);
extern pfn_glPathTexGenNV fp_glPathTexGenNV;
typedef void (APIENTRYP pfn_glPathFogGenNV) (GLenum);
extern pfn_glPathFogGenNV fp_glPathFogGenNV;
typedef void (APIENTRYP pfn_glCoverFillPathNV) (GLuint, GLenum);
extern pfn_glCoverFillPathNV fp_glCoverFillPathNV;
typedef void (APIENTRYP pfn_glCoverStrokePathNV) (GLuint, GLenum);
extern pfn_glCoverStrokePathNV fp_glCoverStrokePathNV;
typedef void (APIENTRYP pfn_glCoverFillPathInstancedNV) (GLsizei, GLenum, const void*, GLuint, GLenum, GLenum, const GLfloat*);
extern pfn_glCoverFillPathInstancedNV fp_glCoverFillPathInstancedNV;
typedef void (APIENTRYP pfn_glCoverStrokePathInstancedNV) (GLsizei, GLenum, const void*, GLuint, GLenum, GLenum, const GLfloat*);
extern pfn_glCoverStrokePathInstancedNV fp_glCoverStrokePathInstancedNV;
typedef void (APIENTRYP pfn_glGetPathParameterivNV) (GLuint, GLenum, GLint*);
extern pfn_glGetPathParameterivNV fp_glGetPathParameterivNV;
typedef void (APIENTRYP pfn_glGetPathParameterfvNV) (GLuint, GLenum, GLfloat*);
extern pfn_glGetPathParameterfvNV fp_glGetPathParameterfvNV;
typedef void (APIENTRYP pfn_glGetPathCommandsNV) (GLuint, GLubyte*);
extern pfn_glGetPathCommandsNV fp_glGetPathCommandsNV;
typedef void (APIENTRYP pfn_glGetPathCoordsNV) (GLuint, GLfloat*);
extern pfn_glGetPathCoordsNV fp_glGetPathCoordsNV;
typedef void (APIENTRYP pfn_glGetPathDashArrayNV) (GLuint, GLfloat*);
extern pfn_glGetPathDashArrayNV fp_glGetPathDashArrayNV;
typedef void (APIENTRYP pfn_glGetPathMetricsNV) (GLbitfield, GLsizei, GLenum, const void*, GLuint, GLsizei, GLfloat*);
extern pfn_glGetPathMetricsNV fp_glGetPathMetricsNV;
typedef void (APIENTRYP pfn_glGetPathMetricRangeNV) (GLbitfield, GLuint, GLsizei, GLsizei, GLfloat*);
extern pfn_glGetPathMetricRangeNV fp_glGetPathMetricRangeNV;
typedef void (APIENTRYP pfn_glGetPathSpacingNV) (GLenum, GLsizei, GLenum, const void*, GLuint, GLfloat, GLfloat, GLenum, GLfloat*);
extern pfn_glGetPathSpacingNV fp_glGetPathSpacingNV;
typedef void (APIENTRYP pfn_glGetPathColorGenivNV) (GLenum, GLenum, GLint*);
extern pfn_glGetPathColorGenivNV fp_glGetPathColorGenivNV;
typedef void (APIENTRYP pfn_glGetPathColorGenfvNV) (GLenum, GLenum, GLfloat*);
extern pfn_glGetPathColorGenfvNV fp_glGetPathColorGenfvNV;
typedef void (APIENTRYP pfn_glGetPathTexGenivNV) (GLenum, GLenum, GLint*);
extern pfn_glGetPathTexGenivNV fp_glGetPathTexGenivNV;
typedef void (APIENTRYP pfn_glGetPathTexGenfvNV) (GLenum, GLenum, GLfloat*);
extern pfn_glGetPathTexGenfvNV fp_glGetPathTexGenfvNV;
typedef GLboolean (APIENTRYP pfn_glIsPointInFillPathNV) (GLuint, GLuint, GLfloat, GLfloat);
extern pfn_glIsPointInFillPathNV fp_glIsPointInFillPathNV;
typedef GLboolean (APIENTRYP pfn_glIsPointInStrokePathNV) (GLuint, GLfloat, GLfloat);
extern pfn_glIsPointInStrokePathNV fp_glIsPointInStrokePathNV;
typedef GLfloat (APIENTRYP pfn_glGetPathLengthNV) (GLuint, GLsizei, GLsizei);
extern pfn_glGetPathLengthNV fp_glGetPathLengthNV;
typedef GLboolean (APIENTRYP pfn_glPointAlongPathNV) (GLuint, GLsizei, GLsizei, GLfloat, GLfloat*, GLfloat*, GLfloat*, GLfloat*);
extern pfn_glPointAlongPathNV fp_glPointAlongPathNV;

 /* GL_NV_pixel_data_range */
extern GLboolean GLAD_NV_pixel_data_range;
#define GL_WRITE_PIXEL_DATA_RANGE_NV           0x8878
#define GL_READ_PIXEL_DATA_RANGE_NV            0x8879
#define GL_WRITE_PIXEL_DATA_RANGE_LENGTH_NV    0x887A
#define GL_READ_PIXEL_DATA_RANGE_LENGTH_NV     0x887B
#define GL_WRITE_PIXEL_DATA_RANGE_POINTER_NV   0x887C
#define GL_READ_PIXEL_DATA_RANGE_POINTER_NV    0x887D
typedef void (APIENTRYP pfn_glPixelDataRangeNV) (GLenum, GLsizei, const void*);
extern pfn_glPixelDataRangeNV fp_glPixelDataRangeNV;
typedef void (APIENTRYP pfn_glFlushPixelDataRangeNV) (GLenum);
extern pfn_glFlushPixelDataRangeNV fp_glFlushPixelDataRangeNV;

 /* GL_NV_point_sprite */
extern GLboolean GLAD_NV_point_sprite;
#define GL_POINT_SPRITE_NV                     0x8861
#define GL_COORD_REPLACE_NV                    0x8862
#define GL_POINT_SPRITE_R_MODE_NV              0x8863
typedef void (APIENTRYP pfn_glPointParameteriNV) (GLenum, GLint);
extern pfn_glPointParameteriNV fp_glPointParameteriNV;
typedef void (APIENTRYP pfn_glPointParameterivNV) (GLenum, const GLint*);
extern pfn_glPointParameterivNV fp_glPointParameterivNV;

 /* GL_NV_present_video */
extern GLboolean GLAD_NV_present_video;
#define GL_FRAME_NV                            0x8E26
#define GL_FIELDS_NV                           0x8E27
#define GL_CURRENT_TIME_NV                     0x8E28
#define GL_NUM_FILL_STREAMS_NV                 0x8E29
#define GL_PRESENT_TIME_NV                     0x8E2A
#define GL_PRESENT_DURATION_NV                 0x8E2B
typedef void (APIENTRYP pfn_glPresentFrameKeyedNV) (GLuint, GLuint64EXT, GLuint, GLuint, GLenum, GLenum, GLuint, GLuint, GLenum, GLuint, GLuint);
extern pfn_glPresentFrameKeyedNV fp_glPresentFrameKeyedNV;
typedef void (APIENTRYP pfn_glPresentFrameDualFillNV) (GLuint, GLuint64EXT, GLuint, GLuint, GLenum, GLenum, GLuint, GLenum, GLuint, GLenum, GLuint, GLenum, GLuint);
extern pfn_glPresentFrameDualFillNV fp_glPresentFrameDualFillNV;
typedef void (APIENTRYP pfn_glGetVideoivNV) (GLuint, GLenum, GLint*);
extern pfn_glGetVideoivNV fp_glGetVideoivNV;
typedef void (APIENTRYP pfn_glGetVideouivNV) (GLuint, GLenum, GLuint*);
extern pfn_glGetVideouivNV fp_glGetVideouivNV;
typedef void (APIENTRYP pfn_glGetVideoi64vNV) (GLuint, GLenum, GLint64EXT*);
extern pfn_glGetVideoi64vNV fp_glGetVideoi64vNV;
typedef void (APIENTRYP pfn_glGetVideoui64vNV) (GLuint, GLenum, GLuint64EXT*);
extern pfn_glGetVideoui64vNV fp_glGetVideoui64vNV;

 /* GL_NV_primitive_restart */
extern GLboolean GLAD_NV_primitive_restart;
#define GL_PRIMITIVE_RESTART_NV                0x8558
#define GL_PRIMITIVE_RESTART_INDEX_NV          0x8559
typedef void (APIENTRYP pfn_glPrimitiveRestartNV) ();
extern pfn_glPrimitiveRestartNV fp_glPrimitiveRestartNV;
typedef void (APIENTRYP pfn_glPrimitiveRestartIndexNV) (GLuint);
extern pfn_glPrimitiveRestartIndexNV fp_glPrimitiveRestartIndexNV;

 /* GL_NV_read_buffer */
extern GLboolean GLAD_NV_read_buffer;
#define GL_READ_BUFFER_NV                      0x0C02
typedef void (APIENTRYP pfn_glReadBufferNV) (GLenum);
extern pfn_glReadBufferNV fp_glReadBufferNV;

 /* GL_NV_read_buffer_front */
extern GLboolean GLAD_NV_read_buffer_front;

 /* GL_NV_read_depth */
extern GLboolean GLAD_NV_read_depth;

 /* GL_NV_read_depth_stencil */
extern GLboolean GLAD_NV_read_depth_stencil;

 /* GL_NV_read_stencil */
extern GLboolean GLAD_NV_read_stencil;

 /* GL_NV_register_combiners */
extern GLboolean GLAD_NV_register_combiners;
#define GL_REGISTER_COMBINERS_NV               0x8522
#define GL_VARIABLE_A_NV                       0x8523
#define GL_VARIABLE_B_NV                       0x8524
#define GL_VARIABLE_C_NV                       0x8525
#define GL_VARIABLE_D_NV                       0x8526
#define GL_VARIABLE_E_NV                       0x8527
#define GL_VARIABLE_F_NV                       0x8528
#define GL_VARIABLE_G_NV                       0x8529
#define GL_CONSTANT_COLOR0_NV                  0x852A
#define GL_CONSTANT_COLOR1_NV                  0x852B
#define GL_SPARE0_NV                           0x852E
#define GL_SPARE1_NV                           0x852F
#define GL_DISCARD_NV                          0x8530
#define GL_E_TIMES_F_NV                        0x8531
#define GL_SPARE0_PLUS_SECONDARY_COLOR_NV      0x8532
#define GL_UNSIGNED_IDENTITY_NV                0x8536
#define GL_UNSIGNED_INVERT_NV                  0x8537
#define GL_EXPAND_NORMAL_NV                    0x8538
#define GL_EXPAND_NEGATE_NV                    0x8539
#define GL_HALF_BIAS_NORMAL_NV                 0x853A
#define GL_HALF_BIAS_NEGATE_NV                 0x853B
#define GL_SIGNED_IDENTITY_NV                  0x853C
#define GL_SIGNED_NEGATE_NV                    0x853D
#define GL_SCALE_BY_TWO_NV                     0x853E
#define GL_SCALE_BY_FOUR_NV                    0x853F
#define GL_SCALE_BY_ONE_HALF_NV                0x8540
#define GL_BIAS_BY_NEGATIVE_ONE_HALF_NV        0x8541
#define GL_COMBINER_INPUT_NV                   0x8542
#define GL_COMBINER_MAPPING_NV                 0x8543
#define GL_COMBINER_COMPONENT_USAGE_NV         0x8544
#define GL_COMBINER_AB_DOT_PRODUCT_NV          0x8545
#define GL_COMBINER_CD_DOT_PRODUCT_NV          0x8546
#define GL_COMBINER_MUX_SUM_NV                 0x8547
#define GL_COMBINER_SCALE_NV                   0x8548
#define GL_COMBINER_BIAS_NV                    0x8549
#define GL_COMBINER_AB_OUTPUT_NV               0x854A
#define GL_COMBINER_CD_OUTPUT_NV               0x854B
#define GL_COMBINER_SUM_OUTPUT_NV              0x854C
#define GL_MAX_GENERAL_COMBINERS_NV            0x854D
#define GL_NUM_GENERAL_COMBINERS_NV            0x854E
#define GL_COLOR_SUM_CLAMP_NV                  0x854F
#define GL_COMBINER0_NV                        0x8550
#define GL_COMBINER1_NV                        0x8551
#define GL_COMBINER2_NV                        0x8552
#define GL_COMBINER3_NV                        0x8553
#define GL_COMBINER4_NV                        0x8554
#define GL_COMBINER5_NV                        0x8555
#define GL_COMBINER6_NV                        0x8556
#define GL_COMBINER7_NV                        0x8557
typedef void (APIENTRYP pfn_glCombinerParameterfvNV) (GLenum, const GLfloat*);
extern pfn_glCombinerParameterfvNV fp_glCombinerParameterfvNV;
typedef void (APIENTRYP pfn_glCombinerParameterfNV) (GLenum, GLfloat);
extern pfn_glCombinerParameterfNV fp_glCombinerParameterfNV;
typedef void (APIENTRYP pfn_glCombinerParameterivNV) (GLenum, const GLint*);
extern pfn_glCombinerParameterivNV fp_glCombinerParameterivNV;
typedef void (APIENTRYP pfn_glCombinerParameteriNV) (GLenum, GLint);
extern pfn_glCombinerParameteriNV fp_glCombinerParameteriNV;
typedef void (APIENTRYP pfn_glCombinerInputNV) (GLenum, GLenum, GLenum, GLenum, GLenum, GLenum);
extern pfn_glCombinerInputNV fp_glCombinerInputNV;
typedef void (APIENTRYP pfn_glCombinerOutputNV) (GLenum, GLenum, GLenum, GLenum, GLenum, GLenum, GLenum, GLboolean, GLboolean, GLboolean);
extern pfn_glCombinerOutputNV fp_glCombinerOutputNV;
typedef void (APIENTRYP pfn_glFinalCombinerInputNV) (GLenum, GLenum, GLenum, GLenum);
extern pfn_glFinalCombinerInputNV fp_glFinalCombinerInputNV;
typedef void (APIENTRYP pfn_glGetCombinerInputParameterfvNV) (GLenum, GLenum, GLenum, GLenum, GLfloat*);
extern pfn_glGetCombinerInputParameterfvNV fp_glGetCombinerInputParameterfvNV;
typedef void (APIENTRYP pfn_glGetCombinerInputParameterivNV) (GLenum, GLenum, GLenum, GLenum, GLint*);
extern pfn_glGetCombinerInputParameterivNV fp_glGetCombinerInputParameterivNV;
typedef void (APIENTRYP pfn_glGetCombinerOutputParameterfvNV) (GLenum, GLenum, GLenum, GLfloat*);
extern pfn_glGetCombinerOutputParameterfvNV fp_glGetCombinerOutputParameterfvNV;
typedef void (APIENTRYP pfn_glGetCombinerOutputParameterivNV) (GLenum, GLenum, GLenum, GLint*);
extern pfn_glGetCombinerOutputParameterivNV fp_glGetCombinerOutputParameterivNV;
typedef void (APIENTRYP pfn_glGetFinalCombinerInputParameterfvNV) (GLenum, GLenum, GLfloat*);
extern pfn_glGetFinalCombinerInputParameterfvNV fp_glGetFinalCombinerInputParameterfvNV;
typedef void (APIENTRYP pfn_glGetFinalCombinerInputParameterivNV) (GLenum, GLenum, GLint*);
extern pfn_glGetFinalCombinerInputParameterivNV fp_glGetFinalCombinerInputParameterivNV;

 /* GL_NV_register_combiners2 */
extern GLboolean GLAD_NV_register_combiners2;
#define GL_PER_STAGE_CONSTANTS_NV              0x8535
typedef void (APIENTRYP pfn_glCombinerStageParameterfvNV) (GLenum, GLenum, const GLfloat*);
extern pfn_glCombinerStageParameterfvNV fp_glCombinerStageParameterfvNV;
typedef void (APIENTRYP pfn_glGetCombinerStageParameterfvNV) (GLenum, GLenum, GLfloat*);
extern pfn_glGetCombinerStageParameterfvNV fp_glGetCombinerStageParameterfvNV;

 /* GL_NV_shader_atomic_counters */
extern GLboolean GLAD_NV_shader_atomic_counters;

 /* GL_NV_shader_atomic_float */
extern GLboolean GLAD_NV_shader_atomic_float;

 /* GL_NV_shader_buffer_load */
extern GLboolean GLAD_NV_shader_buffer_load;
#define GL_BUFFER_GPU_ADDRESS_NV               0x8F1D
#define GL_GPU_ADDRESS_NV                      0x8F34
#define GL_MAX_SHADER_BUFFER_ADDRESS_NV        0x8F35
typedef void (APIENTRYP pfn_glMakeBufferResidentNV) (GLenum, GLenum);
extern pfn_glMakeBufferResidentNV fp_glMakeBufferResidentNV;
typedef void (APIENTRYP pfn_glMakeBufferNonResidentNV) (GLenum);
extern pfn_glMakeBufferNonResidentNV fp_glMakeBufferNonResidentNV;
typedef GLboolean (APIENTRYP pfn_glIsBufferResidentNV) (GLenum);
extern pfn_glIsBufferResidentNV fp_glIsBufferResidentNV;
typedef void (APIENTRYP pfn_glMakeNamedBufferResidentNV) (GLuint, GLenum);
extern pfn_glMakeNamedBufferResidentNV fp_glMakeNamedBufferResidentNV;
typedef void (APIENTRYP pfn_glMakeNamedBufferNonResidentNV) (GLuint);
extern pfn_glMakeNamedBufferNonResidentNV fp_glMakeNamedBufferNonResidentNV;
typedef GLboolean (APIENTRYP pfn_glIsNamedBufferResidentNV) (GLuint);
extern pfn_glIsNamedBufferResidentNV fp_glIsNamedBufferResidentNV;
typedef void (APIENTRYP pfn_glGetBufferParameterui64vNV) (GLenum, GLenum, GLuint64EXT*);
extern pfn_glGetBufferParameterui64vNV fp_glGetBufferParameterui64vNV;
typedef void (APIENTRYP pfn_glGetNamedBufferParameterui64vNV) (GLuint, GLenum, GLuint64EXT*);
extern pfn_glGetNamedBufferParameterui64vNV fp_glGetNamedBufferParameterui64vNV;
typedef void (APIENTRYP pfn_glGetIntegerui64vNV) (GLenum, GLuint64EXT*);
extern pfn_glGetIntegerui64vNV fp_glGetIntegerui64vNV;
typedef void (APIENTRYP pfn_glUniformui64NV) (GLint, GLuint64EXT);
extern pfn_glUniformui64NV fp_glUniformui64NV;
typedef void (APIENTRYP pfn_glUniformui64vNV) (GLint, GLsizei, const GLuint64EXT*);
extern pfn_glUniformui64vNV fp_glUniformui64vNV;
typedef void (APIENTRYP pfn_glGetUniformui64vNV) (GLuint, GLint, GLuint64EXT*);
extern pfn_glGetUniformui64vNV fp_glGetUniformui64vNV;
typedef void (APIENTRYP pfn_glProgramUniformui64NV) (GLuint, GLint, GLuint64EXT);
extern pfn_glProgramUniformui64NV fp_glProgramUniformui64NV;
typedef void (APIENTRYP pfn_glProgramUniformui64vNV) (GLuint, GLint, GLsizei, const GLuint64EXT*);
extern pfn_glProgramUniformui64vNV fp_glProgramUniformui64vNV;

 /* GL_NV_shader_buffer_store */
extern GLboolean GLAD_NV_shader_buffer_store;
#define GL_SHADER_GLOBAL_ACCESS_BARRIER_BIT_NV  0x00000010

 /* GL_NV_shader_storage_buffer_object */
extern GLboolean GLAD_NV_shader_storage_buffer_object;

 /* GL_NV_shadow_samplers_array */
extern GLboolean GLAD_NV_shadow_samplers_array;
#define GL_SAMPLER_2D_ARRAY_SHADOW_NV          0x8DC4

 /* GL_NV_shadow_samplers_cube */
extern GLboolean GLAD_NV_shadow_samplers_cube;
#define GL_SAMPLER_CUBE_SHADOW_NV              0x8DC5

 /* GL_NV_sRGB_formats */
extern GLboolean GLAD_NV_sRGB_formats;
#define GL_SLUMINANCE_NV                       0x8C46
#define GL_SLUMINANCE_ALPHA_NV                 0x8C44
#define GL_SRGB8_NV                            0x8C41
#define GL_SLUMINANCE8_NV                      0x8C47
#define GL_SLUMINANCE8_ALPHA8_NV               0x8C45
#define GL_COMPRESSED_SRGB_S3TC_DXT1_NV        0x8C4C
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV  0x8C4D
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV  0x8C4E
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV  0x8C4F
#define GL_ETC1_SRGB8_NV                       0x88EE

 /* GL_NV_tessellation_program5 */
extern GLboolean GLAD_NV_tessellation_program5;
#define GL_MAX_PROGRAM_PATCH_ATTRIBS_NV        0x86D8
#define GL_TESS_CONTROL_PROGRAM_NV             0x891E
#define GL_TESS_EVALUATION_PROGRAM_NV          0x891F
#define GL_TESS_CONTROL_PROGRAM_PARAMETER_BUFFER_NV  0x8C74
#define GL_TESS_EVALUATION_PROGRAM_PARAMETER_BUFFER_NV  0x8C75

 /* GL_NV_texgen_emboss */
extern GLboolean GLAD_NV_texgen_emboss;
#define GL_EMBOSS_LIGHT_NV                     0x855D
#define GL_EMBOSS_CONSTANT_NV                  0x855E
#define GL_EMBOSS_MAP_NV                       0x855F

 /* GL_NV_texgen_reflection */
extern GLboolean GLAD_NV_texgen_reflection;
#define GL_NORMAL_MAP_NV                       0x8511
#define GL_REFLECTION_MAP_NV                   0x8512

 /* GL_NV_texture_barrier */
extern GLboolean GLAD_NV_texture_barrier;
typedef void (APIENTRYP pfn_glTextureBarrierNV) ();
extern pfn_glTextureBarrierNV fp_glTextureBarrierNV;

 /* GL_NV_texture_border_clamp */
extern GLboolean GLAD_NV_texture_border_clamp;
#define GL_TEXTURE_BORDER_COLOR_NV             0x1004
#define GL_CLAMP_TO_BORDER_NV                  0x812D

 /* GL_NV_texture_compression_s3tc_update */
extern GLboolean GLAD_NV_texture_compression_s3tc_update;

 /* GL_NV_texture_compression_vtc */
extern GLboolean GLAD_NV_texture_compression_vtc;

 /* GL_NV_texture_env_combine4 */
extern GLboolean GLAD_NV_texture_env_combine4;
#define GL_COMBINE4_NV                         0x8503
#define GL_SOURCE3_RGB_NV                      0x8583
#define GL_SOURCE3_ALPHA_NV                    0x858B
#define GL_OPERAND3_RGB_NV                     0x8593
#define GL_OPERAND3_ALPHA_NV                   0x859B

 /* GL_NV_texture_expand_normal */
extern GLboolean GLAD_NV_texture_expand_normal;
#define GL_TEXTURE_UNSIGNED_REMAP_MODE_NV      0x888F

 /* GL_NV_texture_multisample */
extern GLboolean GLAD_NV_texture_multisample;
#define GL_TEXTURE_COVERAGE_SAMPLES_NV         0x9045
#define GL_TEXTURE_COLOR_SAMPLES_NV            0x9046
typedef void (APIENTRYP pfn_glTexImage2DMultisampleCoverageNV) (GLenum, GLsizei, GLsizei, GLint, GLsizei, GLsizei, GLboolean);
extern pfn_glTexImage2DMultisampleCoverageNV fp_glTexImage2DMultisampleCoverageNV;
typedef void (APIENTRYP pfn_glTexImage3DMultisampleCoverageNV) (GLenum, GLsizei, GLsizei, GLint, GLsizei, GLsizei, GLsizei, GLboolean);
extern pfn_glTexImage3DMultisampleCoverageNV fp_glTexImage3DMultisampleCoverageNV;
typedef void (APIENTRYP pfn_glTextureImage2DMultisampleNV) (GLuint, GLenum, GLsizei, GLint, GLsizei, GLsizei, GLboolean);
extern pfn_glTextureImage2DMultisampleNV fp_glTextureImage2DMultisampleNV;
typedef void (APIENTRYP pfn_glTextureImage3DMultisampleNV) (GLuint, GLenum, GLsizei, GLint, GLsizei, GLsizei, GLsizei, GLboolean);
extern pfn_glTextureImage3DMultisampleNV fp_glTextureImage3DMultisampleNV;
typedef void (APIENTRYP pfn_glTextureImage2DMultisampleCoverageNV) (GLuint, GLenum, GLsizei, GLsizei, GLint, GLsizei, GLsizei, GLboolean);
extern pfn_glTextureImage2DMultisampleCoverageNV fp_glTextureImage2DMultisampleCoverageNV;
typedef void (APIENTRYP pfn_glTextureImage3DMultisampleCoverageNV) (GLuint, GLenum, GLsizei, GLsizei, GLint, GLsizei, GLsizei, GLsizei, GLboolean);
extern pfn_glTextureImage3DMultisampleCoverageNV fp_glTextureImage3DMultisampleCoverageNV;

 /* GL_NV_texture_npot_2D_mipmap */
extern GLboolean GLAD_NV_texture_npot_2D_mipmap;

 /* GL_NV_texture_rectangle */
extern GLboolean GLAD_NV_texture_rectangle;
#define GL_TEXTURE_RECTANGLE_NV                0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_NV        0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_NV          0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_NV       0x84F8

 /* GL_NV_texture_shader */
extern GLboolean GLAD_NV_texture_shader;
#define GL_OFFSET_TEXTURE_RECTANGLE_NV         0x864C
#define GL_OFFSET_TEXTURE_RECTANGLE_SCALE_NV   0x864D
#define GL_DOT_PRODUCT_TEXTURE_RECTANGLE_NV    0x864E
#define GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV  0x86D9
#define GL_UNSIGNED_INT_S8_S8_8_8_NV           0x86DA
#define GL_UNSIGNED_INT_8_8_S8_S8_REV_NV       0x86DB
#define GL_DSDT_MAG_INTENSITY_NV               0x86DC
#define GL_SHADER_CONSISTENT_NV                0x86DD
#define GL_TEXTURE_SHADER_NV                   0x86DE
#define GL_SHADER_OPERATION_NV                 0x86DF
#define GL_CULL_MODES_NV                       0x86E0
#define GL_OFFSET_TEXTURE_MATRIX_NV            0x86E1
#define GL_OFFSET_TEXTURE_SCALE_NV             0x86E2
#define GL_OFFSET_TEXTURE_BIAS_NV              0x86E3
#define GL_OFFSET_TEXTURE_2D_MATRIX_NV         0x86E1
#define GL_OFFSET_TEXTURE_2D_SCALE_NV          0x86E2
#define GL_OFFSET_TEXTURE_2D_BIAS_NV           0x86E3
#define GL_PREVIOUS_TEXTURE_INPUT_NV           0x86E4
#define GL_CONST_EYE_NV                        0x86E5
#define GL_PASS_THROUGH_NV                     0x86E6
#define GL_CULL_FRAGMENT_NV                    0x86E7
#define GL_OFFSET_TEXTURE_2D_NV                0x86E8
#define GL_DEPENDENT_AR_TEXTURE_2D_NV          0x86E9
#define GL_DEPENDENT_GB_TEXTURE_2D_NV          0x86EA
#define GL_DOT_PRODUCT_NV                      0x86EC
#define GL_DOT_PRODUCT_DEPTH_REPLACE_NV        0x86ED
#define GL_DOT_PRODUCT_TEXTURE_2D_NV           0x86EE
#define GL_DOT_PRODUCT_TEXTURE_CUBE_MAP_NV     0x86F0
#define GL_DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV     0x86F1
#define GL_DOT_PRODUCT_REFLECT_CUBE_MAP_NV     0x86F2
#define GL_DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV  0x86F3
#define GL_HILO_NV                             0x86F4
#define GL_DSDT_NV                             0x86F5
#define GL_DSDT_MAG_NV                         0x86F6
#define GL_DSDT_MAG_VIB_NV                     0x86F7
#define GL_HILO16_NV                           0x86F8
#define GL_SIGNED_HILO_NV                      0x86F9
#define GL_SIGNED_HILO16_NV                    0x86FA
#define GL_SIGNED_RGBA_NV                      0x86FB
#define GL_SIGNED_RGBA8_NV                     0x86FC
#define GL_SIGNED_RGB_NV                       0x86FE
#define GL_SIGNED_RGB8_NV                      0x86FF
#define GL_SIGNED_LUMINANCE_NV                 0x8701
#define GL_SIGNED_LUMINANCE8_NV                0x8702
#define GL_SIGNED_LUMINANCE_ALPHA_NV           0x8703
#define GL_SIGNED_LUMINANCE8_ALPHA8_NV         0x8704
#define GL_SIGNED_ALPHA_NV                     0x8705
#define GL_SIGNED_ALPHA8_NV                    0x8706
#define GL_SIGNED_INTENSITY_NV                 0x8707
#define GL_SIGNED_INTENSITY8_NV                0x8708
#define GL_DSDT8_NV                            0x8709
#define GL_DSDT8_MAG8_NV                       0x870A
#define GL_DSDT8_MAG8_INTENSITY8_NV            0x870B
#define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV        0x870C
#define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV      0x870D
#define GL_HI_SCALE_NV                         0x870E
#define GL_LO_SCALE_NV                         0x870F
#define GL_DS_SCALE_NV                         0x8710
#define GL_DT_SCALE_NV                         0x8711
#define GL_MAGNITUDE_SCALE_NV                  0x8712
#define GL_VIBRANCE_SCALE_NV                   0x8713
#define GL_HI_BIAS_NV                          0x8714
#define GL_LO_BIAS_NV                          0x8715
#define GL_DS_BIAS_NV                          0x8716
#define GL_DT_BIAS_NV                          0x8717
#define GL_MAGNITUDE_BIAS_NV                   0x8718
#define GL_VIBRANCE_BIAS_NV                    0x8719
#define GL_TEXTURE_BORDER_VALUES_NV            0x871A
#define GL_TEXTURE_HI_SIZE_NV                  0x871B
#define GL_TEXTURE_LO_SIZE_NV                  0x871C
#define GL_TEXTURE_DS_SIZE_NV                  0x871D
#define GL_TEXTURE_DT_SIZE_NV                  0x871E
#define GL_TEXTURE_MAG_SIZE_NV                 0x871F

 /* GL_NV_texture_shader2 */
extern GLboolean GLAD_NV_texture_shader2;
#define GL_DOT_PRODUCT_TEXTURE_3D_NV           0x86EF

 /* GL_NV_texture_shader3 */
extern GLboolean GLAD_NV_texture_shader3;
#define GL_OFFSET_PROJECTIVE_TEXTURE_2D_NV     0x8850
#define GL_OFFSET_PROJECTIVE_TEXTURE_2D_SCALE_NV  0x8851
#define GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_NV  0x8852
#define GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_SCALE_NV  0x8853
#define GL_OFFSET_HILO_TEXTURE_2D_NV           0x8854
#define GL_OFFSET_HILO_TEXTURE_RECTANGLE_NV    0x8855
#define GL_OFFSET_HILO_PROJECTIVE_TEXTURE_2D_NV  0x8856
#define GL_OFFSET_HILO_PROJECTIVE_TEXTURE_RECTANGLE_NV  0x8857
#define GL_DEPENDENT_HILO_TEXTURE_2D_NV        0x8858
#define GL_DEPENDENT_RGB_TEXTURE_3D_NV         0x8859
#define GL_DEPENDENT_RGB_TEXTURE_CUBE_MAP_NV   0x885A
#define GL_DOT_PRODUCT_PASS_THROUGH_NV         0x885B
#define GL_DOT_PRODUCT_TEXTURE_1D_NV           0x885C
#define GL_DOT_PRODUCT_AFFINE_DEPTH_REPLACE_NV  0x885D
#define GL_HILO8_NV                            0x885E
#define GL_SIGNED_HILO8_NV                     0x885F
#define GL_FORCE_BLUE_TO_ONE_NV                0x8860

 /* GL_NV_transform_feedback */
extern GLboolean GLAD_NV_transform_feedback;
#define GL_BACK_PRIMARY_COLOR_NV               0x8C77
#define GL_BACK_SECONDARY_COLOR_NV             0x8C78
#define GL_TEXTURE_COORD_NV                    0x8C79
#define GL_CLIP_DISTANCE_NV                    0x8C7A
#define GL_VERTEX_ID_NV                        0x8C7B
#define GL_PRIMITIVE_ID_NV                     0x8C7C
#define GL_GENERIC_ATTRIB_NV                   0x8C7D
#define GL_TRANSFORM_FEEDBACK_ATTRIBS_NV       0x8C7E
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE_NV   0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_NV  0x8C80
#define GL_ACTIVE_VARYINGS_NV                  0x8C81
#define GL_ACTIVE_VARYING_MAX_LENGTH_NV        0x8C82
#define GL_TRANSFORM_FEEDBACK_VARYINGS_NV      0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START_NV  0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE_NV   0x8C85
#define GL_TRANSFORM_FEEDBACK_RECORD_NV        0x8C86
#define GL_PRIMITIVES_GENERATED_NV             0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_NV  0x8C88
#define GL_RASTERIZER_DISCARD_NV               0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_NV  0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_NV  0x8C8B
#define GL_INTERLEAVED_ATTRIBS_NV              0x8C8C
#define GL_SEPARATE_ATTRIBS_NV                 0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER_NV        0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING_NV  0x8C8F
#define GL_LAYER_NV                            0x8DAA
#define GL_NEXT_BUFFER_NV                      -2
#define GL_SKIP_COMPONENTS4_NV                 -3
#define GL_SKIP_COMPONENTS3_NV                 -4
#define GL_SKIP_COMPONENTS2_NV                 -5
#define GL_SKIP_COMPONENTS1_NV                 -6
typedef void (APIENTRYP pfn_glBeginTransformFeedbackNV) (GLenum);
extern pfn_glBeginTransformFeedbackNV fp_glBeginTransformFeedbackNV;
typedef void (APIENTRYP pfn_glEndTransformFeedbackNV) ();
extern pfn_glEndTransformFeedbackNV fp_glEndTransformFeedbackNV;
typedef void (APIENTRYP pfn_glTransformFeedbackAttribsNV) (GLuint, const GLint*, GLenum);
extern pfn_glTransformFeedbackAttribsNV fp_glTransformFeedbackAttribsNV;
typedef void (APIENTRYP pfn_glBindBufferRangeNV) (GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
extern pfn_glBindBufferRangeNV fp_glBindBufferRangeNV;
typedef void (APIENTRYP pfn_glBindBufferOffsetNV) (GLenum, GLuint, GLuint, GLintptr);
extern pfn_glBindBufferOffsetNV fp_glBindBufferOffsetNV;
typedef void (APIENTRYP pfn_glBindBufferBaseNV) (GLenum, GLuint, GLuint);
extern pfn_glBindBufferBaseNV fp_glBindBufferBaseNV;
typedef void (APIENTRYP pfn_glTransformFeedbackVaryingsNV) (GLuint, GLsizei, const GLint*, GLenum);
extern pfn_glTransformFeedbackVaryingsNV fp_glTransformFeedbackVaryingsNV;
typedef void (APIENTRYP pfn_glActiveVaryingNV) (GLuint, const GLchar*);
extern pfn_glActiveVaryingNV fp_glActiveVaryingNV;
typedef GLint (APIENTRYP pfn_glGetVaryingLocationNV) (GLuint, const GLchar*);
extern pfn_glGetVaryingLocationNV fp_glGetVaryingLocationNV;
typedef void (APIENTRYP pfn_glGetActiveVaryingNV) (GLuint, GLuint, GLsizei, GLsizei*, GLsizei*, GLenum*, GLchar*);
extern pfn_glGetActiveVaryingNV fp_glGetActiveVaryingNV;
typedef void (APIENTRYP pfn_glGetTransformFeedbackVaryingNV) (GLuint, GLuint, GLint*);
extern pfn_glGetTransformFeedbackVaryingNV fp_glGetTransformFeedbackVaryingNV;
typedef void (APIENTRYP pfn_glTransformFeedbackStreamAttribsNV) (GLsizei, const GLint*, GLsizei, const GLint*, GLenum);
extern pfn_glTransformFeedbackStreamAttribsNV fp_glTransformFeedbackStreamAttribsNV;

 /* GL_NV_transform_feedback2 */
extern GLboolean GLAD_NV_transform_feedback2;
#define GL_TRANSFORM_FEEDBACK_NV               0x8E22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED_NV  0x8E23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE_NV  0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING_NV       0x8E25
typedef void (APIENTRYP pfn_glBindTransformFeedbackNV) (GLenum, GLuint);
extern pfn_glBindTransformFeedbackNV fp_glBindTransformFeedbackNV;
typedef void (APIENTRYP pfn_glDeleteTransformFeedbacksNV) (GLsizei, const GLuint*);
extern pfn_glDeleteTransformFeedbacksNV fp_glDeleteTransformFeedbacksNV;
typedef void (APIENTRYP pfn_glGenTransformFeedbacksNV) (GLsizei, GLuint*);
extern pfn_glGenTransformFeedbacksNV fp_glGenTransformFeedbacksNV;
typedef GLboolean (APIENTRYP pfn_glIsTransformFeedbackNV) (GLuint);
extern pfn_glIsTransformFeedbackNV fp_glIsTransformFeedbackNV;
typedef void (APIENTRYP pfn_glPauseTransformFeedbackNV) ();
extern pfn_glPauseTransformFeedbackNV fp_glPauseTransformFeedbackNV;
typedef void (APIENTRYP pfn_glResumeTransformFeedbackNV) ();
extern pfn_glResumeTransformFeedbackNV fp_glResumeTransformFeedbackNV;
typedef void (APIENTRYP pfn_glDrawTransformFeedbackNV) (GLenum, GLuint);
extern pfn_glDrawTransformFeedbackNV fp_glDrawTransformFeedbackNV;

 /* GL_NV_vdpau_interop */
extern GLboolean GLAD_NV_vdpau_interop;
#define GL_SURFACE_STATE_NV                    0x86EB
#define GL_SURFACE_REGISTERED_NV               0x86FD
#define GL_SURFACE_MAPPED_NV                   0x8700
#define GL_WRITE_DISCARD_NV                    0x88BE
typedef void (APIENTRYP pfn_glVDPAUInitNV) (const void*, const void*);
extern pfn_glVDPAUInitNV fp_glVDPAUInitNV;
typedef void (APIENTRYP pfn_glVDPAUFiniNV) ();
extern pfn_glVDPAUFiniNV fp_glVDPAUFiniNV;
typedef GLvdpauSurfaceNV (APIENTRYP pfn_glVDPAURegisterVideoSurfaceNV) (const void*, GLenum, GLsizei, const GLuint*);
extern pfn_glVDPAURegisterVideoSurfaceNV fp_glVDPAURegisterVideoSurfaceNV;
typedef GLvdpauSurfaceNV (APIENTRYP pfn_glVDPAURegisterOutputSurfaceNV) (const void*, GLenum, GLsizei, const GLuint*);
extern pfn_glVDPAURegisterOutputSurfaceNV fp_glVDPAURegisterOutputSurfaceNV;
typedef void (APIENTRYP pfn_glVDPAUIsSurfaceNV) (GLvdpauSurfaceNV);
extern pfn_glVDPAUIsSurfaceNV fp_glVDPAUIsSurfaceNV;
typedef void (APIENTRYP pfn_glVDPAUUnregisterSurfaceNV) (GLvdpauSurfaceNV);
extern pfn_glVDPAUUnregisterSurfaceNV fp_glVDPAUUnregisterSurfaceNV;
typedef void (APIENTRYP pfn_glVDPAUGetSurfaceivNV) (GLvdpauSurfaceNV, GLenum, GLsizei, GLsizei*, GLint*);
extern pfn_glVDPAUGetSurfaceivNV fp_glVDPAUGetSurfaceivNV;
typedef void (APIENTRYP pfn_glVDPAUSurfaceAccessNV) (GLvdpauSurfaceNV, GLenum);
extern pfn_glVDPAUSurfaceAccessNV fp_glVDPAUSurfaceAccessNV;
typedef void (APIENTRYP pfn_glVDPAUMapSurfacesNV) (GLsizei, const GLvdpauSurfaceNV*);
extern pfn_glVDPAUMapSurfacesNV fp_glVDPAUMapSurfacesNV;
typedef void (APIENTRYP pfn_glVDPAUUnmapSurfacesNV) (GLsizei, const GLvdpauSurfaceNV*);
extern pfn_glVDPAUUnmapSurfacesNV fp_glVDPAUUnmapSurfacesNV;

 /* GL_NV_vertex_array_range */
extern GLboolean GLAD_NV_vertex_array_range;
#define GL_VERTEX_ARRAY_RANGE_NV               0x851D
#define GL_VERTEX_ARRAY_RANGE_LENGTH_NV        0x851E
#define GL_VERTEX_ARRAY_RANGE_VALID_NV         0x851F
#define GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV   0x8520
#define GL_VERTEX_ARRAY_RANGE_POINTER_NV       0x8521
typedef void (APIENTRYP pfn_glFlushVertexArrayRangeNV) ();
extern pfn_glFlushVertexArrayRangeNV fp_glFlushVertexArrayRangeNV;
typedef void (APIENTRYP pfn_glVertexArrayRangeNV) (GLsizei, const void*);
extern pfn_glVertexArrayRangeNV fp_glVertexArrayRangeNV;

 /* GL_NV_vertex_array_range2 */
extern GLboolean GLAD_NV_vertex_array_range2;
#define GL_VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV  0x8533

 /* GL_NV_vertex_attrib_integer_64bit */
extern GLboolean GLAD_NV_vertex_attrib_integer_64bit;
typedef void (APIENTRYP pfn_glVertexAttribL1i64NV) (GLuint, GLint64EXT);
extern pfn_glVertexAttribL1i64NV fp_glVertexAttribL1i64NV;
typedef void (APIENTRYP pfn_glVertexAttribL2i64NV) (GLuint, GLint64EXT, GLint64EXT);
extern pfn_glVertexAttribL2i64NV fp_glVertexAttribL2i64NV;
typedef void (APIENTRYP pfn_glVertexAttribL3i64NV) (GLuint, GLint64EXT, GLint64EXT, GLint64EXT);
extern pfn_glVertexAttribL3i64NV fp_glVertexAttribL3i64NV;
typedef void (APIENTRYP pfn_glVertexAttribL4i64NV) (GLuint, GLint64EXT, GLint64EXT, GLint64EXT, GLint64EXT);
extern pfn_glVertexAttribL4i64NV fp_glVertexAttribL4i64NV;
typedef void (APIENTRYP pfn_glVertexAttribL1i64vNV) (GLuint, const GLint64EXT*);
extern pfn_glVertexAttribL1i64vNV fp_glVertexAttribL1i64vNV;
typedef void (APIENTRYP pfn_glVertexAttribL2i64vNV) (GLuint, const GLint64EXT*);
extern pfn_glVertexAttribL2i64vNV fp_glVertexAttribL2i64vNV;
typedef void (APIENTRYP pfn_glVertexAttribL3i64vNV) (GLuint, const GLint64EXT*);
extern pfn_glVertexAttribL3i64vNV fp_glVertexAttribL3i64vNV;
typedef void (APIENTRYP pfn_glVertexAttribL4i64vNV) (GLuint, const GLint64EXT*);
extern pfn_glVertexAttribL4i64vNV fp_glVertexAttribL4i64vNV;
typedef void (APIENTRYP pfn_glVertexAttribL1ui64NV) (GLuint, GLuint64EXT);
extern pfn_glVertexAttribL1ui64NV fp_glVertexAttribL1ui64NV;
typedef void (APIENTRYP pfn_glVertexAttribL2ui64NV) (GLuint, GLuint64EXT, GLuint64EXT);
extern pfn_glVertexAttribL2ui64NV fp_glVertexAttribL2ui64NV;
typedef void (APIENTRYP pfn_glVertexAttribL3ui64NV) (GLuint, GLuint64EXT, GLuint64EXT, GLuint64EXT);
extern pfn_glVertexAttribL3ui64NV fp_glVertexAttribL3ui64NV;
typedef void (APIENTRYP pfn_glVertexAttribL4ui64NV) (GLuint, GLuint64EXT, GLuint64EXT, GLuint64EXT, GLuint64EXT);
extern pfn_glVertexAttribL4ui64NV fp_glVertexAttribL4ui64NV;
typedef void (APIENTRYP pfn_glVertexAttribL1ui64vNV) (GLuint, const GLuint64EXT*);
extern pfn_glVertexAttribL1ui64vNV fp_glVertexAttribL1ui64vNV;
typedef void (APIENTRYP pfn_glVertexAttribL2ui64vNV) (GLuint, const GLuint64EXT*);
extern pfn_glVertexAttribL2ui64vNV fp_glVertexAttribL2ui64vNV;
typedef void (APIENTRYP pfn_glVertexAttribL3ui64vNV) (GLuint, const GLuint64EXT*);
extern pfn_glVertexAttribL3ui64vNV fp_glVertexAttribL3ui64vNV;
typedef void (APIENTRYP pfn_glVertexAttribL4ui64vNV) (GLuint, const GLuint64EXT*);
extern pfn_glVertexAttribL4ui64vNV fp_glVertexAttribL4ui64vNV;
typedef void (APIENTRYP pfn_glGetVertexAttribLi64vNV) (GLuint, GLenum, GLint64EXT*);
extern pfn_glGetVertexAttribLi64vNV fp_glGetVertexAttribLi64vNV;
typedef void (APIENTRYP pfn_glGetVertexAttribLui64vNV) (GLuint, GLenum, GLuint64EXT*);
extern pfn_glGetVertexAttribLui64vNV fp_glGetVertexAttribLui64vNV;
typedef void (APIENTRYP pfn_glVertexAttribLFormatNV) (GLuint, GLint, GLenum, GLsizei);
extern pfn_glVertexAttribLFormatNV fp_glVertexAttribLFormatNV;

 /* GL_NV_vertex_buffer_unified_memory */
extern GLboolean GLAD_NV_vertex_buffer_unified_memory;
#define GL_VERTEX_ATTRIB_ARRAY_UNIFIED_NV      0x8F1E
#define GL_ELEMENT_ARRAY_UNIFIED_NV            0x8F1F
#define GL_VERTEX_ATTRIB_ARRAY_ADDRESS_NV      0x8F20
#define GL_VERTEX_ARRAY_ADDRESS_NV             0x8F21
#define GL_NORMAL_ARRAY_ADDRESS_NV             0x8F22
#define GL_COLOR_ARRAY_ADDRESS_NV              0x8F23
#define GL_INDEX_ARRAY_ADDRESS_NV              0x8F24
#define GL_TEXTURE_COORD_ARRAY_ADDRESS_NV      0x8F25
#define GL_EDGE_FLAG_ARRAY_ADDRESS_NV          0x8F26
#define GL_SECONDARY_COLOR_ARRAY_ADDRESS_NV    0x8F27
#define GL_FOG_COORD_ARRAY_ADDRESS_NV          0x8F28
#define GL_ELEMENT_ARRAY_ADDRESS_NV            0x8F29
#define GL_VERTEX_ATTRIB_ARRAY_LENGTH_NV       0x8F2A
#define GL_VERTEX_ARRAY_LENGTH_NV              0x8F2B
#define GL_NORMAL_ARRAY_LENGTH_NV              0x8F2C
#define GL_COLOR_ARRAY_LENGTH_NV               0x8F2D
#define GL_INDEX_ARRAY_LENGTH_NV               0x8F2E
#define GL_TEXTURE_COORD_ARRAY_LENGTH_NV       0x8F2F
#define GL_EDGE_FLAG_ARRAY_LENGTH_NV           0x8F30
#define GL_SECONDARY_COLOR_ARRAY_LENGTH_NV     0x8F31
#define GL_FOG_COORD_ARRAY_LENGTH_NV           0x8F32
#define GL_ELEMENT_ARRAY_LENGTH_NV             0x8F33
#define GL_DRAW_INDIRECT_UNIFIED_NV            0x8F40
#define GL_DRAW_INDIRECT_ADDRESS_NV            0x8F41
#define GL_DRAW_INDIRECT_LENGTH_NV             0x8F42
typedef void (APIENTRYP pfn_glBufferAddressRangeNV) (GLenum, GLuint, GLuint64EXT, GLsizeiptr);
extern pfn_glBufferAddressRangeNV fp_glBufferAddressRangeNV;
typedef void (APIENTRYP pfn_glVertexFormatNV) (GLint, GLenum, GLsizei);
extern pfn_glVertexFormatNV fp_glVertexFormatNV;
typedef void (APIENTRYP pfn_glNormalFormatNV) (GLenum, GLsizei);
extern pfn_glNormalFormatNV fp_glNormalFormatNV;
typedef void (APIENTRYP pfn_glColorFormatNV) (GLint, GLenum, GLsizei);
extern pfn_glColorFormatNV fp_glColorFormatNV;
typedef void (APIENTRYP pfn_glIndexFormatNV) (GLenum, GLsizei);
extern pfn_glIndexFormatNV fp_glIndexFormatNV;
typedef void (APIENTRYP pfn_glTexCoordFormatNV) (GLint, GLenum, GLsizei);
extern pfn_glTexCoordFormatNV fp_glTexCoordFormatNV;
typedef void (APIENTRYP pfn_glEdgeFlagFormatNV) (GLsizei);
extern pfn_glEdgeFlagFormatNV fp_glEdgeFlagFormatNV;
typedef void (APIENTRYP pfn_glSecondaryColorFormatNV) (GLint, GLenum, GLsizei);
extern pfn_glSecondaryColorFormatNV fp_glSecondaryColorFormatNV;
typedef void (APIENTRYP pfn_glFogCoordFormatNV) (GLenum, GLsizei);
extern pfn_glFogCoordFormatNV fp_glFogCoordFormatNV;
typedef void (APIENTRYP pfn_glVertexAttribFormatNV) (GLuint, GLint, GLenum, GLboolean, GLsizei);
extern pfn_glVertexAttribFormatNV fp_glVertexAttribFormatNV;
typedef void (APIENTRYP pfn_glVertexAttribIFormatNV) (GLuint, GLint, GLenum, GLsizei);
extern pfn_glVertexAttribIFormatNV fp_glVertexAttribIFormatNV;
typedef void (APIENTRYP pfn_glGetIntegerui64i_vNV) (GLenum, GLuint, GLuint64EXT*);
extern pfn_glGetIntegerui64i_vNV fp_glGetIntegerui64i_vNV;

 /* GL_NV_vertex_program */
extern GLboolean GLAD_NV_vertex_program;
#define GL_VERTEX_PROGRAM_NV                   0x8620
#define GL_VERTEX_STATE_PROGRAM_NV             0x8621
#define GL_ATTRIB_ARRAY_SIZE_NV                0x8623
#define GL_ATTRIB_ARRAY_STRIDE_NV              0x8624
#define GL_ATTRIB_ARRAY_TYPE_NV                0x8625
#define GL_CURRENT_ATTRIB_NV                   0x8626
#define GL_PROGRAM_LENGTH_NV                   0x8627
#define GL_PROGRAM_STRING_NV                   0x8628
#define GL_MODELVIEW_PROJECTION_NV             0x8629
#define GL_IDENTITY_NV                         0x862A
#define GL_INVERSE_NV                          0x862B
#define GL_TRANSPOSE_NV                        0x862C
#define GL_INVERSE_TRANSPOSE_NV                0x862D
#define GL_MAX_TRACK_MATRIX_STACK_DEPTH_NV     0x862E
#define GL_MAX_TRACK_MATRICES_NV               0x862F
#define GL_MATRIX0_NV                          0x8630
#define GL_MATRIX1_NV                          0x8631
#define GL_MATRIX2_NV                          0x8632
#define GL_MATRIX3_NV                          0x8633
#define GL_MATRIX4_NV                          0x8634
#define GL_MATRIX5_NV                          0x8635
#define GL_MATRIX6_NV                          0x8636
#define GL_MATRIX7_NV                          0x8637
#define GL_CURRENT_MATRIX_STACK_DEPTH_NV       0x8640
#define GL_CURRENT_MATRIX_NV                   0x8641
#define GL_VERTEX_PROGRAM_POINT_SIZE_NV        0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_NV          0x8643
#define GL_PROGRAM_PARAMETER_NV                0x8644
#define GL_ATTRIB_ARRAY_POINTER_NV             0x8645
#define GL_PROGRAM_TARGET_NV                   0x8646
#define GL_PROGRAM_RESIDENT_NV                 0x8647
#define GL_TRACK_MATRIX_NV                     0x8648
#define GL_TRACK_MATRIX_TRANSFORM_NV           0x8649
#define GL_VERTEX_PROGRAM_BINDING_NV           0x864A
#define GL_PROGRAM_ERROR_POSITION_NV           0x864B
#define GL_VERTEX_ATTRIB_ARRAY0_NV             0x8650
#define GL_VERTEX_ATTRIB_ARRAY1_NV             0x8651
#define GL_VERTEX_ATTRIB_ARRAY2_NV             0x8652
#define GL_VERTEX_ATTRIB_ARRAY3_NV             0x8653
#define GL_VERTEX_ATTRIB_ARRAY4_NV             0x8654
#define GL_VERTEX_ATTRIB_ARRAY5_NV             0x8655
#define GL_VERTEX_ATTRIB_ARRAY6_NV             0x8656
#define GL_VERTEX_ATTRIB_ARRAY7_NV             0x8657
#define GL_VERTEX_ATTRIB_ARRAY8_NV             0x8658
#define GL_VERTEX_ATTRIB_ARRAY9_NV             0x8659
#define GL_VERTEX_ATTRIB_ARRAY10_NV            0x865A
#define GL_VERTEX_ATTRIB_ARRAY11_NV            0x865B
#define GL_VERTEX_ATTRIB_ARRAY12_NV            0x865C
#define GL_VERTEX_ATTRIB_ARRAY13_NV            0x865D
#define GL_VERTEX_ATTRIB_ARRAY14_NV            0x865E
#define GL_VERTEX_ATTRIB_ARRAY15_NV            0x865F
#define GL_MAP1_VERTEX_ATTRIB0_4_NV            0x8660
#define GL_MAP1_VERTEX_ATTRIB1_4_NV            0x8661
#define GL_MAP1_VERTEX_ATTRIB2_4_NV            0x8662
#define GL_MAP1_VERTEX_ATTRIB3_4_NV            0x8663
#define GL_MAP1_VERTEX_ATTRIB4_4_NV            0x8664
#define GL_MAP1_VERTEX_ATTRIB5_4_NV            0x8665
#define GL_MAP1_VERTEX_ATTRIB6_4_NV            0x8666
#define GL_MAP1_VERTEX_ATTRIB7_4_NV            0x8667
#define GL_MAP1_VERTEX_ATTRIB8_4_NV            0x8668
#define GL_MAP1_VERTEX_ATTRIB9_4_NV            0x8669
#define GL_MAP1_VERTEX_ATTRIB10_4_NV           0x866A
#define GL_MAP1_VERTEX_ATTRIB11_4_NV           0x866B
#define GL_MAP1_VERTEX_ATTRIB12_4_NV           0x866C
#define GL_MAP1_VERTEX_ATTRIB13_4_NV           0x866D
#define GL_MAP1_VERTEX_ATTRIB14_4_NV           0x866E
#define GL_MAP1_VERTEX_ATTRIB15_4_NV           0x866F
#define GL_MAP2_VERTEX_ATTRIB0_4_NV            0x8670
#define GL_MAP2_VERTEX_ATTRIB1_4_NV            0x8671
#define GL_MAP2_VERTEX_ATTRIB2_4_NV            0x8672
#define GL_MAP2_VERTEX_ATTRIB3_4_NV            0x8673
#define GL_MAP2_VERTEX_ATTRIB4_4_NV            0x8674
#define GL_MAP2_VERTEX_ATTRIB5_4_NV            0x8675
#define GL_MAP2_VERTEX_ATTRIB6_4_NV            0x8676
#define GL_MAP2_VERTEX_ATTRIB7_4_NV            0x8677
#define GL_MAP2_VERTEX_ATTRIB8_4_NV            0x8678
#define GL_MAP2_VERTEX_ATTRIB9_4_NV            0x8679
#define GL_MAP2_VERTEX_ATTRIB10_4_NV           0x867A
#define GL_MAP2_VERTEX_ATTRIB11_4_NV           0x867B
#define GL_MAP2_VERTEX_ATTRIB12_4_NV           0x867C
#define GL_MAP2_VERTEX_ATTRIB13_4_NV           0x867D
#define GL_MAP2_VERTEX_ATTRIB14_4_NV           0x867E
#define GL_MAP2_VERTEX_ATTRIB15_4_NV           0x867F
typedef GLboolean (APIENTRYP pfn_glAreProgramsResidentNV) (GLsizei, const GLuint*, GLboolean*);
extern pfn_glAreProgramsResidentNV fp_glAreProgramsResidentNV;
typedef void (APIENTRYP pfn_glBindProgramNV) (GLenum, GLuint);
extern pfn_glBindProgramNV fp_glBindProgramNV;
typedef void (APIENTRYP pfn_glDeleteProgramsNV) (GLsizei, const GLuint*);
extern pfn_glDeleteProgramsNV fp_glDeleteProgramsNV;
typedef void (APIENTRYP pfn_glExecuteProgramNV) (GLenum, GLuint, const GLfloat*);
extern pfn_glExecuteProgramNV fp_glExecuteProgramNV;
typedef void (APIENTRYP pfn_glGenProgramsNV) (GLsizei, GLuint*);
extern pfn_glGenProgramsNV fp_glGenProgramsNV;
typedef void (APIENTRYP pfn_glGetProgramParameterdvNV) (GLenum, GLuint, GLenum, GLdouble*);
extern pfn_glGetProgramParameterdvNV fp_glGetProgramParameterdvNV;
typedef void (APIENTRYP pfn_glGetProgramParameterfvNV) (GLenum, GLuint, GLenum, GLfloat*);
extern pfn_glGetProgramParameterfvNV fp_glGetProgramParameterfvNV;
typedef void (APIENTRYP pfn_glGetProgramivNV) (GLuint, GLenum, GLint*);
extern pfn_glGetProgramivNV fp_glGetProgramivNV;
typedef void (APIENTRYP pfn_glGetProgramStringNV) (GLuint, GLenum, GLubyte*);
extern pfn_glGetProgramStringNV fp_glGetProgramStringNV;
typedef void (APIENTRYP pfn_glGetTrackMatrixivNV) (GLenum, GLuint, GLenum, GLint*);
extern pfn_glGetTrackMatrixivNV fp_glGetTrackMatrixivNV;
typedef void (APIENTRYP pfn_glGetVertexAttribdvNV) (GLuint, GLenum, GLdouble*);
extern pfn_glGetVertexAttribdvNV fp_glGetVertexAttribdvNV;
typedef void (APIENTRYP pfn_glGetVertexAttribfvNV) (GLuint, GLenum, GLfloat*);
extern pfn_glGetVertexAttribfvNV fp_glGetVertexAttribfvNV;
typedef void (APIENTRYP pfn_glGetVertexAttribivNV) (GLuint, GLenum, GLint*);
extern pfn_glGetVertexAttribivNV fp_glGetVertexAttribivNV;
typedef void (APIENTRYP pfn_glGetVertexAttribPointervNV) (GLuint, GLenum, void**);
extern pfn_glGetVertexAttribPointervNV fp_glGetVertexAttribPointervNV;
typedef GLboolean (APIENTRYP pfn_glIsProgramNV) (GLuint);
extern pfn_glIsProgramNV fp_glIsProgramNV;
typedef void (APIENTRYP pfn_glLoadProgramNV) (GLenum, GLuint, GLsizei, const GLubyte*);
extern pfn_glLoadProgramNV fp_glLoadProgramNV;
typedef void (APIENTRYP pfn_glProgramParameter4dNV) (GLenum, GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glProgramParameter4dNV fp_glProgramParameter4dNV;
typedef void (APIENTRYP pfn_glProgramParameter4dvNV) (GLenum, GLuint, const GLdouble*);
extern pfn_glProgramParameter4dvNV fp_glProgramParameter4dvNV;
typedef void (APIENTRYP pfn_glProgramParameter4fNV) (GLenum, GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glProgramParameter4fNV fp_glProgramParameter4fNV;
typedef void (APIENTRYP pfn_glProgramParameter4fvNV) (GLenum, GLuint, const GLfloat*);
extern pfn_glProgramParameter4fvNV fp_glProgramParameter4fvNV;
typedef void (APIENTRYP pfn_glProgramParameters4dvNV) (GLenum, GLuint, GLsizei, const GLdouble*);
extern pfn_glProgramParameters4dvNV fp_glProgramParameters4dvNV;
typedef void (APIENTRYP pfn_glProgramParameters4fvNV) (GLenum, GLuint, GLsizei, const GLfloat*);
extern pfn_glProgramParameters4fvNV fp_glProgramParameters4fvNV;
typedef void (APIENTRYP pfn_glRequestResidentProgramsNV) (GLsizei, const GLuint*);
extern pfn_glRequestResidentProgramsNV fp_glRequestResidentProgramsNV;
typedef void (APIENTRYP pfn_glTrackMatrixNV) (GLenum, GLuint, GLenum, GLenum);
extern pfn_glTrackMatrixNV fp_glTrackMatrixNV;
typedef void (APIENTRYP pfn_glVertexAttribPointerNV) (GLuint, GLint, GLenum, GLsizei, const void*);
extern pfn_glVertexAttribPointerNV fp_glVertexAttribPointerNV;
typedef void (APIENTRYP pfn_glVertexAttrib1dNV) (GLuint, GLdouble);
extern pfn_glVertexAttrib1dNV fp_glVertexAttrib1dNV;
typedef void (APIENTRYP pfn_glVertexAttrib1dvNV) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib1dvNV fp_glVertexAttrib1dvNV;
typedef void (APIENTRYP pfn_glVertexAttrib1fNV) (GLuint, GLfloat);
extern pfn_glVertexAttrib1fNV fp_glVertexAttrib1fNV;
typedef void (APIENTRYP pfn_glVertexAttrib1fvNV) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib1fvNV fp_glVertexAttrib1fvNV;
typedef void (APIENTRYP pfn_glVertexAttrib1sNV) (GLuint, GLshort);
extern pfn_glVertexAttrib1sNV fp_glVertexAttrib1sNV;
typedef void (APIENTRYP pfn_glVertexAttrib1svNV) (GLuint, const GLshort*);
extern pfn_glVertexAttrib1svNV fp_glVertexAttrib1svNV;
typedef void (APIENTRYP pfn_glVertexAttrib2dNV) (GLuint, GLdouble, GLdouble);
extern pfn_glVertexAttrib2dNV fp_glVertexAttrib2dNV;
typedef void (APIENTRYP pfn_glVertexAttrib2dvNV) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib2dvNV fp_glVertexAttrib2dvNV;
typedef void (APIENTRYP pfn_glVertexAttrib2fNV) (GLuint, GLfloat, GLfloat);
extern pfn_glVertexAttrib2fNV fp_glVertexAttrib2fNV;
typedef void (APIENTRYP pfn_glVertexAttrib2fvNV) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib2fvNV fp_glVertexAttrib2fvNV;
typedef void (APIENTRYP pfn_glVertexAttrib2sNV) (GLuint, GLshort, GLshort);
extern pfn_glVertexAttrib2sNV fp_glVertexAttrib2sNV;
typedef void (APIENTRYP pfn_glVertexAttrib2svNV) (GLuint, const GLshort*);
extern pfn_glVertexAttrib2svNV fp_glVertexAttrib2svNV;
typedef void (APIENTRYP pfn_glVertexAttrib3dNV) (GLuint, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexAttrib3dNV fp_glVertexAttrib3dNV;
typedef void (APIENTRYP pfn_glVertexAttrib3dvNV) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib3dvNV fp_glVertexAttrib3dvNV;
typedef void (APIENTRYP pfn_glVertexAttrib3fNV) (GLuint, GLfloat, GLfloat, GLfloat);
extern pfn_glVertexAttrib3fNV fp_glVertexAttrib3fNV;
typedef void (APIENTRYP pfn_glVertexAttrib3fvNV) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib3fvNV fp_glVertexAttrib3fvNV;
typedef void (APIENTRYP pfn_glVertexAttrib3sNV) (GLuint, GLshort, GLshort, GLshort);
extern pfn_glVertexAttrib3sNV fp_glVertexAttrib3sNV;
typedef void (APIENTRYP pfn_glVertexAttrib3svNV) (GLuint, const GLshort*);
extern pfn_glVertexAttrib3svNV fp_glVertexAttrib3svNV;
typedef void (APIENTRYP pfn_glVertexAttrib4dNV) (GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
extern pfn_glVertexAttrib4dNV fp_glVertexAttrib4dNV;
typedef void (APIENTRYP pfn_glVertexAttrib4dvNV) (GLuint, const GLdouble*);
extern pfn_glVertexAttrib4dvNV fp_glVertexAttrib4dvNV;
typedef void (APIENTRYP pfn_glVertexAttrib4fNV) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern pfn_glVertexAttrib4fNV fp_glVertexAttrib4fNV;
typedef void (APIENTRYP pfn_glVertexAttrib4fvNV) (GLuint, const GLfloat*);
extern pfn_glVertexAttrib4fvNV fp_glVertexAttrib4fvNV;
typedef void (APIENTRYP pfn_glVertexAttrib4sNV) (GLuint, GLshort, GLshort, GLshort, GLshort);
extern pfn_glVertexAttrib4sNV fp_glVertexAttrib4sNV;
typedef void (APIENTRYP pfn_glVertexAttrib4svNV) (GLuint, const GLshort*);
extern pfn_glVertexAttrib4svNV fp_glVertexAttrib4svNV;
typedef void (APIENTRYP pfn_glVertexAttrib4ubNV) (GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
extern pfn_glVertexAttrib4ubNV fp_glVertexAttrib4ubNV;
typedef void (APIENTRYP pfn_glVertexAttrib4ubvNV) (GLuint, const GLubyte*);
extern pfn_glVertexAttrib4ubvNV fp_glVertexAttrib4ubvNV;
typedef void (APIENTRYP pfn_glVertexAttribs1dvNV) (GLuint, GLsizei, const GLdouble*);
extern pfn_glVertexAttribs1dvNV fp_glVertexAttribs1dvNV;
typedef void (APIENTRYP pfn_glVertexAttribs1fvNV) (GLuint, GLsizei, const GLfloat*);
extern pfn_glVertexAttribs1fvNV fp_glVertexAttribs1fvNV;
typedef void (APIENTRYP pfn_glVertexAttribs1svNV) (GLuint, GLsizei, const GLshort*);
extern pfn_glVertexAttribs1svNV fp_glVertexAttribs1svNV;
typedef void (APIENTRYP pfn_glVertexAttribs2dvNV) (GLuint, GLsizei, const GLdouble*);
extern pfn_glVertexAttribs2dvNV fp_glVertexAttribs2dvNV;
typedef void (APIENTRYP pfn_glVertexAttribs2fvNV) (GLuint, GLsizei, const GLfloat*);
extern pfn_glVertexAttribs2fvNV fp_glVertexAttribs2fvNV;
typedef void (APIENTRYP pfn_glVertexAttribs2svNV) (GLuint, GLsizei, const GLshort*);
extern pfn_glVertexAttribs2svNV fp_glVertexAttribs2svNV;
typedef void (APIENTRYP pfn_glVertexAttribs3dvNV) (GLuint, GLsizei, const GLdouble*);
extern pfn_glVertexAttribs3dvNV fp_glVertexAttribs3dvNV;
typedef void (APIENTRYP pfn_glVertexAttribs3fvNV) (GLuint, GLsizei, const GLfloat*);
extern pfn_glVertexAttribs3fvNV fp_glVertexAttribs3fvNV;
typedef void (APIENTRYP pfn_glVertexAttribs3svNV) (GLuint, GLsizei, const GLshort*);
extern pfn_glVertexAttribs3svNV fp_glVertexAttribs3svNV;
typedef void (APIENTRYP pfn_glVertexAttribs4dvNV) (GLuint, GLsizei, const GLdouble*);
extern pfn_glVertexAttribs4dvNV fp_glVertexAttribs4dvNV;
typedef void (APIENTRYP pfn_glVertexAttribs4fvNV) (GLuint, GLsizei, const GLfloat*);
extern pfn_glVertexAttribs4fvNV fp_glVertexAttribs4fvNV;
typedef void (APIENTRYP pfn_glVertexAttribs4svNV) (GLuint, GLsizei, const GLshort*);
extern pfn_glVertexAttribs4svNV fp_glVertexAttribs4svNV;
typedef void (APIENTRYP pfn_glVertexAttribs4ubvNV) (GLuint, GLsizei, const GLubyte*);
extern pfn_glVertexAttribs4ubvNV fp_glVertexAttribs4ubvNV;

 /* GL_NV_vertex_program1_1 */
extern GLboolean GLAD_NV_vertex_program1_1;

 /* GL_NV_vertex_program2 */
extern GLboolean GLAD_NV_vertex_program2;

 /* GL_NV_vertex_program2_option */
extern GLboolean GLAD_NV_vertex_program2_option;

 /* GL_NV_vertex_program3 */
extern GLboolean GLAD_NV_vertex_program3;

 /* GL_NV_vertex_program4 */
extern GLboolean GLAD_NV_vertex_program4;
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER_NV      0x88FD
typedef void (APIENTRYP pfn_glVertexAttribI1iEXT) (GLuint, GLint);
extern pfn_glVertexAttribI1iEXT fp_glVertexAttribI1iEXT;
typedef void (APIENTRYP pfn_glVertexAttribI2iEXT) (GLuint, GLint, GLint);
extern pfn_glVertexAttribI2iEXT fp_glVertexAttribI2iEXT;
typedef void (APIENTRYP pfn_glVertexAttribI3iEXT) (GLuint, GLint, GLint, GLint);
extern pfn_glVertexAttribI3iEXT fp_glVertexAttribI3iEXT;
typedef void (APIENTRYP pfn_glVertexAttribI4iEXT) (GLuint, GLint, GLint, GLint, GLint);
extern pfn_glVertexAttribI4iEXT fp_glVertexAttribI4iEXT;
typedef void (APIENTRYP pfn_glVertexAttribI1uiEXT) (GLuint, GLuint);
extern pfn_glVertexAttribI1uiEXT fp_glVertexAttribI1uiEXT;
typedef void (APIENTRYP pfn_glVertexAttribI2uiEXT) (GLuint, GLuint, GLuint);
extern pfn_glVertexAttribI2uiEXT fp_glVertexAttribI2uiEXT;
typedef void (APIENTRYP pfn_glVertexAttribI3uiEXT) (GLuint, GLuint, GLuint, GLuint);
extern pfn_glVertexAttribI3uiEXT fp_glVertexAttribI3uiEXT;
typedef void (APIENTRYP pfn_glVertexAttribI4uiEXT) (GLuint, GLuint, GLuint, GLuint, GLuint);
extern pfn_glVertexAttribI4uiEXT fp_glVertexAttribI4uiEXT;
typedef void (APIENTRYP pfn_glVertexAttribI1ivEXT) (GLuint, const GLint*);
extern pfn_glVertexAttribI1ivEXT fp_glVertexAttribI1ivEXT;
typedef void (APIENTRYP pfn_glVertexAttribI2ivEXT) (GLuint, const GLint*);
extern pfn_glVertexAttribI2ivEXT fp_glVertexAttribI2ivEXT;
typedef void (APIENTRYP pfn_glVertexAttribI3ivEXT) (GLuint, const GLint*);
extern pfn_glVertexAttribI3ivEXT fp_glVertexAttribI3ivEXT;
typedef void (APIENTRYP pfn_glVertexAttribI4ivEXT) (GLuint, const GLint*);
extern pfn_glVertexAttribI4ivEXT fp_glVertexAttribI4ivEXT;
typedef void (APIENTRYP pfn_glVertexAttribI1uivEXT) (GLuint, const GLuint*);
extern pfn_glVertexAttribI1uivEXT fp_glVertexAttribI1uivEXT;
typedef void (APIENTRYP pfn_glVertexAttribI2uivEXT) (GLuint, const GLuint*);
extern pfn_glVertexAttribI2uivEXT fp_glVertexAttribI2uivEXT;
typedef void (APIENTRYP pfn_glVertexAttribI3uivEXT) (GLuint, const GLuint*);
extern pfn_glVertexAttribI3uivEXT fp_glVertexAttribI3uivEXT;
typedef void (APIENTRYP pfn_glVertexAttribI4uivEXT) (GLuint, const GLuint*);
extern pfn_glVertexAttribI4uivEXT fp_glVertexAttribI4uivEXT;
typedef void (APIENTRYP pfn_glVertexAttribI4bvEXT) (GLuint, const GLbyte*);
extern pfn_glVertexAttribI4bvEXT fp_glVertexAttribI4bvEXT;
typedef void (APIENTRYP pfn_glVertexAttribI4svEXT) (GLuint, const GLshort*);
extern pfn_glVertexAttribI4svEXT fp_glVertexAttribI4svEXT;
typedef void (APIENTRYP pfn_glVertexAttribI4ubvEXT) (GLuint, const GLubyte*);
extern pfn_glVertexAttribI4ubvEXT fp_glVertexAttribI4ubvEXT;
typedef void (APIENTRYP pfn_glVertexAttribI4usvEXT) (GLuint, const GLushort*);
extern pfn_glVertexAttribI4usvEXT fp_glVertexAttribI4usvEXT;
typedef void (APIENTRYP pfn_glVertexAttribIPointerEXT) (GLuint, GLint, GLenum, GLsizei, const void*);
extern pfn_glVertexAttribIPointerEXT fp_glVertexAttribIPointerEXT;
typedef void (APIENTRYP pfn_glGetVertexAttribIivEXT) (GLuint, GLenum, GLint*);
extern pfn_glGetVertexAttribIivEXT fp_glGetVertexAttribIivEXT;
typedef void (APIENTRYP pfn_glGetVertexAttribIuivEXT) (GLuint, GLenum, GLuint*);
extern pfn_glGetVertexAttribIuivEXT fp_glGetVertexAttribIuivEXT;

 /* GL_NV_video_capture */
extern GLboolean GLAD_NV_video_capture;
#define GL_VIDEO_BUFFER_NV                     0x9020
#define GL_VIDEO_BUFFER_BINDING_NV             0x9021
#define GL_FIELD_UPPER_NV                      0x9022
#define GL_FIELD_LOWER_NV                      0x9023
#define GL_NUM_VIDEO_CAPTURE_STREAMS_NV        0x9024
#define GL_NEXT_VIDEO_CAPTURE_BUFFER_STATUS_NV  0x9025
#define GL_VIDEO_CAPTURE_TO_422_SUPPORTED_NV   0x9026
#define GL_LAST_VIDEO_CAPTURE_STATUS_NV        0x9027
#define GL_VIDEO_BUFFER_PITCH_NV               0x9028
#define GL_VIDEO_COLOR_CONVERSION_MATRIX_NV    0x9029
#define GL_VIDEO_COLOR_CONVERSION_MAX_NV       0x902A
#define GL_VIDEO_COLOR_CONVERSION_MIN_NV       0x902B
#define GL_VIDEO_COLOR_CONVERSION_OFFSET_NV    0x902C
#define GL_VIDEO_BUFFER_INTERNAL_FORMAT_NV     0x902D
#define GL_PARTIAL_SUCCESS_NV                  0x902E
#define GL_SUCCESS_NV                          0x902F
#define GL_FAILURE_NV                          0x9030
#define GL_YCBYCR8_422_NV                      0x9031
#define GL_YCBAYCR8A_4224_NV                   0x9032
#define GL_Z6Y10Z6CB10Z6Y10Z6CR10_422_NV       0x9033
#define GL_Z6Y10Z6CB10Z6A10Z6Y10Z6CR10Z6A10_4224_NV  0x9034
#define GL_Z4Y12Z4CB12Z4Y12Z4CR12_422_NV       0x9035
#define GL_Z4Y12Z4CB12Z4A12Z4Y12Z4CR12Z4A12_4224_NV  0x9036
#define GL_Z4Y12Z4CB12Z4CR12_444_NV            0x9037
#define GL_VIDEO_CAPTURE_FRAME_WIDTH_NV        0x9038
#define GL_VIDEO_CAPTURE_FRAME_HEIGHT_NV       0x9039
#define GL_VIDEO_CAPTURE_FIELD_UPPER_HEIGHT_NV  0x903A
#define GL_VIDEO_CAPTURE_FIELD_LOWER_HEIGHT_NV  0x903B
#define GL_VIDEO_CAPTURE_SURFACE_ORIGIN_NV     0x903C
typedef void (APIENTRYP pfn_glBeginVideoCaptureNV) (GLuint);
extern pfn_glBeginVideoCaptureNV fp_glBeginVideoCaptureNV;
typedef void (APIENTRYP pfn_glBindVideoCaptureStreamBufferNV) (GLuint, GLuint, GLenum, GLintptrARB);
extern pfn_glBindVideoCaptureStreamBufferNV fp_glBindVideoCaptureStreamBufferNV;
typedef void (APIENTRYP pfn_glBindVideoCaptureStreamTextureNV) (GLuint, GLuint, GLenum, GLenum, GLuint);
extern pfn_glBindVideoCaptureStreamTextureNV fp_glBindVideoCaptureStreamTextureNV;
typedef void (APIENTRYP pfn_glEndVideoCaptureNV) (GLuint);
extern pfn_glEndVideoCaptureNV fp_glEndVideoCaptureNV;
typedef void (APIENTRYP pfn_glGetVideoCaptureivNV) (GLuint, GLenum, GLint*);
extern pfn_glGetVideoCaptureivNV fp_glGetVideoCaptureivNV;
typedef void (APIENTRYP pfn_glGetVideoCaptureStreamivNV) (GLuint, GLuint, GLenum, GLint*);
extern pfn_glGetVideoCaptureStreamivNV fp_glGetVideoCaptureStreamivNV;
typedef void (APIENTRYP pfn_glGetVideoCaptureStreamfvNV) (GLuint, GLuint, GLenum, GLfloat*);
extern pfn_glGetVideoCaptureStreamfvNV fp_glGetVideoCaptureStreamfvNV;
typedef void (APIENTRYP pfn_glGetVideoCaptureStreamdvNV) (GLuint, GLuint, GLenum, GLdouble*);
extern pfn_glGetVideoCaptureStreamdvNV fp_glGetVideoCaptureStreamdvNV;
typedef GLenum (APIENTRYP pfn_glVideoCaptureNV) (GLuint, GLuint*, GLuint64EXT*);
extern pfn_glVideoCaptureNV fp_glVideoCaptureNV;
typedef void (APIENTRYP pfn_glVideoCaptureStreamParameterivNV) (GLuint, GLuint, GLenum, const GLint*);
extern pfn_glVideoCaptureStreamParameterivNV fp_glVideoCaptureStreamParameterivNV;
typedef void (APIENTRYP pfn_glVideoCaptureStreamParameterfvNV) (GLuint, GLuint, GLenum, const GLfloat*);
extern pfn_glVideoCaptureStreamParameterfvNV fp_glVideoCaptureStreamParameterfvNV;
typedef void (APIENTRYP pfn_glVideoCaptureStreamParameterdvNV) (GLuint, GLuint, GLenum, const GLdouble*);
extern pfn_glVideoCaptureStreamParameterdvNV fp_glVideoCaptureStreamParameterdvNV;

 /* GL_NVX_conditional_render */
extern GLboolean GLAD_NVX_conditional_render;
typedef void (APIENTRYP pfn_glBeginConditionalRenderNVX) (GLuint);
extern pfn_glBeginConditionalRenderNVX fp_glBeginConditionalRenderNVX;
typedef void (APIENTRYP pfn_glEndConditionalRenderNVX) ();
extern pfn_glEndConditionalRenderNVX fp_glEndConditionalRenderNVX;

 /* GL_OML_interlace */
extern GLboolean GLAD_OML_interlace;
#define GL_INTERLACE_OML                       0x8980
#define GL_INTERLACE_READ_OML                  0x8981

 /* GL_OML_resample */
extern GLboolean GLAD_OML_resample;
#define GL_PACK_RESAMPLE_OML                   0x8984
#define GL_UNPACK_RESAMPLE_OML                 0x8985
#define GL_RESAMPLE_REPLICATE_OML              0x8986
#define GL_RESAMPLE_ZERO_FILL_OML              0x8987
#define GL_RESAMPLE_AVERAGE_OML                0x8988
#define GL_RESAMPLE_DECIMATE_OML               0x8989

 /* GL_OML_subsample */
extern GLboolean GLAD_OML_subsample;
#define GL_FORMAT_SUBSAMPLE_24_24_OML          0x8982
#define GL_FORMAT_SUBSAMPLE_244_244_OML        0x8983

 /* GL_PGI_misc_hints */
extern GLboolean GLAD_PGI_misc_hints;
#define GL_PREFER_DOUBLEBUFFER_HINT_PGI        0x1A1F8
#define GL_CONSERVE_MEMORY_HINT_PGI            0x1A1FD
#define GL_RECLAIM_MEMORY_HINT_PGI             0x1A1FE
#define GL_NATIVE_GRAPHICS_HANDLE_PGI          0x1A202
#define GL_NATIVE_GRAPHICS_BEGIN_HINT_PGI      0x1A203
#define GL_NATIVE_GRAPHICS_END_HINT_PGI        0x1A204
#define GL_ALWAYS_FAST_HINT_PGI                0x1A20C
#define GL_ALWAYS_SOFT_HINT_PGI                0x1A20D
#define GL_ALLOW_DRAW_OBJ_HINT_PGI             0x1A20E
#define GL_ALLOW_DRAW_WIN_HINT_PGI             0x1A20F
#define GL_ALLOW_DRAW_FRG_HINT_PGI             0x1A210
#define GL_ALLOW_DRAW_MEM_HINT_PGI             0x1A211
#define GL_STRICT_DEPTHFUNC_HINT_PGI           0x1A216
#define GL_STRICT_LIGHTING_HINT_PGI            0x1A217
#define GL_STRICT_SCISSOR_HINT_PGI             0x1A218
#define GL_FULL_STIPPLE_HINT_PGI               0x1A219
#define GL_CLIP_NEAR_HINT_PGI                  0x1A220
#define GL_CLIP_FAR_HINT_PGI                   0x1A221
#define GL_WIDE_LINE_HINT_PGI                  0x1A222
#define GL_BACK_NORMALS_HINT_PGI               0x1A223
typedef void (APIENTRYP pfn_glHintPGI) (GLenum, GLint);
extern pfn_glHintPGI fp_glHintPGI;

 /* GL_PGI_vertex_hints */
extern GLboolean GLAD_PGI_vertex_hints;
#define GL_VERTEX_DATA_HINT_PGI                0x1A22A
#define GL_VERTEX_CONSISTENT_HINT_PGI          0x1A22B
#define GL_MATERIAL_SIDE_HINT_PGI              0x1A22C
#define GL_MAX_VERTEX_HINT_PGI                 0x1A22D
#define GL_COLOR3_BIT_PGI                      0x00010000
#define GL_COLOR4_BIT_PGI                      0x00020000
#define GL_EDGEFLAG_BIT_PGI                    0x00040000
#define GL_INDEX_BIT_PGI                       0x00080000
#define GL_MAT_AMBIENT_BIT_PGI                 0x00100000
#define GL_MAT_AMBIENT_AND_DIFFUSE_BIT_PGI     0x00200000
#define GL_MAT_DIFFUSE_BIT_PGI                 0x00400000
#define GL_MAT_EMISSION_BIT_PGI                0x00800000
#define GL_MAT_COLOR_INDEXES_BIT_PGI           0x01000000
#define GL_MAT_SHININESS_BIT_PGI               0x02000000
#define GL_MAT_SPECULAR_BIT_PGI                0x04000000
#define GL_NORMAL_BIT_PGI                      0x08000000
#define GL_TEXCOORD1_BIT_PGI                   0x10000000
#define GL_TEXCOORD2_BIT_PGI                   0x20000000
#define GL_TEXCOORD3_BIT_PGI                   0x40000000
#define GL_TEXCOORD4_BIT_PGI                   0x80000000
#define GL_VERTEX23_BIT_PGI                    0x00000004
#define GL_VERTEX4_BIT_PGI                     0x00000008

 /* GL_QCOM_alpha_test */
extern GLboolean GLAD_QCOM_alpha_test;
#define GL_ALPHA_TEST_QCOM                     0x0BC0
#define GL_ALPHA_TEST_FUNC_QCOM                0x0BC1
#define GL_ALPHA_TEST_REF_QCOM                 0x0BC2
typedef void (APIENTRYP pfn_glAlphaFuncQCOM) (GLenum, GLclampf);
extern pfn_glAlphaFuncQCOM fp_glAlphaFuncQCOM;

 /* GL_QCOM_binning_control */
extern GLboolean GLAD_QCOM_binning_control;
#define GL_BINNING_CONTROL_HINT_QCOM           0x8FB0
#define GL_CPU_OPTIMIZED_QCOM                  0x8FB1
#define GL_GPU_OPTIMIZED_QCOM                  0x8FB2
#define GL_RENDER_DIRECT_TO_FRAMEBUFFER_QCOM   0x8FB3

 /* GL_QCOM_driver_control */
extern GLboolean GLAD_QCOM_driver_control;
typedef void (APIENTRYP pfn_glGetDriverControlsQCOM) (GLint*, GLsizei, GLuint*);
extern pfn_glGetDriverControlsQCOM fp_glGetDriverControlsQCOM;
typedef void (APIENTRYP pfn_glGetDriverControlStringQCOM) (GLuint, GLsizei, GLsizei*, GLchar*);
extern pfn_glGetDriverControlStringQCOM fp_glGetDriverControlStringQCOM;
typedef void (APIENTRYP pfn_glEnableDriverControlQCOM) (GLuint);
extern pfn_glEnableDriverControlQCOM fp_glEnableDriverControlQCOM;
typedef void (APIENTRYP pfn_glDisableDriverControlQCOM) (GLuint);
extern pfn_glDisableDriverControlQCOM fp_glDisableDriverControlQCOM;

 /* GL_QCOM_extended_get */
extern GLboolean GLAD_QCOM_extended_get;
#define GL_TEXTURE_WIDTH_QCOM                  0x8BD2
#define GL_TEXTURE_HEIGHT_QCOM                 0x8BD3
#define GL_TEXTURE_DEPTH_QCOM                  0x8BD4
#define GL_TEXTURE_INTERNAL_FORMAT_QCOM        0x8BD5
#define GL_TEXTURE_FORMAT_QCOM                 0x8BD6
#define GL_TEXTURE_TYPE_QCOM                   0x8BD7
#define GL_TEXTURE_IMAGE_VALID_QCOM            0x8BD8
#define GL_TEXTURE_NUM_LEVELS_QCOM             0x8BD9
#define GL_TEXTURE_TARGET_QCOM                 0x8BDA
#define GL_TEXTURE_OBJECT_VALID_QCOM           0x8BDB
#define GL_STATE_RESTORE                       0x8BDC
typedef void (APIENTRYP pfn_glExtGetTexturesQCOM) (GLuint*, GLint, GLint*);
extern pfn_glExtGetTexturesQCOM fp_glExtGetTexturesQCOM;
typedef void (APIENTRYP pfn_glExtGetBuffersQCOM) (GLuint*, GLint, GLint*);
extern pfn_glExtGetBuffersQCOM fp_glExtGetBuffersQCOM;
typedef void (APIENTRYP pfn_glExtGetRenderbuffersQCOM) (GLuint*, GLint, GLint*);
extern pfn_glExtGetRenderbuffersQCOM fp_glExtGetRenderbuffersQCOM;
typedef void (APIENTRYP pfn_glExtGetFramebuffersQCOM) (GLuint*, GLint, GLint*);
extern pfn_glExtGetFramebuffersQCOM fp_glExtGetFramebuffersQCOM;
typedef void (APIENTRYP pfn_glExtGetTexLevelParameterivQCOM) (GLuint, GLenum, GLint, GLenum, GLint*);
extern pfn_glExtGetTexLevelParameterivQCOM fp_glExtGetTexLevelParameterivQCOM;
typedef void (APIENTRYP pfn_glExtTexObjectStateOverrideiQCOM) (GLenum, GLenum, GLint);
extern pfn_glExtTexObjectStateOverrideiQCOM fp_glExtTexObjectStateOverrideiQCOM;
typedef void (APIENTRYP pfn_glExtGetTexSubImageQCOM) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, void*);
extern pfn_glExtGetTexSubImageQCOM fp_glExtGetTexSubImageQCOM;
typedef void (APIENTRYP pfn_glExtGetBufferPointervQCOM) (GLenum, void**);
extern pfn_glExtGetBufferPointervQCOM fp_glExtGetBufferPointervQCOM;

 /* GL_QCOM_extended_get2 */
extern GLboolean GLAD_QCOM_extended_get2;
typedef void (APIENTRYP pfn_glExtGetShadersQCOM) (GLuint*, GLint, GLint*);
extern pfn_glExtGetShadersQCOM fp_glExtGetShadersQCOM;
typedef void (APIENTRYP pfn_glExtGetProgramsQCOM) (GLuint*, GLint, GLint*);
extern pfn_glExtGetProgramsQCOM fp_glExtGetProgramsQCOM;
typedef GLboolean (APIENTRYP pfn_glExtIsProgramBinaryQCOM) (GLuint);
extern pfn_glExtIsProgramBinaryQCOM fp_glExtIsProgramBinaryQCOM;
typedef void (APIENTRYP pfn_glExtGetProgramBinarySourceQCOM) (GLuint, GLenum, GLchar*, GLint*);
extern pfn_glExtGetProgramBinarySourceQCOM fp_glExtGetProgramBinarySourceQCOM;

 /* GL_QCOM_perfmon_global_mode */
extern GLboolean GLAD_QCOM_perfmon_global_mode;
#define GL_PERFMON_GLOBAL_MODE_QCOM            0x8FA0

 /* GL_QCOM_tiled_rendering */
extern GLboolean GLAD_QCOM_tiled_rendering;
#define GL_COLOR_BUFFER_BIT0_QCOM              0x00000001
#define GL_COLOR_BUFFER_BIT1_QCOM              0x00000002
#define GL_COLOR_BUFFER_BIT2_QCOM              0x00000004
#define GL_COLOR_BUFFER_BIT3_QCOM              0x00000008
#define GL_COLOR_BUFFER_BIT4_QCOM              0x00000010
#define GL_COLOR_BUFFER_BIT5_QCOM              0x00000020
#define GL_COLOR_BUFFER_BIT6_QCOM              0x00000040
#define GL_COLOR_BUFFER_BIT7_QCOM              0x00000080
#define GL_DEPTH_BUFFER_BIT0_QCOM              0x00000100
#define GL_DEPTH_BUFFER_BIT1_QCOM              0x00000200
#define GL_DEPTH_BUFFER_BIT2_QCOM              0x00000400
#define GL_DEPTH_BUFFER_BIT3_QCOM              0x00000800
#define GL_DEPTH_BUFFER_BIT4_QCOM              0x00001000
#define GL_DEPTH_BUFFER_BIT5_QCOM              0x00002000
#define GL_DEPTH_BUFFER_BIT6_QCOM              0x00004000
#define GL_DEPTH_BUFFER_BIT7_QCOM              0x00008000
#define GL_STENCIL_BUFFER_BIT0_QCOM            0x00010000
#define GL_STENCIL_BUFFER_BIT1_QCOM            0x00020000
#define GL_STENCIL_BUFFER_BIT2_QCOM            0x00040000
#define GL_STENCIL_BUFFER_BIT3_QCOM            0x00080000
#define GL_STENCIL_BUFFER_BIT4_QCOM            0x00100000
#define GL_STENCIL_BUFFER_BIT5_QCOM            0x00200000
#define GL_STENCIL_BUFFER_BIT6_QCOM            0x00400000
#define GL_STENCIL_BUFFER_BIT7_QCOM            0x00800000
#define GL_MULTISAMPLE_BUFFER_BIT0_QCOM        0x01000000
#define GL_MULTISAMPLE_BUFFER_BIT1_QCOM        0x02000000
#define GL_MULTISAMPLE_BUFFER_BIT2_QCOM        0x04000000
#define GL_MULTISAMPLE_BUFFER_BIT3_QCOM        0x08000000
#define GL_MULTISAMPLE_BUFFER_BIT4_QCOM        0x10000000
#define GL_MULTISAMPLE_BUFFER_BIT5_QCOM        0x20000000
#define GL_MULTISAMPLE_BUFFER_BIT6_QCOM        0x40000000
#define GL_MULTISAMPLE_BUFFER_BIT7_QCOM        0x80000000
typedef void (APIENTRYP pfn_glStartTilingQCOM) (GLuint, GLuint, GLuint, GLuint, GLbitfield);
extern pfn_glStartTilingQCOM fp_glStartTilingQCOM;
typedef void (APIENTRYP pfn_glEndTilingQCOM) (GLbitfield);
extern pfn_glEndTilingQCOM fp_glEndTilingQCOM;

 /* GL_QCOM_writeonly_rendering */
extern GLboolean GLAD_QCOM_writeonly_rendering;
#define GL_WRITEONLY_RENDERING_QCOM            0x8823

 /* GL_REND_screen_coordinates */
extern GLboolean GLAD_REND_screen_coordinates;
#define GL_SCREEN_COORDINATES_REND             0x8490
#define GL_INVERTED_SCREEN_W_REND              0x8491

 /* GL_S3_s3tc */
extern GLboolean GLAD_S3_s3tc;
#define GL_RGB_S3TC                            0x83A0
#define GL_RGB4_S3TC                           0x83A1
#define GL_RGBA_S3TC                           0x83A2
#define GL_RGBA4_S3TC                          0x83A3
#define GL_RGBA_DXT5_S3TC                      0x83A4
#define GL_RGBA4_DXT5_S3TC                     0x83A5

 /* GL_SGIS_generate_mipmap */
extern GLboolean GLAD_SGIS_generate_mipmap;
#define GL_GENERATE_MIPMAP_SGIS                0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS           0x8192

 /* GL_SGIX_texture_lod_bias */
extern GLboolean GLAD_SGIX_texture_lod_bias;
#define GL_TEXTURE_LOD_BIAS_S_SGIX             0x818E
#define GL_TEXTURE_LOD_BIAS_T_SGIX             0x818F
#define GL_TEXTURE_LOD_BIAS_R_SGIX             0x8190

 /* GL_VIV_shader_binary */
extern GLboolean GLAD_VIV_shader_binary;
#define GL_SHADER_BINARY_VIV                   0x8FC4

} /* namespace glad */

#endif /* __glad_hpp_ */
