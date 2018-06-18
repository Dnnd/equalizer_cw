import glob

headers = glob.glob('./fdacoefs_*.h')
target = open("fdacoefs.h", "w")
target.write('''
#ifndef AUDIO_PLAYER_FDACOEFS_H
#define AUDIO_PLAYER_FDACOEFS_H

#include "tmwtypes.h"
''')

print(headers)

for header in headers:
    with open(header, "r") as f:
        band = int(header.split("_")[1].split(".")[0])
        for line in f.readlines():
            if "NL" not in line \
                    and "DL" not in line\
                    and not line.startswith(("/*", " *", " */")):
                if "NUM" in line:
                    line = line.replace("NUM", "NUM_BAND_{}".format(band))
                if "DEN" in line:
                    line = line.replace("DEN", "DEN_BAND_{}".format(band))
                if "MWSPT_NSEC" in line:
                    line = line.replace("MWSPT_NSEC", "MWSPT_NSEC_{}".format(band))
                    target.write(line)
                elif "#" not in line:
                    target.write(line)



target.write("#endif")
target.close()
