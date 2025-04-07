You are about to see my take on the Philosopher's project ;)

'git push' shortcut:
git config --global alias.upload 'git add . && git commit -m "v0.2wip" && git push'

'valgrind' command:

valgrind --leak-check=full --show-leak-kinds=all -s ./philo 4 510 200 200
