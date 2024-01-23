[PREREQUISITE]
libpthread
make

[EXE]
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]

[SCRIPTS]
git.sh				: add, commit and push to both git repo, my own and the school's
setupremote.sh is	: only used to link my github the internal intranet
test.sh				: run a batch of test. Result are printed in console, detail in result

[SCORE]
100/100

[IMPROVEMENT]

If I had to do this again, I would name my variable explisitly to know if they need mutex or not for exmple :
min_eat is not critical so I would call it smth OK_min_eat, and f_eat would be private_f_eat idk