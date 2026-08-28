// An audio-reactive bar visualizer written in pure SysY.
// It emits a 160x90, 15 FPS, YUV444 Y4M video stream to stdout.

const int WIDTH = 160;
const int HEIGHT = 90;
const int PIXELS = 14400;
const int FPS = 15;
const int FRAMES = 1029;
const int SAMPLE_RATE = 12000;
const int SAMPLES_PER_TICK = 5143;

const int BAR_COUNT = 24;
const int BAR_STEP = 6;
const int LEFT_MARGIN = 8;
const int BOTTOM_MARGIN = 8;

const int C = 40;
const int D = 42;
const int E = 44;
const int G = 47;
const int C0 = 28;
const int E0 = 32;
const int F0 = 33;
const int G0 = 35;
const int A0 = 37;
const int B0 = 39;

int ROOTS[8] = {C0, G0, A0, E0, F0, C0, F0, G0};
int THIRDS[8] = {E, B0, C, G0, A0, E0, A0, B0};
int FIFTHS[8] = {G, D, E, B0, C, G0, C, D};

int CANON_NOTES[96] = {
    E, E, E, E, D, D, D, D,
    C, C, C, C, B0, B0, B0, B0,
    A0, A0, A0, A0, G0, G0, G0, G0,
    A0, A0, A0, A0, B0, B0, B0, B0,

    E, E, G, G, D, D, B0, B0,
    C, C, E, E, B0, B0, G0, G0,
    A0, A0, C, C, G0, G0, E0, E0,
    A0, A0, C, C, B0, B0, D, D,

    E, D, C, E, D, C, B0, D,
    C, B0, A0, C, B0, A0, G0, B0,
    A0, C, F0, A0, G0, E, C, G0,
    A0, C, F0, A0, B0, D, G0, B0
};

int HEADER_A[12] = {89, 85, 86, 52, 77, 80, 69, 71, 50, 32, 87, 0};
int HEADER_B[3] = {32, 72, 0};
int HEADER_C[24] = {
    32, 70, 49, 53, 58, 49, 32, 73, 112, 32, 65, 49,
    58, 49, 32, 67, 52, 52, 52, 10, 0, 0, 0, 0
};
int FRAME_HEADER[7] = {70, 82, 65, 77, 69, 10, 0};

int Y_PLANE[14400];
int U_PLANE[14400];
int V_PLANE[14400];
int BAR_HEIGHTS[24];
int BAR_PEAKS[24];

void put_text(int text[]) {
    int i = 0;
    while (text[i] != 0) {
        putch(text[i]);
        i = i + 1;
    }
}

int abs_int(int value) {
    if (value < 0) return -value;
    return value;
}

int clamp(int value, int low, int high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

int note_to_bar(int note) {
    int bar = (note - C0) * (BAR_COUNT - 1) / (51 - C0);
    return clamp(bar, 0, BAR_COUNT - 1);
}

int canon_note(int local_tick) {
    if (local_tick < 0 || local_tick >= 96) return 0;
    return CANON_NOTES[local_tick];
}

int arpeggio_note(int tick, int chord) {
    int step = tick % 4;
    if (step == 0) return ROOTS[chord] + 12;
    if (step == 1) return FIFTHS[chord];
    if (step == 2) return THIRDS[chord];
    return FIFTHS[chord];
}

int add_band(int height, int bar, int center, int strength, int falloff) {
    int value = strength - abs_int(bar - center) * falloff;
    if (value > 0) return height + value;
    return height;
}

void update_bars(int frame) {
    int sample = frame * SAMPLE_RATE / FPS;
    int tick = sample / SAMPLES_PER_TICK;
    if (tick > 159) tick = 159;

    int note_age = sample % SAMPLES_PER_TICK;
    int pulse = (SAMPLES_PER_TICK - note_age) * 32 / SAMPLES_PER_TICK;
    int chord = tick / 4 % 8;

    int bass_center = note_to_bar(ROOTS[chord]);
    int arp_center = note_to_bar(arpeggio_note(tick, chord));
    int voice_left = canon_note(tick);
    int voice_center = canon_note(tick - 32);
    int voice_right = canon_note(tick - 64);

    int bar = 0;
    while (bar < BAR_COUNT) {
        int height = 5 + (bar * 13 + frame * 3 + bar * frame % 17) % 8;

        height = add_band(height, bar, bass_center, 28, 4);
        height = add_band(height, bar, arp_center, pulse, 6);

        if (voice_left != 0) {
            height = add_band(height, bar, note_to_bar(voice_left), 17 + pulse, 6);
        }
        if (voice_center != 0) {
            height = add_band(height, bar, note_to_bar(voice_center), 15 + pulse, 5);
        }
        if (voice_right != 0) {
            height = add_band(height, bar, note_to_bar(voice_right), 17 + pulse, 6);
        }

        // Emphasize each new chord in the lower bars.
        if (tick % 4 == 0) {
            int chord_energy = pulse / 2 - bar;
            if (chord_energy > 0) height = height + chord_energy;
        }

        if (tick >= 64 && tick < 96) height = height + 5;

        if (tick >= 144) {
            int remaining = 160 * SAMPLES_PER_TICK - sample;
            height = height * remaining / (16 * SAMPLES_PER_TICK);
        }

        height = clamp(height, 2, HEIGHT - BOTTOM_MARGIN - 6);
        BAR_HEIGHTS[bar] = height;

        if (height >= BAR_PEAKS[bar]) {
            BAR_PEAKS[bar] = height;
        } else if (BAR_PEAKS[bar] > 0) {
            BAR_PEAKS[bar] = BAR_PEAKS[bar] - 1;
        }
        bar = bar + 1;
    }
}

void render_frame(int frame) {
    update_bars(frame);

    int floor = HEIGHT - BOTTOM_MARGIN;
    int y = 0;
    while (y < HEIGHT) {
        int x = 0;
        while (x < WIDTH) {
            int index = y * WIDTH + x;
            int luminance = 12 + y * 10 / HEIGHT;
            int chroma_u = 128;
            int chroma_v = 128;

            // A faint moving background grid.
            if ((x + frame) % 32 == 0 || (y + frame / 2) % 24 == 0) {
                luminance = luminance + 7;
            }

            if (x >= LEFT_MARGIN && x < LEFT_MARGIN + BAR_COUNT * BAR_STEP) {
                int local_x = x - LEFT_MARGIN;
                int bar = local_x / BAR_STEP;
                int inside = local_x % BAR_STEP < 4;
                int top = floor - BAR_HEIGHTS[bar];
                int peak_y = floor - BAR_PEAKS[bar];

                if (inside && y >= top && y < floor) {
                    luminance = 155 + (floor - y) * 75 / HEIGHT;
                    chroma_u = 60 + (bar * 9 + frame) % 150;
                    chroma_v = 205 - (bar * 5 + frame / 2) % 120;
                }

                if (inside && y >= peak_y - 1 && y <= peak_y) {
                    luminance = 235;
                    chroma_u = 128;
                    chroma_v = 128;
                }
            }

            if (y == floor) luminance = 80;

            Y_PLANE[index] = clamp(luminance, 0, 255);
            U_PLANE[index] = clamp(chroma_u, 0, 255);
            V_PLANE[index] = clamp(chroma_v, 0, 255);
            x = x + 1;
        }
        y = y + 1;
    }
}

void emit_plane(int plane[]) {
    int i = 0;
    while (i < PIXELS) {
        putch(plane[i]);
        i = i + 1;
    }
}

int main() {
    put_text(HEADER_A);
    putint(WIDTH);
    put_text(HEADER_B);
    putint(HEIGHT);
    put_text(HEADER_C);

    int frame = 0;
    while (frame < FRAMES) {
        render_frame(frame);
        put_text(FRAME_HEADER);
        emit_plane(Y_PLANE);
        emit_plane(U_PLANE);
        emit_plane(V_PLANE);
        frame = frame + 1;
    }
    return 0;
}
