/*
** messages.h for shootandrun in /home/melot_g/rendu/cpp_va
** 
** Made by gautier melot
** Login   <melot_g@epitech.net>
** 
** Started on  Mon Jul 21 17:44:08 2014 gautier melot
** Last update Thu Jul 24 13:13:33 2014 gautier melot
*/

#ifndef		MESSAGES_H_
# define	MESSAGES_H_

# define USAGE		"Usage: ./VanguardArmy [-l library_pathname] [-x size_x] [-y size_y] [-m map_file]"

# define ERR		"Error: "
# define MISS_ARG	"Invalid number of argument: You must precise a value after a flag."
# define INVAL_XY	"Invalid value: The value for x and y arguments must be integers."

# define SIGN_ERR	"Unable to initialise signal handler."

# define EMPTY_ML	"Empty line in the map: The map can't have lines of length 0."
# define WRONG_ML	"Wrong line in the map: The map can't have lines of different lengths."
# define EMPTY_MF	"Empty map file."
# define STOO_BIG	"Too big size for the map: Can't handle a map of more than 30x30."
# define STOO_SMA	"Too small size for the map: A map of less than 20x20 is unusable."
# define WRONG_CT	"Wrong cell type in the map: Only \'m\', \'r\' and \'p\' cell types are handled."

# define UNIT_NOP	"Trying to use a unit wich is not placed on the map."

# define INI_MSG_00	"The war is at it's uttermost point."
# define INI_MSG_01	"Red's Imperial Guard and Blue's Federated's Nations Army"
# define INI_MSG_02	"are fighting one each other for the sake of"
# define INI_MSG_03	"conquiering Anderla III,"
# define INI_MSG_04	"a planet with high startegic value."

# define INI_MSG_10	"The vanguard of each army now met on this site"
# define INI_MSG_11	"and they must utterly destroy the other one squad"
# define INI_MSG_12	"to prevent them to report their presence."

# define INI_MSG_20	"This will give your side the advantage of surprise,"
# define INI_MSG_21	"creating a turning point in this war"
# define INI_MSG_22	"wich shall make your army win !"

# define END_MSG_00	"\'s Army win this fight !"
# define END_MSG_01	"With this, the war shall be put to an end soon enough..."
# define END_MSG_02	"Thanks to you, your side shall conquier this tiny world !"

# define END_MSG_10	"Draw !"
# define END_MSG_11	"The war shall escalate, maybe even it will never ever end..."
# define END_MSG_12	"This world itself may be destroyed, and many lives lost with it."

#endif		/* !MESSAGES_H_ */
