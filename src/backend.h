/*
 This is a part of pacmixer @ http://github.com/KenjiTakahashi/pacmixer
 Karol "Kenji Takahashi" Woźniak © 2012

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <pulse/pulseaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>


typedef struct CONTEXT {
    pa_threaded_mainloop *loop;
    pa_context *context;
    pa_context_state_t state;
} context_t;

typedef struct CALLBACK {
    void *add;
    void *update;
    void *remove;
    void *self;
} callback_t;

typedef struct BACKEND_CHANNEL {
    int maxLevel;
    int normLevel;
    int mutable;
} backend_channel_t;

typedef struct BACKEND_VOLUME {
    int level;
    int mute;
} backend_volume_t;

typedef struct CLIENT_CALLBACK {
    callback_t *callback;
    backend_channel_t *channels;
    backend_volume_t *volumes;
    uint8_t chnum;
    uint32_t index;
} client_callback_t;

typedef void (*tcallback_add_func)(void*, const char*, uint32_t, const backend_channel_t*, uint8_t);
typedef void (*tcallback_update_func)(void*, uint32_t, const backend_volume_t*, uint8_t);
typedef void (*tcallback_remove_func)(void*, uint32_t);

context_t *backend_new();
int backend_init(context_t*, callback_t*);
void backend_destroy(context_t*);

void _cb_state_changed(pa_context*, void*);
void _cb_client(pa_context*, const pa_client_info*, int, void*);
void _cb_sink(pa_context*, const pa_sink_info*, int, void*);
void _cb_u_sink(pa_context*, const pa_sink_info*, int, void*);
void _cb_sink_input(pa_context*, const pa_sink_input_info*, int, void*);
void _cb_u_sink_input(pa_context*, const pa_sink_input_info*, int, void*);
void _cb_event(pa_context*, pa_subscription_event_type_t, uint32_t, void*);
backend_channel_t *_do_channels(pa_cvolume, uint8_t chnum);
backend_volume_t *_do_volumes(pa_cvolume, uint8_t chnum, int mute);