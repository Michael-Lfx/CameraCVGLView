#ifndef NV_RENDERER_H_
#define NV_RENDERER_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <condition_variable>

namespace nv
{
    class NVApp;
    namespace render
    {
        class NVCameraBackground;
        class NVRenderer
        {
        public:
            NVRenderer(NVApp *app);
            ~NVRenderer();

            void Resume();

            void Pause();

            void Destroy();

            void SetWindow(ANativeWindow* window);

            void FlipBackground(bool flip);

            void NotifyCameraReady();

            GLuint GetSurfaceTextureId(){return surface_texture_id_;}

            void CheckGlError(const char *op);

            GLuint LoaderShader(GLenum shader_type, const char* source);
            GLuint CreateProgram(const char* vertex_source, const char* fragment_source);

            void _Run();

        protected:
            bool Initialise();

            bool WindowRestore();

            bool WindowChanged();

            void CreateSurfaceTextureId();

            void ShutDown();

            void DrawFrame();

            void RenderBackground();

            void SwapBuffers();

        private:
            void _renderLoop();


        private:
            enum RenderMessage{
                MSG_NONE = 0,
                MSG_WINDOW_CREATE,
                MSG_WINDOW_UPDATE,
                MSG_WINDOW_DESTROY,
                MSG_LOOP_EXIT
            };


            NVApp             *app_;

            enum RenderMessage msg_;

            //Android Window
            ANativeWindow* window_;

            //EGL Resources
            EGLDisplay display_;
            EGLSurface surface_;
            EGLContext context_;
            EGLConfig  config_;

            NVCameraBackground *cam_background_;

            std::mutex msg_mut_;
            std::mutex win_mut_;
            std::condition_variable win_cond_;
            std::mutex gl_mut_;
            std::condition_variable gl_cond_;

            int width_;
            int height_;

            GLuint surface_texture_id_;
            bool flip_background_;

            bool window_init_;
            bool pause_;
            bool run_;

        };
    }
}


#endif