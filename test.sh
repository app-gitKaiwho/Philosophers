#!/bin/sh

make fclean
make re

SLEEPTIME=2
RED="\033[31m"
GREEN="\033[32m"
ENDCOLOR="\033[0m"
FOLDER="./result/"
echo "\n${GREEN}[WELCOME]\nPlease understand that the test are made in real time and may take some time depending on the number of eat cycle (~1min for 100 cycle)\n"
if [ -n "$1" ]; then
	NTEST=$1
else
  echo "The number of eat cycle for inf. test is editiable as argument : ./test.sh [n_eat_cycle]."
  NTEST=100
fi

echo "Inf. test will be tested with "$NTEST" eat cycle.\n"
sleep $SLEEPTIME

TESTNO=1
echo "test $TESTNO : 1 philo, 800ms to live, 200 to eat, 200 to sleep, should not eat, then die." | tee "$FOLDER"result"$TESTNO"r.txt
./philo 1 800 200 200 $NTEST >> "$FOLDER"result"$TESTNO"r.txt

TESTNO=2
echo "test $TESTNO : 5 philo, 800ms to live, 200 to eat, 200 to sleep, 0 death." | tee "$FOLDER"result"$TESTNO"r.txt
./philo 5 800 200 200 $NTEST >> "$FOLDER"result"$TESTNO"r.txt

TESTNO=3
echo "test $TESTNO : 5 philo, 800ms to live, 200 to eat, 200 to sleep will eat 7 time, 0 death." | tee "$FOLDER"result"$TESTNO"r.txt
./philo 5 800 200 200 7 >> "$FOLDER"result"$TESTNO"r.txt

TESTNO=4
echo "test $TESTNO : 4 philo, 410ms to live, 200 to eat, 200 to sleep, 0 death." | tee "$FOLDER"result"$TESTNO"r.txt
./philo 4 410 200 200 $NTEST >> "$FOLDER"result"$TESTNO"r.txt

TESTNO=5
echo "test $TESTNO : 4 philo, 310ms to live, 200 to eat, 100 to sleep, 1 philo should die." | tee "$FOLDER"result"$TESTNO"r.txt
./philo 4 310 200 100 $NTEST >> "$FOLDER"result"$TESTNO"r.txt

echo "\nResult file are found under "$FOLDER"${ENDCOLOR}\n"