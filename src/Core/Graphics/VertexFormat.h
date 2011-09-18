/* 
 * File:   VertexFormat.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 9:42 PM
 */

#ifndef GRAPHICS_VERTEXFORMAT_H
#define	GRAPHICS_VERTEXFORMAT_H

#include <cstddef>

namespace Graphics
{

    class VertexFormat
    {
    public:
        VertexFormat(size_t vertexSize = 0,
                     ptrdiff_t positionOffset = 0, size_t positionSize = 0,
                     ptrdiff_t texCoordOffset = 0, size_t texCoordSize = 0,
                     ptrdiff_t normalOffset = 0, size_t normalSize = 0);
        
        ~VertexFormat();

        const size_t getVertexSize() const;

        const ptrdiff_t getPositionOffset() const;
        const size_t getPositionSize() const;

        bool hasTexCoords() const;
        const ptrdiff_t getTexCoordOffset() const;
        const size_t getTexCoordSize() const;

        bool hasNormal() const;
        const ptrdiff_t getNormalOffset() const;
        const size_t getNormalSize() const;

        template<typename VertexType>
        static VertexFormat forTexturedVertex()
        {
            return VertexFormat(sizeof (VertexType),
                                offsetof(VertexType, position), sizeof (VertexType::position),
                                offsetof(VertexType, texcoords), sizeof (VertexType::texcoords));
        }

        template<typename VertexType>
        static VertexFormat forTexturedVertexWithNormal()
        {
            return VertexFormat(sizeof (VertexType),
                                offsetof(VertexType, position), sizeof (VertexType::position),
                                offsetof(VertexType, texcoords), sizeof (VertexType::texcoords),
                                offsetof(VertexType, normal), sizeof (VertexType::normal));
        }

    private:
        size_t vertexSize;

        ptrdiff_t positionOffset;
        size_t positionSize;

        ptrdiff_t texCoordOffset;
        size_t texCoordSize;

        ptrdiff_t normalOffset;
        size_t normalSize;
    };
}

#endif	/* GRAPHICS_VERTEXFORMAT_H */

