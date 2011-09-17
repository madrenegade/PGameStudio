/* 
 * File:   Effect.cpp
 * Author: madrenegade
 * 
 * Created on September 17, 2011, 9:51 AM
 */

#include "Renderer/Effect.h"

#include <GL/glew.h>
#include <Cg/cgGL.h>
#include <stdexcept>
#include <glog/logging.h>


#include "Math/Matrix4.h"

namespace Renderer
{

    Effect::Effect()
    {
        context = cgCreateContext();

        if (context == 0)
        {
            throw std::runtime_error("Could not create context");
        }

        cgSetErrorHandler(CgErrorHandler, 0);

        cgGLRegisterStates(context);
        //        cgGLSetManageTextureParameters(context, true);
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

        modelViewProjection = cgGetEffectParameterBySemantic(effect, "ModelViewProjection");
        modelView = cgGetEffectParameterBySemantic(effect, "ModelView");

        const Math::Matrix4 projection = Math::Matrix4::CreatePerspectiveFieldOfView(3.1415 * 60.0 / 180.0, 16.0 / 9.0, 0.1, 100);
        const Math::Matrix4 view = Math::Matrix4::LookAt(Math::Vector3(0, 0, 0), Math::Vector3(0, 0, -1), Math::Vector3(0, 1, 0));

        const Math::Matrix4 mvp = view * projection;
        cgSetMatrixParameterdc(modelViewProjection, mvp);
        cgSetMatrixParameterdc(modelView, view);
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

    Effect::~Effect()
    {
        //        cgDestroyEffect(effect);
        //        cgDestroyContext(context);
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
