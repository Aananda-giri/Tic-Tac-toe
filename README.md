# Tic-Tac-toe
Tic tac toe with:
    
    1. Play with computer mode
    2. two player mode.

## Play with computer mode (Working):
  According to wikihow, sure way to win (most of times) tic-tac-toe by always placing first move on one of 4 edges:
 - we have keept that (4-edges) data in db1
 - and to avoid loosing provided user_moves first and places on one of edges (data in db2)
 - also we need to prevent opponent from making three in a row provided s/he has already two in a row
 - place our three in a row provided we have already two in a row
 - and if above conditions not the case we can make a random move on the board


##Initial idea (not_implemented)
 - The initial idea was to store all possible moves in array (db1) and then compare current board positioins with database and selsct the winning or draw data (avoiding loosing data) from among datas that matches current board configurations.
 
 - Also tic_tac_toe board is symmmetrical [i.e. there are only 3 unique positions to begin with] i.e. only three positions to start with (from among 9 positioins) i.e. we can reduce database size by 1/3.
 - Total datas would be 9!/3 (i.e. 120,960 possible ways to play tic-tac-toe) [still huge amount of data to traverse through]
 - But wait, victory for player is defeat for opponent [i.e. winning_moves=loosing moves], and we can cut off draw_data [roughly another one_third->40,320]
 - Still alot of data to process and definitely implementation would be tidious

