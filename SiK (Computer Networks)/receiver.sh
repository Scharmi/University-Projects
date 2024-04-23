make
./sikradio-receiver -a 127.0.0.1 -P 2200 | play -t raw -b 16 -e signed-integer -c 2 -r 44100 -q -