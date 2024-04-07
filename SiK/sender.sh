make
sox -S "amg.wav" -r 44100 -b 16 -e signed-integer -c 2 -t raw - | pv -q -L 176400 | ./sikradio-sender -a 127.0.0.1 -P 2200 -n "Radio Muzyczka"