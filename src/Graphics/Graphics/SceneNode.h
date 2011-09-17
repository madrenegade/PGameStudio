/* 
 * File:   SceneNode.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:11 AM
 */

#ifndef GRAPHICS_SCENENODE_H
#define	GRAPHICS_SCENENODE_H

namespace Graphics
{
    class Renderer;
    
    class SceneNode
    {
    public:
        virtual ~SceneNode();
        
        virtual void prepare(Renderer* renderer);
        
    protected:
        SceneNode();
    };
}

#endif	/* GRAPHICS_SCENENODE_H */

