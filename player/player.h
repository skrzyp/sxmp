#ifndef xmp_wrapper_h_INCLUDED
#define xmp_wrapper_h_INCLUDED
#include <xmp.h>

extern xmp_context context;
extern struct xmp_frame_info frame_info;
extern struct xmp_module_info module_info;

extern void   module_init(                           );
extern void   module_load(char* path                 );
extern void   module_play(                           );
extern int    module_fill_buffer(                    );
extern int    module_is_played(                      );
extern int    module_get_frame(void* buffer, int size);
extern int*   module_get_buffer(                     );
extern int    module_get_buffer_size(                );
extern char*  module_get_title(                      );
extern int    module_get_position(                   );
extern int    module_get_duration(                   );
extern char*  module_get_type(                       );
extern char*  module_get_author(                     );
extern void   module_deinit(                         );

#endif

