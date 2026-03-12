"\n

\n

\n Given 4 arrays wins, draws, scored, conceded of size N these arrays represent the stats of N teams. The array wins[i] represents the number of wins of the i'th team, draws[i] represents the number of draws of the i'th team, scored[i] represents the score of the i'th team, and conceded[i] represents the concede of the i'th team.\n

\n\n

\n For every win, a team is rewarded 3 points and for every draw, a team is rewarded 1 point. The task is to find the highest and second-highest scoring teams. If there is a tie between the points, it will be resolved by taking the difference between scored[i] - conceded[i].\n

\n\n

\n Return the indexes of the teams.\n

\n\n

\n Function Description\n

\n Complete the function findTopTwoTeams in the editor.\n

\n

\n findTopTwoTeams has the following parameters:\n

\n1. int[] wins: an array of integers representing the number of wins \n2. int[] draws: an array of integers representing the number of draws \n3. int[] scored: an array of integers representing the scores \n4. int[] conceded: an array of integers representing the conceded scores \n

\n

\n\n

\n Returns\n

\n int[]: an array of two integers representing the indexes of the top two teams\n

\n

\n

\n\n

\n Hello! Uber assessment comes with 4 coding questions. Here are the other 3 in the same batch 🥝 -\n

\n ![](.concat(U.default.src, )\n

\n

\n\n

\n ")

Example
Input
wins = [1, 2, 3]
draws = [1, 1, 1]
scored = [10, 20, 30]
conceded = [12, 23, 12]
Output
[2, 1]