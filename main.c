#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif
#include <png.h>


#define false 0 
#define  true 1
#define bool unsigned char 
char* text = "Hello, world.";
int len = 5;

bool loadPngImage(char *name, int *outWidth, int *outHeight, bool *outHasAlpha, GLubyte **outData) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;
 
    if ((fp = fopen(name, "rb")) == NULL)
        return false;
 
    /* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                     NULL, NULL, NULL);
 
    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }
 
    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return false;
    }
 
    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return false;
    }
 
    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);
 
    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);
 
    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
 
    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);
    outWidth = (png_uint_32)(width);
    outHeight = &height;
 
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    *outData = (unsigned char*) malloc(row_bytes * outHeight);
 
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
 
    for (int i = 0; i < outHeight; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }
 
    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
 
    /* Close the file */
    fclose(fp);
 
    /* That's it */
    return true;
}

void display(void)
{

}
int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");

	glutDisplayFunc (display);
	//glutReshapeFunc (reshape);
	//glutKeyboardFunc (Keyboard);
	//glutMouseFunc (MouseButton);
	//glutMotionFunc (MouseMotion);
	//glutIdleFunc (AnimateScene);
	  // Get the initial time, for use by animation
	  /*
	#ifdef _WIN32
	  last_idle_time = GetTickCount();
	#else
	  gettimeofday (&last_idle_time, NULL);
	#endif
	 *
	*/
	glutMainLoop ();
	return 1;

}