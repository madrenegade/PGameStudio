#ifndef RENDERER_ERRORHANDLER_H
#define RENDERER_ERRORHANDLER_H

namespace Renderer
{

    class ErrorHandler
    {
    public:
        static void checkForErrors();

    private:
        ErrorHandler();
        ~ErrorHandler();
    };
} // namespace Systems

#endif // RENDERER_ERRORHANDLER_H
