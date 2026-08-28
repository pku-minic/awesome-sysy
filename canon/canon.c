// A three-voice canon and stereo synthesizer written in pure SysY.
// Three identical melodic voices enter 32 ticks apart over a repeating bass.

const int SAMPLE_RATE = 12000;
// 70 BPM, where one tick is an eighth note.
const int SAMPLES_PER_TICK = 5143;
const int TOTAL_TICKS = 160;
const int TOTAL_SAMPLES = SAMPLES_PER_TICK * TOTAL_TICKS;
const int DATA_SIZE = TOTAL_SAMPLES * 4;

const int C = 40;
const int D = 42;
const int E = 44;
const int F = 45;
const int G = 47;
const int A = 49;
const int B = 51;
const int C0 = 28;
const int D0 = 30;
const int E0 = 32;
const int F0 = 33;
const int G0 = 35;
const int A0 = 37;
const int B0 = 39;

// Pachelbel's ground bass transposed to C major.
int ROOTS[8] = {C0, G0, A0, E0, F0, C0, F0, G0};
int THIRDS[8] = {E, B0, C, G0, A0, E0, A0, B0};
int FIFTHS[8] = {G, D, E, B0, C, G0, C, D};

// A 96-tick melodic line. Its first section uses half notes, the second
// quarter notes, and the final section flowing eighth notes.
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

int DELAY_LEFT[2400];
int DELAY_RIGHT[2400];

void put_u16(int value) {
    putch(value % 256);
    putch(value / 256 % 256);
}

void put_u32(int value) {
    putch(value % 256);
    putch(value / 256 % 256);
    putch(value / 65536 % 256);
    putch(value / 16777216 % 256);
}

void emit_wav_header() {
    putch(82);
    putch(73);
    putch(70);
    putch(70);
    put_u32(DATA_SIZE + 36);

    putch(87);
    putch(65);
    putch(86);
    putch(69);

    putch(102);
    putch(109);
    putch(116);
    putch(32);
    put_u32(16);
    put_u16(1);
    put_u16(2);
    put_u32(SAMPLE_RATE);
    put_u32(SAMPLE_RATE * 4);
    put_u16(4);
    put_u16(16);

    putch(100);
    putch(97);
    putch(116);
    putch(97);
    put_u32(DATA_SIZE);
}

int note_period(int note) {
    if (note == C0) return 92;
    if (note == D0) return 82;
    if (note == E0) return 73;
    if (note == F0) return 69;
    if (note == G0) return 61;
    if (note == A0) return 55;
    if (note == B0) return 49;
    if (note == C) return 46;
    if (note == D) return 41;
    if (note == E) return 36;
    if (note == F) return 34;
    if (note == G) return 31;
    if (note == A) return 27;
    if (note == B) return 24;
    return 49;
}

int triangle(int period, int time, int amplitude) {
    int phase = time % period;
    int half = period / 2;
    if (phase < half) {
        return -amplitude + amplitude * 2 * phase / half;
    }
    return amplitude - amplitude * 2 * (phase - half) / (period - half);
}

int shape(int value, int age, int length, int attack, int release) {
    if (age < attack) value = value * age / attack;
    if (age > length - release) value = value * (length - age) / release;
    return value;
}

int bowed_wave(int note, int time, int amplitude) {
    int period = note_period(note);
    int value = triangle(period, time, amplitude);
    value = value + triangle(period / 2, time + period / 5, amplitude / 7);
    value = value + triangle(period * 2, time, amplitude / 10);
    return value;
}

int bass_voice(int note, int age) {
    int length = SAMPLES_PER_TICK * 4;
    int value = bowed_wave(note, age, 1800);
    return shape(value, age, length, 180, 700);
}

int pad_voice(int note, int time, int age) {
    int length = SAMPLES_PER_TICK * 4;
    int value = bowed_wave(note, time, 320);
    return shape(value, age, length, 900, 900);
}

int pluck_voice(int note, int age) {
    int value = bowed_wave(note, age, 850);
    int remain = SAMPLES_PER_TICK - age;
    value = shape(value, age, SAMPLES_PER_TICK, 60, 300);
    return value * remain / SAMPLES_PER_TICK;
}

int canon_note_length(int local_tick) {
    if (local_tick < 32) return SAMPLES_PER_TICK * 4;
    if (local_tick < 64) return SAMPLES_PER_TICK * 2;
    return SAMPLES_PER_TICK;
}

int canon_note_age(int local_tick, int note_age) {
    if (local_tick < 32) return local_tick % 4 * SAMPLES_PER_TICK + note_age;
    if (local_tick < 64) return (local_tick - 32) % 2 * SAMPLES_PER_TICK + note_age;
    return note_age;
}

int canon_voice(int local_tick, int note_age, int amplitude) {
    if (local_tick < 0 || local_tick >= 96) return 0;
    int note = CANON_NOTES[local_tick];
    int age = canon_note_age(local_tick, note_age);
    int length = canon_note_length(local_tick);
    int value = bowed_wave(note, age, amplitude);
    int attack = 260;
    if (length == SAMPLES_PER_TICK) attack = 100;
    return shape(value, age, length, attack, 650);
}

int arpeggio_note(int tick, int chord) {
    int step = tick % 4;
    if (step == 0) return ROOTS[chord] + 12;
    if (step == 1) return FIFTHS[chord];
    if (step == 2) return THIRDS[chord];
    return FIFTHS[chord];
}

int clamp_sample(int value) {
    if (value > 32767) return 32767;
    if (value < -32768) return -32768;
    return value;
}

void emit_sample(int value) {
    value = clamp_sample(value);
    if (value < 0) value = value + 65536;
    put_u16(value);
}

int main() {
    emit_wav_header();

    int sample = 0;
    int delay_pos = 0;
    while (sample < TOTAL_SAMPLES) {
        int tick = sample / SAMPLES_PER_TICK;
        int note_age = sample % SAMPLES_PER_TICK;
        int chord = tick / 4 % 8;
        int chord_age = sample % (SAMPLES_PER_TICK * 4);

        int bass = bass_voice(ROOTS[chord], chord_age);
        int pad = pad_voice(THIRDS[chord], sample, chord_age);
        pad = pad + pad_voice(FIFTHS[chord], sample, chord_age);
        int arp = pluck_voice(arpeggio_note(tick, chord), note_age);

        // The same melody enters once per complete 32-tick bass cycle.
        int voice_left = canon_voice(tick, note_age, 2700);
        int voice_center = canon_voice(tick - 32, note_age, 2500);
        int voice_right = canon_voice(tick - 64, note_age, 2700);

        int center = bass + pad + arp;
        int left = center + voice_left + voice_center * 3 / 4 + voice_right / 3;
        int right = center + voice_left / 3 + voice_center * 3 / 4 + voice_right;

        int old_left = DELAY_LEFT[delay_pos];
        int old_right = DELAY_RIGHT[delay_pos];
        int dry_left = left;
        int dry_right = right;
        left = left + old_right / 5;
        right = right + old_left / 5;
        DELAY_LEFT[delay_pos] = dry_left + old_left / 6;
        DELAY_RIGHT[delay_pos] = dry_right + old_right / 6;

        // Fade the final half-cycle after the last voice has taken the lead.
        if (tick >= 144) {
            int remaining = TOTAL_SAMPLES - sample;
            int fade_length = SAMPLES_PER_TICK * 16;
            left = left * remaining / fade_length;
            right = right * remaining / fade_length;
        }

        emit_sample(left);
        emit_sample(right);

        delay_pos = delay_pos + 1;
        if (delay_pos == 2400) delay_pos = 0;
        sample = sample + 1;
    }
    return 0;
}
