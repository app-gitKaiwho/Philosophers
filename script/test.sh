#!/bin/sh

SLEEPTIME=2
RED="\033[31m"
GREEN="\033[32m"
ENDCOLOR="\033[0m"
FOLDER="./result/"
FILEPATH=`pwd`

if [ -d "$FOLDER" ]; then
  
  make fclean
  make re

  clear
  echo "\n${GREEN}[WELCOME]\nPlease understand that the test are made in real time and may take some time depending on the number of eat cycle (~1min for 100 cycle)\n"
  if [ -n "$1" ]; then
    NTEST=$1
  else
    echo "The number of eat cycle for inf. test is editiable as argument : ./script/test.sh [n_eat_cycle]."
    NTEST=100
  fi
  echo "Inf. test will be now tested with ["$NTEST"] eat cycle.\n"
  sleep $SLEEPTIME

  TESTNO=1
  echo "\ntest $TESTNO : 1 philo, 800ms to live, 200 to eat, 200 to sleep, should not eat, then die." | tee "$FOLDER"result"$TESTNO"r.txt
  ./philo 1 800 200 200 $NTEST | awk '{print "\t"$0 }' >> "$FOLDER"result"$TESTNO"r.txt
  if ! grep -w -- "died" "$FOLDER"result"$TESTNO"r.txt; then echo '\t0 death'; fi

  TESTNO=2
  echo "\ntest $TESTNO : 5 philo, 800ms to live, 200 to eat, 200 to sleep, 0 death." | tee "$FOLDER"result"$TESTNO"r.txt
  ./philo 5 800 200 200 $NTEST | awk '{print "\t"$0 }' >> "$FOLDER"result"$TESTNO"r.txt
  if ! grep -w -- "died" "$FOLDER"result"$TESTNO"r.txt; then echo '\t0 death'; fi

  TESTNO=3
  echo "\ntest $TESTNO : 5 philo, 800ms to live, 200 to eat, 200 to sleep will eat 7 time, 0 death." | tee "$FOLDER"result"$TESTNO"r.txt
  ./philo 5 800 200 200 7 | awk '{print "\t"$0 }' >> "$FOLDER"result"$TESTNO"r.txt
  if ! grep -w -- "died" "$FOLDER"result"$TESTNO"r.txt; then echo '\t0 death'; fi
  
  TESTNO=4
  echo "\ntest $TESTNO : 4 philo, 410ms to live, 200 to eat, 200 to sleep, 0 death." | tee "$FOLDER"result"$TESTNO"r.txt
  ./philo 4 410 200 200 $NTEST | awk '{print "\t"$0 }' >> "$FOLDER"result"$TESTNO"r.txt
  if ! grep -w -- "died" "$FOLDER"result"$TESTNO"r.txt; then echo '\t0 death'; fi

  TESTNO=5
  echo "\ntest $TESTNO : 4 philo, 310ms to live, 200 to eat, 100 to sleep, 1 philo should die." | tee "$FOLDER"result"$TESTNO"r.txt
  ./philo 4 310 200 100 $NTEST | awk '{print "\t"$0 }' >> "$FOLDER"result"$TESTNO"r.txt
  if ! grep -w -- "died" "$FOLDER"result"$TESTNO"r.txt; then echo '\t0 death'; fi

  echo "\nResult file are found under "$FOLDER"${ENDCOLOR}\n"
else 
  echo "${RED}Please use this script at ${FILEPATH%/*} ${FILEPATH///script/}like this : ./script/test.sh [n_eat_cycle]."
fi
