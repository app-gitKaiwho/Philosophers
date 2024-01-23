[PREREQUISITE]<br>
libpthread<br>
make<br>

[EXE]<br>
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]<br>
<br>
[SCRIPTS]<br>
git.sh				: add, commit and push to both git repo, my own and the school's<br>
setupremote.sh is	: only used to link my github the internal intranet<br>
test.sh				: run a batch of test. Result are printed in console, detail in result<br>
<br>
[SCORE]<br>
100/100<br>
<br>
[IMPROVEMENT]<br>
<br>
If I had to do this again, I would name my variable explisitly to know if they need mutex or not for exmple :<br>
min_eat is not critical so I would call it smth OK_min_eat, and f_eat would be private_f_eat idk.<br>