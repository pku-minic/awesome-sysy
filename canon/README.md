# canon

A Pachelbel-inspired chiptune and audio-reactive bar visualizer implemented in
pure SysY.

The audio program synthesizes a 69-second, 70 BPM arrangement over Pachelbel's
ground bass. One 96-tick melody enters three times, 32 ticks apart, forming an
actual imitative canon across the left, center, and right stereo positions.
The accompaniment contains bass, quiet chord pads, arpeggios, and
cross-channel delay. The visualizer follows the same integer timeline and
emits a YUV4MPEG2 video stream with 24 animated spectrum bars and peak hold.

## Files

* `canon.c`: emits 12 kHz, 16-bit stereo PCM WAV data to standard output.
* `visualizer.c`: emits a 160x90, 15 FPS, YUV444 Y4M stream to standard output.
* `build.sh`: compiles both SysY programs, renders them under QEMU, and muxes
  the resulting audio and video.
* `clean.sh`: removes intermediate build artifacts.

Both programs use only standard SysY features. They do not require floating
point, structs, dynamic allocation, threads, or non-standard library calls.

## Build

Requirements:

* a SysY compiler that supports `-riscv INPUT -o OUTPUT`;
* Docker and the `maxxing/compiler-dev` image;
* FFmpeg on the host.

Run:

```sh
SYSY_COMPILER=/absolute/path/to/compiler ./build.sh
```

Alternatively:

```sh
make COMPILER=/absolute/path/to/compiler
```

The script performs the complete pipeline:

```text
SysY source
  -> RISC-V assembly
  -> RV32 executable
  -> QEMU rendering
  -> WAV + Y4M
  -> H.264/AAC MP4
```

Generated intermediate files are placed in `build/`. The final outputs are:

* `canon.wav`
* `canon-demo.mp4`
* `canon-demo.png`

All generated files are ignored by Git and can be reproduced with the build
script.

To remove intermediate and generated files:

```sh
make clean
```
