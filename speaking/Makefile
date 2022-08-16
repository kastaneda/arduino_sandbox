
# common ffmpeg converting options: 8 bit, 22K
# and cut 1 second in the start (loud click)

FFMPEG_PARAM = -i hello16.wav -y -ss 00:00:01 -ar 22050 -c:a pcm_u8

all: \
	hello8_basic.wav \
	hello8_highpass.wav \
	hello8_afftdn.wav \
	hello8_anlmdn.wav \
	hello8_rnn_bd.wav \
	hello8_rnn_cb.wav \
	hello8_rnn_lq.wav \
	hello8_rnn_mp.wav \
	hello8_rnn_sh.wav

hello16.wav: hello16.wav.gz
	gunzip -k $<

# at first, record it 16-bit (SoX)

rec:
	rec -c 1 -b 16 -r 22050 hello16.wav

# https://askubuntu.com/questions/1306318/changing-sample-format-and-bit-depth-on-audio-files-with-ffmpeg

hello8_basic.wav: hello16.wav
	ffmpeg $(FFMPEG_PARAM) $@

# https://superuser.com/questions/733061/reduce-background-noise-and-optimize-the-speech-from-an-audio-clip-using-ffmpeg

hello8_highpass.wav: hello16.wav
	ffmpeg $(FFMPEG_PARAM) -af "highpass=f=200, lowpass=f=1000" $@

hello8_afftdn.wav: hello16.wav
	ffmpeg $(FFMPEG_PARAM) -af afftdn=nr=40 $@

hello8_anlmdn.wav: hello16.wav
	ffmpeg $(FFMPEG_PARAM) -af anlmdn $@

# https://github.com/GregorR/rnnoise-models

rnn/*:
	$(MAKE) -C rnn

hello8_rnn_bd.wav: rnn/bd.rnnn hello16.wav
	ffmpeg $(FFMPEG_PARAM) -af arnndn=m=rnn/bd.rnnn $@

hello8_rnn_cb.wav: rnn/cb.rnnn hello16.wav
	ffmpeg $(FFMPEG_PARAM) -af arnndn=m=rnn/cb.rnnn $@

hello8_rnn_lq.wav: rnn/lq.rnnn hello16.wav
	ffmpeg $(FFMPEG_PARAM) -af arnndn=m=rnn/lq.rnnn $@

hello8_rnn_mp.wav: rnn/mp.rnnn hello16.wav
	ffmpeg $(FFMPEG_PARAM) -af arnndn=m=rnn/mp.rnnn $@

hello8_rnn_sh.wav: rnn/sh.rnnn hello16.wav
	ffmpeg $(FFMPEG_PARAM) -af arnndn=m=rnn/sh.rnnn $@

.PHONY: all rec rnn

.SECONDARY:
