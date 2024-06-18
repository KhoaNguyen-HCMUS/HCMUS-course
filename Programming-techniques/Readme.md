# Cut Bitmap

Write C/C++ program to cut Bitmap file into equal parts in command program to cut Bitmap file into equal parts in command - line. Each part is saved in a new Bitmap file.

## Installation

Command-line syntax:

&lt;program&gt; &lt;file Bmp&gt; [-h &lt;parts in height&gt;] [-w &lt;parts in width&gt;]

Example: program cutbmp.exe

- Cut 3 parts in height (save in 3 new Bitmap files):

```bash
cutbmp.exe d:/images/img1.bmp --h 3
```

- Cut 2 parts in height, 4 parts in width (save in 8 new Bitmap files):

```bash
cutbmp.exe d:/images/img1.bmp --h 2 --w 4
```
