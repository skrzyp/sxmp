#ifndef xmp_wrapper_h_INCLUDED
#define xmp_wrapper_h_INCLUDED
#include <xmp.h>

extern xmp_context context;
extern struct xmp_frame_info frame_info;
extern struct xmp_module_info module_info;

extern void   init_module(          );
extern int    status_module(        );
extern void   load_module(char* path);
extern void   play_module(          );
extern int    play_module_frame(    );
extern int    get_module_frame(     );
extern int*   get_module_buffer(    );
extern int    get_module_buffer_size();
extern char*  get_module_name(      );
extern void   deinit_module(        );

#endif 

