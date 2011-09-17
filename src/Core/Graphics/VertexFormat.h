/* 
 * File:   VertexFormat.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 9:42 PM
 */

#ifndef GRAPHICS_VERTEXFORMAT_H
#define	GRAPHICS_VERTEXFORMAT_H

namespace Graphics
{

    class VertexFormat
    {
    public:
        VertexFormat();
        ~VertexFormat();
        
        const unsigned int vertexSize() const;
    };
}

#endif	/* GRAPHICS_VERTEXFORMAT_H */

