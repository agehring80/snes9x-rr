#ifndef __GTK_DISPLAY_DRIVER_OPENGL_H
#define __GTK_DISPLAY_DRIVER_OPENGL_H

#include "gtk_s9x.h"
#include "gtk_display_driver.h"

#include <epoxy/gl.h>

#include "gtk_opengl_context.h"
#ifdef GDK_WINDOWING_X11
#include "gtk_glx_context.h"
#endif
#ifdef GDK_WINDOWING_WAYLAND
#include "gtk_wayland_egl_context.h"
#endif

#include "shaders/glsl.h"

#define BUFFER_OFFSET(i)             ((char *) NULL + (i))

class S9xOpenGLDisplayDriver : public S9xDisplayDriver
{
    public:
        S9xOpenGLDisplayDriver (Snes9xWindow *window, Snes9xConfig *config);
        void refresh (int width, int height);
        int init ();
        void deinit ();
        void clear_buffers ();
        void update (int width, int height, int yoffset);
        uint16 *get_next_buffer ();
        uint16 *get_current_buffer ();
        void push_buffer (uint16 *src);
        void *get_parameters ();
        void save (const char *filename);
        static int query_availability ();

    private:
        int opengl_defaults ();
        void swap_buffers ();
        int pbos_available ();
        int shaders_available ();
        int load_shaders (const char *);
        void update_texture_size (int width, int height);
        int init_gl ();
        void resize ();

        GLint                    texture_width;
        GLint                    texture_height;
        GLfloat                  vertices[8];
        GLfloat                  texcoords[8];
        GLuint                   texmap;
        GLuint                   pbo;
        GLuint                   program;
        GLuint                   fragment_shader;
        GLuint                   vertex_shader;

        int                      dyn_resizing;
        int                      using_pbos;
        int                      using_shaders;
        int                      initialized;

        int                      using_glsl_shaders;
        GLSLShader               *glsl_shader;

        GdkWindow                *gdk_window;
        int                      output_window_width;
        int                      output_window_height;

        OpenGLContext            *context;

#ifdef GDK_WINDOWING_X11
        GTKGLXContext            glx;
#endif
#ifdef GDK_WINDOWING_WAYLAND
        WaylandEGLContext        wl;
#endif
};

#endif /* __GTK_DISPLAY_DRIVER_OPENGL_H */
