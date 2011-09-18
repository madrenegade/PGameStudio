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
                     ptrdiff_t normalOffset = 0, size_t normalSize = 0,
                     ptrdiff_t tangentOffset = 0, size_t tangentSize = 0,
                     ptrdiff_t bitangentOffset = 0, size_t bitangentSize = 0);

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

        bool hasTangent() const;
        const ptrdiff_t getTangentOffset() const;
        const size_t getTangentSize() const;

        bool hasBitangent() const;
        const ptrdiff_t getBitangentOffset() const;
        const size_t getBitangentSize() const;

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

        template<typename VertexType>
        static VertexFormat forTNBT()
        {
            return VertexFormat(sizeof (VertexType),
                                offsetof(VertexType, position), sizeof (VertexType::position),
                                offsetof(VertexType, texcoords), sizeof (VertexType::texcoords),
                                offsetof(VertexType, normal), sizeof (VertexType::normal),
                                offsetof(VertexType, tangent), sizeof (VertexType::tangent),
                                offsetof(VertexType, bitangent), sizeof (VertexType::bitangent));
        }

    private:
        size_t vertexSize;

        ptrdiff_t positionOffset;
        size_t positionSize;

        ptrdiff_t texCoordOffset;
        size_t texCoordSize;

        ptrdiff_t normalOffset;
        size_t normalSize;

        ptrdiff_t tangentOffset;
        size_t tangentSize;

        ptrdiff_t bitangentOffset;
        size_t bitangentSize;
    };
}

#endif	/* GRAPHICS_VERTEXFORMAT_H */

