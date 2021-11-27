# AudioFilter

Simple program to filter the user-defined audio file by removing specific frequency range given in Hz.
The program uses the Fast Fourier Transform algorithm to convert the audio signal from the time domain to the frequency domain, applies a filter function and returns to the time domain using inverse FFT.
The effect has been visualized in the Audacity as shown below.

![Result](https://raw.githubusercontent.com/DoxPL/AudioFilter/master/result.png)

Program usage:
```
audio_filter -i <input_file> -o <output_file> -f <from_frequency> -t <to_frequency> [-v]
```
<br />
The tool is under development and may not works as expected in the current phase. <br/><br/>
Supported audio formats:<br />

| Format     | Details |
| ---      | ---       |
| WAV  | Unsigned 8 bit PCM |
| WAV  | Signed 16 bit PCM |
| WAV  | Signed 32 bit PCM |
