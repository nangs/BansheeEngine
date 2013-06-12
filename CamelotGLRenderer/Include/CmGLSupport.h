/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2011 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef OGRE_GLSUPPORT_H
#define OGRE_GLSUPPORT_H

#include "CmGLPrerequisites.h"
#include "CmGLRenderSystem.h"

#include "CmRenderWindow.h"

namespace CamelotFramework
{
    
class CM_RSGL_EXPORT GLSupport
{
public:
    GLSupport() { }
    virtual ~GLSupport() { }

	virtual RenderWindowPtr newWindow(RENDER_WINDOW_DESC& desc, RenderWindowPtr parentWindow) = 0;

    virtual bool supportsPBuffers();

    /**
    * Start anything special
    */
    virtual void start() = 0;
    /**
    * Stop anything special
    */
    virtual void stop() = 0;

    /**
    * Get vendor information
    */
    const String& getGLVendor(void) const
    {
        return mVendor;
    }

    /**
    * Get version information
    */
    const String& getGLVersion(void) const
    {
        return mVersion;
    }

    /**
    * Compare GL version numbers
    */
    bool checkMinGLVersion(const String& v) const;

    /**
    * Check if an extension is available
    */
    virtual bool checkExtension(const String& ext) const;
    /**
    * Get the address of a function
    */
    virtual void* getProcAddress(const String& procname) = 0;

    /** Initialises GL extensions, must be done AFTER the GL context has been
        established.
    */
    virtual void initialiseExtensions();

	/// @copydoc RenderSystem::getDisplayMonitorCount
	virtual unsigned int getDisplayMonitorCount() const
	{
		return 1;
	}

protected:

	// This contains the complete list of supported extensions
    Set<String>::type extensionList;
private:
    String mVersion;
    String mVendor;

}; // class GLSupport

}; // namespace CamelotFramework

#endif 
