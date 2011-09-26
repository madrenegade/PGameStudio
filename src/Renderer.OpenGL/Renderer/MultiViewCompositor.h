/* 
 * File:   MultiViewCompositor.h
 * Author: madrenegade
 *
 * Created on September 26, 2011, 7:58 PM
 */

#ifndef RENDERER_MULTIVIEWCOMPOSITOR_H
#define	RENDERER_MULTIVIEWCOMPOSITOR_H

namespace Renderer
{

    class MultiViewCompositor
    {
    public:
        virtual ~MultiViewCompositor();
        
        virtual void startCompose() const = 0;
        virtual void endCompose() const = 0;

    protected:
        MultiViewCompositor();
    };
}

#endif	/* RENDERER_MULTIVIEWCOMPOSITOR_H */

