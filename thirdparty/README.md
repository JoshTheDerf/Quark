# Third party libraries

## glad

- Upstream: https://github.com/Dav1dde/glad
- Version: 0.1.16a0
- License: MIT

The files we package are automatically generated.
See the header of glad.c for instructions on how to generate them for
the GLES version Godot targets.

## jpeg-compressor

- Upstream: https://github.com/richgel999/jpeg-compressor
- Version: 1.04
- License: Public domain

Files extracted from upstream source:

- `jpgd.{c,h}`

## fonts

### Noto Sans

- Upstream: https://github.com/googlei18n/noto-fonts
- Version: 1.06
- License: OFL-1.1

Use UI font variant if available, because it has tight vertical metrics and good for UI.

### Hack Regular

- Upstream: https://github.com/source-foundry/Hack
- Version: 3.000
- License: MIT + Bitstream Vera License

### DroidSans*.ttf

- Upstream: https://android.googlesource.com/platform/frameworks/base/+/master/data/fonts/
- Version: ? (pre-2014 commit when DroidSansJapanese.ttf was obsoleted)
- License: Apache 2.0


## freetype

- Upstream: https://www.freetype.org
- Version: 2.8.1
- License: FreeType License (BSD-like)

Files extracted from upstream source:

- the src/ folder, stripped of the `Jamfile` files
- the include/ folder
- `docs/{FTL.TXT,LICENSE.TXT}`


## libpng

- Upstream: http://libpng.org/pub/png/libpng.html
- Version: 1.6.34
- License: libpng/zlib

Files extracted from upstream source:

- all .c and .h files of the main directory, except from
  `example.c` and `pngtest.c`
- the arm/ folder
- `scripts/pnglibconf.h.prebuilt` as `pnglibconf.h`


## misc

Collection of single-file libraries used in Godot components.

### core

- `aes256.{cpp,h}`
  * Upstream: http://www.literatecode.com/aes256
  * Version: latest, as of April 2017
  * License: ISC
- `base64.{c,h}`
  * Upstream: http://episec.com/people/edelkind/c.html
  * Version: latest, as of April 2017
  * License: Public Domain
- `fastlz.{c,h}`
  * Upstream: https://github.com/ariya/FastLZ
  * Version: git (f121734, 2007)
  * License: MIT
- `hq2x.{cpp,h}`
  * Upstream: https://github.com/brunexgeek/hqx
  * Version: TBD, file structure differs
  * License: Apache 2.0
- `md5.{cpp,h}`
  * Upstream: http://www.efgh.com/software/md5.htm
  * Version: TBD, might not be latest from above URL
  * License: RSA Message-Digest License
- `pcg.{cpp,h}`
  * Upstream: http://www.pcg-random.org
  * Version: minimal C implementation, http://www.pcg-random.org/download.html
  * License: Apache 2.0
- `sha256.{c,h}`
  * Upstream: https://github.com/ilvn/SHA256
  * Version: git (35ff823, 2015)
  * License: ISC
- `smaz.{c,h}`
  * Upstream: https://github.com/antirez/smaz
  * Version: git (150e125, 2009)
  * License: BSD-3-Clause
  * Modifications: use `const char*` instead of `char*` for input string
- `triangulator.{cpp,h}`
  * Upstream: https://github.com/ivanfratric/polypartition (`src/polypartition.cpp`)
  * Version: TBD, class was renamed
  * License: MIT

### modules

- `curl_hostcheck.{c,h}`
  * Upstream: https://curl.haxx.se/
  * Version: ? (2013)
  * License: MIT
- `yuv2rgb.h`
  * Upstream: http://wss.co.uk/pinknoise/yuv2rgb/ (to check)
  * Version: ?
  * License: BSD

### scene

- `mikktspace.{c,h}`
  * Upstream: https://wiki.blender.org/index.php/Dev:Shading/Tangent_Space_Normal_Maps
  * Version: 1.0
  * License: zlib
- `stb_truetype.h`
  * Upstream: https://github.com/nothings/stb
  * Version: 1.17
  * License: Public Domain (Unlicense) or MIT
- `stb_vorbis.c`
  * Upstream: https://github.com/nothings/stb
  * Version: 1.11
  * License: Public Domain (Unlicense) or MIT


## minizip

- Upstream: http://www.zlib.net
- Version: 1.2.4 (zlib contrib)
- License: zlib

Files extracted from the upstream source:

- contrib/minizip/{crypt.h,ioapi.{c,h},zip.{c,h},unzip.{c,h}}

Important: Some files have Godot-made changes for use in core/io.
They are marked with `/* GODOT start */` and `/* GODOT end */`
comments and a patch is provided in the minizip/ folder.


## nanosvg

- Upstream: https://github.com/memononen/nanosvg
- Version: 9a74da4 (git)
- License: zlib

Files extracted from the upstream source:

- All .h files in `src/`
- LICENSE.txt


## pcre2

- Upstream: http://www.pcre.org/
- Version: 10.23
- License: BSD-3-Clause

Files extracted from upstream source:

- Files listed in NON-AUTOTOOLS-BUILD steps 1-4
- All .h files in src/
- src/pcre2_jit_*.c and src/sljit/*
- AUTHORS and COPYING


## rtaudio

- Upstream: http://www.music.mcgill.ca/~gary/rtaudio/
- Version: 4.1.2
- License: MIT-like

Files extracted from upstream source:

- `RtAudio.{cpp,h}`


## zlib

- Upstream: http://www.zlib.net
- Version: 1.2.11
- License: zlib

Files extracted from upstream source:

- all .c and .h files
