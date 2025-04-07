Thanks for installing Ulises' <so_long> project ;)

To run the game, just type 'run'; it will use the map_default.ber in the folder, but you can give
it any other as an argument :o

For converting the assets to xpm:
./magick collectible.png collectible.xpm
./magick wall.png wall.xpm
./magick floor_sprite.png floor_sprite.xpm 
./magick player.png player.xpm
./magick enemy.png enemy.xpm
./magick exit.png exit.xpm

'git push' shortcut:
git config --global alias.upload 'git add . && git commit -m "v0.2wip" && git push'

'valgrind' command:

valgrind --leak-check=full --show-leak-kinds=all -s ./so_long map_default.ber
