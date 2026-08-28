// A pure SysY MML/MIDI-to-WAV renderer.
// Auto-detects textual MML or Standard MIDI File input on stdin and emits
// 12 kHz, 16-bit stereo PCM WAV data on stdout.

const int MAX_INPUT = 262144;
const int MAX_NOTES = 8192;
const int MAX_TEMPOS = 64;
const int MAX_ACTIVE = 256;
const int SAMPLE_RATE = 12000;
const int MML_PPQ = 96;

int INPUT[262144];
int INPUT_LEN;
int INPUT_POS;

int NOTE_PITCH[8192];
int NOTE_START_TICK[8192];
int NOTE_END_TICK[8192];
int NOTE_VELOCITY[8192];
int NOTE_PAN[8192];
int NOTE_PROGRAM[8192];
int NOTE_START_SAMPLE[8192];
int NOTE_END_SAMPLE[8192];
int NOTE_COUNT;

int TEMPO_TICK[64];
int TEMPO_US[64];
int TEMPO_COUNT;
int DIVISION = 96;
int TOTAL_TICKS;
int TOTAL_SAMPLES;

int ACTIVE_NOTES[256];
int ACTIVE_COUNT;
int DELAY_LEFT[1800];
int DELAY_RIGHT[1800];

int MIDI_PROGRAM[16];
int MIDI_PAN[16];
int ACTIVE_START[2048];
int ACTIVE_VELOCITY[2048];
int ACTIVE_PROGRAM[2048];
int ACTIVE_PAN[2048];

int MML_OCTAVE;
int MML_DEFAULT_LENGTH;
int MML_VELOCITY;
int MML_PAN;
int MML_PROGRAM;
int MML_CURSOR;

int ERROR_CODE;
int ERROR_POS;
int ERROR_PREFIX[13] = {83, 99, 111, 114, 101, 32, 101, 114, 114, 111, 114, 32, 0};
int ERROR_MIDDLE[10] = {32, 97, 116, 32, 98, 121, 116, 101, 32, 0};
int BASE_PERIOD[12] = {46, 43, 41, 39, 36, 34, 32, 31, 29, 27, 26, 24};

void set_error(int code) {
    if (ERROR_CODE == 0) {
        ERROR_CODE = code;
        ERROR_POS = INPUT_POS;
    }
}

void put_text(int text[]) {
    int i = 0;
    while (text[i] != 0) {
        putch(text[i]);
        i = i + 1;
    }
}

void print_error() {
    put_text(ERROR_PREFIX);
    putint(ERROR_CODE);
    put_text(ERROR_MIDDLE);
    putint(ERROR_POS);
    putch(10);
}

int clamp(int value, int low, int high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

int is_digit(int ch) {
    return ch >= 48 && ch <= 57;
}

int uppercase(int ch) {
    if (ch >= 97 && ch <= 122) return ch - 32;
    return ch;
}

void read_input() {
    int ch = getch();
    while (ch != -1 && INPUT_LEN < MAX_INPUT) {
        INPUT[INPUT_LEN] = ch;
        INPUT_LEN = INPUT_LEN + 1;
        ch = getch();
    }
    if (ch != -1) set_error(1);
}

int read_byte() {
    if (INPUT_POS >= INPUT_LEN) {
        set_error(2);
        return 0;
    }
    int value = INPUT[INPUT_POS];
    INPUT_POS = INPUT_POS + 1;
    return value;
}

int read_u16_be() {
    int a = read_byte();
    int b = read_byte();
    return a * 256 + b;
}

int read_u24_be() {
    int a = read_byte();
    int b = read_byte();
    int c = read_byte();
    return a * 65536 + b * 256 + c;
}

int read_u32_be() {
    int a = read_byte();
    int b = read_byte();
    int c = read_byte();
    int d = read_byte();
    return a * 16777216 + b * 65536 + c * 256 + d;
}

int read_vlq() {
    int value = 0;
    int count = 0;
    int done = 0;
    while (!done && count < 5) {
        int byte = read_byte();
        value = value * 128 + byte % 128;
        if (byte < 128) done = 1;
        count = count + 1;
    }
    if (!done) set_error(3);
    return value;
}

void add_tempo(int tick, int microseconds) {
    if (microseconds <= 0) {
        set_error(4);
        return;
    }

    int i = 0;
    while (i < TEMPO_COUNT && TEMPO_TICK[i] < tick) i = i + 1;
    if (i < TEMPO_COUNT && TEMPO_TICK[i] == tick) {
        TEMPO_US[i] = microseconds;
        return;
    }
    if (TEMPO_COUNT >= MAX_TEMPOS) {
        set_error(5);
        return;
    }

    int j = TEMPO_COUNT;
    while (j > i) {
        TEMPO_TICK[j] = TEMPO_TICK[j - 1];
        TEMPO_US[j] = TEMPO_US[j - 1];
        j = j - 1;
    }
    TEMPO_TICK[i] = tick;
    TEMPO_US[i] = microseconds;
    TEMPO_COUNT = TEMPO_COUNT + 1;
}

void add_note(int pitch, int start, int end, int velocity, int pan, int program) {
    if (end <= start) return;
    if (NOTE_COUNT >= MAX_NOTES) {
        set_error(6);
        return;
    }
    NOTE_PITCH[NOTE_COUNT] = clamp(pitch, 0, 127);
    NOTE_START_TICK[NOTE_COUNT] = start;
    NOTE_END_TICK[NOTE_COUNT] = end;
    NOTE_VELOCITY[NOTE_COUNT] = clamp(velocity, 1, 127);
    NOTE_PAN[NOTE_COUNT] = clamp(pan, 0, 127);
    NOTE_PROGRAM[NOTE_COUNT] = clamp(program, 0, 127);
    NOTE_COUNT = NOTE_COUNT + 1;
    if (end > TOTAL_TICKS) TOTAL_TICKS = end;
}

// ---------------- MML parser ----------------

void skip_mml_ignored() {
    int keep_going = 1;
    while (keep_going && INPUT_POS < INPUT_LEN) {
        keep_going = 0;
        int ch = INPUT[INPUT_POS];
        if (ch == 9 || ch == 10 || ch == 13 || ch == 32 || ch == 44 || ch == 124) {
            INPUT_POS = INPUT_POS + 1;
            keep_going = 1;
        } else if (ch == 37) {
            while (INPUT_POS < INPUT_LEN && INPUT[INPUT_POS] != 10) INPUT_POS = INPUT_POS + 1;
            keep_going = 1;
        } else if (ch == 47 && INPUT_POS + 1 < INPUT_LEN && INPUT[INPUT_POS + 1] == 47) {
            INPUT_POS = INPUT_POS + 2;
            while (INPUT_POS < INPUT_LEN && INPUT[INPUT_POS] != 10) INPUT_POS = INPUT_POS + 1;
            keep_going = 1;
        }
    }
}

int parse_mml_number() {
    if (INPUT_POS >= INPUT_LEN || !is_digit(INPUT[INPUT_POS])) {
        set_error(7);
        return 0;
    }
    int value = 0;
    while (INPUT_POS < INPUT_LEN && is_digit(INPUT[INPUT_POS])) {
        value = value * 10 + INPUT[INPUT_POS] - 48;
        INPUT_POS = INPUT_POS + 1;
    }
    return value;
}

int mml_duration_from_length(int length) {
    if (length == 1) return DIVISION * 4;
    if (length == 2) return DIVISION * 2;
    if (length == 4) return DIVISION;
    if (length == 8) return DIVISION / 2;
    if (length == 16) return DIVISION / 4;
    if (length == 32) return DIVISION / 8;
    set_error(8);
    return DIVISION;
}

int parse_mml_duration() {
    int length = MML_DEFAULT_LENGTH;
    if (INPUT_POS < INPUT_LEN && is_digit(INPUT[INPUT_POS])) length = parse_mml_number();
    int duration = mml_duration_from_length(length);
    int addition = duration / 2;
    while (INPUT_POS < INPUT_LEN && INPUT[INPUT_POS] == 46) {
        duration = duration + addition;
        addition = addition / 2;
        INPUT_POS = INPUT_POS + 1;
    }
    return duration;
}

int mml_note_semitone(int ch) {
    if (ch == 67) return 0;
    if (ch == 68) return 2;
    if (ch == 69) return 4;
    if (ch == 70) return 5;
    if (ch == 71) return 7;
    if (ch == 65) return 9;
    if (ch == 66) return 11;
    set_error(9);
    return 0;
}

void reset_mml_track() {
    MML_OCTAVE = 4;
    MML_DEFAULT_LENGTH = 4;
    MML_VELOCITY = 96;
    MML_PAN = 64;
    MML_PROGRAM = 0;
    MML_CURSOR = 0;
}

void parse_mml_note(int ch) {
    int semitone = mml_note_semitone(ch);
    if (INPUT_POS < INPUT_LEN) {
        int accidental = INPUT[INPUT_POS];
        if (accidental == 35 || accidental == 43) {
            semitone = semitone + 1;
            INPUT_POS = INPUT_POS + 1;
        } else if (accidental == 45) {
            semitone = semitone - 1;
            INPUT_POS = INPUT_POS + 1;
        }
    }
    int duration = parse_mml_duration();
    int pitch = (MML_OCTAVE + 1) * 12 + semitone;
    add_note(pitch, MML_CURSOR, MML_CURSOR + duration, MML_VELOCITY, MML_PAN, MML_PROGRAM);
    MML_CURSOR = MML_CURSOR + duration;
}

void parse_mml() {
    DIVISION = MML_PPQ;
    add_tempo(0, 500000);
    reset_mml_track();

    while (INPUT_POS < INPUT_LEN && ERROR_CODE == 0) {
        skip_mml_ignored();
        if (INPUT_POS >= INPUT_LEN) break;
        int ch = uppercase(INPUT[INPUT_POS]);
        INPUT_POS = INPUT_POS + 1;

        if (ch == 65 || ch == 66 || ch == 67 || ch == 68 || ch == 69 || ch == 70 || ch == 71) {
            parse_mml_note(ch);
        } else if (ch == 82) {
            MML_CURSOR = MML_CURSOR + parse_mml_duration();
            if (MML_CURSOR > TOTAL_TICKS) TOTAL_TICKS = MML_CURSOR;
        } else if (ch == 84) {
            int bpm = parse_mml_number();
            if (NOTE_COUNT != 0 || bpm < 20 || bpm > 400) {
                set_error(10);
            } else {
                TEMPO_US[0] = 60000000 / bpm;
            }
        } else if (ch == 79) {
            MML_OCTAVE = parse_mml_number();
            if (MML_OCTAVE < 0 || MML_OCTAVE > 9) set_error(11);
        } else if (ch == 76) {
            MML_DEFAULT_LENGTH = parse_mml_number();
            mml_duration_from_length(MML_DEFAULT_LENGTH);
        } else if (ch == 86) {
            MML_VELOCITY = parse_mml_number();
            if (MML_VELOCITY < 1 || MML_VELOCITY > 127) set_error(12);
        } else if (ch == 80) {
            MML_PAN = parse_mml_number();
            if (MML_PAN < 0 || MML_PAN > 127) set_error(13);
        } else if (ch == 64 || ch == 73) {
            MML_PROGRAM = parse_mml_number();
            if (MML_PROGRAM < 0 || MML_PROGRAM > 127) set_error(14);
        } else if (ch == 62) {
            MML_OCTAVE = MML_OCTAVE + 1;
            if (MML_OCTAVE > 9) set_error(11);
        } else if (ch == 60) {
            MML_OCTAVE = MML_OCTAVE - 1;
            if (MML_OCTAVE < 0) set_error(11);
        } else if (ch == 59) {
            reset_mml_track();
        } else {
            set_error(15);
        }
    }
    if (NOTE_COUNT == 0 && ERROR_CODE == 0) set_error(16);
}

// ---------------- Standard MIDI File parser ----------------

void reset_midi_track_state() {
    int i = 0;
    while (i < 16) {
        MIDI_PROGRAM[i] = 0;
        MIDI_PAN[i] = 64;
        i = i + 1;
    }
    i = 0;
    while (i < 2048) {
        ACTIVE_START[i] = -1;
        i = i + 1;
    }
}

void close_midi_note(int channel, int pitch, int tick) {
    int index = channel * 128 + pitch;
    if (ACTIVE_START[index] >= 0) {
        add_note(
            pitch,
            ACTIVE_START[index],
            tick,
            ACTIVE_VELOCITY[index],
            ACTIVE_PAN[index],
            ACTIVE_PROGRAM[index]
        );
        ACTIVE_START[index] = -1;
    }
}

void open_midi_note(int channel, int pitch, int velocity, int tick) {
    int index = channel * 128 + pitch;
    if (ACTIVE_START[index] >= 0) close_midi_note(channel, pitch, tick);
    ACTIVE_START[index] = tick;
    ACTIVE_VELOCITY[index] = velocity;
    ACTIVE_PAN[index] = MIDI_PAN[channel];
    ACTIVE_PROGRAM[index] = MIDI_PROGRAM[channel];
}

void close_all_midi_notes(int tick) {
    int index = 0;
    while (index < 2048) {
        if (ACTIVE_START[index] >= 0) {
            close_midi_note(index / 128, index % 128, tick);
        }
        index = index + 1;
    }
}

void skip_bytes(int count, int limit) {
    if (count < 0 || INPUT_POS + count > limit) {
        set_error(17);
    } else {
        INPUT_POS = INPUT_POS + count;
    }
}

void parse_midi_track(int track_end) {
    int tick = 0;
    int running_status = 0;
    reset_midi_track_state();

    while (INPUT_POS < track_end && ERROR_CODE == 0) {
        tick = tick + read_vlq();
        int first = read_byte();
        int status = first;
        if (first < 128) {
            if (running_status == 0) {
                set_error(18);
                return;
            }
            status = running_status;
            INPUT_POS = INPUT_POS - 1;
        } else if (status < 240) {
            running_status = status;
        } else {
            running_status = 0;
        }

        int command = status / 16;
        int channel = status % 16;
        if (command == 8) {
            int pitch = read_byte();
            read_byte();
            close_midi_note(channel, pitch, tick);
        } else if (command == 9) {
            int pitch = read_byte();
            int velocity = read_byte();
            if (velocity == 0) {
                close_midi_note(channel, pitch, tick);
            } else {
                open_midi_note(channel, pitch, velocity, tick);
            }
        } else if (command == 10) {
            read_byte();
            read_byte();
        } else if (command == 11) {
            int controller = read_byte();
            int value = read_byte();
            if (controller == 10) MIDI_PAN[channel] = value;
        } else if (command == 12) {
            MIDI_PROGRAM[channel] = read_byte();
        } else if (command == 13) {
            read_byte();
        } else if (command == 14) {
            read_byte();
            read_byte();
        } else if (status == 255) {
            int meta_type = read_byte();
            int length = read_vlq();
            if (meta_type == 81 && length == 3) {
                add_tempo(tick, read_u24_be());
            } else {
                skip_bytes(length, track_end);
            }
        } else if (status == 240 || status == 247) {
            skip_bytes(read_vlq(), track_end);
        } else {
            set_error(19);
        }
    }

    close_all_midi_notes(tick);
    if (tick > TOTAL_TICKS) TOTAL_TICKS = tick;
    if (INPUT_POS != track_end && ERROR_CODE == 0) set_error(20);
    INPUT_POS = track_end;
}

void parse_midi() {
    INPUT_POS = 0;
    if (read_byte() != 77 || read_byte() != 84 || read_byte() != 104 || read_byte() != 100) {
        set_error(21);
        return;
    }

    int header_length = read_u32_be();
    int format = read_u16_be();
    int track_count = read_u16_be();
    DIVISION = read_u16_be();
    if (header_length < 6 || format < 0 || format > 1 || track_count <= 0) set_error(22);
    if (DIVISION <= 0 || DIVISION >= 32768) set_error(23);
    if (header_length > 6) skip_bytes(header_length - 6, INPUT_LEN);

    int track = 0;
    while (track < track_count && ERROR_CODE == 0) {
        if (read_byte() != 77 || read_byte() != 84 || read_byte() != 114 || read_byte() != 107) {
            set_error(24);
            break;
        }
        int length = read_u32_be();
        int track_end = INPUT_POS + length;
        if (length < 0 || track_end > INPUT_LEN) {
            set_error(25);
            break;
        }
        parse_midi_track(track_end);
        track = track + 1;
    }

    if (TEMPO_COUNT == 0) add_tempo(0, 500000);
    if (TEMPO_TICK[0] != 0) add_tempo(0, 500000);
    if (NOTE_COUNT == 0 && ERROR_CODE == 0) set_error(26);
}

// ---------------- Timing, sorting, and synthesis ----------------

int samples_per_quarter(int microseconds) {
    int scaled = microseconds / 1000 * SAMPLE_RATE;
    scaled = scaled + microseconds % 1000 * SAMPLE_RATE / 1000;
    return (scaled + 500) / 1000;
}

int tick_to_sample(int tick) {
    int sample = 0;
    int previous_tick = 0;
    int current_tempo = 500000;
    int tempo_index = 0;
    if (TEMPO_COUNT > 0 && TEMPO_TICK[0] == 0) {
        current_tempo = TEMPO_US[0];
        tempo_index = 1;
    }

    while (tempo_index < TEMPO_COUNT && TEMPO_TICK[tempo_index] <= tick) {
        int next_tick = TEMPO_TICK[tempo_index];
        int delta = next_tick - previous_tick;
        int quarter_samples = samples_per_quarter(current_tempo);
        sample = sample + delta / DIVISION * quarter_samples;
        sample = sample + delta % DIVISION * quarter_samples / DIVISION;
        previous_tick = next_tick;
        current_tempo = TEMPO_US[tempo_index];
        tempo_index = tempo_index + 1;
    }

    int delta = tick - previous_tick;
    int quarter_samples = samples_per_quarter(current_tempo);
    sample = sample + delta / DIVISION * quarter_samples;
    sample = sample + delta % DIVISION * quarter_samples / DIVISION;
    return sample;
}

void swap_notes(int a, int b) {
    int temp = NOTE_PITCH[a];
    NOTE_PITCH[a] = NOTE_PITCH[b];
    NOTE_PITCH[b] = temp;
    temp = NOTE_START_TICK[a];
    NOTE_START_TICK[a] = NOTE_START_TICK[b];
    NOTE_START_TICK[b] = temp;
    temp = NOTE_END_TICK[a];
    NOTE_END_TICK[a] = NOTE_END_TICK[b];
    NOTE_END_TICK[b] = temp;
    temp = NOTE_VELOCITY[a];
    NOTE_VELOCITY[a] = NOTE_VELOCITY[b];
    NOTE_VELOCITY[b] = temp;
    temp = NOTE_PAN[a];
    NOTE_PAN[a] = NOTE_PAN[b];
    NOTE_PAN[b] = temp;
    temp = NOTE_PROGRAM[a];
    NOTE_PROGRAM[a] = NOTE_PROGRAM[b];
    NOTE_PROGRAM[b] = temp;
    temp = NOTE_START_SAMPLE[a];
    NOTE_START_SAMPLE[a] = NOTE_START_SAMPLE[b];
    NOTE_START_SAMPLE[b] = temp;
    temp = NOTE_END_SAMPLE[a];
    NOTE_END_SAMPLE[a] = NOTE_END_SAMPLE[b];
    NOTE_END_SAMPLE[b] = temp;
}

void sort_notes(int left, int right) {
    int i = left;
    int j = right;
    int pivot = NOTE_START_SAMPLE[(left + right) / 2];
    while (i <= j) {
        while (NOTE_START_SAMPLE[i] < pivot) i = i + 1;
        while (NOTE_START_SAMPLE[j] > pivot) j = j - 1;
        if (i <= j) {
            swap_notes(i, j);
            i = i + 1;
            j = j - 1;
        }
    }
    if (left < j) sort_notes(left, j);
    if (i < right) sort_notes(i, right);
}

void prepare_notes() {
    int i = 0;
    int max_sample = 0;
    while (i < NOTE_COUNT) {
        NOTE_START_SAMPLE[i] = tick_to_sample(NOTE_START_TICK[i]);
        NOTE_END_SAMPLE[i] = tick_to_sample(NOTE_END_TICK[i]);
        if (NOTE_END_SAMPLE[i] > max_sample) max_sample = NOTE_END_SAMPLE[i];
        i = i + 1;
    }
    if (NOTE_COUNT > 1) sort_notes(0, NOTE_COUNT - 1);

    // Prove that the fixed active-voice pool is large enough before emitting
    // the WAV header, so excessive polyphony becomes a clean parse error.
    ACTIVE_COUNT = 0;
    i = 0;
    while (i < NOTE_COUNT && ERROR_CODE == 0) {
        int active = 0;
        while (active < ACTIVE_COUNT) {
            int note_index = ACTIVE_NOTES[active];
            if (NOTE_END_SAMPLE[note_index] <= NOTE_START_SAMPLE[i]) {
                ACTIVE_COUNT = ACTIVE_COUNT - 1;
                ACTIVE_NOTES[active] = ACTIVE_NOTES[ACTIVE_COUNT];
            } else {
                active = active + 1;
            }
        }
        if (ACTIVE_COUNT >= MAX_ACTIVE) {
            set_error(28);
        } else {
            ACTIVE_NOTES[ACTIVE_COUNT] = i;
            ACTIVE_COUNT = ACTIVE_COUNT + 1;
        }
        i = i + 1;
    }
    ACTIVE_COUNT = 0;

    TOTAL_SAMPLES = max_sample + SAMPLE_RATE * 2;
    if (TOTAL_SAMPLES <= 0 || TOTAL_SAMPLES > 500000000) set_error(27);
}

int note_period(int pitch) {
    int period = BASE_PERIOD[pitch % 12];
    int octave = pitch / 12;
    while (octave < 5) {
        period = period * 2;
        octave = octave + 1;
    }
    while (octave > 5) {
        period = period / 2;
        octave = octave - 1;
    }
    if (period < 2) period = 2;
    return period;
}

int triangle(int period, int time, int amplitude) {
    int phase = time % period;
    int half = period / 2;
    if (phase < half) return -amplitude + amplitude * 2 * phase / half;
    return amplitude - amplitude * 2 * (phase - half) / (period - half);
}

int shape(int value, int age, int length, int attack, int release) {
    if (attack > 0 && age < attack) value = value * age / attack;
    if (release > length) release = length;
    if (release > 0 && age > length - release) value = value * (length - age) / release;
    return value;
}

int synth_note(int note_index, int age) {
    int pitch = NOTE_PITCH[note_index];
    int program = NOTE_PROGRAM[note_index];
    int length = NOTE_END_SAMPLE[note_index] - NOTE_START_SAMPLE[note_index];
    int amplitude = 2200 * NOTE_VELOCITY[note_index] / 127;
    int period = note_period(pitch);
    int value = triangle(period, age, amplitude);

    if (program >= 32 && program < 40) {
        value = value + triangle(period * 2, age, amplitude / 3);
        value = shape(value, age, length, 80, 500);
    } else if (program >= 40 && program < 48) {
        value = value + triangle(period / 2, age + period / 5, amplitude / 7);
        value = value + triangle(period * 2, age, amplitude / 10);
        value = shape(value, age, length, 240, 700);
    } else if (program < 8) {
        value = value + triangle(period / 2, age, amplitude / 5);
        value = shape(value, age, length, 40, 400);
        value = value * (length - age + length) / (length * 2);
    } else {
        value = value + triangle(period / 2, age, amplitude / 8);
        value = shape(value, age, length, 100, 500);
    }
    return value;
}

int clamp_sample(int value) {
    if (value > 32767) return 32767;
    if (value < -32768) return -32768;
    return value;
}

void put_u16_le(int value) {
    putch(value % 256);
    putch(value / 256 % 256);
}

void put_u32_le(int value) {
    putch(value % 256);
    putch(value / 256 % 256);
    putch(value / 65536 % 256);
    putch(value / 16777216 % 256);
}

void emit_wav_header() {
    int data_size = TOTAL_SAMPLES * 4;
    putch(82); putch(73); putch(70); putch(70);
    put_u32_le(data_size + 36);
    putch(87); putch(65); putch(86); putch(69);
    putch(102); putch(109); putch(116); putch(32);
    put_u32_le(16);
    put_u16_le(1);
    put_u16_le(2);
    put_u32_le(SAMPLE_RATE);
    put_u32_le(SAMPLE_RATE * 4);
    put_u16_le(4);
    put_u16_le(16);
    putch(100); putch(97); putch(116); putch(97);
    put_u32_le(data_size);
}

void emit_pcm_sample(int value) {
    value = clamp_sample(value);
    if (value < 0) value = value + 65536;
    put_u16_le(value);
}

void remove_finished_notes(int sample) {
    int i = 0;
    while (i < ACTIVE_COUNT) {
        int note_index = ACTIVE_NOTES[i];
        if (NOTE_END_SAMPLE[note_index] <= sample) {
            ACTIVE_COUNT = ACTIVE_COUNT - 1;
            ACTIVE_NOTES[i] = ACTIVE_NOTES[ACTIVE_COUNT];
        } else {
            i = i + 1;
        }
    }
}

void render_wav() {
    emit_wav_header();
    int sample = 0;
    int next_note = 0;
    int delay_pos = 0;

    while (sample < TOTAL_SAMPLES) {
        remove_finished_notes(sample);
        while (next_note < NOTE_COUNT && NOTE_START_SAMPLE[next_note] <= sample) {
            if (NOTE_END_SAMPLE[next_note] > sample) {
                if (ACTIVE_COUNT < MAX_ACTIVE) {
                    ACTIVE_NOTES[ACTIVE_COUNT] = next_note;
                    ACTIVE_COUNT = ACTIVE_COUNT + 1;
                }
            }
            next_note = next_note + 1;
        }

        int left = 0;
        int right = 0;
        int i = 0;
        while (i < ACTIVE_COUNT) {
            int note_index = ACTIVE_NOTES[i];
            int age = sample - NOTE_START_SAMPLE[note_index];
            int value = synth_note(note_index, age);
            int pan = NOTE_PAN[note_index];
            if (pan < 64) {
                left = left + value;
                right = right + value * pan / 64;
            } else {
                right = right + value;
                left = left + value * (127 - pan) / 63;
            }
            i = i + 1;
        }

        int old_left = DELAY_LEFT[delay_pos];
        int old_right = DELAY_RIGHT[delay_pos];
        int dry_left = left;
        int dry_right = right;
        left = left + old_right / 6;
        right = right + old_left / 6;
        DELAY_LEFT[delay_pos] = dry_left + old_left / 7;
        DELAY_RIGHT[delay_pos] = dry_right + old_right / 7;

        emit_pcm_sample(left);
        emit_pcm_sample(right);

        delay_pos = delay_pos + 1;
        if (delay_pos == 1800) delay_pos = 0;
        sample = sample + 1;
    }
}

int main() {
    read_input();
    if (ERROR_CODE == 0) {
        if (INPUT_LEN >= 4 && INPUT[0] == 77 && INPUT[1] == 84 && INPUT[2] == 104 && INPUT[3] == 100) {
            parse_midi();
        } else {
            INPUT_POS = 0;
            parse_mml();
        }
    }
    if (ERROR_CODE == 0) prepare_notes();

    if (ERROR_CODE != 0) {
        print_error();
        return 1;
    }

    render_wav();
    return 0;
}
