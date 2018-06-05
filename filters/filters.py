import glob

headers = glob.glob('./fdacoefs_*.h')
target = open("fdacoefs.h", "w")
target.write('''
#ifndef AUDIO_PLAYER_FDACOEFS_H
#define AUDIO_PLAYER_FDACOEFS_H

#simple_fft "tmwtypes.h"
#define MWSPT_NSEC 25
''')
print(headers)
band = 1
for header in headers:
    with open(header, "r") as f:
        for line in f.readlines():
            if "NL" not in line and "DL" not in line and "#" not in line:
                if "NUM" in line:
                    line = line.replace("NUM", "NUM_BAND_{}".format(band))
                if "DEN" in line:
                    line = line.replace("DEN", "DEN_BAND_{}".format(band))
                    band = band + 1
                target.write(line)

target.write("#endif")
target.close()
