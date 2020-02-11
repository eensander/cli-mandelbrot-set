rm app
g++ -c main.cpp -std=gnu++11 -Wall -Wextra
g++ main.o -o app
rm main.o
