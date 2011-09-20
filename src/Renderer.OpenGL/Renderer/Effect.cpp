/* 
 * File:   Effect.cpp
 * Author: madrenegade
 * 
 * Created on September 17, 2011, 9:51 AM
 */

#include "Renderer/Effect.h"
#include "Renderer/Texture.h"

#include <GL/glew.h>
#include <Cg/cgGL.h>
#include <stdexcept>
#include <glog/logging.h>

#include "Math/Vector2.h"
#include "Math/Matrix4.h"

namespace Renderer
{
    CGcontext Effect::context = 0;
    
    Effect::Effect()
    {

    }
    
    Effect::Effect(const Effect& other)
    {
//        effect = cgCopyEffect(other.effect);
    }
    
    Effect::~Effect()
    {
//        cgDestroyEffect(effect);
    }

    void Effect::initialize()
    {
        context = cgCreateContext();

        if (context == 0)
        {
            throw std::runtime_error("Could not create context");
        }

        cgSetErrorHandler(CgErrorHandler, 0);

        cgGLRegisterStates(context);
        cgGLSetManageTextureParameters(context, true);
    }

    void Effect::deinitialize()
    {
        cgDestroyContext(context);
    }

    void Effect::load(const char* code)
    {
        effect = cgCreateEffect(context, code, 0);

        if (effect == 0)
        {
            throw std::runtime_error("Could not create effect");
        }

        technique = cgGetNamedTechnique(effect, "High");

        if (technique == 0)
        {
            throw std::runtime_error("Technique not found");
        }

        if (cgValidateTechnique(technique) == false)
        {
            throw std::runtime_error("Technique not valid");
        }
    }

    void Effect::set(const char* semantic, double d)
    {
        CGparameter parameter = cgGetEffectParameterBySemantic(effect, semantic);
        cgSetParameter1d(parameter, d);
    }

    void Effect::set(const char* semantic, const Math::Vector2& v)
    {
        CGparameter parameter = cgGetEffectParameterBySemantic(effect, semantic);
        cgSetParameter2d(parameter, v.X, v.Y);
    }

    void Effect::set(const char* semantic, const Math::Vector3& v)
    {
        CGparameter parameter = cgGetEffectParameterBySemantic(effect, semantic);
        cgSetParameter3d(parameter, v.X, v.Y, v.Z);
    }

    void Effect::set(const char* semantic, const Math::Vector4& v)
    {
        CGparameter parameter = cgGetEffectParameterBySemantic(effect, semantic);
        cgSetParameter4d(parameter, v.X, v.Y, v.Z, v.W);
    }

    void Effect::set(const char* semantic, const Math::Matrix4& matrix)
    {
        CGparameter parameter = cgGetEffectParameterBySemantic(effect, semantic);
        cgSetMatrixParameterdc(parameter, matrix);
    }

    void Effect::set(unsigned int level, const Texture* texture)
    {
        char semantic[] = {'T', 'E', 'X', static_cast<unsigned char> (level + 48), '\0'};

        CGparameter parameter = cgGetEffectParameterBySemantic(effect, semantic);
        cgGLSetTextureParameter(parameter, texture->getID());
    }

    void Effect::CgErrorHandler(CGcontext context, CGerror error, void* pData)
    {
        switch (error)
        {
            case CG_COMPILER_ERROR:
                LOG(FATAL) << cgGetErrorString(error) << std::endl << cgGetLastListing(context);
                break;

            default:
                LOG(FATAL) << cgGetErrorString(error);
                break;
        }

        throw std::runtime_error("CG ERROR");
    }

    

    void Effect::activate()
    {
        currentPass = cgGetFirstPass(technique);
        cgSetPassState(currentPass);
    }

    bool Effect::hasNextPass()
    {
        return currentPass != 0;
    }

    void Effect::gotoNextPass()
    {
        cgResetPassState(currentPass);

        currentPass = cgGetNextPass(currentPass);

        if (currentPass != 0)
        {
            cgSetPassState(currentPass);
        }
    }

    void Effect::deactivate()
    {
        //        cgResetPassState(currentPass);
    }
}
